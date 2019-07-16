// XMultiMixer.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"


XNLEXPORT xlong XI_STDCALL createMixer(xint sample, xint bits, xint channel, xint bufferedSize){
	caStreamMixer * pStream = new caStreamMixer();
	pStream->config(sample, bits, channel);
	return (xlong)pStream;
}

XNLEXPORT xbool putData(xlong hm, xint id,xlong timestamp, const short * data,xint offset, xint countOfShort, xint flags, xint serial){
	caStreamMixer * pStream = (caStreamMixer*)hm;
	pStream->putData(id, timestamp, data + offset, countOfShort, flags, serial);
	return true;
}

XNLEXPORT xint readData(xlong hm, xint * flagOut, xint flagCount, short * data, xint offset, xint countOfShort){
	caStreamMixer * pStream = (caStreamMixer*)hm;
	cavector<int> flags;
	int rd = pStream->readData(&flags, data + offset, countOfShort);
	if (flagCount > flags.size()){
		flagOut[0] = flags.size();
		for (int i = 0; i < flags.size(); i++){
			flagOut[i + 1] = flags[i];
		}
	}
	return rd;
}

XNLEXPORT void closeMixer(xlong hm){
	caStreamMixer * pStream = (caStreamMixer*)hm;
	pStream->reset();
	delete pStream;
}

XNLEXPORT void resetMixer(xlong hm){
	caStreamMixer * pStream = (caStreamMixer*)hm;
	pStream->reset();
}