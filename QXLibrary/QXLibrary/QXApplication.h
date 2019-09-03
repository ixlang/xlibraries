#pragma once
#include "qxlibrary_global.h"


extern XIDENT * methodIdent;


class NotifyEvent : public QEvent
{
public:
	NotifyEvent(xlong _value):
		QEvent(XNotify){
		value = _value;
	}
	virtual ~NotifyEvent() {

	}
	xlong value;
	const static Type XNotify = static_cast<Type>(QEvent::User + 0xFF);
};


class QXApplication :
	public QApplication
{
	Q_OBJECT
public:

	QXApplication(int &argc, char **argv);
	virtual ~QXApplication();
    bool notify(QObject *, QEvent *) Q_DECL_OVERRIDE;
	static bool TranslateEvent(QObject * obj, XObject * xobj, QEvent * evn, XContext * context);
};

class ActionReceiver :
	public QObject 
{
	Q_OBJECT

public:
	ActionReceiver() {
		signalMapper = new QSignalMapper();
		setup = false;
	}
	

private slots:
	bool ActionTriggered(QObject * act) {

		XObjectData * objectData = (XObjectData *)act->userData(Qt::UserRole);
		QString st = act->objectName();
		if (objectData != NULL) {
			if (objectData->getObject() != 0) {
				XThread thread;
				gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[TRIGGER_ID].methodId);
			}
		}

		return true;
	}
	void tritemPressed(QTreeWidgetItem *item, int column) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * hitem = gs_env->createObject();
					gs_env->setValue(hitem, (xlong)item);

					XObject * xcolumn = gs_env->createObject();
					gs_env->setValue(xcolumn, (xint)column);

					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ITEMPRESS_ID].methodId, hitem, xcolumn);

					gs_env->dereferenceObject(hitem);
					gs_env->dereferenceObject(xcolumn);
				}
			}
		}
	}
	void tritemClicked(QTreeWidgetItem *item, int column) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * hitem = gs_env->createObject();
					gs_env->setValue(hitem, (xlong)item);

					XObject * xcolumn = gs_env->createObject();
					gs_env->setValue(xcolumn, (xint)column);

					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ITEMCLK_ID].methodId, hitem, xcolumn);

					gs_env->dereferenceObject(hitem);
					gs_env->dereferenceObject(xcolumn);
				}
			}
		}
	}
	void tritemDoubleClicked(QTreeWidgetItem *item, int column) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * hitem = gs_env->createObject();
					gs_env->setValue(hitem, (xlong)item);

					XObject * xcolumn = gs_env->createObject();
					gs_env->setValue(xcolumn, (xint)column);

					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ITEMDBCLK_ID].methodId, hitem, xcolumn);

					gs_env->dereferenceObject(hitem);
					gs_env->dereferenceObject(xcolumn);
				}
			}
		}
	}
	void tritemActivated(QTreeWidgetItem *item, int column) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * hitem = gs_env->createObject();
					gs_env->setValue(hitem, (xlong)item);

					XObject * xcolumn = gs_env->createObject();
					gs_env->setValue(xcolumn, (xint)column);

					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ITEMACTIVE_ID].methodId, hitem, xcolumn);

					gs_env->dereferenceObject(hitem);
					gs_env->dereferenceObject(xcolumn);
				}
			}
		}
	}
	void tritemEntered(QTreeWidgetItem *item, int column) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * hitem = gs_env->createObject();
					gs_env->setValue(hitem, (xlong)item);

					XObject * xcolumn = gs_env->createObject();
					gs_env->setValue(xcolumn, (xint)column);

					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ITEMENTER_ID].methodId, hitem, xcolumn);

					gs_env->dereferenceObject(hitem);
					gs_env->dereferenceObject(xcolumn);
				}
			}
		}
	}
	void tritemChanged(QTreeWidgetItem *item, int column) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * hitem = gs_env->createObject();
					gs_env->setValue(hitem, (xlong)item);

					XObject * xcolumn = gs_env->createObject();
					gs_env->setValue(xcolumn, (xint)column);

					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ITEMCHANGE_ID].methodId, hitem, xcolumn);

					gs_env->dereferenceObject(hitem);
					gs_env->dereferenceObject(xcolumn);
				}
			}
		}
	}
	void tritemExpanded(QTreeWidgetItem *item) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * hitem = gs_env->createObject();
					gs_env->setValue(hitem, (xlong)item);

					XObject * xcolumn = gs_env->createObject();

					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ITEMEXPAND_ID].methodId, hitem);

					gs_env->dereferenceObject(hitem);
				}
			}
		}
	}
	void tritemCollapsed(QTreeWidgetItem *item) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * hitem = gs_env->createObject();
					gs_env->setValue(hitem, (xlong)item);

					XObject * xcolumn = gs_env->createObject();

					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ITEMCOLLPA_ID].methodId, hitem);

					gs_env->dereferenceObject(hitem);
				}
			}
		}
	}
	void trcurrentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * hitem = gs_env->createObject();
					gs_env->setValue(hitem, (xlong)current);

					XObject * xcolumn = gs_env->createObject();
					gs_env->setValue(xcolumn, (xlong)previous);

					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ITEMCURCHA_ID].methodId, hitem, xcolumn);

					gs_env->dereferenceObject(hitem);
					gs_env->dereferenceObject(xcolumn);
				}
			}
		}
	}
	void tritemSelectionChanged() {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ITEMSELCHA_ID].methodId);
				}
			}
		}
	}

	void btnclicked(bool checked) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * bc = gs_env->createObject();
					gs_env->setValue(bc, checked);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[BTNCLICK_ID].methodId, bc);
					gs_env->dereferenceObject(bc);
				}
			}
		}

	}

	void btntoggled(bool checked) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * bc = gs_env->createObject();
					gs_env->setValue(bc, checked);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[TOGGLE_ID].methodId, bc);
					gs_env->dereferenceObject(bc);
				}
			}
		}
	}

	void btnpressed() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ONPRESS_ID].methodId);
				}
			}
		}
	}

	void btnreleased() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ONRELEASE_ID].methodId);
				}
			}
		}
	}

	void onFinish(int res) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * bc = gs_env->createObject();
					gs_env->setValue(bc, (xint)res);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ONFINISH_ID].methodId, bc);
					gs_env->dereferenceObject(bc);
				}
			}
		}
	}

	void onEditTextChanged(const QString & str) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					QByteArray pbtext = str.toUtf8();
					gs_env->setValue(thread.getThread(), text, pbtext.data(), pbtext.length());
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CURTEXTCHANGE].methodId, text);
					gs_env->dereferenceObject(text);
				}
			}
		}
	}

	void onActivated(int index) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * bc = gs_env->createObject();
					gs_env->setValue(bc, (xint)index);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_ACTIVATED].methodId, bc);
					gs_env->dereferenceObject(bc);
				}
			}
		}
	}
	
	void onfswFileChanged( QString path) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					QByteArray pbtext = path.toUtf8();
					gs_env->setValue(thread.getThread(), text, pbtext.data(), pbtext.length());
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_FILECHANGE].methodId, text);
					gs_env->dereferenceObject(text);
				}
			}
		}
	}

	void onfswDirectoryChanged(QString path) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					QByteArray pbtext = path.toUtf8();
					gs_env->setValue(thread.getThread(), text, pbtext.data(), pbtext.length());
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_DIRCHANGE].methodId, text);
					gs_env->dereferenceObject(text);
				}
			}
		}
	}

	void onCurrentIndexChanged(int index) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * bc = gs_env->createObject();
					gs_env->setValue(bc, (xint)index);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_SELCHANGE].methodId, bc);
					gs_env->dereferenceObject(bc);
				}
			}
		}
	}


	void onAccept() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ONACCEPT_ID].methodId);
				}
			}
		}
	}

	void onReject() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ONREJECT_ID].methodId);
				}
			}
		}
	}


	void QSCN_SELCHANGED(bool yes) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * dir = gs_env->createObject();
					gs_env->setValue(dir, yes);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_SELCHANGED_ID].methodId, dir);
					gs_env->dereferenceObject(dir);
				}
			}
		}
	}

	void SCN_AUTOCCANCELLED() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_AUTOCCANCELLED_ID].methodId);
				}
			}
		}
	}

	void SCN_AUTOCCHARDELETED() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_AUTOCCHARDELETED_ID].methodId);
				}
			}
		}
	}

	void SCN_AUTOCCOMPLETED(const char *selection, int position, int ch, int method) {

	}

	void SCN_AUTOCSELECTION(const char *selection, int position, int ch, int method) {

	}

	void SCN_AUTOCSELECTION(const char *selection, int position) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * sel = gs_env->createObject();
					XObject * pos = gs_env->createObject();
					if (selection != 0) {
						gs_env->setValue(thread.getThread(), sel, selection, strlen(selection));
					}
					gs_env->setValue(pos, (xint)position);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_AUTOCSELECTION_ID_1].methodId, sel, pos);
					gs_env->dereferenceObject(sel);
					gs_env->dereferenceObject(pos);
				}
			}
		}
	}

	void SCEN_CHANGE() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[SCEN_CHANGE_ID].methodId);
				}
			}
		}
	}

	void SCN_CALLTIPCLICK(int direction) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * dir = gs_env->createObject();
					gs_env->setValue(dir, xint(direction));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CALLTIPCLICK_ID].methodId, dir);
					gs_env->dereferenceObject(dir);
				}
			}
		}
	}

	void SCN_CHARADDED(int charadded) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * dir = gs_env->createObject();
					gs_env->setValue(dir, xint(charadded));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CHARADDED_ID].methodId, dir);
					gs_env->dereferenceObject(dir);
				}
			}
		}
	}

	void SCN_DOUBLECLICK(int position, int line, int modifiers) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * _x = gs_env->createObject();
					XObject * _y = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(_x, xint(line));
					gs_env->setValue(_y, xint(modifiers));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_DOUBLECLICK_ID].methodId, pos, _x, _y);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(_x);
					gs_env->dereferenceObject(_y);
				}
			}
		}
	}

	void SCN_DWELLEND(int position, int x, int y) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * _x = gs_env->createObject();
					XObject * _y = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(_x, xint(x));
					gs_env->setValue(_y, xint(y));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_DWELLEND_ID].methodId, pos, _x, _y);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(_x);
					gs_env->dereferenceObject(_y);
				}
			}
		}
	}

	void SCN_DWELLSTART(int position, int x, int y) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * _x = gs_env->createObject();
					XObject * _y = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(_x, xint(x));
					gs_env->setValue(_y, xint(y));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_DWELLSTART_ID].methodId, pos, _x, _y);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(_x);
					gs_env->dereferenceObject(_y);
				}
			}
		}
	}

	void SCN_FOCUSIN() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_FOCUSIN_ID].methodId);
				}
			}
		}
	}

	void SCN_FOCUSOUT() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_FOCUSOUT_ID].methodId);
				}
			}
		}
	}

	void SCN_HOTSPOTCLICK(int position, int modifiers) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * mod = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(mod, xint(modifiers));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_HOTSPOTCLICK_ID].methodId, pos, mod);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(mod);
				}
			}
		}
	}

	void SCN_HOTSPOTDOUBLECLICK(int position, int modifiers) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * mod = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(mod, xint(modifiers));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_HOTSPOTDOUBLECLICK_ID].methodId, pos, mod);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(mod);
				}
			}
		}
	}

	void SCN_HOTSPOTRELEASECLICK(int position, int modifiers) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * mod = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(mod, xint(modifiers));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_HOTSPOTRELEASECLICK_ID].methodId, pos, mod);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(mod);
				}
			}
		}
	}

	void SCN_INDICATORCLICK(int position, int modifiers) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * mod = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(mod, xint(modifiers));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_INDICATORCLICK_ID].methodId, pos, mod);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(mod);
				}
			}
		}
	}

	void SCN_INDICATORRELEASE(int position, int modifiers) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * mod = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(mod, xint(modifiers));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_INDICATORRELEASE_ID].methodId, pos, mod);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(mod);
				}
			}
		}
	}

	void SCN_MACRORECORD(unsigned int msg, unsigned long wparam, void * lparam) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * _x = gs_env->createObject();
					XObject * _y = gs_env->createObject();
					gs_env->setValue(pos, xint(msg));
					gs_env->setValue(_x, xlong(wparam));
					gs_env->setValue(_y, xlong(lparam));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_MACRORECORD_ID].methodId, pos, _x, _y);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(_x);
					gs_env->dereferenceObject(_y);
				}
			}
		}
	}

	void SCN_MARGINCLICK(int position, int modifiers, int margin) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * _x = gs_env->createObject();
					XObject * _y = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(_x, xint(modifiers));
					gs_env->setValue(_y, xint(margin));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_MARGINCLICK_ID].methodId, pos, _x, _y);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(_x);
					gs_env->dereferenceObject(_y);
				}
			}
		}
	}

	void SCN_MARGINRIGHTCLICK(int position, int modifiers, int margin) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * _x = gs_env->createObject();
					XObject * _y = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(_x, xint(modifiers));
					gs_env->setValue(_y, xint(margin));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_MARGINRIGHTCLICK_ID].methodId, pos, _x, _y);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(_x);
					gs_env->dereferenceObject(_y);
				}
			}
		}
	}

	void SCN_MODIFIED(int position, int modType, const char * text, int length, int linesAdded, int line, int foldLevelNow, int foldLevelPrev, int token, int annotationLinesAdded) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * mod = gs_env->createObject();
					XObject * txt = gs_env->createObject();
					XObject * len = gs_env->createObject();

					XObject * lsa = gs_env->createObject();
					XObject * lin = gs_env->createObject();
					XObject * fln = gs_env->createObject();

					XObject * flp = gs_env->createObject();
					XObject * tok = gs_env->createObject();
					XObject * ala = gs_env->createObject();

					gs_env->setValue(pos, xint(position));
					gs_env->setValue(mod, xint(modType));
					if (text != 0) {
						gs_env->setValue(thread.getThread(), txt, text, strlen(text));
					}
					gs_env->setValue(len, (xint)length);

					gs_env->setValue(lsa, xint(linesAdded));
					gs_env->setValue(lin, xint(line));
					gs_env->setValue(fln, xint(foldLevelNow));

					gs_env->setValue(flp, xint(foldLevelPrev));
					gs_env->setValue(tok, xint(token));
					gs_env->setValue(ala, xint(annotationLinesAdded));

					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_MODIFIED_ID].methodId, pos, mod, txt, len, lsa, lin, fln, flp, tok, ala);

					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(mod);
					gs_env->dereferenceObject(txt);
					gs_env->dereferenceObject(len);
					gs_env->dereferenceObject(lsa);
					gs_env->dereferenceObject(lin);
					gs_env->dereferenceObject(fln);				
					gs_env->dereferenceObject(flp);
					gs_env->dereferenceObject(tok);
					gs_env->dereferenceObject(ala);
				}
			}
		}
	}

	void SCN_MODIFYATTEMPTRO() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_MODIFYATTEMPTRO_ID].methodId);
				}
			}
		}
	}

	void SCN_NEEDSHOWN(int position, int length) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * mod = gs_env->createObject();
					gs_env->setValue(pos, xint(position));
					gs_env->setValue(mod, xint(length));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_NEEDSHOWN_ID].methodId, pos, mod);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(mod);
				}
			}
		}
	}

	void SCN_PAINTED() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_PAINTED_ID].methodId);
				}
			}
		}
	}

	void SCN_SAVEPOINTLEFT() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_SAVEPOINTLEFT_ID].methodId);
				}
			}
		}
	}

	void SCN_SAVEPOINTREACHED() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_SAVEPOINTREACHED_ID].methodId);
				}
			}
		}
	}

	void SCN_STYLENEEDED(int position) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * dir = gs_env->createObject();
					gs_env->setValue(dir, xint(position));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_STYLENEEDED_ID].methodId, dir);
					gs_env->dereferenceObject(dir);
				}
			}
		}
	}

	void SCN_UPDATEUI(int updated) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * dir = gs_env->createObject();
					gs_env->setValue(dir, xint(updated));
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_UPDATEUI_ID].methodId, dir);
					gs_env->dereferenceObject(dir);
				}
			}
		}
	}

	void SCN_USERLISTSELECTION(const char *, int, int, int) {

	}

	void SCN_USERLISTSELECTION(const char * text, int length) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * pos = gs_env->createObject();
					XObject * len = gs_env->createObject();
					if (text != 0) {
						gs_env->setValue(thread.getThread(), pos, text, strlen(text));
					}
					gs_env->setValue(len, length);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_USERLISTSELECTION_ID].methodId, pos, len);
					gs_env->dereferenceObject(pos);
					gs_env->dereferenceObject(len);
				}
			}
		}
	}

	void SCN_ZOOM() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_ZOOM_ID].methodId);
				}
			}
		}
	}
	void etextChanged(const QString & str) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					QByteArray pbtext = str.toUtf8();
					gs_env->setValue(thread.getThread(), text, pbtext.data(), pbtext.length());
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_EDITCHANGE].methodId, text);
					gs_env->dereferenceObject(text);
				}
			}
		}
	}
	void etextEdited(const QString & str) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					QByteArray pbtext = str.toUtf8();
					gs_env->setValue(thread.getThread(), text, pbtext.data(), pbtext.length());
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_EDITEDITED].methodId, text);
					gs_env->dereferenceObject(text);
				}
			}
		}
	}
	void ecursorPositionChanged(int a, int b) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					XObject * pos = gs_env->createObject();
					gs_env->setValue(text, a);
					gs_env->setValue(pos, b);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_EDITPOSCHANGE].methodId, text, pos);
					gs_env->dereferenceObject(text);
					gs_env->dereferenceObject(pos);
				}
			}
		}
	}

	void ereturnPressed() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_EDITRETURN].methodId);
				}
			}
		}
	}
	void eeditingFinished() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_EDITFINISH].methodId);
				}
			}
		}
	}
	void oncellPress(int row, int column) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {

					XThread thread;
					XObject * text = gs_env->createObject();
					XObject * pos = gs_env->createObject();
					gs_env->setValue(text, row);
					gs_env->setValue(pos, column);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLPRESS].methodId, text, pos);
					gs_env->dereferenceObject(text);
					gs_env->dereferenceObject(pos);

				}
			}
		}
	}

	void onPreviewRequested(QPrinter *printer) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					gs_env->setValue(text, (xlong)printer);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_PRINTVIEWREQUEST].methodId, text);
					gs_env->dereferenceObject(text);
				}
			}
		}
	}

	void oncellItemPress(QTableWidgetItem * item) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {

					XThread thread;
					XObject * text = gs_env->createObject();
					gs_env->setValue(text, (xlong)item);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLITEMPRESS].methodId, text);
					gs_env->dereferenceObject(text);

				}
			}
		}
	}
	void oncellClick(int row, int column) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {

					XThread thread;
					XObject * text = gs_env->createObject();
					XObject * pos = gs_env->createObject();
					gs_env->setValue(text, row);
					gs_env->setValue(pos, column);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLCLICK].methodId, text, pos);
					gs_env->dereferenceObject(text);
					gs_env->dereferenceObject(pos);

				}
			}
		}
	}
	void oncellItemClick(QTableWidgetItem * item) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					gs_env->setValue(text, (xlong)item);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLITEMCLICK].methodId, text);
					gs_env->dereferenceObject(text);
				}
			}
		}
	}
	void oncellDBClick(int row, int column) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {

					XThread thread;
					XObject * text = gs_env->createObject();
					XObject * pos = gs_env->createObject();
					gs_env->setValue(text, row);
					gs_env->setValue(pos, column);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLDBCLICK].methodId, text, pos);
					gs_env->dereferenceObject(text);
					gs_env->dereferenceObject(pos);

				}
			}
		}
	}
	void oncellItemDBClick(QTableWidgetItem * item) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					gs_env->setValue(text, (xlong)item);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLITEMDBCLICK].methodId, text);
					gs_env->dereferenceObject(text);

				}
			}
		}
	}
	void oncellEnter(int row, int column) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {

					XThread thread;
					XObject * text = gs_env->createObject();
					XObject * pos = gs_env->createObject();
					gs_env->setValue(text, row);
					gs_env->setValue(pos, column);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLENTER].methodId, text, pos);
					gs_env->dereferenceObject(text);
					gs_env->dereferenceObject(pos);

				}
			}
		}
	}
	void oncellItemEnter(QTableWidgetItem * item) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					gs_env->setValue(text, (xlong)item);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLITEMENTER].methodId, text);
					gs_env->dereferenceObject(text);
				}
			}
		}
	}
	void oncellActive(int row, int column) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {

					XThread thread;
					XObject * text = gs_env->createObject();
					XObject * pos = gs_env->createObject();
					gs_env->setValue(text, row);
					gs_env->setValue(pos, column);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLACTIVE].methodId, text, pos);
					gs_env->dereferenceObject(text);
					gs_env->dereferenceObject(pos);

				}
			}
		}
	}
	void oncellItemActive(QTableWidgetItem * item) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					gs_env->setValue(text, (xlong)item);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLITEMACTIVE].methodId, text);
					gs_env->dereferenceObject(text);
				}
			}
		}
	}
	void oncellChanged(int row, int column) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {

					XThread thread;
					XObject * text = gs_env->createObject();
					XObject * pos = gs_env->createObject();
					gs_env->setValue(text, row);
					gs_env->setValue(pos, column);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLCHANGE].methodId, text, pos);
					gs_env->dereferenceObject(text);
					gs_env->dereferenceObject(pos);

				}
			}
		}
	}
	void oncellItemChanged(QTableWidgetItem * item) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * text = gs_env->createObject();
					gs_env->setValue(text, (xlong)item);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_CELLITEMCHANGE].methodId, text);
					gs_env->dereferenceObject(text);
				}
			}
		}
	}
	void eselectionChanged() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_EDITSELCHANGE].methodId);
				}
			}
		}
	}

	void onValueChanged(QtProperty *property, int val) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * prop = gs_env->createObject();

					XObject * text = gs_env->createObject();
					gs_env->setValue(prop, (xlong)property);
					gs_env->setValue(text, (xint)val);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_ENUMCHANGED].methodId, prop, text);
					gs_env->dereferenceObject(text);
					gs_env->dereferenceObject(prop);
				}
			}
		}
	}

	void onValueChanged(QtProperty *property, const QVariant &val) {

		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;

					XObject * value = gs_env->createObject();
					XObject * prop = gs_env->createObject();
					XObject * text = gs_env->createObject();
					QString str = val.toString();
					QByteArray _data = str.toUtf8();

					gs_env->setValue(thread.getThread(), value, _data.data(), _data.length());
					gs_env->setValue(prop, (xlong)property);
					gs_env->setValue(text, (xint)val.type());

					val.toString();
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_VVALUECHANGE].methodId, prop, text, value);

					gs_env->dereferenceObject(text);
					gs_env->dereferenceObject(prop);
					gs_env->dereferenceObject(value);
				}
			}
		}
	}

	void onAttributeChanged(QtProperty *property,const QString &attribute, const QVariant &val) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XObjectData * objectData = (XObjectData *)obj->userData(Qt::UserRole);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;

					
					XObject * prop = gs_env->createObject();
					XObject * text = gs_env->createObject();

					XObject * value = gs_env->createObject();
					QString str = val.toString();
					QByteArray _data = str.toUtf8();
					gs_env->setValue(thread.getThread(), value, _data.data(), _data.length());

					XObject * attr = gs_env->createObject();
					_data = attribute.toUtf8();
					gs_env->setValue(thread.getThread(), attr, _data.data(), _data.length());

					gs_env->setValue(prop, (xlong)property);
					gs_env->setValue(text, (xint)val.type());

					val.toString();
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_VATTRCHANGE].methodId, prop, attr, text, value);

					gs_env->dereferenceObject(text);
					gs_env->dereferenceObject(prop);
					gs_env->dereferenceObject(value);
					gs_env->dereferenceObject(attr);
				}
			}
		}
	}

private:
	QSignalMapper *signalMapper;
	bool setup;

public:
	static QMetaObject::Connection XLINK(const QObject *sender, const char *signal,
		const QObject *receiver, const char *member, Qt::ConnectionType t = Qt::AutoConnection) {
		disconnect(sender, signal, receiver, member);
		return connect(sender, signal, receiver, member, t);
	}

	void installAction(QObject * act) {

		XLINK(act, SIGNAL(triggered()), signalMapper, SLOT(map()));
		signalMapper->setMapping(act, act);

		if (setup == false) {
			XLINK(signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(ActionTriggered(QObject*)));
			setup = true;
		}
	}

	void installTreeAction(QObject * act) {
		XLINK(act, SIGNAL(itemPressed(QTreeWidgetItem*, int)), this, SLOT(tritemPressed(QTreeWidgetItem*, int)));
		XLINK(act, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(tritemClicked(QTreeWidgetItem*, int)));
		XLINK(act, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(tritemDoubleClicked(QTreeWidgetItem*, int)));
		XLINK(act, SIGNAL(itemActivated(QTreeWidgetItem*, int)), this, SLOT(tritemActivated(QTreeWidgetItem*, int)));
		XLINK(act, SIGNAL(itemEntered(QTreeWidgetItem*, int)), this, SLOT(tritemEntered(QTreeWidgetItem*, int)));
		XLINK(act, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(tritemChanged(QTreeWidgetItem*, int)));
		XLINK(act, SIGNAL(itemExpanded(QTreeWidgetItem*)), this, SLOT(tritemExpanded(QTreeWidgetItem*)));
		XLINK(act, SIGNAL(itemCollapsed(QTreeWidgetItem*)), this, SLOT(tritemCollapsed(QTreeWidgetItem*)));
		XLINK(act, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)), this, SLOT(trcurrentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)));
		XLINK(act, SIGNAL(itemSelectionChanged()), this, SLOT(tritemSelectionChanged()));
	}

	void installButtonAction(QObject * btn) {
		XLINK(btn, SIGNAL(clicked(bool)), this, SLOT(btnclicked(bool)));
		XLINK(btn, SIGNAL(toggled(bool)), this, SLOT(btntoggled(bool)));
		XLINK(btn, SIGNAL(pressed()), this, SLOT(btnpressed()));
		XLINK(btn, SIGNAL(released()), this, SLOT(btnreleased()));
	}

	void installEditAction(QObject * edit) {
		XLINK(edit, SIGNAL(textChanged(const QString &)), this, SLOT(etextChanged(const QString &)));
		XLINK(edit, SIGNAL(textEdited(const QString &)), this, SLOT(etextEdited(const QString &)));
		XLINK(edit, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(ecursorPositionChanged(int, int)));
		XLINK(edit, SIGNAL(returnPressed()), this, SLOT(ereturnPressed()));
		XLINK(edit, SIGNAL(editingFinished()), this, SLOT(eeditingFinished()));
		XLINK(edit, SIGNAL(selectionChanged()), this, SLOT(eselectionChanged()));
	}

	void installTableCellChange(QTableWidget * t) {
		XLINK(t, SIGNAL(cellChanged(int, int)), this, SLOT(oncellChanged(int,int)));
		XLINK(t, SIGNAL(itemChanged(QTableWidgetItem *)), this, SLOT(oncellItemChanged(QTableWidgetItem *)));

		XLINK(t, SIGNAL(cellEntered(int, int)), this, SLOT(oncellEnter(int, int)));
		XLINK(t, SIGNAL(itemEntered(QTableWidgetItem *)), this, SLOT(oncellItemEnter(QTableWidgetItem *)));

		XLINK(t, SIGNAL(cellActivated(int, int)), this, SLOT(oncellActive(int, int)));
		XLINK(t, SIGNAL(itemActivated(QTableWidgetItem *)), this, SLOT(oncellItemActive(QTableWidgetItem *)));

		XLINK(t, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(oncellDBClick(int, int)));
		XLINK(t, SIGNAL(itemDoubleClicked(QTableWidgetItem *)), this, SLOT(oncellItemDBClick(QTableWidgetItem *)));

		XLINK(t, SIGNAL(cellClicked(int, int)), this, SLOT(oncellClick(int, int)));
		XLINK(t, SIGNAL(itemClicked(QTableWidgetItem *)), this, SLOT(oncellItemClick(QTableWidgetItem *)));

		XLINK(t, SIGNAL(cellPressed(int, int)), this, SLOT(oncellPress(int, int)));
		XLINK(t, SIGNAL(itemPressed(QTableWidgetItem *)), this, SLOT(oncellItemPress(QTableWidgetItem *)));
	}

	void installDialogAction(QDialog * dlg) {
		XLINK(dlg, SIGNAL(finished(int)), this, SLOT(onFinish(int)));
		XLINK(dlg, SIGNAL(accepted()), this, SLOT(onAccept()));
		XLINK(dlg, SIGNAL(rejected()), this, SLOT(onReject()));
	}

	void installPrintViewDialogAction(QPrintPreviewDialog * dlg) {
		XLINK(dlg, SIGNAL(paintRequested(QPrinter *)), this, SLOT(onPreviewRequested(QPrinter *)));
	}

	void installComboBoxAction(QComboBox * cmb) {
		XLINK(cmb, SIGNAL(currentIndexChanged(int)), this, SLOT(onCurrentIndexChanged(int)));
		XLINK(cmb, SIGNAL(editTextChanged(const QString &)), this, SLOT(onEditTextChanged(const QString &)));
		XLINK(cmb, SIGNAL(activated(int)), this, SLOT(onActivated(int)));
	}


	void installColorPropertyChange(QtColorPropertyManager * p) {

	}

	void installBoolPropertyChange(QtBoolPropertyManager * p) {

	}

	void installDatePropertyChange(QtDatePropertyManager * p) {

	}

	void installDateTimePropertyChange(QtDateTimePropertyManager * p) {

	}

	void installDoublePropertyChange(QtDoublePropertyManager*qobject) {

	}

	void installEnumPropertyChange(QtEnumPropertyManager*qobject) {
		XLINK(qobject, SIGNAL(valueChanged(QtProperty *, int )), this, SLOT(onValueChanged(QtProperty *, int)));
	}

	void installFlagPropertyChange(QtFlagPropertyManager*qobject) {

	}

	void installFontPropertyChange(QtFontPropertyManager*qobject) {

	}

	void installGroupPropertyChange(QtGroupPropertyManager*qobject) {

	}

	void installIntPropertyChange(QtIntPropertyManager*qobject) {

	}

	void installPointPropertyChange(QtPointPropertyManager*qobject) {

	}

	void installRectPropertyChange(QtRectPropertyManager*qobject) {

	}

	void installSizePropertyChange(QtSizePropertyManager*qobject) {

	}

	void installSizePolicyPropertyChange(QtSizePolicyPropertyManager*qobject) {

	}

	void installStringPropertyChange(QtStringPropertyManager*qobject) {

	}

	void installTimePropertyChange(QtTimePropertyManager*qobject) {

	}

	void installVariantPropertyChange(QtVariantPropertyManager*qobject) {
		XLINK(qobject, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(onValueChanged(QtProperty *, const QVariant &)));
		XLINK(qobject, SIGNAL(attributeChanged(QtProperty *,const QString &, const QVariant &)), this, SLOT(onAttributeChanged(QtProperty *,const QString &, const QVariant &)));
	}

	void installFSWEvent(QFileSystemWatcher * fsw) {
		XLINK(fsw, SIGNAL(fileChanged(QString )), this, SLOT(onfswFileChanged(QString )));
		XLINK(fsw, SIGNAL(directoryChanged(QString )), this, SLOT(onfswDirectoryChanged(QString )));
	}

	void installSciAction(QsciScintilla * sci) {
		XLINK(sci, SIGNAL(QSCN_SELCHANGED(bool)), this, SLOT(QSCN_SELCHANGED(bool))); 
		XLINK(sci, SIGNAL(SCN_AUTOCCANCELLED()), this, SLOT(SCN_AUTOCCANCELLED()));
		XLINK(sci, SIGNAL(SCN_AUTOCCHARDELETED()), this, SLOT(SCN_AUTOCCHARDELETED()));
		XLINK(sci, SIGNAL(SCN_AUTOCCOMPLETED(const char *, int , int , int )), this, SLOT(SCN_AUTOCCOMPLETED(const char *, int, int, int)));
		XLINK(sci, SIGNAL(SCN_AUTOCSELECTION(const char *, int , int , int )), this, SLOT(SCN_AUTOCSELECTION(const char *, int, int, int)));
		XLINK(sci, SIGNAL(SCN_AUTOCSELECTION(const char *, int )), this, SLOT(SCN_AUTOCSELECTION(const char *, int)));
		XLINK(sci, SIGNAL(SCEN_CHANGE()), this, SLOT(SCEN_CHANGE()));
		XLINK(sci, SIGNAL(SCN_CALLTIPCLICK(int)), this, SLOT(SCN_CALLTIPCLICK(int)));
		XLINK(sci, SIGNAL(SCN_CHARADDED(int)), this, SLOT(SCN_CHARADDED(int)));
		XLINK(sci, SIGNAL(SCN_DOUBLECLICK(int , int , int )), this, SLOT(SCN_DOUBLECLICK(int, int, int)));
		XLINK(sci, SIGNAL(SCN_DWELLEND(int, int, int)), this, SLOT(SCN_DWELLEND(int, int, int)));
		XLINK(sci, SIGNAL(SCN_DWELLSTART(int, int, int)), this, SLOT(SCN_DWELLSTART(int, int, int)));
		XLINK(sci, SIGNAL(SCN_FOCUSIN()), this, SLOT(SCN_FOCUSIN()));
		XLINK(sci, SIGNAL(SCN_FOCUSOUT()), this, SLOT(SCN_FOCUSOUT()));
		XLINK(sci, SIGNAL(SCN_HOTSPOTCLICK(int, int)), this, SLOT(SCN_HOTSPOTCLICK(int, int)));
		XLINK(sci, SIGNAL(SCN_HOTSPOTDOUBLECLICK(int, int)), this, SLOT(SCN_HOTSPOTDOUBLECLICK(int, int)));
		XLINK(sci, SIGNAL(SCN_HOTSPOTRELEASECLICK(int , int )), this, SLOT(SCN_HOTSPOTRELEASECLICK(int, int)));
		XLINK(sci, SIGNAL(SCN_INDICATORCLICK(int , int )), this, SLOT(SCN_INDICATORCLICK(int, int)));
		XLINK(sci, SIGNAL(SCN_INDICATORRELEASE(int , int )), this, SLOT(SCN_INDICATORRELEASE(int, int)));
		XLINK(sci, SIGNAL(SCN_MACRORECORD(unsigned int, unsigned long, void *)), this, SLOT(SCN_MACRORECORD(unsigned int, unsigned long, void *)));
		XLINK(sci, SIGNAL(SCN_MARGINCLICK(int , int , int )), this, SLOT(SCN_MARGINCLICK(int, int, int)));
		XLINK(sci, SIGNAL(SCN_MARGINRIGHTCLICK(int , int , int )), this, SLOT(SCN_MARGINRIGHTCLICK(int, int, int)));
		XLINK(sci, SIGNAL(SCN_MODIFIED(int, int, const char *, int, int, int, int, int, int, int)), this, SLOT(SCN_MODIFIED(int, int, const char *, int, int, int, int, int, int, int)));
		XLINK(sci, SIGNAL(SCN_MODIFYATTEMPTRO()), this, SLOT(SCN_MODIFYATTEMPTRO()));
		XLINK(sci, SIGNAL(SCN_NEEDSHOWN(int, int)), this, SLOT(SCN_NEEDSHOWN(int, int)));
		XLINK(sci, SIGNAL(SCN_PAINTED()), this, SLOT(SCN_PAINTED()));
		XLINK(sci, SIGNAL(SCN_SAVEPOINTLEFT()), this, SLOT(SCN_SAVEPOINTLEFT()));
		XLINK(sci, SIGNAL(SCN_SAVEPOINTREACHED()), this, SLOT(SCN_SAVEPOINTREACHED()));
		XLINK(sci, SIGNAL(SCN_STYLENEEDED(int)), this, SLOT(SCN_STYLENEEDED(int)));
		XLINK(sci, SIGNAL(SCN_UPDATEUI(int)), this, SLOT(SCN_UPDATEUI(int)));		//!
		XLINK(sci, SIGNAL(SCN_USERLISTSELECTION(const char *, int, int, int)), this, SLOT(SCN_USERLISTSELECTION(const char *, int, int, int)));
		XLINK(sci, SIGNAL(SCN_USERLISTSELECTION(const char *, int)), this, SLOT(SCN_USERLISTSELECTION(const char *, int)));
		XLINK(sci, SIGNAL(SCN_ZOOM()), this, SLOT(SCN_ZOOM()));
	}
};
