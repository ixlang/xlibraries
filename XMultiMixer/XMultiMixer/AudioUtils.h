#pragma once
#define MIN_SAMPLE_TIME 20
#define BITS_OF_BYTE	8

class AudioUtils{
public:
	static size_t AudioUtils::ms2bytes(int sample_rate, int bit_wide, int channel, long64 million_second){
		return (size_t)((sample_rate * bit_wide * channel * million_second) / (BITS_OF_BYTE * 1000));
	}

	static long64 AudioUtils::bytes2ms(size_t data_bytelength, int sample_rate, int bit_wide, int channel){
		return ((long64)data_bytelength * BITS_OF_BYTE * 1000) / (sample_rate * bit_wide * channel);
	}
};