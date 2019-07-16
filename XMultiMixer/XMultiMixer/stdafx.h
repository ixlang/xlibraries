// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
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


// TODO:  在此处引用程序需要的其他头文件
