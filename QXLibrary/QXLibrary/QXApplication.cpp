#include "qxlibrary_global.h"
#include "QXApplication.h"
#ifdef WIN32
#include <conio.h>
#endif
#include <assert.h>
extern XNLEnv * gs_env;

extern XObject * _application;

XMethod * onNotify = NULL;
XMethod * createObject = NULL;

extern megInfo megs[];
XNLEXPORT XObject * getObjectXControl(QObject * obj);
std::map<int, const char*> msgMap;
XObjectData * _maindata = 0;
extern XIDENT * methodIdent;
ActionReceiver ar;




QXApplication::QXApplication(int &argc, char **argv)
	:QApplication(argc, argv)
{
	for (size_t i = 0; i < 169; i++) {
		msgMap[megs[i].id] = megs[i].name;
	}
}

QXApplication::~QXApplication()
{
}


 XObject * getObjectControl(QObject * obj) {
	if (obj == 0) {
		return 0;
	}
	XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

	if (objectData == NULL) {
		objectData = new XObjectData();
		XObject * object_type = gs_env->createObject();
		XObject * objectvalue = gs_env->createObject();
		const char * type = obj->metaObject()->className();
		if (strcmp(type, "QMenu") == 0) {
			QMenu * pm = (QMenu*)obj;
			QList<QAction*> acts =  pm->actions();
			for (QAction* act : acts) {
				getObjectControl(act);
				ar.installAction(act);
			}
		}
		if (strcmp(type, "QTreeWidget") == 0) {
			ar.installTreeAction(obj);
		}
		if (strcmp(type, "QPushButton") == 0 || strcmp(type, "QCheckBox") == 0) {
			ar.installButtonAction(obj);
		}
		if (strcmp(type, "QLineEdit") == 0) {
			ar.installEditAction(obj);
		}
		if (strcmp(type, "QTableWidget") == 0) {
			ar.installTableCellChange((QTableWidget*)obj);
		}
		if (strcmp(type, "QDialog") == 0) {
			QDialog * pm = (QDialog*)obj;
			ar.installDialogAction(pm);
		}
		if (strcmp(type, "QComboBox") == 0) {
			ar.installComboBoxAction((QComboBox*)obj);
		}
		if (strcmp(type, "QFileSystemWatcher") == 0) {
			ar.installFSWEvent((QFileSystemWatcher*)obj);
		}
		XThread thread;

		gs_env->setValue(thread.getThread(), object_type, type, strlen(type));
		gs_env->setValue(objectvalue, (xlong)obj);
		XObject * res = gs_env->invoke(thread.getThread(), _application, createObject, objectvalue, object_type);
		if (res != 0) {
			int tp = gs_env->getObjectType(res);

			if (gs_env->getObjectType(res) == XNLEnv::t_object) {
				objectData->setObject(res);
			}else {
				objectData->setObject(NULL);
			}
			gs_env->dereferenceObject(res);
		}
		else {
			objectData->setObject(NULL);
		}
		obj->setUserData(Qt::UserRole, objectData);
		gs_env->dereferenceObject(object_type);
		gs_env->dereferenceObject(objectvalue);
	}
	return objectData->getObject();
}



XNLEXPORT  XObject * getObjectXControl(QObject * obj) {
	if (obj == NULL) {
		return NULL;
	}

	XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

	if (objectData == NULL) {
		return NULL;
	}

	if (objectData->getObject() == NULL) {
		return NULL;
	}

	return objectData->getObject();
}

int serial = 0;

bool QXApplication::notify(QObject * obj, QEvent * evn){

		//cprintf("%d = %s [%s:%s] \n", evn->type(), msgMap[evn->type()], obj->metaObject()->className(), obj->objectName().toLatin1().data());
    

    QStringList pargs = QCoreApplication::arguments();
	XObject * xobj = getObjectXControl(obj);
	if (xobj == NULL) {
		return QApplication::notify(obj, evn);
	}
	
	XThread thread;

	if (xobj != NULL) {
		int tp = gs_env->getObjectType(xobj);
		if (tp == XNLEnv::XDataType::t_object) {
			if (false == TranslateEvent(obj, xobj, evn, thread.getThread())) {
				return false;
			}
		}
	}
	
    return QApplication::notify(obj, evn);
}

XNLEXPORT  void nativeFinalize(XObject * xobj) {
	XThread thread;
	gs_env->void_invoke(thread.getThread(), xobj, methodIdent[FINALIZE_ID].methodId);
}

template<class _Type>
XObject * createXObject(_Type v) {
	XObject * obj = gs_env->createObject();
	gs_env->setValue(obj, v);
	return obj;
}

XNLEXPORT XObject * createXObject(QString v) {
	XThread thread;
	QByteArray qba = v.toUtf8();
	XObject * obj = gs_env->createObject();
	gs_env->setValue(thread.getThread(), obj, qba.data(), qba.length());
	return obj;
}


bool QXApplication::TranslateEvent(QObject * obj,XObject * xobj ,QEvent * evn, XContext * context) {
	
	int type = evn->type();
	
	if (type == NotifyEvent::XNotify) {
		type = NOTIFY_ID;
	}

	int method = methodIdent[type].methodId;
	if (method == -1) {
		return true;
	}

	switch (type){
	case NOTIFY_ID:
	{
		XObject * timeid = createXObject(((QTimerEvent*)evn)->timerId());
		gs_env->setValue(timeid, (xlong)((NotifyEvent*)evn)->value);
		gs_env->void_invoke(context, xobj, method, timeid);
		gs_env->dereferenceObject(timeid);
	}
		break;
	case QEvent::Timer:
	{
		XObject * timeid = createXObject(((QTimerEvent*)evn)->timerId());
		gs_env->void_invoke(context, xobj, method, timeid);
		gs_env->dereferenceObject(timeid);
	}
		break;

	case QEvent::MouseButtonPress:
	{
		XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

		XObject * Button = createXObject((int)((QMouseEvent*)evn)->button());
		XObject * x = createXObject((int)((QMouseEvent*)evn)->x());
		XObject * y = createXObject((int)((QMouseEvent*)evn)->y());
		XObject * flags = createXObject((int)((QMouseEvent*)evn)->flags());
		XObject * source = createXObject((int)((QMouseEvent*)evn)->source());

		gs_env->void_invoke(context, xobj, method, Button, x, y, flags, source);
		
		gs_env->dereferenceObject(Button);
		gs_env->dereferenceObject(x);
		gs_env->dereferenceObject(y);
		gs_env->dereferenceObject(flags);
		gs_env->dereferenceObject(source);
		
	}
		break;

	case QEvent::MouseButtonRelease:
	{
		XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

		XObject * Button = createXObject((int)((QMouseEvent*)evn)->button());
		XObject * x = createXObject((int)((QMouseEvent*)evn)->x());
		XObject * y = createXObject((int)((QMouseEvent*)evn)->y());
		XObject * flags = createXObject((int)((QMouseEvent*)evn)->flags());
		XObject * source = createXObject((int)((QMouseEvent*)evn)->source());


		gs_env->void_invoke(context, xobj, method, Button, x, y, flags, source);
		
		gs_env->dereferenceObject(Button);
		gs_env->dereferenceObject(x);
		gs_env->dereferenceObject(y);
		gs_env->dereferenceObject(flags);
		gs_env->dereferenceObject(source);
		
	}
		break;

	case QEvent::MouseButtonDblClick:
	{
		XObject * Button = createXObject((int)((QMouseEvent*)evn)->button());
		XObject * x = createXObject((int)((QMouseEvent*)evn)->x());
		XObject * y = createXObject((int)((QMouseEvent*)evn)->y());
		XObject * flags = createXObject((int)((QMouseEvent*)evn)->flags());
		XObject * source = createXObject((int)((QMouseEvent*)evn)->source());

		gs_env->void_invoke(context, xobj, method, Button, x, y, flags, source);
		
		gs_env->dereferenceObject(Button);
		gs_env->dereferenceObject(x);
		gs_env->dereferenceObject(y);
		gs_env->dereferenceObject(flags);
		gs_env->dereferenceObject(source);
	}
		break;

	case QEvent::MouseMove:
	{
		XObject * Button = createXObject((int)((QMouseEvent*)evn)->button());
		XObject * x = createXObject((int)((QMouseEvent*)evn)->x());
		XObject * y = createXObject((int)((QMouseEvent*)evn)->y());
		XObject * flags = createXObject((int)((QMouseEvent*)evn)->flags());
		XObject * source = createXObject((int)((QMouseEvent*)evn)->source());

		XObject * actionobj = 0;

		gs_env->void_invoke(context, xobj, method, Button, x, y, flags, source);
		

		gs_env->dereferenceObject(Button);
		gs_env->dereferenceObject(x);
		gs_env->dereferenceObject(y);
		gs_env->dereferenceObject(flags);
		gs_env->dereferenceObject(source);
	}
		break;

	case QEvent::KeyPress:
	{
		XObject * key = createXObject((int)((QKeyEvent*)evn)->key());
		XObject * repeat = createXObject(((QKeyEvent*)evn)->isAutoRepeat());
		XObject * count = createXObject((int)((QKeyEvent*)evn)->count());
		XObject * text = createXObject(((QKeyEvent*)evn)->text());
		XObject * scanCode = createXObject((int)((QKeyEvent*)evn)->nativeScanCode());
		XObject * virtualKey = createXObject((int)((QKeyEvent*)evn)->nativeVirtualKey());
		XObject * modifier = createXObject((int)((QKeyEvent*)evn)->modifiers());

		XContext * pContext = context;
		XObject * res = gs_env->invoke(pContext, xobj, method, key, repeat, count, text, scanCode, virtualKey, modifier);

		gs_env->dereferenceObject(key);
		gs_env->dereferenceObject(repeat);
		gs_env->dereferenceObject(count);
		gs_env->dereferenceObject(text);
		gs_env->dereferenceObject(scanCode);
		gs_env->dereferenceObject(virtualKey);
		gs_env->dereferenceObject(modifier);

		if (res != 0) {
			bool bret = true;
			if (gs_env->getBoolValue(res, &bret)) {
				if (bret) {
					evn->accept();
				}
				else {
					evn->ignore();
					gs_env->dereferenceObject(res);
					return false;
				}
			}
			else {
				evn->accept();
			}
			gs_env->dereferenceObject(res);
		}
		Qt::Key_Up;
	}
		break;

	case QEvent::KeyRelease:
	{
		XObject * key = createXObject((int)((QKeyEvent*)evn)->key());
		XObject * repeat = createXObject(((QKeyEvent*)evn)->isAutoRepeat());
		XObject * count = createXObject((int)((QKeyEvent*)evn)->count());
		XObject * text = createXObject(((QKeyEvent*)evn)->text());
		XObject * scanCode = createXObject((int)((QKeyEvent*)evn)->nativeScanCode());
		XObject * virtualKey = createXObject((int)((QKeyEvent*)evn)->nativeVirtualKey());
		XObject * modifier = createXObject((int)((QKeyEvent*)evn)->modifiers());

		XContext * pContext = context;
		XObject * res = gs_env->invoke(pContext, xobj, method, key, repeat, count, text, scanCode, virtualKey, modifier);

		gs_env->dereferenceObject(key);
		gs_env->dereferenceObject(repeat);
		gs_env->dereferenceObject(count);
		gs_env->dereferenceObject(text);
		gs_env->dereferenceObject(scanCode);
		gs_env->dereferenceObject(virtualKey);
		gs_env->dereferenceObject(modifier);

		if (res != 0) {
			bool bret = true;
			if (gs_env->getBoolValue(res, &bret)) {
				if (bret) {
					evn->accept();
				}
				else {
					evn->ignore();
					gs_env->dereferenceObject(res);
					return false;
				}
			}
			else {
				evn->accept();
			}
			gs_env->dereferenceObject(res);
		}
	}
		break;

	case QEvent::FocusIn:
	{
		XObject * focus = createXObject(((QFocusEvent*)evn)->gotFocus());
		XObject * reson = createXObject(((QFocusEvent*)evn)->reason());

		gs_env->void_invoke(context, xobj, method, focus, reson);

		gs_env->dereferenceObject(focus);
		gs_env->dereferenceObject(reson);
	}
		//QFocusEvent
		break;

	case QEvent::FocusOut:
	{
		XObject * focus = createXObject(((QFocusEvent*)evn)->gotFocus());
		XObject * reson = createXObject(((QFocusEvent*)evn)->reason());

		gs_env->void_invoke(context, xobj, method, focus, reson);

		gs_env->dereferenceObject(focus);
		gs_env->dereferenceObject(reson);
	}
		break;

	case QEvent::FocusAboutToChange:
	{
		XObject * focus = createXObject(((QFocusEvent*)evn)->gotFocus());
		XObject * reson = createXObject(((QFocusEvent*)evn)->reason());

		gs_env->void_invoke(context, xobj, method, focus, reson);

		gs_env->dereferenceObject(focus);
		gs_env->dereferenceObject(reson);
	}
		break;

	case QEvent::Enter:
	{
		XObject * x = createXObject(((QEnterEvent*)evn)->x());
		XObject * y = createXObject(((QEnterEvent*)evn)->y());

		gs_env->void_invoke(context, xobj, method, x, y);

		gs_env->dereferenceObject(x);
		gs_env->dereferenceObject(y);
	}
		//QEnterEvent
		break;

	case QEvent::Leave:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::Paint:
		//QPaintEvent
	{
		QWidget * pw = qobject_cast<QWidget *>(obj);
		if (pw != 0) {
			QPainter painter(pw);
			XObject * l = createXObject(((QPaintEvent*)evn)->rect().left());
			XObject * t = createXObject(((QPaintEvent*)evn)->rect().top());
			XObject * r = createXObject(((QPaintEvent*)evn)->rect().right());
			XObject * b = createXObject(((QPaintEvent*)evn)->rect().bottom());
			XObject * p = createXObject((xlong)&painter);

			gs_env->void_invoke(context, xobj, method, l, t, r, b, p);

			gs_env->dereferenceObject(l);
			gs_env->dereferenceObject(t);
			gs_env->dereferenceObject(r);
			gs_env->dereferenceObject(b);
			gs_env->dereferenceObject(p);
		}
	}
		break;

	case QEvent::Move:
	{
		XObject * x = createXObject(((QMoveEvent*)evn)->pos().x());
		XObject * y = createXObject(((QMoveEvent*)evn)->pos().y());
		XObject * ox = createXObject(((QMoveEvent*)evn)->oldPos().x());
		XObject * oy = createXObject(((QMoveEvent*)evn)->oldPos().y());

		gs_env->void_invoke(context, xobj, method, x, y, ox, oy);

		gs_env->dereferenceObject(x);
		gs_env->dereferenceObject(y);
		gs_env->dereferenceObject(ox);
		gs_env->dereferenceObject(oy);
	}
		//QMoveEvent
		break;

	case QEvent::Resize:
	{
		XObject * w = createXObject(((QResizeEvent*)evn)->size().width());
		XObject * h = createXObject(((QResizeEvent*)evn)->size().height());
		XObject * ow = createXObject(((QResizeEvent*)evn)->oldSize().width());
		XObject * oh = createXObject(((QResizeEvent*)evn)->oldSize().height());

		gs_env->void_invoke(context, xobj, method, w, h, ow, oh);

		gs_env->dereferenceObject(w);
		gs_env->dereferenceObject(h);
		gs_env->dereferenceObject(ow);
		gs_env->dereferenceObject(oh);
	}
		break;

	case QEvent::Create:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::Destroy:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::Show:
		gs_env->void_invoke(context, xobj, method);
		//QShowEvent
		break;

	case QEvent::Hide:
		gs_env->void_invoke(context, xobj, method);
		//QHideEvent
		break;

	case QEvent::Close:
	{

		XObject * res = gs_env->invoke(context, xobj, method);

		if (res != 0) {
			bool bret = true;
			if (gs_env->getBoolValue(res, &bret)) {
				if (bret) {
					evn->accept();
				}
				else {
					evn->ignore();
					gs_env->dereferenceObject(res);
					return false;
				}
			}
			else {
				evn->accept();
			}
			gs_env->dereferenceObject(res);
		}

	}
		//QCloseEvent
		break;

	case QEvent::Quit:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::ParentChange:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::ParentAboutToChange:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::ThreadChange:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::WindowActivate:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::WindowDeactivate:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::ShowToParent:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::HideToParent:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::Wheel:
	{
		XObject * button = createXObject((int)((QWheelEvent*)evn)->buttons());
		XObject * x = createXObject(((QWheelEvent*)evn)->x());
		XObject * y = createXObject(((QWheelEvent*)evn)->y());
		XObject * Orientation = createXObject((int)((QWheelEvent*)evn)->orientation());
		XObject * delta = createXObject(((QWheelEvent*)evn)->delta());
		XObject * inverted = createXObject(((QWheelEvent*)evn)->inverted());

		gs_env->void_invoke(context, xobj, method, button, x, y, Orientation, delta, inverted);
		
		gs_env->dereferenceObject(button);
		gs_env->dereferenceObject(x);
		gs_env->dereferenceObject(y);
		gs_env->dereferenceObject(Orientation);
		gs_env->dereferenceObject(delta);
		gs_env->dereferenceObject(inverted);
	}
		//
		break;

	case QEvent::WindowTitleChange:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::WindowIconChange:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::ApplicationWindowIconChange:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::ApplicationFontChange:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::ApplicationLayoutDirectionChange:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::ApplicationPaletteChange:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::PaletteChange:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::Clipboard:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::Speech:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::MetaCall:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::SockAct:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::WinEventAct:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::DeferredDelete:
		//QDeferredDeleteEvent
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::DragEnter:
	{
		QDragEnterEvent *ge = (QDragEnterEvent *)evn;

		XObject * l = createXObject(ge->answerRect().left());
		XObject * t = createXObject(ge->answerRect().top());
		XObject * r = createXObject(ge->answerRect().right());
		XObject * b = createXObject(ge->answerRect().bottom());

		XObject * res = gs_env->invoke(context, xobj, method, l, t, r ,b);

		gs_env->dereferenceObject(l);
		gs_env->dereferenceObject(t);
		gs_env->dereferenceObject(r);
		gs_env->dereferenceObject(b);

		if (res != 0) {
			bool bret = true;
			if (gs_env->getBoolValue(res, &bret)) {
				if (bret) {
					ge->acceptProposedAction();
				}
			}
			gs_env->dereferenceObject(res);
		}
	}
		 
		break;

	case QEvent::DragMove:
	{
		QDragMoveEvent *ge = (QDragMoveEvent *)evn;

		XObject * l = createXObject(ge->answerRect().left());
		XObject * t = createXObject(ge->answerRect().top());
		XObject * r = createXObject(ge->answerRect().right());
		XObject * b = createXObject(ge->answerRect().bottom());

		XObject * res = gs_env->invoke(context, xobj, method, l, t, r, b);

		gs_env->dereferenceObject(l);
		gs_env->dereferenceObject(t);
		gs_env->dereferenceObject(r);
		gs_env->dereferenceObject(b);

		if (res != 0) {
			bool bret = true;
			if (gs_env->getBoolValue(res, &bret)) {
				if (bret) {
					ge->acceptProposedAction();
				}
			}
			gs_env->dereferenceObject(res);
		}
	}
		break;

	case QEvent::DragLeave:
	{
		

		XObject * l = createXObject(0);
		XObject * t = createXObject(0);
		XObject * r = createXObject(0);
		XObject * b = createXObject(0);

		gs_env->void_invoke(context, xobj, method, l, t, r, b);

		gs_env->dereferenceObject(l);
		gs_env->dereferenceObject(t);
		gs_env->dereferenceObject(r);
		gs_env->dereferenceObject(b);

	}
		break;

	case QEvent::Drop:
	{
		QDropEvent *ge = (QDropEvent *)evn;
		QList<QUrl> urls = ge->mimeData()->urls();

		XObject * strbjects = gs_env->createStringArray(urls.size());

		XThread thread;

		if (urls.isEmpty() == false) {
			for (size_t i = 0; i < urls.size(); i++) {
				const QUrl & surl = urls.at(i);
				QByteArray str = surl.toLocalFile().toUtf8();
				xstring xs = str.data();
				int xl = str.length();
				gs_env->setElementValue(thread.getThread(), strbjects, i, &xs, &xl, 1);
			}
		}

		gs_env->void_invoke(context, xobj, method, strbjects);

		gs_env->dereferenceObject(strbjects);
	}
		
		break;

	case QEvent::DragResponse:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::ChildAdded:
		//QChildEvent
		//OutputDebugString(L"ChildAdded");
		break;

	case QEvent::ChildPolished:
		//QChildEvent
		break;

	case QEvent::ChildRemoved:
		//QChildEvent
		break;

	case QEvent::ShowWindowRequest:

		break;

	case QEvent::PolishRequest:

		break;

	case QEvent::Polish:

		break;

	case QEvent::LayoutRequest:

		break;

	case QEvent::UpdateRequest:
		gs_env->void_invoke(context, xobj, method);
		break;

	case QEvent::UpdateLater:

		break;

	case QEvent::EmbeddingControl:

		break;

	case QEvent::ActivateControl:

		break;

	case QEvent::DeactivateControl:

		break;

	case QEvent::ContextMenu:
	{
		XObject * x = createXObject((xint)((QContextMenuEvent*)evn)->x());
		XObject * y = createXObject((xint)((QContextMenuEvent*)evn)->y());
		XObject * reson = createXObject((xint)((QContextMenuEvent*)evn)->reason());

		gs_env->void_invoke(context, xobj, method, x, y, reson);

		gs_env->dereferenceObject(x);
		gs_env->dereferenceObject(y);
		gs_env->dereferenceObject(reson);
	}
		break;

	case QEvent::InputMethod:
		//QInputMethodEvent
		break;

	case QEvent::TabletMove:
		//QTabletEvent
		break;

	case QEvent::LocaleChange:

		break;

	case QEvent::LanguageChange:

		break;

	case QEvent::LayoutDirectionChange:

		break;

	case QEvent::Style:

		break;

	case QEvent::TabletPress:
		//QTabletEvent
		break;

	case QEvent::TabletRelease:
		//QTabletEvent
		break;

	case QEvent::OkRequest:

		break;

	case QEvent::HelpRequest:
		//QHelpEvent
		break;

	case QEvent::IconDrag:
		//QIconDragEvent
		break;

	case QEvent::FontChange:

		break;

	case QEvent::EnabledChange:

		break;

	case QEvent::ActivationChange:

		break;

	case QEvent::StyleChange:

		break;

	case QEvent::IconTextChange:

		break;

	case QEvent::ModifiedChange:

		break;

	case QEvent::MouseTrackingChange:

		break;

	case QEvent::WindowBlocked:

		break;

	case QEvent::WindowUnblocked:

		break;

	case QEvent::WindowStateChange:

		break;

	case QEvent::ReadOnlyChange:

		break;

	case QEvent::ToolTip:
		//QHelpEvent
		break;

	case QEvent::WhatsThis:
		//QHelpEvent
		break;

	case QEvent::StatusTip:
		//QStatusTipEvent
		break;

	case QEvent::ActionChanged:
		//QActionEvent
		break;

	case QEvent::ActionAdded:
		//QActionEvent
		break;

	case QEvent::ActionRemoved:
		//QActionEvent
		break;

	case QEvent::FileOpen:
		//QFileOpenEvent
		break;

	case QEvent::Shortcut:
		//QShortcutEvent
		break;

	case QEvent::ShortcutOverride:
		//QKeyEvent
		break;

	case QEvent::WhatsThisClicked:

		break;

	case QEvent::ToolBarChange:

		break;

	case QEvent::ApplicationActivate:

		break;

	case QEvent::ApplicationDeactivate:

		break;

	case QEvent::QueryWhatsThis:

		break;

	case QEvent::EnterWhatsThisMode:

		break;

	case QEvent::LeaveWhatsThisMode:

		break;

	case QEvent::ZOrderChange:

		break;

	case QEvent::HoverEnter:
		//QHoverEvent
		break;

	case QEvent::HoverLeave:
		//QHoverEvent
		break;

	case QEvent::HoverMove:
		//QHoverEvent
		break;

	case QEvent::AcceptDropsChange:

		break;

	case QEvent::ZeroTimerEvent:

		break;

	case QEvent::GraphicsSceneMouseMove:
		//QGraphicsSceneMouseEvent
		break;

	case QEvent::GraphicsSceneMousePress:
		//QGraphicsSceneMouseEvent
		break;

	case QEvent::GraphicsSceneMouseRelease:
		//QGraphicsSceneMouseEvent
		break;

	case QEvent::GraphicsSceneMouseDoubleClick:
		//QGraphicsSceneMouseEvent
		break;

	case QEvent::GraphicsSceneContextMenu:
		//QGraphicsSceneContextMenuEvent
		break;

	case QEvent::GraphicsSceneHoverEnter:
		//QGraphicsSceneHoverEvent
		break;

	case QEvent::GraphicsSceneHoverMove:
		//QGraphicsSceneHoverEvent
		break;

	case QEvent::GraphicsSceneHoverLeave:
		//QGraphicsSceneHoverEvent
		break;

	case QEvent::GraphicsSceneHelp:
		//QHelpEvent
		break;

	case QEvent::GraphicsSceneDragEnter:
		//QGraphicsSceneDragDropEvent
		break;

	case QEvent::GraphicsSceneDragMove:
		//QGraphicsSceneDragDropEvent
		break;

	case QEvent::GraphicsSceneDragLeave:
		//QGraphicsSceneDragDropEvent
		break;

	case QEvent::GraphicsSceneDrop:
		//QGraphicsSceneDragDropEvent
		break;

	case QEvent::GraphicsSceneWheel:
		//QGraphicsSceneWheelEvent
		break;

	case QEvent::KeyboardLayoutChange:

		break;

	case QEvent::DynamicPropertyChange:

		break;

	case QEvent::TabletEnterProximity:
		//QTabletEvent
		break;

	case QEvent::TabletLeaveProximity:
		//QTabletEvent
		break;

	case QEvent::NonClientAreaMouseMove:
		//QMouseEvent
		break;

	case QEvent::NonClientAreaMouseButtonPress:
		//(QMouseEvent).
		break;

	case QEvent::NonClientAreaMouseButtonRelease:
		// (QMouseEvent).
		break;

	case QEvent::NonClientAreaMouseButtonDblClick:
		//A mouse double click occurred outside the client area(QMouseEvent).
		break;

	case QEvent::MacSizeChange:

		break;

	case QEvent::ContentsRectChange:

		break;

	case QEvent::MacGLWindowChange:

		break;

	case QEvent::FutureCallOut:

		break;

	case QEvent::GraphicsSceneResize:
		//Widget was resized (QGraphicsSceneResizeEvent).
		break;

	case QEvent::GraphicsSceneMove:
		//QGraphicsSceneMoveEvent
		break;

	case QEvent::CursorChange:

		break;

	case QEvent::ToolTipChange:

		break;

	case QEvent::NetworkReplyUpdated:

		break;

	case QEvent::GrabMouse:
		//Item gains mouse grab (QGraphicsItem only).
		break;

	case QEvent::UngrabMouse:
		//	Item loses mouse grab (QGraphicsItem, QQuickItem).
		break;

	case QEvent::GrabKeyboard:
		//	Item gains keyboard grab (QGraphicsItem only).
		break;

	case QEvent::UngrabKeyboard:
		//	Item loses keyboard grab (QGraphicsItem only).
		break;

	case QEvent::MacGLClearDrawable:

		break;

	case QEvent::StateMachineSignal:
		//	A signal delivered to a state machine (QStateMachine::SignalEvent).
		break;

	case QEvent::StateMachineWrapped:
		//The event is a wrapper for, i.e., contains, another event (QStateMachine::WrappedEvent).
		break;

	case QEvent::TouchBegin:
		//QTouchEvent
		break;

	case QEvent::TouchUpdate:
		//QTouchEvent
		break;

	case QEvent::TouchEnd:
		//QTouchEvent
		break;

	case QEvent::NativeGesture:
		//QNativeGestureEvent
		break;

	case QEvent::RequestSoftwareInputPanel:

		break;

	case QEvent::CloseSoftwareInputPanel:

		break;

	case QEvent::WinIdChange:

		break;

	case QEvent::Gesture:
		//QGestureEvent
		break;

	case QEvent::GestureOverride:
		//QGestureEvent
		break;

	case QEvent::ScrollPrepare:
		//QScrollPrepareEvent
		break;

	case QEvent::Scroll:
		//QScrollEvent
		break;

	case QEvent::Expose:

		break;

	case QEvent::InputMethodQuery:
		//	A input method query event (QInputMethodQueryEvent)
		break;

	case QEvent::OrientationChange:
		//	The screens orientation has changes (QScreenOrientationChangeEvent).
		break;

	case QEvent::TouchCancel:
		//	Cancellation of touch-event sequence (QTouchEvent).
		break;

	case QEvent::ThemeChange:

		break;

	case QEvent::SockClose:

		break;

	case QEvent::PlatformPanel:

		break;

	case QEvent::StyleAnimationUpdate:

		break;

	case QEvent::ApplicationStateChange:

		break;

	case QEvent::WindowChangeInternal:

		break;

	case QEvent::ScreenChangeInternal:

		break;

	case QEvent::PlatformSurface:
		//	A native platform surface has been created or is about to be destroyed (QPlatformSurfaceEvent).
		break;

	case QEvent::Pointer:

		break;

	case QEvent::TabletTrackingChange:

		break;

	case QEvent::User:

		break;

	case QEvent::MaxUser:

		break;
	}

	return true;
}
