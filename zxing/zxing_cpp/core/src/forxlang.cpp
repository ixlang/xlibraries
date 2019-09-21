#include <string>
#include <stdlib.h>
#include <cstring>
#include <typeinfo>
#include "../../../../../../../xcross/xnl.h"

#include "MultiFormatReader.h"
#include "MultiFormatWriter.h"
#include "BitMatrix.h"
#include "LuminanceSource.h"
#include "HybridBinarizer.h"
#include "TextUtfEncoding.h"

using namespace ZXing;

XNLEnv* gs_env = 0;

XNLEXPORT xint XI_STDCALL XNLMain(XNLEnv* env, xint version) {
	gs_env = env->getEnv();
	return 0;
}

XNLEXPORT xint XI_STDCALL XNLExit(XNLEnv* env) {
	env->releaseEnv(gs_env);
	gs_env = 0;
	return 0;
}

int get_bmp_length(BitMatrix& img, xbool naked) {
	unsigned int _width = img.width(), _height = img.height();
	const unsigned int
		align = (4 - (4 * _width) % 4) % 4,
		buf_size = (4 * _width + align) * _height,
		file_size = (naked ? 0 : 54) + buf_size;

	return file_size;
}

int get_bmp(BitMatrix &img, unsigned char* buffer, int  buf_length, xbool naked) {

	if (img.empty()) {
		return 0;
	}

	unsigned char* header = &buffer[0], align_buf[4] = { 0 };
	unsigned int _width = img.width(), _height = img.height();


	const unsigned int
		align = (4 - (4 * _width) % 4) % 4,
		buf_size = (4 * _width + align) * _height,
		file_size = (naked ? 0 : 54) + buf_size;

	if (buf_length < file_size) {
		return 0;
	}

	size_t pos = 0;

	if (!naked) {
		memset(buffer, 0, 54);
		header[0] = 'B'; header[1] = 'M';
		header[0x02] = file_size & 0xFF;
		header[0x03] = (file_size >> 8) & 0xFF;
		header[0x04] = (file_size >> 16) & 0xFF;
		header[0x05] = (file_size >> 24) & 0xFF;
		header[0x0A] = 0x36;
		header[0x0E] = 0x28;
		header[0x12] = _width & 0xFF;
		header[0x13] = (_width >> 8) & 0xFF;
		header[0x14] = (_width >> 16) & 0xFF;
		header[0x15] = (_width >> 24) & 0xFF;
		header[0x16] = _height & 0xFF;
		header[0x17] = (_height >> 8) & 0xFF;
		header[0x18] = (_height >> 16) & 0xFF;
		header[0x19] = (_height >> 24) & 0xFF;
		header[0x1A] = 1;
		header[0x1B] = 0;
		header[0x1C] = 32;
		header[0x1D] = 0;
		header[0x22] = buf_size & 0xFF;
		header[0x23] = (buf_size >> 8) & 0xFF;
		header[0x24] = (buf_size >> 16) & 0xFF;
		header[0x25] = (buf_size >> 24) & 0xFF;
		header[0x27] = 0x1;
		header[0x2B] = 0x1;
		pos = 54;
	}
	int* pclr = (int*)& buffer[pos];

	for (int y = 0; y < _height; y++) {
		for (int x = 0; x < _width; x++) {
			int offset = y * _width;
			pclr[offset + x] = img.get(x, y) ? 0xff000000 : 0xffffffff;
		}
	}
	
	for (int al = 0; al < align; al++) {
		buffer[pos++] = 0;
	}
	
	return pos;
}

XNLEXPORT XObject * XI_CDECL generator_qr(xint format, xstring content, xint width, xint height, xbool naked) {
	MultiFormatWriter writer((BarcodeFormat)format);
	

	std::wstring wstr = ZXing::TextUtfEncoding::FromUtf8(content);

	XObject* pimg = 0;

	try {

		BitMatrix matrix = writer.encode(wstr, width, height);
		
		int size = get_bmp_length(matrix, naked);
		pimg = gs_env->createByteArray(size);
		unsigned char* pdata = (unsigned char*)gs_env->getPointerOfArray(pimg);
		get_bmp(matrix, pdata, size, naked);
	}
	catch (...) {

	}
	return pimg;
}


#include "DecodeHints.h"
#include "GenericLuminanceSource.h"
#include "Result.h"
using Binarizer = ZXing::HybridBinarizer;

XNLEXPORT XObject* XI_CDECL
read_qrcode(xbyte* data,xint offset, xint width, xint height, xint row_bytes, xint pixel_bytes,
	xint index_r,
	xint index_g, xint index_b, xint * num_bits, xint* status, xint* format)
{
	const void *buffer  = data + offset;
	ZXing::DecodeHints hints;
	hints.setShouldTryHarder(true);
	ZXing::MultiFormatReader reader(hints);

	ZXing::GenericLuminanceSource source((int)width, (int)height, buffer, row_bytes, pixel_bytes, index_r, index_g, index_b);
	Binarizer binImage(std::shared_ptr<ZXing::LuminanceSource>(&source, [](void*) {}));

	ZXing::Result reader_result = reader.read(binImage);

	*num_bits = reader_result.numBits();
	*status = static_cast<int>(reader_result.status());

	if (reader_result.status() != ZXing::DecodeStatus::NoError) {
		return 0;
	}

	*format = static_cast<int>(reader_result.format());

	auto s = ZXing::TextUtfEncoding::ToUtf8(reader_result.text());

	XObject* bytes = gs_env->createByteArray(sizeof(char) * s.size());
	unsigned char* pdata = (unsigned char*)gs_env->getPointerOfArray(bytes);

	std::memcpy(pdata, s.data(), sizeof(char) * s.size());

	return bytes;
}
