// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 从 Windows 头中排除极少使用的资料
// Windows 头文件: 
#include <windows.h>
#include <cocos/cocos2d.h>
#include <ui/CocosGUI.h>
#include <string.h>
#include "E:/Developments/Cadaqs/caNamespace/castudio/xcross/xcross/xnl.h"
#include "audio/include/SimpleAudioEngine.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
using namespace cocos2d::ui;
using namespace CocosDenshion;
USING_NS_CC;

#include "xid.h"

template<class T>
size_t _xcountof_heaper(T  arr_[], size_t t) { return t / sizeof(T); }
#define _xcountof(a) _xcountof_heaper(a, sizeof(a))

// TODO:  在此处引用程序需要的其他头文件
