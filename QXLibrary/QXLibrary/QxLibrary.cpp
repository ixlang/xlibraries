#include "qxlibrary_global.h"
#include "QXApplication.h"

//#include<QtPlugin>  // for release



#ifdef WIN32
#include <conio.h>
#include <codecvt>
#endif
#include <stdio.h>
#include <locale>

#include <assert.h>
#ifndef MOBILE_APP

Q_IMPORT_PLUGIN(QGifPlugin) //for releas
Q_IMPORT_PLUGIN(QICNSPlugin) //for releas
Q_IMPORT_PLUGIN(QICOPlugin) //for releas
Q_IMPORT_PLUGIN(QJpegPlugin) //for releas


Q_IMPORT_PLUGIN(QTgaPlugin) //for releas
Q_IMPORT_PLUGIN(QTiffPlugin) //for releas
Q_IMPORT_PLUGIN(QWbmpPlugin) //for releas
Q_IMPORT_PLUGIN(QWebpPlugin) //for releas
#ifdef WIN32
#include <QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
Q_IMPORT_PLUGIN(QWindowsPrinterSupportPlugin) //for releas
#elif defined(__linux__)
//#ifdef __arm__
//#include <QtPlugin>
//Q_IMPORT_PLUGIN(QLinuxFbIntegrationPlugin)
//#else
#include <QtPlugin>
//Q_IMPORT_PLUGIN(QFcitxPlatformInputContextPlugin)
Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
//#endif
#elif defined(__APPLE__)
#include <QtPlugin>
Q_IMPORT_PLUGIN(QCocoaIntegrationPlugin)
#endif
#else
//#include <QtPlugin>
//Q_IMPORT_PLUGIN(QAndroidPlatformIntegrationPlugin)
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

#ifdef WIN32
#include <direct.h>
#include <io.h>
#include <conio.h>
#else
#include <sys/stat.h>
#endif


QColor QMakeColor(xint c) {
	QColor qc(c);
	qc.setAlpha((c >> 24) & 0xff);
	return qc;
}


#ifdef WIN32

bool CheckFileRelation(const char *strName, const char *strExt, const char *strAppKey) {

	bool nRet = false;
	HKEY hExtKey;
	char szPath[_MAX_PATH];
	DWORD dwSize = sizeof(szPath);

	if (RegOpenKeyA(HKEY_CLASSES_ROOT, strExt, &hExtKey) == ERROR_SUCCESS) {
		RegQueryValueExA(hExtKey, NULL, NULL, NULL, (LPBYTE)szPath, &dwSize);
		if (_stricmp(szPath, strAppKey) == 0) {
			nRet = true;
		}
		RegCloseKey(hExtKey);
		return nRet;
	}

	return nRet;
}

bool RegisterFileRelation(const char *strName, const char *strExt, const  char *strAppName, const char * args, const char *strAppKey, const char *strDefaultIcon, const char *strDescribe) {

	char strTemp[4096];
	HKEY hKey;
	int res = ERROR_SUCCESS;
	if (ERROR_SUCCESS != RegCreateKeyA(HKEY_CLASSES_ROOT, strExt, &hKey)) {
		return false;
	}
	res = RegSetValueA(hKey, "", REG_SZ, strAppKey, strlen(strAppKey) + 1);
	RegCloseKey(hKey);
	if (res != ERROR_SUCCESS) {
		return false;
	}

	if (ERROR_SUCCESS != RegCreateKeyA(HKEY_CLASSES_ROOT, strAppKey, &hKey)) {
		return false;
	}
	res = RegSetValueA(hKey, "", REG_SZ, strDescribe, strlen(strDescribe) + 1);
	RegCloseKey(hKey);
	if (res != ERROR_SUCCESS) {
		return false;
	}

	if (strDefaultIcon != 0) {
		sprintf(strTemp, "%s\\DefaultIcon", strAppKey);
		if (ERROR_SUCCESS != RegCreateKeyA(HKEY_CLASSES_ROOT, strTemp, &hKey)) {
			return false;
		}

		res = RegSetValueA(hKey, "", REG_SZ, strDefaultIcon, strlen(strDefaultIcon) + 1);
		RegCloseKey(hKey);
		if (res != ERROR_SUCCESS) {
			return false;
		}
	}
	if (strAppName != 0) {
		sprintf(strTemp, "%s\\Shell", strAppKey);
		if (ERROR_SUCCESS != RegCreateKeyA(HKEY_CLASSES_ROOT, strTemp, &hKey)) {
			return false;
		}
		res = RegSetValueA(hKey, "", REG_SZ, "Open", strlen("Open") + 1);
		RegCloseKey(hKey);
		if (res != ERROR_SUCCESS) {
			return false;
		}

		sprintf(strTemp, "%s\\Shell\\Open\\Command", strAppKey);
		if (ERROR_SUCCESS != RegCreateKeyA(HKEY_CLASSES_ROOT, strTemp, &hKey)) {
			return false;
		}
		if (args != 0) {
			sprintf(strTemp, "%s %s \"%%1\"", strAppName, args);
		}
		else {
			sprintf(strTemp, "%s \"%%1\"", strAppName);
		}
		res = RegSetValueA(hKey, "", REG_SZ, strTemp, strlen(strTemp) + 1);
		RegCloseKey(hKey);
		if (res != ERROR_SUCCESS) {
			return false;
		}
	}
	return true;
}



#elif defined(__linux__)
#include<unistd.h>

bool CheckFileRelation(const char *strName, const char *strExt, const char *strAppKey) {

	char buffer[1024];
	sprintf(buffer, "/usr/share/mime/packages/%s.xml", strName);
	if (access(buffer, 0) < 0) {
		return false;
	}

	sprintf(buffer, "/usr/share/applications/%s.desktop", strName);
	if (access(buffer, 0) < 0) {
		return false;
	}

	return true;
}

bool RegisterFileRelation(const char *strName, const char *strExt, const  char *strAppName, const char * args, const char *strAppKey, const char *strDefaultIcon, const char *strDescribe) {
	char buffer[1024];
	sprintf(buffer, "/usr/share/mime/packages/%s.xml", strName);
	FILE * fp = fopen(buffer, "wb");
	if (fp == 0) {
		return false;
	}

	const char * content = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
	fwrite(content, strlen(content), 1, fp);

	content = "<mime-info xmlns=\"http://www.freedesktop.org/standards/shared-mime-info\">\n";
	fwrite(content, strlen(content), 1, fp);

	sprintf(buffer, "  <mime-type type=\"%s\">\n", strAppKey);
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "    <comment>%s</comment>\n", strDescribe);
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "    <glob pattern=\"*%s\"/>\n", strExt);
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "    <sub-class-of type=\"application/xml\"/>\n", strExt);
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "  </mime-type>\n", strExt);
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "</mime-info>\n", strExt);
	fwrite(buffer, strlen(buffer), 1, fp);

	fclose(fp);


	sprintf(buffer, "/usr/share/applications/%s.desktop", strName);
	fopen(buffer, "wb");
	if (fp == 0) {
		return false;
	}

	sprintf(buffer, "%s\n", "[Desktop Entry]");
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "%s\n", "Version = 1.0");
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "%s\n", "Type=Application");
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "Name=%s\n", strName);
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "GenericName=%s\n", strDescribe);
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "Comment=%s\n", strDescribe);
	fwrite(buffer, strlen(buffer), 1, fp);

	if (args != 0) {
		sprintf(buffer, "Exec=\"%s\" %s %%F\n", strAppName, args);
		fwrite(buffer, strlen(buffer), 1, fp);
	}
	else {
		sprintf(buffer, "Exec=\"%s\" %%F\n", strAppName);
		fwrite(buffer, strlen(buffer), 1, fp);
	}

	if (strDefaultIcon != 0) {
		sprintf(buffer, "Icon=\"%s\"\n", strDefaultIcon);
		fwrite(buffer, strlen(buffer), 1, fp);
	}

	sprintf(buffer, "%s\n", "Terminal=false");
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "%s\n", "X-MultipleArgs=false");
	fwrite(buffer, strlen(buffer), 1, fp);

	/*sprintf(buffer, "%s\n", "Categories=Development;IDE;GTK;");
	fwrite(buffer, strlen(buffer), 1, fp);
	*/
	sprintf(buffer, "%s\n", "StartupNotify=true");
	fwrite(buffer, strlen(buffer), 1, fp);

	sprintf(buffer, "MimeType=%s;\n", strAppKey);
	fwrite(buffer, strlen(buffer), 1, fp);

	fclose(fp);

	system("update-mime-database /usr/share/mime");
	return true;

}
#endif

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


void checkMainThread(){
    if (QThread::currentThreadId() != ui_thread_id){
        XThread thread;
        gs_env->throwNativeException(thread.getThread(), "must from UIThread");
    }
}

XNLEXPORT xlong  XI_CDECL createQxApplication(XObject * x){
		
        _application = gs_env->referenceObject(x);

        int onNotifyId = gs_env->getMethodId("/bool@/Qt/QApplication/onNotify(/Qt/QObject,/String,/String,/long,/int)");
        onNotify = gs_env->getVirtualMethod(x, onNotifyId);
		if (onNotify == 0) {
			QString s;
			s.sprintf("can not found Method in xlang : %s", "/bool@/Qt/QApplication/onNotify(/Qt/QObject,/String,/String,/long,/int)");
			gs_env->throwNativeException(ui_thread, s.toUtf8().data());
		}

        onNotifyId = gs_env->getMethodId("/*@/Qt/QApplication/onCreateXObject(/long,/String)");
        createObject = gs_env->getVirtualMethod(x, onNotifyId);
		if (createObject == 0) {
			QString s;
			s.sprintf("can not found Method in xlang : %s", "/*@/Qt/QApplication/onCreateXObject(/long,/String)");
			gs_env->throwNativeException(ui_thread, s.toUtf8().data());
		}

        MAX_METHOD = getEventMaxCount();
        methodIdent = new XIDENT[MAX_METHOD];
		ui_thread = gs_env->getContext(&ui_release);

        memset(methodIdent, 0, sizeof(XIDENT) * MAX_METHOD);
        for (size_t i = 0; i < getEventSize(); i++) {
            XIDENT * pme = &methodIdent[megs[i].id];
            pme->path = methods[i].path;
            if (pme->path != NULL) {
                pme->methodId = gs_env->getMethodId(pme->path);
				if (pme->methodId == -1) {
					QString s;
					s.sprintf("can not found Method in xlang : %s", pme->path);
					gs_env->throwNativeException(ui_thread, s.toUtf8().data());
				}
            }
        }
		
		ui_thread_id = QThread::currentThreadId();
        if (_xapplication == 0){
            _xapplication = new QXApplication(global_argc, 0);
        }
		//uithreadid = GetCurrentThreadId();
        //qapp->installEventFilter(new QFilter());
		//qDebug() << "Supported formats:" << QImageReader::supportedImageFormats();
        return (xlong)_xapplication;
}

XNLEXPORT xlong  XI_CDECL locaUiFile(xstring path, XObject * x, xlong parent){
        checkMainThread();

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
        checkMainThread();

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
        checkMainThread();

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
        checkMainThread();
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


XNLEXPORT xlong  XI_CDECL createQPObject(xint type, XObject * x, xlong parent, xlong param1, xlong param2, xlong param3, xlong param4) {
	QObject * qobject = 0;
    checkMainThread();
	switch (type){
	case qtPrinter:
	{
		QPrinter * qw = new QPrinter((QPrinter::PrinterMode)param1);
		return (xlong)qw;
	}
	break;
	case qtSciPrinter:
	{
		QsciPrinter * qw = new QsciPrinter((QPrinter::PrinterMode)param1);
		return (xlong)qw;
	}
	break;
		case qtPrintDialog:
			if (parent != 0) {
				if (param1 != 0) {
					qobject = new QPrintDialog((QPrinter*)param1, (QWidget*)parent);
				}
				else {
					qobject = new QPrintDialog((QWidget*)parent);
				}
			}
			else {
				if (param1 != 0) {
					qobject = new QPrintDialog((QPrinter*)param1);
				}
				else {
					qobject = new QPrintDialog();
				}
			}

			ar.installDialogAction((QPrintDialog*)qobject);
			((QPrintDialog*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
			break;

		case qtPrintViewDialog:
			if (parent != 0) {
				if (param1 != 0) {
					qobject = new QPrintPreviewDialog((QPrinter*)param1, (QWidget*)parent);
				}
				else {
					qobject = new QPrintPreviewDialog((QWidget*)parent);
				}
			}
			else {
				qobject = new QPrintPreviewDialog();
			}
			ar.installDialogAction((QDialog*)qobject);
			ar.installPrintViewDialogAction((QPrintPreviewDialog*)qobject);
			((QPrintPreviewDialog*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
			break;
	}

	if (qobject != NULL) {
		XObjectData * objectData = new XObjectData();
		objectData->setObject(x);
		qobject->setUserData(Qt::UserRole, objectData);
	}

	return (xlong)qobject;
}

XNLEXPORT xlong  XI_CDECL createQObject(xint type, XObject * x, xlong parent) {
        checkMainThread();
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
			//ar.installFSWEvent(fsw);
			qobject = fsw;
		}
		break;

		case qtVLayout:
		{
			QVBoxLayout * fsw = new QVBoxLayout((QWidget*)parent);
			qobject = fsw;
		}
		break;

		case qtHLayout:
		{
			QHBoxLayout * fsw = new QHBoxLayout((QWidget*)parent);
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
                //ar.installSciAction((QsciScintilla*)qobject);
                ((QsciScintilla*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
                break;
        case qtPushButton:
                if (parent != 0) {
                        qobject = new QPushButton((QWidget*)parent);
                }
                else {
                        qobject = new QPushButton();
                }
               // ar.installButtonAction(qobject);
                break;

        case qtLineEdit:
                if (parent != 0) {
                        qobject = new QLineEdit((QWidget*)parent);
                }
                else {
                        qobject = new QLineEdit();
                }
               // ar.installEditAction(qobject);
                break;
		case qtSlider:
			if (parent != 0) {
				qobject = new QSlider((QWidget*)parent);
			}
			else {
				qobject = new QSlider();
			}
			//ar.installSliderAction(qobject);
			break;
		case qtTabBar:
			if (parent != 0) {
				qobject = new QTabBar((QWidget*)parent);
			}
			else {
				qobject = new QTabBar();
			}
			//ar.installSliderAction(qobject);
			break;
		case qtTabWidget:
			if (parent != 0) {
				qobject = new QTabWidget((QWidget*)parent);
			}
			else {
				qobject = new QTabWidget();
			}
			//ar.installSliderAction(qobject);
			break;
		case qtDockWidget:
			if (parent != 0) {
				qobject = new QDockWidget((QWidget*)parent);
			}
			else {
				qobject = new QDockWidget();
			}
			break;
		case qtTextEdit:
			if (parent != 0) {
				qobject = new QTextEdit((QWidget*)parent);
			}
			else {
				qobject = new QTextEdit();
			}
			//ar.installTextEditAction(qobject);
			break;
		case qtDateEdit:
			if (parent != 0) {
				qobject = new QDateEdit((QWidget*)parent);
			}
			else {
				qobject = new QDateEdit();
			}
			//ar.installDateTimeEditAction(qobject);
			break;
		case qtDateTimeEdit:
			if (parent != 0) {
				qobject = new QDateTimeEdit((QWidget*)parent);
			}
			else {
				qobject = new QDateTimeEdit();
			}
			//ar.installDateTimeEditAction(qobject);
			break;
		case qtTimeEdit:
			if (parent != 0) {
				qobject = new QTimeEdit((QWidget*)parent);
			}
			else {
				qobject = new QTimeEdit();
			}
			//ar.installDateTimeEditAction(qobject);
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
				//ar.installAction((QAction*)qobject);
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
                //ar.installTreeAction(qobject);
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
			//ar.installTableCellChange((QTableWidget*)qobject);
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
            //ar.installDialogAction((QDialog*)qobject);
            ((QDialog*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
            break;

        case qtComboBox:
            if (parent != 0) {
               qobject = new QComboBox((QWidget*)parent);
            }else{
               qobject = new QComboBox();
            }
			//ar.installComboBoxAction((QComboBox*)qobject);
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
			//ar.installBoolPropertyChange((QtBoolPropertyManager*)qobject);
            break;
        case qtColorPropertyManager :// 17,
            if (parent != 0) {
               qobject = new QtColorPropertyManager((QObject*)parent);
            }else{
               qobject = new QtColorPropertyManager();
            }
			//ar.installColorPropertyChange((QtColorPropertyManager*)qobject);
            break;
        case qtDatePropertyManager :// 18,
            if (parent != 0) {
               qobject = new QtDatePropertyManager((QObject*)parent);
            }else{
               qobject = new QtDatePropertyManager();
            }
			//ar.installDatePropertyChange((QtDatePropertyManager*)qobject);
            break;
        case qtDateTimePropertyManager :// 19,
            if (parent != 0) {
               qobject = new QtDateTimePropertyManager((QObject*)parent);
            }else{
               qobject = new QtDateTimePropertyManager();
            }
			//ar.installDateTimePropertyChange((QtDateTimePropertyManager*)qobject);
            break;
        case qtDoublePropertyManager :// 20,
            if (parent != 0) {
               qobject = new QtDoublePropertyManager((QObject*)parent);
            }else {
               qobject = new QtDoublePropertyManager();
            }
			//ar.installDoublePropertyChange((QtDoublePropertyManager*)qobject);
            break;
        case qtEnumPropertyManager :// 21,
            if (parent != 0) {
               qobject = new QtEnumPropertyManager((QObject*)parent);
            }else{
               qobject = new QtEnumPropertyManager();
            }
			//ar.installEnumPropertyChange((QtEnumPropertyManager*)qobject);
            break;
        case qtFlagPropertyManager :// 22,
            if (parent != 0) {
               qobject = new QtFlagPropertyManager((QObject*)parent);
            } else {
               qobject = new QtFlagPropertyManager();
            }
			//ar.installFlagPropertyChange((QtFlagPropertyManager*)qobject);
            break;
        case qtFontPropertyManager :// 23,
            if (parent != 0) {
               qobject = new QtFontPropertyManager((QObject*)parent);
            }else {
               qobject = new QtFontPropertyManager();
            }
			//ar.installFontPropertyChange((QtFontPropertyManager*)qobject);
            break;
        case qtGroupPropertyManager :// 24,
            if (parent != 0) {
               qobject = new QtGroupPropertyManager((QObject*)parent);
            }else {
               qobject = new QtGroupPropertyManager();
            }
			//ar.installGroupPropertyChange((QtGroupPropertyManager*)qobject);
            break;
        case qtIntPropertyManager :// 25,
            if (parent != 0) {
               qobject = new QtIntPropertyManager((QObject*)parent);
            }else {
               qobject = new QtIntPropertyManager();
            }
			//ar.installIntPropertyChange((QtIntPropertyManager*)qobject);
            break;
        case qtPointPropertyManager :// 26,
            if (parent != 0) {
               qobject = new QtPointPropertyManager((QObject*)parent);
            }else {
               qobject = new QtPointPropertyManager();
            }
			//ar.installPointPropertyChange((QtPointPropertyManager*)qobject);
            break;
        case qtRectPropertyManager :// 27,
            if (parent != 0) {
               qobject = new QtRectPropertyManager((QObject*)parent);
            }else {
               qobject = new QtRectPropertyManager();
            }
			//ar.installRectPropertyChange((QtRectPropertyManager*)qobject);
            break;
        case qtSizePropertyManager :// 28,
            if (parent != 0) {
               qobject = new QtSizePropertyManager((QObject*)parent);
            }else {
               qobject = new QtSizePropertyManager();
            }
			//ar.installSizePropertyChange((QtSizePropertyManager*)qobject);
            break;
        case qtSizePolicyPropertyManager :// 29,
            if (parent != 0) {
               qobject = new QtSizePolicyPropertyManager((QObject*)parent);
            }else {
               qobject = new QtSizePolicyPropertyManager();
            }
			//ar.installSizePolicyPropertyChange((QtSizePolicyPropertyManager*)qobject);
            break;
        case qtStringPropertyManager :// 30,
            if (parent != 0) {
               qobject = new QtStringPropertyManager((QObject*)parent);
            }else {
               qobject = new QtStringPropertyManager();
            }
			//ar.installStringPropertyChange((QtStringPropertyManager*)qobject);
            break;
        case qtTimePropertyManager :// 31,
            if (parent != 0) {
               qobject = new QtTimePropertyManager((QObject*)parent);
            }else {
               qobject = new QtTimePropertyManager();
            }
			//ar.installTimePropertyChange((QtTimePropertyManager*)qobject);
            break;
        case qtVariantPropertyManager :// 32,
            if (parent != 0) {
               qobject = new QtVariantPropertyManager((QObject*)parent);
            }else {
               qobject = new QtVariantPropertyManager();
            }
			//ar.installVariantPropertyChange((QtVariantPropertyManager*)qobject);
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
            //ar.installButtonAction(qobject);
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
		case qtReportEngine:
#ifndef MOBILE_APP
			if (parent != 0) {
				qobject = new LimeReport::ReportEngine((QObject*)parent);
			}else {
				qobject = new LimeReport::ReportEngine();
			}
			//ar.installReportView((LimeReport::ReportEngine*)qobject);
#endif
			break;
        default:
            break;
        }

        if (qobject != NULL) {

			installAction(qobject);

            XObjectData * objectData = new XObjectData();
            objectData->setObject(x);
            qobject->setUserData(Qt::UserRole, objectData);
        }

        return (xlong)qobject;
}

XNLEXPORT void XI_CDECL ShowUi(xlong widget){
        checkMainThread();
        QWidget* getWidget = (QWidget*)widget;
        getWidget->show();
}


XNLEXPORT void XI_CDECL ApplicationRun(xlong app) {
        checkMainThread();
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
        checkMainThread();
        switch (proid)
        {
		case BOXSETSPACING:
			((QBoxLayout*)h)->setSpacing(value);
			break;
		case BOXADDSPACING:
			((QBoxLayout*)h)->addSpacing(value);
			break;
		case BOXADDSTRETCH:
			((QBoxLayout*)h)->addStretch(value);
			break;
		case TABWIDGETSETCURRENTINDEX:
		{
			QTabWidget * pset = ((QTabWidget*)h);
			if (pset != 0) {
				pset->setCurrentIndex(value);
			}
		}
		break;
		case TABWIDGETSETELIDEMODE:
		{
			QTabWidget * pset = ((QTabWidget*)h);
			if (pset != 0) {
				pset->setElideMode((Qt::TextElideMode)value);
			}
		}
		break;
		case TABWIDGETSETTABSHAPE:
		{
			QTabWidget * pset = ((QTabWidget*)h);
			if (pset != 0) {
				pset->setTabShape((QTabWidget::TabShape)value);
			}
		}
		break;
		case TABWIDGETSETTABPOSITION:
		{
			QTabWidget * pset = ((QTabWidget*)h);
			if (pset != 0) {
				pset->setTabPosition((QTabWidget::TabPosition)value);
			}
		}
		break;
		case TABWIDGETREMOVETAB:
		{
			QTabWidget * pset = ((QTabWidget*)h);
			if (pset != 0) {
				pset->removeTab(value);
			}
		}
		break;
		case TABBARSETCURRENTINDEX:
		{
			QTabBar * pset = ((QTabBar*)h);
			if (pset != 0) {
				pset->setCurrentIndex(value);
			}
		}
		break;
		case TABBARSETSELECTIONBEHAVIORONREMOVE:
		{
			QTabBar * pset = ((QTabBar*)h);
			if (pset != 0) {
				pset->setSelectionBehaviorOnRemove((QTabBar::SelectionBehavior)value);
			}
		}
		break;
		case TABBARSETELIDEMODE:
		{
			QTabBar * pset = ((QTabBar*)h);
			if (pset != 0) {
				pset->setElideMode((Qt::TextElideMode)value);
			}
		}
		break;
		case TABBARREMOVETAB:
		{
			QTabBar * pset = ((QTabBar*)h);
			if (pset != 0) {
				pset->removeTab(value);
			}
		}
		break;
		case TABBARSETSHAPE:
		{
			QTabBar * pset = ((QTabBar*)h);
			if (pset != 0) {
				pset->setShape((QTabBar::Shape)value);
			}
		}
		break;
		case SLD_SETMIN:
		{
			QAbstractSlider * pset = ((QSlider*)h);
			if (pset != 0) {
				pset->setMinimum(value);
			}
		}
		break;
		case SLD_SETMAX:
		{
			QAbstractSlider * pset = ((QSlider*)h);
			if (pset != 0) {
				pset->setMaximum(value);
			}
		}
		break;
		case SLD_SETSINGLESTEP:
		{
			QAbstractSlider * pset = ((QSlider*)h);
			if (pset != 0) {
				pset->setSingleStep(value);
			}
		}
		break;
		case SLD_SETPAGESTEP:
		{
			QAbstractSlider * pset = ((QSlider*)h);
			if (pset != 0) {
				pset->setPageStep(value);
			}
		}
		break;
		case SLD_SETSLIDPOS:
		{
			QAbstractSlider * pset = ((QSlider*)h);
			if (pset != 0) {
				pset->setSliderPosition(value);
			}
		}
		break;
		case SLD_SETORIENTATION:
		{
			QAbstractSlider * pset = ((QSlider*)h);
			if (pset != 0) {
				pset->setOrientation((Qt::Orientation)value);
			}
		}
		break;
		case SLD_SETVALUE:
		{
			QAbstractSlider * pset = ((QSlider*)h);
			if (pset != 0) {
				pset->setValue(value);
			}
		}
		break;
		case SLD_TRIGGERACTION:
		{
			QAbstractSlider * pset = ((QSlider*)h);
			if (pset != 0) {
				pset->triggerAction((QAbstractSlider::SliderAction)value);
			}
		}
		break;
		case DOCKSETALLOWEDAREAS:
		{
			QDockWidget * pset = ((QDockWidget*)h);
			if (pset != 0) {
				pset->setAllowedAreas((Qt::DockWidgetAreas)value);
			}
		}
		break;
		case TESETLINEWRAPMODE:
		{
			QTextEdit * pset = ((QTextEdit*)h);
			if (pset != 0) {
				pset->setLineWrapMode((QTextEdit::LineWrapMode)value);
			}
		}
		break;
		case SETDOCKNESTINGENABLED:
		{
			QMainWindow * pset = ((QMainWindow*)h);
			if (pset != 0) {
				pset->setDockNestingEnabled(value ? true : false);
			}
		}
		break;
		case TEZOOMOUT:
		{
			QTextEdit * pset = ((QTextEdit*)h);
			if (pset != 0) {
				pset->zoomOut(value);
			}
		}
		break;
		case TEZOOMIN:
		{
			QTextEdit * pset = ((QTextEdit*)h);
			if (pset != 0) {
				pset->zoomIn(value);
			}
		}
		break;
		case TESETAUTOFORMATTING:
		{
			QTextEdit * pset = ((QTextEdit*)h);
			if (pset != 0) {
				pset->setAutoFormatting((QTextEdit::AutoFormatting)value);
			}
		}
		break;
        case TESETALIGNMENT:
		{
			QTextEdit * pset = ((QTextEdit*)h);
			if (pset != 0) {
				pset->setAlignment((Qt::Alignment)value);
			}
		}
		break;
		case TESETTEXTBACKGROUNDCOLOR:
		{
			QTextEdit * pset = ((QTextEdit*)h);
			if (pset != 0) {
				pset->setTextBackgroundColor(QMakeColor(value));
			}
		}
		break;
		case TESETTEXTCOLOR:
		{
			QTextEdit * pset = ((QTextEdit*)h);
			if (pset != 0) {
				pset->setTextColor(QMakeColor(value));
			}
		}
		break;
		case TESETFONTWEIGHT:
		{
			QTextEdit * pset = ((QTextEdit*)h);
			if (pset != 0) {
				pset->setFontWeight(value);
			}
		}
		break;
		case TESETWORDWRAPMODE:
		{
			QTextEdit * pset = ((QTextEdit*)h);
			if (pset != 0) {
				pset->setWordWrapMode((QTextOption::WrapMode)value);
			}
		}
		break;
		case PRINTERSETOUTFMT:
		{
			QPrinter * pset = ((QPrinter*)h);
			if (pset != 0) {
				pset->setOutputFormat((QPrinter::OutputFormat)value);
			}
		}
		break;
		case PRTDLGSETOPTS:
		{
			QPrintDialog * pset = ((QPrintDialog*)h);
			if (pset != 0) {
				pset->setOptions((QPrintDialog::PrintDialogOptions)value);
			}
		}
		break;
		case PRTDLGDONE:
		{
			QDialog * pset = ((QDialog*)h);
			if (pset != 0) {
				pset->done(value);
			}
		}
		break;
		case PVWDLGDONE:
		{
			QPrintPreviewDialog * pset = ((QPrintPreviewDialog*)h);
			if (pset != 0) {
				pset->done(value);
			}
		}
		break;
		case QSCIDISABLESHORTCUT:
		{
			QsciCommandSet * pset = ((QsciScintilla*)h)->standardCommands();
			if (pset != 0) {
				QsciCommand * pcmd = pset->find((QsciCommand::Command)value);
				if (pcmd != 0) {
					pcmd->setKey(0);
				}
			}
		}
			break;
		case QSCIUNBINDSHORTCUT:
		{
			QsciCommandSet * pset = ((QsciScintilla*)h)->standardCommands();
			if (pset != 0) {
				QsciCommand * pcmd = pset->boundTo(value);
				if (pcmd != 0) {
					pcmd->setKey(0);
				}
			}
		}
		break;
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
		case SHOWREPORT:
#ifndef MOBILE_APP
			return ((LimeReport::ReportEngine *)h)->previewReport(LimeReport::PreviewHint(value));
#endif
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


XNLEXPORT xlong XI_CDECL native_long2_string(xlong h, xint proid, xlong v0, xlong v, xlong v1, xstring v3) {
	switch (proid) {
	case TABWIDGETADDTAB:
		return ((QTabWidget*)h)->addTab((QWidget*)v0, *(QIcon*)v, QString::fromUtf8(v3));
		break;
	case TABWIDGETINSERTTAB:
		return ((QTabWidget*)h)->insertTab(v0, (QWidget*)v,  QString::fromUtf8(v3));
		break;
	case TABWIDGETINSERTTAB2:
		return ((QTabWidget*)h)->insertTab(v0, (QWidget*)v, *(QIcon*)v1, QString::fromUtf8(v3));
		break;
	}
	return 0;
}

XNLEXPORT xbool XI_CDECL widget_get_int_bool(xlong h, xint proid, xint v) {

        switch (proid)
        {
		case TABWIDGETISTABENABLED:
		{
			QTabWidget * titem = (QTabWidget *)h;
			return titem->isTabEnabled(v);
		}
		break;
		case TABBARISTABENABLED:
		{
			QTabBar * titem = (QTabBar *)h;
			return titem->isTabEnabled(v);
		}
		break;
		case TREEITEMISEXPAND:
		{
			QTreeWidgetItem * titem = (QTreeWidgetItem *)h;
			return titem->isExpanded();
		}
			break;
		case PRTDLGTEST:
		{
			QPrintDialog * titem = (QPrintDialog *)h;
			return titem->testOption((QPrintDialog::PrintDialogOption)v);
		}
		break;
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
		case APPLICATIONATTRIBUTES:
			QCoreApplication::setAttribute((Qt::ApplicationAttribute)v, v1);
			break;
		case TABWIDGETSETTABENABLED:
			((QTabWidget*)h)->setTabEnabled(v, v1);
			break;
		case TABBARSETTABENABLED:
			((QTabBar*)h)->setTabEnabled(v, v1);
			break;
		case PRTDLGSETOPT:
			((QPrintDialog*)h)->setOption((QPrintDialog::PrintDialogOption)v, v1);
			break;
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
		case TABWIDGETAUTOHIDE:
			return ((QTabWidget*)h)->tabBarAutoHide();
			break;
		case TABWIDGETDOCUMENTMODE:
			return ((QTabWidget*)h)->documentMode();
			break;
		case TABWIDGETUSESSCROLLBUTTONS:
			return ((QTabWidget*)h)->usesScrollButtons();
			break;
		case TABWIDGETHASHEIGHTFORWIDTH:
			return ((QTabWidget*)h)->hasHeightForWidth();
			break;
		case TABWIDGETISMOVABLE:
			return ((QTabWidget*)h)->isMovable();
			break;
		case TABWIDGETTABSCLOSABLE:
			return ((QTabWidget*)h)->tabsClosable();
			break;
		case TABBARCHANGECURRENTONDRAG:
			return ((QTabBar*)h)->changeCurrentOnDrag();
			break;
		case TABBARAUTOHIDE:
			return ((QTabBar*)h)->autoHide();
			break;
		case TABBARDOCUMENTMODE:
			return ((QTabBar*)h)->documentMode();
			break;
		case TABBARISMOVABLE:
			return ((QTabBar*)h)->isMovable();
			break;
		case TABBAREXPANDING:
			return ((QTabBar*)h)->expanding();
			break;
		case TABBARTABSCLOSABLE:
			return ((QTabBar*)h)->tabsClosable();
			break;
		case TABBARUSESSCROLLBUTTONS:
			return ((QTabBar*)h)->usesScrollButtons();
			break;
		case TABBARDRAWBASE:
			return ((QTabBar*)h)->drawBase();
			break;
		case SLD_GETTRACKING:
			return ((QAbstractSlider*)h)->hasTracking();
			break;
		case SLD_GETSLIDDOWN:
			return ((QAbstractSlider*)h)->isSliderDown();
			break;
		case SLD_GETINVERTEDAPPEARANCE:
			return ((QAbstractSlider*)h)->invertedAppearance();
			break;
		case SLD_GETINVERTEDCONTROLS:
			return ((QAbstractSlider*)h)->invertedControls();
			break;
		case ISDOCKNESTINGENABLED:
			return ((QMainWindow*)h)->isDockNestingEnabled();
			break;
		case TETABCHANGESFOCUS:
			return ((QTextEdit*)h)->tabChangesFocus();
			break;
		case TEGETREADONLY:
			return ((QTextEdit*)h)->isReadOnly();
			break;
		case PAINTDEVICEACTIVE:
			return ((QPaintDevice*)h)->paintingActive();
			break;
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
		case TABWIDGETTABBAR:
			xobj = getObjectControl(((QTabWidget*)h)->tabBar());
			break;
		case TABWIDGETCURRENTWIDGET:
			xobj = getObjectControl(((QTabWidget*)h)->currentWidget());
			break;
		case TOOLBARADDSEPAR:
				xobj = getObjectControl(((QToolBar*)h)->addSeparator());
			break;
		case MENUADDSEPAR:
				xobj = getObjectControl(((QMenu*)h)->addSeparator());
			break;
		case MENUBARADDSEPAR:
				xobj = getObjectControl(((QMenuBar*)h)->addSeparator());
			break;
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
		case MENUACTION:
			xobj = getObjectControl(((QMenu*)h)->menuAction());
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
		case PAINTDEVICEPRFS:
			return ((QPaintDevice*)h)->devicePixelRatioFScale();
			break;
		case PAINTDEVICEMETRICGETPRF:
			return ((QPaintDevice*)h)->devicePixelRatioF();
			break;
        }
        return 0;
}

XNLEXPORT void XI_CDECL widget_set_double_value(xlong h, xint proid, double v) {

        switch (proid)
        {
		case TESETFONTPOINTSIZE:
			((QTextEdit*)h)->setFontPointSize(v);
			break;
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
		case TABWIDGETSETTABBARAUTOHIDE:
			((QTabWidget*)h)->setTabBarAutoHide(v);
			break;
		case TABWIDGETSETDOCUMENTMODE:
			((QTabWidget*)h)->setDocumentMode(v);
			break;
		case TABWIDGETSETUSESSCROLLBUTTONS:
			((QTabWidget*)h)->setUsesScrollButtons(v);
			break;
		case TABWIDGETSETMOVABLE:
			((QTabWidget*)h)->setMovable(v);
			break;
		case TABWIDGETSETTABSCLOSABLE:
			((QTabWidget*)h)->setTabsClosable(v);
			break;
		case TABBARSETCHANGECURRENTONDRAG:
			((QTabBar*)h)->setChangeCurrentOnDrag(v);
			break;
		case TABBARSETAUTOHIDE:
			((QTabBar*)h)->setAutoHide(v);
			break;
		case TABBARSETDOCUMENTMODE:
			((QTabBar*)h)->setDocumentMode(v);
			break;
		case TABBARSETMOVABLE:
			((QTabBar*)h)->setMovable(v);
			break;
		case TABBARSETEXPANDING:
			((QTabBar*)h)->setExpanding(v);
			break;
		case TABBARSETTABSCLOSABLE:
			((QTabBar*)h)->setTabsClosable(v);
			break;
		case TABBARUSEBUTTONS:
			((QTabBar*)h)->setUsesScrollButtons(v);
			break;
		case TABBARSETDRAWBASE:
			((QTabBar*)h)->setDrawBase(v);
			break;
		case SLD_SETTRACKING:
			((QAbstractSlider*)h)->setTracking(v);
			break;
		case SLD_SETSLIDDOWN:
			((QAbstractSlider*)h)->setSliderDown(v);
			break;
		case SLD_SETINVERTEDAPPEARANCE:
			((QAbstractSlider*)h)->setInvertedAppearance(v);
			break;
		case SLD_SETINVERTEDCONTROLS:
			((QAbstractSlider*)h)->setInvertedControls(v);
			break;
		case TESETTABCHANGESFOCUS:
			((QTextEdit*)h)->setTabChangesFocus(v);
			break;
		case TESETFONTITALIC:
			((QTextEdit*)h)->setFontItalic(v);
			break;
		case TESETFONTUNDERLINE:
			((QTextEdit*)h)->setFontUnderline(v);
			break;
		case TESETREADONLY:
			((QTextEdit*)h)->setReadOnly(v);
			break;
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
		case TABWIDGETELIDEMODE:
			return ((QTabWidget*)h)->elideMode();
			break;
		case TABWIDGETTABSHAPE:
			return ((QTabWidget*)h)->tabShape();
			break;
		case TABWIDGETTABPOSITION:
			return ((QTabWidget*)h)->tabPosition();
			break;
		case TABWIDGETCOUNT:
			return ((QTabWidget*)h)->count();
			break;
		case TABWIDGETCURRENTINDEX:
			return ((QTabWidget*)h)->currentIndex();
			break;
		case TABBARSELECTIONBEHAVIORONREMOVE:
			return ((QTabBar*)h)->selectionBehaviorOnRemove();
			break;
		case TABBARCOUNT:
			return ((QTabBar*)h)->count();
			break;
		case TABBARCURRENTINDEX:
			return ((QTabBar*)h)->currentIndex();
			break;
		case TABBARELIDEMODE:
			return ((QTabBar*)h)->elideMode();
			break;
		case TABBARSHAPE:
			return ((QTabBar*)h)->shape();
			break;
		case SLD_GETMIN:
			return ((QAbstractSlider*)h)->minimum();
			break;
		case SLD_GETMAX:
			return ((QAbstractSlider*)h)->maximum();
			break;
		case SLD_GETSINGLESTEP:
			return ((QAbstractSlider*)h)->singleStep();
			break;
		case SLD_GETPAGESTEP:
			return ((QAbstractSlider*)h)->pageStep();
			break;
		case SLD_GETSLIDPOS:
			return ((QAbstractSlider*)h)->sliderPosition();
			break;
		case SLD_GETVALUE:
			return ((QAbstractSlider*)h)->value();
			break;
		case TEGETAUTOFORMATTING:
			return ((QTextEdit*)h)->autoFormatting();
			break;
		case TEGETWRAPMODE:
			return ((QTextEdit*)h)->wordWrapMode();
			break;
		case TEGETALIGNMENT:
			return ((QTextEdit*)h)->alignment();
			break;
		case PRINTERGETOUTFMT:
			return ((QPrinter*)h)->outputFormat();
			break;
		case PAINTDEVICETYPE:
			return ((QPaintDevice*)h)->devType();
			break;
		case PAINTERTYPE:
			return ((QPrinter*)h)->devType();
			break;
		case PRTDLGGETOPTS:
			return ((QPrintDialog*)h)->options();
			break;
		case PRTDLGEXEC:
			return ((QDialog*)h)->exec();
			break;
		case PVWDLGEXEC:
			return ((QPrintPreviewDialog*)h)->exec();
			break;

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



XNLEXPORT xint XI_CDECL widget_set_v2int_value(xlong h, xint proid, xint xv, xint yv) {
        switch (proid)
        {
		case BOXSETSTRETCH:
			((QBoxLayout*)h)->setStretch(xv, yv);
			break;
		case QSCIUPDATESHORTCUT:
		{
			QsciCommandSet * pset = ((QsciScintilla*)h)->standardCommands();
			if (pset != 0) {
				QsciCommand * pcmd = pset->find((QsciCommand::Command)xv);
				if (pcmd != 0) {
					pcmd->setKey(yv);
				}
			}
		}
		break;
		case TABWIDGETSETICONSIZE:
			((QTabWidget*)h)->setIconSize(QSize(xv, yv));
			break;
		case TABWIDGETHEIGHTFORWIDTH:
			return ((QTabWidget*)h)->heightForWidth(xv);
			break;
		case TABBARSETICONSIZE:
			((QTabBar*)h)->setIconSize(QSize(xv, yv));
			break;
		case TABBARTABAT:
			return ((QTabBar*)h)->tabAt(QPoint(xv, yv));
			break;
		case TABBARMOVETAB:
			((QTabBar*)h)->moveTab(xv, yv);
			break;
		case SLD_SETRANGE:
			((QAbstractSlider*)h)->setRange(xv, yv);
			break;
        case RESIZE:
                ((QWidget*)h)->resize(xv, yv);
                break;
		case SETICONSIZE:
			((QToolBar*)h)->setIconSize(QSize(xv, yv));
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
			((QGradient*)h)->setColorAt(w, QMakeColor(xv));
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
		case TABWIDGETSETTABWHATSTHIS:
			((QTabWidget*)h)->setTabWhatsThis(xv, yv);
			break;
		case TABWIDGETSETTABTOOLTIP:
			((QTabWidget*)h)->setTabToolTip(xv, yv);
			break;
		case TABWIDGETSETTABTEXT:
			((QTabWidget*)h)->setTabText(xv, yv);
			break;
		case TABBARSETACCESSIBLETABNAME:
			((QTabBar*)h)->setAccessibleTabName(xv, yv);
			break;
		case TABBARSETTABWHATSTHIS:
			((QTabBar*)h)->setTabWhatsThis(xv, yv);
			break;
		case TABBARSETTABTOOLTIP:
			((QTabBar*)h)->setTabToolTip(xv, yv);
			break;
		case TABBARSETTABTEXT:
			((QTabBar*)h)->setTabText(xv, yv);
			break;
		case TABBARADDTAB:
			return ((QTabBar*)h)->addTab(yv);
			break;
		case TABBARINSERTTAB:
			return ((QTabBar*)h)->insertTab(xv, yv);
			break;
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
#ifndef MOBILE_APP
		case LOADREPORTFROMFILE:
			return ((LimeReport::ReportEngine *)h)->loadFromFile(QString::fromUtf8(yv)) ? 1 : 0;
			break;

		case LOADREPORTFROMTEXT:
			return ((LimeReport::ReportEngine *)h)->loadFromString(QString::fromUtf8(yv)) ? 1 : 0;
			break;
#endif
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
		case TESETCURRENTFONT:
		{
			((QTextEdit*)h)->setCurrentFont(*(QFont*)(value));
		}
		break;
		case TABWIDGETSETCURRENTWIDGET:
		{
			((QTabWidget*)h)->setCurrentWidget((QWidget*)(value));
		}
		break;
		case SETDATETIME:
		{
			((QDateTimeEdit*)h)->setDateTime(QDateTime::fromMSecsSinceEpoch(value));
		}
		break;
		case CLIPBOARDIMAGE:
		{
			QClipboard * clipboard = QApplication::clipboard();
			if (clipboard != 0) {
				clipboard->setImage(*(QImage*)value);
			}
		}
			break;
        case PALETTE:
                ((QWidget*)h)->setPalette(*(QPalette*)value);
                break;
		case SETLAYOUT:
			((QWidget*)h)->setLayout((QLayout*)value);
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
               // ar.installAction((QAction*)value);
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
		case SETSTYLE: {
			QStyle * style = QStyleFactory::create(QString::fromUtf8(value));
			if (style != 0) {
				((QWidget*)h)->setStyle(style);
			}
		}
					   
			break;
		case TESCROLLTOANCHOR:
			((QTextEdit*)h)->scrollToAnchor(QString::fromUtf8(value));

			break;

		case TEAPPEND:
			((QTextEdit*)h)->append(QString::fromUtf8(value));
			break;
		case TEINSERTHTML:
			((QTextEdit*)h)->insertHtml(QString::fromUtf8(value));
			break;
		case TEINSERTPLAINTEXT:
			((QTextEdit*)h)->insertPlainText(QString::fromUtf8(value));
			break;
		case TESETPLACEHOLDERTEXT:
			((QTextEdit*)h)->setPlaceholderText(QString::fromUtf8(value));
			break;
		case TESETTEXT:
			((QTextEdit*)h)->setText(QString::fromUtf8(value));
			break;
		case TESETHTML:
			((QTextEdit*)h)->setHtml(QString::fromUtf8(value));
			break;
		case TESETPLAINTEXT:
			((QTextEdit*)h)->setPlainText(QString::fromUtf8(value));
			break;
		case TESETFONTFAMILY:
			((QTextEdit*)h)->setFontFamily(QString::fromUtf8(value));
			break;
		case OBJECTSETNAME:
			((QObject*)h)->setObjectName(QString::fromUtf8(value));
			break;
		case CLIPBOARDTEXT:
		{
			QClipboard * clipboard = QApplication::clipboard();
			if (clipboard != 0) {
				clipboard->setText(QString::fromUtf8(value));
			}
		}
			break;
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

		case TABWIDGETCLEAR:
			((QTabWidget*)h)->clear();
			break;
		case TESELECTALL:
			((QTextEdit*)h)->selectAll();
			break;
		case TECLEAR:
			((QTextEdit*)h)->clear();
			break;
		case TEREDO:
			((QTextEdit*)h)->redo();
			break;
		case TEUNDO:
			((QTextEdit*)h)->undo();
			break;
		case TEPASTE:
			((QTextEdit*)h)->paste();
			break;
		case TECOPY:
			((QTextEdit*)h)->copy();
			break;
		case TECUT:
			((QTextEdit*)h)->cut();
			break;
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
		case SCIPRINTERDTOR:
			delete (QsciPrinter*)h;
			break;
		case PRINTERDTOR:
			delete (QPrinter*)h;
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
		case TRIGGER:
			((QAction*)h)->triggered();
			break;
		case TABLECLEARCONTENT:
			((QTableWidget*)h)->clearContents();
			break;
        default:
                break;
        }
}

XNLEXPORT xbool XI_CDECL array_int2(xlong h, xint proid, XObject * obj, xint pos, xint len) {
		bool bret = false;

        switch (proid)
        {
		case ASSOCIATEEXT:
		{
#if (defined(WIN32) || defined(__linux))
			if (gs_env->isArray(obj)) {
				QStringList columns;
				xlong size = gs_env->getLengthOfArray(obj);
				if (size == 7) {
					const char ** text = new const char *[size];
					size_t *length = new size_t[size];

					if (gs_env->getElementValue(obj, 0, text, length, size)) {
						bret = RegisterFileRelation(text[0], text[1], text[2], text[3], text[4], text[5], text[6]);
					}
					delete[] text;
					delete[]length;
				}
			}
#endif
			return bret;
		}
		break;
		case CHECKASSOCIATED:
		{
#if (defined(WIN32) || defined(__linux))
			if (gs_env->isArray(obj)) {
				QStringList columns;
				xlong size = gs_env->getLengthOfArray(obj);
				if (size == 3) {
					const char ** text = new const char *[size];
					size_t *length = new size_t[size];

					if (gs_env->getElementValue(obj, 0, text, length, size)) {
						bret = CheckFileRelation(text[0], text[1], text[2]);
					}
					delete[] text;
					delete[]length;
				}
			}
#endif
			return bret;
		}
		break;

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
						installAction(child);
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
		case MAINWNDADDMENU:
			obj = ((QMainWindow*)h)->menuBar()->addMenu(QString::fromUtf8(name));
			break;
        case ADDACTION:
            obj = ((QMenuBar*)h)->addAction(QString::fromUtf8(name));
            break;
		case ADDACT:
			obj = ((QMenu*)h)->addAction(QString::fromUtf8(name));
			break;
		case ADDMENU:
			obj = ((QMenu*)h)->addMenu(QString::fromUtf8(name));
			break;

        }

		if (obj != 0) {
			XObject * output = getObjectControl(obj);
			if (output != 0) {
				return gs_env->referenceObject(output);
			}
		}
		return 0;
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
		case PAINTDEVICEMETRICGET:
			{
			QPaintDevice * device = (QPaintDevice*)h;
				switch (v)
				{
				case QPaintDevice::PdmWidth:
					return device->width();
				case QPaintDevice::PdmHeight:
					return device->height();
				case QPaintDevice::PdmWidthMM:
					return device->widthMM();
				case QPaintDevice::PdmHeightMM:
					return device->heightMM();
				case QPaintDevice::PdmDpiX:
					return device->logicalDpiX();
				case QPaintDevice::PdmDpiY:
					return device->logicalDpiY();
				case QPaintDevice::PdmPhysicalDpiX:
					return device->physicalDpiX();
				case QPaintDevice::PdmPhysicalDpiY:
					return device->physicalDpiY();
				case QPaintDevice::PdmDevicePixelRatio:
					return device->devicePixelRatio();
				case QPaintDevice::PdmNumColors:
					return device->colorCount();
				case QPaintDevice::PdmDepth:
					return device->depth();
				default:
					break;
				}
				break;
			}
        }
        return 0;
}

XNLEXPORT XObject *  XI_CDECL core_getString(xlong h, xint proid) {
        QByteArray qba;
        switch (proid)
        {
		case BUTTONGETTEXT:
			qba = ((QPushButton*)h)->text().toUtf8();
			break;
		case WIDGETGETTITLE:
			qba = ((QWidget*)h)->windowTitle().toUtf8();
			break;
		case TEGETPLACEHOLDERTEXT:
			qba = ((QTextEdit*)h)->placeholderText().toUtf8();
			break;
		case TETOPLAINTEXT:
			qba = ((QTextEdit*)h)->toPlainText().toUtf8();
			break;
		case TETOHTML:
			qba = ((QTextEdit*)h)->toHtml().toUtf8();
			break;
		case CLIPBOARDTEXT:
		{
			QClipboard * clipboard = QApplication::clipboard();
			if (clipboard != 0) {
				qba = clipboard->text().toUtf8();
			}
		}
			break;
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
	QObject * obj = 0;

	switch (proid) {
		case ADDACT:
			obj = ((QMenu*)h)->addAction(*loadIcon(QString::fromUtf8(v1)), QString::fromUtf8(v2));
			break;
	}


	if (obj != 0) {
		XObject * output = getObjectControl(obj);
		if (output != 0) {
			return gs_env->referenceObject(output);
		}
	}
	return 0;
}

XNLEXPORT XObject * XI_CDECL object_get_handle(xlong h, xint proid, xlong h1) {

        switch (proid)
        {
		case TABWIDGETCORNERWIDGET:
		{
			XObject *  output = getObjectControl(((QTabWidget*)h)->cornerWidget((Qt::Corner)h1));
			if (output != 0) {
				return gs_env->referenceObject(output);
			}
		}
			break;
		case TABWIDGETWIDGET:
		{
			XObject *  output = getObjectControl(((QTabWidget*)h)->widget(h1));
			if (output != 0) {
				return gs_env->referenceObject(output);
			}
		}
			break;
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
		case TABBARACCESSIBLETABNAME:
		{
			QTabBar * pImage = (QTabBar*)h;
			QByteArray qba = pImage->accessibleTabName(h1).toUtf8();
			return data2String(qba);
		}
		break;
        default:
                break;
        }
        return 0;
}

XNLEXPORT XObject * XI_CDECL object_get_handle2(xlong h, xint proid, xlong hv, xlong h1) {
	QObject * qobj = 0;
	switch (proid) {
		case TABLEGETCELLWIDGET:
		{
			QTableWidget * qt = (QTableWidget*)h;
			qobj = qt->cellWidget(hv, h1);

		}
		break;
		case TABBARTABBUTTON:
			qobj = ((QTabBar*)h)->tabButton(hv, (QTabBar::ButtonPosition)h1);
			break;
		case MENUBARINSMENU:
			qobj = ((QMenuBar*)h)->insertMenu((QAction*)hv, (QMenu*)h1);
			break;
		case MENUINSMENU:
			qobj = ((QMenu*)h)->insertMenu((QAction*)hv, (QMenu*)h1);
			break;
	}

	if (qobj != 0) {
		XObject * xobj = getObjectControl(qobj);
		if (xobj != NULL) {
			return gs_env->referenceObject(xobj);
		}
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
		case OPENMULTI:
		{
			QStringList files = QFileDialog::getOpenFileNames((QWidget*)parent, QString::fromUtf8(caption), QString::fromUtf8(defaultPath), QString::fromUtf8(pattern));
			if (files.size() > 0) {
				XObject * outs = gs_env->createStringArray(files.size());
				XThread currentthread;
				for (int i = 0; i < files.size(); i++) {
					QByteArray charstr = files[i].toUtf8();
					xstring p = charstr.data();
					int pl = charstr.length();
					gs_env->setElementValue(currentthread.getThread(), outs, i, &p, &pl, 1);
				}
				return outs;
			}
			return 0;
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
		case TABWIDGETADDTAB:
		{
			return ((QTabWidget*)handle)->addTab((QWidget *)v1, v2);
		}
		break;
		case TABBARADDTAB:
		{
			QIcon * icon = (QIcon *)v1;
			return ((QTabBar*)handle)->addTab(*icon, v2);
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

		case REGDATASOURCE:
		{
#ifndef MOBILE_APP
			LimeReport::ICallbackDatasource * qobject = 0;
			try {
				qobject = ((LimeReport::ReportEngine*)handle)->dataManager()->createCallbackDatasource(QString::fromUtf8(v2));
				if (qobject != NULL) {
					XObjectData * objectData = new XObjectData();
					objectData->setObject(v1);
					qobject->setUserData(Qt::UserRole, objectData);
					ar.installDatasourceCallback(qobject);
				}
			}
			catch (LimeReport::ReportError &exception) {

			}
			
			
			return (xlong)qobject;
#endif
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
		case WIDGETRENDERF:
		{
			((QWidget*)h)->render((QPainter*)v1, QPoint(x1, x2), QRegion(x3, x4, y1, y2, (QRegion::RegionType)y3), QWidget::RenderFlags(y4));
		}
		break;
		case WIDGETRENDER4:
		{
			((QWidget*)h)->render((QPainter*)v1, QPoint(x1, x2), QRegion(), QWidget::RenderFlags(y4));
		}
		break;
		case WIDGETRENDER2:
		{
			((QWidget*)h)->render((QPainter*)v1, QPoint(), QRegion(), QWidget::RenderFlags(y4));
		}
		break;
		case WIDGETRENDER1:
		{
			((QWidget*)h)->render((QPainter*)v1);
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
		case SCI_PROP:
			return ((QsciScintilla*)handle)->setProperty(v1, QString::fromUtf8(v2));
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
		case TABWIDGETICONSIZE:
		{
			QTabWidget* twidget = (QTabWidget *)handle;
			xlong hp = (xlong)twidget->iconSize().width();
			hp <<= 32;
			return hp | twidget->iconSize().height();
		}
		break;
		case TABWIDGETMINIMUMSIZEHINT:
		{
			QTabBar * twidget = (QTabBar *)handle;
			xlong hp = (xlong)twidget->minimumSizeHint().width();
			hp <<= 32;
			return hp | twidget->minimumSizeHint().height();
		}
		break;
		case TABWIDGETSIZEHINT:
		{
			QTabBar * twidget = (QTabBar *)handle;
			xlong hp = (xlong)twidget->sizeHint().width();
			hp <<= 32;
			return hp | twidget->sizeHint().height();
		}
		break;
		case TABBARICONSIZE:
		{
			QTabBar * twidget = (QTabBar *)handle;
			xlong hp = (xlong)twidget->iconSize().width();
			hp <<= 32;
			return hp | twidget->iconSize().height();
		}
		break;
		case TABBARMINIMUMSIZEHINT:
		{
			QTabBar * twidget = (QTabBar *)handle;
			xlong hp = (xlong)twidget->minimumSizeHint().width();
			hp <<= 32;
			return hp | twidget->minimumSizeHint().height();
		}
		break;
		case TABBARSIZEHINT:
		{
			QTabBar * twidget = (QTabBar *)handle;
			xlong hp = (xlong)twidget->sizeHint().width();
			hp <<= 32;
			return hp | twidget->sizeHint().height();
		}
		break;
		case GETDATETIME:
		{
			QDateTimeEdit * twidget = (QDateTimeEdit *)handle;
			return (xlong)twidget->dateTime().toMSecsSinceEpoch();
		}
		break;
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
		case PAINTERFROMDEVICE:
		{
			QPaintDevice * pimg = (QPaintDevice *)handle;
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
		case TABWIDGETTABWHATSTHIS:
			qba = ((QTabWidget *)v1)->tabWhatsThis(v2).toUtf8();
			break;
		case TABWIDGETTABTOOLTIP:
			qba = ((QTabWidget *)v1)->tabToolTip(v2).toUtf8();
			break;
		case TABWIDGETTABTEXT:
			qba = ((QTabBar *)v1)->tabText(v2).toUtf8();
			break;
		case TABBARTABWHATSTHIS:
			qba = ((QTabBar *)v1)->tabWhatsThis(v2).toUtf8();
			break;
		case TABBARTABTOOLTIP:
			qba = ((QTabBar *)v1)->tabToolTip(v2).toUtf8();
			break;
		case TABBARTABTEXT:
			qba = ((QTabBar *)v1)->tabText(v2).toUtf8();
			break;
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
		case PRINTSCIRANGE:
		{
			QsciPrinter * printer = (QsciPrinter *)h;
			printer->printRange((QsciScintilla*)xv, yv, zv);
		}
		break;
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
		{
			((QToolBar*)h)->addWidget((QWidget*)xv);
		}
			break;
		case TOOLBARADDACTION:
		{
			((QToolBar*)h)->addAction((QAction*)xv);
		}
		break;
		case TOOLBARREMACTION:
		{
			((QToolBar*)h)->removeAction((QAction*)xv);
		}
		break;
		case MAINWNDADDTOOLBAR:
		{
			((QMainWindow*)h)->addToolBar((QToolBar*)xv);
		}
		break;
		case MAINWNDMENUADD:
		{
			//((QMainWindow*)h)->menuBar()->addMenu((QToolBar*)xv);
			((QMenuBar*)h)->addMenu((QMenu*)xv);
		}
		break;

		case LAYTOUADDWIDGET:
		{
			((QBoxLayout*)h)->addWidget((QWidget*)xv);
		}
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
                                  //ar.installAction((QAction*)v[i]);
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

		case SETDATE:// 133,
		{

			if (gs_env->isArray(value)) {
				xint * pint = (xint *)gs_env->getPointerOfArray(value);
				((QDateTimeEdit *)h)->setDate(QDate(pint[0], pint[1], pint[2]));
			}
		}
		break;

		case SETTIME:// 133,
		{

			if (gs_env->isArray(value)) {
				xint * pint = (xint *)gs_env->getPointerOfArray(value);
				((QDateTimeEdit *)h)->setTime(QTime(pint[0], pint[1], pint[2], pint[3]));
			}
		}
		break;

		case GETDATE:// 133,
		{

			if (gs_env->isArray(value)) {
				xint * pint = (xint *)gs_env->getPointerOfArray(value);
				QDate date = ((QDateTimeEdit *)h)->date();  
				pint[0] = date.year();
				pint[1] = date.month();
				pint[2] = date.day();
			}
		}
		break;

		case GETTIME:// 133,
		{

			if (gs_env->isArray(value)) {
				xint * pint = (xint *)gs_env->getPointerOfArray(value);
				QTime time = ((QDateTimeEdit *)h)->time();
				pint[0] = time.hour();
				pint[1] = time.minute();
				pint[2] = time.second();
				pint[3] = time.msec();
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
		case TABWIDGETSETTABICON:
		{
			QTabWidget * obj = (QTabWidget*)h;
			obj->setTabIcon(iv, *((QIcon*)h1));
		}
		break;
		case TABBARSETTABBUTTON:
		{
			QTabBar * obj = (QTabBar*)h;
			obj->setTabButton(hv, (QTabBar::ButtonPosition)iv, ((QWidget*)h1));
		}
		break;
		case TABBARSETTABICON:
		{
			QTabBar * obj = (QTabBar*)hv;
			obj->setTabIcon(iv, *((QIcon*)h1));
		}
		break;
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
		case TABIFYDOCKWIDGET:
		{
			QMainWindow * obj = (QMainWindow*)h;
			obj->tabifyDockWidget((QDockWidget*)hv, (QDockWidget*)h1);
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
		case TABWIDGETSETCORNERWIDGET:
			((QTabWidget*)h)->setCornerWidget((QWidget*)hv, (Qt::Corner)iv);
			break;
		case QPB_SETEXPAND:
			((QtTreePropertyBrowser*)h)->setExpanded((QtBrowserItem*)hv, iv != 0);
			break;
		case QPB_SETSELECT:
			((QtTreePropertyBrowser*)h)->setSelected((QtBrowserItem*)hv, iv != 0);
			break;
		case QPB_SETVISIBLE:
			((QtTreePropertyBrowser*)h)->setItemVisible((QtBrowserItem*)hv, iv != 0);
			break;
		case QPB_SETBACKCOLOR:
			((QtTreePropertyBrowser*)h)->setBackgroundColor((QtBrowserItem*)hv, QMakeColor(iv));
			break;
		case CLIPBOARDIMAGE:
		{
			QClipboard * clipboard = QApplication::clipboard();
			if (clipboard != 0) {
				return (xlong)new QImage(clipboard->image());
			}
		}
		break;
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
		case TREEITEMSELED:
		{
			QTreeWidgetItem * obj = (QTreeWidgetItem*)hv;
			QTreeWidget * tree = (QTreeWidget *)h;
			tree->setItemSelected(obj, iv != 0);
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
		case TABBARTABTEXTCOLOR:
			return (xlong)((QTabBar*)handle)->tabTextColor(value).value();
			break;
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

		QImage * qm = new QImage(width, height, (QImage::Format)v1);
		if (handle == 0) {
			qm->fill(Qt::GlobalColor::transparent);
		}
		else {
			uchar * data = qm->bits();
			size_t count = qm->byteCount();
			memcpy(data, (uchar*)handle, count);
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
		case TABBARSETTABTEXTCOLOR:
			((QTabBar*)handle)->setTabTextColor(value1, (v2));
			break;
        case SETMGRFACTORY:
                ((QtTreePropertyBrowser*)handle)->setFactoryForManager((QtAbstractPropertyManager*)value1, (QtAbstractEditorFactory<QtAbstractPropertyManager>*)v2);
                break;

		case TOOLBARINSWIDGET:
				((QToolBar*)handle)->insertWidget((QAction*)value1, (QWidget*)v2);
			break;
		case TOOLBARINSACTION:
			((QToolBar*)handle)->insertAction((QAction*)value1, (QAction*)v2);
			break;

		case TOOLBARINSSEPAR:
			((QToolBar*)handle)->insertSeparator((QAction*)value1);
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
		case TABWIDGETINDEXOF:
			return ((QTabWidget *)h)->indexOf((QWidget*)h1);
			break;
        case INSERTWIDGET:
                return ((QStatusBar *)h)->insertWidget(v2, (QWidget*)h1, v1);
                break;
        case INSERTPERWIDGET:
                return ((QStatusBar *)h)->insertPermanentWidget(v2, (QWidget*)h1, v1);
                break;
		case ADDDOCKWIDGET:
		{
			QMainWindow * obj = (QMainWindow*)h;
			obj->addDockWidget((Qt::DockWidgetArea)v1, (QDockWidget*)(h1), (Qt::Orientation)v2);
		}
		break;
        default:
                break;
        }
        return 0;
}

#ifdef MOBILE_APP

void * getFunction(const char * name) {
    if (strcmp(name, "XNLMain") == 0) return  (void*)&XNLMain;
    if (strcmp(name, "XNLExit") == 0) return  (void*)&XNLExit;
    if (strcmp(name, "locaUiFile") == 0) return (void*)&locaUiFile;
    if (strcmp(name, "ShowUi") == 0) return (void*)&ShowUi;
    if (strcmp(name, "createQxApplication") == 0) return (void*)&createQxApplication;
    if (strcmp(name, "ApplicationRun") == 0) return (void*)& ApplicationRun;
    if (strcmp(name, "widget_set_vint_value") == 0) return (void*)& widget_set_vint_value;
    if (strcmp(name, "widget_get_bool_value") == 0) return (void*)& widget_get_bool_value;
    if (strcmp(name, "widget_get_object") == 0) return (void*)& widget_get_object;
    if (strcmp(name, "widget_get_double_value") == 0) return (void*)& widget_get_double_value;
    if (strcmp(name, "widget_set_double_value") == 0) return (void*)& widget_set_double_value;
    if (strcmp(name, "widget_set_bool_value") == 0) return (void*)& widget_set_bool_value;
    if (strcmp(name, "widget_set_bkrl") == 0) return (void*)& widget_set_bkrl;
    if (strcmp(name, "widget_get_int_value") == 0) return (void*)& widget_get_int_value;
    if (strcmp(name, "widget_set_v2int_value") == 0) return (void*)& widget_set_v2int_value;
    if (strcmp(name, "widget_set_native_value") == 0) return (void*)& widget_set_native_value;
    if (strcmp(name, "widget_slot_string") == 0) return (void*)& widget_slot_string;
    if (strcmp(name, "widget_slot") == 0) return (void*)& widget_slot;
    if (strcmp(name, "core_sub_class") == 0) return (void*)& core_sub_class;
    if (strcmp(name, "findControl") == 0) return (void*)& findControl;
    if (strcmp(name, "core_getName") == 0) return (void*)& core_getName;
    if (strcmp(name, "core_getClassName") == 0) return (void*)& core_getClassName;
    if (strcmp(name, "core_getParent") == 0) return (void*)& core_getParent;
    if (strcmp(name, "createQObject") == 0) return (void*)& createQObject;
    if (strcmp(name, "createNObject") == 0) return (void*)& createNObject;
    if (strcmp(name, "widget_set_intstring_value") == 0) return (void*)& widget_set_intstring_value;
    if (strcmp(name, "widget_set_v3int_value") == 0) return (void*)& widget_set_v3int_value;
    if (strcmp(name, "widget_set_intintstring_value") == 0) return (void*)& widget_set_intintstring_value;
    if (strcmp(name, "core_getString") == 0) return (void*)& core_getString;
    if (strcmp(name, "object_get_string") == 0) return (void*)& object_get_string;
    if (strcmp(name, "object_get_handle_string") == 0) return (void*)& object_get_handle_string;
    if (strcmp(name, "object_get_string2") == 0) return (void*)& object_get_string2;
    if (strcmp(name, "object_get_handle") == 0) return (void*)& object_get_handle;
    if (strcmp(name, "object_get_handle2") == 0) return (void*)& object_get_handle2;
    if (strcmp(name, "object_get_string_handle_string2") == 0) return (void*)& object_get_string_handle_string2;
    if (strcmp(name, "object_get_string_handle_string_int") == 0) return (void*)& object_get_string_handle_string_int;
    if (strcmp(name, "object_get_string2_handle_string2") == 0) return (void*)& object_get_string2_handle_string2;
    if (strcmp(name, "object_get_string2_handle_string_int") == 0) return (void*)& object_get_string2_handle_string_int;
    if (strcmp(name, "attachControl") == 0) return (void*)& attachControl;
    if (strcmp(name, "openfile_dlg_string3_obj") == 0) return (void*)& openfile_dlg_string3_obj;
    if (strcmp(name, "long_string2") == 0) return (void*)& long_string2;
    if (strcmp(name, "long_long_string2") == 0) return (void*)& long_long_string2;
    if (strcmp(name, "long_get") == 0) return (void*)& long_get;
    if (strcmp(name, "core_attach") == 0) return (void*)& core_attach;
    if (strcmp(name, "widget_set_intlongstring_value") == 0) return (void*)& widget_set_intlongstring_value;
    if (strcmp(name, "widget_set_intlongint_value") == 0) return (void*)& widget_set_intlongint_value;
    if (strcmp(name, "widget_set_object_value") == 0) return (void*)& widget_set_object_value;
    if (strcmp(name, "object_set_long_int_long") == 0) return (void*)& object_set_long_int_long;
    if (strcmp(name, "object_get_long_int") == 0) return (void*)& object_get_long_int;
    if (strcmp(name, "long_string2_int2") == 0) return (void*)& long_string2_int2;
    if (strcmp(name, "widget_set_int_bool_value") == 0) return (void*)& widget_set_int_bool_value;
    if (strcmp(name, "string_bool5_int2_bool2") == 0) return (void*)& string_bool5_int2_bool2;
    if (strcmp(name, "long_intstring") == 0) return (void*)& long_intstring;
    if (strcmp(name, "long_intlong") == 0) return (void*)& long_intlong;
    if (strcmp(name, "void_long2") == 0) return (void*)& void_long2;
    if (strcmp(name, "widget_set_long_object_value") == 0) return (void*)& widget_set_long_object_value;
    if (strcmp(name, "core_getintlong") == 0) return (void*)& core_getintlong;
    if (strcmp(name, "native_double2") == 0) return (void*)& native_double2;
    if (strcmp(name, "native_double4") == 0) return (void*)& native_double4;
    if (strcmp(name, "core_getStringlongint") == 0) return (void*)& core_getStringlongint;
    if (strcmp(name, "int_long_int_long_int_int") == 0) return (void*)& int_long_int_long_int_int;
    if (strcmp(name, "widget_set_int2_object_value") == 0) return (void*)& widget_set_int2_object_value;
    if (strcmp(name, "array_int2") == 0) return (void*)& array_int2;
    if (strcmp(name, "locaUiData") == 0) return (void*)& locaUiData;
    if (strcmp(name, "widget_set_bint_value") == 0) return (void*)& widget_set_bint_value;
    if (strcmp(name, "create_array_int2") == 0) return (void*)& create_array_int2;
    if (strcmp(name, "createSObject") == 0) return (void*)& createSObject;
    if (strcmp(name, "long_longstring") == 0) return (void*)& long_longstring;
    if (strcmp(name, "long_intlong2") == 0) return (void*)& long_intlong2;
    if (strcmp(name, "widget_get_int_bool") == 0) return (void*)& widget_get_int_bool;
	if (strcmp(name, "native_long2_string") == 0) return (void*)& native_long2_string;
    if (strcmp(name, "widget_set_v2int_double_value") == 0) return (void*)& widget_set_v2int_double_value;
    if (strcmp(name, "native_int4") == 0) return (void*)& native_int4;
    if (strcmp(name, "long_long_int9") == 0) return (void*)& long_long_int9;
    if (strcmp(name, "long_double2") == 0) return (void*)& long_double2;
    if (strcmp(name, "long_object_string") == 0) return (void*)& long_object_string;
    if (strcmp(name, "pointer_intlong2") == 0) return (void*)& pointer_intlong2;
    if (strcmp(name, "createPObject") == 0) return (void*)& createPObject;
    if (strcmp(name, "createQPObject") == 0) return (void*)& createQPObject;
	return 0;
}

#include <QtAndroid>
#include <QJsonObject>
#include <android/log.h>
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "QXLibrary",__VA_ARGS__)

typedef void (*__init_function_ptr)(void*(*prcload)(const char *),
    void*(*prcgetf)(void *, const char *),
    void(*prcfree)(void*),
    int(*prcout)(const char *, size_t),
    int(*prcin)(const char *, size_t),
    void (*preexit)(void));

typedef void * (*__init_xrvm_ptr)();

typedef int (*__start_xrvm_ptr)(void * pvm,
                                const char * app_path,
                                unsigned char * data,
                                size_t len,
                                int argc,
                                const char * argv[],
                                int * errcode);

__init_function_ptr __init_function_p = 0;
__init_xrvm_ptr __init_xrvm_p = 0;
__start_xrvm_ptr __start_xrvm_p = 0;

//#include "../../../../../xcross/libxrvm.h"
#include <dlfcn.h>

char * mymod = 0;

void* load_module(const char * name) {
	if (strcmp(name, "libQXLibrary.so") == 0) {
		if (mymod == 0) {
			mymod = new char[8];
		}
		return mymod;
	}
	return  dlopen(name, RTLD_NOW);
}

void * get_function(void * handle, const char * name) {
	if (handle == mymod && mymod != 0) {
		return getFunction(name);
	}
	return dlsym(handle, name);
}

void free_library(void * handle) {
	if (mymod != 0) {
		delete[] mymod;
		return;
	}
	dlclose(handle);
}

int std_stream_out(const char * text, size_t len) {
	return len;
}
int std_stream_in(const char * text, size_t len) {
	return 0;
}

void onexit(){
    LOGD("libQXLibrary: %s", "wille exit");
}

bool loadXRVM(bool & debug){
    debug = true;
    void * xhandle = dlopen("libxrvmd.so", RTLD_NOW);

    if (xhandle == 0){
        debug = false;
        xhandle = dlopen("libxrvm.so", RTLD_NOW);
    }

    if (xhandle != 0){
       __init_function_p = (__init_function_ptr)dlsym(xhandle, "__init_function");
       __init_xrvm_p = (__init_xrvm_ptr)dlsym(xhandle, "__init_xrvm");
       __start_xrvm_p = (__start_xrvm_ptr)dlsym(xhandle, "__start_xrvm");
       return true;
    }

    return false;
}


QString getRunArgument() {
  QString argument;
  QAndroidJniObject activity = QtAndroid::androidActivity();
  if (activity.isValid()) {
    QAndroidJniObject intent = activity.callObjectMethod("getIntent", "()Landroid/content/Intent;");
    if (intent.isValid()) {
       QAndroidJniObject data = intent.callObjectMethod("getExtras", "()Landroid/os/Bundle;");
       if (data.isValid()) {
           argument = data.toString();
       }
    }
  }
  return argument;
}

void processArgv(char * data, int len, std::vector<const char*> & argout){
    char * hp = data;
    char * ep = (data + len - 1);
    while (hp != ep){
        if (*hp == '{'){
            hp++;
            break;
        }
        hp++;
    }
    while (ep != hp){
        if (*ep == '}'){
            *ep = 0;
            len = ep - hp;
            data = hp;
            break;
        }
        ep--;
    }
    if (ep == hp){
        return;
    }
    bool ds = false;
    char * p = data, *q = data + len;
    bool begin = false;

    while (p != q){
        if (*p != '\\'){
            if (*p == '"'){ ds = !ds; }
            if (!ds){
                if (!begin && *p != ' ' && *p != ','){
                    begin = true;
                    argout.push_back(p);
                }
                if (*p == ','){
                    *p = 0;
                    begin = false;
                }
            }
        }
        else{
            p++;
        }
        p++;
    }
}


int main(int argc, char *argv[]) {
    //_xapplication = new QXApplication(argc, argv);
    QString _argv = getRunArgument();
    //LOGD("QXLibrary: %s", "qt start --------------------------------------");
    int dbgport = -1;

    bool runasDebug = false;
    if (loadXRVM(runasDebug) == false){
        return 0;
    }

    //LOGD("QXLibrary: %s", _argv.toUtf8().data());
    std::vector<const char*> arglist;
    for (int x = 0;x < argc; x++){
        arglist.push_back(argv[x]);
    }
    //LOGD("QXLibrary: %s", "qt start --------------------------------------2");
    QByteArray _argpb = _argv.toUtf8();

    if (_argpb.size() > 0){
        processArgv(_argpb.data(), _argpb.size(), arglist);

        if (arglist.size() > 0){
            if (runasDebug){
                for (size_t i = 0; i < arglist.size(); i++){
                    if (0 == strncmp(arglist[i], "xdbn=", 5)){
                        dbgport = atoi(arglist[i] + 5);
                        arglist.erase(arglist.begin() + i);
                        break;
                    }
                }
            }
        }
    }
    //LOGD("QXLibrary: %s", "qt start --------------------------------------3");
    char dbgargv[128];

    if (runasDebug){
        if (dbgport > 0){
            sprintf(dbgargv, "-xdbn:%d", dbgport);
            arglist.push_back(dbgargv);
        }
    }

    //LOGD("QXLibrary: %s", "qt start --------------------------------------4");
    QFile fileSrc("assets:/app.exc");
    if (fileSrc.open(QFile::ReadOnly)) {
      //  LOGD("QXLibrary: %s", "qt start --------------------------------------5");
        QByteArray data;
        data = fileSrc.readAll();
        fileSrc.close();


        int error = 0;
        //LOGD("QXLibrary: %s", "qt start --------------------------------------6");
        unsigned char * pdata = new unsigned char[data.size() + 32], * pcode = 0;

        size_t mod = size_t(pdata) % 32;
        if (mod != 0){
            pcode = pdata + (32 - mod);
        }else{
            pcode = pdata;
        }

        memcpy(pcode, data.data(), data.size());
        size_t codelen = data.size();
        data.clear();
        //LOGD("QXLibrary: %s", "qt start --------------------------------------7");
        void * handle = __init_xrvm_p();
        __init_function_p(&load_module, &get_function, &free_library, &std_stream_out, &std_stream_in, &onexit);
        __start_xrvm_p(handle, argv[0], pcode, codelen, arglist.size(), &arglist[0], &error);
        //LOGD("QXLibrary: %s err = %d", "qt start --------------------------------------8", error);
    }

    return 0;
}


#endif
