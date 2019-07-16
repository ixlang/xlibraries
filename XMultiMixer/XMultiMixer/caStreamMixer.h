#pragma once
class caStreamMixer
{
public:
	caStreamMixer();
	~caStreamMixer();

	typedef camapex<ulong32, caMediaStream*> streamMap;
	camapex<ulong32, caMediaStream*> _pStreams;
	int channel;
	int sample;
	int bitwide;

	caspinlock	mixlock;

	void putData(ulong32 identifier, long64 timestamp, const short * data, int numsOfShorts, int flags, short serial);
	int readData(cavector<int>*identifierlst, short * data, size_t numsOfShorts);
	void reset();
	void config(int s,int b,int c){
		sample = s;
		bitwide = b;
		channel = c;
	}
	//void delay();
protected:
	int readData_core(cavector<int>*identifierlst, short * data, size_t numsOfShorts, bool * bNext);

private:
	size_t mixout_shorts;
	long64 first_timestamp;
	long64 last_timestamp;
	bool firstdelay;
};

