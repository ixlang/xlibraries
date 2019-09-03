#pragma once

class XCApplication :
	public cocos2d::Application {
	XObject * xobject;
public:
	XCApplication(XObject * obj) {
		xobject = obj;
	}
	virtual ~XCApplication() {
		AudioEngine::end();
	}

	virtual void initGLContextAttrs() {
		gs_env->void_invoke(main_thread, xobject, xfunctions[x_initGLContextAttrs].xid);
	}


	virtual bool applicationDidFinishLaunching() {
		return gs_env->bool_invoke(main_thread, xobject, xfunctions[x_applicationDidFinishLaunching].xid);
	}


	virtual void applicationDidEnterBackground() {
		gs_env->void_invoke(main_thread, xobject, xfunctions[x_applicationDidEnterBackground].xid);
	}


	virtual void applicationWillEnterForeground() {
		gs_env->void_invoke(main_thread, xobject, xfunctions[x_applicationWillEnterForeground].xid);
	}
};

class XScene : public Scene {

public:
	double wh[2];
	bool withwh = false;

	XScene(XObject * obj) {
		setUserData(gs_env->referenceObject(obj));
	}

	virtual bool init() {
		return gs_env->bool_invoke(main_thread, getXObject(), xfunctions[x_NodeOnCreate].xid);
	}

	virtual bool original_init() {
		return Scene::init();
	}

	XObject * getXObject() {
		return (XObject *)getUserData();
	}

	bool to_create() {
		if (withwh) {
			return initWithSize(Size(wh[0], wh[1]));
		}
		return init();
	}

	void freeXObject() {
		XObject * pobj = getXObject();
		if (pobj != 0) {
			gs_env->dereferenceObject(pobj);
			setUserData(0);
		}
	}
};