// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

BOOL WINAPI DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	} 
	return TRUE;
}


static cocos2d::Size designResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);


void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}


class HelloWorld : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene()
	{
		return HelloWorld::create();
	}

	virtual bool init()
	{
		//////////////////////////////
		// 1. super init first
		if (!Scene::init()){
			return false;
		}

		auto visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		/////////////////////////////
		// 2. add a menu item with "X" image, which is clicked to quit the program
		//    you may modify it.

		// add a "close" icon to exit the progress. it's an autorelease object
		auto closeItem = MenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

		if (closeItem == nullptr ||
			closeItem->getContentSize().width <= 0 ||
			closeItem->getContentSize().height <= 0)
		{
			problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
		}
		else
		{
			float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
			float y = origin.y + closeItem->getContentSize().height / 2;
			closeItem->setPosition(Vec2(x, y));
		}

		// create menu, it's an autorelease object
		auto menu = Menu::create(closeItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 1);

		/////////////////////////////
		// 3. add your codes below...

		// add a label shows "Hello World"
		// create and initialize a label

		auto label = Label::createWithTTF("Hello world", "fonts/Marker Felt.ttf", 24);
		if (label == nullptr)
		{
			problemLoading("'fonts/Marker Felt.ttf'");
		}
		else
		{
			// position the label on the center of the screen
			label->setPosition(Vec2(origin.x + visibleSize.width / 2,
				origin.y + visibleSize.height - label->getContentSize().height));

			// add the label as a child to this layer
			this->addChild(label, 1);
		}

		// add "HelloWorld" splash screen"
		auto sprite = Sprite::create("HelloWorld.png");
		if (sprite == nullptr)
		{
			problemLoading("'HelloWorld.png'");
		}
		else
		{
			// position the sprite on the center of the screen
			sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

			// add the sprite as a child to this layer
			this->addChild(sprite, 0);
		}
		return true;
	}

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender) {
		Director::getInstance()->end();
	}

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);
};


class AppDelegate : cocos2d::Application {
public:
	AppDelegate() {

	}
	virtual ~AppDelegate() {
		AudioEngine::end();
	}

	virtual void initGLContextAttrs() {
		/*GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8, 0 };

		cocos2d::GLView::setGLContextAttrs(glContextAttrs);*/
	}


	virtual bool applicationDidFinishLaunching() {
		return true;
		/*
		auto director = Director::getInstance();
		auto glview = director->getOpenGLView();
		if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
			glview = GLViewImpl::createWithRect("HelloCpp", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
			glview = GLViewImpl::create("HelloCpp");
#endif
			director->setOpenGLView(glview);
		}
		
		// turn on display FPS
		director->setDisplayStats(true);
		
		// set FPS. the default value is 1.0/60 if you don't call this
		director->setAnimationInterval(1.0f / 60);
		
		// Set the design resolution
		glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
		auto frameSize = glview->getFrameSize();
		// if the frame's height is larger than the height of medium size.
		if (frameSize.height > mediumResolutionSize.height)
		{
			director->setContentScaleFactor(MIN(largeResolutionSize.height / designResolutionSize.height, largeResolutionSize.width / designResolutionSize.width));
		}
		// if the frame's height is larger than the height of small size.
		else if (frameSize.height > smallResolutionSize.height)
		{
			director->setContentScaleFactor(MIN(mediumResolutionSize.height / designResolutionSize.height, mediumResolutionSize.width / designResolutionSize.width));
		}
		// if the frame's height is smaller than the height of medium size.
		else
		{
			director->setContentScaleFactor(MIN(smallResolutionSize.height / designResolutionSize.height, smallResolutionSize.width / designResolutionSize.width));
		}

		//register_all_packages();

		// create a scene. it's an autorelease object
		auto scene = HelloWorld::createScene();

		// run
		director->runWithScene(scene);

		return true;*/
	}


	virtual void applicationDidEnterBackground() {
		/*Director::getInstance()->stopAnimation();

		AudioEngine::pauseAll();*/
	}


	virtual void applicationWillEnterForeground() {
		/*Director::getInstance()->startAnimation();
		AudioEngine::resumeAll();*/
	}


};

/*int main(int argc, char * argv[]) {
	AppDelegate app;
	return Application::getInstance()->run();
	return 0;
}
*/