// xcimg.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
/*#if _MSC_VER
#define snprintf _snprintf
#endif*/

#include <stdio.h>
#include <random>

#define cimg_OS 0
#include "CImg.h"
#include <mutex>

#ifdef WIN32
#define XCDECL __cdecl
#else
#define XCDECL __attribute__((__cdecl__))
#endif

#define STDC extern "C"

using namespace std;
using namespace cimg_library;
std::mutex gs_img_lock;

int get_bmp_length(CImg<unsigned char> & img) {
	unsigned int _width = img.width(), _height = img.height(), _spectrum = img.spectrum();
	const unsigned int
		align = (4 - (3 * _width) % 4) % 4,
		buf_size = (3 * _width + align)* _height,
		file_size = 54 + buf_size;
	
	return file_size;
}

int get_bmp(CImg<unsigned char> & img, unsigned char * buffer, int  buf_length) {

	if (img.is_empty()) {
		return 0;
	}

	unsigned char *  header = &buffer[0], align_buf[4] = { 0 };
	unsigned int _width = img.width(), _height = img.height(), _spectrum = img.spectrum();
	memset(buffer, 0, 54);
	const unsigned int
		align = (4 - (3 * _width) % 4) % 4,
		buf_size = (3 * _width + align)* _height,
		file_size = 54 + buf_size;

	if (buf_length < file_size){
		return 0;
	}

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
	header[0x1C] = 24;
	header[0x1D] = 0;
	header[0x22] = buf_size & 0xFF;
	header[0x23] = (buf_size >> 8) & 0xFF;
	header[0x24] = (buf_size >> 16) & 0xFF;
	header[0x25] = (buf_size >> 24) & 0xFF;
	header[0x27] = 0x1;
	header[0x2B] = 0x1;

	size_t pos = 54;

	const unsigned char
		*ptr_r = img.data(0, _height - 1, 0, 0),
		*ptr_g = (_spectrum >= 2) ? img.data(0, _height - 1, 0, 1) : 0,
		*ptr_b = (_spectrum >= 3) ? img.data(0, _height - 1, 0, 2) : 0;

	switch (_spectrum) {
	case 1: {
		cimg_forY(img, y) {
			cimg_forX(img, x) {
				const unsigned char val = (unsigned char)*(ptr_r++);
				buffer[pos++] = val;
				buffer[pos++] = val;
				buffer[pos++] = val;

			}
			for (int al = 0; al < align; al++) {
				buffer[pos++] = 0;
			}
			ptr_r -= 2 * _width;
		}
	} break;
	case 2: {
		cimg_forY(img, y) {
			cimg_forX(img, x) {
				buffer[pos++] = 0;
				buffer[pos++] = (unsigned char)(*(ptr_g++));
				buffer[pos++] = (unsigned char)(*(ptr_r++));
			}
			for (int al = 0; al < align; al++) {
				buffer[pos++] = 0;
			}
			ptr_r -= 2 * _width; ptr_g -= 2 * _width;
		}
	} break;
	default: {
		cimg_forY(img, y) {
			cimg_forX(img, x) {
				buffer[pos++] = (unsigned char)(*(ptr_b++));
				buffer[pos++] = (unsigned char)(*(ptr_g++));
				buffer[pos++] = (unsigned char)(*(ptr_r++));
			}
			for (int al = 0; al < align; al++) {
				buffer[pos++] = 0;
			}
			ptr_r -= 2 * _width; ptr_g -= 2 * _width; ptr_b -= 2 * _width;
		}
	}
	}
	return pos;
}


STDC void* XCDECL alloc_vcode(const char * image_text, int width, int height) {

	
	std::lock_guard<std::mutex> lock(gs_img_lock);

	std::random_device rd;
	std::mt19937 mt_rand(rd());
	std::uniform_real_distribution<double> fraction_dist;
	int text_size = strlen(image_text);

	int offset = width / text_size;
	int fontSize = offset * 1.5;
	int ytop = (height - fontSize) / 2;

	CImg<unsigned char> * pImg = new CImg<unsigned char>(width, height, 1, 3, 0);

	if (pImg == 0){
		return 0;
	}

	CImg<unsigned char> color(3);

	char letter[2] = { 0, 0 };
	for (unsigned int k = 0; k < text_size; ++k) {
		CImg<unsigned char> tmp;
		*letter = image_text[k];
		if (*letter) {

			cimg_forX(color, i) color[i] = (unsigned char)(128 + (mt_rand() % 127));

			unsigned char t_clo[] = { (unsigned char)(128 + (mt_rand() % 127)), (unsigned char)(128 + (mt_rand() % 127)), (unsigned char)(128 + (mt_rand() % 127)) };

			tmp.draw_text((int)(10 * (0.5f - fraction_dist(mt_rand))),
				ytop + (int)(ytop * (0.5f - fraction_dist(mt_rand))),
				letter,
				t_clo,
				0,
				1,
				fontSize).resize(-100, -100, 1, 3);

			const float sin_offset = (float)fraction_dist(mt_rand) * 3, sin_freq = (float)fraction_dist(mt_rand) / 7;
			cimg_forYC(*pImg, y, v) pImg->get_shared_row(y, 0, v).shift((int)(4 * std::cos(y*sin_freq + sin_offset)));
			pImg->draw_image(text_size + offset*k, tmp);
		}
	}

	CImg<unsigned char> copy = (+(*pImg)).fill(0);
	for (unsigned int l = 0; l < 3; ++l) {
		if (l) copy.blur(0.5f).normalize(0, 148);
		for (unsigned int k = 0; k < 10; ++k) {
			cimg_forX(color, i) color[i] = (unsigned char)(128 + fraction_dist(mt_rand) * 127);
			if (fraction_dist(mt_rand) < 0.5f) copy.draw_circle((int)(fraction_dist(mt_rand)*pImg->width()),
				(int)(fraction_dist(mt_rand)*pImg->height()),
				(int)(fraction_dist(mt_rand) * 30),
				color.data(), 0.6f, ~0U);
			else copy.draw_line((int)(fraction_dist(mt_rand)*pImg->width()),
				(int)(fraction_dist(mt_rand)*pImg->height()),
				(int)(fraction_dist(mt_rand)*pImg->width()),
				(int)(fraction_dist(mt_rand)*pImg->height()),
				color.data(), 0.6f);
		}
	}

	*pImg |= copy;
	pImg->noise(10, 2);
	*pImg = (+*pImg).fill(255) - *pImg;

	return pImg;
}


STDC int XCDECL get_buffer_req(void * img){
	if (img == 0){
		return 0;
	}
	return get_bmp_length(*(CImg<unsigned char>*)img);
}

STDC int XCDECL get_data(void * img, unsigned char * buffer, int  buf_length) {
	if (img == 0){
		return 0;
	}
	return get_bmp(*(CImg<unsigned char>*)img, buffer, buf_length);
}

STDC void XCDECL delloc_vcode(void * img){
	std::lock_guard<std::mutex> lock(gs_img_lock);
	if (img == 0){
		return ;
	}

	delete (CImg<unsigned char>*)img;
}
