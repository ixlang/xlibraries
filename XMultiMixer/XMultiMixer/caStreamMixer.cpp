#include "stdafx.h"

caStreamMixer::caStreamMixer()
{
	mixout_shorts = 0;
	first_timestamp = 0;
	last_timestamp = 0;
	firstdelay = false;
}


caStreamMixer::~caStreamMixer()
{
}

void caStreamMixer::reset(){
	mixlock.lock();
	while (_pStreams.size() > 0){
		delete * _pStreams.begin();
		_pStreams.erase(_pStreams.begin());
	}
	mixlock.unlock();
}

void caStreamMixer::putData(ulong32 identifier, long64 timestamp, const short * data, int numsOfShorts, int flags, short serial){

	caMediaStream * pStream = nilptr;

	mixlock.lock();

	streamMap::iterator iter = _pStreams.find(identifier);

	if (iter == streamMap::NullEnd()){
		pStream = new caMediaStream(sample, bitwide, channel);
		pStream->setIdentifier(identifier);
		_pStreams.put(identifier, pStream);
	} else{
		pStream = *iter;
	}

	pStream->write(flags, serial, data, numsOfShorts, timestamp);

	mixlock.unlock();
}

int caStreamMixer::readData(cavector<int>*identifierlst, short * data, size_t numsOfShorts){

	mixlock.lock();
	bool  bNext = false;
	size_t start = 0;
	size_t readed = readData_core(identifierlst, data, numsOfShorts, &bNext);

	numsOfShorts -= readed;
	start += readed;

	while (bNext && numsOfShorts > 0){
		readed = readData_core(identifierlst, data + start, numsOfShorts, &bNext);
		if (readed == 0){
			break;
		}

		numsOfShorts -= readed;
		start += readed;
	}

	mixlock.unlock();

	return start;
}


int caStreamMixer::readData_core(cavector<int>*identifierlst, short * data, size_t numsOfShorts, bool * bNext){

	size_t readable = 0;
	bool bContinueRead = false;

	if (_pStreams.size() != 0){
		streamMap::iterator iter = _pStreams.begin();

		long64 reftime = 0;
		long64 realtime = 0;
		//先获取一个参考时间
		while (iter != streamMap::NullEnd()){
			if ((*iter)->isEmpty()){
				delete *iter;
				_pStreams.erase(iter);
				iter = _pStreams.begin();
				continue;
			}

			reftime = (*iter)->getfirstTime(true);
			long64 streamtime = (*iter)->getfirstTime(false);
			if (reftime != 0){
				break;
			}
			if ((realtime == 0) || (realtime > streamtime)){
				realtime = streamtime;
			}
			iter++;
		}

		//获取不到参考时间 就使用真实时间
		if (reftime == 0){
			reftime = realtime;
		}

		if (reftime != 0){
			iter = _pStreams.begin();
			while (iter != streamMap::NullEnd()){
				if ((*iter)->isEmpty()){
					delete *iter;
					_pStreams.erase(iter);
					iter = _pStreams.begin();
					continue;
				}
				size_t stream_len = (*iter)->length(reftime, &bContinueRead);
				if (readable == 0 || readable > stream_len){
					readable = stream_len;
				}
				if (bContinueRead){
					*bNext = true;
				}
				iter++;
			}

			if (readable != 0){
				readable = camin(readable, numsOfShorts);

				int mix_cnt = 0;
				iter = _pStreams.begin();
				while (iter != streamMap::NullEnd()){
					caMediaStream * pStream = (*iter);
					if (pStream->mixToBuffer(data, readable, reftime, mix_cnt)){
						mix_cnt++;
						identifierlst->push_back(pStream->getIdentifier());;
					}
					iter++;
				}
			}
		}
	}

	return readable;
}