#include "stdafx.h"
#include "caMediaStream.h"


caMediaStream::caMediaStream(int s, int b, int c)
{
	sample = s;
	bitwide = b;
	channel = c;
}


caMediaStream::~caMediaStream()
{
}



uint32 caMediaStream::mix_core(short * buffer, uint32 numsOfShort, short * serial, int mixcnt){

	size_t copied = 0;

	if (timelist.size() > 0){
		caMediaBlock * pFrame = &*timelist.begin();

		if (*serial == short(-1)){
			*serial = pFrame->serial;
		} else
		if (pFrame->serial != *serial){
			return 0;
		}

		copied = camin((size_t)numsOfShort, pFrame->length);

		long sourcepos = pFrame->position - base_position;

		if (mixcnt > 0){
			int final_mix_cnt = (mixcnt + 1);
			for (size_t i = 0; i < copied; i++){
				buffer[i] = short(((int(buffer[i]) * mixcnt) / final_mix_cnt) + (media_data[sourcepos + i] / final_mix_cnt));
			}
		} else{
			memcpy(buffer, &media_data[pFrame->position - base_position], copied * sizeof(short));
		}

		media_data.erase(0, copied);

		if (copied == pFrame->length){
			timelist.pop_head();
			if (media_data.size() == 0){
				timelist.clear();
				base_position = 0;
			} else{
				base_position += copied;
			}
		} else{
			pFrame->length -= copied;
			pFrame->position += copied;
			pFrame->timestamp += AudioUtils::bytes2ms(copied * sizeof(short), sample, bitwide, channel);
			pFrame->usetime = false;
			base_position += copied;
		}
	}
	return copied;
}

uint32 caMediaStream::mix(short * buffer, uint32 numsOfShort, int mixcnt){

	int copied = 0;
	int readed = 0;

	short _serial = short(-1);

	while (numsOfShort != 0){
		readed = mix_core(buffer, numsOfShort, &_serial, mixcnt);

		if (readed == 0){
			break;
		}

		copied += readed;
		buffer += readed;
		numsOfShort -= readed;
	}

	return copied;
}


int caMediaStream::write(short flags, short serial, const short * buffer, int numsOfShort, long64 capturetime){

	if (numsOfShort == 0){
		return 0;
	}

	bool needNewObj = true;

	_lock.lock();

	if (timelist.size() != 0){
		calist<caMediaBlock>::iterator last = --timelist.end();
		caMediaBlock * pFrame = &*last;
		if (pFrame->serial == serial){
			pFrame->length += numsOfShort;
			needNewObj = false;
			if (flags & MEDIA_STREAM_END){
				pFrame->bEnd = TRUE;
			}
		}
	}

	if (needNewObj == true){
		timelist.push_back(caMediaBlock(media_data.size() + base_position, numsOfShort, capturetime, flags, serial));
	}

	media_data.push_back(buffer, numsOfShort);

	_lock.unlock();

	return numsOfShort;
}

long64 caMediaStream::getfirstTime_core(bool brefTime)const{
	long64 timestamp = 0;


	if (timelist.size() != 0){
		const caMediaBlock * pFrame = &*timelist.begin();
		if (pFrame->usetime != brefTime){
			timestamp = pFrame->timestamp;
		}
	}


	return timestamp;
}

long64 caMediaStream::getfirstTime(bool brefTime)const{

	_lock.lock();
	long64 timestamp = getfirstTime_core(brefTime);
	_lock.unlock();

	return timestamp;
}


size_t caMediaStream::length(long64 refetime, bool * bNext)const{

	size_t numsOfBytes = 0;
	*bNext = false;
	_lock.lock();
	if (timelist.size() != 0){

		calist<caMediaBlock>::iterator iter = timelist.begin();
		short serial = iter->serial;
		numsOfBytes = iter->length;

		long64 realtime = 0;

		if (iter->usetime){
			realtime = iter->timestamp;
		}

		if (realtime > refetime){
			long64 timediff = realtime - refetime;
			numsOfBytes += AudioUtils::ms2bytes(sample, bitwide, channel, timediff);
		}
		
		if (iter->bEnd){
			*bNext = true;
		}

		iter++;

		while (iter != timelist.end()){
			if (serial != iter->serial){
				*bNext = true;
				break;
			}else
			if (iter->bEnd){
				*bNext = true;
			}
			numsOfBytes += iter->length;
			iter++;
		}
	}
	_lock.unlock();

	return numsOfBytes;
}

void caMediaStream::setIdentifier(ulong32 id){
	_identifier = id;
}

bool caMediaStream::isEmpty(){
	_lock.lock();
	bool be = timelist.size() == 0;
	_lock.unlock();

	return be;
}

ulong32 caMediaStream::getIdentifier()const{
	return _identifier;
}

bool caMediaStream::mixToBuffer(short * data, size_t numOfShorts, long64 reftime, int mixcnt){
	bool mixed = false;

	_lock.lock();
	if (timelist.size() != 0){

		size_t start = 0;

		long64 realtime = getfirstTime_core(false);
		
		if (realtime > reftime){
			long64 timediff = realtime - reftime;
			start = AudioUtils::ms2bytes(sample, bitwide, channel, timediff) / sizeof(short);
		}

		
		if (mixcnt > 0){
			size_t remix = camin(start, numOfShorts);
			for (size_t i = 0; i < remix; i++){
				data[i] = short((int(data[i]) * mixcnt) / (mixcnt + 1));
			}
		}

		if (start < numOfShorts){
			mix(data + start, numOfShorts - start, mixcnt);
		}

		mixed = true;
	}
	_lock.unlock();

	return mixed;
}