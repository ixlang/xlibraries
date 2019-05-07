#include "qxlibrary_global.h"
#include "QXApplication.h"

#include<QtPlugin>  // for release

Q_IMPORT_PLUGIN(QGifPlugin) //for releas
Q_IMPORT_PLUGIN(QICNSPlugin) //for releas
Q_IMPORT_PLUGIN(QICOPlugin) //for releas
Q_IMPORT_PLUGIN(QJpegPlugin) //for releas

Q_IMPORT_PLUGIN(QTgaPlugin) //for releas
Q_IMPORT_PLUGIN(QTiffPlugin) //for releas
Q_IMPORT_PLUGIN(QWbmpPlugin) //for releas
Q_IMPORT_PLUGIN(QWebpPlugin) //for releas

#ifdef WIN32
#include <conio.h>
#include <codecvt>
#endif
#include <stdio.h>
#include <locale>

#include <assert.h>
#ifdef WIN32
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
#elif defined(__linux__)
#ifdef __arm__
#include <QtPlugin>
Q_IMPORT_PLUGIN(QLinuxFbIntegrationPlugin)
#else
#include <QtPlugin>
Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
#endif
#elif defined(__APPLE__)
#include <QtPlugin>
Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif
XNLEnv * gs_env = 0;
XObject * _application = 0;
QXApplication * _xapplication = 0;


extern int onNotifyId;
extern XMethod * onNotify;
extern XMethod * createObject;

extern ActionReceiver ar;

int MAX_METHOD = 0;
XIDENT * methodIdent = NULL;


size_t getEventMaxCount();
size_t getEventSize();
extern megInfo megs[];
XObject * getObjectControl(QObject * obj);
extern std::map<int, const char*> msgMap;
static int global_argc = 0;
XContext * ui_thread = 0;
bool ui_release = false;
Qt::HANDLE ui_thread_id = 0;

QMap<QString, QIcon*> iconMap;

void CleanupQImage(void* p) {
	delete[](unsigned char *)p;
}


XObject * data2String(QByteArray & data) {
	XObject * strobj = gs_env->createObject();
	XThread thread;
	gs_env->setValue(thread.getThread(), strobj, data.data(), data.size());
	return strobj;
}

void extartStringArray(XObject * value, QStringList & enumNames) {
	xlong size = gs_env->getLengthOfArray(value);
	const char ** text = new const char *[size];
	size_t * length = new size_t[size];

	if (gs_env->getElementValue(value, 0, text, length, size)) {
		for (xlong i = 0; i < size; i++) {
			enumNames.push_back(QString::fromUtf8(text[i], length[i]));
		}
	}
	delete[] text;
	delete[] length;
}

void extartByteArray(XObject * value, QByteArray & data) {
	xlong size = gs_env->getLengthOfArray(value);
	data.resize(size);
    gs_env->getElementValue(value, 0, (xbyte*)data.data(), size);
}

QIcon * loadIcon(QString file) {
    QMap<QString, QIcon*>::iterator iter = iconMap.find(file);
    if (iter == iconMap.cend()) {
            QIcon * icon = new QIcon(file);
            iconMap.insert(file, icon);
            return icon;
    }
    return *iter;
}




XNLEXPORT xlong  XI_CDECL createQxApplication(XObject * x){

        _application = gs_env->referenceObject(x);

        int onNotifyId = gs_env->getMethodId("/bool@/QXApplication/onNotify(/QXObject,/String,/String,/long,/int)");
        onNotify = gs_env->getVirtualMethod(x, onNotifyId);

        onNotifyId = gs_env->getMethodId("/*@/QXApplication/onCreateXObject(/long,/String)");
        createObject = gs_env->getVirtualMethod(x, onNotifyId);

        MAX_METHOD = getEventMaxCount();
        methodIdent = new XIDENT[MAX_METHOD];

        memset(methodIdent, 0, sizeof(XIDENT) * MAX_METHOD);
        for (size_t i = 0; i < getEventSize(); i++) {
                XIDENT * pme = &methodIdent[megs[i].id];
                pme->path = methods[i].path;
                if (pme->path != NULL) {
                        pme->methodId = gs_env->getMethodId(pme->path);
                        assert(pme->methodId != -1);
                }
        }
		ui_thread = gs_env->getContext(&ui_release);
		ui_thread_id = QThread::currentThreadId();
        _xapplication = new QXApplication(global_argc, 0);
		//uithreadid = GetCurrentThreadId();
        //qapp->installEventFilter(new QFilter());
		//qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();
        return (xlong)_xapplication;
}

XNLEXPORT xlong  XI_CDECL locaUiFile(xstring path, XObject * x, xlong parent){
        QString uifilePath = QString::fromUtf8(path);

        QUiLoader uiLoader;
        QFile file(uifilePath);
        file.open(QIODevice::ReadOnly);

        QWidget* getWidget = 0;
		
        if (parent != 0) {
                getWidget = uiLoader.load(&file, (QWidget*)parent);
        }else {
                getWidget = uiLoader.load(&file);
        }

        if (getWidget != NULL) {

                XObjectData * objectData = new XObjectData();
                objectData->setObject(x);
                getWidget->setUserData(Qt::UserRole, objectData);
                getWidget->setAttribute(Qt::WA_DeleteOnClose);

                if (strcmp(getWidget->metaObject()->className(), "QDialog") == 0) {
                        ar.installDialogAction((QDialog*)getWidget);
                }
        }
        //QAction * at = getWidget->findChild<QAction*>(QString::fromUtf8("actionclean"));
        //const char * type = getWidget->metaObject()->className();
        file.close();
        //a.instance()->setEventDispatcher(NULL);
        return (xlong)getWidget;
}

XNLEXPORT xlong  XI_CDECL locaUiData(xlong buffer, XObject * x, xlong parent) {

        QUiLoader uiLoader;

        QBuffer * device = (QBuffer *)buffer;

        QWidget* getWidget = 0;
        if (parent != 0) {
                getWidget = uiLoader.load(device, (QWidget*)parent);
        }
        else {
                getWidget = uiLoader.load(device);
        }

        if (getWidget != NULL) {

                XObjectData * objectData = new XObjectData();
                objectData->setObject(x);
                getWidget->setUserData(Qt::UserRole, objectData);
                getWidget->setAttribute(Qt::WA_DeleteOnClose);

                if (strcmp(getWidget->metaObject()->className(), "QDialog") == 0) {
                        ar.installDialogAction((QDialog*)getWidget);
                }
        }
        //QAction * at = getWidget->findChild<QAction*>(QString::fromUtf8("actionclean"));
        //const char * type = getWidget->metaObject()->className();
        //a.instance()->setEventDispatcher(NULL);
        return (xlong)getWidget;
}

XNLEXPORT xlong  XI_CDECL createNObject(xint type, xlong param) {
        switch (type)
        {
        case qtFont:
                return (xlong)new QFont();
                break;
        case qtMatrix:
                return (xlong)new QMatrix();
                break;
        case qtBuffer:
                return (xlong)new QBuffer();
                break;
		case qtPath:
				return (xlong) new QPainterPath();
			break;
		case qtBrush:
			if (param != 0) {
				return (xlong)new QBrush(*(QGradient*)param);
			}else {
				return (xlong)new QBrush();
			}
			break;
		case qtImgBrush:
			if (param != 0) {
				return (xlong)new QBrush(*(QImage*)param);
			}
			else {
				return (xlong)new QBrush();
			}
			break;
        case qtIcon:
        {
                QPixmap pixmap;
                pixmap.loadFromData(*(QByteArray*)param);
                return (xlong)new QIcon(pixmap);
        }
                break;

        default:
                break;
        }
        return 0;
}

XNLEXPORT xlong  XI_CDECL createSObject(xint type, xstring param) {
        switch (type)
        {
        case qtFont:
                return (xlong)new QFont(QString::fromUtf8(param));
                break;
        case qtIcon:
        {
                return (xlong)new QIcon(QString::fromUtf8(param));
        }
		break;
        default:
                break;
        }
        return 0;
}

XNLEXPORT xlong  XI_CDECL createPObject(xint type, xptr param) {
	switch (type)
	{
	case qtLineGradient:
	{
		double * fp = (double*)param;
		return (xlong)new QLinearGradient(fp[0], fp[1], fp[2], fp[3]);
	}
		break;
	case qtRadialGradient3:
	{
		double * fp = (double*)param;
		return (xlong)new QRadialGradient(fp[0], fp[1], fp[2]);
	}
		break;

	case qtRadialGradient5:
	{
		double * fp = (double*)param;
		return (xlong)new QRadialGradient(fp[0], fp[1], fp[2], fp[3], fp[4]);
	}
	break;

	case qtRadialGradient6:
	{
		double * fp = (double*)param;
		return (xlong)new QRadialGradient(fp[0], fp[1], fp[2], fp[3], fp[4], fp[5]);
	}
	break;

	case qtConicalGradient:
	{
		double * fp = (double*)param;
		return (xlong)new QConicalGradient(fp[0], fp[1], fp[2]);
	}
		break;
	default:
		break;
	}
	return 0;
}



/*class XCustomModel 
	:public QAbstractItemModel {
	
public:

	XCustomModel(QObject * parent) 
	:QAbstractItemModel(parent){

	}

	XCustomModel(){

	}

	Q_INVOKABLE virtual QModelIndex index(int row, int column,
		const QModelIndex &parent = QModelIndex()) const {
		QStandardItemModel;
	}

	Q_INVOKABLE virtual QModelIndex parent(const QModelIndex &child) const {

	}

	Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const {

	}

	Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex()) const {

	}

	Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const {

	}
};*/

XNLEXPORT xlong  XI_CDECL createQObject(xint type, XObject * x, xlong parent) {

        QObject * qobject = 0;
        switch (type)
        {
        case None:

                break;
        case qtWidget:
        {
                QWidget * qw = 0;
                if (parent != 0) {
                        qw = new QWidget((QWidget*)parent);
                }
                else {
                        qw = new QWidget();
                }
                qw->setAttribute(Qt::WA_DeleteOnClose, true);
                qobject = qw;

        }
                break;
		case qtFileWatch:
		{
			QFileSystemWatcher * fsw = new QFileSystemWatcher((QWidget*)parent);
			ar.installFSWEvent(fsw);
			qobject = fsw;
		}
		break;

        case qtMainWindow:
        {
                QWidget * qw = 0;

                if (parent != 0) {
                        qw = new QMainWindow((QWidget*)parent);
                }
                else {
                        qw = new QMainWindow();
                }

                qw->setAttribute(Qt::WA_DeleteOnClose, true);
                qobject = qw;
        }
                break;
        case qtSci:
                if (parent != 0) {
                        qobject = new QsciScintilla((QWidget*)parent);
                }else {
                        qobject = new QsciScintilla();
                }
                ar.installSciAction((QsciScintilla*)qobject);
                ((QsciScintilla*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
                break;
        case qtPushButton:
                if (parent != 0) {
                        qobject = new QPushButton((QWidget*)parent);
                }
                else {
                        qobject = new QPushButton();
                }
                ar.installButtonAction(qobject);
                break;
        case qtLineEdit:
                if (parent != 0) {
                        qobject = new QLineEdit((QWidget*)parent);
                }
                else {
                        qobject = new QLineEdit();
                }
                ar.installEditAction(qobject);
                break;
        case qtMenuBar:
                if (parent != 0) {
                        qobject = new QMenuBar((QWidget*)parent);
                }
                else {
                        qobject = new QMenuBar();
                }
                break;
        case qtMenu:
                if (parent != 0) {
                        qobject = new QMenu((QWidget*)parent);
                }
                else {
                        qobject = new QMenu();
                }
                break;
        case qtAction:
                if (parent != 0) {
                        qobject = new QAction((QWidget*)parent);
                }
                else {
                        qobject = new QAction();
                }
                break;
        case qtMdiSubWnd:
                qobject = new QMdiSubWindow();
                ((QMdiArea*)parent)->addSubWindow((QMdiSubWindow*)qobject);
                ((QMdiSubWindow*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
                break;
        case qtTreeView:
                if (parent != 0) {
                        qobject = new QTreeWidget((QWidget*)parent);
                }
                else {
                        qobject = new QTreeWidget();
                }
                ar.installTreeAction(qobject);
                ((QTreeWidget*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
                break;
        case qtListView:
                if (parent != 0) {
                        qobject = new QListView((QWidget*)parent);
                }
                else {
                        qobject = new QListView();
                }
                ((QListView*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
                break;
		case qtTableWidget:
			if (parent != 0) {
				qobject = new QTableWidget((QWidget*)parent);
			}
			else {
				qobject = new QTableWidget();
			}
			ar.installTableCellChange((QTableWidget*)qobject);
			((QTableWidget*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
			break;
		/*case qtStdModel:
			if (parent != 0) {
				qobject = new QStandardItemModel((QWidget*)parent);
			}
			else {
				qobject = new QStandardItemModel();
			}
			break;

		case qtDataModel:
			if (parent != 0) {
				qobject = new XCustomModel((QWidget*)parent);
			}
			else {
				qobject = new XCustomModel();
			}
			break;
			*/
        case qtDialog:
            if (parent != 0) {
               qobject = new QDialog((QWidget*)parent);
            }else{
               qobject = new QDialog();
            }
            ar.installDialogAction((QDialog*)qobject);
            ((QDialog*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
            break;
        case qtComboBox:
            if (parent != 0) {
               qobject = new QComboBox((QWidget*)parent);
            }else{
               qobject = new QComboBox();
            }
			ar.installComboBoxAction((QComboBox*)qobject);
            break;
        case qtPropertyBrowser :// 15
            if (parent != 0) {
               qobject = new QtTreePropertyBrowser((QWidget*)parent);
            }else{
               qobject = new QtTreePropertyBrowser();
            }
            ((QtTreePropertyBrowser*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
            break;
        case qtBoolPropertyManager :// 16,
            if (parent != 0) {
               qobject = new QtBoolPropertyManager((QObject*)parent);
            }else{
               qobject = new QtBoolPropertyManager();
            }
			ar.installBoolPropertyChange((QtBoolPropertyManager*)qobject);
            break;
        case qtColorPropertyManager :// 17,
            if (parent != 0) {
               qobject = new QtColorPropertyManager((QObject*)parent);
            }else{
               qobject = new QtColorPropertyManager();
            }
			ar.installColorPropertyChange((QtColorPropertyManager*)qobject);
            break;
        case qtDatePropertyManager :// 18,
            if (parent != 0) {
               qobject = new QtDatePropertyManager((QObject*)parent);
            }else{
               qobject = new QtDatePropertyManager();
            }
			ar.installDatePropertyChange((QtDatePropertyManager*)qobject);
            break;
        case qtDateTimePropertyManager :// 19,
            if (parent != 0) {
               qobject = new QtDateTimePropertyManager((QObject*)parent);
            }else{
               qobject = new QtDateTimePropertyManager();
            }
			ar.installDateTimePropertyChange((QtDateTimePropertyManager*)qobject);
            break;
        case qtDoublePropertyManager :// 20,
            if (parent != 0) {
               qobject = new QtDoublePropertyManager((QObject*)parent);
            }else {
               qobject = new QtDoublePropertyManager();
            }
			ar.installDoublePropertyChange((QtDoublePropertyManager*)qobject);
            break;
        case qtEnumPropertyManager :// 21,
            if (parent != 0) {
               qobject = new QtEnumPropertyManager((QObject*)parent);
            }else{
               qobject = new QtEnumPropertyManager();
            }
			ar.installEnumPropertyChange((QtEnumPropertyManager*)qobject);
            break;
        case qtFlagPropertyManager :// 22,
            if (parent != 0) {
               qobject = new QtFlagPropertyManager((QObject*)parent);
            } else {
               qobject = new QtFlagPropertyManager();
            }
			ar.installFlagPropertyChange((QtFlagPropertyManager*)qobject);
            break;
        case qtFontPropertyManager :// 23,
            if (parent != 0) {
               qobject = new QtFontPropertyManager((QObject*)parent);
            }else {
               qobject = new QtFontPropertyManager();
            }
			ar.installFontPropertyChange((QtFontPropertyManager*)qobject);
            break;
        case qtGroupPropertyManager :// 24,
            if (parent != 0) {
               qobject = new QtGroupPropertyManager((QObject*)parent);
            }else {
               qobject = new QtGroupPropertyManager();
            }
			ar.installGroupPropertyChange((QtGroupPropertyManager*)qobject);
            break;
        case qtIntPropertyManager :// 25,
            if (parent != 0) {
               qobject = new QtIntPropertyManager((QObject*)parent);
            }else {
               qobject = new QtIntPropertyManager();
            }
			ar.installIntPropertyChange((QtIntPropertyManager*)qobject);
            break;
        case qtPointPropertyManager :// 26,
            if (parent != 0) {
               qobject = new QtPointPropertyManager((QObject*)parent);
            }else {
               qobject = new QtPointPropertyManager();
            }
			ar.installPointPropertyChange((QtPointPropertyManager*)qobject);
            break;
        case qtRectPropertyManager :// 27,
            if (parent != 0) {
               qobject = new QtRectPropertyManager((QObject*)parent);
            }else {
               qobject = new QtRectPropertyManager();
            }
			ar.installRectPropertyChange((QtRectPropertyManager*)qobject);
            break;
        case qtSizePropertyManager :// 28,
            if (parent != 0) {
               qobject = new QtSizePropertyManager((QObject*)parent);
            }else {
               qobject = new QtSizePropertyManager();
            }
			ar.installSizePropertyChange((QtSizePropertyManager*)qobject);
            break;
        case qtSizePolicyPropertyManager :// 29,
            if (parent != 0) {
               qobject = new QtSizePolicyPropertyManager((QObject*)parent);
            }else {
               qobject = new QtSizePolicyPropertyManager();
            }
			ar.installSizePolicyPropertyChange((QtSizePolicyPropertyManager*)qobject);
            break;
        case qtStringPropertyManager :// 30,
            if (parent != 0) {
               qobject = new QtStringPropertyManager((QObject*)parent);
            }else {
               qobject = new QtStringPropertyManager();
            }
			ar.installStringPropertyChange((QtStringPropertyManager*)qobject);
            break;
        case qtTimePropertyManager :// 31,
            if (parent != 0) {
               qobject = new QtTimePropertyManager((QObject*)parent);
            }else {
               qobject = new QtTimePropertyManager();
            }
			ar.installTimePropertyChange((QtTimePropertyManager*)qobject);
            break;
        case qtVariantPropertyManager :// 32,
            if (parent != 0) {
               qobject = new QtVariantPropertyManager((QObject*)parent);
            }else {
               qobject = new QtVariantPropertyManager();
            }
			ar.installVariantPropertyChange((QtVariantPropertyManager*)qobject);
            break;
        case qtProperty :// 33,
                break;
        case qtVariantProperty :// 34;
                break;
		case qtToolbar:
			if (parent != 0) {
				qobject = new QToolBar((QWidget*)parent);
			}else {
				qobject = new QToolBar();
			}
			break;
        case qtCheckBox:
            if (parent != 0) {
               qobject = new QCheckBox((QWidget*)parent);
            }else {
               qobject = new QCheckBox();
            }
            ar.installButtonAction(qobject);
            break;
        case qtLabel:// 34;
            if (parent != 0) {
                    qobject = new QLabel((QWidget*)parent);
            }
            else {
                    qobject = new QLabel();
            }
            break;
        case qtStatusBar:
            if (parent != 0) {
                    qobject = new QStatusBar((QWidget*)parent);
            }
            else {
                    qobject = new QStatusBar();
            }
            break;
        case qtProgressBar:
            if (parent != 0) {
                    qobject = new QProgressBar((QWidget*)parent);
            }
            else {

                    qobject = new QProgressBar();
            }
            break;
        case qtVariantEditorFactory:
            if (parent != 0) {
                    qobject = new QtVariantEditorFactory((QObject*)parent);
            }else {
                    qobject = new QtVariantEditorFactory();
            }
            break;
        default:
            break;
        }

        if (qobject != NULL) {
            XObjectData * objectData = new XObjectData();
            objectData->setObject(x);
            qobject->setUserData(Qt::UserRole, objectData);
        }

        return (xlong)qobject;
}

XNLEXPORT void XI_CDECL ShowUi(xlong widget){
        QWidget* getWidget = (QWidget*)widget;
        getWidget->show();
}


XNLEXPORT void XI_CDECL ApplicationRun(xlong app) {
        QXApplication * exe = (QXApplication*)app;
        exe->exec();
}


XNLEXPORT xint  XI_STDCALL XNLMain(XNLEnv * env, xint version){
        gs_env = env->getEnv();
        return 0;
}


XNLEXPORT xint  XI_STDCALL XNLExit(XNLEnv * env){
        if (gs_env != 0) {
			if (ui_release) {
				gs_env->releaseContext(ui_thread);
			}
                if (_application != 0) {
                        gs_env->dereferenceObject(_application);
                        _application = 0;
                }
                //env->releaseEnv(gs_env);
        }
        //_CrtDumpMemoryLeaks();
        return 0;
}


XNLEXPORT void XI_CDECL widget_set_vint_value(xlong h, xint proid, xint value) {
        switch (proid)
        {
        case SETFOCUSPOLICY:
                ((QWidget*)h)->setFocusPolicy((Qt::FocusPolicy)value);
            break;
		case SETCURSOR:
				((QWidget*)h)->setCursor((Qt::CursorShape)value);
			break;
        case FIXEDHEIGHT:
                ((QWidget*)h)->setFixedHeight(value);
                break;
        case FIXEDWIDTH:
                ((QWidget*)h)->setFixedWidth(value);
                break;
        case DOCKWIDGETFEATURE:
                ((QDockWidget*)h)->setFeatures((QDockWidget::DockWidgetFeatures)value);
                break;
        case FONTPTSIZE:
                ((QFont*)h)->setPointSize(value);
                break;
		case PAINTFONTPTSIZE:
		{
			QFont copyfont(((QPainter*)h)->font());
			copyfont.setPointSize(value);
			((QPainter*)h)->setFont(copyfont);
		}
			break;
		case SETSHRCUT:
			((QAction*)h)->setShortcut((QKeySequence::StandardKey)value);
			break;
        case FONTPXSIZE:
            ((QFont*)h)->setPixelSize(value);
            break;
		case PAINTFONTPXSIZE:
		{			
			QFont copyfont(((QPainter*)h)->font());
			copyfont.setPixelSize(value);
			((QPainter*)h)->setFont(copyfont);
		}
			break;
        case MDIMODE:
                ((QMdiArea*)h)->setViewMode((QMdiArea::ViewMode)value);
                break;
        case MDISETSCROLLH:
                ((QMdiArea*)h)->setHorizontalScrollBarPolicy((Qt::ScrollBarPolicy)value);
                break;
        case MDISETSCROLLV:
                ((QMdiArea*)h)->setVerticalScrollBarPolicy((Qt::ScrollBarPolicy)value);
                break;
        case WINDOWFLAG:
                ((QWidget*)h)->setWindowFlags((Qt::WindowFlags)value);
                break;
        case COMBOBOXSETID:
                ((QComboBox*)h)->setCurrentIndex(value);
                break;
        case SETCONTEXTMENUPOLICY:
                ((QWidget*)h)->setContextMenuPolicy((Qt::ContextMenuPolicy)value);
                break;
        case QPALIGN:
                ((QProgressBar*)h)->setAlignment((Qt::Alignment)value);
                break;
        case QPORIENTATION:
                ((QProgressBar*)h)->setOrientation((Qt::Orientation)value);
                break;
        case QPTEXTDIR:
                ((QProgressBar*)h)->setTextDirection((QProgressBar::Direction)value);
                break;
		case SETSPREAD:
				((QGradient*)h)->setSpread((QGradient::Spread)value);
				break;
        case QPMININUM:
                ((QProgressBar*)h)->setMinimum(value);
                break;
        case QPMAXINUM:
                ((QProgressBar*)h)->setMaximum(value);
                break;
        case QPVALUE:
                ((QProgressBar*)h)->setValue(value);
                break;
        case TRELIDMODE:
                ((QTreeWidget*)h)->setTextElideMode((Qt::TextElideMode)(value));
                break;

        case TREESETCURROW:
                ((QTreeWidget*)h)->setCurrentIndex(((QTreeWidget*)h)->model()->index(value, ((QTreeWidget*)h)->currentIndex().column()));
                break;

        case TREESETCURCOL:
                ((QTreeWidget*)h)->setCurrentIndex(((QTreeWidget*)h)->model()->index(((QTreeWidget*)h)->currentIndex().row(), value));
                break;

        case QXPAINTBGMMODE:
                ((QPainter*)h)->setBackgroundMode((Qt::BGMode)value);
                break;

		case TABLEREMOVEROW:
				((QTableWidget*)h)->removeRow(value);
				break;
		case TABLEREMOVECOLUMN:
			((QTableWidget*)h)->removeColumn(value);
			break;
		case TABLESETCOLUMNCNT:
			((QTableWidget*)h)->setColumnCount(value);
			break;
		case TABLESETROWCNT:
			((QTableWidget*)h)->setRowCount(value);
			break;
		case TABLESELECTROW:
			((QTableWidget*)h)->selectColumn(value);
			break;
		case TABLESETVHRM:
			((QTableWidget*)h)->verticalHeader()->setSectionResizeMode((QHeaderView::ResizeMode) value);
			break;
		case TABLESETVHDSS:
			((QTableWidget*)h)->verticalHeader()->setDefaultSectionSize(value);
			break;
		case TABLESETSM:
			((QTableWidget*)h)->setSelectionMode((QAbstractItemView::SelectionMode)value);
			break;
		case TABLESETSB:
			((QTableWidget*)h)->setSelectionBehavior((QAbstractItemView::SelectionBehavior)value);
			break;
		case TABLESETET:
			((QTableWidget*)h)->setEditTriggers((QAbstractItemView::EditTrigger)value);
			break;
		case TABLESETHHFH:
			((QTableWidget*)h)->horizontalHeader()->setFixedHeight(value);
			break;
			default:
                break;
        }
}

XNLEXPORT xint XI_CDECL widget_set_bint_value(xlong h, xint proid, xint value) {
        switch (proid)
        {
        case OPENBUFFER:
                if (((QBuffer*)h)->open((QFlag)value)) {
                        return 1;
                }
                break;
        default:
                break;
        }
        return 0;
}

XNLEXPORT xbool XI_CDECL widget_get_int_bool(xlong h, xint proid, xint v) {

        switch (proid)
        {
        case TRITEMGETCHECK:
        {
                QTreeWidgetItem * titem = (QTreeWidgetItem *)h;
                return Qt::Checked == titem->checkState(v);
        }
        break;
		case TABITEMGETCHECK:
		{
			QTableWidgetItem * titem = (QTableWidgetItem *)h;
			return Qt::Checked == titem->checkState();
		}
		break;
        }
        return false;
}

XNLEXPORT void XI_CDECL widget_set_int_bool_value(xlong h, xint proid, xint v, xbool v1) {
        switch (proid)
        {
        case SETWINDOWFLAG:
                ((QWidget*)h)->setWindowFlag((Qt::WindowType)v, v1);
                break;
        case TRITEMSETCHECK:
        {
                QTreeWidgetItem * titem = (QTreeWidgetItem *)h;
                titem->setCheckState(v, v1 ? Qt::Checked : Qt::Unchecked);
        }
        break;
		case TABITEMSETCHECK:
		{
			QTableWidgetItem * titem = (QTableWidgetItem *)h;
			titem->setCheckState(v1 ? Qt::Checked : Qt::Unchecked);
		}
		break;
        case SETATTRIBUTE:
                ((QWidget*)h)->setAttribute((Qt::WidgetAttribute)v, v1);
                break;

        case SETRENDERHINT:
                ((QPainter*)h)->setRenderHint((QPainter::RenderHint)v, v1);
                break;
		case SETCOMPOSITIONMODE:
			((QPainter*)h)->setCompositionMode((QPainter::CompositionMode)v);
			break;

        }
}

XNLEXPORT xbool XI_CDECL widget_get_bool_value(xlong h, xint proid) {

        switch (proid)
        {
		case ENABLEDROG:
				return ((QWidget*)h)->acceptDrops();
				break;
        case VISIBLE:
                return ((QWidget*)h)->isVisible();
                break;
        case MAXIMIZED:
                return ((QWidget*)h)->isMaximized();
                break;
        case MINIMIZED:
                return ((QWidget*)h)->isMinimized();
                break;
		case UPDATEENABLE:
			return ((QWidget*)h)->updatesEnabled();
			break;
        case ENABLED:
                return ((QWidget*)h)->isEnabled();
                break;
        case ACTIVED:
                return ((QWidget*)h)->isActiveWindow();
                break;
        case FULLSCREEN:
                return ((QWidget*)h)->isFullScreen();
                break;
        case HIDDEN:
                return ((QWidget*)h)->isHidden();
                break;
		case HASFOCUS:
				return ((QWidget*)h)->hasFocus();
				break;
        case MODAL:
                return ((QWidget*)h)->isModal();
                break;
        case SIZEGRIPENABLED:
                return ((QStatusBar*)h)->isSizeGripEnabled();
                break;
        case WINDOW:
                return ((QWidget*)h)->isWindow();
                break;
        case TREEWIDGETCLEAR:
                ((QTreeWidget*)h)->clear();

                return true;
                break;
        case COMBOXCLR:
                ((QComboBox*)h)->clear();
                break;
        case TREEPROPCLEAR:
                ((QtTreePropertyBrowser*)h)->clear();
                break;
        case SCIFINDNEXT:
                return ((QsciScintilla*)h)->findNext();
                break;
        case CHKGETCHECK:
                return ((QAbstractButton*)h)->isChecked();
                break;
		case CHECKABLE:
				return ((QAction*)h)->isCheckable();
				break;
		case CHECKED:
				return ((QAction*)h)->isChecked();
				break;
        case QPVISIBLE:
                return ((QProgressBar*)h)->isTextVisible();
                break;
        case QPINVERTAPPEAR:
                return ((QProgressBar*)h)->invertedAppearance();
                break;
        default:
                break;
        }
        return 0;
}

XNLEXPORT XObject * XI_CDECL widget_get_object(xlong h, xint proid) {
        XObject * xobj = 0;
        switch (proid)
        {
        case TITLEBAR:
                xobj = getObjectControl(((QDockWidget*)h)->titleBarWidget());
                break;
        case WINDOW:
                xobj = getObjectControl(((QMainWindow*)h)->window());
                break;
        case MENUBAR:
                xobj = getObjectControl(((QMainWindow*)h)->menuBar());
                break;
        case STATUSBAR:
                xobj = getObjectControl(((QMainWindow*)h)->statusBar());
                break;
        case GETWIDGET:
                xobj = getObjectControl(((QDockWidget*)h)->widget());
                break;
        case SUBGETWIDGET:
                xobj = getObjectControl(((QMdiSubWindow*)h)->widget());
                break;
        case CENTRALWIDGET:
                xobj = getObjectControl(((QMainWindow*)h)->centralWidget());
                break;
        case CURRENTSUBWIN:
                xobj = getObjectControl(((QMdiArea*)h)->currentSubWindow());
                break;
        case GETVIEWPORT:
        {
                QAbstractScrollArea * qab = qobject_cast<QAbstractScrollArea *>((QObject*)h);
                if (qab != 0) {
                        xobj = getObjectControl(qab->viewport());
                }
        }

                break;
        case GETTAG:
        {
                XObjectData * objectData = (XObjectData *)((QObject*)h)->userData(Qt::UserRole);
                if (objectData != 0) {
                        xobj = objectData->getTag();
                }
        }
        break;
		case TREEGETTOPITEMS:
		{
			size_t tc = ((QTreeWidget*)h)->topLevelItemCount();
			XObject * objs = gs_env->createLongArray(tc);

			xlong *lva = new xlong[tc];

			for (size_t i = 0; i < tc; i++) {
				lva[i] = (xlong)((QTreeWidget*)h)->topLevelItem(i);
			}

			gs_env->setElementValue(objs, 0, lva, tc);
			delete[]lva;
			return objs;
		}
			break;
        case TREEGETSELITEM:
        {
                QList<QTreeWidgetItem*> items = ((QTreeWidget*)h)->selectedItems();
                XObject * objs = gs_env->createLongArray(items.size());

                QList<QTreeWidgetItem*>::iterator iter = items.begin();
                int id = 0;
				xlong * lva = new xlong[items.size()];

				size_t i = 0;
                while (iter != items.end()) {
					lva[i++] = (xlong)*iter++;
                }
				gs_env->setElementValue(objs, 0, lva, items.size());
				delete[]lva;
                return objs;
        }
                break;
		case TABLEGETSELITEM:
		{
			QList<QTableWidgetItem*> items = ((QTableWidget*)h)->selectedItems();
			XObject * objs = gs_env->createLongArray(items.size());

			QList<QTableWidgetItem*>::iterator iter = items.begin();
			int id = 0;
			xlong * lva = new xlong[items.size()];

			size_t i = 0;
			while (iter != items.end()) {
				lva[i++] = (xlong)*iter++;
			}
			gs_env->setElementValue(objs, 0, lva, items.size());
			delete[]lva;
			return objs;
		}
		break;
		case TABLEGETSELRANGE:
		{
			QList<QTableWidgetSelectionRange> items = ((QTableWidget*)h)->selectedRanges();
			XObject * objs = gs_env->createLongArray(items.size() * 2);

			QList<QTableWidgetSelectionRange>::iterator iter = items.begin();
			int id = 0;
			xlong * lva = new xlong[items.size() * 2];

			size_t i = 0;
			while (iter != items.end()) {
				QTableWidgetSelectionRange & wsr = *iter;
				lva[i] = wsr.leftColumn();
				lva[i] = (lva[i] << 32) | wsr.rightColumn();

				lva[i + 1] = wsr.topRow();
				lva[i + 1] = (lva[i + 1] << 32) | wsr.bottomRow();

				iter++;
				i += 2;
			}
			gs_env->setElementValue(objs, 0, lva, items.size() * 2);
			delete[]lva;
			return objs;
		}
		break;
        case TREEGETCHILDREN:
        {
                size_t count = ((QTreeWidgetItem*)h)->childCount();
                XObject * objs = gs_env->createLongArray(count);
				xlong * lva = new xlong[count];

                for (size_t i =0; i < count; i ++){
					lva[i] = (xlong)((QTreeWidgetItem*)h)->child(i);
                }
				gs_env->setElementValue(objs, 0, lva, count);
				delete[] lva;
                return objs;
        }
                break;
        case SAVESTATE:
        {
                QByteArray data = ((QMainWindow*)h)->saveState();

                XObject * objs = gs_env->createByteArray(data.size());

         
                gs_env->setElementValue(objs, 0, (xbyte*)data.data(), data.size());
                

                return objs;
        }
                break;
        }
        if (xobj != 0) {

                return gs_env->referenceObject(xobj);
        }
        return 0;
}



XNLEXPORT double XI_CDECL widget_get_double_value(xlong h, xint proid) {

        switch (proid)
        {
        case OPACITY:
                return ((QWidget*)h)->windowOpacity();
                break;
        }
        return 0;
}

XNLEXPORT void XI_CDECL widget_set_double_value(xlong h, xint proid, double v) {

        switch (proid)
        {
        case OPACITY:
                ((QWidget*)h)->setWindowOpacity(v);
                break;
        case QXPAINTOPACITY:
                ((QPainter*)h)->setOpacity(v);
                break;
        }

}

XNLEXPORT void XI_CDECL widget_set_bool_value(xlong h, xint proid, xbool v) {
        switch (proid)
        {
        case FLATING:
                ((QDockWidget*)h)->setFloating(v);
                break;

        case VISIBLE:
                ((QWidget*)h)->setVisible(v);
                break;


        case MAXIMIZED:
                if (v) {
                        ((QWidget*)h)->showMaximized();
                }else {
                        ((QWidget*)h)->showNormal();
                }
                break;
		case QPBADJUST:
		{
			((QtTreePropertyBrowser*)h)->setResizeMode(v ? QtTreePropertyBrowser::ResizeMode::Interactive : QtTreePropertyBrowser::ResizeMode::Fixed);
		}
			break;
        case MINIMIZED:
                if (v) {
                        ((QWidget*)h)->showMinimized();
                }else {
                        ((QWidget*)h)->showNormal();
                }
                break;
        case SIZEGRIPENABLED:
                ((QStatusBar*)h)->setSizeGripEnabled(v);
                break;
		case UPDATEENABLE:
				((QWidget*)h)->setUpdatesEnabled(v);
				break;
        case ENABLED:
                ((QWidget*)h)->setEnabled(v);
                break;
        case ACTENABLED:
                ((QAction*)h)->setEnabled(v);
                break;
        case ACTIVED:
                if (v) {
                        ((QWidget*)h)->activateWindow();
                }
                break;

        case MODAL:
                ((QDialog*)h)->setModal(v);
                break;

        case SPWVM:
                ((QtTreePropertyBrowser*)h)->setPropertiesWithoutValueMarked(v);
                break;

        case SRID:
                ((QtTreePropertyBrowser*)h)->setRootIsDecorated(v);
                break;

        case CHKSETCHECK:
                ((QAbstractButton*)h)->setChecked(v);
                break;

        case SETSEP:
                ((QAction*)h)->setSeparator(v);
                break;
		case CHECKABLE:
				((QAction*)h)->setCheckable(v);
			break;

		case CHECKED:
				((QAction*)h)->setChecked(v);
			break;

        case QPVISIBLE:
                ((QProgressBar*)h)->setTextVisible(v);
                break;

        case QPINVERTAPPEAR:
                ((QProgressBar*)h)->setInvertedAppearance(v);
                break;

        case TRCOLUMNSHOW:
                ((QTreeWidget*)h)->header()->setVisible(v);

                break;

        case TRSORTENABLE:
                ((QTreeWidget*)h)->setSortingEnabled(v);
                break;

        case TRSELECTMODE:
                ((QTreeWidget*)h)->setSelectionBehavior((v ? QTreeWidget::SelectRows : QTreeWidget::SelectItems));
                break;

        case TRAUTORESIZE:
                ((QTreeWidget*)h)->header()->setSectionResizeMode(v? QHeaderView::ResizeToContents : QHeaderView::Fixed);
                break;

        case TRIEMSETEXPAND:
        {
                QTreeWidgetItem * titem = (QTreeWidgetItem *)h;
                titem->setExpanded(v);
        }
                break;
        case TRIEMSETHIDDEN:
        {
                QTreeWidgetItem * titem = (QTreeWidgetItem *)h;
                titem->setHidden(v);
        }
		break;
		case TABLESETHHLS:
		{
			((QTableWidget*)h)->horizontalHeader()->setStretchLastSection(v);
		}
        break;
		case TABLESETSG:
		{
				((QTableWidget*)h)->setShowGrid(v);
		}
		break;
		case TABLESETVHV:
		{
			((QTableWidget*)h)->verticalHeader()->setVisible(v);
		}
		break;
		case ENABLEDROG:
			((QWidget*)h)->setAcceptDrops(v);
			break;
        }
}

XNLEXPORT void XI_CDECL widget_set_bkrl(xlong h, xint r) {
        ((QWidget*)h)->setBackgroundRole((QPalette::ColorRole)r);
}

XNLEXPORT xint XI_CDECL widget_get_int_value(xlong h, xint proid) {
        switch (proid)
        {
		case FONTASCENT: {
			QFontMetrics fm(*(QFont*)h);
			return fm.ascent();
		}
			break;
		case FONTDESCENT: {
			QFontMetrics fm(*(QFont*)h);
			return fm.descent();
		}
		 break;
		case PAINTFONTASCENT: {
			QFontMetrics fm(((QPainter*)h)->font());
			return fm.ascent();
		}
			break;
		case PAINTFONTDESCENT: {
			QFontMetrics fm(((QPainter*)h)->font());
			return fm.descent();
		}
			break;
        case SETFOCUSPOLICY:
            return ((QWidget*)h)->focusPolicy();
            break;
        case MINIMUMHEIGHT:
                return ((QWidget*)h)->minimumHeight();
                break;

        case MAXIMUMHEIGHT:
                return ((QWidget*)h)->maximumHeight();
                break;

        case MINIMUMWIDTH:
                return ((QWidget*)h)->minimumWidth();
                break;

        case MAXIMUMWIDTH:
                return ((QWidget*)h)->maximumWidth();
                break;

        case WIDTH:
                return ((QWidget*)h)->width();
                break;

        case HEIGHT:
                return ((QWidget*)h)->height();
                break;

        case X_POS:
                return ((QWidget*)h)->x();
                break;

        case Y_POS:
                return ((QWidget*)h)->y();
                break;

        case IMGFORMAT:
                return ((QImage*)h)->format();
                break;

        case IMGWIDTH:
                return ((QImage*)h)->width();
                break;

        case IMGHEIGHT:
                return ((QImage*)h)->height();
                break;

        case COMBOBOXGETID:
                return ((QComboBox*)h)->currentIndex();
                break;

        case QPMININUM:
                return ((QProgressBar*)h)->minimum();
                break;

        case QPMAXINUM:
                return ((QProgressBar*)h)->maximum();
                break;

        case QPVALUE:
                return ((QProgressBar*)h)->value();
                break;

        case QPALIGN:
                return ((QProgressBar*)h)->alignment();
                break;

        case QPORIENTATION:
                return ((QProgressBar*)h)->orientation();
                break;

        case QPTEXTDIR:
                return ((QProgressBar*)h)->textDirection();
                break;

        case TRHEADERWIDTH:
                return ((QTreeWidget*)h)->header()->width();
                break;

        case TREEGETCURROW:
                return ((QTreeWidget*)h)->currentIndex().row();
                break;

		case GETFONTPIXELSIZE:
			return ((QFont*)h)->pixelSize();
			break;

		case GETFONTPTSIZE:
			return ((QFont*)h)->pointSize();
			break;

        case TREEGETCURCOL:
                return ((QTreeWidget*)h)->currentIndex().column();
                break;

        case TREEGETCOUNT:
                return ((QTreeWidget*)h)->topLevelItemCount();
                break;

        case TREEITEMGETFLAG:
                return ((QTreeWidgetItem*)h)->flags();
                break;
		case TABITEMGETFLAG:
			return ((QTableWidgetItem*)h)->flags();
			break;
        case SCREENCOUNT:
        {
                QDesktopWidget * desktop = QApplication::desktop();
                return desktop->screenCount();
        }
        break;
        case CURRENTSCREEN:
        {
                QDesktopWidget * desktop = QApplication::desktop();
                return desktop->screenNumber((QWidget*)h);
        }
        break;
        }

        return 0;
}


QColor QMakeColor(xint c) {
        QColor qc(c);
        qc.setAlpha((c >> 24) & 0xff);
        return qc;
}
XNLEXPORT xint XI_CDECL widget_set_v2int_value(xlong h, xint proid, xint xv, xint yv) {
        switch (proid)
        {
        case RESIZE:
                ((QWidget*)h)->resize(xv, yv);
                break;

        case SCROLL:
                ((QWidget*)h)->scroll(xv, yv);
                break;

        case FIXEDSIZE:
                ((QWidget*)h)->setFixedSize(xv, yv);
                break;

        case SCICMD:
                return ((QsciScintilla*)h)->SendScintilla(xv, yv);
                break;

        case MOVE:
                ((QWidget*)h)->move(xv, yv);
                break;

        case SETCOLUMBWIDTH:
        {
                QTreeWidget * parent = (QTreeWidget *)h;
                parent->setColumnWidth(xv, yv);
        }
        break;
        case QPRANGE:
                ((QProgressBar*)h)->setRange(xv, yv);
                break;
		case SETPROPWIDTHS:
			((QtTreePropertyBrowser*)h)->setHeaderWidth(xv, yv);
			break;
        case TREESETCURROW:
                ((QTreeWidget*)h)->setCurrentIndex(((QTreeWidget*)h)->model()->index(xv, yv));
        break;
        case TREEITEMFLAG:
        {
                int flag = ((QTreeWidgetItem*)h)->flags();
                flag &= ~yv;
                flag |= (xv & 0xffffffff);
                ((QTreeWidgetItem*)h)->setFlags((Qt::ItemFlags)flag);
        }
        break;
		case TABLEITEMFLAG:
		{
			int flag = ((QTableWidgetItem*)h)->flags();
			flag &= ~yv;
			flag |= (xv & 0xffffffff);
			((QTableWidgetItem*)h)->setFlags((Qt::ItemFlags)flag);
		}
		break;
        case SETBRUSH:
        {
                QBrush brush;
                brush.setColor(QMakeColor(xv));
                brush.setStyle(Qt::BrushStyle(yv));
                ((QPainter*)h)->setBrush(brush);
        }
        break;
        case SETBKBRUSH:
        {
                QBrush brush;
                brush.setColor(QMakeColor(xv));
                brush.setStyle(Qt::BrushStyle(yv));
                ((QPainter*)h)->setBackground(brush);
        }
        break;
		case TABLESETHHRS:
		{
			((QTableWidget*)h)->horizontalHeader()->resizeSection(xv, yv);
		}
		break;
        case PALETTE:
        {
                QPalette pal;
                pal.setColor((QPalette::ColorRole)xv, QMakeColor(yv));
                ((QWidget*)h)->setPalette(pal);
        }
                break;
        }
        return 0;
}

XNLEXPORT xint XI_CDECL widget_set_v2int_double_value(xlong h, xint proid, xint xv, double w, xint yv) {
        switch (proid)
        {
        case SETPEN:
        {
                QPen pen;
                pen.setWidth(w);
                pen.setColor(QMakeColor(xv));
                pen.setStyle(Qt::PenStyle(yv));
				
                ((QPainter*)h)->setPen(pen);
        }
                break;

		case SETCOLORAT:
			((QGradient*)h)->setColorAt(w, xv);
			break;
        }
        return 0;
}

XNLEXPORT void XI_CDECL native_int4(xlong h, xint proid, xint v1, xint v2, xint v3, xint v4) {
        switch (proid)
        {
        case QXPAINTDRAWLINE:
        {
                ((QPainter*)h)->drawLine(v1, v2, v3, v4);

        }
        break;
		case QXPAINTDRAWRECT:
		{
			((QPainter*)h)->drawRect(v1, v2, v3, v4);

		}
		break;

        case DRAWELLIPSE:
        {
                ((QPainter*)h)->drawEllipse(v1, v2, v3, v4);
        }
        break;
        }
}

XNLEXPORT xint XI_CDECL widget_set_v3int_value(xlong h, xint proid, xint v1, xint v2, xint v3) {
        switch (proid)
        {
        case SCICMD:
                return ((QsciScintilla*)h)->SendScintilla(v1, v2, v3);
                break;
        }
        return 0;
}

XNLEXPORT xint XI_CDECL widget_set_intstring_value(xlong h, xint proid, xint xv, xstring yv) {
        switch (proid)
        {
        case SCICMD:
                return ((QsciScintilla*)h)->SendScintilla(xv, yv);
                break;
		case FSWADDFILE:
			if (((QFileSystemWatcher*)h)->addPath(QString::fromUtf8(yv))) {
				return 1;
			}
			break;
		case FSWREMFILE:
			if (((QFileSystemWatcher*)h)->removePath(QString::fromUtf8(yv))) {
				return 1;
			}
			break;
        }
        return 0;
}


XNLEXPORT xint XI_CDECL widget_set_intintstring_value(xlong h, xint proid, xint v1, xint v2, xstring v3) {

        switch (proid)
        {
        case SCICMD:
                return ((QsciScintilla*)h)->SendScintilla(v1, v2, v3);
                break;
        case DRAWTEXT:
                ((QPainter*)h)->drawText(QPoint(v1, v2), QString::fromUtf8(v3));
                break;

        }
        return 0;
}

XNLEXPORT void XI_CDECL widget_set_native_value(xlong h, xint proid, xlong value) {
        switch (proid)
        {
        case PALETTE:
                ((QWidget*)h)->setPalette(*(QPalette*)value);
                break;

        case STYLE:
                ((QWidget*)h)->setStyle((QStyle*)value);
                break;
		case DRAWPATH:
		{
			QPainterPath * buf = (QPainterPath *)value;
			((QPainter*)h)->drawPath(*buf);
		}
		break;
        case SCIFONT:
                ((QsciScintilla*)h)->setFont(*(QFont*)value);
                break;

        case SETAPPFONT:
                _xapplication->setFont(*(QFont*)value);
                break;

        case SETWIDGET:
                ((QDockWidget*)h)->setWidget((QWidget*)value);
                break;

		case SETBRUSH:
				((QPainter*)h)->setBrush(*(QBrush*)value);
				break;

        case SUBSETWIDGET:
                ((QMdiSubWindow*)h)->setWidget((QWidget*)value);
                break;

        case PARENTWIDGET:
                ((QWidget*)h)->setParent((QWidget*)value);
                break;


        case PAINTSETMATRIX:
                ((QPainter*)h)->setMatrix(*(QMatrix*)value);
                break;


        case XNOTIFY:
                _xapplication->postEvent((QObject*)h, new NotifyEvent(value));
                break;

        case REMSUBWIN:
                ((QMdiArea*)h)->removeSubWindow((QWidget*)value);
                break;

        case ADDSUBWIN:
                ((QMdiArea*)h)->addSubWindow((QWidget*)value);
                break;

        case SETACTSUBWIN:
                ((QMdiArea*)h)->setActiveSubWindow((QMdiSubWindow*)value);
                break;

        case ADDSUBPROPERTY:
                ((QtProperty*)h)->addSubProperty((QtProperty*)value);
                break;

        case ADDDEFACTION:
                ((QWidget*)h)->addAction((QAction*)value);
                ar.installAction((QAction*)value);
                break;

        case REMOVEWIDGET:
                ((QStatusBar*)h)->removeWidget((QWidget*)value);
                break;

        case PAINTERSETFONT:
		{
			QFont* pf = (QFont*)value;
			((QPainter*)h)->setFont(*pf);
		}
                
                break;

        case TREEWIDGETREM:
        {
                QTreeWidgetItem* item = (QTreeWidgetItem*)value;

                if (item != 0) {
                        QTreeWidgetItem* parent = item->parent();
                        if (parent != 0) {
                                parent->removeChild(item);
                        }
                        else {
                                int i = ((QTreeWidget*)h)->indexOfTopLevelItem(item);
                                /*QList<QTreeWidgetItem *> children(item->takeChildren());
                                qDeleteAll(children);*/
                                delete ((QTreeWidget*)h)->takeTopLevelItem(i);
                        }
                }
                //((QTreeWidget*)h)->takeTopLevelItem(id);
        }

        break;
        case TREESETCURITEM:
                QTreeWidgetItem* item = (QTreeWidgetItem*)value;
                if (item != 0) {
                        ((QTreeWidget*)h)->setCurrentItem(item);
                }
                break;
        }
}

XNLEXPORT void XI_CDECL widget_slot_string(xlong h, xint proid, xstring value) {
        switch (proid)
        {
        case WINDOWTITLE:
                ((QWidget*)h)->setWindowTitle(QString::fromUtf8(value));
                break;
        case WINDOWICON:
                ((QWidget*)h)->setWindowIcon(*loadIcon(QString::fromUtf8(value)));
                break;
        case FONTSETFAMILY:
                ((QFont*)h)->setFamily(QString::fromUtf8(value));
                break;
        case LINEEDITSETTEXT:
                ((QLineEdit*)h)->setText(QString::fromUtf8(value));
                break;
        case BUTTONSETTEXT:
                ((QAbstractButton*)h)->setText(QString::fromUtf8(value));
                break;
        case LBLSETTEXT:
                ((QLabel*)h)->setText(QString::fromUtf8(value));
                break;
        case COMBOSETTEXT:
                ((QComboBox*)h)->setCurrentText(QString::fromUtf8(value));
                break;
        case ACTSETTEXT:
                ((QAction*)h)->setText(QString::fromUtf8(value));
                break;
		case SETWHATSTHIS:
				((QWidget*)h)->setWhatsThis(QString::fromUtf8(value));
				break;
        case SHOWMESSAGE:
                ((QStatusBar*)h)->showMessage(QString::fromUtf8(value));
                break;
        case QPFORMAT:
                ((QProgressBar*)h)->setFormat(QString::fromUtf8(value));
                break;
		case SETSHRCUT:
				((QAction*)h)->setShortcut(QKeySequence::fromString(QString::fromUtf8(value)));
				break;
        case STYLESHEET:
        {

                QFile file(QString::fromUtf8(value));
                file.open(QFile::ReadOnly);
                QString qss = QLatin1String(file.readAll());
                ((QApplication*)h)->setStyleSheet(qss);
                file.close();
        }
                break;
		case STYLESHEETSTRING:
		{
			((QApplication*)h)->setStyleSheet(QString::fromUtf8(value));
		}
		break;
        case PALETTECOLOR:
                ((QApplication*)h)->setPalette(QPalette(QColor(value)));

                break;
		case OPENURL:
				QDesktopServices::openUrl(QUrl(QString::fromUtf8(value)));
			break;
        case OPENLOCAL:
                QDesktopServices::openUrl(QUrl::fromLocalFile((QString::fromUtf8(value))));
            break;
		case SETTOOLTIPS:
			((QWidget*)h)->setToolTip(QString::fromUtf8(value));
			break;
		case SETSTYLESHEET:
		{
			QFile file(QString::fromUtf8(value));
			file.open(QFile::ReadOnly);
			QString qss = QLatin1String(file.readAll());
			((QWidget*)h)->setStyleSheet(qss);
			file.close();
		}
			break;
		case SETSTYLESHEETSTRING:
			((QWidget*)h)->setStyleSheet(QString::fromUtf8(value));
			break;
		case SETWIDGETFONT:
		{
			QFont ft;
			ft.fromString(QString::fromUtf8(value));
			((QWidget*)h)->setFont(ft);
		}
			break;
		case LOADTRANSLATE: 
		{
			QTranslator *trans = new QTranslator;
			if (trans->load(QString::fromUtf8(value))) {
				((QApplication*)h)->installTranslator(trans);
			}
		}
			break;

        }
}

XNLEXPORT void XI_CDECL widget_slot(xlong h, xint proid) {
        switch (proid)
        {
        case CLOSE:
                ((QWidget*)h)->close();
                break;
        case HIDE:
                ((QWidget*)h)->hide();
                break;
        case LOWER:
                ((QWidget*)h)->lower();
                break;
        case RAISE:
                ((QWidget*)h)->raise();
                break;
        case REPAINT:
                ((QWidget*)h)->repaint();
                break;
        case UPDATE:
                ((QWidget*)h)->update();
                break;
        case SHOWFULLSCREEN:
                ((QWidget*)h)->showFullScreen();
                break;
        case SHOWMAX:
                ((QWidget*)h)->showMaximized();
                break;
        case SHOWMIN:
                ((QWidget*)h)->showMinimized();
                break;
        case SHOWNORMAL:
                ((QWidget*)h)->showNormal();
                break;
        case SHOW:
                ((QWidget*)h)->show();
                break;
        case FONTCTOR:
                delete (QFont*)h;
                break;
		case PATHCTOR:
			delete (QPainterPath*)h;
			break;
        case NATIVEFINALIZE:
        {
                QObject * pObj = (QObject*)h;
                XObjectData * objectData = (XObjectData *)pObj->userData(Qt::UserRole);
                pObj->setUserData(Qt::UserRole, 0);
                if (objectData != 0) {
                        delete objectData;
                }
        }
                break;

        case CASCADESUBWIN:
                ((QMdiArea*)h)->cascadeSubWindows();
                break;

        case TILESUBWIN:
                ((QMdiArea*)h)->tileSubWindows();
                break;

        case SETFOCUS:
                ((QWidget*)h)->setFocus();
                break;

        case QPFORMAT:
                ((QProgressBar*)h)->resetFormat();
                break;

        case QPRESET:
                ((QProgressBar*)h)->reset();
                break;

        case DELLOCBUFFER:
        {
                ((QBuffer*)h)->close();
                delete (QBuffer*)h;
        }
                break;

		case DELLOCGRADIENT:
		{
			delete (QGradient*)h;
		}
		break;


        case DELLOCICON:
        {
                delete (QIcon*)h;
        }
        break;
        case DELLOCBYTEARRAY:
        {
                delete (QByteArray*)h;
        }
        break;
        case TRSCROLLBOTTOM:
                ((QTreeWidget*)h)->scrollToBottom();
                break;
        case TRIEMCLEARCHILD:
        {
                QTreeWidgetItem * titem = (QTreeWidgetItem *)h;
                QList<QTreeWidgetItem *> children(titem->takeChildren());
                qDeleteAll(children);
                break;
        }

        case DELETEIMAGE:
                delete ((QImage*)h);
                break;

        case MATRIXDTOR:
                delete ((QMatrix*)h);
                break;
		case DELLOCBRUSH:
		
				delete ((QBrush*)h);
				break;
        case PAINTERSAVE:
                ((QPainter*)h)->save();
                break;

        case PAINTERRESTORE:
                ((QPainter*)h)->restore();
                break;

        case PAINTRESETMATRIX:
                ((QPainter*)h)->resetMatrix();
                break;

        case PAINTRESETTRANSFORM:
                ((QPainter*)h)->resetTransform();
                break;
        case DELLOCPAINTER:
                delete ((QPainter*)h);
                break;
        case DELETEWIDGET:
                delete ((QWidget*)h);
                break;
		case TABLECLEAR:
			((QTableWidget*)h)->clear();
			break;
		case TABLECLEARCONTENT:
			((QTableWidget*)h)->clearContents();
			break;
        default:
                break;
        }
}

XNLEXPORT xbool XI_CDECL array_int2(xlong h, xint proid, XObject * obj, xint pos, xint len) {
        switch (proid)
        {
        case BUFFERSETDATA:
        {
                QBuffer * buf = (QBuffer *)h;
                if (gs_env->isArray(obj)) {
                        QByteArray byteArray;
						extartByteArray(obj, byteArray);
                        buf->setData(byteArray);
                }
                return true;
        }
                break;

        case QXPAINTDRAWLINE:
        {

                if (gs_env->isArray(obj)) {
                        for (int i = 2, c = gs_env->getLengthOfArray(obj); i < c; i += 2) {
                                xint x, y, ex, ey;
                                gs_env->getElementValue(obj, i - 2, &x, 1);
                                gs_env->getElementValue(obj, i - 1, &y, 1);
                                gs_env->getElementValue(obj, i , &ex, 1);
                                gs_env->getElementValue(obj, i + 1, &ey, 1);
                                ((QPainter*)h)->drawLine(x, y, ex, ey);
                        }
                }
                return true;
        }
        break;
        default:
                break;
        }
        return false;
}

XNLEXPORT xlong XI_CDECL create_array_int2(xlong h, xint proid, XObject * obj, xint pos, xint len) {
        switch (proid)
        {
        case BUFFERSETDATA:
        {
                if (gs_env->isArray(obj)) {
                        QByteArray * byteArray = new QByteArray();
						extartByteArray(obj, *byteArray);

                        return (xlong)byteArray;
                }
                return true;
        }
        break;
        default:
                break;
        }
        return 0;
}

XNLEXPORT xbool XI_CDECL core_sub_class(xlong h, XObject * pthis, XObject * subclass) {

        return 0;
}

XNLEXPORT XObject * XI_CDECL findControl(xlong h, xstring name) {
        QObject * obj = (QObject *)h;
        QObject * child = obj->findChild<QObject*>(QString::fromUtf8(name));
        if (child != NULL) {
                XObject * xobj = getObjectControl(child);
                if (xobj != NULL) {

                        return gs_env->referenceObject(xobj);
                }
        }
        return gs_env->createObject();
}

XNLEXPORT xlong XI_CDECL attachControl(xlong h, XObject * x, xstring name) {
        QObject * obj = (QObject *)h;

        QObject * child = obj->findChild<QObject*>(QString::fromUtf8(name));
        if (child != NULL) {
                XObjectData * data = (XObjectData *)child->userData(Qt::UserRole);
                if (data == NULL) {
                        data = new XObjectData();
                        child->setUserData(Qt::UserRole, data);

                        const char * type = child->metaObject()->className();
                        if (strcmp(type, "QMenu") == 0) {
                                QMenu * pm = (QMenu*)child;
                                QList<QAction*> acts = pm->actions();
                                for (QAction* act : acts) {
                                        getObjectControl(act);
                                        ar.installAction(act);
                                }
                        }
                        if (strcmp(type, "QTreeWidget") == 0) {
                            ar.installTreeAction(child);
                        }
						if (strcmp(type, "QTableWidget") == 0) {
							ar.installTableCellChange((QTableWidget*)child);
						}
                        if (strcmp(type, "QPushButton") == 0 || strcmp(type, "QCheckBox") == 0) {
                            ar.installButtonAction(child);
                        }
                        if (strcmp(type, "QLineEdit") == 0) {
                            ar.installEditAction(child);
                        }
						if (strcmp(type, "QComboBox") == 0) {
							ar.installComboBoxAction((QComboBox*)child);
						}
						if (strcmp(type, "QFileSystemWatcher") == 0) {
							ar.installFSWEvent((QFileSystemWatcher*)child);
						}
                }
                data->setObject(x);
                return (xlong)child;
        }

        return 0;
}

XNLEXPORT xlong XI_CDECL core_attach(xlong h, XObject * x) {
        QObject * obj = (QObject *)h;

        if (obj != NULL) {
                XObjectData * data = (XObjectData *)obj->userData(Qt::UserRole);
                if (data == NULL) {
                        data = new XObjectData();
                        obj->setUserData(Qt::UserRole, data);
                }


                data->setObject(x);
                return (xlong)obj;
        }

        return 0;
}

XNLEXPORT XObject * XI_CDECL object_get_string(xlong h, xint proid, xstring name) {
        QObject * obj = 0;
        switch (proid) {
        case ADDACTION:
                obj = ((QMenuBar*)h)->addAction(QString::fromUtf8(name));
                break;
        }

        return getObjectControl(obj);
}

XNLEXPORT XObject * XI_CDECL core_getName(xlong h) {
        QByteArray qba;
        QObject * obj = (QObject *)h;
        if (obj != 0) {
                qba = obj->objectName().toUtf8();
        }
        return data2String(qba);
}

XNLEXPORT XObject *  XI_CDECL core_getClassName(xlong h) {


        return 0;
}

XNLEXPORT XObject * XI_CDECL core_getParent(xlong h) {


        return 0;
}
XNLEXPORT xint XI_CDECL core_getintlong(xlong h, xint proid, xlong v) {
        switch (proid)
        {
        case PEORENUMVALUE:
                return ((QtEnumPropertyManager*)h)->value((QtProperty*)v);
                break;
        }
        return 0;
}

XNLEXPORT XObject *  XI_CDECL core_getString(xlong h, xint proid) {
        QByteArray qba;
        switch (proid)
        {
        case LINEEDITGETTEXT:
                qba = ((QLineEdit*)h)->text().toUtf8();
                break;
        case LBLGETTEXT:
                qba = ((QLabel*)h)->text().toUtf8();
                break;
        case COMBOGETTEXT:
                qba = ((QComboBox*)h)->currentText().toUtf8();
                break;
        case QSCIGETTEXT:
                qba = ((QsciScintilla*)h)->text().toUtf8();
                break;
        case QSCIGETSELTXT:
                qba = ((QsciScintilla*)h)->selectedText().toUtf8();
                break;
        case PROPGETVALUE:
                qba = ((QtVariantProperty *)h)->valueText().toUtf8();
                break;
        case ACTGETTEXT:
                qba = ((QAction *)h)->text().toUtf8();
                break;
        case CURRENTMESSAGE:
                qba = ((QStatusBar *)h)->currentMessage().toUtf8();
                break;
        case QPTEXT:
                qba = ((QProgressBar *)h)->text().toUtf8();
                break;
        case QPFORMAT:
                qba = ((QProgressBar*)h)->format().toUtf8();
                break;
		case GETSTYLESHEEY:
				qba = ((QWidget*)h)->styleSheet().toUtf8();
			break;
		case GETFONTDESCRIPTION:
				qba = ((QFont*)h)->toString().toUtf8();
			break;
		case GETFONTNAME:
			qba = ((QFont*)h)->family().toUtf8();
			break;
		case GETTOOLTIPS:
			qba = ((QWidget*)h)->toolTip().toUtf8();
			break;
        }
        return data2String(qba);
}


XNLEXPORT XObject * XI_CDECL object_get_handle_string(xlong h, xint proid, xlong handle, xstring name) {


        return 0;
}

XNLEXPORT XObject * XI_CDECL object_get_string2(xlong h, xint proid, xstring v1, xstring v2) {


        return 0;
}

XNLEXPORT XObject * XI_CDECL object_get_handle(xlong h, xint proid, xlong h1) {

        switch (proid)
        {
        case IMGGETDATA:
        {
                QImage * pImage = (QImage*)h;
                const uchar *  data = pImage->bits();
                size_t count = pImage->byteCount();
                XObject * obj = gs_env->createByteArray(count);
     
                gs_env->setElementValue(obj, 0, (xbyte*)data, count);
                

                return obj;
        }
                break;
        default:
                break;
        }
        return 0;
}

XNLEXPORT XObject * XI_CDECL object_get_handle2(xlong h, xint proid, xlong hv, xlong h1) {

	switch (proid) {
		case TABLEGETCELLWIDGET:
		{
			QTableWidget * qt = (QTableWidget*)h;
			QWidget * pw = qt->cellWidget(hv, h1);
			if (pw != 0) {
				XObject * xobj = getObjectControl(pw);
				if (xobj != NULL) {
					return gs_env->referenceObject(xobj);
				}
			}
		}
		break;
	}

        return 0;
}

XNLEXPORT XObject * XI_CDECL object_get_string_handle_string2(xlong h, xint proid, xstring text, xlong handle, xstring v1, xstring v2) {


        return 0;
}

XNLEXPORT XObject * XI_CDECL object_get_string_handle_string_int(xlong h, xint proid, xstring text, xlong handle, xstring v1, xint v2) {


        return 0;
}

XNLEXPORT XObject * XI_CDECL object_get_string2_handle_string2(xlong h, xint proid, xstring h1, xstring text, xlong handle, xstring v1, xstring v2) {


        return 0;
}

XNLEXPORT XObject * XI_CDECL object_get_string2_handle_string_int(xlong h, xint proid, xstring h1, xstring text, xlong handle, xstring v1, xint v2) {


        return 0;
}


XNLEXPORT XObject *  XI_CDECL openfile_dlg_string3_obj(xint proid, xstring caption, xstring defaultPath, xstring pattern, xlong parent) {

        QByteArray qba;

        switch (proid) {
        case SAVE:
        {
                QString file = QFileDialog::getSaveFileName((QWidget*)parent, QString::fromUtf8(caption), QString::fromUtf8(defaultPath), QString::fromUtf8(pattern));
                qba = file.toUtf8();
        }
                break;

        case OPEN:
        {
                QString file = QFileDialog::getOpenFileName((QWidget*)parent, QString::fromUtf8(caption), QString::fromUtf8(defaultPath), QString::fromUtf8(pattern));
                qba = file.toUtf8();
        }
                break;

        case FOLDER:
                if (pattern != 0) {
                        QString file = QFileDialog::getExistingDirectory((QWidget*)parent, QString::fromUtf8(caption), QString::fromUtf8(defaultPath), (QFileDialog::Option)QString::fromUtf8(pattern).toInt());
                        qba = file.toUtf8();
                }
                else {
                        QString file = QFileDialog::getExistingDirectory((QWidget*)parent, QString::fromUtf8(caption), QString::fromUtf8(defaultPath));
                        qba = file.toUtf8();
                }
                break;
		case GETFONT:
		{
			bool bOk = false;
			QFont deffont;
			deffont.fromString(QString::fromUtf8(defaultPath));
			QFont file = QFontDialog::getFont(&bOk, deffont, (QWidget*)parent, QString::fromUtf8(caption));
			if (bOk == false) {
				return 0;
			}
			qba = file.toString().toUtf8();
		}
			break;
        }

        return data2String(qba);
}

XNLEXPORT xlong XI_CDECL long_longstring(xlong handle, xint proid, xlong v1, xstring v2) {
        switch (proid)
        {
        case TREEWIDGETADD:
        {
                QTreeWidget * twidget = (QTreeWidget *)handle;
                QTreeWidgetItem * item = 0;

                if (twidget != 0) {
                        item = new QTreeWidgetItem(twidget);
                }
                else {
                        item = new QTreeWidgetItem();
                }
                item->setText(0, QString::fromUtf8(v2));
                if (v1 != 0) {
                        item->setIcon(0, *(QIcon*)(v1));
                }

                return (xlong)item;
        }
        break;
        case MEASURETEXT:
        {
                QFontMetrics fm(*(QFont*)handle);
                QRect rc = fm.boundingRect(QString::fromUtf8(v2));
                xlong v = rc.width();
                v <<= 32;
                return v | rc.height();
        }
                break;

		case PAINTMEASURETEXT:
		{
			QPainter * fm = (QPainter*)handle;
			QRect rc = fm->fontMetrics().boundingRect(QString::fromUtf8(v2));
			xlong v = rc.width();
			v <<= 32;
			return v | rc.height();
		}
		break;
        default:
                break;
        }

        return 0;
}

XNLEXPORT xlong XI_CDECL long_object_string(xlong handle, xint proid, XObject * v1, xstring v2) {
        switch (proid)
        {
        case IMGLOAD:

                if (gs_env->isArray(v1)) {
                        QByteArray byteArray;
						extartByteArray(v1, byteArray);

                        QImage * pimage = new QImage();
                        if (false == pimage->loadFromData(byteArray, v2)) {
                            delete pimage;
                            pimage = 0;
                        }
						
                        return (xlong)pimage;
                }

                break;
        default:
                break;
        }

        return 0;
}



XNLEXPORT void XI_CDECL long_long_int9(xlong h, xint proid, xlong v1, xint x1, xint x2, xint x3, xint x4, xint y1, xint y2, xint y3, xint y4, xint z1) {
        switch (proid)
        {
        case DRAWIMAGE:
                ((QPainter*)h)->drawImage(QRect(x1, x2, x3, x4), *(QImage*)v1, QRect(y1, y2, y3, y4), Qt::ImageConversionFlag(z1));
        break;
        case FILLRECT:
        {
                ((QPainter*)h)->fillRect(QRect(x1, x2, x3, x4), QBrush(QMakeColor(y1), Qt::BrushStyle(y2)));
        }
        break;
        case ROUNDRECT:
        {
                ((QPainter*)h)->drawRoundRect(QRect(x1, x2, x3, x4),y1, y2);
        }
        break;
        case ROUNDEDRECT:
        {
                ((QPainter*)h)->drawRoundedRect(QRect(x1, x2, x3, x4), y1, y2);
        }
        break;
        }
}

XNLEXPORT xlong XI_CDECL long_string2(xlong handle, xint proid, xstring v1, xstring v2) {
        switch (proid)
        {
		case OPENURL:
			if (QDesktopServices::openUrl(QUrl(QString::fromUtf8(v1)))) {
				return 1;
			}
			break;
		case OPENLOCAL:
			if (QDesktopServices::openUrl(QUrl::fromLocalFile((QString::fromUtf8(v1))))) {
				return 1;
			}
			break;

		case QPBSETLABELS:
		{
			QStringList ql;
			ql.push_back(QString::fromUtf8(v1));
			ql.push_back(QString::fromUtf8(v2));
			((QtTreePropertyBrowser*)handle)->setHeaderLabels(ql);
			return 1;
		}
			break;
        case TREEWIDGETADD:
        {
                QTreeWidget * twidget = (QTreeWidget *)handle;
                QTreeWidgetItem * item = 0;

                if (twidget != 0) {
                        item = new QTreeWidgetItem(twidget);
                }
                else {
                        item = new QTreeWidgetItem();
                }
                item->setText(0, QString::fromUtf8(v2));
                if (v1 != 0) {
                        item->setIcon(0, *loadIcon(QString::fromUtf8(v1)));
                }

                return (xlong)item;
        }
        break;
        case IMGLOAD:
        {
                QImage * pimage = new QImage();
                if (false == pimage->load(QString::fromUtf8(v1), v2)) {
                        delete pimage;
                        pimage = 0;
                }
                return (xlong)pimage;
                break;
        }
        case LOADFONT:
        {
                int fontId = QFontDatabase::addApplicationFont(QString::fromUtf8(v1));
                if (fontId != -1) {
                        QStringList list = QFontDatabase::applicationFontFamilies(fontId);
                        int id = 0;
                        if (v2 != 0) {
                                id = list.indexOf(QString::fromUtf8(v2));
                        }
                        return (xlong)new QFont(list.at(0));
                }
                break;
        }
		case LOADFONTDESCRIPTION:
		{
			QFont * ft = new QFont();
			ft->fromString(QString::fromUtf8(v1));
			return (xlong)ft;
			break;
		}
        default:
                break;
        }

        return 0;
}

XNLEXPORT xint XI_CDECL long_string2_int2(xlong handle, xint proid, xstring v1, xstring v2, xint flags, xint flags2) {
        switch (proid)
        {
        case MESSAGEBOXWAR:
                return (xint)QMessageBox::warning((QWidget*)handle, QString::fromUtf8(v1), QString::fromUtf8(v2), (QMessageBox::StandardButton)flags, (QMessageBox::StandardButton)flags2);
                break;
        case MESSAGEBOXERR:
                return (xint)QMessageBox::critical((QWidget*)handle, QString::fromUtf8(v1), QString::fromUtf8(v2), (QMessageBox::StandardButton)flags, (QMessageBox::StandardButton)flags2);
                break;
        case MESSAGEBOXINF:
                return (xint)QMessageBox::information((QWidget*)handle, QString::fromUtf8(v1), QString::fromUtf8(v2), (QMessageBox::StandardButton)flags, (QMessageBox::StandardButton)flags2);
                break;
        case MESSAGEBOXABT:
                QMessageBox::about((QWidget*)handle, QString::fromUtf8(v1), QString::fromUtf8(v2));
                break;
        case MESSAGEBOXQUE:
                return (xint)QMessageBox::question((QWidget*)handle, QString::fromUtf8(v1), QString::fromUtf8(v2), (QMessageBox::StandardButton)flags, (QMessageBox::StandardButton)flags2);
                break;
		case SCICMD:
				return ((QsciScintilla*)handle)->SendScintilla(flags, v1, v2);
			break;
        default:
                break;
        }

        return 0;
}

XNLEXPORT xlong XI_CDECL long_long_string2(xlong handle, xint proid, xlong l1, xstring v1, xstring v2) {
        switch (proid)
        {
        case TREEWIDGETINST:
        {
                QTreeWidgetItem * parent = (QTreeWidgetItem *)l1;
                //QTreeWidget * twidget = (QTreeWidget *)handle;
                QTreeWidgetItem * item = new QTreeWidgetItem();
                item->setText(0, QString::fromUtf8(v2));
                if (v1 != 0) {
                        item->setIcon(0, *loadIcon(QString::fromUtf8(v1)));
                }
                parent->addChild(item);
                return (xlong)item;
        }
        break;
		case TABLESETITEM:
		{
			int line = (l1 >> 32) & 0xffffffff;
			int row = l1 & 0xffffffff;
			QTableWidgetItem * pitem = 0;
			
			if (v1 != 0) {
				pitem = new QTableWidgetItem(*loadIcon(QString::fromUtf8(v1)), QString::fromUtf8(v2));
			}
			else {
				pitem = new QTableWidgetItem(QString::fromUtf8(v2));
			}
			((QTableWidget*)handle)->setItem(line, row, pitem);
			return (xlong)pitem;
		}
			break;
		case QIMGSAVE:
		{
			QImage * pimg = (QImage*)handle;
			QString filename = QString::fromUtf8(v1);
			return pimg->save(filename, v2, l1) ? 1: 0;
		}
			break;
        default:
                break;
        }

        return 0;
}

XNLEXPORT xlong XI_CDECL long_get(xlong handle, xint proid) {
        switch (proid)
        {

        case TREEWIDGETGETSEL:
        {
                QTreeWidget * twidget = (QTreeWidget *)handle;
                return (xlong)twidget->currentItem();
        }
        break;
        case TREEITEMPARENT:
        {
                QTreeWidgetItem * twidget = (QTreeWidgetItem *)handle;
                if (twidget != 0) {
                        return (xlong)twidget->parent();
                }
        }
        break;
        case PAINTERGETMATRIX:
        {
                QPainter * m = (QPainter *)handle;
                return (xlong) new QMatrix(m->matrix());
        }
        break;
        case PAINTERGETFCONT:
        {
                QPainter * m = (QPainter *)handle;
                return (xlong) new QFont(m->font());
        }
        break;
        case PAINTERFROMIMG:
        {
                QImage * pimg = (QImage *)handle;
                return (xlong)new QPainter(pimg);
        }
        break;
        default:
                break;
        }

        return 0;
}

XNLEXPORT void XI_CDECL widget_set_intlongstring_value(xlong h, xint proid, xlong xv, xint yv, xstring zv) {
        switch (proid)
        {

        case SETITEMTEXT:
        {
                QTreeWidgetItem * parent = (QTreeWidgetItem *)xv;
                if (parent != 0) {
                        parent->setText(yv, QString::fromUtf8(zv));
                }
        }
        break;
		case SETTABLEITEMTEXT:
		{
			QTableWidgetItem * parent = (QTableWidgetItem *)xv;
			if (parent != 0) {
				parent->setText(QString::fromUtf8(zv));
			}
		}
		break;
		case SETTABLEITEMICON:
		{
			QTableWidgetItem * parent = (QTableWidgetItem *)xv;
			if (parent != 0) {
				parent->setIcon(*loadIcon(QString::fromUtf8(zv)));
			}
		}
		break;
        case SETITEMICON:
        {
                QTreeWidgetItem * parent = (QTreeWidgetItem *)xv;
                if (parent != 0) {
                        parent->setIcon(yv, *loadIcon(QString::fromUtf8(zv)));
                }
        }

        break;
		case SHOWTOOLTIPS:
		{
			if (zv == 0 && h != 0) {
				QToolTip::showText(QPoint((xv >> 32) & 0xffffffff, xv & 0xffffffff), ((QWidget*)h)->toolTip(), (QWidget*)h, QRect(), yv);
			}
			else
			if (zv != 0) {
				QToolTip::showText(QPoint((xv >> 32) & 0xffffffff, xv & 0xffffffff), QString::fromUtf8(zv), (QWidget*)h, QRect(), yv);
			}
		}

		break;
        default:
                break;

        }
}


XNLEXPORT XObject * XI_CDECL core_getStringlongint(xlong h, xint proid, xlong v1, xint v2) {
        QByteArray qba;

        switch (proid)
        {
        case TRGETITEMTEXT:
            qba = ((QTreeWidgetItem *)v1)->text(v2).toUtf8();
        break;
        case QSCIGETRANGE:
			if (v2 > v1) {
				qba = ((QsciScintilla*)h)->text(v1, v2).toUtf8();
			}
            break;
		case TABLEGETTEXTBYRC:
			qba = ((QTableWidget*)h)->item(v1, v2)->text().toUtf8();
			break;
		case TABLEGETTEXTBYITEM:
			qba = ((QTableWidgetItem*)h)->text().toUtf8();
			break;
        default:
            break;

        }

        return data2String(qba);
}

XNLEXPORT void XI_CDECL widget_set_intlongint_value(xlong h, xint proid, xlong xv, xint yv, xint zv) {
        switch (proid)
        {
		case TRSETFOREBR:
		{
			QTreeWidgetItem * parent = (QTreeWidgetItem *)h;
			parent->setForeground(yv, *(QBrush*)xv);
		}
		break;
		case TRSETBACKBR:
		{
			QTreeWidgetItem * parent = (QTreeWidgetItem *)h;
			parent->setBackground(yv, *(QBrush*)xv);
		}
		break;
        case SETITEMCOLOR:
        {
                QTreeWidgetItem * parent = (QTreeWidgetItem *)xv;
                parent->setTextColor(yv, QMakeColor(zv));
        }
        break;
		case SETTABLEITEMCOLOR:
		{
			QTableWidgetItem * parent = (QTableWidgetItem *)xv;
			parent->setTextColor(QMakeColor(zv));
		}
		break;
        case SETBACKCOLOR:
        {
                QTreeWidgetItem * parent = (QTreeWidgetItem *)xv;
                parent->setBackgroundColor(yv, QMakeColor(zv));
        }
        break;
		case SETTABLEITEMBACKCOLOR:
		{
			QTableWidgetItem * parent = (QTableWidgetItem *)xv;
			parent->setBackgroundColor(QMakeColor(zv));
		}
		break;
        case ADDWIDGET:
        {
                ((QStatusBar*)h)->addWidget((QWidget*)xv, yv);
        }
                break;

        case ADDPERWIDGET:
        {
                ((QStatusBar*)h)->addPermanentWidget((QWidget*)xv, yv);
        }
                break;
        case DRAWIMAGE:
        {
                ((QPainter*)h)->drawImage(QPoint(yv, zv), *(QImage*)xv);
        }
                break;
		case TOOLBARADDWIDGET:
			((QToolBar*)h)->addWidget((QWidget*)xv);
			break;
		case TABLESETCELLWIDGET:
		{
			((QTableWidget*)h)->setCellWidget(yv, zv, (QWidget*)xv);
		}
		break;

        default:
                break;
        }
}

XNLEXPORT void XI_CDECL widget_set_int2_object_value(xlong h, xint proid, xint id, xint iv, XObject * value) {
        switch (proid)
        {
        case SCICMD:
        {
                if (id == QsciScintilla::SCI_AUTOCSHOW) {
                        if (gs_env->isArray(value)) {
                                QStringList wlist;
                                xlong size = gs_env->getLengthOfArray(value);
								const char ** text = new const char *[size];
								size_t* length = new size_t[size];

								if (gs_env->getElementValue(value, 0, text, length, size)) {
									for (xlong i = 0; i < size; i++) {
										wlist.push_back(QString::fromUtf8(text[i], length[i]));
									}
								}
								delete[]text;
								delete[]length;

                                wlist.sort();

                                ((QsciScintilla*)h)->SendScintilla(QsciScintilla::SCI_AUTOCSETCHOOSESINGLE, true);
                                ((QsciScintilla*)h)->SendScintilla(QsciScintilla::SCI_AUTOCSETSEPARATOR, (const char)'\x03');

                                QByteArray wlist_s = wlist.join(QChar((const char)'\x03')).toUtf8();
                                ((QsciScintilla*)h)->SendScintilla((int)QsciScintilla::SCI_AUTOCSHOW, (char*)0, ScintillaBytesConstData(wlist_s));

                        }
                }
        }
        }
}

XNLEXPORT void XI_CDECL widget_set_long_object_value(xlong h, xint proid, xlong ph, XObject * value) {
        switch (proid)
        {
                case PROPSETENUM:
                {
                        QtEnumPropertyManager * twidget = (QtEnumPropertyManager *)h;

                        if (gs_env->isArray(value)) {
                                QStringList columns;
                                xlong size = gs_env->getLengthOfArray(value);
								const char ** text = new const char *[size];
								size_t * length = new size_t[size];
								gs_env->getElementValue(value, 0, text, length, size);
                                for (size_t i = 0; i < size; i++) {
                                   columns.push_back(QString::fromUtf8(text[i], length[i]));
                                }
								delete[] text;
								delete []length;
                                twidget->setEnumNames((QtProperty*)ph, columns);
                        }
                }
        }
}



XNLEXPORT void XI_CDECL widget_set_object_value(xlong h, xint proid, XObject * value) {
        switch (proid)
        {
        case PROPSETVALUE:
        {
                int type = gs_env->getObjectType(value);
                switch (type)
                {
                case XNLEnv::t_byte:
                case XNLEnv::t_short:
                case XNLEnv::t_char:
                case XNLEnv::t_int:
                case XNLEnv::t_long:
                {
                        xint v;
                        gs_env->getIntValue(value, &v);
                        ((QtVariantProperty *)h)->setValue(v);
                }
                break;
                case XNLEnv::t_string:
                {
                        const char * str = 0;
                        int length = 0;;
                        gs_env->getStringValue(value, &str, &length);
                        ((QtVariantProperty *)h)->setValue(QString::fromUtf8(str, length));
                }
                break;
                case XNLEnv::t_bool:
                {
                        bool v;
                        gs_env->getBoolValue(value, &v);
                        ((QtVariantProperty *)h)->setValue(v);
                }
                break;
                case XNLEnv::t_double:
                {
                        double v;
                        gs_env->getDoubleValue(value, &v);
                        ((QtVariantProperty *)h)->setValue(v);
                }
                break;
                default:
                        break;
                }
        }
                break;
        case SETCOLUMNS:
        {
                QTreeWidget * twidget = (QTreeWidget *)h;

                if (gs_env->isArray(value)) {
                        QStringList columns;
                        xlong size = gs_env->getLengthOfArray(value);
						const char ** text = new const char *[size];
						size_t *length = new size_t[size];

						if (gs_env->getElementValue(value, 0, text, length, size)) {
							for (xlong i = 0; i < size; i++) {
                                columns.push_back(QString::fromUtf8(text[i], length[i]));
                            }
                        }
						delete[] text;
						delete[]length;

                        twidget->setHeaderLabels(columns);
                        twidget->setColumnCount(columns.size());
                }
        }
        break;
		case SETTABHHCOLUMNS:
		{
			QTableWidget * twidget = (QTableWidget *)h;

			if (gs_env->isArray(value)) {
				QStringList columns;
				xlong size = gs_env->getLengthOfArray(value);
				const char ** text = new const char *[size];
				size_t *length = new size_t[size];

				if (gs_env->getElementValue(value, 0, text, length, size)) {
					for (xlong i = 0; i < size; i++) {
						columns.push_back(QString::fromUtf8(text[i], length[i]));
					}
				}
				delete[] text;
				delete[]length;

				twidget->setHorizontalHeaderLabels(columns);
				//
			}
		}
		break;
		case SETTABVHCOLUMNS:
		{
			QTableWidget * twidget = (QTableWidget *)h;

			if (gs_env->isArray(value)) {
				QStringList columns;
				xlong size = gs_env->getLengthOfArray(value);
				const char ** text = new const char *[size];
				size_t *length = new size_t[size];

				if (gs_env->getElementValue(value, 0, text, length, size)) {
					for (xlong i = 0; i < size; i++) {
						columns.push_back(QString::fromUtf8(text[i], length[i]));
					}
				}
				delete[] text;
				delete[]length;

				twidget->setVerticalHeaderLabels(columns);
				//twidget->setColumnCount(columns.size());
			}
		}
		break;
        case ADDDEFACTION:
        {
                QWidget * twidget = (QWidget *)h;

                if (gs_env->isArray(value)) {
                        QList<QAction*> actions;
                        xlong size = gs_env->getLengthOfArray(value);
						xlong *v = new xlong[size];

						if (gs_env->getElementValue(value, 0, v, (size_t)size)) {
							 for (xlong i = 0; i < size; i++) {
                                  actions.push_back((QAction*)v[i]);
                                  ar.installAction((QAction*)v[i]);
                             }
                        }
						delete[] v;
                        twidget->addActions(actions);
                }
        }
        break;

        break;
        case SETTAG:
        {
                XObjectData * objectData = (XObjectData *)((QObject*)h)->userData(Qt::UserRole);
                if (objectData == 0) {
                        objectData = new XObjectData();
                        ((QObject*)h)->setUserData(Qt::UserRole, objectData);
                }

                objectData->setTag(gs_env->referenceObject( value));
        }
        break;
        case PROPATTRCONST :// 129,
                break;
        case PROPATTRSSTEP :// 130,
        {
                int type = gs_env->getObjectType(value);
                if (type == XNLEnv::t_double) {
                        double v;
                        gs_env->getDoubleValue(value, &v);
                        ((QtVariantProperty *)h)->setAttribute("singleStep", v);
                }
                else {
                        xint v;
                        gs_env->getIntValue(value, &v);
                        ((QtVariantProperty *)h)->setAttribute("singleStep", v);
                }
        }
                break;
        case PROPATTRDECIM :// 131,
        {
                xint v;
                gs_env->getIntValue(value, &v);
                ((QtVariantProperty *)h)->setAttribute("decimals", v);

        }
        break;
        case PROPATTRENUMI :// 132,
        {

        }
        break;
        case PROPATTRENUMN :// 133,
        {

                if (gs_env->isArray(value)) {
                        QStringList enumNames;
                        xlong size = gs_env->getLengthOfArray(value);
						const char ** text = new const char *[size];
						size_t * length = new size_t[size];

						if (gs_env->getElementValue(value, 0, text, length, size)) {
							for (xlong i = 0; i < size; i++) {
                                 enumNames.push_back(QString::fromUtf8(text[i], length[i]));
                            }
                        }
						delete[] text;
						delete[] length;
                        ((QtVariantProperty *)h)->setAttribute(QLatin1String("enumNames"), enumNames);
                }
        }
        break;
        case PROPATTRFLAGN :// 134,
        {

                if (gs_env->isArray(value)) {
					QStringList enumNames;
					extartStringArray(value, enumNames);
                    ((QtVariantProperty *)h)->setAttribute(QLatin1String("flagNames"), enumNames);
                }
        }
        break;
        case COMBOBOXADD:// 134,
        {

                if (gs_env->isArray(value)) {
                    QStringList enumNames;
					extartStringArray(value, enumNames);
                    ((QComboBox *)h)->addItems(enumNames);
                }
        }
        break;
        case PROPATTRMAXIM :// 135,
        {
                int type = gs_env->getObjectType(value);
                if (type == XNLEnv::t_double) {
                        double v;
                        gs_env->getDoubleValue(value, &v);
                        ((QtVariantProperty *)h)->setAttribute("maximum", v);
                }
                else {
                        xint v;
                        gs_env->getIntValue(value, &v);
                        ((QtVariantProperty *)h)->setAttribute("maximum", v);
                }
        }
        break;
        case PROPATTRMINIM :// 136,
        {
                int type = gs_env->getObjectType(value);
                if (type == XNLEnv::t_double) {
                        double v;
                        gs_env->getDoubleValue(value, &v);
                        ((QtVariantProperty *)h)->setAttribute("minimum", v);
                }
                else {
                        xint v;
                        gs_env->getIntValue(value, &v);
                        ((QtVariantProperty *)h)->setAttribute("minimum", v);
                }
        }
        break;
        case PROPATTRREGEX :// 137,
        {
                int type = gs_env->getObjectType(value);
                if (type == XNLEnv::t_string) {
                        const char* v = 0;
                        int length = 0;
                        gs_env->getStringValue(value, &v, &length);
                        ((QtVariantProperty *)h)->setAttribute("regExp", QString::fromUtf8(v, length));
                }
        }
        break;
        case PROPATTRECHOM :// 138,
        {
                int type = gs_env->getObjectType(value);
                xint v;
                gs_env->getIntValue(value, &v);
                ((QtVariantProperty *)h)->setAttribute("echoMode", v);
        }
        break;
        case LOADSTATE:// 133,
        {

                if (gs_env->isArray(value)) {
                        QByteArray data;
						extartByteArray(value, data);
                        ((QMainWindow *)h)->restoreState(data);
                }
        }
        break;
        default:
                break;
        }
}

XNLEXPORT void XI_CDECL object_set_long_int_long(xlong h, xint proid, xlong hv,int iv, xlong h1) {
        switch (proid)
        {
        case SETTAG:
        {
                QTreeWidgetItem * obj = (QTreeWidgetItem*)hv;
                obj->setData(iv, Qt::UserRole, h1);
        }
                break;
		case TABLESETTAG:
		{
			QTableWidgetItem * obj = (QTableWidgetItem*)hv;
			obj->setData(Qt::UserRole, h1);
		}
		break;
        default:
                break;
        }
}

XNLEXPORT xlong XI_CDECL long_double2(xlong h, xint proid, double v1, double v2) {
        switch (proid)
        {
                case MATRIXTRANSLATE:
                {
                        return (xlong)new QMatrix(((QMatrix*)h)->translate(v1, v2));
                }
                break;
                case MATRIXSCALE:
                {
                        return (xlong)new QMatrix(((QMatrix*)h)->scale(v1, v2));
                }
                break;
                case MATRIXSHEAR:
                {
                        return (xlong)new QMatrix(((QMatrix*)h)->shear(v1, v2));
                }
                break;
                case MATRIXROTATE:
                {
                        return (xlong)new QMatrix(((QMatrix*)h)->rotate(v1));
                }
                break;
        }
        return 0;
}

XNLEXPORT xlong XI_CDECL object_get_long_int(xlong h, xint proid, xlong hv, int iv) {
        switch (proid)
        {
        case GETTAG:
        {
                QTreeWidgetItem * obj = (QTreeWidgetItem*)hv;
                QVariant v = obj->data(iv, Qt::UserRole);
                return v.value<xlong>();
        }
        break;
		case TABLEGETTAG:
		{
			QTableWidgetItem * obj = (QTableWidgetItem*)hv;
			QVariant v = obj->data(Qt::UserRole);
			return v.value<xlong>();
		}
		break;
        case MATRIXMUL:
        {
                QMatrix * obj = (QMatrix*)h;
                QMatrix * mbj = (QMatrix*)hv;
                return (xlong)new QMatrix(obj->operator*(*mbj));
        }
        break;
        case MATRIXMAPPOINT:
        {
                QMatrix * obj = (QMatrix*)h;
                QPoint pt = obj->map(QPoint(hv, iv));
                xlong rt = pt.x();
                rt <<= 32;
                rt |= (pt.y() & 0xffffffff);
                return rt;
        }
        break;
        case SCREENPOSITION:
        {
                QDesktopWidget * desktop = QApplication::desktop();
                int current_screen = hv;
                if (current_screen == -1) {
                        current_screen = desktop->screenNumber((QWidget*)h);
                }else
                if (current_screen >= desktop->screenCount()) {
                        return 0;
                }
                //获取程序所在屏幕的尺寸
                QRect rect = desktop->screenGeometry(current_screen);
                xlong v = rect.left();
                v <<= 32;
                v |= (rect.top() & 0xffffffff);
                return v;
        }
        break;
        case SCREENSIZE:
        {
                QDesktopWidget * desktop = QApplication::desktop();
                int current_screen = hv;
                if (current_screen == -1) {
                        current_screen = desktop->screenNumber((QWidget*)h);
                }else
                if (current_screen >= desktop->screenCount()) {
                        return 0;
                }
                //获取程序所在屏幕的尺寸
                QRect rect = desktop->screenGeometry(current_screen);
                xlong v = rect.width();
                v <<= 32;
                v |= (rect.height() & 0xffffffff);
                return v;
        }
        break;
		case GETTOPITEM:
		{
				QTreeWidget * obj = (QTreeWidget*)h;
				return (xlong)obj->topLevelItem(hv);
		}
			break;
		case TABLEGETITEM:
		{
			QTableWidget * obj = (QTableWidget*)h;
			return (xlong)obj->item(hv, iv);
		}
		break;
        default:
                break;
        }
        return 0;
}

XNLEXPORT xbool XI_CDECL string_bool5_int2_bool2(xlong handle,xint proid, xstring text, xbool regex, xbool bCase, xbool bWholeWord, xbool warp, xbool forward, xint startLine, xint startIndex, xbool show, xbool posix) {
        switch (proid)
        {
        case SCIFINDFIRST:
                return ((QsciScintilla*)handle)->findFirst(QString::fromUtf8(text), regex, bCase, bWholeWord, warp, forward, startLine, startIndex, show, posix);
                break;
        default:
                break;
        }
        return false;
}

XNLEXPORT xlong XI_CDECL long_intstring(xlong handle, xint proid, xint type, xstring v1) {

        switch (proid)
        {
        case PROPADDPROPERTY:
                return (xlong)((QtVariantPropertyManager*)handle)->addProperty(type, QString::fromUtf8(v1));
                break;
        case PROPADDPROPERTYGROUP:
                return (xlong)((QtVariantPropertyManager*)handle)->addProperty(QtVariantPropertyManager::groupTypeId(), QString::fromUtf8(v1));
                break;
        case PROPADDPROPERTYENUM:
                return (xlong)((QtVariantPropertyManager*)handle)->addProperty(QtVariantPropertyManager::enumTypeId(), QString::fromUtf8(v1));
                break;
        case PROPADDPROPERTYFLAG:
                return (xlong)((QtVariantPropertyManager*)handle)->addProperty(QtVariantPropertyManager::flagTypeId(), QString::fromUtf8(v1));
                break;
        default:
                break;
        }
        return 0;
}

XNLEXPORT xlong XI_CDECL long_intlong(xlong handle, xint proid, xlong value) {

        switch (proid)
        {
        case ADDPROPERTY:
                return (xlong)((QtTreePropertyBrowser*)handle)->addProperty((QtProperty*)value);
                break;
        case BUFFERSETDATA:
                ((QBuffer*)handle)->setData(*(QByteArray*)value);
                break;
        default:
                break;
        }
        return 0;
}



XNLEXPORT xlong XI_CDECL long_intlong2(xlong handle, xint proid, xlong value, xlong v1) {

        switch (proid)
        {

        case MAPPOINT:
        {
                QPoint opt(v1 >> 32 & 0xffffffff, v1 & 0xffffffff);
                QPoint npt;
                if (handle == 0 && value != 0) {
                        npt = ((QWidget*)value)->mapFromGlobal(opt);
                }else
                if (value == 0) {
                        npt = ((QWidget*)handle)->mapToGlobal(opt);
                }else {
                        npt = ((QWidget*)handle)->mapTo((QWidget*)value, opt);
                }
                xlong ret = npt.x();
                ret <<= 32;
                ret |= (npt.y() & 0xffffffff);
                return ret;
        }
                break;

        case IMGLOAD:
        {
                int width = (value >> 32) & 0xffffffff;
                int height = (value & 0xffffffff);

				QImage * qm = 0;
				if (handle == 0) {
					qm = new QImage(width, height, (QImage::Format)v1);
					qm->fill(Qt::GlobalColor::transparent);
				}
				else {
					uchar * pbuf = new uchar[width * height * 4];
					memcpy(pbuf, (uchar*)handle, width * height * 4);
					qm = new QImage(pbuf, width, height, (QImage::Format)v1, CleanupQImage, pbuf);
				}
                
                return (xlong)qm;
        }
                break;

        default:
                break;

        }
        return 0;
}


XNLEXPORT xlong XI_CDECL pointer_intlong2(void* handle, xint proid, xlong value, xlong v1) {

	switch (proid)
	{

	case IMGLOAD:
	{
		int width = (value >> 32) & 0xffffffff;
		int height = (value & 0xffffffff);

		QImage * qm = 0;
		if (handle == 0) {
			qm = new QImage(width, height, (QImage::Format)v1);
			qm->fill(Qt::GlobalColor::transparent);
		}
		else {
			uchar * pbuf = new uchar[width * height * 4];
			memcpy(pbuf, (uchar*)handle, width * height * 4);
			qm = new QImage(pbuf, width, height, (QImage::Format)v1, CleanupQImage, pbuf);
		}

		return (xlong)qm;
	}
	break;


	case PATHMOVETO: {
		double * pd = (double *)handle;
		QPainterPath * pp = (QPainterPath*)value;
		pp->moveTo(pd[0], pd[1]);
	}
		break;

	case PATHLINETO: {
		double * pd = (double *)handle;
		QPainterPath * pp = (QPainterPath*)value;
		pp->lineTo(pd[0], pd[1]);
	}
		break;

	case PATHARCMOVETO: {
		double * pd = (double *)handle;
		QPainterPath * pp = (QPainterPath*)value;
		pp->arcMoveTo(pd[0], pd[1], pd[2] - pd[0], pd[3] - pd[1], pd[4]);
	}
		break;

	case PATHARCTO:{
		double * pd = (double *)handle;
		QPainterPath * pp = (QPainterPath*)value;
		pp->arcTo(pd[0], pd[1], pd[2] - pd[0], pd[3] - pd[1], pd[4], pd[5]);
	}
		break;

	case CUBICTO: {
		double * pd = (double *)handle;
		QPainterPath * pp = (QPainterPath*)value;
		pp->cubicTo(pd[0], pd[1], pd[2], pd[3], pd[4], pd[5]);
	}
		break;

	case QUADTO: {
		double * pd = (double *)handle;
		QPainterPath * pp = (QPainterPath*)value;
		pp->quadTo(pd[0], pd[1], pd[2], pd[3]);
	}
		break;

	case ADDRECT: {
		double * pd = (double *)handle;
		QPainterPath * pp = (QPainterPath*)value;
		pp->addRect(pd[0], pd[1], pd[2] - pd[0], pd[3] - pd[1]);
	}
		break;

	case ADDELLIPSE: {
		double * pd = (double *)handle;
		QPainterPath * pp = (QPainterPath*)value;
		pp->addEllipse(pd[0], pd[1], pd[2] - pd[0], pd[3] - pd[1]);
	}
		break;

	default:
		break;

	}
	return 0;
}


XNLEXPORT void XI_CDECL void_long2(xlong handle, xint proid, xlong value1, xlong v2) {
        switch (proid)
        {
        case SETMGRFACTORY:
                ((QtTreePropertyBrowser*)handle)->setFactoryForManager((QtAbstractPropertyManager*)value1, (QtAbstractEditorFactory<QtAbstractPropertyManager>*)v2);
                break;

		case TOOLBARINSWIDGET:
				((QToolBar*)handle)->insertWidget((QAction*)value1, (QWidget*)v2);
			break;

        default:
                break;
        }
}

XNLEXPORT void XI_CDECL native_double2(xlong h, xint proid, double v1, double v2) {
        switch (proid)
        {
        case PROPSETARRTSZMAX:
                ((QtVariantProperty *)h)->setAttribute("maximum", QSize(v1, v2));
                break;
        case PROPSETARRTSZMIN:
                ((QtVariantProperty *)h)->setAttribute("minimum", QSize(v1, v2));
                break;
        case PROPSETARRTPTMAX:
                ((QtVariantProperty *)h)->setAttribute("maximum", QPoint(v1, v2));
                break;
        case PROPSETARRTPTMIN:
                ((QtVariantProperty *)h)->setAttribute("minimum", QPoint(v1, v2));
                break;
        case PROPSETVALUEPT:
                ((QtVariantProperty *)h)->setValue(QPoint(v1, v2));
                break;
        case PROPSETVALUESZ:
                ((QtVariantProperty *)h)->setValue(QSize(v1, v2));
                break;
        default:
                break;
        }
}

XNLEXPORT void XI_CDECL native_double4(double v1, double v2, double v3, double v4, xlong h, xint proid) {
        switch (proid)
        {
        case PROPSETARRTRC:
                ((QtVariantProperty *)h)->setAttribute("constraint", QRect(v1, v2, v3, v4));
                break;
        case PROPSETVALUERC:
                ((QtVariantProperty *)h)->setValue(QRect(v1, v2, v3, v4));
                break;
        default:
                break;
        }
}

XNLEXPORT xint XI_CDECL int_long_int_long_int_int(xlong h, xint proid, xlong h1, xint v1, xint v2) {
        switch (proid)
        {
        case INSERTWIDGET:
                return ((QStatusBar *)h)->insertWidget(v2, (QWidget*)h1, v1);
                break;
        case INSERTPERWIDGET:
                return ((QStatusBar *)h)->insertPermanentWidget(v2, (QWidget*)h1, v1);
                break;
        default:
                break;
        }
        return 0;
}
