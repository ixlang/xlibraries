// libxcocos.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "XCApplication.h"
#include "xfunctionmap.h"

XNLEnv * gs_env = 0;
XContext * main_thread = 0;
bool main_release = false;

enum CC_OBJECT_TYPE {
	CC_UNKNOWTYPE = -1,
	CC_OBJ_APPLICATION,
	CC_OBJ_SCENE,
	CC_OBJ_DIRECTOR,
	CC_OBJ_SIMPLEAUDIO
};

// 底层已经被释放  只有上层引用
#define REF_UNUSED 1

#define REF_FINALIZED 2

void cc2x_cleanup(Ref * ref, void * obj) {
	XObjectId* pid = gs_env->getObjectId((XObject*)obj); 
	gs_env->dereferenceObject((XObject*)obj);

	// 上层没有释放 则保留一个ID
	if ((ref->xflags & REF_FINALIZED) == 0) {
		ref->xflags |= REF_UNUSED;
		ref->xobject = pid;
	}else {
		ref->xflags = 0;
	}
}

void cc2x_reactive(Ref * ref, void * obj) {
	if ((ref->xflags & REF_UNUSED) == REF_UNUSED) {
		ref->xobject = gs_env->refObjectById((XObjectId*)ref->xobject);
		ref->xflags = 0;
	}
}

void initXMethod() {

	Ref::setDestroyProc(cc2x_reactive, cc2x_cleanup);

	for (xint i = 0; i < _xcountof(xfunctions); i++) {
		xfunctions[i].xid = gs_env->getMethodId(xfunctions[i].methodpath);
		assert(xfunctions[i].xid != -1);
	}
}

XObject * string2XString(const std::string & data) {
	XObject * strobj = gs_env->createObject();
	gs_env->setValue(main_thread, strobj, data.c_str(), data.length());
	return strobj;
}

void InstallWidgetEvent(Widget * w) {
	w->addTouchEventListener([=](Ref* ref, Widget::TouchEventType type) {
		XObject * pobjId = (XObject *)ref->xobject;
		if (pobjId != 0) {
			gs_env->void_Invoke(main_thread, pobjId, xfunctions[x_WidgetTouch].xid, (int)type);
		}
	});

	w->addClickEventListener([=](Ref* ref) {
		XObject * pobjId = (XObject *)ref->xobject;
		if (pobjId != 0) {
			gs_env->void_invoke(main_thread, pobjId, xfunctions[x_WidgetClick].xid);
		}
	});

	w->setFocusListener([=](Widget* w, bool focused) {
		XObject * pobjId = (XObject *)w->xobject;
		if (pobjId != 0) {
			gs_env->void_Invoke(main_thread, pobjId, xfunctions[x_WidgetFocused].xid, focused);
		}
	});
}

XNLEXPORT void XI_CDECL xcocox_object_dtor(xlong handle, xint proid) {
	switch (proid) {
	case CC_OBJ_APPLICATION:
		break;
	case CC_OBJ_DIRECTOR:
		break;
	case CC_OBJ_SIMPLEAUDIO:
		SimpleAudioEngine::end();
		break;
	}
}

XNLEXPORT xlong XI_CDECL create_refable_object_string_params(xint proid, XObject * obj, xstring v, XObject * params) {
	Ref * ref = 0;

	switch (proid)
	{
	case CC_BUTTONCREATEPLIST: {
		XObject *images[3];

		xstring normal = 0, selected = 0, disabled = 0;
		int ln;

		 
		gs_env->getElementValue(main_thread, params, 0, images, 3);

		gs_env->getStringValue(images[0], &normal, &ln);
		gs_env->getStringValue(images[1], &selected, &ln);
		gs_env->getStringValue(images[2], &disabled, &ln);

		Button * button = Button::create(normal, selected == 0 ? "" : selected, disabled == 0 ? "" : disabled, TextureResType::PLIST);
		InstallWidgetEvent(button);
		ref = button;
	}
								  break;
	case CC_BUTTONCREATE: {
		XObject *images[3];

		xstring normal = 0, selected = 0, disabled = 0;
		int ln;


		gs_env->getElementValue(main_thread, params, 0, images, 3);

		gs_env->getStringValue(images[0], &normal, &ln);
		gs_env->getStringValue(images[1], &selected, &ln);
		gs_env->getStringValue(images[2], &disabled, &ln);
		Button * button = Button::create(normal, selected == 0 ? "" : selected, disabled == 0 ? "" : disabled, TextureResType::LOCAL);
		InstallWidgetEvent(button);
		ref = button;
	}
		break;
	case CC_GLVIEWCREATEWITHRECT: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		ref = GLViewImpl::createWithRect(v, Rect(param[0], param[1], param[2], param[3]));

	}
		break;
	case CC_GLVIEWCREATE: {
		ref = GLViewImpl::create(v);
	}
						  break;
	case CC_GLVIEWCREATEWITHFULLSCREEN: {
		ref = GLViewImpl::createWithFullScreen(v);
	}
		break;

	case CC_CREATESPRITE: {
		if (params != 0) {
			double * param = (double*)gs_env->getPointerOfArray(params);
			ref = Sprite::create(v, Rect(param[0], param[1], param[2], param[3]));
		}else {
			ref = Sprite::create(v);
		}
	}
	 break;
	case CC_CREATEDIRECTOR: {
		ref = Director::getInstance();
	}
	break;
	case CC_ROTATEBYCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		xlong len = gs_env->getLengthOfArray(params);
		if (len == 2) {
			ref = RotateBy::create(param[0], param[1]);
		}
		else {
			ref = RotateBy::create(param[0], param[1], param[2]);
		}
		break;
	}
	case CC_MOVEBYCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		xlong len = gs_env->getLengthOfArray(params);
		if (len == 2) {
			ref = MoveBy::create(param[0], Vec2(param[1], param[2]));
		} 
		else {
			ref = MoveBy::create(param[0], Vec3(param[1], param[2], param[3]));
		}
		break;
	}
	case CC_REPEATFOREVERCREATE: {
		xlong * param = (xlong*)gs_env->getPointerOfArray(params);
		ref = RepeatForever::create((ActionInterval*)param[0]);
		break;
	}
	case CC_REPEATCREATE: {
		xlong * param = (xlong*)gs_env->getPointerOfArray(params);
		ref = Repeat::create((ActionInterval*)param[0], param[1]);
		break;
	}
	case CC_SKEWBYCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		ref = SkewBy::create(param[0], param[1], param[2]);
		break;
	}
	case CC_SKEWTOCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		ref = SkewTo::create(param[0], param[1], param[2]);
		break;
	}
	case CC_JUMPBYCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		ref = JumpBy::create(param[0], Vec2(param[1], param[2]), param[3], param[4] + 0.5f);
		break;
	}
	case CC_FADETOCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		ref = FadeTo::create(param[0], param[1] * 255);
		break;
	}
	case CC_FADEINCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		ref = FadeIn::create(param[0]);
		break;
	}
	case CC_TINTTOCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		ref = TintTo::create(param[0], param[1] * 255, param[2] * 255, param[3] * 255);
		break;
	}
	case CC_TINTBYCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		ref = TintBy::create(param[0], param[1] * 255, param[2] * 255, param[3] * 255);
		break;
	}
	case CC_FADEOUTCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		ref = FadeOut::create(param[0]);
		break;
	}
	case CC_BEZIERBYCREATE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		ccBezierConfig bc = {
			Vec2(param[1], param[2]),
			Vec2(param[3], param[4]),
			Vec2(param[5], param[6]),
		};

		ref = BezierBy::create(param[0], bc);
		break;
	}
	case CC_ACTCREATESPEED: {
		XObject * acts[2];
		gs_env->getElementValue(main_thread, params, 0, acts, 2);

		xlong h;
		double sp;
		gs_env->getLongValue(acts[0], &h);
		gs_env->getDoubleValue(acts[1], &sp);

		ref = Speed::create((ActionInterval*)h, sp);
		break;
	}
	case CC_EASERATEACTIONCREATE: {
		XObject * acts[2];
		gs_env->getElementValue(main_thread, params, 0, acts, 2);

		xlong h;
		double sp;
		gs_env->getLongValue(acts[0], &h);
		gs_env->getDoubleValue(acts[1], &sp);

		ref = EaseRateAction::create((ActionInterval*)h, sp);
		break;
	}
	case CC_EASEINCREATE: {
		XObject * acts[2];
		gs_env->getElementValue(main_thread, params, 0, acts, 2);

		xlong h;
		double sp;
		gs_env->getLongValue(acts[0], &h);
		gs_env->getDoubleValue(acts[1], &sp);

		ref = EaseIn::create((ActionInterval*)h, sp);
		break;
	}
	case CC_EASEOUTCREATE: {
		XObject * acts[2];
		gs_env->getElementValue(main_thread, params, 0, acts, 2);

		xlong h;
		double sp;
		gs_env->getLongValue(acts[0], &h);
		gs_env->getDoubleValue(acts[1], &sp);

		ref = EaseOut::create((ActionInterval*)h, sp);
		break;
	}
	case CC_EASEINOUTCREATE: {
		XObject * acts[2];
		gs_env->getElementValue(main_thread, params, 0, acts, 2);

		xlong h;
		double sp;
		gs_env->getLongValue(acts[0], &h);
		gs_env->getDoubleValue(acts[1], &sp);

		ref = EaseInOut::create((ActionInterval*)h, sp);
		break;
	}
	case CC_FOLLOWCREATE: {
		XObject * acts[2];
		gs_env->getElementValue(main_thread, params, 0, acts, 2);

		xlong h;
		gs_env->getLongValue(acts[0], &h);
		double * dp = (double *)gs_env->getPointerOfArray(acts[1]);
		int len = gs_env->getLengthOfArray(acts[1]);

		if (len == 4) {
			ref = Follow::create((Node*)h, Rect(dp[0], dp[1], dp[2], dp[3]));
		}
		else {
			ref = Follow::createWithOffset((Node*)h, dp[0], dp[1], Rect(dp[2], dp[3], dp[4], dp[5]));
		}
		break;
	}
	case CC_LABELCREATE: {
		int len = gs_env->getLengthOfArray(params);

		XObject * acts[6];
		gs_env->getElementValue(main_thread, params, 0, acts, len);

		xstring fontpath;
		int fl;
		double fontsize, cx, cy;
		int ha, va;

		gs_env->getStringValue(acts[0], &fontpath, &fl);
		gs_env->getDoubleValue(acts[1], &fontsize);
		Label * plab = 0;
		if (len == 6) {
			gs_env->getDoubleValue(acts[2], &cx);
			gs_env->getDoubleValue(acts[3], &cy);
			gs_env->getIntValue(acts[4], &ha);
			gs_env->getIntValue(acts[5], &va);

			plab = Label::createWithTTF(v, fontpath, fontsize, Size(cx, cy), (TextHAlignment)ha, (TextVAlignment)va);
		}
		else {
			plab = Label::createWithTTF(v, fontpath, fontsize);
		}
		ref = plab;
		break;
	}
	case CC_LABELCREATESYS: {
		int len = gs_env->getLengthOfArray(params);

		XObject * acts[6];
		gs_env->getElementValue(main_thread, params, 0, acts, len);

		xstring fontpath;
		int fl;
		double fontsize, cx, cy;
		int ha, va;

		gs_env->getStringValue(acts[0], &fontpath, &fl);
		gs_env->getDoubleValue(acts[1], &fontsize);

		if (len == 6) {
			gs_env->getDoubleValue(acts[2], &cx);
			gs_env->getDoubleValue(acts[3], &cy);
			gs_env->getIntValue(acts[4], &ha);
			gs_env->getIntValue(acts[5], &va);

			ref = Label::createWithSystemFont(v, fontpath, fontsize, Size(cx, cy), (TextHAlignment)ha, (TextVAlignment)va);
		}
		else {
			ref = Label::createWithSystemFont(v, fontpath, fontsize);
		}
		break;
	}
	default:
		break;
	}

	if (ref != 0) {
		// 本身的一个引用是给autorelease用的
		ref->retain();
		ref->xobject = gs_env->referenceObject(obj);
	}

	return (xlong)ref;
}

XNLEXPORT xlong XI_CDECL xcocos_func_param_long_objs(xlong handle, xint proid, xstring v, XObject* params) {
	switch (proid)
	{
	case CC_SAEPLAYEFFECTLOOP:{
			double * param = (double*)gs_env->getPointerOfArray(params);
			if (param != 0) {
				((SimpleAudioEngine*)handle)->playEffect(v, true, param[0], param[1], param[2]);
			}
			break;
		}
	case CC_SAEPLAYEFFECT: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((SimpleAudioEngine*)handle)->playEffect(v, false, param[0], param[1], param[2]);
		}
		break;
	}
	}
	return 0;
}

XNLEXPORT xlong XI_CDECL xcocox_long_string_func(xlong handle, xint proid, xstring v) {
	switch (proid)
	{
	case CC_SAEUNLOADEFFECT:
	{
		((SimpleAudioEngine *)handle)->unloadEffect(v);
	}
	break;
	case CC_SAEPRELOADEFFECT:
	{
		 ((SimpleAudioEngine *)handle)->preloadEffect(v);
	}
	break;
	case CC_SAEPLAYEFFECT:
	{
		return ((SimpleAudioEngine *)handle)->playEffect(v);
	}
	break;
	case CC_NODEGETCHILDBYNAME:
	{
		return (xlong)((Node *)handle)->getChildByName(v);
	}
		break;
	case CC_NODEGETCOMPONENT:
	{
		return (xlong)((Node *)handle)->getComponent(v);
	}
		break;
	}
	return 0;
}

XNLEXPORT xlong XI_CDECL xcocox_long_int_func_long(xlong handle, xint proid, xlong param) {
	switch (proid)
	{
	case CC_LISTVIEWGETINDEX:
		return (xlong)((ListView *)handle)->getIndex((Widget*)param);
		break;
	case CC_NODEADDCOMPONENT:
		return (xlong)((Node *)handle)->addComponent((Component*)param);
		break;
	case CC_NODERUNACT: {
		return (xlong)((Node *)handle)->runAction((Action*)param);
	}
		break;
	}
	return 0;
}
XNLEXPORT xlong XI_CDECL xcocox_long_int_func(xlong handle, xint proid, xint v) {
	switch (proid)
	{
	case CC_LISTVIEWGETITEM:
		return (xlong) ((ListView *)handle)->getItem(v);
		break;
	case CC_DIRGETMATRIX:
		return (xlong) new Mat4(((Director *)handle)->getMatrix((MATRIX_STACK_TYPE)v));
		break;
	case CC_DIRGETPROJECTIONMATRIX:
		return (xlong) new Mat4(((Director *)handle)->getProjectionMatrix(v));
		break;
	case CC_NODEGETCHILDBYTAG:
	{
		return (xlong)((Node *)handle)->getChildByTag(v);
	}
	
		break;
	case CC_NODEGETACTIONBYTAG:
	{
		return (xlong)((Node *)handle)->getActionByTag(v);
	}
		break;
	case CC_NODEGETNUMBEROFRUNNINGACTIONSBYTAG:
		return (xlong)((Node *)handle)->getNumberOfRunningActionsByTag(v);
		break;
	default:
		break;
	}
	return 0;
}

XNLEXPORT void XI_CDECL xcocox_void_func_int_long(xlong handle, xint proid, xint v1, xlong param) {
	switch (proid)
	{
	case CC_LISTVIEWINSERTCUSTOMITEM:
		((ListView *)handle)->insertCustomItem((Widget*)param, v1);
		break;
	case CC_DIRLOADMATRIX:
		((Director *)handle)->loadMatrix((MATRIX_STACK_TYPE)v1, *(Mat4*)param);
		break;
	case CC_DIRLOADPROJECTIONMATRIX:
		((Director *)handle)->loadProjectionMatrix(*(Mat4*)param, v1);
		break;
	case CC_DIRMULTIPLYMATRIX:
		((Director *)handle)->multiplyMatrix((MATRIX_STACK_TYPE)v1, *(Mat4*)param);
		break;
	case CC_DIRMULTIPLYPROJECTIONMATRIX:
		((Director *)handle)->multiplyProjectionMatrix(*(Mat4*)param, v1);
		break;
	case CC_NODEADDCHILD:
		((Node *)handle)->addChild((Node*)param, v1);
		break;
	case CC_NODEREMOVECHILDBYTAG:
		((Node *)handle)->removeChildByTag(v1, param);
		break;
	case CC_NODEREORDERCHILD:
		((Node *)handle)->reorderChild((Node*)param, v1);
		break;
	default:
		break;
	}
}

void cdecl xcocox_void_func_int_long_int_string(xlong handle, xint proid, xint v1, xlong param, xstring name) {
	switch (proid)
	{
	case CC_LAYOUTSETBACKGROUNDIMAGE:
		((Layout *)handle)->setBackGroundImage(name, (TextureResType)v1);
		break;
	case CC_SAEPLAYBACKGROUNDMUSIC:
		((SimpleAudioEngine *)handle)->playBackgroundMusic(name, v1 != 0);
		break;
	case CC_NODEADDCHILD:
		((Node *)handle)->addChild((Node*)param, v1, name);
		break;
	case CC_NODEREMOVECHILDBYNAME:
		((Node *)handle)->removeChildByName(name, param != 0);
		break;

	default:
		break;
	}
}

XNLEXPORT void XI_CDECL xcocox_void_func_int_long_int(xlong handle, xint proid, xint v1, xlong param, xint v2) {
	switch (proid)
	{
	case CC_NODEADDCHILD:
		((Node *)handle)->addChild((Node*)param, v1, v2);
		break;
	case CC_NODEREMOVECHILD:
		((Node *)handle)->removeChild((Node*)param, v1 != 0);
		break;
	default:
		break;
	}
}

XNLEXPORT void XI_CDECL xcocox_void_func_int(xlong handle, xint proid, xint v) {
	switch (proid)
	{
	case CC_LISTVIEWSETCURSELECTEDINDEX:
		((ListView *)handle)->setCurSelectedIndex(v);
		break;
	case CC_LISTVIEWSETMAGNETICALLOWEDOUTOFBOUNDARY:
		((ListView *)handle)->setMagneticAllowedOutOfBoundary(0 != v);
		break;
	case CC_LISTVIEWSETMAGNETICTYPE:
		((ListView *)handle)->setMagneticType((ListView::MagneticType)v);
		break;
	case CC_LISTVIEWSETGRAVITY:
		((ListView *)handle)->setGravity((ListView::Gravity)v);
		break;
	case CC_LISTVIEWREMOVEITEM:
		((ListView *)handle)->removeItem(v);
		break;
	case CC_LISTVIEWINSERTDEFAULTITEM:
		((ListView *)handle)->insertDefaultItem(v);
		break;
	case CC_SCROLLVIEWSETSCROLLBARAUTOHIDEENABLED:
		((ScrollView *)handle)->setScrollBarAutoHideEnabled(v != 0);
		break;
	case CC_SCROLLVIEWSETSCROLLBAROPACITY:
		((ScrollView *)handle)->setScrollBarOpacity(v);
		break;
	case CC_SCROLLVIEWSETSCROLLBARENABLED:
		((ScrollView *)handle)->setScrollBarEnabled(0 != v);
		break;
	case CC_SCROLLVIEWSETINERTIASCROLLENABLED:
		((ScrollView *)handle)->setInertiaScrollEnabled(0 != v);
		break;
	case CC_SCROLLVIEWSETBOUNCEENABLED:
		((ScrollView *)handle)->setBounceEnabled(0 != v);
		break;
	case CC_SCROLLVIEWSETDIRECTION:
		((ScrollView *)handle)->setDirection((ScrollView::Direction)v);
		break;
	case CC_ABSTRACTCHECKBUTTONSETSELECTED:
		((AbstractCheckButton *)handle)->setSelected(0 != v);
		break;
	case CC_LAYOUTSETPASSFOCUSTOCHILD:
		((Layout *)handle)->setPassFocusToChild(0 != v);
		break;
	case CC_LAYOUTSETLOOPFOCUS:
		((Layout *)handle)->setLoopFocus(0 != v);
		break;
	case CC_LAYOUTSETLAYOUTTYPE:
		((Layout *)handle)->setLayoutType((Layout::Type)v);
		break;
	case CC_LAYOUTSETCLIPPINGTYPE:
		((Layout *)handle)->setClippingType((Layout::ClippingType)v);
		break;
	case CC_LAYOUTSETCLIPPINGENABLED:
		((Layout *)handle)->setClippingEnabled(0 != v);
		break;
	case CC_LAYOUTSETBACKGROUNDIMAGEOPACITY:
		((Layout *)handle)->setBackGroundImageOpacity(v);
		break;
	case CC_LAYOUTSETBACKGROUNDCOLOROPACITY:
		((Layout *)handle)->setBackGroundColorOpacity(v);
		break;
	case CC_LAYOUTSETBACKGROUNDIMAGESCALE9ENABLED:
		((Layout *)handle)->setBackGroundImageScale9Enabled(0 != v);
		break;
	case CC_LAYOUTSETBACKGROUNDCOLORTYPE:
		((Layout *)handle)->setBackGroundColorType((Layout::BackGroundColorType)v);
		break;
	case CC_SAESTOPEFFECT:
		((SimpleAudioEngine *)handle)->stopEffect(v);
		break;
	case CC_SAERESUMEEFFECT:
		((SimpleAudioEngine *)handle)->resumeEffect(v);
		break;
	case CC_SAEPAUSEEFFECT:
		((SimpleAudioEngine *)handle)->pauseEffect(v);
		break;
	case CC_SAESTOPBACKGROUNDMUSIC:
		((SimpleAudioEngine *)handle)->stopBackgroundMusic(0 != v);
		break;
	case CC_BTNSETTITLEALIGNMENT:
		((Button *)handle)->setTitleAlignment((TextHAlignment)v);
		break;
	case CC_BTNSETPRESSEDACTIONENABLED:
		((Button *)handle)->setPressedActionEnabled(0 != v);
		break;
	case CC_BTNSETSCALE9ENABLED:
		((Button *)handle)->setScale9Enabled(0 != v);
		break;
	case CC_WIDGETSETLAYOUTCOMPONENTENABLED:
		((Widget *)handle)->setLayoutComponentEnabled(0 != v);
		break;
	case CC_WIDGETSETUNIFYSIZEENABLED:
		((Widget *)handle)->setUnifySizeEnabled(0 != v);
		break;
	case CC_WIDGETENABLEDPADNAVIGATION:
		((Widget *)handle)->enableDpadNavigation(0 != v);
		break;
	case CC_WIDGETSETFOCUSENABLED:
		((Widget *)handle)->setFocusEnabled(0 != v);
		break;
	case CC_WIDGETSETFOCUSED:
		((Widget *)handle)->setFocused(0 != v);
		break;
	case CC_WIDGETSETSWALLOWTOUCHES:
		((Widget *)handle)->setSwallowTouches(0 != v);
		break;
	case CC_WIDGETSETPROPAGATETOUCHEVENTS:
		((Widget *)handle)->setPropagateTouchEvents(0 != v);
		break;
	case CC_WIDGETSETACTIONTAG:
		((Widget *)handle)->setActionTag(v);
		break;
	case CC_WIDGETIGNORECONTENTADAPTWITHSIZE:
		((Widget *)handle)->ignoreContentAdaptWithSize(0 != v);
		break;
	case CC_WIDGETSETSIZETYPE:
		((Widget *)handle)->setSizeType((SizeType)v);
		break;
	case CC_WIDGETSETFLIPPEDY:
		((Widget *)handle)->setFlippedY(v != 0);
		break;
	case CC_WIDGETSETFLIPPEDX:
		((Widget *)handle)->setFlippedX(v != 0);
		break;
	case CC_WIDGETSETPOSITIONTYPE:
		((Widget *)handle)->setPositionType((PositionType)v);
		break;
	case CC_WIDGETSETHIGHLIGHTED:
		((Widget *)handle)->setHighlighted(v != 0);
		break;
	case CC_WIDGETSETBRIGHTSTYLE:
		((Widget *)handle)->setBrightStyle((Widget::BrightStyle)v);
		break;
	case CC_WIDGETSETTOUCHENABLED:
		((Widget *)handle)->setTouchEnabled(v != 0);
		break;
	case CC_WIDGETSETBRIGHT:
		((Widget *)handle)->setBright(v != 0);
		break;
	case CC_DIRPOPTOROOTSCENESTACKLEVEL:
		 ((Director *)handle)->popToSceneStackLevel(v);
		break;
	case CC_DIRSETALPHABLENDING:
		 ((Director *)handle)->setAlphaBlending(v == 1);
		break;
	case CC_DIRSETDEPTHTEST:
		 ((Director *)handle)->setDepthTest(v == 1);
		break;

	case CC_DIRPUSHMATRIX:
		((Director *)handle)->pushMatrix((MATRIX_STACK_TYPE)v);
		break;
	case CC_DIRPUSHPROJECTIONMATRIX:
		((Director *)handle)->pushProjectionMatrix(v);
		break;
	case CC_DIRPOPMATRIX:
		((Director *)handle)->popMatrix((MATRIX_STACK_TYPE)v);
		break;
	case CC_DIRPOPPROJECTIONMATRIX:
		((Director *)handle)->popProjectionMatrix(v);
		break;
	case CC_DIRLOADIDENTITYMATRIX:
		((Director *)handle)->loadIdentityMatrix((MATRIX_STACK_TYPE)v);
		break;
	case CC_DIRLOADPROJECTIONIDENTITYMATRIX:
		((Director *)handle)->loadProjectionIdentityMatrix(v);
		break;
	case CC_DIRINITPROJECTIONMATRIXSTACK:
		((Director *)handle)->initProjectionMatrixStack(v);
		break;
	case CC_NODESETLOCALZORDER:
		((Node *)handle)->setZOrder(v);
		break;
	case CC_NODESETVISIBLE:
		((Node *)handle)->setVisible(v != 0);
		break;
	case CC_NODESETIGNOREANCHORPOINTFORPOSITION:
		((Node *)handle)->setIgnoreAnchorPointForPosition(v != 0);
		break;
	case CC_NODEREMOVEFROMPARENTANDCLEANUP:
		((Node *)handle)->removeFromParentAndCleanup(v != 0);
		break;
	case CC_NODEREMOVEALLCHILDRENWITHCLEANUP:
		((Node *)handle)->removeAllChildrenWithCleanup(v != 0);
		break;
	case CC_NODESETTAG:
		((Node *)handle)->setTag(v);
		break;
	case CC_NODESTOPACTIONBYTAG:
		((Node *)handle)->stopActionByTag(v);
		break;
	case CC_NODESTOPALLACTIONSBYTAG:
		((Node *)handle)->stopAllActionsByTag(v);
		break;
	case CC_NODESTOPACTIONSBYFLAGS:
		((Node *)handle)->stopActionsByFlags(v);
		break;
	case CC_NODESETOPACITY:
		((Node *)handle)->setOpacity(v);
		break;
	case CC_NODEUPDATEDISPLAYEDOPACITY:
		((Node *)handle)->updateDisplayedOpacity(v);
		break;
	case CC_NODESETCASCADEOPACITYENABLED:
		((Node *)handle)->setCascadeOpacityEnabled(v);
		break;
	case CC_NODESETCASCADECOLORENABLED:
		((Node *)handle)->setCascadeColorEnabled(v);
		break;
	case CC_NODESETOPACITYMODIFYRGB:
		((Node *)handle)->setOpacityModifyRGB(v);
		break;
	case CC_DIRSETDISPLAYSTATS:
		((Director *)handle)->setDisplayStats(v != 0);
		break;
	case CC_ACTSETTAG:
		((Action *)handle)->setTag(v);
		break;
	case CC_ACTSETFLAGS:
		((Action *)handle)->setFlags(v);
		break;
	case CC_FOLLOWSETBOUNDARYSET:
		((Follow *)handle)->setBoundarySet(v != 0);
		break;
	case CC_WIDGETSETENABLED:
		((Widget *)handle)->setEnabled(v != 0);
		break;
	default:
		break;
	}
}

XNLEXPORT void XI_CDECL xcocox_void_func_long(xlong handle, xint proid, xlong param) {
	switch (proid)
	{
	case CC_LISTVIEWPUSHBACKCUSTOMITEM:
		((ListView *)handle)->pushBackCustomItem((Widget*)param);
		break;
	case CC_LISTVIEWSETITEMMODEL:
		((ListView *)handle)->setItemModel((Widget*)param);
		break;
	case CC_BTNSETTITLELABEL:
		((Button *)handle)->setTitleLabel((Label*)param);
		break;
	case CC_WIDGETSETLAYOUTPARAMETER:
		((Widget *)handle)->setLayoutParameter((LayoutParameter*)param);
		break;
	case CC_DIRRUNSCENE:
		 ((Director *)handle)->runWithScene((Scene*)param);
		break;
	case CC_DIRPUSHSCENE:
		 ((Director *)handle)->pushScene((Scene*)param);
		break;
	case CC_DIRREPLACESCENE:
		 ((Director *)handle)->replaceScene((Scene*)param);
		break;
	case CC_DIRSETSCHEDULER:
		((Director *)handle)->setScheduler((Scheduler*)param);
		break;
	case CC_DIRSETACTIONMANAGER:
		((Director *)handle)->setActionManager((ActionManager*)param);
		break;
	case CC_NODESTOPACTION:
		((Node *)handle)->stopAction((Action*)param);
		break;
	case CC_DIRSETEVENTDISPATCHER:
		((Director *)handle)->setEventDispatcher((EventDispatcher*)param);
		break;
	case CC_NODESETROTATIONQUAT:
		((Node *)handle)->setRotationQuat(*(Quaternion*)param);
		break;
	case CC_NODEADDCHILD:
		((Node *)handle)->addChild((Node*)param);
		break;
	case CC_NODESETPARENT:
		((Node *)handle)->setParent((Node*)param);
		break;
	case CC_DIRSETGLVIEW:
		((Director *)handle)->setOpenGLView((GLView*)param);
		break;
	case CC_ACTSTARTWITHTARGET:
		((Action *)handle)->startWithTarget((Node*)param);
		break;
	case CC_ACTSETTARGET:
		((Action *)handle)->setTarget((Node*)param);
		break;
	default:
		break;
	}
}

xlong XI_CDECL xcocox_long_func(xlong handle, xint proid) {
	switch (proid)
	{
	case CC_LISTVIEWGETBOTTOMMOSTITEMINCURRENTVIEW:
	{
		return (xlong)((ListView *)handle)->getBottommostItemInCurrentView();
	}
	break;
	case CC_LISTVIEWGETTOPMOSTITEMINCURRENTVIEW:
	{
		return (xlong)((ListView *)handle)->getTopmostItemInCurrentView();
	}
	break;
	case CC_LISTVIEWGETRIGHTMOSTITEMINCURRENTVIEW:
	{
		return (xlong)((ListView *)handle)->getRightmostItemInCurrentView();
	}
	break;
	case CC_LISTVIEWGETLEFTMOSTITEMINCURRENTVIEW:
	{
		return (xlong)((ListView *)handle)->getLeftmostItemInCurrentView();
	}
	break;
	case CC_LISTVIEWGETCENTERITEMINCURRENTVIEW:
	{
		return (xlong)((ListView *)handle)->getCenterItemInCurrentView();
	}
	break;
	case CC_SCROLLVIEWGETINNERCONTAINER:
	{
		return (xlong)((ScrollView *)handle)->getInnerContainer();
	}
	break;
	case CC_ABSTRACTCHECKBUTTONGETRENDERERFRONTCROSSDISABLED:
	{
		return (xlong)((AbstractCheckButton *)handle)->getRendererFrontCrossDisabled();
	}
	break;
	case CC_ABSTRACTCHECKBUTTONGETRENDERERBACKGROUNDDISABLED:
	{
		return (xlong)((AbstractCheckButton *)handle)->getRendererBackgroundDisabled();
	}
	break;
	case CC_ABSTRACTCHECKBUTTONGETRENDERERFRONTCROSS:
	{
		return (xlong)((AbstractCheckButton *)handle)->getRendererFrontCross();
	}
	break;
	case CC_ABSTRACTCHECKBUTTONGETRENDERERBACKGROUNDSELECTED:
	{
		return (xlong)((AbstractCheckButton *)handle)->getRendererBackgroundSelected();
	}
	break;
	case CC_ABSTRACTCHECKBUTTONGETRENDERERBACKGROUND:
	{
		return (xlong)((AbstractCheckButton *)handle)->getRendererBackground();
	}
	break;
	case CC_BTNGETTITLELABEL:
	{
		return (xlong)((Button *)handle)->getTitleLabel();
	}
	break;
	case CC_WIDGETGETCURRENTFOCUSEDWIDGET:
	{
		return (xlong)((Widget *)handle)->getCurrentFocusedWidget();
	}
	break;
	case CC_WIDGETGETLAYOUTPARAMETER:
	{
		return (xlong)((Widget *)handle)->getLayoutParameter();
	}
	break;
	case CC_REPEATFOREVERGETINNERACTION:
	{
		return (xlong)((RepeatForever *)handle)->getInnerAction();
	}
	break;
	case CC_REPEATGETINNERACTION:
	{
		return (xlong)((Repeat*)handle)->getInnerAction();
	}
	break;
	case CC_DIRGETSCHEDULER:
	{
		return (xlong)((Director *)handle)->getScheduler();
	}
	break;
	case CC_DIRGETACTIONMANAGER:
	{
		return (xlong)((Director *)handle)->getActionManager();
	}
	break;
	case CC_DIRGETEVENTDISPATCHER:
	{
		return (xlong)((Director *)handle)->getEventDispatcher();
	}
	break;
	case CC_DIRGETRENDERER:
	{
		return (xlong)((Director *)handle)->getRenderer();
	}
	break;
	case CC_NODEGETPARENT:
	{
		return (xlong)((Node*)handle)->getParent();
	}
	break;
	case CC_NODEGETSCENE:
	{
		return (xlong)((Node*)handle)->getScene();
	}
	break;
	case CC_DIRGETGLVIEW:
	{
		return (xlong)((Director*)handle)->getOpenGLView();
	}
	break;
	case CC_ACTCLONE:
	{
		return (xlong)((Action*)handle)->clone();
	}
	break;
	case CC_ACTREVERSE:
	{
		return (xlong)((Action*)handle)->clone();
	}
	break;
	case CC_ACTGETTARGET:
	{
		return (xlong)((Action*)handle)->getTarget();
	}
	break;
	default:
		break;
	}
	return 0;
}

XNLEXPORT double XI_CDECL xcocox_get_double(xlong handle, xint proid) {
	switch (proid)
	{
	case CC_LISTVIEWGETSCROLLDURATION:
		return ((ListView *)handle)->getScrollDuration();
		break;
	case CC_LISTVIEWGETBOTTOMPADDING:
		return ((ListView *)handle)->getBottomPadding();
		break;
	case CC_LISTVIEWGETRIGHTPADDING:
		return ((ListView *)handle)->getRightPadding();
		break;
	case CC_LISTVIEWGETTOPPADDING:
		return ((ListView *)handle)->getTopPadding();
		break;
	case CC_LISTVIEWGETLEFTPADDING:
		return ((ListView *)handle)->getLeftPadding();
		break;
	case CC_LISTVIEWGETITEMSMARGIN:
		return ((ListView *)handle)->getItemsMargin();
		break;
	case CC_SCROLLVIEWGETTOUCHTOTALTIMETHRESHOLD:
		return ((ScrollView *)handle)->getTouchTotalTimeThreshold();
		break;
	case CC_SCROLLVIEWGETSCROLLBARAUTOHIDETIME:
		return ((ScrollView *)handle)->getScrollBarAutoHideTime();
		break;
	case CC_SCROLLVIEWGETSCROLLBARWIDTH:
		return ((ScrollView *)handle)->getScrollBarWidth();
		break;
	case CC_SCROLLVIEWGETSCROLLEDPERCENTHORIZONTAL:
		return ((ScrollView *)handle)->getScrolledPercentHorizontal();
		break;
	case CC_SCROLLVIEWGETSCROLLEDPERCENTVERTICAL:
		return ((ScrollView *)handle)->getScrolledPercentVertical();
		break;
	case CC_ABSTRACTCHECKBUTTONGETZOOMSCALE:
		return ((AbstractCheckButton *)handle)->getZoomScale();
		break;
	case CC_SAEGETEFFECTSVOLUME:
		return ((SimpleAudioEngine *)handle)->getEffectsVolume();
		break;
	case CC_SAEGETBACKGROUNDMUSICVOLUME:
		return ((SimpleAudioEngine *)handle)->getBackgroundMusicVolume();
		break;
	case CC_BTNGETZOOMSCALE:
		return ((Button *)handle)->getZoomScale();
		break;
	case CC_BTNGETTITLEFONTSIZE:
		return ((Button *)handle)->getTitleFontSize();
		break;
	case CC_WIDGETGETTOPBOUNDARY:
		return ((Widget *)handle)->getTopBoundary();
		break;
	case CC_WIDGETGETRIGHTBOUNDARY:
		return ((Widget *)handle)->getRightBoundary();
		break;
	case CC_WIDGETGETBOTTOMBOUNDARY:
		return ((Widget *)handle)->getBottomBoundary();
		break;
	case CC_WIDGETGETLEFTBOUNDARY:
		return ((Widget *)handle)->getLeftBoundary();
		break;
	case CC_DIRGETZE:
		return ((Director *)handle)->getZEye();
		break;
	case CC_DIRGETCONTENTSCALEFACTOR:
		return ((Director *)handle)->getContentScaleFactor();
		break;
	case CC_DIRGETDELTATIME:
		return ((Director *)handle)->getDeltaTime();
		break;
	case CC_DIRGETFRAMERATE:
		return ((Director *)handle)->getFrameRate();
		break;
	case CC_NODEGETGLOBALZORDER:
		return ((Node *)handle)->getGlobalZOrder();
		break;
	case CC_NODEGETSCALEX:
		return ((Node *)handle)->getScaleX();
		break;
	case CC_NODEGETSCALEY:
		return ((Node *)handle)->getScaleY();
		break;
	case CC_NODEGETSCALEZ:
		return ((Node *)handle)->getScaleZ();
		break;
	case CC_NODEGETSCALE:
		return ((Node *)handle)->getScale();
		break;
	case CC_NODEGETPOSITIONX:
		return ((Node *)handle)->getPositionX();
		break;
	case CC_NODEGETPOSITIONY:
		return ((Node *)handle)->getPositionY();
		break;
	case CC_NODEGETPOSITIONZ:
		return ((Node *)handle)->getPositionZ();
		break;
	case CC_NODEGETSKEWX:
		return ((Node *)handle)->getSkewX();
		break;
	case CC_NODEGETSKEWY:
		return ((Node *)handle)->getSkewY();
		break;
	case CC_NODEGETROTATION:
		return ((Node *)handle)->getRotation();
		break;
	case CC_NODEGETROTATIONX:
		return ((Node *)handle)->getRotationX();
		break;
	case CC_NODEGETROTATIONY:
		return ((Node *)handle)->getRotationY();
		break;
	case CC_ACTIONGETDURATION:
		return ((FiniteTimeAction *)handle)->getDuration();
		break;
	case CC_ACTIONINTERVALGETELAPSED:
		return ((ActionInterval *)handle)->getElapsed();
		break;
	case CC_ACTIONSPEEDGETSPEED:
		return ((Speed *)handle)->getSpeed();
		break;
	default:
		break;
	}
	return 0;
}

XNLEXPORT xlong XI_CDECL xcocos_func_param_objs(xlong handle, xint proid, XObject * params) {
	switch (proid)
	{
	case CC_LISTVIEWGETCLOSESTITEMTOPOSITIONINCURRENTVIEW: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			return (xlong)((ListView*)handle)->getClosestItemToPositionInCurrentView(Vec2(param[0], param[1]), Vec2(param[2], param[3]));
		}
	}
		break;
	case CC_LISTVIEWGETCLOSESTITEMTOPOSITION: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			return (xlong)((ListView*)handle)->getClosestItemToPosition(Vec2(param[0], param[1]), Vec2(param[2], param[3]));
		}
	}
		break;
	case CC_LISTVIEWSETPADDING: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((ListView*)handle)->setPadding(param[0], param[1], param[2], param[3]);
		}
	}
		break;
	case CC_SCROLLVIEWSETSCROLLBARCOLOR: {
		xbyte * param = (xbyte*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((ScrollView*)handle)->setScrollBarColor(Color3B(param[0], param[1], param[2]));
		}
	}
		break;
	case CC_SCROLLVIEWSETSCROLLBARPOSITIONFROMCORNERFORHORIZONTAL: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((ScrollView*)handle)->setScrollBarPositionFromCornerForHorizontal(Vec2(param[0], param[1]));
		}
	}
		break;
	case CC_SCROLLVIEWSETSCROLLBARPOSITIONFROMCORNERFORVERTICAL: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((ScrollView*)handle)->setScrollBarPositionFromCornerForVertical(Vec2(param[0], param[1]));
		}
	}
		break;
	case CC_SCROLLVIEWSETSCROLLBARPOSITIONFROMCORNER: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((ScrollView*)handle)->setScrollBarPositionFromCorner(Vec2(param[0], param[1]));
		}
	}
		break;
	case CC_SCROLLVIEWSETINNERCONTAINERPOSITION: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((ScrollView*)handle)->setInnerContainerPosition(Vec2(param[0], param[1]));
		}
	}
		break;
	case CC_SCROLLVIEWSETINNERCONTAINERSIZE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((ScrollView*)handle)->setInnerContainerSize(Size(param[0], param[1]));
		}
	}
		break;
	case CC_SCROLLVIEWJUMPTOPERCENTBOTHDIRECTION: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((ScrollView*)handle)->jumpToPercentBothDirection(Vec2(param[0], param[1]));
		}
	}
		break;
	case CC_LAYOUTSETBACKGROUNDIMAGECOLOR: {
		xbyte * param = (xbyte*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Layout*)handle)->setBackGroundImageColor(Color3B(param[0], param[1], param[2]));
		}
	}
	break;
	case CC_LAYOUTSETBACKGROUNDCOLORVECTOR: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Layout*)handle)->setBackGroundColorVector(Vec2(param[0], param[1]));
		}
	}
	break;
	case CC_LAYOUTSETBACKGROUNDCOLOR6: {
		xbyte * param = (xbyte*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Layout*)handle)->setBackGroundColor(Color3B(param[0], param[1], param[2]), Color3B(param[3], param[4], param[5]));
		}
	}
	break;
	case CC_LAYOUTSETBACKGROUNDCOLOR: {
		xbyte * param = (xbyte*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Layout*)handle)->setBackGroundColor(Color3B(param[0], param[1], param[2]));
		}
	}
	 break;
	case CC_LAYOUTSETBACKGROUNDIMAGECAPINSETS: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Layout*)handle)->setBackGroundImageCapInsets(Rect(param[0], param[1], param[2], param[3]));
		}
	}
								  break;
	case CC_BTNSETTITLEALIGNMENT: {
		xint * param = (xint*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Button*)handle)->setTitleAlignment((TextHAlignment)param[0], (TextVAlignment)param[1]);
		}
	}
		break;
	case CC_BTNSETTITLECOLOR: {
		xbyte * param = (xbyte*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Button*)handle)->setTitleColor(Color3B(param[0], param[1], param[2]));
		}
	}
		break;
	case CC_BTNSETCAPINSETSDISABLEDRENDERER: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Button*)handle)->setCapInsetsDisabledRenderer(Rect(param[0], param[1], param[2], param[3]));
		}
	}
		break;
	case CC_BTNSETCAPINSETSPRESSEDRENDERER: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Button*)handle)->setCapInsetsPressedRenderer(Rect(param[0], param[1], param[2], param[3]));
		}
	}
		break;
	case CC_BTNSETCAPINSETSNORMALRENDERER: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Button*)handle)->setCapInsetsNormalRenderer(Rect(param[0], param[1], param[2], param[3]));
		}
	}
		break;
	case CC_BTNSETCAPINSETS: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Button*)handle)->setCapInsets(Rect(param[0], param[1], param[2], param[3]));
		}
	}
	 break;
	case CC_WIDGETUPDATESIZEANDPOSITION: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Widget*)handle)->updateSizeAndPosition(Size(param[0], param[1]));
		}
	}
	break;
	case CC_WIDGETSETSIZEPERCENT: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Widget*)handle)->setSizePercent(Size(param[0], param[1]));
		}
	}
	 break;
	case CC_WIDGETISCLIPPINGPARENTCONTAINSPOINT: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Widget*)handle)->isClippingParentContainsPoint(Vec2(param[0], param[1]));
		}
	}
	break;
	case CC_WIDGETSETPOSITIONPERCENT: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Widget*)handle)->setPositionPercent(Vec2(param[0], param[1]));
		}
	}
		break;
	case CC_WIDGETADDCCSEVENTLISTENER:
	{
		((Widget*)handle)->addCCSEventListener([=](Ref * ref, int ) {

		});
	}
	break;
	case CC_WIDGETADDCLICKEVENTLISTENER:
	{
		((Widget*)handle)->addClickEventListener([=](Ref * ref) {

		});
	}
	break;
	case CC_WIDGETADDTOUCHEVENTLISTENER:
	{
		((Widget*)handle)->addTouchEventListener([=](Ref * ref, Widget::TouchEventType type) {

		});
	}
		break;
	
	case CC_NODESETSCALE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Node*)handle)->setScale(param[0], param[1]);
		}
	}
		break;
	case CC_NODESETPOSITION: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Node*)handle)->setPosition(param[0], param[1]);
		}
	}
		break;
	case CC_NODESETPOSITIONNORMALIZED: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Node*)handle)->setPositionNormalized(Vec2(param[0], param[1]));
		}
	}
		break;
	case CC_NODESETPOSITION3D: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Node*)handle)->setPosition3D(Vec3(param[0], param[1], param[2]));
		}
	}
		break;
	case CC_NODESETANCHORPOINT: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Node*)handle)->setAnchorPoint(Vec2(param[0], param[1]));
		}
	}
		break;
	case CC_NODESETCONTENTSIZE: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Node*)handle)->setContentSize(Size(param[0], param[1]));
		}
	}
		break;
	case CC_NODESETROTATION3D: {
		double * param = (double*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			((Node*)handle)->setRotation3D(Vec3(param[0], param[1], param[2]));
		}
	}
		break;
	case CC_GLVIEWSETGLCONTEXTATTRS: {
		xint * param = (xint*)gs_env->getPointerOfArray(params);
		if (param != 0) {
			GLContextAttrs glContextAttrs = { param[0], param[1], param[2], param[3], param[4], param[5], param[6] };
			cocos2d::GLView::setGLContextAttrs(glContextAttrs);
		}
	}
		 break;

	case CC_DIRRUNONUI: 
	{
		XObject * xobj = gs_env->referenceObject(params);
		((Director*)handle)->getScheduler()->performFunctionInCocosThread([=]() {
			gs_env->void_invoke(main_thread, xobj, xfunctions[x_RunnableRun].xid);
			gs_env->dereferenceObject(xobj);
		});
	}
		break;
	case CC_OBJECTINCREF:
		if (((Ref *)handle)->xobject != 0) {
			gs_env->dereferenceObject((XObject*)((Ref *)handle)->xobject);
			((Ref *)handle)->xobject = 0;
		}
		((Ref *)handle)->xobject = gs_env->referenceObject(params);
		break;
	default:
		break;
	}
	return 0;
}

XNLEXPORT XObject * XI_CDECL xcocox_obj_get_obj(xlong handle, xint proid, XObject * param) {

	XObject * obj = 0;

	switch (proid) {
	case CC_DIRCVTGL: {
		double xy[2];
		gs_env->getElementValue(param, 0, &xy[0], 2);
		Director * pdir = (Director *)handle;

		Vec2 out = pdir->convertToGL(Vec2(xy[0], xy[1]));

		obj = gs_env->createDoubleArray(2);
		double value[2];
		value[0] = out.x;
		value[1] = out.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;

	case CC_DIRCVTUI: {
		double xy[2];
		gs_env->getElementValue(param, 0, &xy[0], 2);
		Director * pdir = (Director *)handle;

		Vec2 out = pdir->convertToUI(Vec2(xy[0], xy[1]));

		obj = gs_env->createDoubleArray(2);
		double value[2];
		value[0] = out.x;
		value[1] = out.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;

	case CC_DIRSETCLEARCOLOR: {
		double xy[4];
		gs_env->getElementValue(param, 0, &xy[0], 4);
		Director * pdir = (Director *)handle;
		pdir->setClearColor(Color4F(xy[0], xy[1], xy[2], xy[3]));
	}
		break;
	case CC_NODECONVERTTONODESPACE: {
		double xy[2];
		gs_env->getElementValue(param, 0, &xy[0], 2);
		Node * pdir = (Node *)handle;

		Vec2 out = pdir->convertToNodeSpace(Vec2(xy[0], xy[1]));

		obj = gs_env->createDoubleArray(2);
		double value[2];
		value[0] = out.x;
		value[1] = out.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
									 break;
	case CC_NODECONVERTTOWORLDSPACE: {
		double xy[2];
		gs_env->getElementValue(param, 0, &xy[0], 2);
		Node * pdir = (Node *)handle;

		Vec2 out = pdir->convertToWorldSpace(Vec2(xy[0], xy[1]));

		obj = gs_env->createDoubleArray(2);
		double value[2];
		value[0] = out.x;
		value[1] = out.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;

	case CC_NODECONVERTTONODESPACEAR: {
		double xy[2];
		gs_env->getElementValue(param, 0, &xy[0], 2);
		Node * pdir = (Node *)handle;

		Vec2 out = pdir->convertToNodeSpaceAR(Vec2(xy[0], xy[1]));

		obj = gs_env->createDoubleArray(2);
		double value[2];
		value[0] = out.x;
		value[1] = out.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		 break;

	case CC_NODECONVERTTOWORLDSPACEAR: {
		double xy[2];
		gs_env->getElementValue(param, 0, &xy[0], 2);
		Node * pdir = (Node *)handle;

		Vec2 out = pdir->convertToWorldSpaceAR(Vec2(xy[0], xy[1]));

		obj = gs_env->createDoubleArray(2);
		double value[2];
		value[0] = out.x;
		value[1] = out.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;
	
	}

	return obj;
}

XObject * XI_CDECL xcocox_obj_get_long(xlong handle, xint proid, xlong v) {
	XObject * obj = 0;

	switch (proid)
	{
	case CC_NODECONVERTTOUCHTONODESPACE:
	{
		Vec2 out = ((Node*)handle)->convertTouchToNodeSpace((Touch*)v);
		obj = gs_env->createDoubleArray(2);
		double value[2];
		value[0] = out.x;
		value[1] = out.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;
	case CC_NODECONVERTTOUCHTONODESPACEAR:
	{
		Vec2 out = ((Node*)handle)->convertTouchToNodeSpaceAR((Touch*)v);
		obj = gs_env->createDoubleArray(2);
		double value[2];
		value[0] = out.x;
		value[1] = out.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;
	default:
		break;
	}

	return obj;
}

XNLEXPORT XObject * XI_CDECL xcocox_obj_get(xlong handle, xint proid) {
	XObject * obj = 0;


	switch (proid) {
	case CC_LISTVIEWGETITEMS:
	{
		ListView * pdir = (ListView *)handle;
		Vector<Widget*> ws = pdir->getItems();
		obj = gs_env->createLongArray(ws.size());
		xlong *xl = new xlong[ws.size()];
		for (size_t i = 0; i < ws.size(); i++) {
			xl[i] = (xlong)ws.at(i);
		}
		gs_env->setElementValue(obj, 0, &xl[0], ws.size());
		delete[]xl;
	}
	break;
	case CC_SCROLLVIEWGETSCROLLBARCOLOR:
	{
		obj = gs_env->createDoubleArray(3);
		ScrollView * pdir = (ScrollView *)handle;
		Color3B so = pdir->getScrollBarColor();
		double value[3];
		value[0] = so.r;
		value[1] = so.g;
		value[2] = so.b;
		gs_env->setElementValue(obj, 0, value, 3);
	}
	break;
	case CC_SCROLLVIEWGETSCROLLBARPOSITIONFROMCORNERFORHORIZONTAL:
	{
		obj = gs_env->createDoubleArray(2);
		ScrollView * pdir = (ScrollView *)handle;
		Vec2 so = pdir->getScrollBarPositionFromCornerForHorizontal();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_SCROLLVIEWGETSCROLLBARPOSITIONFROMCORNERFORVERTICAL:
	{
		obj = gs_env->createDoubleArray(2);
		ScrollView * pdir = (ScrollView *)handle;
		Vec2 so = pdir->getScrollBarPositionFromCornerForVertical();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_SCROLLVIEWGETINNERCONTAINERPOSITION:
	{
		obj = gs_env->createDoubleArray(2);
		ScrollView * pdir = (ScrollView *)handle;
		Vec2 so = pdir->getInnerContainerPosition();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_SCROLLVIEWGETINNERCONTAINERSIZE:
	{
		obj = gs_env->createDoubleArray(2);
		ScrollView * pdir = (ScrollView *)handle;
		Size so = pdir->getInnerContainerSize();
		double value[2];
		value[0] = so.width;
		value[1] = so.height;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_SCROLLVIEWGETSCROLLEDPERCENTBOTHDIRECTION:
	{
		obj = gs_env->createDoubleArray(2);
		ScrollView * pdir = (ScrollView *)handle;
		Vec2 so = pdir->getScrolledPercentBothDirection();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_LAYOUTGETBACKGROUNDIMAGETEXTURESIZE:
	{
		obj = gs_env->createDoubleArray(2);

		Layout * pdir = (Layout *)handle;
		Size so = pdir->getBackGroundImageTextureSize();
		double value[2];
		value[0] = so.width;
		value[1] = so.height;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_LAYOUTGETBACKGROUNDIMAGECOLOR:
	{
		obj = gs_env->createDoubleArray(4);

		Layout * pdir = (Layout *)handle;
		Color3B so = pdir->getBackGroundImageColor();
		xbyte value[4];
		value[0] = so.r;
		value[1] = so.g;
		value[2] = so.b;
		gs_env->setElementValue(obj, 0, value, 3);
	}
	break;
	case CC_LAYOUTGETBACKGROUNDCOLORVECTOR:
	{
		obj = gs_env->createDoubleArray(2);
		Layout * pdir = (Layout *)handle;
		Vec2 so = pdir->getBackGroundColorVector();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_LAYOUTGETBACKGROUNDENDCOLOR:
	{
		obj = gs_env->createDoubleArray(4);

		Layout * pdir = (Layout *)handle;
		Color3B so = pdir->getBackGroundEndColor();
		xbyte value[4];
		value[0] = so.r;
		value[1] = so.g;
		value[2] = so.b;
		gs_env->setElementValue(obj, 0, value, 3);
	}
	break;
	case CC_LAYOUTGETBACKGROUNDSTARTCOLOR:
	{
		obj = gs_env->createDoubleArray(4);

		Layout * pdir = (Layout *)handle;
		Color3B so = pdir->getBackGroundStartColor();
		xbyte value[4];
		value[0] = so.r;
		value[1] = so.g;
		value[2] = so.b;
		gs_env->setElementValue(obj, 0, value, 3);
	}
	break;
	case CC_LAYOUTGETBACKGROUNDCOLOR:
	{
		obj = gs_env->createDoubleArray(4);

		Layout * pdir = (Layout *)handle;
		Color3B so = pdir->getBackGroundColor();
		xbyte value[4];
		value[0] = so.r;
		value[1] = so.g;
		value[2] = so.b;
		gs_env->setElementValue(obj, 0, value, 3);
	}
	break;
	case CC_LAYOUTGETBACKGROUNDIMAGECAPINSETS:
	{
		obj = gs_env->createDoubleArray(4);

		Layout * pdir = (Layout *)handle;
		Rect so = pdir->getBackGroundImageCapInsets();
		double value[4];
		value[0] = so.origin.x;
		value[1] = so.origin.y;
		value[2] = so.size.width;
		value[3] = so.size.height;
		gs_env->setElementValue(obj, 0, value, 4);
	}
	break;
	case CC_BTNGETTITLEFONTNAME:
	{
		Button * pdir = (Button *)handle;
		const std::string & so = pdir->getTitleFontName();
		obj = string2XString(so);
	}
	break;
	case CC_BTNGETTITLECOLOR:
	{
		obj = gs_env->createDoubleArray(4);

		Button * pdir = (Button *)handle;
		Color3B so = pdir->getTitleColor();
		xbyte value[4];
		value[0] = so.r;
		value[1] = so.g;
		value[2] = so.b;
		gs_env->setElementValue(obj, 0, value, 3);
	}
	break;
	case CC_BTNGETTITLETEXT:
	{
		Button * pdir = (Button *)handle;
		const std::string & so = pdir->getTitleText();
		obj = string2XString(so);
	}
	break;
	case CC_BTNGETCAPINSETSDISABLEDRENDERER:
	{
		obj = gs_env->createDoubleArray(4);

		Button * pdir = (Button *)handle;
		Rect so = pdir->getCapInsetsDisabledRenderer();
		double value[4];
		value[0] = so.origin.x;
		value[1] = so.origin.y;
		value[2] = so.size.width;
		value[3] = so.size.height;
		gs_env->setElementValue(obj, 0, value, 4);
	}
	break;
	case CC_BTNGETCAPINSETSPRESSEDRENDERER:
	{
		obj = gs_env->createDoubleArray(4);

		Button * pdir = (Button *)handle;
		Rect so = pdir->getCapInsetsPressedRenderer();
		double value[4];
		value[0] = so.origin.x;
		value[1] = so.origin.y;
		value[2] = so.size.width;
		value[3] = so.size.height;
		gs_env->setElementValue(obj, 0, value, 4);
	}
	break;
	case CC_BTNGETCAPINSETSNORMALRENDERER:
	{
		obj = gs_env->createDoubleArray(4);

		Button * pdir = (Button *)handle;
		Rect so = pdir->getCapInsetsNormalRenderer();
		double value[4];
		value[0] = so.origin.x;
		value[1] = so.origin.y;
		value[2] = so.size.width;
		value[3] = so.size.height;
		gs_env->setElementValue(obj, 0, value, 4);
	}
	break;
	case CC_WIDGETGETCALLBACKTYPE:
	{
		Widget * pdir = (Widget *)handle;
		const std::string & so = pdir->getCallbackType();
		obj = string2XString(so);
	}
	break;
	case CC_WIDGETGETCALLBACKNAME:
	{
		Widget * pdir = (Widget *)handle;
		const std::string & so = pdir->getCallbackName();
		obj = string2XString(so);
	}
	break;
	case CC_WIDGETGETVIRTUALRENDERERSIZE:
	{
		obj = gs_env->createDoubleArray(2);

		Widget * pdir = (Widget *)handle;
		Size so = pdir->getVirtualRendererSize();
		double value[2];
		value[0] = so.width;
		value[1] = so.height;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_WIDGETGETLAYOUTSIZE:
	{
		obj = gs_env->createDoubleArray(2);

		Widget * pdir = (Widget *)handle;
		Size so = pdir->getLayoutSize();
		double value[2];
		value[0] = so.width;
		value[1] = so.height;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_WIDGETGETWORLDPOSITION:
	{
		obj = gs_env->createDoubleArray(2);

		Widget * pdir = (Widget *)handle;
		Vec2 so = pdir->getWorldPosition();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_WIDGETGETSIZEPERCENT:
	{
		obj = gs_env->createDoubleArray(2);

		Widget * pdir = (Widget *)handle;
		Vec2 so = pdir->getSizePercent();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_WIDGETGETCUSTOMSIZE:
	{
		obj = gs_env->createDoubleArray(2);

		Widget * pdir = (Widget *)handle;
		Size so = pdir->getCustomSize();
		double value[2];
		value[0] = so.width;
		value[1] = so.height;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_WIDGETGETTOUCHENDPOSITION:
	{
		obj = gs_env->createDoubleArray(2);

		Widget * pdir = (Widget *)handle;
		Vec2 so = pdir->getTouchEndPosition();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_WIDGETGETTOUCHMOVEPOSITION:
	{
		obj = gs_env->createDoubleArray(2);

		Widget * pdir = (Widget *)handle;
		Vec2 so = pdir->getTouchMovePosition();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_WIDGETGETTOUCHBEGANPOSITION:
	{
		obj = gs_env->createDoubleArray(2);

		Widget * pdir = (Widget *)handle;
		Vec2 so = pdir->getTouchBeganPosition();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_WIDGETGETPOSITIONPERCENT:
	{
		obj = gs_env->createDoubleArray(2);

		Widget * pdir = (Widget *)handle;
		Vec2 so = pdir->getPositionPercent();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_DIRGETVS:
	{
		obj = gs_env->createDoubleArray(2);
		
		Director * pdir = (Director *)handle;
		Size so = pdir->getVisibleSize();
		double value[2] ;
		value[0] = so.width;
		value[1] = so.height;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;
	case CC_DIRGETVO:
	{
		obj = gs_env->createDoubleArray(2);

		Director * pdir = (Director *)handle;
		Vec2 so = pdir->getVisibleOrigin();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
	break;
	case CC_DIRGETSAR:
	{
		obj = gs_env->createDoubleArray(4);

		Director * pdir = (Director *)handle;
		Rect so = pdir->getSafeAreaRect();
		double value[4];
		value[0] = so.origin.x;
		value[1] = so.origin.y;
		value[2] = so.size.width;
		value[3] = so.size.height;
		gs_env->setElementValue(obj, 0, value, 4);
	}
	break;
	case CC_DIRGETCLEARCOLOR: {
		obj = gs_env->createDoubleArray(4);

		Director * pdir = (Director *)handle;
		Color4F so = pdir->getClearColor();
		double value[4];
		value[0] = so.r;
		value[1] = so.g;
		value[2] = so.b;
		value[3] = so.a;
		gs_env->setElementValue(obj, 0, value, 4);
	}
	break;
	case CC_NODEGETPOSITIONNORMALIZED: {
		obj = gs_env->createDoubleArray(2);

		Node * pdir = (Node *)handle;
		Vec2 so = pdir->getPositionNormalized();
		double value[4];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;
	case CC_NODEGETPOSITION: {
		obj = gs_env->createDoubleArray(2);

		Node * pdir = (Node *)handle;
		Vec2 so = pdir->getPosition();
		double value[4];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;
	case CC_NODEGETPOSITION3D: {
		obj = gs_env->createDoubleArray(3);

		Node * pdir = (Node *)handle;
		Vec3 so = pdir->getPosition3D();
		double value[3];
		value[0] = so.x;
		value[1] = so.y;
		value[2] = so.z;
		gs_env->setElementValue(obj, 0, value, 3);
	}
		break;
	case CC_NODEGETANCHORPOINT: {
		obj = gs_env->createDoubleArray(2);

		Node * pdir = (Node *)handle;
		Vec2 so = pdir->getAnchorPoint();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;
	case CC_NODEGETANCHORPOINTINPOINTS: {
		obj = gs_env->createDoubleArray(2);

		Node * pdir = (Node *)handle;
		Vec2 so = pdir->getAnchorPointInPoints();
		double value[2];
		value[0] = so.x;
		value[1] = so.y;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;
	case CC_NODEGETCONTENTSIZE: {
		obj = gs_env->createDoubleArray(2);

		Node * pdir = (Node *)handle;
		Size so = pdir->getContentSize();
		double value[2];
		value[0] = so.width;
		value[1] = so.height;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;
	case CC_NODEGETROTATION3D: {
		obj = gs_env->createDoubleArray(3);

		Node * pdir = (Node *)handle;
		Vec3 so = pdir->getRotation3D();
		double value[3];
		value[0] = so.x;
		value[1] = so.y;
		value[2] = so.z;
		gs_env->setElementValue(obj, 0, value, 3);
	}
		break;
	case CC_NODEGETBOUNDINGBOX:
	{
		obj = gs_env->createDoubleArray(4);

		Node * pdir = (Node *)handle;
		Rect so = pdir->getBoundingBox();
		double value[4];
		value[0] = so.origin.x;
		value[1] = so.origin.y;
		value[2] = so.size.width;
		value[3] = so.size.height;
		gs_env->setElementValue(obj, 0, value, 4);
	}
	break;
	case CC_GLVIEWGETFRAME: {
		obj = gs_env->createDoubleArray(2);

		GLView * pdir = (GLView *)handle;
		Size so = pdir->getFrameSize();
		double value[2];
		value[0] = so.width;
		value[1] = so.height;
		gs_env->setElementValue(obj, 0, value, 2);
	}
		break;
	case CC_REFGETXOBJ: {
		Ref * ref = (Ref *)handle;
		if (ref != 0) {
			obj = gs_env->referenceObject((XObject*)ref->xobject);
		}
	}
		break;
	}

	return obj;
}

XNLEXPORT xint XI_STDCALL XNLMain(XNLEnv * env, xint version) {
	gs_env = env->getEnv();
	main_thread = gs_env->getContext(&main_release);
	initXMethod();
	return 0;
}


XNLEXPORT xint XI_STDCALL XNLExit(XNLEnv * env) {
	env->releaseEnv(gs_env);
	return 0;
}

XNLEXPORT void XI_CDECL xcocox_void_double_bool_func(xlong handle, xint proid, double f, xbool b) {
	switch (proid) {
	case CC_SCROLLVIEWSCROLLTOBOTTOMRIGHT:
		((ScrollView*)handle)->scrollToBottomRight(f, b);
		break;
	case CC_SCROLLVIEWSCROLLTOBOTTOMLEFT:
		((ScrollView*)handle)->scrollToBottomLeft(f, b);
		break;
	case CC_SCROLLVIEWSCROLLTOTOPRIGHT:
		((ScrollView*)handle)->scrollToTopRight(f, b);
		break;
	case CC_SCROLLVIEWSCROLLTOTOPLEFT:
		((ScrollView*)handle)->scrollToTopLeft(f, b);
		break;
	case CC_SCROLLVIEWSCROLLTORIGHT:
		((ScrollView*)handle)->scrollToRight(f, b);
		break;
	case CC_SCROLLVIEWSCROLLTOLEFT:
		((ScrollView*)handle)->scrollToLeft(f, b);
		break;
	case CC_SCROLLVIEWSCROLLTOTOP:
		((ScrollView*)handle)->scrollToTop(f, b);
		break;
	case CC_SCROLLVIEWSCROLLTOBOTTOM:
		((ScrollView*)handle)->scrollToBottom(f , b);
		break;
	}
}

XNLEXPORT void XI_CDECL xcocox_void_object_bool_func(xlong handle, xint proid, XObject * params, xbool b) {
	switch (proid) {
	case CC_SCROLLVIEWSCROLLTOPERCENTBOTHDIRECTION:
	{
		double * param = (double *)gs_env->getPointerOfArray(params);
		((ScrollView*)handle)->scrollToPercentBothDirection(Vec2(param[0], param[1]), param[3], b);
	}
	break;
	case CC_SCROLLVIEWSCROLLTOPERCENTHORIZONTAL:
	{
		double * param = (double *)gs_env->getPointerOfArray(params);
		((ScrollView*)handle)->scrollToPercentHorizontal(param[0], param[1], b);
	}
	break;
	case CC_SCROLLVIEWSCROLLTOPERCENTVERTICAL:
	{
		double * param = (double *)gs_env->getPointerOfArray(params);
		((ScrollView*)handle)->scrollToPercentVertical(param[0], param[1], b);
	}
		break;
	}
}

XNLEXPORT void XI_CDECL xcocox_void_func(xlong handle, xint proid) {
	switch (proid) {
	case CC_LISTVIEWREMOVEALLITEMS:
		((ListView*)handle)->removeAllItems();
		break;
	case CC_LISTVIEWREMOVELASTITEM:
		((ListView*)handle)->removeLastItem();
		break;
	case CC_LISTVIEWPUSHBACKDEFAULTITEM:
		((ListView*)handle)->pushBackDefaultItem();
		break;
	case CC_SCROLLVIEWJUMPTOBOTTOMRIGHT:
		((ScrollView*)handle)->jumpToBottomRight();
		break;
	case CC_SCROLLVIEWJUMPTOBOTTOMLEFT:
		((ScrollView*)handle)->jumpToBottomLeft();
		break;
	case CC_SCROLLVIEWJUMPTOTOPRIGHT:
		((ScrollView*)handle)->jumpToTopRight();
		break;
	case CC_SCROLLVIEWJUMPTOTOPLEFT:
		((ScrollView*)handle)->jumpToTopLeft();
		break;
	case CC_SCROLLVIEWJUMPTORIGHT:
		((ScrollView*)handle)->jumpToRight();
		break;
	case CC_SCROLLVIEWJUMPTOLEFT:
		((ScrollView*)handle)->jumpToLeft();
		break;
	case CC_SCROLLVIEWJUMPTOTOP:
		((ScrollView*)handle)->jumpToTop();
		break;
	case CC_SCROLLVIEWJUMPTOBOTTOM:
		((ScrollView*)handle)->jumpToBottom();
		break;
	case CC_SCROLLVIEWSTOPOVERALLSCROLL:
		((ScrollView*)handle)->stopOverallScroll();
		break;
	case CC_SCROLLVIEWSTOPAUTOSCROLL:
		((ScrollView*)handle)->stopAutoScroll();
		break;
	case CC_SCROLLVIEWSTOPSCROLL:
		((ScrollView*)handle)->stopScroll();
		break;
	case CC_LAYOUTFORCEDOLAYOUT:
		((Layout*)handle)->forceDoLayout();
		break;
	case CC_LAYOUTREQUESTDOLAYOUT:
		((Layout*)handle)->requestDoLayout();
		break;
	case CC_LAYOUTREMOVEBACKGROUNDIMAGE:
		((Layout*)handle)->removeBackGroundImage();
		break;
	case CC_SAESTOPALLEFFECTS:
		((SimpleAudioEngine*)handle)->stopAllEffects();
		break;
	case CC_SAERESUMEALLEFFECTS:
		((SimpleAudioEngine*)handle)->resumeAllEffects();
		break;
	case CC_SAEPAUSEALLEFFECTS:
		((SimpleAudioEngine*)handle)->pauseAllEffects();
		break;
	case CC_SAEREWINDBACKGROUNDMUSIC:
		((SimpleAudioEngine*)handle)->rewindBackgroundMusic();
		break;
	case CC_SAERESUMEBACKGROUNDMUSIC:
		((SimpleAudioEngine*)handle)->resumeBackgroundMusic();
		break;
	case CC_SAEPAUSEBACKGROUNDMUSIC:
		((SimpleAudioEngine*)handle)->pauseBackgroundMusic();
		break;
	case CC_WIDGETREQUESTFOCUS:
		((Widget*)handle)->requestFocus();
		break;
	case CC_WIDGETUPDATESIZEANDPOSITION:
		((Widget*)handle)->updateSizeAndPosition();
		break;
	case APP_RUN:
		((XCApplication*)handle)->run();
		break;
	case CC_DIRPOPSCENE:
		((Director*)handle)->popScene();
		break;
	case CC_DIRPOPTOROOTSCENE:
		((Director*)handle)->popToRootScene();
		break;
	case CC_DIREND:
		((Director*)handle)->end();
		break;
	case CC_DIRPAUSE:
		((Director*)handle)->pause();
		break;
	case CC_DIRRESUME:
		((Director*)handle)->resume();
		break;
	case CC_DIRRESTART:
		((Director*)handle)->restart();
		break;
	case CC_DIRSTOPANI:
		((Director*)handle)->stopAnimation();
		break;
	case CC_DIRSTARTANI:
		((Director*)handle)->startAnimation();
		break;
	case CC_DIRDRAWSCENE:
		((Director*)handle)->drawScene();
		break;
	case CC_DIRPURGECACHEDDATA:
		((Director*)handle)->purgeCachedData();
		break;
	case CC_DIRSETDEFAULTVALUES:
		((Director*)handle)->setDefaultValues();
		break;
	case CC_DIRSETGLDEFAULTVALUES:
		((Director*)handle)->setGLDefaultValues();
		break;
	case CC_DIRMAINLOOP:
		((Director *)handle)->mainLoop();
		break;
	case CC_DIRRESETMATRIXSTACK:
		((Director *)handle)->resetMatrixStack();
		break;
	case CC_SCENERMALLCHLD:
		((Scene *)handle)->removeAllChildren();
		break;
	case CC_NODEUPDATEORDEROFARRIVAL:
		((Node *)handle)->updateOrderOfArrival();
		break;
	case CC_NODEREMOVEFROMPARENT:
		((Node *)handle)->removeFromParent();
		break;
	case CC_NODEREMOVEALLCHILDREN:
		((Node *)handle)->removeAllChildren();
		break;
	case CC_NODESORTALLCHILDREN:
		((Node *)handle)->sortAllChildren();
		break;
	case CC_NODECLEANUP:
		((Node *)handle)->cleanup();
		break;
	case CC_NODESTOPALLACTIONS:
		((Node *)handle)->stopAllActions();
		break;

	case CC_NODERESUME:
		((Node *)handle)->resume();
		break;
	case CC_NODEPAUSE:
		((Node *)handle)->pause();
		break;
	case CC_NODEUPDATETRANSFORM:
		((Node *)handle)->updateTransform();
		break;
	case CC_NODEREMOVEALLCOMPONENTS:
		((Node *)handle)->removeAllComponents();
		break;
	case CC_OBJECTDEREF: {
		
		Ref * ref = ((Ref *)handle);
		if (ref != 0) {
			/*XObject * pxobj = (XObject *)ref->xobject;
			int xflags = ref->xflags;
			*/
			ref->xobject = 0;
			ref->xflags |= REF_FINALIZED;
			ref->release();
			
			/*if (pxobj != 0) {
				gs_env->dereferenceObject(pxobj);
			}*/
		}
	}
		break;
	case CC_ACTSTOP:
		((Action *)handle)->stop();
		break;
	}
}


XNLEXPORT void XI_CDECL xcocox_void_double_func(xlong handle, xint proid, double v) {
	switch (proid) {
	case CC_LISTVIEWSETSCROLLDURATION:
		((ListView*)handle)->setScrollDuration(v);
		break;
	case CC_LISTVIEWSETBOTTOMPADDING:
		((ListView*)handle)->setBottomPadding(v);
		break;
	case CC_LISTVIEWSETRIGHTPADDING:
		((ListView*)handle)->setRightPadding(v);
		break;
	case CC_LISTVIEWSETTOPPADDING:
		((ListView*)handle)->setTopPadding(v);
		break;
	case CC_LISTVIEWSETLEFTPADDING:
		((ListView*)handle)->setLeftPadding(v);
		break;
	case CC_LISTVIEWSETITEMSMARGIN:
		((ListView*)handle)->setItemsMargin(v);
		break;
	case CC_SCROLLVIEWSETTOUCHTOTALTIMETHRESHOLD:
		((ScrollView*)handle)->setTouchTotalTimeThreshold(v);
		break;
	case CC_SCROLLVIEWSETSCROLLBARAUTOHIDETIME:
		((ScrollView*)handle)->setScrollBarAutoHideTime(v);
		break;
	case CC_SCROLLVIEWSETSCROLLBARWIDTH:
		((ScrollView*)handle)->setScrollBarWidth(v);
		break;
	case CC_SCROLLVIEWJUMPTOPERCENTHORIZONTAL:
		((ScrollView*)handle)->jumpToPercentHorizontal(v);
		break;
	case CC_SCROLLVIEWJUMPTOPERCENTVERTICAL:
		((ScrollView*)handle)->jumpToPercentVertical(v);
		break;
	case CC_ABSTRACTCHECKBUTTONSETZOOMSCALE:
		((AbstractCheckButton*)handle)->setZoomScale(v);
		break;
	case CC_SAESETEFFECTSVOLUME:
		((SimpleAudioEngine*)handle)->setEffectsVolume(v);
		break;
	case CC_SAESETBACKGROUNDMUSICVOLUME:
		((SimpleAudioEngine*)handle)->setBackgroundMusicVolume(v);
		break;
	case CC_BTNSETZOOMSCALE:
		((Button*)handle)->setZoomScale(v);
		break;
	case CC_BTNSETTITLEFONTSIZE:
		((Button*)handle)->setTitleFontSize(v);
		break;
	case APP_SETINTERVAL:
		((XCApplication*)handle)->setAnimationInterval(v);
		break;
	case CC_DIRMAINLOOP:
		((Director*)handle)->mainLoop(v);
		break;
	case CC_DIRSETCONTENTSCALEFACTOR:
		((Director*)handle)->setContentScaleFactor(v);
		break;
	case CC_NODESETGLOBALZORDER:
		((Node*)handle)->setGlobalZOrder(v);
		break;
	case CC_NODESETSCALEX:
		((Node*)handle)->setScaleX(v);
		break;
	case CC_NODESETSCALEY:
		((Node*)handle)->setScaleY(v);
		break;
	case CC_NODESETSCALEZ:
		((Node*)handle)->setScaleZ(v);
		break;
	case CC_NODESETSCALE:
		((Node*)handle)->setScale(v);
		break;
	case CC_NODESETPOSITIONX:
		((Node*)handle)->setPositionX(v);
		break;
	case CC_NODESETPOSITIONY:
		((Node*)handle)->setPositionY(v);
		break;
	case CC_NODESETPOSITIONZ:
		((Node*)handle)->setPositionZ(v);
		break;
	case CC_NODESETSKEWX:
		((Node*)handle)->setSkewX(v);
		break;
	case CC_NODESETSKEWY:
		((Node*)handle)->setSkewY(v);
		break;
	case CC_NODESETROTATION:
		((Node*)handle)->setRotation(v);
		break;
	case CC_NODESETROTATIONX:
		((Node*)handle)->setRotationX(v);
		break;
	case CC_NODESETROTATIONY:
		((Node*)handle)->setRotationY(v);
		break;
	case CC_NODEUPDATE:
		((Node*)handle)->update(v);
		break;
	case CC_ACTSTEP:
		((Action*)handle)->step(v);
		break;
	case CC_DIRSETANIMATIONINTERVAL:
		((Director*)handle)->setAnimationInterval(v);
		break;
	case CC_ACTIONSETDURATION:
		((FiniteTimeAction*)handle)->setDuration(v);
		break;
	case CC_ACTIONINTERVALSETAMPLITUDERATE:
		((ActionInterval*)handle)->setAmplitudeRate(v);
		break;
	case CC_ACTIONSPEEDSETSPEED:
		((Speed*)handle)->setSpeed(v);
		break;
	}
}

XNLEXPORT xlong XI_CDECL xcocos_func_param_long_int_objs(xlong handle, xint proid, xint v, XObject * params) {
	switch (proid) {
	case CC_LISTVIEWSCROLLTOITEM5:
	{
		double * param = (double*)gs_env->getPointerOfArray(params);
		((ListView*)handle)->scrollToItem(v, Vec2(param[0], param[1]), Vec2(param[2], param[3]), param[4]);
	}

	break;
	case CC_LISTVIEWSCROLLTOITEM:
	{
		double * param = (double*)gs_env->getPointerOfArray(params);
		((ListView*)handle)->scrollToItem(v, Vec2(param[0], param[1]), Vec2(param[2], param[3]));
	}

	break;
	case CC_LISTVIEWGETBOTTOMMOSTITEMINCURRENTVIEW:
	{
		double * param = (double*)gs_env->getPointerOfArray(params);
		((ListView*)handle)->jumpToItem(v, Vec2(param[0], param[1]), Vec2(param[2], param[3]));
	}

	break;
	case CC_GLVIEWSETDESIGNRESOLUTIONSIZE: 
	{
		double * param = (double*)gs_env->getPointerOfArray(params);
		((GLView*)handle)->setDesignResolutionSize(param[0], param[1],(ResolutionPolicy) v);
	}
		
		break;
	}
	return 0;
}

XNLEXPORT xint XI_CDECL xcocox_int_func(xlong handle, xint proid) {
	switch (proid) {
	case CC_LISTVIEWGETCURSELECTEDINDEX:
		return (xint)((ListView*)handle)->getCurSelectedIndex();
		break;
	case CC_LISTVIEWGETMAGNETICALLOWEDOUTOFBOUNDARY:
		return (xint)((ListView*)handle)->getMagneticAllowedOutOfBoundary() ? 1 : 0;
		break;
	case CC_LISTVIEWGETMAGNETICTYPE:
		return (xint)((ListView*)handle)->getMagneticType();
		break;
	case CC_SCROLLVIEWISAUTOSCROLLING:
		return (xint)((ScrollView*)handle)->isAutoScrolling() ? 1 : 0;
		break;
	case CC_SCROLLVIEWISSCROLLING:
		return (xint)((ScrollView*)handle)->isScrolling() ? 1 : 0;
		break;
	case CC_SCROLLVIEWISSCROLLBARAUTOHIDEENABLED:
		return (xint)((ScrollView*)handle)->isScrollBarAutoHideEnabled() ? 1 : 0;
		break;
	case CC_SCROLLVIEWGETSCROLLBAROPACITY:
		return (xint)((ScrollView*)handle)->getScrollBarOpacity();
		break;
	case CC_SCROLLVIEWISSCROLLBARENABLED:
		return (xint)((ScrollView*)handle)->isScrollBarEnabled() ? 1 : 0;
		break;
	case CC_SCROLLVIEWISINERTIASCROLLENABLED:
		return (xint)((ScrollView*)handle)->isInertiaScrollEnabled() ? 1 : 0;
		break;
	case CC_SCROLLVIEWISBOUNCEENABLED:
		return (xint)((ScrollView*)handle)->isBounceEnabled() ? 1 : 0;
		break;
	case CC_SCROLLVIEWGETDIRECTION:
		return (xint)((ScrollView*)handle)->getDirection();
		break;
	case CC_ABSTRACTCHECKBUTTONISSELECTED:
		return (xint)((AbstractCheckButton*)handle)->isSelected() ? 1 : 0;
		break;
	case CC_LAYOUTISPASSFOCUSTOCHILD:
		return (xint)((Layout*)handle)->isPassFocusToChild() ? 1 : 0;
		break;
	case CC_LAYOUTISLOOPFOCUS:
		return (xint)((Layout*)handle)->isLoopFocus() ?  1 : 0;
		break;
	case CC_LAYOUTGETLAYOUTTYPE:
		return (xint)((Layout*)handle)->getLayoutType();
		break;
	case CC_LAYOUTISCLIPPINGENABLED:
		return (xint)((Layout*)handle)->isClippingEnabled() ? 1 : 0;
		break;
	case CC_LAYOUTGETCLIPPINGTYPE:
		return (xint)((Layout*)handle)->getClippingType();
		break;
	case CC_LAYOUTGETBACKGROUNDIMAGEOPACITY:
		return (xint)((Layout*)handle)->getBackGroundImageOpacity();
		break;
	case CC_LAYOUTGETBACKGROUNDCOLOROPACITY:
		return (xint)((Layout*)handle)->getBackGroundColorOpacity();
		break;
	case CC_LAYOUTISBACKGROUNDIMAGESCALE9ENABLED:
		return (xint)((Layout*)handle)->isBackGroundImageScale9Enabled() ? 1 : 0;
		break;
	case CC_LAYOUTGETBACKGROUNDCOLORTYPE:
		return (xint)((Layout*)handle)->getBackGroundColorType();
		break;
	case CC_SAEISBACKGROUNDMUSICPLAYING:
		return (xint)((SimpleAudioEngine*)handle)->isBackgroundMusicPlaying() ? 1 : 0;
		break;
	case CC_SAEWILLPLAYBACKGROUNDMUSIC:
		return (xint)((SimpleAudioEngine*)handle)->willPlayBackgroundMusic() ? 1 : 0;
		break;
	case CC_BTNISSCALE9ENABLED:
		return (xint)((Button*)handle)->isScale9Enabled() ? 1 : 0;
		break;
	case CC_WIDGETINIT:
		return (xint)((Widget*)handle)->init() ? 1 : 0;
		break;
	case CC_WIDGETISLAYOUTCOMPONENTENABLED:
		return (xint)((Widget*)handle)->isLayoutComponentEnabled() ? 1 : 0;
		break;
	case CC_WIDGETISUNIFYSIZEENABLED:
		return (xint)((Widget*)handle)->isUnifySizeEnabled() ? 1 : 0;
		break;
	case CC_WIDGETISFOCUSENABLED:
		return (xint)((Widget*)handle)->isFocusEnabled() ? 1 : 0;
		break;
	case CC_WIDGETISFOCUSED:
		return (xint)((Widget*)handle)->isFocused() ? 1 : 0;
		break;
	case CC_WIDGETISSWALLOWTOUCHES:
		return (xint)((Widget*)handle)->isSwallowTouches() ? 1 : 0;
		break;
	case CC_WIDGETISPROPAGATETOUCHEVENTS:
		return (xint)((Widget*)handle)->isPropagateTouchEvents() ? 1 : 0;
		break;
	case CC_WIDGETGETACTIONTAG:
		return (xint)((Widget*)handle)->getActionTag();
		break;
	case CC_WIDGETISIGNORECONTENTADAPTWITHSIZE:
		return (xint)((Widget*)handle)->isIgnoreContentAdaptWithSize() ? 1 : 0;
		break;
	case CC_WIDGETGETSIZETYPE:
		return (xint)((Widget*)handle)->getSizeType();
		break;
	case CC_WIDGETISFLIPPEDY:
		return (xint)((Widget*)handle)->isFlippedY() != 0;
		break;
	case CC_WIDGETISFLIPPEDX:
		return (xint)((Widget*)handle)->isFlippedX() != 0;
		break;
	case CC_WIDGETGETPOSITIONTYPE:
		return (xint)((Widget*)handle)->getPositionType();
		break;
	case CC_WIDGETISHIGHLIGHTED:
		return (xint)((Widget*)handle)->isHighlighted() ?  1 : 0;
		break;
	case CC_WIDGETISTOUCHENABLED:
		return (xint)((Widget*)handle)->isTouchEnabled() ? 1 : 0;
		break;
	case CC_WIDGETISBRIGHT:
		return (xint)((Widget*)handle)->isBright() ? 1 : 0;
		break;
	case APP_GETPLARFORM:
		return (xint)((XCApplication*)handle)->getTargetPlatform();
		break;
	case CC_DIRGETPROJECTIONMATRIXSTACKSIZE:
		return (xint)((Director*)handle)->getProjectionMatrixStackSize();
		break;
	case CC_DIRISVALID:
		return (xint)((Director*)handle)->isValid() ? 1 : 0;
		break;
	case CC_NODEGETLOCALZORDER:
		return ((Node*)handle)->getZOrder();
		break;
	case CC_NODEISVISIBLE:
		return ((Node*)handle)->isVisible() ? 1 : 0;
		break;
	case CC_NODEISIGNOREANCHORPOINTFORPOSITION:
		return ((Node*)handle)->isIgnoreAnchorPointForPosition() ? 1 : 0;
		break;
	case CC_NODEGETCHILDRENCOUNT:
		return ((Node*)handle)->getChildrenCount();
		break;
	case CC_NODEGETTAG:
		return ((Node *)handle)->getTag();
		break;
	case CC_NODEISRUNNING:
		return ((Node *)handle)->isRunning();
		break;
	case CC_NODEGETOPACITY:
		return ((Node *)handle)->getOpacity();
		break;
	case CC_NODEGETDISPLAYEDOPACITY:
		return ((Node *)handle)->getDisplayedOpacity();
		break;
	case CC_NODEISCASCADEOPACITYENABLED:
		return ((Node *)handle)->isCascadeOpacityEnabled() ? 1 : 0;
		break;
	case CC_NODEISCASCADECOLORENABLED:
		return ((Node *)handle)->isCascadeColorEnabled() ? 1 : 0;
		break;
	case CC_NODEISOPACITYMODIFYRGB:
		return ((Node *)handle)->isOpacityModifyRGB() ? 1 : 0;
		break;
	case CC_NODEGETNUMBEROFRUNNINGACTIONS:
		return ((Node *)handle)->getNumberOfRunningActions();
		break;
	case CC_SCENEINIT:
		return ((XScene *)handle)->original_init() ? 1 : 0;
		break;
	case CC_SCENECREATE:
		return ((XScene *)handle)->to_create() ? 1 : 0;
		break; 
	case CC_ACTISDONE:
		return ((Action *)handle)->isDone() ? 1 : 0;
		break;
	case CC_ACTGETTAG:
		return ((Action *)handle)->getTag();
		break;
	case CC_ACTGETFLAGS:
		return ((Action *)handle)->getFlags();
		break;
	case CC_FOLLOWISBOUNDARYSET:
		return ((Follow *)handle)->isBoundarySet() ? 1 : 0;
		break;
	case CC_WIDGETISENABLED:
		return ((Widget *)handle)->isEnabled() ? 1 : 0;
		break;
	}
	return 0;
}


XNLEXPORT XObject * XI_CDECL xcocox_string_func(xlong handle, xint proid) {
	std::string text;
	switch (proid) {
	case APP_GETVERSION:
		text = ((XCApplication*)handle)->getVersion();
		break;
	case APP_GETSRCPATH:
		text = ((XCApplication*)handle)->getResourceRootPath();
		break;
	case CC_NODEGETDESCRIPTION:
		text = ((Node*)handle)->getDescription();
		break;
	case CC_NODEGETNAME:
		text = ((Node*)handle)->getName();
		break;
	}
	return string2XString(text);
}


XNLEXPORT bool XI_CDECL xcocox_bool_func_string(xlong handle, xint proid, xstring uri) {
	switch (proid) {
	case CC_SAEPRELOAD:
		((SimpleAudioEngine*)handle)->preloadBackgroundMusic(uri);
		break;
	case CC_BTNSETTITLEFONTNAME:
		((Button*)handle)->setTitleFontName(uri);
		break;
	case CC_BTNSETTITLETEXT:
		((Button*)handle)->setTitleText(uri);
		break;
	case CC_WIDGETSETCALLBACKTYPE:
		((Widget*)handle)->setCallbackType(uri);
		break;
	case CC_WIDGETSETCALLBACKNAME:
		((Widget*)handle)->setCallbackName(uri);
		break;
	case APP_OPENURL:
		return ((XCApplication*)handle)->openURL(uri);
		break;
	case APP_SETSRCPATH:
		((XCApplication*)handle)->setResourceRootPath(uri);
		break;
	case CC_NODESETNAME:
		((Node*)handle)->setName(uri);
		break;
	case CC_NODEREMOVECOMPONENT:
		((Node*)handle)->removeComponent(uri);
		break;
	}
	return 0;
}




XNLEXPORT xlong XI_CDECL create_xxobject_params(xint proid, XObject * obj, XObject * params) {
	switch (proid)
	{
	case CC_OBJ_SCENE:
	{
		XScene * pScene = new XScene(obj);
		if (pScene != 0) {
			pScene->autorelease();
			pScene->retain();
			if (params != 0) {
				pScene->withwh = true;
				gs_env->getElementValue(params, 0, &pScene->wh[0], 2);
			}
			return xlong(pScene);
		}
	}
		break;
	default:
		break;
	}
	return 0;
}


XNLEXPORT xlong XI_CDECL create_xxobject(xint proid, XObject * obj, xint type) {
	if (proid == CC_CREATEOBJECT) {
		switch (type) {
		case CC_OBJ_APPLICATION:
			return (xlong)new XCApplication(gs_env->referenceObject(obj));
			break;

		case CC_OBJ_SIMPLEAUDIO:
			return (xlong)SimpleAudioEngine::getInstance();
			break;
		}
	}
	return 0;
}