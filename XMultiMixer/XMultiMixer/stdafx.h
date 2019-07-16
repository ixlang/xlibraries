// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>

#define MEDIA_STREAM_INVALID		0xf
#define MEDIA_STREAM_BEGIN			0x0
#define MEDIA_STREAM_DATA			0x1
#define MEDIA_STREAM_END			0x2
#define MEDIA_MARK_FILTER			0x3

#include <castl.h>
#include <camap.h>
#include <calist.h>
#include <cavector.h>
#include <casynch.h>
using namespace castl;
#include <xnl.h>

#include "AudioUtils.h"
#include "caMediaStream.h"
#include "caStreamMixer.h"


// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
