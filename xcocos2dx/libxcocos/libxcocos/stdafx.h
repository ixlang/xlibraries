// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // �� Windows ͷ���ų�����ʹ�õ�����
// Windows ͷ�ļ�: 
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

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
