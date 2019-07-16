#pragma once

class caMediaBlock
{
public:
	~caMediaBlock(){

	}

public:
	size_t position;
	size_t length;
	long64 timestamp;
	short flag;
	short serial;
	bool usetime;
	bool bEnd;
	caMediaBlock()
		:position(0)
		, length(0)
		, timestamp(0)
		, flag(0)
		, serial(0)
		, usetime(false)
		, bEnd(false){
	}

	caMediaBlock(size_t _position, size_t _length, long64 _timestamp, short _flag, short _serial)
		:position(_position)
		, length(_length)
		, timestamp(_timestamp)
		, flag(_flag)
		, serial(_serial)
	{
		usetime = (flag == MEDIA_STREAM_BEGIN);
		bEnd = (flag == MEDIA_STREAM_END);
	}

};



class caMediaStream
{
public:
	caMediaStream(int s, int b, int c);
	~caMediaStream();

protected:
	size_t					base_position;
	calist<caMediaBlock>	timelist;
	cavector<short>			media_data;
	caspinlock				_lock;
	ulong32					_identifier;
	int channel;
	int sample;
	int bitwide;

protected:
	uint32 mix_core(short * buffer, uint32 numsOfShort, short * serial, int mixcnt);
	uint32 mix(short * buffer, uint32 numsOfShort, int mixcnt);
	long64 getfirstTime_core(bool brefTime)const;
public:
	int write(short flags, short serial, const short * buffer, int numsOfShort, long64 capturetime);
	long64 getfirstTime(bool brefTime)const;
	size_t length(long64 refetime, bool * bNext)const;
	void setIdentifier(ulong32 id);
	ulong32 getIdentifier()const;
	bool mixToBuffer(short * data,size_t numOfShorts,long64 reftime, int mixcnt);
	bool isEmpty();
};

