// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#ifdef WIN32
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>

#include <fftw3.h>
#include "xnl\xnl.h"
#else
#include <stdlib.h>
#include <stdint.h>
#include "xnl/xnl.h"
#include <fftw3.h>
#endif
// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
