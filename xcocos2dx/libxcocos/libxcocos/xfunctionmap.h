#pragma once

XLANG_VIRTUAL_METHOD xfunctions[] = {
	{ x_initGLContextAttrs, "/void@/Cocos2dx/Application/initGLContextAttrs()", 0 },
	{ x_applicationDidFinishLaunching, "/bool@/Cocos2dx/Application/applicationDidFinishLaunching()", 0 },
	{ x_applicationDidEnterBackground, "/void@/Cocos2dx/Application/applicationDidEnterBackground()", 0 },
	{ x_applicationWillEnterForeground, "/void@/Cocos2dx/Application/applicationWillEnterForeground()", 0 },
	{ x_NodeOnCreate, "/bool@/Cocos2dx/Node/onCreate()", 0 },
	{ x_RunnableRun , "/void@/Cocos2dx/Runnable/run()", 0},
	{ x_NativeFinalize , "/void@/Cocos2dx/Refable/native_finalize()", 0 },
	{ x_WidgetTouch , "/void@/Cocos2dx/Widget/onTouch(/int)", 0 },
	{ x_WidgetClick , "/void@/Cocos2dx/Widget/onClick()", 0 },
	{ x_WidgetFocused , "/void@/Cocos2dx/Widget/onFocus(/bool)", 0 }
};