#include "qxlibrary_global.h"
#include "QXApplication.h"

//#include<QtPlugin>  // for release
#if defined(QT_NO_OPENGL)
typedef unsigned int GLenum;
typedef unsigned char GLboolean;
typedef unsigned int GLbitfield;
typedef signed char GLbyte;
typedef short GLshort;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned int GLuint;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef ptrdiff_t GLsizeiptr;
typedef ptrdiff_t GLintptr;
typedef uint64_t GLuint64;
typedef int64_t GLint64;
typedef struct __GLsync *GLsync;
#endif
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



Q_IMPORT_PLUGIN(QGenericEnginePlugin)
Q_IMPORT_PLUGIN(QM3uPlaylistPlugin)

#include <QtPlugin>

#ifdef WIN32
Q_IMPORT_PLUGIN(AudioCaptureServicePlugin) //for releas
Q_IMPORT_PLUGIN(QWasapiPlugin)
Q_IMPORT_PLUGIN(DSServicePlugin)
Q_IMPORT_PLUGIN(QWindowsAudioPlugin)
Q_IMPORT_PLUGIN(WMFServicePlugin) //for releas
//Q_IMPORT_PLUGIN(QNativeWifiEnginePlugin)
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)
Q_IMPORT_PLUGIN(QWindowsPrinterSupportPlugin) //for releas
//Q_IMPORT_PLUGIN(AVFMediaPlayerServicePlugin)
//Q_IMPORT_PLUGIN(AVFServicePlugin)
#elif defined(__linux__)
Q_IMPORT_PLUGIN(QAlsaPlugin)
//Q_IMPORT_PLUGIN(QPulseAudioPlugin)
Q_IMPORT_PLUGIN(QComposePlatformInputContextPlugin)
Q_IMPORT_PLUGIN(QIbusPlatformInputContextPlugin)
//Q_IMPORT_PLUGIN(QVirtualKeyboardPlugin)
//#ifdef __arm__
//#include <QtPlugin>
//Q_IMPORT_PLUGIN(QLinuxFbIntegrationPlugin)
//#else
#include <QtPlugin>
Q_IMPORT_PLUGIN(QFcitxPlatformInputContextPlugin)
Q_IMPORT_PLUGIN(QXcbIntegrationPlugin)
//#endif
#elif defined(__APPLE__)
#include <QtPlugin>
Q_IMPORT_PLUGIN(CoreAudioPlugin)
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
int xhangle_reg_id = 0;

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
#if !defined(QT_NO_OPENGL)
#include <QGLWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#endif
#ifdef WIN32

bool CheckFileRelation(const char *strName, const char *strExt, const char *strAppKey) {
	bool nRet = false;
	HKEY hExtKey;
	char szPath[_MAX_PATH];
	DWORD dwSize = sizeof(szPath);
	QAudioDeviceInfo;
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
    /*if (QThread::currentThreadId() != ui_thread_id){
        XThread thread;
        gs_env->throwNativeException(thread.getThread(), "must from UIThread");
    }*/
}

XNLEXPORT xlong  XI_CDECL createQxApplication(XObject * x){
		
        _application = gs_env->referenceObject(x);
		MAX_METHOD = getEventMaxCount();
		methodIdent = new XIDENT[MAX_METHOD];
		ui_thread = gs_env->getContext(&ui_release);

        int onNotifyId = gs_env->getMethodId("/bool@/Qt/QApplication/onNotify(/Qt/QObject,/String,/String,/long,/int)");
        onNotify = gs_env->getVirtualMethod(x, onNotifyId);
		if (onNotify == 0) {
            QString s = QString("can not found Method in xlang : %1").arg("/bool@/Qt/QApplication/onNotify(/Qt/QObject,/String,/String,/long,/int)");
			gs_env->throwNativeException(ui_thread, s.toUtf8().data());
		}

        onNotifyId = gs_env->getMethodId("/*@/Qt/QApplication/onCreateXObject(/long,/String)");
        createObject = gs_env->getVirtualMethod(x, onNotifyId);
		if (createObject == 0) {
            QString s = QString("can not found Method in xlang : %1").arg("/*@/Qt/QApplication/onCreateXObject(/long,/String)");
			gs_env->throwNativeException(ui_thread, s.toUtf8().data());
		}

        

        memset(methodIdent, 0, sizeof(XIDENT) * MAX_METHOD);
        for (size_t i = 0; i < getEventSize(); i++) {
            XIDENT * pme = &methodIdent[megs[i].id];
            pme->path = methods[i].path;
            if (pme->path != NULL) {
                pme->methodId = gs_env->getMethodId(pme->path);
				if (pme->methodId == -1) {
                    QString s = QString("can not found Method in xlang : %1").arg(pme->path);
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

		XUILoader uiLoader;
        QFile file(uifilePath);
        file.open(QIODevice::ReadOnly);

        QWidget* getWidget = 0;
		
        if (parent != 0) {
                getWidget = uiLoader.load(&file, (QWidget*)parent);
        }else {
                getWidget = uiLoader.load(&file);
        }

        if (getWidget != NULL) {

				XMetaPtr objectData = new XObjectData();
                objectData->setObject(x);
                getWidget->setProperty(XHANDLE, MAKEPROPERTY(objectData));
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

		XUILoader uiLoader;

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
                getWidget->setProperty(XHANDLE, MAKEPROPERTY(objectData));
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
		case qtSurfaceFormat:
			return (xlong)new QSurfaceFormat();
			break;
		case qtAudioFormat:
			return (xlong)new QAudioFormat();
			break;
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
	case qtAudioInput:
		qobject = new XAudioInput(*(QAudioFormat*)param1, (QObject*)parent);
		break;

	case qtAudioOutput:
		qobject = new XAudioOutput(*(QAudioFormat*)param1, (QObject*)parent);
		break;

	case qtMediaPlayer:
		qobject = new QMediaPlayer((QObject*)parent, (QMediaPlayer::Flag)(param1));
		break;
	case qtPrinter:
	{
		QPrinter * qw = new QPrinter((QPrinter::PrinterMode)param1);
		return (xlong)qw;
	}
	break;
#ifndef MOBILE_APP
	case qtSciPrinter:
	{
		QsciPrinter * qw = new QsciPrinter((QPrinter::PrinterMode)param1);
		return (xlong)qw;
	}
	break;
#endif
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
		installAction(qobject);
		XObjectData * objectData = new XObjectData();
		objectData->setObject(x);
        qobject->setProperty(XHANDLE, MAKEPROPERTY(objectData));
	}

	return (xlong)qobject;
}

XNLEXPORT xlong  XI_CDECL createQSObject(xint type, XObject * x, xlong parent, xstring sparam) {
	checkMainThread();
	QObject * qobject = 0;

	switch (type)
	{
#ifndef MOBILE_APP
	case qtDockStyle:
		qobject = new VisualStudio2019Style(QString::fromUtf8(sparam), *(QByteArray*)parent);

		break;
	case qtDockWidgetPanel:
	{

		if (parent != 0) {
			qobject = new DockWidgetPanel(QString::fromUtf8(sparam), (DockPanelManager*)parent);
			/*if (qobject != NULL) {
				((DockWidgetPanel*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
			}*/
		}
	}
	break;
	case qtDockToolBar:
		qobject = new DockToolBar(QString::fromUtf8(sparam), (QWidget*)parent);
		if (qobject != NULL) {
			((DockToolBar*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
		}
	break;
#endif
	}


	if (qobject != NULL) {
		installAction(qobject);
		XObjectData * objectData = new XObjectData();
		objectData->setObject(x);
        qobject->setProperty(XHANDLE, MAKEPROPERTY(objectData));
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
		case qtOpenGLWidget:
		{
#if !defined(QT_NO_OPENGL)
			XOpenGLWidget * qw = 0;
			if (parent != 0) {
				qw = new XOpenGLWidget((QWidget*)parent);
			}
			else {
				qw = new XOpenGLWidget();
			}

			qw->setAttribute(Qt::WA_DeleteOnClose, true);
			qobject = qw;
#endif
		}
			break;
		case qtVideoWidget:
		{
			QVideoWidget * qw = 0;
			if (parent != 0) {
				qw = new QVideoWidget((QWidget*)parent);
			}
			else {
				qw = new QVideoWidget();
			}

			qw->setAttribute(Qt::WA_DeleteOnClose, true);
			qobject = qw;

		}
			break;
#ifndef MOBILE_APP
		case qtDockPanelManager:
		{
			
			if (parent != 0) {
				qobject = new DockPanelManager((QWidget*)parent);
			}
		}
		break;
		case qtDockWidgetPanel:
		{

			if (parent != 0) {
				qobject = new DockWidgetPanel((DockPanelManager*)parent);
			}
			if (qobject != NULL) {
				//((DockWidgetPanel*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
			}
		}
		break;
		case qtDockDocumentPanel:
		{

			if (parent != 0) {
				qobject = new DockDocumentPanel((DockPanelManager*)parent);
			}
			if (qobject != NULL) {
				//((DockDocumentPanel*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
			}
		}
		break;
		case qtDockWindow:
		{

			if (parent != 0) {
				qobject = new DockWindow((DockPanelManager*)parent);
			}
			if (qobject != NULL) {
				//((DockWindow*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
			}
		}
		break;
		case qtmDockPanelManager:
		{

			if (parent != 0) {
				qobject = new DockPanelManager((QMainWindow*)parent);
			}
		}
		break;
#endif
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
		case qtDockMainWindow:
		{
#ifndef MOBILE_APP
			QWidget * qw = 0;

			if (parent != 0) {
				qw = new DockMainWindow((QWidget*)parent);
			}
			else {
				qw = new DockMainWindow();
			}

			//qw->setAttribute(Qt::WA_DeleteOnClose, true);
			qobject = qw;
#endif
		}
		break;
#ifndef MOBILE_APP
        case qtSci:
                if (parent != 0) {
                        qobject = new QsciScintilla((QWidget*)parent);
                }else {
                        qobject = new QsciScintilla();
                }
                //ar.installSciAction((QsciScintilla*)qobject);
                ((QsciScintilla*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
                break;
#endif
        case qtPushButton:
                if (parent != 0) {
                        qobject = new QPushButton((QWidget*)parent);
                }
                else {
                        qobject = new QPushButton();
                }
               // ar.installButtonAction(qobject);
                break;

		case qtSystemTrayIcon:
			if (parent != 0) {
				qobject = new QSystemTrayIcon((QObject*)parent);
			}
			else {
				qobject = new QSystemTrayIcon();
			}
			break;
		case qtCalendarWidget:
			if (parent != 0) {
				qobject = new QCalendarWidget((QWidget*)parent);
			}
			else {
				qobject = new QCalendarWidget();
			}
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
                break;
#ifndef MOBILE_APP
		case qtDockBarManager:
			if (parent != 0) {
				qobject = new DockBarManager((QWidget*)parent);
			}
			break;
		case qtDockToolBar:
			qobject = new DockToolBar((QWidget*)parent);
			//((DockToolBar*)qobject)->setAttribute(Qt::WA_DeleteOnClose);
			break;
#endif
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
#ifndef MOBILE_APP
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
#endif
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
#ifndef MOBILE_APP
		case qtReportEngine:

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
            qobject->setProperty(XHANDLE, MAKEPROPERTY(objectData));
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
                env->releaseEnv(gs_env);
        }
        //_CrtDumpMemoryLeaks();
        return 0;
}


XNLEXPORT void XI_CDECL widget_set_vint_value(xlong h, xint proid, xint value) {
        checkMainThread();
        switch (proid)
        {
		case QSURFACEFORMAT_SETSWAPINTERVAL:
			((QSurfaceFormat*)h)->setSwapInterval((QSurfaceFormat::FormatOption)value);
			break;

		case QSURFACEFORMAT_SETOPTIONS:
			((QSurfaceFormat*)h)->setOptions((QSurfaceFormat::FormatOption)value);
			break;

		case QSURFACEFORMAT_SETMINORVERSION:
			((QSurfaceFormat*)h)->setMinorVersion(value);
			break;

		case QSURFACEFORMAT_SETMAJORVERSION:
			((QSurfaceFormat*)h)->setMajorVersion(value);
			break;

		case QSURFACEFORMAT_SETRENDERABLETYPE:
			((QSurfaceFormat*)h)->setRenderableType((QSurfaceFormat::RenderableType)value);
			break;

		case QSURFACEFORMAT_SETSWAPBEHAVIOR:
			((QSurfaceFormat*)h)->setSwapBehavior((QSurfaceFormat::SwapBehavior)value);
			break;

		case QSURFACEFORMAT_SETSAMPLES:
			((QSurfaceFormat*)h)->setSamples(value);
			break;

		case QSURFACEFORMAT_SETALPHABUFFERSIZE:
			((QSurfaceFormat*)h)->setAlphaBufferSize(value);
			break;

		case QSURFACEFORMAT_SETBLUEBUFFERSIZE:
			((QSurfaceFormat*)h)->setBlueBufferSize(value);
			break;

		case QSURFACEFORMAT_SETGREENBUFFERSIZE:
			((QSurfaceFormat*)h)->setGreenBufferSize(value);
			break;

		case QSURFACEFORMAT_SETREDBUFFERSIZE:
			((QSurfaceFormat*)h)->setRedBufferSize(value);
			break;

		case QSURFACEFORMAT_SETSTENCILBUFFERSIZE:
			((QSurfaceFormat*)h)->setStencilBufferSize(value);
			break;

		case QSURFACEFORMAT_SETDEPTHBUFFERSIZE:
			((QSurfaceFormat*)h)->setDepthBufferSize(value);
			break;

		case QOPENGLWIDGET_SETUPDATEBEHAVIOR:
#if !defined(QT_NO_OPENGL)
			((XOpenGLWidget*)h)->setUpdateBehavior((XOpenGLWidget::UpdateBehavior)value);
#endif
			break;

		case QAUDIOOUTPUT_SETNOTIFYINTERVAL:
			((XAudioOutput*)h)->setNotifyInterval(value);
			break;

		case QAUDIOOUTPUT_SETBUFFERSIZE:
			((XAudioOutput*)h)->setBufferSize(value);
			break;

		case QAUDIOINPUT_SETNOTIFYINTERVAL:
			((XAudioInput*)h)->setNotifyInterval(value);
			break;

		case QAUDIOINPUT_SETBUFFERSIZE:
			((XAudioInput*)h)->setBufferSize(value);
			break;

		case QAUDIOFORMAT_SETSAMPLETYPE:
			((QAudioFormat*)h)->setSampleType((QAudioFormat::SampleType)value);
			break;
		case QAUDIOFORMAT_SETBYTEORDER:
			((QAudioFormat*)h)->setByteOrder((QAudioFormat::Endian)value);
			break;
		case QAUDIOFORMAT_SETSAMPLESIZE:
			((QAudioFormat*)h)->setSampleSize(value);
			break;
		case QAUDIOFORMAT_SETCHANNELCOUNT:
			((QAudioFormat*)h)->setChannelCount(value);
			break;
		case QAUDIOFORMAT_SETSAMPLERATE:
			((QAudioFormat*)h)->setSampleRate(value);
			break;
		case QVIDEOWIDGET_SETSATURATION:
			((QVideoWidget*)h)->setSaturation(value);
			break;
		case QVIDEOWIDGET_SETHUE:
			((QVideoWidget*)h)->setHue(value);
			break;
		case QVIDEOWIDGET_SETCONTRAST:
			((QVideoWidget*)h)->setContrast(value);
			break;
		case QVIDEOWIDGET_SETBRIGHTNESS:
			((QVideoWidget*)h)->setBrightness(value);
			break;
		case QVIDEOWIDGET_SETASPECTRATIOMODE:
			((QVideoWidget*)h)->setAspectRatioMode((Qt::AspectRatioMode)value);
			break;
		case QMEDIAPLAYER_SETVOLUME:
			((QMediaPlayer*)h)->setVolume(value);
			break;
		case QMEDIAPLAYER_SETAUDIOROLE:
			((QMediaPlayer*)h)->setAudioRole((QAudio::Role)value);
			break;
		case QMEDIAOBJECT_SETNOTIFYINTERVAL:
			((QMediaObject*)h)->setNotifyInterval(value);
			break;
#ifndef MOBILE_APP
		case QTNDS_SETTHEME:
			((VisualStudio2019Style*)h)->setTheme((VisualStudio2019Style::Theme)value);
			break;
		case QTNDWP_SETFEATURES:
			((DockWidgetPanel*)h)->setFeatures((DockWidgetPanel::DockPanelFeatures)value);
			break;
		case QTNDWP_SETALLOWEDAREAS:
			((DockWidgetPanel*)h)->setAllowedAreas((DockPanelAreas)value);
			break;
		case QTNQPM_SETDEFAULTPANEFEATURES:
			((DockPanelManager*)h)->setDefaultPaneFeatures((DockWidgetPanel::DockPanelFeatures)value);
			break;
		case QTNQPM_SETMARGIN:
			((DockPanelManager*)h)->setMargin(value);
			break;
		case QTNWT_SETBACKGROUNDCOLOR:
			((WindowTitleBar*)h)->setBackgroundColor(QColor(value));
			break;
		case QTNWT_SETSYSBUTTONKIND:
			((WindowTitleBar*)h)->setSysButtonKind((WindowTitleBar::SysButtonKind)value);
			break;
		case QTNWT_SETBORDERTHICKNESS:
			((WindowTitleBar*)h)->setBorderThickness(value);
			break;
		case QTNWT_SETTITLEHEIGHT:
			((WindowTitleBar*)h)->setTitleHeight(value);
			break;
#endif
		case QLABEL_SETALIGNMENT:
			((QLabel*)h)->setAlignment((Qt::Alignment)value);
			break;
		case QLAYOUT_SETMARGIN:
			((QLayout*)h)->setMargin(value);
			break;
		case QTV_SETGRIDSTYLE:
			((QTableView*)h)->setGridStyle((Qt::PenStyle)value);
			break;
		case QH_SETDEFAULTALIGNMENT:
			((QHeaderView*)h)->setDefaultAlignment((Qt::Alignment)value);
			break;

		case QH_SETMAXIMUMSECTIONSIZE:
			((QHeaderView*)h)->setMaximumSectionSize(value);
			break;

		case QH_SETMINIMUMSECTIONSIZE:
			((QHeaderView*)h)->setMinimumSectionSize(value);
			break;

		case QH_SETDEFAULTSECTIONSIZE:
			((QHeaderView*)h)->setDefaultSectionSize(value);
			break;

		case QH_SETRESIZECONTENTSPRECISION:
			((QHeaderView*)h)->setResizeContentsPrecision(value);
			break;
		case QH_SHOWSECTION:
			((QHeaderView*)h)->showSection(value);
			break;
		case QH_HIDESECTION:
			((QHeaderView*)h)->hideSection(value);
			break;
		case QH_RESIZESECTIONS:
			((QHeaderView*)h)->resizeSections((QHeaderView::ResizeMode)value);
			break;
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
		case QAUDIOFORMAT_FRAMESFORBYTES:
			return  (((QAudioFormat*)h)->framesForBytes(value));
			break;

		case QAUDIOFORMAT_BYTESFORFRAMES:
			return  (((QAudioFormat*)h)->bytesForFrames(value));
			break;

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
#if !defined(QT_NO_OPENGL)
		case QOPENGLFUNCTIONS_HASOPENGLFEATURE:
		{
			QOpenGLFunctions * titem = (QOpenGLFunctions *)h;
			return titem->hasOpenGLFeature((QOpenGLFunctions::OpenGLFeature)v);
		}
		break;
#endif
		case QSURFACEFORMAT_TESTOPTION:
		{
			QSurfaceFormat * titem = (QSurfaceFormat *)h;
			return titem->testOption((QSurfaceFormat::FormatOption)v);
		}
		break;

#ifndef MOBILE_APP
		case QTNDWP_ISAREAALLOWED:
		{
			DockWidgetPanel * titem = (DockWidgetPanel *)h;
			return titem->isAreaAllowed((DockPanelAreas)v);
		}
		break;
#endif
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
		case QSURFACEFORMAT_SETOPTION:
			((QSurfaceFormat*)h)->setOption((QSurfaceFormat::FormatOption)v, v1);
			break;
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
#ifdef QT_OPENGL_ES_2
		case QOPENGLFUNCTIONS_ES2_INITIALIZEOPENGLFUNCTIONS:
			return ((QOpenGLFunctions_ES2*)h)->initializeOpenGLFunctions();
#endif
			break;
		case QOPENGLFUNCTIONS_1_1_INITIALIZEOPENGLFUNCTIONS:
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
			return ((QOpenGLFunctions_1_1*)h)->initializeOpenGLFunctions();
#else
			return false;
#endif
			break;
		case QOPENGLFUNCTIONS_1_0_INITIALIZEOPENGLFUNCTIONS:
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
			return ((QOpenGLFunctions_1_0*)h)->initializeOpenGLFunctions();
#else
			return false;
#endif
			break;

		case QSURFACEFORMAT_STEREO:
			return ((QSurfaceFormat*)h)->stereo();
			break;
		case QSURFACEFORMAT_HASALPHA:
			return ((QSurfaceFormat*)h)->hasAlpha();
			break;
		case QOPENGLCONTEXT_SUPPORTSTHREADEDOPENGL:
#if !defined(QT_NO_OPENGL)
			return QOpenGLContext::supportsThreadedOpenGL();
			break;
		case QOPENGLCONTEXT_ISOPENGLES:
			return ((QOpenGLContext*)h)->isOpenGLES();
			break;
		case QOPENGLCONTEXT_ISVALID:
			return ((QOpenGLContext*)h)->isValid();
			break;
		case QOPENGLCONTEXT_CREATE:
			return ((QOpenGLContext*)h)->create();
			break;
		case QOPENGLWIDGET_ISVALID:
			return ((XOpenGLWidget*)h)->isValid();
#endif
			break;
		case QAUDIODEVICEINFO_ISNULL:
			return ((QAudioDeviceInfo*)h)->isNull();
			break;
		case QAUDIOFORMAT_ISVALID:
			return ((QAudioFormat*)h)->isValid();
			break;
		case QMEDIAPLAYER_ISVIDEOAVAILABLE:
			return ((QMediaPlayer*)h)->isVideoAvailable();
			break;
		case QMEDIAPLAYER_ISAUDIOAVAILABLE:
			return ((QMediaPlayer*)h)->isAudioAvailable();
			break;
		case QMEDIAPLAYER_ISMUTED:
			return ((QMediaPlayer*)h)->isMuted();
			break;
		case QMEDIAOBJECT_ISMETADATAAVAILABLE:
			return ((QMediaObject*)h)->isMetaDataAvailable();
			break;
		case QMEDIAOBJECT_ISAVAILABLE:
			return ((QMediaObject*)h)->isAvailable();
			break;
#ifndef MOBILE_APP
		case QTNDLP_ISEMPTY:
			return ((DockLayoutPanel*)h)->isEmpty();
			break;
		case QTNDWP_ISVALID:
			return ((DockWidgetPanel*)h)->isValid();
			break;
		case QTNDWP_SHOWPANEL:
			((DockWidgetPanel*)h)->showPanel();
			break;
		case QTNDWP_ISCLOSED:
			return ((DockWidgetPanel*)h)->isClosed();
			break;
		case QTNDWP_CLOSEPANEL:
			((DockWidgetPanel*)h)->closePanel();
			break;
		case QTNDWP_ISAUTOHIDE:
			return ((DockWidgetPanel*)h)->isAutoHide();
			break;
		case QTNDWP_ISACTIVE:
			return ((DockWidgetPanel*)h)->isActive();
			break;
		case QTNDWP_ACTIVATE:
			((DockWidgetPanel*)h)->activate();
			break;
		case QTNDWP_DEACTIVATE:
			((DockWidgetPanel*)h)->deactivate();
			break;
		case QTNDWP_ISFLOAT:
			return ((DockWidgetPanel*)h)->isFloat();
			break;
		case QTNDW_FINALIZATIONWINDOW:
			((DockWindow*)h)->finalizationWindow();
			break;
		case QTNQPM_BESTFIT:
			((DockPanelManager*)h)->bestFit();
			break;
		case QTNQPM_BEGINUPDATE:
			((DockPanelManager*)h)->beginUpdate();
			break;
		case QTNQPM_ENDUPDATE:
			((DockPanelManager*)h)->endUpdate();
			break;
		case QTNQPM_ISARROWMARKERSSHOWN:
			return ((DockPanelManager*)h)->isArrowMarkersShown();
			break;
		case QTNQPM_ISDOCKPANELTRANSPARENTWHILEDRAGGING:
			return ((DockPanelManager*)h)->isDockPanelTransparentWhileDragging();
			break;
		case QTNQPM_ISDOCKPANELFULLCONTENTSWHILEDRAGGINGSHOWN:
			return ((DockPanelManager*)h)->isDockPanelFullContentsWhileDraggingShown();
			break;
		case QTNQPM_CLEARDOCKPANELS:
			((DockPanelManager*)h)->clearDockPanels();
			break;
		case QTNWT_ISQWIZARDSUPPORTS:
			return ((WindowTitleBar*)h)->isQWizardSupports();
			break;
		case QTNWT_ISSYSMENUBUTTONVISIBLE:
			return ((WindowTitleBar*)h)->isSysMenuButtonVisible();
			break;
		case QTNWT_EXTENDVIEWINTOTITLEBAR:
			return ((WindowTitleBar*)h)->extendViewIntoTitleBar();
			break;
		case QTNWT_BLURBEHINDWINDOWENABLED:
			return ((WindowTitleBar*)h)->blurBehindWindowEnabled();
			break;
		case QTNWT_STYLEDFRAME:
			return ((WindowTitleBar*)h)->styledFrame();
			break;
		case QTNWT_ISVISIBLE:
			return ((WindowTitleBar*)h)->isVisible();
			break;
		case QTNCLEARDOCKPANELS:
			((DockMainWindow*)h)->clearDockPanels();
			break;
#endif
		case QTV_ISCORNERBUTTONENABLED:
			return ((QTableView*)h)->isCornerButtonEnabled();
			break;

		case QTV_WORDWRAP:
			return ((QTableView*)h)->wordWrap();
			break;

		case QTV_SHOWGRID:
			return ((QTableView*)h)->showGrid();
			break;

		case QTV_ISSORTINGENABLED:
			return ((QTableView*)h)->isSortingEnabled();
			break;

		case QH_SECTIONSMOVABLE:
			return ((QHeaderView*)h)->sectionsMovable();
			break;

		case QH_SECTIONSHIDDEN:
			return ((QHeaderView*)h)->sectionsHidden();
			break;

		case QH_SECTIONSMOVED:
			return ((QHeaderView*)h)->sectionsMoved();
			break;

		case QH_CASCADINGSECTIONRESIZES:
			return ((QHeaderView*)h)->cascadingSectionResizes();
			break;

		case QH_STRETCHLASTSECTION:
			return ((QHeaderView*)h)->stretchLastSection();
			break;

		case QH_ISSORTINDICATORSHOWN:
			return ((QHeaderView*)h)->isSortIndicatorShown();
			break;

		case QH_HIGHLIGHTSECTIONS:
			return ((QHeaderView*)h)->highlightSections();
			break;

		case QH_SECTIONSCLICKABLE:
			return ((QHeaderView*)h)->sectionsClickable();
			break;

		case QSTI_SUPPORTSMESSAGES:
			return QSystemTrayIcon::supportsMessages();
			break;

		case QSTI_ISSYSTEMTRAYAVAILABLE:
			return QSystemTrayIcon::isSystemTrayAvailable();
			break;

		case QSTI_VISIBLE:
			return ((QSystemTrayIcon*)h)->isVisible();
			break;
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
#ifndef MOBILE_APP
		case QTNCLEARDOCKBARS:
			((DockMainWindow*)h)->clearDockBars();
			break;
#endif
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
		case QOPENGLCONTEXT_GLOBALSHARECONTEXT:
#if !defined(QT_NO_OPENGL)
			xobj = getObjectControl(QOpenGLContext::globalShareContext());
			break;
		case QOPENGLCONTEXT_CURRENTCONTEXT:
			xobj = getObjectControl(QOpenGLContext::currentContext());
			break;
		case QOPENGLCONTEXT_SHARECONTEXT:
			xobj = getObjectControl((((QOpenGLContext*)(h))->shareContext()));
			break;
		case QOPENGLWIDGET_CONTEXT:
			xobj = getObjectControl((((XOpenGLWidget*)(h))->context()));
#endif
		break;
		case QVIDEOWIDGET_MEDIAOBJECT:
			xobj = getObjectControl(((QVideoWidget*)h)->mediaObject());
			break;
		case QMEDIAOBJECT_SERVICE:
			xobj = getObjectControl(((QMediaObject*)h)->service());
			break;
#ifndef MOBILE_APP
		case QTNWTB_GET:
			xobj = getObjectControl(WindowTitleBar::get((QWidget*)h));
			break;
		case QTNWTB_FIND:
			xobj = getObjectControl(WindowTitleBar::find((QWidget*)h));
			break;
		case QTNDWP_WIDGET:
			xobj = getObjectControl(((DockWidgetPanel*)h)->widget());
			break;
		case QTNDWP_MENUBUTTON:
			xobj = getObjectControl(((DockWidgetPanel*)h)->menuButton());
			break;
		case QTNDWP_VISIBLEACTION:
			xobj = getObjectControl(((DockWidgetPanel*)h)->visibleAction());
			break;
		case QTNDWP_TITLEBAR:
			xobj = getObjectControl(((DockWidgetPanel*)h)->titleBar());
			break;
		case QTNDPB_DOCKWINDOW:
			xobj = getObjectControl(((DockPanelBase*)h)->dockWindow());
			break;
		case QTNDPB_TOPDOCKWINDOW:
			xobj = getObjectControl(((DockPanelBase*)h)->topDockWindow());
			break;
		case QTNDPB_PARENTPANEL:
			xobj = getObjectControl(((DockPanelBase*)h)->parentPanel());
			break;
		case QTNDPB_DOCKMANAGER:
			xobj = getObjectControl(((DockPanelBase*)h)->dockManager());
			break;
		case QTNDW_LAYOUTPANEL:
			xobj = getObjectControl(((DockWindow*)h)->layoutPanel());
			break;
		case QTNDW_DOCKMANAGER:
			xobj = getObjectControl(((DockWindow*)h)->dockManager());
			break;
		case QTNQPM_CENTRALWIDGET:
			xobj = getObjectControl(((DockPanelManager*)h)->centralWidget());
			break;
		case QTNQPM_ACTIVEDOCKPANEL:
			xobj = getObjectControl(((DockPanelManager*)h)->activeDockPanel());
			break;
		case QTNQPM_CENTRALLAYOUTPANEL:
			xobj = getObjectControl(((DockPanelManager*)h)->centralLayoutPanel());
			break;
		case QTNQPM_LAYOUTPANEL:
			xobj = getObjectControl(((DockPanelManager*)h)->layoutPanel());
			break;
		case QTNQPM_MANAGEDWIDGET:
			xobj = getObjectControl(((DockPanelManager*)h)->managedWidget());
			break;
		case QTNDB_CENTRALWIDGET:
			xobj = getObjectControl(((DockBarManager*)h)->centralWidget());
			break;
		case QTNDB_MANAGEDWIDGET:
			xobj = getObjectControl(((DockBarManager*)h)->managedWidget());
			break;
		case QTNWT_WIDGET:
			xobj = getObjectControl(((WindowTitleBar*)h)->widget());
			break;
#endif
		case QTW_HORIZONTALHEADER:
			xobj = getObjectControl(((QTableWidget*)h)->horizontalHeader());
			break;
		case QTW_VERTICALHEADER:
			xobj = getObjectControl(((QTableWidget*)h)->verticalHeader());
			break;
		case QSTI_GETCONTEXTMENU:
			xobj = getObjectControl(((QSystemTrayIcon*)h)->contextMenu());
			break;
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
#ifndef MOBILE_APP
		case QTNMENUBAR:
			xobj = getObjectControl(((DockMainWindow*)h)->menuBar());
			break;
		case QTNTITLEBAR:
			xobj = getObjectControl(((DockMainWindow*)h)->titleBar());
			break;
		case QTNTITLEBARWIDGET:
			xobj = getObjectControl(((DockMainWindow*)h)->titleBarWidget());
			break;
		case QTNSTATUSBAR:
			xobj = getObjectControl(((DockMainWindow*)h)->statusBar());
			break;
#endif
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
#ifndef MOBILE_APP
		case QTNCENTRALWIDGET:
			xobj = getObjectControl(((DockMainWindow*)h)->centralWidget());
			break;
		case QTNDOCKBARMANAGER:
			xobj = getObjectControl(((DockMainWindow*)h)->dockBarManager());
			break;
		case QTNDOCKPANELMANAGER:
			xobj = getObjectControl(((DockMainWindow*)h)->dockPanelManager());
			break;
#endif
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
                XMetaPtr objectData =(((QObject*)h)->property(XHANDLE).GETPROPERTY_VALUE);
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
		case QMEDIAPLAYER_SUPPORTEDAUDIOROLES:
		{
			QList<QAudio::Role> qar = ((QMediaPlayer*)h)->supportedAudioRoles();
			size_t tc = qar.size();
			XObject * objs = gs_env->createIntArray(tc);

			xint *lva = new xint[tc];

			for (size_t i = 0; i < tc; i++) {
				lva[i] = qar[i];
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
#ifndef MOBILE_APP
		case DBMSAVESTATE:
		{
			QBuffer data;
			if (data.open(QBuffer::WriteOnly)) {
				((DockBarManager *)h)->saveStateToDevice(&data);
			}
			XObject * objs = gs_env->createByteArray(data.size());
			const QByteArray & qb = data.data();
			gs_env->setElementValue(objs, 0, (xbyte*)qb.data(), qb.size());
			return objs;
		}
		break;

		case DPMSAVESTATE:
		{
			QBuffer data;
			if (data.open(QBuffer::WriteOnly)) {
				((DockPanelManager *)h)->saveStateToDevice(&data);
			}
			XObject * objs = gs_env->createByteArray(data.size());
			const QByteArray & qb = data.data();
			gs_env->setElementValue(objs, 0, (xbyte*)qb.data(), qb.size());
			return objs;
		}
		break;

		case DMSAVESTATE:
		{
			QBuffer data, data1;
			if (data.open(QBuffer::WriteOnly) && data1.open(QBuffer::WriteOnly)) {
				((DockMainWindow *)h)->saveStateToDevice(&data, &data1);
			}
			XObject * objs = gs_env->createByteArray(data.size() + sizeof(xint) + data1.size());
			const QByteArray & qb = data.data();
			const QByteArray & qb1 = data1.data();
			xint start = data.size();

			gs_env->setElementValue(objs, 0, (xbyte*)&start, sizeof(xint));
			gs_env->setElementValue(objs, sizeof(xint), (xbyte*)qb.data(), qb.size());
			gs_env->setElementValue(objs, sizeof(xint) + qb.size(), (xbyte*)qb1.data(), qb1.size());
			return objs;
		}
		break;
#endif

		case QH_SAVESTATE:
		{
			QByteArray data = ((QHeaderView*)h)->saveState();
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
		case QAUDIOOUTPUT_VOLUME:
			return ((QAudioOutput*)h)->volume();
			break;
		case QAUDIOINPUT_VOLUME:
			return ((QAudioInput*)h)->volume();
			break;
		case QMEDIAPLAYER_PLAYBACKRATE:
			return ((QMediaPlayer*)h)->playbackRate();
			break;
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
		case QAUDIOOUTPUT_SETVOLUME:
			((QAudioOutput*)h)->setVolume(v);
			break;

		case QAUDIOINPUT_SETVOLUME:
			((QAudioInput*)h)->setVolume(v);
			break;

		case QMEDIAPLAYER_SETPLAYBACKRATE:
			((QMediaPlayer*)h)->setPlaybackRate(v);
			break;
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
		case QSURFACEFORMAT_SETSTEREO:
			return ((QSurfaceFormat*)h)->setStereo(v);
			break;
		case QVIDEOWIDGET_SETFULLSCREEN:
			return ((QVideoWidget*)h)->setFullScreen(v);
			break;
		case QMEDIAPLAYER_SETMUTED:
			return ((QMediaPlayer*)h)->setMuted(v);
			break;
		case QSCI_ENABLESCROLLBARMARKER:
			return ((QsciScintilla*)h)->setMarkedScrollEnabled(v);
			break;
#ifndef MOBILE_APP
		case QTNDWP_SETAUTOHIDE:
			return ((DockWidgetPanel*)h)->setAutoHide(v);
			break;
		case QTNDWP_SETFLOAT:
			return ((DockWidgetPanel*)h)->setFloat(v);
			break;
		case QTNQPM_SETARROWMARKERSSHOWN:
			return ((DockPanelManager*)h)->setArrowMarkersShown(v);
			break;
		case QTNQPM_SETDOCKPANELTRANSPARENTWHILEDRAGGING:
			return ((DockPanelManager*)h)->setDockPanelTransparentWhileDragging(v);
			break;
		case QTNQPM_SETDOCKPANELFULLCONTENTSWHILEDRAGGINGSHOWN:
			return ((DockPanelManager*)h)->setDockPanelFullContentsWhileDraggingShown(v);
			break;
		case QTNWT_SETQWIZARDSUPPORTS:
			return ((WindowTitleBar*)h)->setQWizardSupports(v);
			break;
		case QTNWT_SETSYSMENUBUTTONVISIBLE:
			return ((WindowTitleBar*)h)->setSysMenuButtonVisible(v);
			break;
		case QTNWT_SETEXTENDVIEWINTOTITLEBAR:
			return ((WindowTitleBar*)h)->setExtendViewIntoTitleBar(v);
			break;
		case QTNWT_SETBLURBEHINDWINDOWENABLED:
			return ((WindowTitleBar*)h)->setBlurBehindWindowEnabled(v);
			break;
		case QTNWT_SETSTYLEDFRAME:
			return ((WindowTitleBar*)h)->setStyledFrame(v);
			break;
		case QTNWT_SETVISIBLE:
			return ((WindowTitleBar*)h)->setVisible(v);
			break;
#endif
		case QTV_SETCORNERBUTTONENABLED:
			return ((QTableView*)h)->setCornerButtonEnabled(v);
			break;

		case QTV_SETWORDWRAP:
			return ((QTableView*)h)->setWordWrap(v);
			break;

		case QTV_SETSORTINGENABLED:
			((QTableView*)h)->setSortingEnabled(v);
			break;

		case QH_SETCASCADINGSECTIONRESIZES:
			((QHeaderView*)h)->setCascadingSectionResizes(v);
			break;

		case QH_SETSTRETCHLASTSECTION:
			((QHeaderView*)h)->setStretchLastSection(v);
			break;

		case QH_SETSORTINDICATORSHOWN:
			((QHeaderView*)h)->setSortIndicatorShown(v);
			break;

		case QH_SETHIGHLIGHTSECTIONS:
			((QHeaderView*)h)->setHighlightSections(v);
			break;

		case QH_SETSECTIONSCLICKABLE:
			((QHeaderView*)h)->setSectionsClickable(v);
			break;

		case QH_SETSECTIONSMOVABLE:
			((QHeaderView*)h)->setSectionsMovable(v);
			break;

		case QSTI_SETVISIBLE:
			((QSystemTrayIcon*)h)->setVisible(v);
			break;

		case QCW_SETGRIDVISIBLE:
			((QCalendarWidget*)h)->setGridVisible(v);
			break;

		case QCW_SETNAVIGATIONBARVISIBLE:
			((QCalendarWidget*)h)->setNavigationBarVisible(v);
			break;

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
#if !defined(QT_NO_OPENGL)
		case QOPENGLFUNCTIONS_OPENGLFEATURES:
			return ((QOpenGLFunctions*)h)->openGLFeatures();
			break;
#endif
		case QSURFACEFORMAT_DEPTHBUFFERSIZE:
			return ((QSurfaceFormat*)h)->depthBufferSize();
			break;

		case QSURFACEFORMAT_STENCILBUFFERSIZE:
			return ((QSurfaceFormat*)h)->stencilBufferSize();
			break;

		case QSURFACEFORMAT_REDBUFFERSIZE:
			return ((QSurfaceFormat*)h)->redBufferSize();
			break;

		case QSURFACEFORMAT_GREENBUFFERSIZE:
			return ((QSurfaceFormat*)h)->greenBufferSize();
			break;

		case QSURFACEFORMAT_BLUEBUFFERSIZE:
			return ((QSurfaceFormat*)h)->blueBufferSize();
			break;

		case QSURFACEFORMAT_ALPHABUFFERSIZE:
			return ((QSurfaceFormat*)h)->alphaBufferSize();
			break;

		case QSURFACEFORMAT_SAMPLES:
			return ((QSurfaceFormat*)h)->samples();
			break;

		case QSURFACEFORMAT_SWAPBEHAVIOR:
			return ((QSurfaceFormat*)h)->swapBehavior();
			break;

		case QSURFACEFORMAT_RENDERABLETYPE:
			return ((QSurfaceFormat*)h)->renderableType();
			break;

		case QSURFACEFORMAT_MAJORVERSION:
			return ((QSurfaceFormat*)h)->majorVersion();
			break;

		case QSURFACEFORMAT_MINORVERSION:
			return ((QSurfaceFormat*)h)->minorVersion();
			break;

		case QSURFACEFORMAT_OPTIONS:
			return ((QSurfaceFormat*)h)->options();
			break;

		case QSURFACEFORMAT_SWAPINTERVAL:
			return ((QSurfaceFormat*)h)->swapInterval();
			break;

		case QOPENGLCONTEXT_OPENGLMODULETYPE:
#if !defined(QT_NO_OPENGL)
			return ((QOpenGLContext*)h)->openGLModuleType();
			break;

		case QOPENGLCONTEXT_DEFAULTFRAMEBUFFEROBJECT:
			return ((QOpenGLContext*)h)->defaultFramebufferObject();
			break;

		case QOPENGLWIDGET_DEFAULTFRAMEBUFFEROBJECT:
			return ((XOpenGLWidget*)h)->defaultFramebufferObject();
			break;

		case QOPENGLWIDGET_UPDATEBEHAVIOR:
			return ((XOpenGLWidget*)h)->updateBehavior();
#endif
			break;

		case QAUDIODEVICEINFO_SUPPORTEDBYTEORDERS:
		{
			xint flag = 0;
			QList<QAudioFormat::Endian> qe = ((QAudioDeviceInfo*)h)->supportedByteOrders();
			for (int i = 0; i < qe.size(); i++) {
				flag |= qe[i] + 1;
			}
			return flag;
		}
			break;

		case QAUDIOINPUT_STATE:
			return ((XAudioInput*)h)->state();
			break;

		case QAUDIOINPUT_ERROR:
			return ((XAudioInput*)h)->error();
			break;

		case QAUDIOINPUT_NOTIFYINTERVAL:
			return ((XAudioInput*)h)->notifyInterval();
			break;

		case QAUDIOINPUT_PERIODSIZE:
			return ((XAudioInput*)h)->periodSize();
			break;

		case QAUDIOINPUT_BUFFERSIZE:
			return ((XAudioInput*)h)->bufferSize();
			break;

			//-----
		case QAUDIOOUTPUT_STATE:
			return ((XAudioOutput*)h)->state();
			break;

		case QAUDIOOUTPUT_ERROR:
			return ((XAudioOutput*)h)->error();
			break;

		case QAUDIOOUTPUT_NOTIFYINTERVAL:
			return ((XAudioOutput*)h)->notifyInterval();
			break;

		case QAUDIOOUTPUT_PERIODSIZE:
			return ((XAudioOutput*)h)->periodSize();
			break;

		case QAUDIOOUTPUT_BYTESFREE:
			return ((XAudioOutput*)h)->bytesFree();
			break;

		case QAUDIOOUTPUT_BUFFERSIZE:
			return ((XAudioOutput*)h)->bufferSize();
			break;

		case QAUDIOFORMAT_BYTESPERFRAME:
			return ((QAudioFormat*)h)->bytesPerFrame();
			break;
		case QAUDIOFORMAT_SAMPLETYPE:
			return ((QAudioFormat*)h)->sampleType();
			break;
		case QAUDIOFORMAT_BYTEORDER:
			return ((QAudioFormat*)h)->byteOrder();
			break;
		case QAUDIOFORMAT_SAMPLESIZE:
			return ((QAudioFormat*)h)->sampleSize();
			break;
		case QAUDIOFORMAT_CHANNELCOUNT:
			return ((QAudioFormat*)h)->channelCount();
			break;
		case QAUDIOFORMAT_SAMPLERATE:
			return ((QAudioFormat*)h)->sampleRate();
			break;
		case QVIDEOWIDGET_SATURATION:
			return ((QVideoWidget*)h)->saturation();
			break;
		case QVIDEOWIDGET_HUE:
			return ((QVideoWidget*)h)->hue();
			break;
		case QVIDEOWIDGET_CONTRAST:
			return ((QVideoWidget*)h)->contrast();
			break;
		case QVIDEOWIDGET_BRIGHTNESS:
			return ((QVideoWidget*)h)->brightness();
			break;
		case QVIDEOWIDGET_ASPECTRATIOMODE:
			return ((QVideoWidget*)h)->aspectRatioMode();
			break;
		case QMEDIAPLAYER_AUDIOROLE:
			return ((QMediaPlayer*)h)->audioRole();
			break;
		case QMEDIAPLAYER_AVAILABILITY:
			return ((QMediaPlayer*)h)->availability();
			break;
		case QMEDIAPLAYER_ERROR:
			return ((QMediaPlayer*)h)->error();
			break;
		case QMEDIAPLAYER_ISSEEKABLE:
			return ((QMediaPlayer*)h)->isSeekable();
			break;
		case QMEDIAPLAYER_BUFFERSTATUS:
			return ((QMediaPlayer*)h)->bufferStatus();
			break;
		case QMEDIAPLAYER_VOLUME:
			return ((QMediaPlayer*)h)->volume();
			break;
		case QMEDIAPLAYER_MEDIASTATUS:
			return ((QMediaPlayer*)h)->mediaStatus();
			break;
		case QMEDIAPLAYER_STATE:
			return ((QMediaPlayer*)h)->state();
			break;
		case QMEDIAOBJECT_NOTIFYINTERVAL:
			return ((QMediaObject*)h)->notifyInterval();
			break;
		case QMEDIAOBJECT_AVAILABILITY:
			return ((QMediaObject*)h)->availability();
			break;
#ifndef MOBILE_APP
		case QTNDS_THEME:
			return ((VisualStudio2019Style*)h)->theme();
			break;
		case QTNDLP_CHILDCOUNT:
			return ((DockLayoutPanel*)h)->childCount();
			break;
		case QTNDLP_LAYOUTTYPE:
			return ((DockLayoutPanel*)h)->layoutType();
			break;
		case QTNDWP_FEATURES:
			return ((DockWidgetPanel*)h)->features();
			break;
		case QTNDWP_ALLOWEDAREAS:
			return ((DockWidgetPanel*)h)->allowedAreas();
			break;
		case QTNQPM_DEFAULTPANEFEATURES:
			return ((DockPanelManager*)h)->defaultPaneFeatures();
			break;
		case QTNQPM_MARGIN:
			return ((DockPanelManager*)h)->margin();
			break;
		case QTNDB_DOCKBARCOUNT:
			return ((DockBarManager*)h)->dockBarCount();
			break;
		case QTNWT_FRAMECOLOR:
			return ((WindowTitleBar*)h)->frameColor().value();
			break;
		case QTNWT_BACKGROUNDCOLOR:
			return ((WindowTitleBar*)h)->backgroundColor().value();
			break;
		case QTNWT_SYSBUTTONKIND:
			return ((WindowTitleBar*)h)->sysButtonKind();
			break;
		case QTNWT_BORDERTHICKNESS:
			return ((WindowTitleBar*)h)->borderThickness();
			break;
		case QTNWT_TITLEHEIGHT:
			return ((WindowTitleBar*)h)->titleHeight();
			break;
#endif
		case QLABEL_GETALIGNMENT:
			return ((QLabel*)h)->alignment();
			break;
		case QTV_GRIDSTYLE:
			return ((QTableView*)h)->gridStyle();
			break;
		case QH_DEFAULTALIGNMENT:
			return ((QHeaderView*)h)->defaultAlignment();
			break;
		case QH_MAXIMUMSECTIONSIZE:
			return ((QHeaderView*)h)->maximumSectionSize();
			break;
		case QH_MINIMUMSECTIONSIZE:
			return ((QHeaderView*)h)->minimumSectionSize();
			break;
		case QH_DEFAULTSECTIONSIZE:
			return ((QHeaderView*)h)->defaultSectionSize();
			break;
		case QH_SORTINDICATORORDER:
			return ((QHeaderView*)h)->sortIndicatorOrder();
			break;
		case QH_SORTINDICATORSECTION:
			return ((QHeaderView*)h)->sortIndicatorSection();
			break;
		case QH_STRETCHSECTIONCOUNT:
			return ((QHeaderView*)h)->stretchSectionCount();
			break;
		case QH_RESIZECONTENTSPRECISION:
			return ((QHeaderView*)h)->resizeContentsPrecision();
			break;
		case QH_COUNT:
			return ((QHeaderView*)h)->count();
			break;
		case QH_HIDDENSECTIONCOUNT:
			return ((QHeaderView*)h)->hiddenSectionCount();
			break;
		case QH_GETLENGTH:
			return ((QHeaderView*)h)->length();
			break;
		case QH_GETOFFSET:
			return ((QHeaderView*)h)->offset();
			break;
		case QH_ORIENTATION:
			return ((QHeaderView*)h)->orientation();
			break;
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
		case QSURFACEFORMAT_SETVERSION:
			((QSurfaceFormat*)h)->setVersion(xv, yv);
			break;

		case QTV_SORTBYCOLUMN:
			((QTableView*)h)->sortByColumn(xv, (Qt::SortOrder)yv);
			break;

		case QTV_COLUMNSPAN:
			return ((QTableView*)h)->columnSpan(xv, yv);
			break;

		case QTV_ROWSPAN:
			return ((QTableView*)h)->rowSpan(xv, yv);
			break;

		case QTV_SETCOLUMNHIDDEN:
			((QTableView*)h)->setColumnHidden(xv, yv != 0);
			break;

		case QTV_ISCOLUMNHIDDEN:
			return ((QTableView*)h)->isColumnHidden(xv) ? 1 : 0;
			break;
		case QTV_SETROWHIDDEN:
			((QTableView*)h)->setRowHidden(xv, yv != 0);
			break;

		case QTV_ISROWHIDDEN:
			return ((QTableView*)h)->isRowHidden(xv);
			break;

		case QTV_COLUMNWIDTH:
			return ((QTableView*)h)->columnWidth(xv);
			break;

		case QTV_SETCOLUMNWIDTH:
			((QTableView*)h)->setColumnWidth(xv, yv);
			break;

		case QTV_COLUMNAT:
			return ((QTableView*)h)->columnAt(xv);
			break;

		case QTV_COLUMNVIEWPORTPOSITION:
			return ((QTableView*)h)->columnViewportPosition(xv);
			break;

		case QTV_ROWHEIGHT:
			return ((QTableView*)h)->rowHeight(xv);
			break;

		case QTV_SETROWHEIGHT:
			((QTableView*)h)->setRowHeight(xv, yv);
			break;

		case QTV_ROWAT:
			return ((QTableView*)h)->rowAt(xv);
			break;

		case QTV_ROWVIEWPORTPOSITION:
			return ((QTableView*)h)->rowViewportPosition(xv);
			break;

		case QH_SETSORTINDICATOR:
			((QHeaderView*)h)->setSortIndicator(xv, (Qt::SortOrder)yv);
			break;

		case QH_SETSECTIONRESIZEMODE:
			((QHeaderView*)h)->setSectionResizeMode(xv, (QHeaderView::ResizeMode)yv);
			break;

		case QH_SECTIONRESIZEMODE:
			return ((QHeaderView*)h)->sectionResizeMode(xv);
			break;

		case QH_LOGICALINDEX:
			return ((QHeaderView*)h)->logicalIndex(xv);
			break;
		case QH_VISUALINDEX:
			return ((QHeaderView*)h)->visualIndex(xv);
			break;
		case QH_SETSECTIONHIDDEN:
			((QHeaderView*)h)->setSectionHidden(xv, yv != 0);
			break;
		case QH_ISSECTIONHIDDEN:
			return ((QHeaderView*)h)->isSectionHidden(xv) ? 1 : 0;
			break;
		case QH_RESIZESECTION:
			((QHeaderView*)h)->resizeSection(xv, yv);
			break;
		case QH_SWAPSECTIONS:
			((QHeaderView*)h)->swapSections(xv, yv);
			break;
		case QH_MOVESECTION:
			((QHeaderView*)h)->moveSection(xv, yv);
			break;
		case QH_SECTIONVIEWPORTPOSITION:
			return ((QHeaderView*)h)->sectionViewportPosition(xv);
			break;
		case QH_SECTIONPOSITION:
			return ((QHeaderView*)h)->sectionPosition(xv);
			break;
		case QH_SECTIONSIZE:
			return ((QHeaderView*)h)->sectionSize(xv);
			break;
		case QH_LOGICALINDEXATXY:
			return ((QHeaderView*)h)->logicalIndexAt(xv, yv);
			break;
		case QH_LOGICALINDEXAT:
			return ((QHeaderView*)h)->logicalIndexAt(xv);
			break;
		case QH_VISUALINDEXAT:
			return ((QHeaderView*)h)->visualIndexAt(xv);
			break;
		case QH_SECTIONSIZEHINT:
			return ((QHeaderView*)h)->sectionSizeHint(xv);
				break;
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
		case QTV_SETSPAN:
		{
			((QTableView*)h)->setSpan(v1, v2, v3, v4);

		}
		break;

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
		case QSCI_SETSCROLLBARMARKER:
			((QsciScintilla*)h)->enableScrollMark(v1, v2, v3);
			break;
		case QCW_SETSELECTEDDATE:
			((QCalendarWidget*)h)->setSelectedDate(QDate(v1 , v2 , v3 ));
			break;
		case QCW_SETDATERANGE:
			((QCalendarWidget*)h)->setDateRange(QDate(v1 >> 16, v2 >> 16, v3 >> 16), QDate(v1 & 0xffff, v2 & 0xffff, v3 & 0xffff));
			break;
		case QCW_SETCURRENTPAGE:
			 ((QCalendarWidget*)h)->setCurrentPage(v1, v2);
			break;
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
		case QSURFACEFORMAT_SETDEFAULTFORMAT:
		{
			QSurfaceFormat::setDefaultFormat(*(QSurfaceFormat*)value);
		}
		break;

		case QOPENGLCONTEXT_SETSHARECONTEXT:
		{
#if !defined(QT_NO_OPENGL)
			((QOpenGLContext*)h)->setShareContext((QOpenGLContext*)(value));
		}
		break;

		case QOPENGLCONTEXT_SETFORMAT:
		{
			((QOpenGLContext*)h)->setFormat(*(QSurfaceFormat*)(value));
		}
		break;

		case QOPENGLWIDGET_SETFORMAT:
		{

			((XOpenGLWidget*)h)->setFormat(*(QSurfaceFormat*)(value));
#endif
		}
		break;

		case QMEDIAPLAYER_SETPOSITION:
		{
			((QMediaPlayer*)h)->setPosition((value));
		}
		break;
		case QTMW_SETCENTRALWIDGET:
		{
			((QMainWindow*)h)->setCentralWidget((QWidget*)(value));
		}
		break;
		case QTAPP_SETSTYLE:
		{
			((QApplication*)h)->setStyle((QStyle*)(value));
		}
		break;
#ifndef MOBILE_APP
		case QTNDDP_SETWIDGET:
		{
			((DockDocumentPanel*)h)->setWidget((QWidget*)(value));
		}
		break;
		case QTNDWP_SETWIDGET:
		{
			((DockWidgetPanel*)h)->setWidget((QWidget*)(value));
		}
		break;
		case QTNDWP_SETICON:
		{
			((DockWidgetPanel*)h)->setIcon(*(QIcon*)(value));
		}
		break;
		case QTNDWP_SETMENUBUTTON:
		{
			((DockWidgetPanel*)h)->setMenuButton((QMenu*)(value));
		}
		break;
		case QTNDWP_SETTITLEBAR:
		{
			((DockWidgetPanel*)h)->setTitleBar((QWidget*)(value));
		}
		break;
		case QTNDWP_SETPARENTPANEL:
		{
			((DockWidgetPanel*)h)->setParentPanel((DockPanelBase*)(value));
		}
		break;
		case QTNQPM_SETCENTRALWIDGET:
		{
			((DockPanelManager*)h)->setCentralWidget((QWidget*)(value));
		}
		break;
		case QTNQPM_CLOSEDOCKPANEL:
		{
			((DockPanelManager*)h)->closeDockPanel((DockWidgetPanel*)(value));
		}
		break;
		case QTNQPM_REMOVEDOCKPANEL:
		{
			((DockPanelManager*)h)->removeDockPanel((DockWidgetPanel*)(value));
		}
		break;
		case QTNDB_SETCENTRALWIDGET:
		{
			((DockBarManager*)h)->setCentralWidget((QWidget*)(value));
		}
		break;
		case QTNDB_REMOVEDOCKBAR:
		{
			((DockBarManager*)h)->removeDockBar((DockToolBar*)(value));
		}
		break;
		case QTNREMOVEDOCKPANEL:
		{
			((DockMainWindow*)h)->removeDockPanel((DockWidgetPanel*)(value));
		}
		break;
		case QTNREMOVEDOCKBAR:
		{
			((DockMainWindow*)h)->removeDockBar((DockToolBar*)(value));
		}
		break;
#endif
		case QSTI_SETCONTEXTMENU:
		{
			((QSystemTrayIcon*)h)->setContextMenu((QMenu*)(value));
		}
		break;
		case QSTI_SETICON:
		{
			((QSystemTrayIcon*)h)->setIcon(*(QIcon*)(value));
		}
		break;
		case QW_SETICON:
		{
			((QWidget*)h)->setWindowIcon(*(QIcon*)(value));
		}
		break;
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


		case QAUDIOFORMAT_SETCODEC:
			((QAudioFormat*)h)->setCodec(QString::fromUtf8(value));

			break;
		case QTAPP_SETSTYLE:
			((QApplication*)h)->setStyle(QString::fromUtf8(value));

			break;
#ifndef MOBILE_APP
		case QTNDWP_SETCAPTION:
			((DockWidgetPanel*)h)->setCaption(QString::fromUtf8(value));

			break;
		case QTNQPM_SETDOCKWINDOWTITLE:
			((DockPanelManager*)h)->setDockWindowTitle(QString::fromUtf8(value));
			break;
#endif
		case QSTI_SETTOOLTIP:
			((QSystemTrayIcon*)h)->setToolTip(QString::fromUtf8(value));

			break;

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
		case QMEDIAPLAYER_SETMEDIA:
		{
			((QMediaPlayer*)h)->setMedia(QUrl::fromLocalFile(QString::fromUtf8(value)));
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
		case QOPENGLFUNCTIONS_INITIALIZEOPENGLFUNCTIONS:
#if !defined(QT_NO_OPENGL)
			return ((QOpenGLFunctions*)h)->initializeOpenGLFunctions();
			break;
		case QOPENGLCONTEXT_DONECURRENT:
			((QOpenGLContext*)h)->doneCurrent();
			break;
		case QOPENGLWIDGET_DONECURRENT:
			((XOpenGLWidget*)h)->doneCurrent();
			break;
		case QOPENGLWIDGET_MAKECURRENT:
			((XOpenGLWidget*)h)->makeCurrent();
#endif
			break;
		case QAUDIOINPUT_RESUME:
			((XAudioInput*)h)->resume();
			break;
		case QAUDIOINPUT_SUSPEND:
			((XAudioInput*)h)->suspend();
			break;
		case QAUDIOINPUT_RESET:
			((XAudioInput*)h)->reset();
			break;
		case QAUDIOINPUT_STOP:
			((XAudioInput*)h)->stop();
			break;
		case QAUDIOINPUT_START:
			((XAudioInput*)h)->start();
			break;


		case QAUDIOOUTPUT_RESUME:
			((XAudioOutput*)h)->resume();
			break;
		case QAUDIOOUTPUT_SUSPEND:
			((XAudioOutput*)h)->suspend();
			break;
		case QAUDIOOUTPUT_RESET:
			((XAudioOutput*)h)->reset();
			break;
		case QAUDIOOUTPUT_STOP:
			((XAudioOutput*)h)->stop();
			break;
		case QAUDIOOUTPUT_START:
			((XAudioOutput*)h)->start();
			break;

		case QMEDIAPLAYER_STOP:
			((QMediaPlayer*)h)->stop();
			break;
		case QMEDIAPLAYER_PAUSE:
			((QMediaPlayer*)h)->pause();
			break;
		case QMEDIAPLAYER_PLAY:
			((QMediaPlayer*)h)->play();
			break;
#ifndef MOBILE_APP
		case QTNDB_CLEARDOCKBARS:
			((DockBarManager*)h)->clearDockBars();
			break;
		case QTNWT_SHOWHELP:
			((WindowTitleBar*)h)->showHelp();
			break;

		case QTNWT_BACKREQUESTED:
			((WindowTitleBar*)h)->backRequested();
			break;

		case QTNWT_REMOVEANDDELETE:
			((WindowTitleBar*)h)->removeAndDelete();
			break;

		case QTNWT_SHOW:
			((WindowTitleBar*)h)->show();
			break;

		case QTNWT_HIDE:
			((WindowTitleBar*)h)->hide();
			break;

		case QTNWT_UPDATE:
			((WindowTitleBar*)h)->update();
			break;
#endif
		case QTV_CLEARSPANS:
			((QTableView*)h)->clearSpans();
			break;

		case QH_RESET:
			((QHeaderView*)h)->reset();
			break;

		case QH_DOITEMSLAYOUT:
			((QHeaderView*)h)->doItemsLayout();
			break;

		case QH_RESETDEFAULTSECTIONSIZE:
			((QHeaderView*)h)->resetDefaultSectionSize();
			break;

		case QCW_SHOWNEXTMONTH:
			((QCalendarWidget*)h)->showNextMonth();
			break;

		case QCW_SHOWPREVIOUSMONTH:
			((QCalendarWidget*)h)->showPreviousMonth();
			break;

		case QCW_SHOWNEXTYEAR:
			((QCalendarWidget*)h)->showNextYear();
			break;

		case QCW_SHOWPREVIOUSYEAR:
			((QCalendarWidget*)h)->showPreviousYear();
			break;

		case QCW_SHOWSELECTEDDATE:
			((QCalendarWidget*)h)->showSelectedDate();
			break;

		case QCW_SHOWTODAY:
			((QCalendarWidget*)h)->showToday();
			break;

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
				XMetaPtr objectData = (pObj->property(XHANDLE).GETPROPERTY_VALUE);
                pObj->setProperty(XHANDLE, MAKEPROPERTY((XObjectData *)NULL));
                /*if (objectData.ptr() != 0) {
                    delete objectData;
                }*/
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

		case QSURFACEFORMAT:
		{
			delete (QSurfaceFormat*)h;
		}
		break;

		case QAUDIODEVICEINFO_FINALIZE:
			delete (QAudioDeviceInfo*)h;
			break;

		case QAUDIOFORMAT_FINALIZE:
			delete (QAudioFormat*)h;
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
				XMetaPtr data = (child->property(XHANDLE).GETPROPERTY_VALUE);
                if (data == NULL) {
                        data = new XObjectData();
                        child->setProperty(XHANDLE, MAKEPROPERTY(data));
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
                XMetaPtr data = (obj->property(XHANDLE).GETPROPERTY_VALUE);
                if (data == NULL) {
                     data = new XObjectData();
                     obj->setProperty(XHANDLE, MAKEPROPERTY(data));
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
		case QAUDIODEVICEINFO_ISFORMATSUPPORTED:
			return ((QAudioDeviceInfo*)h)->isFormatSupported(*(QAudioFormat*)v) ? 1 : 0;
			break;
		case QAUDIOFORMAT_FRAMESFORDURATION:
			((QAudioFormat*)h)->framesForDuration(v);
			break;
		case QAUDIOFORMAT_BYTESFORDURATION:
			((QAudioFormat*)h)->bytesForDuration(v);
			break;
		case QMEDIAPLAYER_SETVIDEOOUTPUT:
			((QMediaPlayer*)h)->setVideoOutput((QVideoWidget*)v);
			break;
		case QMEDIAOBJECT_UNBIND:
			((QMediaObject*)h)->unbind((QObject*)v);
			break;
		case QMEDIAOBJECT_BIND:
			return ((QMediaObject*)h)->bind((QObject*)v) ? 1 : 0;
			break;
#ifndef MOBILE_APP
		case QTNQPM_ISDOCKPANELCLOSED:
			return ((DockPanelManager*)h)->isDockPanelClosed((DockWidgetPanel*)v);
			break;
		case QTNQPM_ISDOCKPANELAUTOHIDE:
			return ((DockPanelManager*)h)->isDockPanelAutoHide((DockWidgetPanel*)v);
			break;
		case QTNQPM_ISDOCKPANELFLOAT:
			return ((DockPanelManager*)h)->isDockPanelFloat((DockWidgetPanel*)v);
			break;
#endif
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
		case QAUDIODEVICEINFO_SUPPORTEDSAMPLETYPES:
		{
			XThread th;
			QList<QAudioFormat::SampleType> qsl = ((QAudioDeviceInfo*)h)->supportedSampleTypes();
			XObject * obj = gs_env->createIntArray(qsl.size());
			for (int i = 0; i < qsl.size(); i++) {
				xint iv = qsl[i];
				gs_env->setElementValue(obj, i, &iv, 1);
			}
			return obj;
		}
		break;

		case QAUDIODEVICEINFO_SUPPORTEDSAMPLESIZES:
		{
			XThread th;
			QList<int> qsl = ((QAudioDeviceInfo*)h)->supportedSampleSizes();
			XObject * obj = gs_env->createIntArray(qsl.size());
			for (int i = 0; i < qsl.size(); i++) {
				xint iv = qsl[i];
				gs_env->setElementValue(obj, i, &iv, 1);
			}
			return obj;
		}
		break;
		case QAUDIODEVICEINFO_SUPPORTEDCHANNELCOUNTS:
		{
			XThread th;
			QList<int> qsl = ((QAudioDeviceInfo*)h)->supportedChannelCounts();
			XObject * obj = gs_env->createIntArray(qsl.size());
			for (int i = 0; i < qsl.size(); i++) {
				xint iv = qsl[i];
				gs_env->setElementValue(obj, i, &iv, 1);
			}
			return obj;
		}
		break;
		case QAUDIODEVICEINFO_SUPPORTEDSAMPLERATES:
		{
			XThread th;
			QList<int> qsl = ((QAudioDeviceInfo*)h)->supportedSampleRates();
			XObject * obj = gs_env->createIntArray(qsl.size());
			for (int i = 0; i < qsl.size(); i++) {
				xint iv = qsl[i];
				gs_env->setElementValue(obj, i, &iv, 1);
			}
			return obj;
		}
			break;
		case QAUDIODEVICEINFO_SUPPORTEDCODECS:
		{
			XThread th;
			QStringList qsl = ((QAudioDeviceInfo*)h)->supportedCodecs();
			XObject * obj = gs_env->createStringArray(qsl.size());
			for (int i = 0; i < qsl.size(); i++) {
				QByteArray qa = qsl[i].toUtf8();
				xstring xs = qa.data();
				int sl = qa.size();
				gs_env->setElementValue(th.getThread(), obj, i, &xs, &sl, 1);
			}
			return obj;
		}
			break;
		case QAUDIODEVICEINFO_NAME:
			qba = ((QAudioDeviceInfo*)h)->deviceName().toUtf8();
			break;
		case QAUDIOFORMAT_CODEC:
			qba = ((QAudioFormat*)h)->codec().toUtf8();
			break;
		case QMEDIAPLAYER_ERRORSTRING:
			qba = ((QMediaPlayer*)h)->errorString().toUtf8();
			break;
#ifndef MOBILE_APP
		case QTNDWP_CAPTION:
			qba = ((DockWidgetPanel*)h)->caption().toUtf8();
			break;
		case QTNQPM_DOCKWINDOWTITLE:
			qba = ((DockPanelManager*)h)->dockWindowTitle().toUtf8();
			break;
#endif
		case QSTI_TOOLTIP:
			qba = ((QSystemTrayIcon*)h)->toolTip().toUtf8();
			break;
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
	QObject * obj = 0;
#ifndef MOBILE_APP
	switch (proid) {
	case QTNQPM_ADDDOCUMENTPANEL:
		obj = ((DockPanelManager*)h)->addDocumentPanel(QString::fromUtf8(name));
		break;
	case QTNDB_ADDTOOLBAR:
		obj = ((DockBarManager*)h)->addToolBar(QString::fromUtf8(name), (DockBarArea)handle);
		break;
	case QTNADDTOOLBAR:
		obj = ((DockMainWindow*)h)->addToolBar(QString::fromUtf8(name),(DockBarArea)handle);
		break;
	case QTNADDDOCUMENTPANEL:
		obj = ((DockMainWindow*)h)->addDocumentPanel(QString::fromUtf8(name));
		break;
	}

#endif
	if (obj != 0) {
		XObject * output = getObjectControl(obj);
		if (output != 0) {
			return gs_env->referenceObject(output);
		}
	}
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
		case QAUDIODEVICEINFO_AVAILABLEDEVICES:
		{
			XThread thr;
			QList<QAudioDeviceInfo> qsl = QAudioDeviceInfo::availableDevices((QAudio::Mode)h1);

			XObject * obj = gs_env->createLongArray(qsl.size());
			for (size_t i = 0; i < qsl.size(); i++) {
				xlong lv = (xlong)new QAudioDeviceInfo(qsl[i]);
				gs_env->setElementValue(obj, i, &lv, 1);
			}
			return obj;
		}
		break;

		case QMEDIAPLAYER_SUPPORTEDMIMETYPES:
		{
			XThread thr;
			QStringList qsl = QMediaPlayer::supportedMimeTypes((QMediaPlayer::Flag)h1);
			XObject * obj = gs_env->createStringArray(qsl.size());
			for (size_t i = 0; i < qsl.size(); i++) {
				QByteArray qsa = qsl[i].toUtf8();
				xstring str = qsa.data();
				int len = qsa.length();
				gs_env->setElementValue(thr.getThread() , obj, i, &str, &len, 1);
			}
			return obj;
		}
			break;
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


XNLEXPORT XObject * XI_CDECL long_int4(xlong h, xint proid, xlong hv, xint i1, xint i2, xint i3, xint i4) {
	QObject * qobj = 0;
	switch (proid) {
#ifndef MOBILE_APP
	case QTNQPM_ADDDOCKWINDOW:
	{
		DockPanelManager * qt = (DockPanelManager*)h;
		qobj = qt->addDockWindow((DockPanelBase*)hv, QRect(i1, i2, i3, i4));

	}
	break;
	case QTNADDDOCKWINDOW:
	{
		DockMainWindow * qt = (DockMainWindow*)h;
		qobj = qt->addDockWindow((DockPanelBase*)hv, QRect(i1, i2, i3, i4));

	}
	break;
#endif
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
	QObject * qobj = 0;
	switch (proid)
	{
#ifndef MOBILE_APP
	case QTNQPM_ADDDOCKPANELS:
	{
		DockPanelManager * qt = (DockPanelManager*)h;
		QString qss = QString::fromUtf8(v1);
		QStringList qsl = qss.split(",");

		QByteArray charstr = qsl[0].toUtf8();
		xstring cxs = charstr.data();

		charstr = qsl[1].toUtf8();
		xstring cys = charstr.data();

		qobj = qt->addDockPanel(QString::fromUtf8(text), QSize(atoi(cxs), atoi(cys)), (DockPanelArea)v2, (DockPanelBase*)handle);
	}
	break;
	case QTNQPM_ADDDOCKPANEL:
	{
		DockPanelManager * qt = (DockPanelManager*)h;
		qobj = qt->addDockPanel(QString::fromUtf8(text), (DockPanelArea)v2, (DockPanelBase*)handle);
	}
	break;
	case QTNADDDOCKPANELS:
	{
		DockMainWindow * qt = (DockMainWindow*)h;
		QString qss = QString::fromUtf8(v1);
		QStringList qsl = qss.split(",");

		QByteArray charstr = qsl[0].toUtf8();
		xstring cxs = charstr.data(); 

		charstr = qsl[1].toUtf8();
		xstring cys = charstr.data();
		
		qobj = qt->addDockPanel(QString::fromUtf8(text), QSize(atoi(cxs), atoi(cys)),(DockPanelArea)v2, (DockPanelBase*)handle);
	}
	break;
	case QTNADDDOCKPANEL:
	{
		DockMainWindow * qt = (DockMainWindow*)h;
		qobj = qt->addDockPanel(QString::fromUtf8(text), (DockPanelArea)v2, (DockPanelBase*)handle);
	}
		break;
#endif
	case QSTI_SHOWMESSAGE:
	{
		QSystemTrayIcon * obj = (QSystemTrayIcon*)h;
		obj->showMessage(QString::fromUtf8(text), QString::fromUtf8(v1), (handle == 0) ? QIcon() : (*(QIcon*)handle), v2);
	}
		break;
	default:
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

XNLEXPORT xlong XI_CDECL long_object_string_int(xlong handle, xint proid, XObject * v1, xstring v2, xint v3) {

	return 0;
}

XNLEXPORT xlong XI_CDECL long_object_string(xlong handle, xint proid, XObject * v1, xstring v2) {
        switch (proid)
        {
		case QMEDIAPLAYER_HASSUPPORT:
		{
			QStringList qsl;
			if (gs_env->isArray(v1)) {
				size_t c = gs_env->getLengthOfArray(v1);
				for (size_t i = 0; i < c; i++) {
					xstring str = 0;
					size_t len;
					if (gs_env->getElementValue(v1, i, &str, &len, 1)) {
						if (str != 0) {
							qsl.push_back(QString::fromUtf8(str, len));
						}
					}
				}
			}
			return QMediaPlayer::hasSupport(QString::fromUtf8(v2), qsl, (QMediaPlayer::Flag)handle);
		}
			break;
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
					qobject->setProperty(XHANDLE, MAKEPROPERTY(objectData)); 
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
		case QSTI_SHOWMESSAGE:
			 ((QSystemTrayIcon*)handle)->showMessage(QString::fromUtf8(v1), QString::fromUtf8(v2), (QSystemTrayIcon::MessageIcon)flags, flags2);
			break;

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

#if !defined(QT_NO_OPENGL) 
		case QOPENGLCONTEXT_FUNCTIONS_ES2:
		{

#ifdef QT_OPENGL_ES_2
			return (xlong)(((QOpenGLContext*)(handle))->versionFunctions<QOpenGLFunctions_ES2>());
#else
			return 0;
#endif
		}
		break;
#if !defined(QT_OPENGL_ES_2)
		case QOPENGLCONTEXT_FUNCTIONS_1_1:
		{
			return (xlong)(((QOpenGLContext*)(handle))->versionFunctions<QOpenGLFunctions_1_1>());
		}
		break;
		case QOPENGLCONTEXT_FUNCTIONS_1_0:
		{
			return (xlong)(((QOpenGLContext*)(handle))->versionFunctions<QOpenGLFunctions_1_0>());

		}
		break;
#endif
#endif
		case QSURFACEFORMAT_DEFAULTFORMAT:
		{
			return (xlong)new QSurfaceFormat((((QSurfaceFormat*)(handle))->defaultFormat()));
		}
		break;
#if !defined(QT_NO_OPENGL)
		case QOPENGLCONTEXT_EXTRAFUNCTIONS:
		{
			return (xlong)(((QOpenGLContext*)(handle))->extraFunctions());
		}
		break;

		case QOPENGLCONTEXT_FUNCTIONS:
		{
			return (xlong) (((QOpenGLContext*)(handle))->functions());
		}
		break;

		case QOPENGLCONTEXT_FORMAT:
		{
			return (xlong) new QSurfaceFormat(((QOpenGLContext*)(handle))->format());
		}
		break;

		case QOPENGLWIDGET_GRABFRAMEBUFFER:
		{
			return (xlong) new QImage(((XOpenGLWidget*)(handle))->grabFramebuffer());
		}

		break;

		case QOPENGLWIDGET_FORMAT:
		{
			return (xlong) new QSurfaceFormat(((XOpenGLWidget*)(handle))->format());
		}
		break;
#endif
		case QAUDIODEVICEINFO_DEFAULTOUTPUTDEVICE:
		{
			return (xlong) new QAudioDeviceInfo(((QAudioDeviceInfo*)(handle))->defaultOutputDevice());
		}
		break;

		case QAUDIODEVICEINFO_DEFAULTINPUTDEVICE:
		{
			return (xlong) new QAudioDeviceInfo(((QAudioDeviceInfo*)(handle))->defaultInputDevice());
		}
		break;

		case QAUDIODEVICEINFO_PREFERREDFORMAT:
		{
			return (xlong) new QAudioFormat(((QAudioDeviceInfo*)(handle))->preferredFormat());
		}
		break;

		case QAUDIOINPUT_ELAPSEDUSECS:
		{
			return ((XAudioInput*)(handle))->elapsedUSecs();
		}
		break;

		case QAUDIOINPUT_PROCESSEDUSECS:
		{
			return ((XAudioInput*)(handle))->processedUSecs();
		}
		break;

		case QAUDIOINPUT_FORMAT:
		{
			return (xlong)new QAudioFormat(((XAudioInput*)(handle))->format());
		}
		break;

		case QAUDIOOUTPUT_ELAPSEDUSECS:
		{
			return ((XAudioOutput*)(handle))->elapsedUSecs();
		}
		break;

		case QAUDIOOUTPUT_PROCESSEDUSECS:
		{
			return ((XAudioOutput*)(handle))->processedUSecs();
		}
		break;

		case QAUDIOOUTPUT_FORMAT:
		{
			return (xlong)new QAudioFormat(((XAudioOutput*)(handle))->format());
		}
		break;

		case QMEDIAPLAYER_POSITION:
		{
			return ((QMediaPlayer*)(handle))->position();
		}
		break;
		case QMEDIAPLAYER_DURATION:
		{
			return ((QMediaPlayer*)(handle))->duration();
		}
		break;
		case QSTI_GETICON:
		{
			QSystemTrayIcon* twidget = (QSystemTrayIcon *)handle;
			return (xlong)(new QIcon(twidget->icon()));
		}
		break;
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

		case QVIDEOWIDGET_SIZEHINT:
		{
			QVideoWidget * twidget = (QVideoWidget *)handle;
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

XNLEXPORT xlong XI_CDECL widget_set_int2_object_value(xlong h, xint proid, xint id, xint iv, XObject * value) {
        switch (proid)
        {

		case QAUDIOOUTPUT_WRITE:
		{
			xlong r = 0;
			if (gs_env->isArray(value)) {
				xlong size = gs_env->getLengthOfArray(value);
				XNLEnv::XDataType _t = gs_env->getComponentType(value);
				xbyte * text = 0;
				int len = 0;
				switch (_t)
				{
				case XNLEnv::t_byte:
					text = new xbyte[iv];
					len = iv;
					gs_env->getElementValue(value, id, text, iv);
					break;
				case XNLEnv::t_short:
					len = iv * 2;
					text = new xbyte[iv * 2];
					gs_env->getElementValue(value, id, (short*)text, iv);
					break;
				case XNLEnv::t_int:
					len = iv * 4;
					text = new xbyte[iv * 4];
					gs_env->getElementValue(value, id, (xint*)text, iv);
					break;

				case XNLEnv::t_float:
					len = iv * 4;
					text = new xbyte[iv * 4];
					gs_env->getElementValue(value, id, (xfloat*)text, iv);
					break;

				case XNLEnv::t_double:
					len = iv * 8;
					text = new xbyte[iv * 8];
					gs_env->getElementValue(value, id, (xdouble*)text, iv);
					break;
				default:
					break;
				}
				if (text != 0) {
					r = ((XAudioOutput*)h)->write((char*)text, len);
					delete[] text;
				}
			}
			return r;
		}
		break;

		case QAUDIOINPUT_READ:
		{
			xlong r = 0;
			if (gs_env->isArray(value)) {
				xlong size = gs_env->getLengthOfArray(value);
				xbyte * text = new xbyte[iv];
				r = ((XAudioInput*)h)->read((char*)text, iv);
				gs_env->setElementValue(value, id, text, r);
				delete[] text;
				return r;
			}
		}
		break;
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

		return 0;
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
                XMetaPtr objectData =(((QObject*)h)->property(XHANDLE).GETPROPERTY_VALUE);
                if (objectData == 0) {
                        objectData = new XObjectData();
                        ((QObject*)h)->setProperty(XHANDLE, MAKEPROPERTY(objectData));
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
#ifndef MOBILE_APP
		case DBMLOADSTATE:// 133,
		{

			if (gs_env->isArray(value)) {
				QByteArray data;
				extartByteArray(value, data);
				QBuffer buffer;
				buffer.setBuffer(&data);
				if (buffer.open(QIODevice::ReadOnly)) {
					((DockBarManager *)h)->loadStateFromDevice(&buffer);
				}

			}
		}
		break;

		case DPMLOADSTATE:// 133,
		{

			if (gs_env->isArray(value)) {
				QByteArray data;
				extartByteArray(value, data);
				QBuffer buffer;
				buffer.setBuffer(&data);
				if (buffer.open(QIODevice::ReadOnly)) {
					((DockPanelManager *)h)->loadStateFromDevice(&buffer);
				}

			}
		}
		break;

		case DMLOADSTATE:// 133,
		{

			if (gs_env->isArray(value)) {
				QByteArray data;
				extartByteArray(value, data);

				xint len = *(xint*)data.data();

				QBuffer buffer;
				buffer.setData(data.data() + sizeof(xint), len);
				
				QBuffer buffer1;

				xint start = sizeof(xint) + len;
				buffer.setData(data.data() + start, data.length() - start);

				if (buffer.open(QIODevice::ReadOnly) && buffer1.open(QIODevice::ReadOnly)) {
					((DockMainWindow *)h)->loadStateFromDevice(&buffer, &buffer1);
				}
			}
		}
		break;
#endif
		case QH_LOADSTATE:// 133,
		{

			if (gs_env->isArray(value)) {
				QByteArray data;
				extartByteArray(value, data);
				((QHeaderView *)h)->restoreState(data);

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
#ifndef MOBILE_APP
		case QTNDPM_INSERTDOCKPANEL:
		{
			DockPanelManager * obj = (DockPanelManager*)h;
			obj->insertDockPanel((DockWidgetPanel*)hv, (DockPanelArea)iv, (DockPanelBase*)h1);
		}
		break;
		case QTNDMW_INSERTDOCKPANEL:
		{
			DockMainWindow * obj = (DockMainWindow*)h;
			obj->insertDockPanel((DockWidgetPanel*)hv, (DockPanelArea)iv, (DockPanelBase*)h1);
		}
		break;
#endif
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
		case QAUDIODEVICEINFO_NEARESTFORMAT:
			return (xlong)new QAudioFormat(((QAudioDeviceInfo*)h)->nearestFormat(*(QAudioFormat*)hv));
			break;
		case QAUDIOFORMAT_DURATIONFORFRAMES:
			return ((QAudioFormat*)h)->durationForFrames(iv);
			break;
		case QAUDIOFORMAT_DURATIONFORBYTES:
			return ((QAudioFormat*)h)->durationForBytes(iv);
			break;
#ifndef MOBILE_APP
		case QTNDPB_SETDOCKWINDOW:
			((DockPanelBase*)h)->setDockWindow((DockWindowBase*)hv);
			break;
		case QTNDPB_SETPARENTPANEL:
			((DockPanelBase*)h)->setParentPanel((DockPanelBase*)hv);
			break;
		case QTNDW_INITIALIZATIONWINDOW:
			((DockWindow*)h)->initializationWindow((DockPanelBase*)hv);
			break;
		case QTNQPM_SHOWDOCKPANEL:
			((DockPanelManager*)h)->showDockPanel((DockDocumentPanel*)hv, iv != 0);
			break;
		case QTNQPM_SETDOCKPANELAUTOHIDE:
			((DockPanelManager*)h)->setDockPanelAutoHide((DockDocumentPanel*)hv, iv != 0);
			break;
		case QTNQPM_SETDOCKPANELFLOAT:
			((DockPanelManager*)h)->setDockPanelFloat((DockDocumentPanel*)hv, iv != 0);
			break;
		case QTNQPM_INSERTDOCUMENTPANEL:
			((DockPanelManager*)h)->insertDocumentPanel((DockDocumentPanel*)hv);
			break;
		case QTNDB_INSERTDOCKBAR:
			((DockBarManager*)h)->insertDockBar((DockToolBar*)hv, (DockBarArea)iv);
			break;
		case QTNWT_SETWIDGET:
			((WindowTitleBar*)h)->setWidget((QWidget*)hv, (WindowTitleBar::WidgetAlign)iv);
			break;
		case QTNINSERTDOCUMENTPANEL:
			((DockMainWindow*)h)->insertDocumentPanel((DockDocumentPanel*)hv);
			break;
		case QTNINSERTDOCKBAR:
			return ((DockMainWindow*)h)->insertDockBar((DockToolBar*)hv, (DockBarArea)iv) ? 1 : 0;
			break;
#endif
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
		case QOPENGLCONTEXT_ARESHARING:
		{
#if !defined(QT_NO_OPENGL)
			return QOpenGLContext::areSharing(((QOpenGLContext*)value), ((QOpenGLContext*)v1)) ? 1 : 0;
#endif
		}
			break;
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
#ifndef MOBILE_APP
		case QTNDB_MOVEDOCKBAR:
			((DockBarManager*)handle)->moveDockBar((DockToolBar*)value1, (DockToolBar*)v2);
			break;
		case QTNDB_INSERTDOCKBAR:
			((DockBarManager*)handle)->insertDockBar((DockToolBar*)value1, (DockToolBar*)v2);
			break;
		case QTNMOVEDOCKBAR:
			((DockMainWindow*)handle)->moveDockBar((DockToolBar*)value1, (DockToolBar*)v2);
			break;
		case QTNINSERTDOCKBAR:
			((DockMainWindow*)handle)->insertDockBar((DockToolBar*)value1, (DockToolBar*)v2);
			break;
#endif
		case QLAYOUT_SETCONTENTSMARGINS:
			((QLayout*)handle)->setContentsMargins(value1 >> 32 & 0xffffffff, value1 & 0xffffffff, v2 >> 32 & 0xffffffff, v2 & 0xffffffff);
			break;

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

XNLEXPORT void XI_CDECL qfn_glBindTexture(xlong nativehandle, xint target, xint texture) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBindTexture(target, texture);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBlendFunc(xlong nativehandle, xint sfactor, xint dfactor) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBlendFunc(sfactor, dfactor);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glClear(xlong nativehandle, GLbitfield mask) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glClear(mask);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glClearColor(xlong nativehandle, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glClearColor(red, green, blue, alpha);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glClearStencil(xlong nativehandle, xint s) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glClearStencil(s);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glColorMask(xlong nativehandle, bool red, bool green, bool blue, bool alpha) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glColorMask(red, green, blue, alpha);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glCopyTexImage2D(xlong nativehandle, xint target, xint level, xint internalformat, xint x, xint y, xint width, xint height, xint border) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glCopyTexSubImage2D(xlong nativehandle, xint target, xint level, xint xoffset, xint yoffset, xint x, xint y, xint width, xint height) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glCullFace(xlong nativehandle, xint mode) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glCullFace(mode);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteTextures(xlong nativehandle, xint n, xint *  textures) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDeleteTextures(n, (GLuint*)textures);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDepthFunc(xlong nativehandle, xint func) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDepthFunc(func);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDepthMask(xlong nativehandle, bool flag) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDepthMask(flag);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDisable(xlong nativehandle, xint cap) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDisable(cap);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDrawArrays(xlong nativehandle, xint mode, xint first, xint count) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDrawArrays(mode, first, count);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDrawElements(xlong nativehandle, xint mode, xint count, xint type, xbyte *  indices) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDrawElements(mode, count, type, indices);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glEnable(xlong nativehandle, xint cap) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glEnable(cap);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glFinish(xlong nativehandle) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glFinish();
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glFlush(xlong nativehandle) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glFlush();
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glFrontFace(xlong nativehandle, xint mode) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glFrontFace(mode);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGenTextures(xlong nativehandle, xint n, xint *  textures) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGenTextures(n, (GLuint*)textures);
#else

#endif
}

XNLEXPORT bool XI_CDECL qfn_glGetBooleanv(xlong nativehandle, xint pname) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  GLboolean b; ((QOpenGLFunctions*)nativehandle)->glGetBooleanv(pname, &b); return b;
#else
	return false;
#endif
}

XNLEXPORT xint XI_CDECL qfn_glGetError(xlong nativehandle) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glGetError();
#else
	return 0;
#endif
}

XNLEXPORT xfloat XI_CDECL qfn_glGetFloatv(xlong nativehandle, xint pname) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  xfloat f; ((QOpenGLFunctions*)nativehandle)->glGetFloatv(pname, &f); return f;
#else
	return 0;
#endif
}

XNLEXPORT xint XI_CDECL qfn_glGetIntegerv(xlong nativehandle, xint pname) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  GLint i; ((QOpenGLFunctions*)nativehandle)->glGetIntegerv(pname, &i); return i;
#else
	return 0;
#endif
}

XNLEXPORT xstring XI_CDECL qfn_glGetString(xlong nativehandle, xint name) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return (char*)((QOpenGLFunctions*)nativehandle)->glGetString(name);
#else
	return 0;
#endif
}

XNLEXPORT xfloat XI_CDECL qfn_glGetTexParameterfv(xlong nativehandle, xint target, xint pname) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  xfloat f; ((QOpenGLFunctions*)nativehandle)->glGetTexParameterfv(target, pname, &f); return f;
#else
	return 0;
#endif
}

XNLEXPORT xint XI_CDECL qfn_glGetTexParameteriv(xlong nativehandle, xint target, xint pname) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  GLint i; ((QOpenGLFunctions*)nativehandle)->glGetTexParameteriv(target, pname, &i); return i;
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glHint(xlong nativehandle, xint target, xint mode) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glHint(target, mode);
#else

#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsEnabled(xlong nativehandle, xint cap) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glIsEnabled(cap);
#else
	return false;
#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsTexture(xlong nativehandle, xint texture) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glIsTexture(texture);
#else
	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_glLineWidth(xlong nativehandle, float width) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glLineWidth(width);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glPixelStorei(xlong nativehandle, xint pname, xint param) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glPixelStorei(pname, param);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glPolygonOffset(xlong nativehandle, float factor, float units) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glPolygonOffset(factor, units);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glReadPixels(xlong nativehandle, xint x, xint y, xint width, xint height, xint format, xint type, xbyte * pixels) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glReadPixels(x, y, width, height, format, type, pixels);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glScissor(xlong nativehandle, xint x, xint y, xint width, xint height) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glScissor(x, y, width, height);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glStencilFunc(xlong nativehandle, xint func, xint ref, xint mask) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glStencilFunc(func, ref, mask);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glStencilMask(xlong nativehandle, xint mask) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glStencilMask(mask);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glStencilOp(xlong nativehandle, xint fail, xint zfail, xint zpass) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glStencilOp(fail, zfail, zpass);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexImage2D(xlong nativehandle, xint target, xint level, xint internalformat, xint width, xint height, xint border, xint format, xint type, xbyte * pixels) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexParameterf(xlong nativehandle, xint target, xint pname, float param) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glTexParameterf(target, pname, param);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexParameterfv(xlong nativehandle, xint target, xint pname, float * params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glTexParameterfv(target, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexParameteri(xlong nativehandle, xint target, xint pname, xint param) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glTexParameteri(target, pname, param);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexParameteriv(xlong nativehandle, xint target, xint pname, xint * params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glTexParameteriv(target, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexSubImage2D(xlong nativehandle, xint target, xint level, xint xoffset, xint yoffset, xint width, xint height, xint format, xint type, xbyte * pixels) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glViewport(xlong nativehandle, xint x, xint y, xint width, xint height) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glViewport(x, y, width, height);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glActiveTexture(xlong nativehandle, xint texture) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glActiveTexture(texture);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glAttachShader(xlong nativehandle, xint program, xint shader) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glAttachShader(program, shader);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBindAttribLocation(xlong nativehandle, xint program, xint index, xstring name) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBindAttribLocation(program, index, name);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBindBuffer(xlong nativehandle, xint target, xint buffer) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBindBuffer(target, buffer);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBindFramebuffer(xlong nativehandle, xint target, xint framebuffer) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBindFramebuffer(target, framebuffer);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBindRenderbuffer(xlong nativehandle, xint target, xint renderbuffer) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBindRenderbuffer(target, renderbuffer);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBlendColor(xlong nativehandle, GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBlendColor(red, green, blue, alpha);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBlendEquation(xlong nativehandle, xint mode) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBlendEquation(mode);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBlendEquationSeparate(xlong nativehandle, xint modeRGB, xint modeAlpha) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBlendEquationSeparate(modeRGB, modeAlpha);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBlendFuncSeparate(xlong nativehandle, xint srcRGB, xint dstRGB, xint srcAlpha, xint dstAlpha) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBufferData(xlong nativehandle, xint target, xint size, xbyte * data, xint usage) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBufferData(target, size, data, usage);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBufferSubData(xlong nativehandle, xint target, xint offset, xint size, xbyte * data) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glBufferSubData(target, offset, size, data);
#else

#endif
}

XNLEXPORT xint XI_CDECL qfn_glCheckFramebufferStatus(xlong nativehandle, xint target) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glCheckFramebufferStatus(target);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glClearDepthf(xlong nativehandle, GLclampf depth) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glClearDepthf(depth);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glCompileShader(xlong nativehandle, xint shader) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glCompileShader(shader);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glCompressedTexImage2D(xlong nativehandle, xint target, xint level, xint internalformat, xint width, xint height, xint border, xint imageSize, xbyte * data) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glCompressedTexSubImage2D(xlong nativehandle, xint target, xint level, xint xoffset, xint yoffset, xint width, xint height, xint format, xint imageSize, xbyte * data) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
#else

#endif
}

XNLEXPORT xint XI_CDECL qfn_glCreateProgram(xlong nativehandle) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glCreateProgram();
#else
	return 0;
#endif
}

XNLEXPORT xint XI_CDECL qfn_glCreateShader(xlong nativehandle, xint type) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glCreateShader(type);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteBuffers(xlong nativehandle, xint n, xint * buffers) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDeleteBuffers(n, (GLuint*)buffers);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteFramebuffers(xlong nativehandle, xint n, xint * framebuffers) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDeleteFramebuffers(n, (GLuint*)framebuffers);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteProgram(xlong nativehandle, xint program) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDeleteProgram(program);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteRenderbuffers(xlong nativehandle, xint n, xint * renderbuffers) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDeleteRenderbuffers(n, (GLuint*)renderbuffers);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteShader(xlong nativehandle, xint shader) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDeleteShader(shader);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDepthRangef(xlong nativehandle, GLclampf zNear, GLclampf zFar) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDepthRangef(zNear, zFar);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDetachShader(xlong nativehandle, xint program, xint shader) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDetachShader(program, shader);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDisableVertexAttribArray(xlong nativehandle, xint index) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glDisableVertexAttribArray(index);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glEnableVertexAttribArray(xlong nativehandle, xint index) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glEnableVertexAttribArray(index);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glFramebufferRenderbuffer(xlong nativehandle, xint target, xint attachment, xint renderbuffertarget, xint renderbuffer) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glFramebufferTexture2D(xlong nativehandle, xint target, xint attachment, xint textarget, xint texture, xint level) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glFramebufferTexture2D(target, attachment, textarget, texture, level);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGenBuffers(xlong nativehandle, xint n, xint *  buffers) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGenBuffers(n, (GLuint*)buffers);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGenerateMipmap(xlong nativehandle, xint target) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGenerateMipmap(target);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGenFramebuffers(xlong nativehandle, xint n, xint *  framebuffers) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGenFramebuffers(n, (GLuint*)framebuffers);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGenRenderbuffers(xlong nativehandle, xint n, xint *  renderbuffers) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGenRenderbuffers(n, (GLuint*)renderbuffers);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetActiveAttrib(xlong nativehandle, xint program, xint index, xint bufsize, xint *  length, xint *  size, xint *  type, xbyte * name) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetActiveAttrib(program, index, bufsize, length, size, (GLenum*)type, (char*)name);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetActiveUniform(xlong nativehandle, xint program, xint index, xint bufsize, xint *  length, xint *  size, xint *  type, xbyte * name) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetActiveUniform(program, index, bufsize, length, size, (GLenum*)type, (char*)name);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetAttachedShaders(xlong nativehandle, xint program, xint maxcount, xint *  count, xint *  shaders) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetAttachedShaders(program, maxcount, count, (GLuint*)shaders);
#else

#endif
}

XNLEXPORT xint XI_CDECL qfn_glGetAttribLocation(xlong nativehandle, xint program, xstring name) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glGetAttribLocation(program, name);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glGetBufferParameteriv(xlong nativehandle, xint target, xint pname, xint *  params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetBufferParameteriv(target, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetFramebufferAttachmentParameteriv(xlong nativehandle, xint target, xint attachment, xint pname, xint *  params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetProgramiv(xlong nativehandle, xint program, xint pname, xint *  params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetProgramiv(program, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetProgramInfoLog(xlong nativehandle, xint program, xint bufsize, xint *  length, xbyte * infolog) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetProgramInfoLog(program, bufsize, length, (char *)infolog);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetRenderbufferParameteriv(xlong nativehandle, xint target, xint pname, xint *  params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetRenderbufferParameteriv(target, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetShaderiv(xlong nativehandle, xint shader, xint pname, xint *  params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetShaderiv(shader, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetShaderInfoLog(xlong nativehandle, xint shader, xint bufsize, xint *  length, xbyte * infolog) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetShaderInfoLog(shader, bufsize, length, (char *)infolog);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetShaderPrecisionFormat(xlong nativehandle, xint shadertype, xint precisiontype, xint *  range, xint *  precision) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetShaderSource(xlong nativehandle, xint shader, xint bufsize, xint *  length, xbyte * source) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetShaderSource(shader, bufsize, length, (char *)source);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetUniformfv(xlong nativehandle, xint program, xint location, float *  params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetUniformfv(program, location, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetUniformiv(xlong nativehandle, xint program, xint location, xint *  params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetUniformiv(program, location, params);
#else

#endif
}

XNLEXPORT xint XI_CDECL qfn_glGetUniformLocation(xlong nativehandle, xint program, xstring name) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glGetUniformLocation(program, name);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glGetVertexAttribfv(xlong nativehandle, xint index, xint pname, float *  params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetVertexAttribfv(index, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetVertexAttribiv(xlong nativehandle, xint index, xint pname, xint *  params) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetVertexAttribiv(index, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetVertexAttribPointerv(xlong nativehandle, xint index, xint pname, xlong * pointer) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glGetVertexAttribPointerv(index, pname, (void**)pointer);
#else

#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsBuffer(xlong nativehandle, xint buffer) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glIsBuffer(buffer);
#else
	return false;
#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsFramebuffer(xlong nativehandle, xint framebuffer) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glIsFramebuffer(framebuffer);
#else
	return false;
#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsProgram(xlong nativehandle, xint program) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glIsProgram(program);
#else
	return false;
#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsRenderbuffer(xlong nativehandle, xint renderbuffer) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glIsRenderbuffer(renderbuffer);
#else
	return false;
#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsShader(xlong nativehandle, xint shader) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  return ((QOpenGLFunctions*)nativehandle)->glIsShader(shader);
#else
	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_glLinkProgram(xlong nativehandle, xint program) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glLinkProgram(program);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glReleaseShaderCompiler(xlong nativehandle) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glReleaseShaderCompiler();
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glRenderbufferStorage(xlong nativehandle, xint target, xint internalformat, xint width, xint height) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glRenderbufferStorage(target, internalformat, width, height);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glSampleCoverage(xlong nativehandle, GLclampf value, bool invert) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glSampleCoverage(value, invert);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glShaderBinary(xlong nativehandle, xint n, xint * shaders, xint binaryformat, xbyte * binary, xint length) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glShaderBinary(n, (GLuint*)shaders, binaryformat, binary, length);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glShaderSource(xlong nativehandle, xint shader, xint count, xstring string, xint * length) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  if (count > 1)return; ((QOpenGLFunctions*)nativehandle)->glShaderSource(shader, count, (const char**)&string, length);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glStencilFuncSeparate(xlong nativehandle, xint face, xint func, xint ref, xint mask) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glStencilFuncSeparate(face, func, ref, mask);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glStencilMaskSeparate(xlong nativehandle, xint face, xint mask) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glStencilMaskSeparate(face, mask);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glStencilOpSeparate(xlong nativehandle, xint face, xint fail, xint zfail, xint zpass) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glStencilOpSeparate(face, fail, zfail, zpass);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform1f(xlong nativehandle, xint location, float x) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform1f(location, x);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform1fv(xlong nativehandle, xint location, xint count, float * v) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform1fv(location, count, v);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform1i(xlong nativehandle, xint location, xint x) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform1i(location, x);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform1iv(xlong nativehandle, xint location, xint count, xint * v) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform1iv(location, count, v);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform2f(xlong nativehandle, xint location, float x, float y) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform2f(location, x, y);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform2fv(xlong nativehandle, xint location, xint count, float * v) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform2fv(location, count, v);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform2i(xlong nativehandle, xint location, xint x, xint y) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform2i(location, x, y);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform2iv(xlong nativehandle, xint location, xint count, xint * v) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform2iv(location, count, v);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform3f(xlong nativehandle, xint location, float x, float y, float z) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform3f(location, x, y, z);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform3fv(xlong nativehandle, xint location, xint count, float * v) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform3fv(location, count, v);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform3i(xlong nativehandle, xint location, xint x, xint y, xint z) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform3i(location, x, y, z);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform3iv(xlong nativehandle, xint location, xint count, xint * v) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform3iv(location, count, v);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform4f(xlong nativehandle, xint location, float x, float y, float z, float w) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform4f(location, x, y, z, w);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform4fv(xlong nativehandle, xint location, xint count, float * v) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform4fv(location, count, v);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform4i(xlong nativehandle, xint location, xint x, xint y, xint z, xint w) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform4i(location, x, y, z, w);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform4iv(xlong nativehandle, xint location, xint count, xint * v) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniform4iv(location, count, v);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniformMatrix2fv(xlong nativehandle, xint location, xint count, bool transpose, float * value) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniformMatrix2fv(location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniformMatrix3fv(xlong nativehandle, xint location, xint count, bool transpose, float * value) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniformMatrix3fv(location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniformMatrix4fv(xlong nativehandle, xint location, xint count, bool transpose, float * value) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUniformMatrix4fv(location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUseProgram(xlong nativehandle, xint program) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glUseProgram(program);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glValidateProgram(xlong nativehandle, xint program) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glValidateProgram(program);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttrib1f(xlong nativehandle, xint indx, float x) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glVertexAttrib1f(indx, x);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttrib1fv(xlong nativehandle, xint indx, float * values) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glVertexAttrib1fv(indx, values);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttrib2f(xlong nativehandle, xint indx, float x, float y) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glVertexAttrib2f(indx, x, y);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttrib2fv(xlong nativehandle, xint indx, float * values) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glVertexAttrib2fv(indx, values);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttrib3f(xlong nativehandle, xint indx, float x, float y, float z) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glVertexAttrib3f(indx, x, y, z);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttrib3fv(xlong nativehandle, xint indx, float * values) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glVertexAttrib3fv(indx, values);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttrib4f(xlong nativehandle, xint indx, float x, float y, float z, float w) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glVertexAttrib4f(indx, x, y, z, w);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttrib4fv(xlong nativehandle, xint indx, float * values) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glVertexAttrib4fv(indx, values);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttribPointer(xlong nativehandle, xint indx, xint size, xint type, bool normalized, xint stride, xbyte * ptr) {
#if !defined(QT_NO_OPENGL)
	CHECK_NONE_HANDLE(nativehandle)  ((QOpenGLFunctions*)nativehandle)->glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glReadBuffer(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glReadBuffer(mode);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDrawRangeElements(xlong nativehandle, int mode, int start, int end, int count, int type, void  * indices) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDrawRangeElements(mode, start, end, count, type, indices);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexImage3D(xlong nativehandle, int target, int level, int internalformat, int width, int height, int depth, int border, int format, int type, void  * pixels) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glTexImage3D(target, level, internalformat, width, height, depth, border, format, type, pixels);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexSubImage3D(xlong nativehandle, int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int type, void  * pixels) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glCopyTexSubImage3D(xlong nativehandle, int target, int level, int xoffset, int yoffset, int zoffset, int x, int y, int width, int height) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glCopyTexSubImage3D(target, level, xoffset, yoffset, zoffset, x, y, width, height);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glCompressedTexImage3D(xlong nativehandle, int target, int level, int internalformat, int width, int height, int depth, int border, int imageSize, void  * data) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glCompressedTexImage3D(target, level, internalformat, width, height, depth, border, imageSize, data);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glCompressedTexSubImage3D(xlong nativehandle, int target, int level, int xoffset, int yoffset, int zoffset, int width, int height, int depth, int format, int imageSize, void  * data) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, data);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGenQueries(xlong nativehandle, int n, int  * ids) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGenQueries(n, (GLuint*)ids);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteQueries(xlong nativehandle, int n, int  * ids) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDeleteQueries(n, (GLuint*)ids);
#else

#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsQuery(xlong nativehandle, int id) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glIsQuery(id);
#else
	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_glBeginQuery(xlong nativehandle, int target, int id) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBeginQuery(target, id);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glEndQuery(xlong nativehandle, int target) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glEndQuery(target);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetQueryiv(xlong nativehandle, int target, int pname, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetQueryiv(target, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetQueryObjectuiv(xlong nativehandle, int id, int pname, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetQueryObjectuiv(id, pname, (GLuint*)params);
#else

#endif
}

XNLEXPORT bool XI_CDECL qfn_glUnmapBuffer(xlong nativehandle, int target) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glUnmapBuffer(target);
#else
	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_glGetBufferPointerv(xlong nativehandle, int target, int pname, xlong* params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetBufferPointerv(target, pname, (void**)params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDrawBuffers(xlong nativehandle, int n, int  * bufs) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDrawBuffers(n, (GLuint*)bufs);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniformMatrix2x3fv(xlong nativehandle, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniformMatrix2x3fv(location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniformMatrix3x2fv(xlong nativehandle, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniformMatrix3x2fv(location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniformMatrix2x4fv(xlong nativehandle, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniformMatrix2x4fv(location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniformMatrix4x2fv(xlong nativehandle, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniformMatrix4x2fv(location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniformMatrix3x4fv(xlong nativehandle, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniformMatrix3x4fv(location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniformMatrix4x3fv(xlong nativehandle, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniformMatrix4x3fv(location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBlitFramebuffer(xlong nativehandle, int srcX0, int srcY0, int srcX1, int srcY1, int dstX0, int dstY0, int dstX1, int dstY1, int mask, int filter) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBlitFramebuffer(srcX0, srcY0, srcX1, srcY1, dstX0, dstY0, dstX1, dstY1, mask, filter);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glRenderbufferStorageMultisample(xlong nativehandle, int target, int samples, int internalformat, int width, int height) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glRenderbufferStorageMultisample(target, samples, internalformat, width, height);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glFramebufferTextureLayer(xlong nativehandle, int target, int attachment, int texture, int level, int layer) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glFramebufferTextureLayer(target, attachment, texture, level, layer);
#else

#endif
}

XNLEXPORT void  * XI_CDECL qfn_glMapBufferRange(xlong nativehandle, int target, xlong offset, GLsizeiptr length, int access) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glMapBufferRange(target, offset, length, access);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glFlushMappedBufferRange(xlong nativehandle, int target, xlong offset, GLsizeiptr length) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glFlushMappedBufferRange(target, offset, length);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBindVertexArray(xlong nativehandle, int array) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBindVertexArray(array);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteVertexArrays(xlong nativehandle, int n, int  * arrays) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDeleteVertexArrays(n, (GLuint*)arrays);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGenVertexArrays(xlong nativehandle, int n, int  * arrays) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGenVertexArrays(n, (GLuint*)arrays);
#else

#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsVertexArray(xlong nativehandle, int array) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glIsVertexArray(array);
#else
	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_glGetIntegeri_v(xlong nativehandle, int target, int index, int  * data) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetIntegeri_v(target, index, data);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBeginTransformFeedback(xlong nativehandle, int primitiveMode) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBeginTransformFeedback(primitiveMode);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glEndTransformFeedback(xlong nativehandle) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glEndTransformFeedback();
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBindBufferRange(xlong nativehandle, int target, int index, int buffer, xlong offset, GLsizeiptr size) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBindBufferRange(target, index, buffer, offset, size);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBindBufferBase(xlong nativehandle, int target, int index, int buffer) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBindBufferBase(target, index, buffer);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTransformFeedbackVaryings(xlong nativehandle, int program, int count, xstring varyings, int bufferMode) {
#if !defined(QT_NO_OPENGL)
	if (count > 1)return;  ((QOpenGLExtraFunctions*)nativehandle)->glTransformFeedbackVaryings(program, count, (const GLchar *const*)&varyings, bufferMode);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetTransformFeedbackVarying(xlong nativehandle, int program, int index, int bufSize, int  * length, int  * size, int  * type, xbyte  * name) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetTransformFeedbackVarying(program, index, bufSize, length, size, (GLenum*)type, (GLchar*)name);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttribIPointer(xlong nativehandle, int index, int size, int type, int stride, void  * pointer) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glVertexAttribIPointer(index, size, type, stride, pointer);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetVertexAttribIiv(xlong nativehandle, int index, int pname, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetVertexAttribIiv(index, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetVertexAttribIuiv(xlong nativehandle, int index, int pname, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetVertexAttribIuiv(index, pname, (GLuint*)params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttribI4i(xlong nativehandle, int index, int x, int y, int z, int w) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glVertexAttribI4i(index, x, y, z, w);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttribI4ui(xlong nativehandle, int index, int x, int y, int z, int w) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glVertexAttribI4ui(index, x, y, z, w);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttribI4iv(xlong nativehandle, int index, int  * v) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glVertexAttribI4iv(index, v);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttribI4uiv(xlong nativehandle, int index, int  * v) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glVertexAttribI4uiv(index, (GLuint*)v);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetUniformuiv(xlong nativehandle, int program, int location, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetUniformuiv(program, location, (GLuint*)params);
#else

#endif
}

XNLEXPORT int XI_CDECL qfn_glGetFragDataLocation(xlong nativehandle, int program, xstring name) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glGetFragDataLocation(program, name);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform1ui(xlong nativehandle, int location, int v0) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniform1ui(location, v0);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform2ui(xlong nativehandle, int location, int v0, int v1) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniform2ui(location, v0, v1);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform3ui(xlong nativehandle, int location, int v0, int v1, int v2) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniform3ui(location, v0, v1, v2);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform4ui(xlong nativehandle, int location, int v0, int v1, int v2, int v3) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniform4ui(location, v0, v1, v2, v3);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform1uiv(xlong nativehandle, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniform1uiv(location, count, (GLuint*)value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform2uiv(xlong nativehandle, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniform2uiv(location, count, (GLuint*)value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform3uiv(xlong nativehandle, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniform3uiv(location, count, (GLuint*)value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniform4uiv(xlong nativehandle, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniform4uiv(location, count, (GLuint*)value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glClearBufferiv(xlong nativehandle, int buffer, int drawbuffer, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glClearBufferiv(buffer, drawbuffer, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glClearBufferuiv(xlong nativehandle, int buffer, int drawbuffer, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glClearBufferuiv(buffer, drawbuffer, (GLuint*)value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glClearBufferfv(xlong nativehandle, int buffer, int drawbuffer, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glClearBufferfv(buffer, drawbuffer, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glClearBufferfi(xlong nativehandle, int buffer, int drawbuffer, float depth, int stencil) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glClearBufferfi(buffer, drawbuffer, depth, stencil);
#else

#endif
}

XNLEXPORT xstring XI_CDECL qfn_glGetStringi(xlong nativehandle, int name, int index) {
#if !defined(QT_NO_OPENGL)
	return (xstring)((QOpenGLExtraFunctions*)nativehandle)->glGetStringi(name, index);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glCopyBufferSubData(xlong nativehandle, int readTarget, int writeTarget, xlong readOffset, xlong writeOffset, GLsizeiptr size) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glCopyBufferSubData(readTarget, writeTarget, readOffset, writeOffset, size);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetUniformIndices(xlong nativehandle, int program, int uniformCount, xstring uniformNames, int  * uniformIndices) {
#if !defined(QT_NO_OPENGL)
	if (uniformCount > 1)return; ((QOpenGLExtraFunctions*)nativehandle)->glGetUniformIndices(program, uniformCount, (const GLchar *const*)&uniformNames, (GLuint*)uniformIndices);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetActiveUniformsiv(xlong nativehandle, int program, int uniformCount, int  * uniformIndices, int pname, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetActiveUniformsiv(program, uniformCount, (GLuint*)uniformIndices, pname, params);
#else

#endif
}

XNLEXPORT int XI_CDECL qfn_glGetUniformBlockIndex(xlong nativehandle, int program, xstring uniformBlockName) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glGetUniformBlockIndex(program, uniformBlockName);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glGetActiveUniformBlockiv(xlong nativehandle, int program, int uniformBlockIndex, int pname, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetActiveUniformBlockiv(program, uniformBlockIndex, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetActiveUniformBlockName(xlong nativehandle, int program, int uniformBlockIndex, int bufSize, int  * length, xbyte  * uniformBlockName) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetActiveUniformBlockName(program, uniformBlockIndex, bufSize, length, (GLchar*)uniformBlockName);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glUniformBlockBinding(xlong nativehandle, int program, int uniformBlockIndex, int uniformBlockBinding) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDrawArraysInstanced(xlong nativehandle, int mode, int first, int count, int instancecount) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDrawArraysInstanced(mode, first, count, instancecount);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDrawElementsInstanced(xlong nativehandle, int mode, int count, int type, void  * indices, int instancecount) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDrawElementsInstanced(mode, count, type, indices, instancecount);
#else

#endif
}

XNLEXPORT void* XI_CDECL qfn_glFenceSync(xlong nativehandle, int condition, int flags) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glFenceSync(condition, flags);
#else

#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsSync(xlong nativehandle, GLsync sync) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glIsSync(sync);
#else
	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteSync(xlong nativehandle, GLsync sync) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDeleteSync(sync);
#else

#endif
}

XNLEXPORT int XI_CDECL qfn_glClientWaitSync(xlong nativehandle, GLsync sync, int flags, GLuint64 timeout) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glClientWaitSync(sync, flags, timeout);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glWaitSync(xlong nativehandle, GLsync sync, int flags, GLuint64 timeout) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glWaitSync(sync, flags, timeout);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetInteger64v(xlong nativehandle, int pname, xlong  * data) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetInteger64v(pname, (GLint64*)data);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetSynciv(xlong nativehandle, GLsync sync, int pname, int bufSize, int  * length, int  * values) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetSynciv(sync, pname, bufSize, length, values);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetInteger64i_v(xlong nativehandle, int target, int index, xlong  * data) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetInteger64i_v(target, index, (GLint64*)data);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetBufferParameteri64v(xlong nativehandle, int target, int pname, xlong  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetBufferParameteri64v(target, pname, (GLint64*)params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGenSamplers(xlong nativehandle, int count, int  * samplers) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGenSamplers(count, (GLuint*)samplers);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteSamplers(xlong nativehandle, int count, int  * samplers) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDeleteSamplers(count, (GLuint*)samplers);
#else

#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsSampler(xlong nativehandle, int sampler) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glIsSampler(sampler);
#else
	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_glBindSampler(xlong nativehandle, int unit, int sampler) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBindSampler(unit, sampler);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glSamplerParameteri(xlong nativehandle, int sampler, int pname, int param) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glSamplerParameteri(sampler, pname, param);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glSamplerParameteriv(xlong nativehandle, int sampler, int pname, int  * param) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glSamplerParameteriv(sampler, pname, param);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glSamplerParameterf(xlong nativehandle, int sampler, int pname, float param) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glSamplerParameterf(sampler, pname, param);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glSamplerParameterfv(xlong nativehandle, int sampler, int pname, float  * param) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glSamplerParameterfv(sampler, pname, param);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetSamplerParameteriv(xlong nativehandle, int sampler, int pname, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetSamplerParameteriv(sampler, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetSamplerParameterfv(xlong nativehandle, int sampler, int pname, float  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetSamplerParameterfv(sampler, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttribDivisor(xlong nativehandle, int index, int divisor) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glVertexAttribDivisor(index, divisor);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBindTransformFeedback(xlong nativehandle, int target, int id) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBindTransformFeedback(target, id);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteTransformFeedbacks(xlong nativehandle, int n, int  * ids) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDeleteTransformFeedbacks(n, (GLuint*)ids);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGenTransformFeedbacks(xlong nativehandle, int n, int  * ids) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGenTransformFeedbacks(n, (GLuint*)ids);
#else

#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsTransformFeedback(xlong nativehandle, int id) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glIsTransformFeedback(id);
#else
	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_glPauseTransformFeedback(xlong nativehandle) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glPauseTransformFeedback();
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glResumeTransformFeedback(xlong nativehandle) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glResumeTransformFeedback();
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetProgramBinary(xlong nativehandle, int program, int bufSize, int  * length, int  * binaryFormat, void  * binary) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetProgramBinary(program, bufSize, length, (GLenum*)binaryFormat, binary);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramBinary(xlong nativehandle, int program, int binaryFormat, void  * binary, int length) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramBinary(program, binaryFormat, binary, length);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramParameteri(xlong nativehandle, int program, int pname, int value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramParameteri(program, pname, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glInvalidateFramebuffer(xlong nativehandle, int target, int numAttachments, int  * attachments) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glInvalidateFramebuffer(target, numAttachments, (GLenum*)attachments);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glInvalidateSubFramebuffer(xlong nativehandle, int target, int numAttachments, int  * attachments, int x, int y, int width, int height) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glInvalidateSubFramebuffer(target, numAttachments, (GLenum*)attachments, x, y, width, height);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexStorage2D(xlong nativehandle, int target, int levels, int internalformat, int width, int height) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glTexStorage2D(target, levels, internalformat, width, height);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexStorage3D(xlong nativehandle, int target, int levels, int internalformat, int width, int height, int depth) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glTexStorage3D(target, levels, internalformat, width, height, depth);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetInternalformativ(xlong nativehandle, int target, int internalformat, int pname, int bufSize, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetInternalformativ(target, internalformat, pname, bufSize, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDispatchCompute(xlong nativehandle, int num_groups_x, int num_groups_y, int num_groups_z) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDispatchCompute(num_groups_x, num_groups_y, num_groups_z);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDispatchComputeIndirect(xlong nativehandle, xlong indirect) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDispatchComputeIndirect(indirect);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDrawArraysIndirect(xlong nativehandle, int mode, void  * indirect) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDrawArraysIndirect(mode, indirect);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDrawElementsIndirect(xlong nativehandle, int mode, int type, void  * indirect) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDrawElementsIndirect(mode, type, indirect);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glFramebufferParameteri(xlong nativehandle, int target, int pname, int param) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glFramebufferParameteri(target, pname, param);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetFramebufferParameteriv(xlong nativehandle, int target, int pname, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetFramebufferParameteriv(target, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetProgramInterfaceiv(xlong nativehandle, int program, int programInterface, int pname, int* params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetProgramInterfaceiv(program, programInterface, pname, (GLint*)params);
#else

#endif
}

XNLEXPORT int XI_CDECL qfn_glGetProgramResourceIndex(xlong nativehandle, int program, int programInterface, xstring name) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glGetProgramResourceIndex(program, programInterface, name);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glGetProgramResourceName(xlong nativehandle, int program, int programInterface, int index, int bufSize, int  * length, xbyte  * name) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetProgramResourceName(program, programInterface, index, bufSize, length, (GLchar*)name);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetProgramResourceiv(xlong nativehandle, int program, int programInterface, int index, int propCount, int  * props, int bufSize, int  * length, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetProgramResourceiv(program, programInterface, index, propCount, (GLenum*)props, bufSize, length, params);
#else

#endif
}

XNLEXPORT int XI_CDECL qfn_glGetProgramResourceLocation(xlong nativehandle, int program, int programInterface, xstring name) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glGetProgramResourceLocation(program, programInterface, name);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glUseProgramStages(xlong nativehandle, int pipeline, int stages, int program) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glUseProgramStages(pipeline, stages, program);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glActiveShaderProgram(xlong nativehandle, int pipeline, int program) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glActiveShaderProgram(pipeline, program);
#else

#endif
}

XNLEXPORT int XI_CDECL qfn_glCreateShaderProgramv(xlong nativehandle, int type, int count, xstring strings) {
#if !defined(QT_NO_OPENGL)
	if (count > 1)return 0;  return ((QOpenGLExtraFunctions*)nativehandle)->glCreateShaderProgramv(type, count, (const GLchar *const*)&strings);
#else
	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_glBindProgramPipeline(xlong nativehandle, int pipeline) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBindProgramPipeline(pipeline);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glDeleteProgramPipelines(xlong nativehandle, int n, int  * pipelines) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glDeleteProgramPipelines(n, (GLuint*)pipelines);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGenProgramPipelines(xlong nativehandle, int n, int  * pipelines) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGenProgramPipelines(n, (GLuint*)pipelines);
#else

#endif
}

XNLEXPORT bool XI_CDECL qfn_glIsProgramPipeline(xlong nativehandle, int pipeline) {
#if !defined(QT_NO_OPENGL)
	return ((QOpenGLExtraFunctions*)nativehandle)->glIsProgramPipeline(pipeline);
#else
	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_glGetProgramPipelineiv(xlong nativehandle, int pipeline, int pname, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetProgramPipelineiv(pipeline, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform1i(xlong nativehandle, int program, int location, int v0) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform1i(program, location, v0);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform2i(xlong nativehandle, int program, int location, int v0, int v1) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform2i(program, location, v0, v1);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform3i(xlong nativehandle, int program, int location, int v0, int v1, int v2) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform3i(program, location, v0, v1, v2);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform4i(xlong nativehandle, int program, int location, int v0, int v1, int v2, int v3) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform4i(program, location, v0, v1, v2, v3);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform1ui(xlong nativehandle, int program, int location, int v0) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform1ui(program, location, v0);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform2ui(xlong nativehandle, int program, int location, int v0, int v1) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform2ui(program, location, v0, v1);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform3ui(xlong nativehandle, int program, int location, int v0, int v1, int v2) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform3ui(program, location, v0, v1, v2);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform4ui(xlong nativehandle, int program, int location, int v0, int v1, int v2, int v3) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform4ui(program, location, v0, v1, v2, v3);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform1f(xlong nativehandle, int program, int location, float v0) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform1f(program, location, v0);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform2f(xlong nativehandle, int program, int location, float v0, float v1) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform2f(program, location, v0, v1);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform3f(xlong nativehandle, int program, int location, float v0, float v1, float v2) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform3f(program, location, v0, v1, v2);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform4f(xlong nativehandle, int program, int location, float v0, float v1, float v2, float v3) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform4f(program, location, v0, v1, v2, v3);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform1iv(xlong nativehandle, int program, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform1iv(program, location, count, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform2iv(xlong nativehandle, int program, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform2iv(program, location, count, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform3iv(xlong nativehandle, int program, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform3iv(program, location, count, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform4iv(xlong nativehandle, int program, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform4iv(program, location, count, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform1uiv(xlong nativehandle, int program, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform1uiv(program, location, count, (GLuint*)value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform2uiv(xlong nativehandle, int program, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform2uiv(program, location, count, (GLuint*)value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform3uiv(xlong nativehandle, int program, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform3uiv(program, location, count, (GLuint*)value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform4uiv(xlong nativehandle, int program, int location, int count, int  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform4uiv(program, location, count, (GLuint*)value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform1fv(xlong nativehandle, int program, int location, int count, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform1fv(program, location, count, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform2fv(xlong nativehandle, int program, int location, int count, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform2fv(program, location, count, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform3fv(xlong nativehandle, int program, int location, int count, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform3fv(program, location, count, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniform4fv(xlong nativehandle, int program, int location, int count, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniform4fv(program, location, count, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniformMatrix2fv(xlong nativehandle, int program, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniformMatrix2fv(program, location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniformMatrix3fv(xlong nativehandle, int program, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniformMatrix3fv(program, location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniformMatrix4fv(xlong nativehandle, int program, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniformMatrix4fv(program, location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniformMatrix2x3fv(xlong nativehandle, int program, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniformMatrix2x3fv(program, location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniformMatrix3x2fv(xlong nativehandle, int program, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniformMatrix3x2fv(program, location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniformMatrix2x4fv(xlong nativehandle, int program, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniformMatrix2x4fv(program, location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniformMatrix4x2fv(xlong nativehandle, int program, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniformMatrix4x2fv(program, location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniformMatrix3x4fv(xlong nativehandle, int program, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniformMatrix3x4fv(program, location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glProgramUniformMatrix4x3fv(xlong nativehandle, int program, int location, int count, bool transpose, float  * value) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glProgramUniformMatrix4x3fv(program, location, count, transpose, value);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glValidateProgramPipeline(xlong nativehandle, int pipeline) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glValidateProgramPipeline(pipeline);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetProgramPipelineInfoLog(xlong nativehandle, int pipeline, int bufSize, int  * length, xbyte  * infoLog) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetProgramPipelineInfoLog(pipeline, bufSize, length, (GLchar*)infoLog);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBindImageTexture(xlong nativehandle, int unit, int texture, int level, bool layered, int layer, int access, int format) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBindImageTexture(unit, texture, level, layered, layer, access, format);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetBooleani_v(xlong nativehandle, int target, int index, xbyte  * data) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetBooleani_v(target, index, data);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glMemoryBarrier(xlong nativehandle, int barriers) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glMemoryBarrier(barriers);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glMemoryBarrierByRegion(xlong nativehandle, int barriers) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glMemoryBarrierByRegion(barriers);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glTexStorage2DMultisample(xlong nativehandle, int target, int samples, int internalformat, int width, int height, bool fixedsamplelocations) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glTexStorage2DMultisample(target, samples, internalformat, width, height, fixedsamplelocations);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetMultisamplefv(xlong nativehandle, int pname, int index, float  * val) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetMultisamplefv(pname, index, val);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glSampleMaski(xlong nativehandle, int maskNumber, int mask) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glSampleMaski(maskNumber, mask);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetTexLevelParameteriv(xlong nativehandle, int target, int level, int pname, int  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetTexLevelParameteriv(target, level, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glGetTexLevelParameterfv(xlong nativehandle, int target, int level, int pname, float  * params) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glGetTexLevelParameterfv(target, level, pname, params);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glBindVertexBuffer(xlong nativehandle, int bindingindex, int buffer, xlong offset, int stride) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glBindVertexBuffer(bindingindex, buffer, offset, stride);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttribFormat(xlong nativehandle, int attribindex, int size, int type, bool normalized, int relativeoffset) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glVertexAttribFormat(attribindex, size, type, normalized, relativeoffset);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttribIFormat(xlong nativehandle, int attribindex, int size, int type, int relativeoffset) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glVertexAttribIFormat(attribindex, size, type, relativeoffset);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexAttribBinding(xlong nativehandle, int attribindex, int bindingindex) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glVertexAttribBinding(attribindex, bindingindex);
#else

#endif
}

XNLEXPORT void XI_CDECL qfn_glVertexBindingDivisor(xlong nativehandle, int bindingindex, int divisor) {
#if !defined(QT_NO_OPENGL)
	((QOpenGLExtraFunctions*)nativehandle)->glVertexBindingDivisor(bindingindex, divisor);
#else

#endif
}




XNLEXPORT void XI_CDECL qfn_1_0_glViewport(xlong nativehandle, int x, int y, int width, int height) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glViewport(x, y, width, height);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glDepthRange(xlong nativehandle, double nearVal, double farVal) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glDepthRange(nearVal, farVal);
#else


#endif
}

XNLEXPORT bool XI_CDECL qfn_1_0_glIsEnabled(xlong nativehandle, int cap) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_0*)nativehandle)->glIsEnabled(cap);
#else

	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetTexLevelParameteriv(xlong nativehandle, int target, int level, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetTexLevelParameteriv(target, level, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetTexLevelParameterfv(xlong nativehandle, int target, int level, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetTexLevelParameterfv(target, level, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetTexParameteriv(xlong nativehandle, int target, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetTexParameteriv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetTexParameterfv(xlong nativehandle, int target, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetTexParameterfv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetTexImage(xlong nativehandle, int target, int level, int format, int type, void  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetTexImage(target, level, format, type, pixels);
#else


#endif
}

XNLEXPORT xstring XI_CDECL qfn_1_0_glGetString(xlong nativehandle, int name) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return (xstring)((QOpenGLFunctions_1_0*)nativehandle)->glGetString(name);
#else

	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetIntegerv(xlong nativehandle, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetIntegerv(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetFloatv(xlong nativehandle, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetFloatv(pname, params);
#else


#endif
}

XNLEXPORT int XI_CDECL qfn_1_0_glGetError(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_0*)nativehandle)->glGetError();
#else

	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetDoublev(xlong nativehandle, int pname, double  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetDoublev(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetBooleanv(xlong nativehandle, int pname, bool  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetBooleanv(pname, (GLboolean*)params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glReadPixels(xlong nativehandle, int x, int y, int width, int height, int format, int type, void  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glReadPixels(x, y, width, height, format, type, pixels);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glReadBuffer(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glReadBuffer(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPixelStorei(xlong nativehandle, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPixelStorei(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPixelStoref(xlong nativehandle, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPixelStoref(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glDepthFunc(xlong nativehandle, int func) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glDepthFunc(func);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glStencilOp(xlong nativehandle, int fail, int zfail, int zpass) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glStencilOp(fail, zfail, zpass);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glStencilFunc(xlong nativehandle, int func, int ref, int mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glStencilFunc(func, ref, mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLogicOp(xlong nativehandle, int opcode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLogicOp(opcode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glBlendFunc(xlong nativehandle, int sfactor, int dfactor) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glBlendFunc(sfactor, dfactor);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glFlush(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glFlush();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glFinish(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glFinish();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEnable(xlong nativehandle, int cap) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEnable(cap);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glDisable(xlong nativehandle, int cap) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glDisable(cap);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glDepthMask(xlong nativehandle, bool flag) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glDepthMask(flag);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColorMask(xlong nativehandle, bool red, bool green, bool blue, bool alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColorMask(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glStencilMask(xlong nativehandle, int mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glStencilMask(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glClearDepth(xlong nativehandle, double depth) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glClearDepth(depth);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glClearStencil(xlong nativehandle, int s) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glClearStencil(s);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glClearColor(xlong nativehandle, float red, float green, float blue, float alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glClearColor(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glClear(xlong nativehandle, GLbitfield mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glClear(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glDrawBuffer(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glDrawBuffer(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexImage2D(xlong nativehandle, int target, int level, int internalformat, int width, int height, int border, int format, int type, const void  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexImage1D(xlong nativehandle, int target, int level, int internalformat, int width, int border, int format, int type, const void  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexParameteriv(xlong nativehandle, int target, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexParameteriv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexParameteri(xlong nativehandle, int target, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexParameteri(target, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexParameterfv(xlong nativehandle, int target, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexParameterfv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexParameterf(xlong nativehandle, int target, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexParameterf(target, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glScissor(xlong nativehandle, int x, int y, int width, int height) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glScissor(x, y, width, height);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPolygonMode(xlong nativehandle, int face, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPolygonMode(face, mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPointSize(xlong nativehandle, float size) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPointSize(size);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLineWidth(xlong nativehandle, float width) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLineWidth(width);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glHint(xlong nativehandle, int target, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glHint(target, mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glFrontFace(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glFrontFace(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glCullFace(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glCullFace(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTranslatef(xlong nativehandle, float x, float y, float z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTranslatef(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTranslated(xlong nativehandle, double x, double y, double z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTranslated(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glScalef(xlong nativehandle, float x, float y, float z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glScalef(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glScaled(xlong nativehandle, double x, double y, double z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glScaled(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRotatef(xlong nativehandle, float angle, float x, float y, float z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRotatef(angle, x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRotated(xlong nativehandle, double angle, double x, double y, double z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRotated(angle, x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPushMatrix(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPushMatrix();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPopMatrix(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPopMatrix();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glOrtho(xlong nativehandle, double left, double right, double bottom, double top, double zNear, double zFar) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glOrtho(left, right, bottom, top, zNear, zFar);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMultMatrixd(xlong nativehandle, const double  * m) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMultMatrixd(m);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMultMatrixf(xlong nativehandle, const float  * m) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMultMatrixf(m);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMatrixMode(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMatrixMode(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLoadMatrixd(xlong nativehandle, const double  * m) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLoadMatrixd(m);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLoadMatrixf(xlong nativehandle, const float  * m) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLoadMatrixf(m);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLoadIdentity(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLoadIdentity();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glFrustum(xlong nativehandle, double left, double right, double bottom, double top, double zNear, double zFar) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glFrustum(left, right, bottom, top, zNear, zFar);
#else


#endif
}

XNLEXPORT bool XI_CDECL qfn_1_0_glIsList(xlong nativehandle, int list) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_0*)nativehandle)->glIsList(list);
#else

	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetTexGeniv(xlong nativehandle, int coord, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetTexGeniv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetTexGenfv(xlong nativehandle, int coord, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetTexGenfv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetTexGendv(xlong nativehandle, int coord, int pname, double  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetTexGendv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetTexEnviv(xlong nativehandle, int target, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetTexEnviv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetTexEnvfv(xlong nativehandle, int target, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetTexEnvfv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetPolygonStipple(xlong nativehandle, GLubyte  * mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetPolygonStipple(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetPixelMapusv(xlong nativehandle, int map, GLushort  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetPixelMapusv(map, values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetPixelMapuiv(xlong nativehandle, int map, int  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetPixelMapuiv(map, (GLuint*)values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetPixelMapfv(xlong nativehandle, int map, float  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetPixelMapfv(map, values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetMaterialiv(xlong nativehandle, int face, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetMaterialiv(face, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetMaterialfv(xlong nativehandle, int face, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetMaterialfv(face, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetMapiv(xlong nativehandle, int target, int query, int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetMapiv(target, query, v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetMapfv(xlong nativehandle, int target, int query, float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetMapfv(target, query, v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetMapdv(xlong nativehandle, int target, int query, double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetMapdv(target, query, v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetLightiv(xlong nativehandle, int light, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetLightiv(light, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetLightfv(xlong nativehandle, int light, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetLightfv(light, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glGetClipPlane(xlong nativehandle, int plane, double  * equation) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glGetClipPlane(plane, equation);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glDrawPixels(xlong nativehandle, int width, int height, int format, int type, const void  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glDrawPixels(width, height, format, type, pixels);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glCopyPixels(xlong nativehandle, int x, int y, int width, int height, int type) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glCopyPixels(x, y, width, height, type);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPixelMapusv(xlong nativehandle, int map, int mapsize, const GLushort  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPixelMapusv(map, mapsize, values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPixelMapuiv(xlong nativehandle, int map, int mapsize, const int  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPixelMapuiv(map, mapsize, (GLuint*)values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPixelMapfv(xlong nativehandle, int map, int mapsize, const float  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPixelMapfv(map, mapsize, values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPixelTransferi(xlong nativehandle, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPixelTransferi(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPixelTransferf(xlong nativehandle, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPixelTransferf(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPixelZoom(xlong nativehandle, float xfactor, float yfactor) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPixelZoom(xfactor, yfactor);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glAlphaFunc(xlong nativehandle, int func, float ref) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glAlphaFunc(func, ref);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalPoint2(xlong nativehandle, int i, int j) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalPoint2(i, j);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalMesh2(xlong nativehandle, int mode, int i1, int i2, int j1, int j2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalMesh2(mode, i1, i2, j1, j2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalPoint1(xlong nativehandle, int i) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalPoint1(i);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalMesh1(xlong nativehandle, int mode, int i1, int i2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalMesh1(mode, i1, i2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalCoord2fv(xlong nativehandle, const float  * u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalCoord2fv(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalCoord2f(xlong nativehandle, float u, float v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalCoord2f(u, v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalCoord2dv(xlong nativehandle, const double  * u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalCoord2dv(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalCoord2d(xlong nativehandle, double u, double v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalCoord2d(u, v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalCoord1fv(xlong nativehandle, const float  * u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalCoord1fv(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalCoord1f(xlong nativehandle, float u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalCoord1f(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalCoord1dv(xlong nativehandle, const double  * u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalCoord1dv(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEvalCoord1d(xlong nativehandle, double u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEvalCoord1d(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMapGrid2f(xlong nativehandle, int un, float u1, float u2, int vn, float v1, float v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMapGrid2f(un, u1, u2, vn, v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMapGrid2d(xlong nativehandle, int un, double u1, double u2, int vn, double v1, double v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMapGrid2d(un, u1, u2, vn, v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMapGrid1f(xlong nativehandle, int un, float u1, float u2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMapGrid1f(un, u1, u2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMapGrid1d(xlong nativehandle, int un, double u1, double u2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMapGrid1d(un, u1, u2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMap2f(xlong nativehandle, int target, float u1, float u2, int ustride, int uorder, float v1, float v2, int vstride, int vorder, const float  * points) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMap2d(xlong nativehandle, int target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, const double  * points) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMap1f(xlong nativehandle, int target, float u1, float u2, int stride, int order, const float  * points) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMap1f(target, u1, u2, stride, order, points);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMap1d(xlong nativehandle, int target, double u1, double u2, int stride, int order, const double  * points) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMap1d(target, u1, u2, stride, order, points);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPushAttrib(xlong nativehandle, GLbitfield mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPushAttrib(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPopAttrib(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPopAttrib();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glAccum(xlong nativehandle, int op, float value) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glAccum(op, value);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glIndexMask(xlong nativehandle, int mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glIndexMask(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glClearIndex(xlong nativehandle, float c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glClearIndex(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glClearAccum(xlong nativehandle, float red, float green, float blue, float alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glClearAccum(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPushName(xlong nativehandle, int name) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPushName(name);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPopName(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPopName();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPassThrough(xlong nativehandle, float token) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPassThrough(token);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLoadName(xlong nativehandle, int name) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLoadName(name);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glInitNames(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glInitNames();
#else


#endif
}

XNLEXPORT int XI_CDECL qfn_1_0_glRenderMode(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_0*)nativehandle)->glRenderMode(mode);
#else

	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glSelectBuffer(xlong nativehandle, int size, int  * buffer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glSelectBuffer(size, (GLuint*)buffer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glFeedbackBuffer(xlong nativehandle, int size, int type, float  * buffer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glFeedbackBuffer(size, type, buffer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexGeniv(xlong nativehandle, int coord, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexGeniv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexGeni(xlong nativehandle, int coord, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexGeni(coord, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexGenfv(xlong nativehandle, int coord, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexGenfv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexGenf(xlong nativehandle, int coord, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexGenf(coord, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexGendv(xlong nativehandle, int coord, int pname, const double  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexGendv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexGend(xlong nativehandle, int coord, int pname, double param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexGend(coord, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexEnviv(xlong nativehandle, int target, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexEnviv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexEnvi(xlong nativehandle, int target, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexEnvi(target, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexEnvfv(xlong nativehandle, int target, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexEnvfv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexEnvf(xlong nativehandle, int target, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexEnvf(target, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glShadeModel(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glShadeModel(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glPolygonStipple(xlong nativehandle, const GLubyte  * mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glPolygonStipple(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMaterialiv(xlong nativehandle, int face, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMaterialiv(face, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMateriali(xlong nativehandle, int face, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMateriali(face, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMaterialfv(xlong nativehandle, int face, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMaterialfv(face, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glMaterialf(xlong nativehandle, int face, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glMaterialf(face, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLineStipple(xlong nativehandle, int factor, GLushort pattern) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLineStipple(factor, pattern);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLightModeliv(xlong nativehandle, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLightModeliv(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLightModeli(xlong nativehandle, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLightModeli(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLightModelfv(xlong nativehandle, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLightModelfv(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLightModelf(xlong nativehandle, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLightModelf(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLightiv(xlong nativehandle, int light, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLightiv(light, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLighti(xlong nativehandle, int light, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLighti(light, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLightfv(xlong nativehandle, int light, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLightfv(light, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glLightf(xlong nativehandle, int light, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glLightf(light, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glFogiv(xlong nativehandle, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glFogiv(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glFogi(xlong nativehandle, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glFogi(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glFogfv(xlong nativehandle, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glFogfv(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glFogf(xlong nativehandle, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glFogf(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColorMaterial(xlong nativehandle, int face, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColorMaterial(face, mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glClipPlane(xlong nativehandle, int plane, const double  * equation) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glClipPlane(plane, equation);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex4sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex4sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex4s(xlong nativehandle, short x, short y, short z, short w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex4s(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex4iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex4iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex4i(xlong nativehandle, int x, int y, int z, int w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex4i(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex4fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex4fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex4f(xlong nativehandle, float x, float y, float z, float w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex4f(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex4dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex4dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex4d(xlong nativehandle, double x, double y, double z, double w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex4d(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex3sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex3sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex3s(xlong nativehandle, short x, short y, short z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex3s(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex3iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex3iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex3i(xlong nativehandle, int x, int y, int z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex3i(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex3fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex3fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex3f(xlong nativehandle, float x, float y, float z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex3f(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex3dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex3dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex3d(xlong nativehandle, double x, double y, double z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex3d(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex2sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex2sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex2s(xlong nativehandle, short x, short y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex2s(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex2iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex2iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex2i(xlong nativehandle, int x, int y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex2i(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex2fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex2fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex2f(xlong nativehandle, float x, float y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex2f(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex2dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex2dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glVertex2d(xlong nativehandle, double x, double y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glVertex2d(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord4sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord4sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord4s(xlong nativehandle, short s, short t, short r, short q) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord4s(s, t, r, q);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord4iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord4iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord4i(xlong nativehandle, int s, int t, int r, int q) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord4i(s, t, r, q);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord4fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord4fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord4f(xlong nativehandle, float s, float t, float r, float q) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord4f(s, t, r, q);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord4dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord4dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord4d(xlong nativehandle, double s, double t, double r, double q) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord4d(s, t, r, q);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord3sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord3sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord3s(xlong nativehandle, short s, short t, short r) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord3s(s, t, r);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord3iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord3iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord3i(xlong nativehandle, int s, int t, int r) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord3i(s, t, r);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord3fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord3fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord3f(xlong nativehandle, float s, float t, float r) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord3f(s, t, r);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord3dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord3dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord3d(xlong nativehandle, double s, double t, double r) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord3d(s, t, r);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord2sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord2sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord2s(xlong nativehandle, short s, short t) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord2s(s, t);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord2iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord2iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord2i(xlong nativehandle, int s, int t) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord2i(s, t);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord2fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord2fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord2f(xlong nativehandle, float s, float t) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord2f(s, t);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord2dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord2dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord2d(xlong nativehandle, double s, double t) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord2d(s, t);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord1sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord1sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord1s(xlong nativehandle, short s) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord1s(s);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord1iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord1iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord1i(xlong nativehandle, int s) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord1i(s);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord1fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord1fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord1f(xlong nativehandle, float s) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord1f(s);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord1dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord1dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glTexCoord1d(xlong nativehandle, double s) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glTexCoord1d(s);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRectsv(xlong nativehandle, const short  * v1, const short  * v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRectsv(v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRects(xlong nativehandle, short x1, short y1, short x2, short y2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRects(x1, y1, x2, y2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRectiv(xlong nativehandle, const int  * v1, const int  * v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRectiv(v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRecti(xlong nativehandle, int x1, int y1, int x2, int y2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRecti(x1, y1, x2, y2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRectfv(xlong nativehandle, const float  * v1, const float  * v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRectfv(v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRectf(xlong nativehandle, float x1, float y1, float x2, float y2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRectf(x1, y1, x2, y2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRectdv(xlong nativehandle, const double  * v1, const double  * v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRectdv(v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRectd(xlong nativehandle, double x1, double y1, double x2, double y2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRectd(x1, y1, x2, y2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos4sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos4sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos4s(xlong nativehandle, short x, short y, short z, short w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos4s(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos4iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos4iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos4i(xlong nativehandle, int x, int y, int z, int w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos4i(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos4fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos4fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos4f(xlong nativehandle, float x, float y, float z, float w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos4f(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos4dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos4dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos4d(xlong nativehandle, double x, double y, double z, double w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos4d(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos3sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos3sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos3s(xlong nativehandle, short x, short y, short z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos3s(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos3iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos3iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos3i(xlong nativehandle, int x, int y, int z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos3i(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos3fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos3fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos3f(xlong nativehandle, float x, float y, float z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos3f(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos3dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos3dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos3d(xlong nativehandle, double x, double y, double z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos3d(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos2sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos2sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos2s(xlong nativehandle, short x, short y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos2s(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos2iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos2iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos2i(xlong nativehandle, int x, int y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos2i(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos2fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos2fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos2f(xlong nativehandle, float x, float y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos2f(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos2dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos2dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glRasterPos2d(xlong nativehandle, double x, double y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glRasterPos2d(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNormal3sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNormal3sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNormal3s(xlong nativehandle, short nx, short ny, short nz) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNormal3s(nx, ny, nz);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNormal3iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNormal3iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNormal3i(xlong nativehandle, int nx, int ny, int nz) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNormal3i(nx, ny, nz);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNormal3fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNormal3fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNormal3f(xlong nativehandle, float nx, float ny, float nz) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNormal3f(nx, ny, nz);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNormal3dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNormal3dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNormal3d(xlong nativehandle, double nx, double ny, double nz) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNormal3d(nx, ny, nz);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNormal3bv(xlong nativehandle, const GLbyte  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNormal3bv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNormal3b(xlong nativehandle, xbyte nx, xbyte ny, xbyte nz) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNormal3b(nx, ny, nz);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glIndexsv(xlong nativehandle, const short  * c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glIndexsv(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glIndexs(xlong nativehandle, short c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glIndexs(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glIndexiv(xlong nativehandle, const int  * c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glIndexiv(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glIndexi(xlong nativehandle, int c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glIndexi(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glIndexfv(xlong nativehandle, const float  * c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glIndexfv(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glIndexf(xlong nativehandle, float c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glIndexf(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glIndexdv(xlong nativehandle, const double  * c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glIndexdv(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glIndexd(xlong nativehandle, double c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glIndexd(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEnd(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEnd();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEdgeFlagv(xlong nativehandle, const GLboolean  * flag) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEdgeFlagv(flag);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEdgeFlag(xlong nativehandle, bool flag) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEdgeFlag(flag);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4usv(xlong nativehandle, const GLushort  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4usv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4us(xlong nativehandle, GLushort red, GLushort green, GLushort blue, GLushort alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4us(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4uiv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4uiv((GLuint*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4ui(xlong nativehandle, int red, int green, int blue, int alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4ui(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4ubv(xlong nativehandle, const xbyte  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4ubv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4ub(xlong nativehandle, xbyte red, xbyte green, xbyte blue, xbyte alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4ub(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4s(xlong nativehandle, short red, short green, short blue, short alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4s(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4i(xlong nativehandle, int red, int green, int blue, int alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4i(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4f(xlong nativehandle, float red, float green, float blue, float alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4f(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4d(xlong nativehandle, double red, double green, double blue, double alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4d(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4bv(xlong nativehandle, const xbyte  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4bv((GLbyte*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor4b(xlong nativehandle, xbyte red, xbyte green, xbyte blue, xbyte alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor4b(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3usv(xlong nativehandle, const GLushort  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3usv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3us(xlong nativehandle, GLushort red, GLushort green, GLushort blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3us(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3uiv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3uiv((GLuint*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3ui(xlong nativehandle, int red, int green, int blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3ui(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3ubv(xlong nativehandle, const xbyte  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3ubv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3ub(xlong nativehandle, xbyte red, xbyte green, xbyte blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3ub(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3s(xlong nativehandle, short red, short green, short blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3s(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3i(xlong nativehandle, int red, int green, int blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3i(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3f(xlong nativehandle, float red, float green, float blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3f(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3d(xlong nativehandle, double red, double green, double blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3d(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3bv(xlong nativehandle, const xbyte  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3bv((GLbyte*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glColor3b(xlong nativehandle, xbyte red, xbyte green, xbyte blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glColor3b(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glBitmap(xlong nativehandle, int width, int height, float xorig, float yorig, float xmove, float ymove, const xbyte  * bitmap) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glBegin(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glBegin(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glListBase(xlong nativehandle, int base) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glListBase(base);
#else


#endif
}

XNLEXPORT int XI_CDECL qfn_1_0_glGenLists(xlong nativehandle, int range) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_0*)nativehandle)->glGenLists(range);
#else

	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glDeleteLists(xlong nativehandle, int list, int range) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glDeleteLists(list, range);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glCallLists(xlong nativehandle, int n, int type, void* lists) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glCallLists(n, type, lists);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glCallList(xlong nativehandle, int list) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glCallList(list);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glEndList(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glEndList();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_0_glNewList(xlong nativehandle, int list, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_0*)nativehandle)->glNewList(list, mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glViewport(xlong nativehandle, int x, int y, int width, int height) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glViewport(x, y, width, height);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDepthRange(xlong nativehandle, double nearVal, double farVal) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDepthRange(nearVal, farVal);
#else


#endif
}

XNLEXPORT bool XI_CDECL qfn_1_1_glIsEnabled(xlong nativehandle, int cap) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_1*)nativehandle)->glIsEnabled(cap);
#else

	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetTexLevelParameteriv(xlong nativehandle, int target, int level, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetTexLevelParameteriv(target, level, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetTexLevelParameterfv(xlong nativehandle, int target, int level, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetTexLevelParameterfv(target, level, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetTexParameteriv(xlong nativehandle, int target, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetTexParameteriv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetTexParameterfv(xlong nativehandle, int target, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetTexParameterfv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetTexImage(xlong nativehandle, int target, int level, int format, int type, xbyte  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetTexImage(target, level, format, type, pixels);
#else


#endif
}

XNLEXPORT xstring XI_CDECL qfn_1_1_glGetString(xlong nativehandle, int name) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return (xstring)((QOpenGLFunctions_1_1*)nativehandle)->glGetString(name);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetIntegerv(xlong nativehandle, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetIntegerv(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetFloatv(xlong nativehandle, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetFloatv(pname, params);
#else


#endif
}

XNLEXPORT int XI_CDECL qfn_1_1_glGetError(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_1*)nativehandle)->glGetError();
#else

	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetDoublev(xlong nativehandle, int pname, double  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetDoublev(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetBooleanv(xlong nativehandle, int pname, bool  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetBooleanv(pname, (GLboolean*)params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glReadPixels(xlong nativehandle, int x, int y, int width, int height, int format, int type, xbyte  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glReadPixels(x, y, width, height, format, type, pixels);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glReadBuffer(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glReadBuffer(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPixelStorei(xlong nativehandle, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPixelStorei(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPixelStoref(xlong nativehandle, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPixelStoref(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDepthFunc(xlong nativehandle, int func) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDepthFunc(func);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glStencilOp(xlong nativehandle, int fail, int zfail, int zpass) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glStencilOp(fail, zfail, zpass);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glStencilFunc(xlong nativehandle, int func, int ref, int mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glStencilFunc(func, ref, mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLogicOp(xlong nativehandle, int opcode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLogicOp(opcode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glBlendFunc(xlong nativehandle, int sfactor, int dfactor) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glBlendFunc(sfactor, dfactor);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glFlush(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glFlush();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glFinish(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glFinish();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEnable(xlong nativehandle, int cap) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEnable(cap);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDisable(xlong nativehandle, int cap) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDisable(cap);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDepthMask(xlong nativehandle, bool flag) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDepthMask(flag);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColorMask(xlong nativehandle, bool red, bool green, bool blue, bool alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColorMask(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glStencilMask(xlong nativehandle, int mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glStencilMask(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glClearDepth(xlong nativehandle, double depth) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glClearDepth(depth);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glClearStencil(xlong nativehandle, int s) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glClearStencil(s);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glClearColor(xlong nativehandle, float red, float green, float blue, float alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glClearColor(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glClear(xlong nativehandle, int mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glClear(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDrawBuffer(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDrawBuffer(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexImage2D(xlong nativehandle, int target, int level, int internalformat, int width, int height, int border, int format, int type, const xbyte  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexImage1D(xlong nativehandle, int target, int level, int internalformat, int width, int border, int format, int type, const xbyte  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexImage1D(target, level, internalformat, width, border, format, type, pixels);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexParameteriv(xlong nativehandle, int target, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexParameteriv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexParameteri(xlong nativehandle, int target, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexParameteri(target, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexParameterfv(xlong nativehandle, int target, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexParameterfv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexParameterf(xlong nativehandle, int target, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexParameterf(target, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glScissor(xlong nativehandle, int x, int y, int width, int height) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glScissor(x, y, width, height);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPolygonMode(xlong nativehandle, int face, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPolygonMode(face, mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPointSize(xlong nativehandle, float size) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPointSize(size);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLineWidth(xlong nativehandle, float width) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLineWidth(width);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glHint(xlong nativehandle, int target, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glHint(target, mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glFrontFace(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glFrontFace(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glCullFace(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glCullFace(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexubv(xlong nativehandle, const xbyte  * c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexubv(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexub(xlong nativehandle, xbyte c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexub(c);
#else


#endif
}

XNLEXPORT bool XI_CDECL qfn_1_1_glIsTexture(xlong nativehandle, int texture) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_1*)nativehandle)->glIsTexture(texture);
#else

	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGenTextures(xlong nativehandle, int n, int  * textures) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGenTextures(n, (GLuint*)textures);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDeleteTextures(xlong nativehandle, int n, const int  * textures) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDeleteTextures(n, (GLuint*)textures);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glBindTexture(xlong nativehandle, int target, int texture) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glBindTexture(target, texture);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexSubImage2D(xlong nativehandle, int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, const xbyte  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexSubImage1D(xlong nativehandle, int target, int level, int xoffset, int width, int format, int type, const xbyte  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glCopyTexSubImage2D(xlong nativehandle, int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glCopyTexSubImage1D(xlong nativehandle, int target, int level, int xoffset, int x, int y, int width) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glCopyTexSubImage1D(target, level, xoffset, x, y, width);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glCopyTexImage2D(xlong nativehandle, int target, int level, int internalformat, int x, int y, int width, int height, int border) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glCopyTexImage1D(xlong nativehandle, int target, int level, int internalformat, int x, int y, int width, int border) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glCopyTexImage1D(target, level, internalformat, x, y, width, border);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPolygonOffset(xlong nativehandle, float factor, float units) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPolygonOffset(factor, units);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetPointerv(xlong nativehandle, int pname, void  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetPointerv(pname, (void**)params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDrawElements(xlong nativehandle, int mode, int count, int type, const xbyte  * indices) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDrawElements(mode, count, type, indices);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDrawArrays(xlong nativehandle, int mode, int first, int count) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDrawArrays(mode, first, count);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTranslatef(xlong nativehandle, float x, float y, float z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTranslatef(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTranslated(xlong nativehandle, double x, double y, double z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTranslated(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glScalef(xlong nativehandle, float x, float y, float z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glScalef(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glScaled(xlong nativehandle, double x, double y, double z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glScaled(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRotatef(xlong nativehandle, float angle, float x, float y, float z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRotatef(angle, x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRotated(xlong nativehandle, double angle, double x, double y, double z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRotated(angle, x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPushMatrix(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPushMatrix();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPopMatrix(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPopMatrix();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glOrtho(xlong nativehandle, double left, double right, double bottom, double top, double zNear, double zFar) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glOrtho(left, right, bottom, top, zNear, zFar);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMultMatrixd(xlong nativehandle, const double  * m) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMultMatrixd(m);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMultMatrixf(xlong nativehandle, const float  * m) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMultMatrixf(m);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMatrixMode(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMatrixMode(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLoadMatrixd(xlong nativehandle, const double  * m) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLoadMatrixd(m);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLoadMatrixf(xlong nativehandle, const float  * m) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLoadMatrixf(m);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLoadIdentity(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLoadIdentity();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glFrustum(xlong nativehandle, double left, double right, double bottom, double top, double zNear, double zFar) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glFrustum(left, right, bottom, top, zNear, zFar);
#else


#endif
}

XNLEXPORT bool XI_CDECL qfn_1_1_glIsList(xlong nativehandle, int list) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_1*)nativehandle)->glIsList(list);
#else

	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetTexGeniv(xlong nativehandle, int coord, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetTexGeniv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetTexGenfv(xlong nativehandle, int coord, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetTexGenfv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetTexGendv(xlong nativehandle, int coord, int pname, double  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetTexGendv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetTexEnviv(xlong nativehandle, int target, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetTexEnviv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetTexEnvfv(xlong nativehandle, int target, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetTexEnvfv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetPolygonStipple(xlong nativehandle, xbyte  * mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetPolygonStipple(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetPixelMapusv(xlong nativehandle, int map, short  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetPixelMapusv(map, (GLushort*)values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetPixelMapuiv(xlong nativehandle, int map, int  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetPixelMapuiv(map, (GLuint*)values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetPixelMapfv(xlong nativehandle, int map, float  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetPixelMapfv(map, values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetMaterialiv(xlong nativehandle, int face, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetMaterialiv(face, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetMaterialfv(xlong nativehandle, int face, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetMaterialfv(face, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetMapiv(xlong nativehandle, int target, int query, int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetMapiv(target, query, v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetMapfv(xlong nativehandle, int target, int query, float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetMapfv(target, query, v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetMapdv(xlong nativehandle, int target, int query, double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetMapdv(target, query, v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetLightiv(xlong nativehandle, int light, int pname, int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetLightiv(light, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetLightfv(xlong nativehandle, int light, int pname, float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetLightfv(light, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glGetClipPlane(xlong nativehandle, int plane, double  * equation) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glGetClipPlane(plane, equation);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDrawPixels(xlong nativehandle, int width, int height, int format, int type, const xbyte  * pixels) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDrawPixels(width, height, format, type, pixels);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glCopyPixels(xlong nativehandle, int x, int y, int width, int height, int type) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glCopyPixels(x, y, width, height, type);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPixelMapusv(xlong nativehandle, int map, int mapsize, const short  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPixelMapusv(map, mapsize, (GLushort*)values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPixelMapuiv(xlong nativehandle, int map, int mapsize, const int  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPixelMapuiv(map, mapsize, (GLuint*)values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPixelMapfv(xlong nativehandle, int map, int mapsize, const float  * values) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPixelMapfv(map, mapsize, values);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPixelTransferi(xlong nativehandle, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPixelTransferi(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPixelTransferf(xlong nativehandle, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPixelTransferf(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPixelZoom(xlong nativehandle, float xfactor, float yfactor) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPixelZoom(xfactor, yfactor);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glAlphaFunc(xlong nativehandle, int func, float ref) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glAlphaFunc(func, ref);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalPoint2(xlong nativehandle, int i, int j) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalPoint2(i, j);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalMesh2(xlong nativehandle, int mode, int i1, int i2, int j1, int j2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalMesh2(mode, i1, i2, j1, j2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalPoint1(xlong nativehandle, int i) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalPoint1(i);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalMesh1(xlong nativehandle, int mode, int i1, int i2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalMesh1(mode, i1, i2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalCoord2fv(xlong nativehandle, const float  * u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalCoord2fv(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalCoord2f(xlong nativehandle, float u, float v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalCoord2f(u, v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalCoord2dv(xlong nativehandle, const double  * u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalCoord2dv(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalCoord2d(xlong nativehandle, double u, double v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalCoord2d(u, v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalCoord1fv(xlong nativehandle, const float  * u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalCoord1fv(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalCoord1f(xlong nativehandle, float u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalCoord1f(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalCoord1dv(xlong nativehandle, const double  * u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalCoord1dv(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEvalCoord1d(xlong nativehandle, double u) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEvalCoord1d(u);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMapGrid2f(xlong nativehandle, int un, float u1, float u2, int vn, float v1, float v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMapGrid2f(un, u1, u2, vn, v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMapGrid2d(xlong nativehandle, int un, double u1, double u2, int vn, double v1, double v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMapGrid2d(un, u1, u2, vn, v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMapGrid1f(xlong nativehandle, int un, float u1, float u2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMapGrid1f(un, u1, u2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMapGrid1d(xlong nativehandle, int un, double u1, double u2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMapGrid1d(un, u1, u2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMap2f(xlong nativehandle, int target, float u1, float u2, int ustride, int uorder, float v1, float v2, int vstride, int vorder, const float  * points) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMap2f(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMap2d(xlong nativehandle, int target, double u1, double u2, int ustride, int uorder, double v1, double v2, int vstride, int vorder, const double  * points) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMap2d(target, u1, u2, ustride, uorder, v1, v2, vstride, vorder, points);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMap1f(xlong nativehandle, int target, float u1, float u2, int stride, int order, const float  * points) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMap1f(target, u1, u2, stride, order, points);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMap1d(xlong nativehandle, int target, double u1, double u2, int stride, int order, const double  * points) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMap1d(target, u1, u2, stride, order, points);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPushAttrib(xlong nativehandle, int mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPushAttrib(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPopAttrib(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPopAttrib();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glAccum(xlong nativehandle, int op, float value) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glAccum(op, value);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexMask(xlong nativehandle, int mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexMask(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glClearIndex(xlong nativehandle, float c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glClearIndex(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glClearAccum(xlong nativehandle, float red, float green, float blue, float alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glClearAccum(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPushName(xlong nativehandle, int name) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPushName(name);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPopName(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPopName();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPassThrough(xlong nativehandle, float token) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPassThrough(token);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLoadName(xlong nativehandle, int name) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLoadName(name);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glInitNames(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glInitNames();
#else


#endif
}

XNLEXPORT int XI_CDECL qfn_1_1_glRenderMode(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_1*)nativehandle)->glRenderMode(mode);
#else

	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glSelectBuffer(xlong nativehandle, int size, int  * buffer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glSelectBuffer(size, (GLuint*)buffer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glFeedbackBuffer(xlong nativehandle, int size, int type, float  * buffer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glFeedbackBuffer(size, type, buffer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexGeniv(xlong nativehandle, int coord, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexGeniv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexGeni(xlong nativehandle, int coord, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexGeni(coord, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexGenfv(xlong nativehandle, int coord, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexGenfv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexGenf(xlong nativehandle, int coord, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexGenf(coord, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexGendv(xlong nativehandle, int coord, int pname, const double  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexGendv(coord, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexGend(xlong nativehandle, int coord, int pname, double param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexGend(coord, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexEnviv(xlong nativehandle, int target, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexEnviv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexEnvi(xlong nativehandle, int target, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexEnvi(target, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexEnvfv(xlong nativehandle, int target, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexEnvfv(target, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexEnvf(xlong nativehandle, int target, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexEnvf(target, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glShadeModel(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glShadeModel(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPolygonStipple(xlong nativehandle, const xbyte  * mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPolygonStipple(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMaterialiv(xlong nativehandle, int face, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMaterialiv(face, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMateriali(xlong nativehandle, int face, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMateriali(face, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMaterialfv(xlong nativehandle, int face, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMaterialfv(face, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glMaterialf(xlong nativehandle, int face, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glMaterialf(face, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLineStipple(xlong nativehandle, int factor, short pattern) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLineStipple(factor, pattern);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLightModeliv(xlong nativehandle, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLightModeliv(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLightModeli(xlong nativehandle, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLightModeli(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLightModelfv(xlong nativehandle, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLightModelfv(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLightModelf(xlong nativehandle, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLightModelf(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLightiv(xlong nativehandle, int light, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLightiv(light, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLighti(xlong nativehandle, int light, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLighti(light, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLightfv(xlong nativehandle, int light, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLightfv(light, pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glLightf(xlong nativehandle, int light, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glLightf(light, pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glFogiv(xlong nativehandle, int pname, const int  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glFogiv(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glFogi(xlong nativehandle, int pname, int param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glFogi(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glFogfv(xlong nativehandle, int pname, const float  * params) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glFogfv(pname, params);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glFogf(xlong nativehandle, int pname, float param) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glFogf(pname, param);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColorMaterial(xlong nativehandle, int face, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColorMaterial(face, mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glClipPlane(xlong nativehandle, int plane, const double  * equation) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glClipPlane(plane, equation);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex4sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex4sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex4s(xlong nativehandle, short x, short y, short z, short w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex4s(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex4iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex4iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex4i(xlong nativehandle, int x, int y, int z, int w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex4i(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex4fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex4fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex4f(xlong nativehandle, float x, float y, float z, float w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex4f(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex4dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex4dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex4d(xlong nativehandle, double x, double y, double z, double w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex4d(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex3sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex3sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex3s(xlong nativehandle, short x, short y, short z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex3s(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex3iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex3iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex3i(xlong nativehandle, int x, int y, int z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex3i(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex3fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex3fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex3f(xlong nativehandle, float x, float y, float z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex3f(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex3dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex3dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex3d(xlong nativehandle, double x, double y, double z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex3d(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex2sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex2sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex2s(xlong nativehandle, short x, short y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex2s(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex2iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex2iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex2i(xlong nativehandle, int x, int y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex2i(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex2fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex2fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex2f(xlong nativehandle, float x, float y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex2f(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex2dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex2dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertex2d(xlong nativehandle, double x, double y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertex2d(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord4sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord4sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord4s(xlong nativehandle, short s, short t, short r, short q) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord4s(s, t, r, q);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord4iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord4iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord4i(xlong nativehandle, int s, int t, int r, int q) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord4i(s, t, r, q);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord4fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord4fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord4f(xlong nativehandle, float s, float t, float r, float q) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord4f(s, t, r, q);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord4dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord4dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord4d(xlong nativehandle, double s, double t, double r, double q) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord4d(s, t, r, q);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord3sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord3sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord3s(xlong nativehandle, short s, short t, short r) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord3s(s, t, r);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord3iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord3iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord3i(xlong nativehandle, int s, int t, int r) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord3i(s, t, r);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord3fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord3fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord3f(xlong nativehandle, float s, float t, float r) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord3f(s, t, r);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord3dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord3dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord3d(xlong nativehandle, double s, double t, double r) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord3d(s, t, r);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord2sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord2sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord2s(xlong nativehandle, short s, short t) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord2s(s, t);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord2iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord2iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord2i(xlong nativehandle, int s, int t) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord2i(s, t);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord2fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord2fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord2f(xlong nativehandle, float s, float t) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord2f(s, t);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord2dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord2dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord2d(xlong nativehandle, double s, double t) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord2d(s, t);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord1sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord1sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord1s(xlong nativehandle, short s) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord1s(s);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord1iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord1iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord1i(xlong nativehandle, int s) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord1i(s);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord1fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord1fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord1f(xlong nativehandle, float s) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord1f(s);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord1dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord1dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoord1d(xlong nativehandle, double s) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoord1d(s);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRectsv(xlong nativehandle, const short  * v1, const short  * v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRectsv(v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRects(xlong nativehandle, short x1, short y1, short x2, short y2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRects(x1, y1, x2, y2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRectiv(xlong nativehandle, const int  * v1, const int  * v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRectiv(v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRecti(xlong nativehandle, int x1, int y1, int x2, int y2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRecti(x1, y1, x2, y2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRectfv(xlong nativehandle, const float  * v1, const float  * v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRectfv(v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRectf(xlong nativehandle, float x1, float y1, float x2, float y2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRectf(x1, y1, x2, y2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRectdv(xlong nativehandle, const double  * v1, const double  * v2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRectdv(v1, v2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRectd(xlong nativehandle, double x1, double y1, double x2, double y2) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRectd(x1, y1, x2, y2);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos4sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos4sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos4s(xlong nativehandle, short x, short y, short z, short w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos4s(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos4iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos4iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos4i(xlong nativehandle, int x, int y, int z, int w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos4i(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos4fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos4fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos4f(xlong nativehandle, float x, float y, float z, float w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos4f(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos4dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos4dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos4d(xlong nativehandle, double x, double y, double z, double w) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos4d(x, y, z, w);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos3sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos3sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos3s(xlong nativehandle, short x, short y, short z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos3s(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos3iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos3iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos3i(xlong nativehandle, int x, int y, int z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos3i(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos3fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos3fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos3f(xlong nativehandle, float x, float y, float z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos3f(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos3dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos3dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos3d(xlong nativehandle, double x, double y, double z) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos3d(x, y, z);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos2sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos2sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos2s(xlong nativehandle, short x, short y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos2s(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos2iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos2iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos2i(xlong nativehandle, int x, int y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos2i(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos2fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos2fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos2f(xlong nativehandle, float x, float y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos2f(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos2dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos2dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glRasterPos2d(xlong nativehandle, double x, double y) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glRasterPos2d(x, y);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormal3sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormal3sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormal3s(xlong nativehandle, short nx, short ny, short nz) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormal3s(nx, ny, nz);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormal3iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormal3iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormal3i(xlong nativehandle, int nx, int ny, int nz) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormal3i(nx, ny, nz);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormal3fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormal3fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormal3f(xlong nativehandle, float nx, float ny, float nz) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormal3f(nx, ny, nz);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormal3dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormal3dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormal3d(xlong nativehandle, double nx, double ny, double nz) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormal3d(nx, ny, nz);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormal3bv(xlong nativehandle, const xbyte  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormal3bv((GLbyte*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormal3b(xlong nativehandle, xbyte nx, xbyte ny, xbyte nz) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormal3b(nx, ny, nz);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexsv(xlong nativehandle, const short  * c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexsv(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexs(xlong nativehandle, short c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexs(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexiv(xlong nativehandle, const int  * c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexiv(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexi(xlong nativehandle, int c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexi(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexfv(xlong nativehandle, const float  * c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexfv(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexf(xlong nativehandle, float c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexf(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexdv(xlong nativehandle, const double  * c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexdv(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexd(xlong nativehandle, double c) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexd(c);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEnd(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEnd();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEdgeFlagv(xlong nativehandle, const bool  * flag) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEdgeFlagv((GLboolean*)flag);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEdgeFlag(xlong nativehandle, bool flag) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEdgeFlag(flag);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4usv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4usv((GLushort*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4us(xlong nativehandle, short red, short green, short blue, short alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4us(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4uiv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4uiv((GLuint*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4ui(xlong nativehandle, int red, int green, int blue, int alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4ui(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4ubv(xlong nativehandle, const xbyte  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4ubv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4ub(xlong nativehandle, xbyte red, xbyte green, xbyte blue, xbyte alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4ub(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4s(xlong nativehandle, short red, short green, short blue, short alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4s(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4i(xlong nativehandle, int red, int green, int blue, int alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4i(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4f(xlong nativehandle, float red, float green, float blue, float alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4f(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4d(xlong nativehandle, double red, double green, double blue, double alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4d(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4bv(xlong nativehandle, const xbyte  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4bv((GLbyte*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor4b(xlong nativehandle, xbyte red, xbyte green, xbyte blue, xbyte alpha) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor4b(red, green, blue, alpha);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3usv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3usv((GLushort*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3us(xlong nativehandle, short red, short green, short blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3us(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3uiv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3uiv((GLuint*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3ui(xlong nativehandle, int red, int green, int blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3ui(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3ubv(xlong nativehandle, const xbyte  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3ubv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3ub(xlong nativehandle, xbyte red, xbyte green, xbyte blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3ub(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3sv(xlong nativehandle, const short  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3sv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3s(xlong nativehandle, short red, short green, short blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3s(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3iv(xlong nativehandle, const int  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3iv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3i(xlong nativehandle, int red, int green, int blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3i(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3fv(xlong nativehandle, const float  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3fv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3f(xlong nativehandle, float red, float green, float blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3f(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3dv(xlong nativehandle, const double  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3dv(v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3d(xlong nativehandle, double red, double green, double blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3d(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3bv(xlong nativehandle, const xbyte  * v) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3bv((GLbyte*)v);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColor3b(xlong nativehandle, xbyte red, xbyte green, xbyte blue) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColor3b(red, green, blue);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glBitmap(xlong nativehandle, int width, int height, float xorig, float yorig, float xmove, float ymove, const xbyte  * bitmap) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glBitmap(width, height, xorig, yorig, xmove, ymove, bitmap);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glBegin(xlong nativehandle, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glBegin(mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glListBase(xlong nativehandle, int base) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glListBase(base);
#else


#endif
}

XNLEXPORT int XI_CDECL qfn_1_1_glGenLists(xlong nativehandle, int range) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_1*)nativehandle)->glGenLists(range);
#else

	return 0;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDeleteLists(xlong nativehandle, int list, int range) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDeleteLists(list, range);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glCallLists(xlong nativehandle, int n, int type, const xbyte  * lists) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glCallLists(n, type, lists);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glCallList(xlong nativehandle, int list) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glCallList(list);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEndList(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEndList();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNewList(xlong nativehandle, int list, int mode) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNewList(list, mode);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPushClientAttrib(xlong nativehandle, int mask) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPushClientAttrib(mask);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPopClientAttrib(xlong nativehandle) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPopClientAttrib();
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glPrioritizeTextures(xlong nativehandle, int n, const int  * textures, const float  * priorities) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glPrioritizeTextures(n, (GLuint*)textures, priorities);
#else


#endif
}

XNLEXPORT bool XI_CDECL qfn_1_1_glAreTexturesResident(xlong nativehandle, int n, const int  * textures, bool  * residences) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	return ((QOpenGLFunctions_1_1*)nativehandle)->glAreTexturesResident(n, (GLuint*)textures, (GLboolean*)residences);
#else

	return false;
#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glVertexPointer(xlong nativehandle, int size, int type, int stride, const xbyte  * pointer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glVertexPointer(size, type, stride, pointer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glTexCoordPointer(xlong nativehandle, int size, int type, int stride, const xbyte  * pointer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glTexCoordPointer(size, type, stride, pointer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glNormalPointer(xlong nativehandle, int type, int stride, const xbyte  * pointer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glNormalPointer(type, stride, pointer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glInterleavedArrays(xlong nativehandle, int format, int stride, const xbyte  * pointer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glInterleavedArrays(format, stride, pointer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glIndexPointer(xlong nativehandle, int type, int stride, const xbyte  * pointer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glIndexPointer(type, stride, pointer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEnableClientState(xlong nativehandle, int array) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEnableClientState(array);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glEdgeFlagPointer(xlong nativehandle, int stride, const xbyte  * pointer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glEdgeFlagPointer(stride, pointer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glDisableClientState(xlong nativehandle, int array) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glDisableClientState(array);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glColorPointer(xlong nativehandle, int size, int type, int stride, const xbyte  * pointer) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glColorPointer(size, type, stride, pointer);
#else


#endif
}

XNLEXPORT void XI_CDECL qfn_1_1_glArrayElement(xlong nativehandle, int i) {
#if !defined(QT_NO_OPENGL) && !defined(QT_OPENGL_ES_2)
	((QOpenGLFunctions_1_1*)nativehandle)->glArrayElement(i);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glActiveTexture(xlong nativehandle, int texture) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glActiveTexture(texture);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glAttachShader(xlong nativehandle, int program, int shader) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glAttachShader(program, shader);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBindAttribLocation(xlong nativehandle, int program, int index, xstring  name) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glBindAttribLocation(program, index, name);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBindBuffer(xlong nativehandle, int target, int buffer) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glBindBuffer(target, buffer);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBindFramebuffer(xlong nativehandle, int target, int framebuffer) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glBindFramebuffer(target, framebuffer);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBindRenderbuffer(xlong nativehandle, int target, int renderbuffer) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glBindRenderbuffer(target, renderbuffer);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBindTexture(xlong nativehandle, int target, int texture) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glBindTexture(target, texture);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBlendColor(xlong nativehandle, float red, float green, float blue, float alpha) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glBlendColor(red, green, blue, alpha);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBlendEquation(xlong nativehandle, int mode) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glBlendEquation(mode);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBlendEquationSeparate(xlong nativehandle, int modeRGB, int modeAlpha) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glBlendEquationSeparate(modeRGB, modeAlpha);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBlendFunc(xlong nativehandle, int sfactor, int dfactor) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glBlendFunc(sfactor, dfactor);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBlendFuncSeparate(xlong nativehandle, int srcRGB, int dstRGB, int srcAlpha, int dstAlpha) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBufferData(xlong nativehandle, int target, int* size, const xbyte *  data, int usage) {
#ifdef QT_OPENGL_ES_2
	size_t isize = *size;
    ((QOpenGLFunctions_ES2*)nativehandle)->glBufferData(target, (GLsizeiptr)&isize, data, usage);
     *size = isize;
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glBufferSubData(xlong nativehandle, int target, int* offset, int* size, const xbyte *  data) {
#ifdef QT_OPENGL_ES_2
    size_t isize = *size;
	((QOpenGLFunctions_ES2*)nativehandle)->glBufferSubData(target, (GLintptr)offset, (GLsizeiptr)&isize, data);
	*size = isize;
#else


#endif
}


XNLEXPORT int XI_CDECL qfn_ES2_glCheckFramebufferStatus(xlong nativehandle, int target) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glCheckFramebufferStatus(target);
#else

	return 0;
#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glClear(xlong nativehandle, int mask) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glClear(mask);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glClearColor(xlong nativehandle, float red, float green, float blue, float alpha) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glClearColor(red, green, blue, alpha);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glClearDepthf(xlong nativehandle, float depth) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glClearDepthf(depth);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glClearStencil(xlong nativehandle, int s) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glClearStencil(s);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glColorMask(xlong nativehandle, bool red, bool green, bool blue, bool alpha) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glColorMask(red, green, blue, alpha);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glCompileShader(xlong nativehandle, int shader) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glCompileShader(shader);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glCompressedTexImage2D(xlong nativehandle, int target, int level, int internalformat, int width, int height, int border, int imageSize, const xbyte *  data) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glCompressedTexSubImage2D(xlong nativehandle, int target, int level, int xoffset, int yoffset, int width, int height, int format, int imageSize, const xbyte *  data) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glCopyTexImage2D(xlong nativehandle, int target, int level, int internalformat, int x, int y, int width, int height, int border) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glCopyTexSubImage2D(xlong nativehandle, int target, int level, int xoffset, int yoffset, int x, int y, int width, int height) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
#else


#endif
}


XNLEXPORT int XI_CDECL qfn_ES2_glCreateProgram(xlong nativehandle) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glCreateProgram();
#else

	return 0;
#endif
}


XNLEXPORT int XI_CDECL qfn_ES2_glCreateShader(xlong nativehandle, int type) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glCreateShader(type);
#else

	return 0;
#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glCullFace(xlong nativehandle, int mode) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glCullFace(mode);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDeleteBuffers(xlong nativehandle, int n, const int *  buffers) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDeleteBuffers(n, (GLuint*)buffers);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDeleteFramebuffers(xlong nativehandle, int n, const int *  framebuffers) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDeleteFramebuffers(n, (GLuint*)framebuffers);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDeleteProgram(xlong nativehandle, int program) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDeleteProgram(program);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDeleteRenderbuffers(xlong nativehandle, int n, const int *  renderbuffers) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDeleteRenderbuffers(n, (GLuint*)renderbuffers);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDeleteShader(xlong nativehandle, int shader) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDeleteShader(shader);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDeleteTextures(xlong nativehandle, int n, const int *  textures) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDeleteTextures(n, (GLuint*)textures);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDepthFunc(xlong nativehandle, int func) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDepthFunc(func);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDepthMask(xlong nativehandle, bool flag) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDepthMask(flag);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDepthRangef(xlong nativehandle, float zNear, float zFar) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDepthRangef(zNear, zFar);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDetachShader(xlong nativehandle, int program, int shader) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDetachShader(program, shader);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDisable(xlong nativehandle, int cap) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDisable(cap);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDisableVertexAttribArray(xlong nativehandle, int index) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDisableVertexAttribArray(index);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDrawArrays(xlong nativehandle, int mode, int first, int count) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDrawArrays(mode, first, count);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glDrawElements(xlong nativehandle, int mode, int count, int type, const xbyte *  indices) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glDrawElements(mode, count, type, indices);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glEnable(xlong nativehandle, int cap) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glEnable(cap);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glEnableVertexAttribArray(xlong nativehandle, int index) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glEnableVertexAttribArray(index);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glFinish(xlong nativehandle) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glFinish();
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glFlush(xlong nativehandle) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glFlush();
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glFramebufferRenderbuffer(xlong nativehandle, int target, int attachment, int renderbuffertarget, int renderbuffer) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glFramebufferTexture2D(xlong nativehandle, int target, int attachment, int textarget, int texture, int level) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glFramebufferTexture2D(target, attachment, textarget, texture, level);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glFrontFace(xlong nativehandle, int mode) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glFrontFace(mode);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGenBuffers(xlong nativehandle, int n, int *  buffers) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGenBuffers(n, (GLuint*)buffers);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGenerateMipmap(xlong nativehandle, int target) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGenerateMipmap(target);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGenFramebuffers(xlong nativehandle, int n, int *  framebuffers) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGenFramebuffers(n, (GLuint*)framebuffers);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGenRenderbuffers(xlong nativehandle, int n, int *  renderbuffers) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGenRenderbuffers(n, (GLuint*)renderbuffers);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGenTextures(xlong nativehandle, int n, int *  textures) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGenTextures(n, (GLuint*)textures);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetActiveAttrib(xlong nativehandle, int program, int index, int bufsize, int *  length, int *  size, int *  type, xbyte *  name) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGetActiveAttrib(program, index, bufsize, length, size, (GLenum*)type, (GLchar*)name);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetActiveUniform(xlong nativehandle, int program, int index, int bufsize, int *  length, int *  size, int *  type, xbyte *  name) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGetActiveUniform(program, index, bufsize, length, size, (GLenum*)type, (GLchar*)name);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetAttachedShaders(xlong nativehandle, int program, int maxcount, int *  count, int *  shaders) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGetAttachedShaders(program, maxcount, count, (GLuint*)shaders);
#else


#endif
}


XNLEXPORT int XI_CDECL qfn_ES2_glGetAttribLocation(xlong nativehandle, int program, const xbyte *  name) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGetAttribLocation(program, (GLchar*)name);
#else

	return 0;
#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetBooleanv(xlong nativehandle, int pname, bool *  params) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGetBooleanv(pname, (GLboolean*)params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetBufferParameteriv(xlong nativehandle, int target, int pname, int *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetBufferParameteriv(target, pname, params);
#else


#endif
}


XNLEXPORT int XI_CDECL qfn_ES2_glGetError(xlong nativehandle) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetError();
#else

	return 0;
#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetFloatv(xlong nativehandle, int pname, float *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetFloatv(pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetFramebufferAttachmentParameteriv(xlong nativehandle, int target, int attachment, int pname, int *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetIntegerv(xlong nativehandle, int pname, int *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetIntegerv(pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetProgramiv(xlong nativehandle, int program, int pname, int *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetProgramiv(program, pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetProgramInfoLog(xlong nativehandle, int program, int bufsize, int *  length, xbyte *  infolog) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGetProgramInfoLog(program, bufsize, length, (GLchar*)infolog);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetRenderbufferParameteriv(xlong nativehandle, int target, int pname, int *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetRenderbufferParameteriv(target, pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetShaderiv(xlong nativehandle, int shader, int pname, int *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetShaderiv(shader, pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetShaderInfoLog(xlong nativehandle, int shader, int bufsize, int *  length, xbyte *  infolog) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGetShaderInfoLog(shader, bufsize, length, (GLchar*)infolog);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetShaderPrecisionFormat(xlong nativehandle, int shadertype, int precisiontype, int *  range, int *  precision) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetShaderSource(xlong nativehandle, int shader, int bufsize, int *  length, xbyte *  source) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGetShaderSource(shader, bufsize, length, (GLchar*)source);
#else


#endif
}


XNLEXPORT xstring XI_CDECL qfn_ES2_glGetString(xlong nativehandle, int name) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetString(name);
#else

	return 0;
#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetTexParameterfv(xlong nativehandle, int target, int pname, float *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetTexParameterfv(target, pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetTexParameteriv(xlong nativehandle, int target, int pname, int *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetTexParameteriv(target, pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetUniformfv(xlong nativehandle, int program, int location, float *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetUniformfv(program, location, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetUniformiv(xlong nativehandle, int program, int location, int *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetUniformiv(program, location, params);
#else


#endif
}


XNLEXPORT int XI_CDECL qfn_ES2_glGetUniformLocation(xlong nativehandle, int program, xstring  name) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glGetUniformLocation(program, (GLchar*)name);
#else

	return 0;
#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetVertexAttribfv(xlong nativehandle, int index, int pname, float *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetVertexAttribfv(index, pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetVertexAttribiv(xlong nativehandle, int index, int pname, int *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetVertexAttribiv(index, pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glGetVertexAttribPointerv(xlong nativehandle, int index, int pname, void**  pointer) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glGetVertexAttribPointerv(index, pname, pointer);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glHint(xlong nativehandle, int target, int mode) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glHint(target, mode);
#else


#endif
}


XNLEXPORT bool XI_CDECL qfn_ES2_glIsBuffer(xlong nativehandle, int buffer) {
#ifdef QT_OPENGL_ES_2
	return ((QOpenGLFunctions_ES2*)nativehandle)->glIsBuffer(buffer);
#else

	return false;
#endif
}


XNLEXPORT bool XI_CDECL qfn_ES2_glIsEnabled(xlong nativehandle, int cap) {
#ifdef QT_OPENGL_ES_2
	return ((QOpenGLFunctions_ES2*)nativehandle)->glIsEnabled(cap);
#else

	return false;
#endif
}


XNLEXPORT bool XI_CDECL qfn_ES2_glIsFramebuffer(xlong nativehandle, int framebuffer) {
#ifdef QT_OPENGL_ES_2
	return ((QOpenGLFunctions_ES2*)nativehandle)->glIsFramebuffer(framebuffer);
#else

	return false;
#endif
}


XNLEXPORT bool XI_CDECL qfn_ES2_glIsProgram(xlong nativehandle, int program) {
#ifdef QT_OPENGL_ES_2
	return ((QOpenGLFunctions_ES2*)nativehandle)->glIsProgram(program);
#else

	return false;
#endif
}


XNLEXPORT bool XI_CDECL qfn_ES2_glIsRenderbuffer(xlong nativehandle, int renderbuffer) {
#ifdef QT_OPENGL_ES_2
	return ((QOpenGLFunctions_ES2*)nativehandle)->glIsRenderbuffer(renderbuffer);
#else

	return false;
#endif
}


XNLEXPORT bool XI_CDECL qfn_ES2_glIsShader(xlong nativehandle, int shader) {
#ifdef QT_OPENGL_ES_2
	return ((QOpenGLFunctions_ES2*)nativehandle)->glIsShader(shader);
#else

	return false;
#endif
}


XNLEXPORT bool XI_CDECL qfn_ES2_glIsTexture(xlong nativehandle, int texture) {
#ifdef QT_OPENGL_ES_2
	return ((QOpenGLFunctions_ES2*)nativehandle)->glIsTexture(texture);
#else

	return false;
#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glLineWidth(xlong nativehandle, float width) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glLineWidth(width);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glLinkProgram(xlong nativehandle, int program) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glLinkProgram(program);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glPixelStorei(xlong nativehandle, int pname, int param) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glPixelStorei(pname, param);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glPolygonOffset(xlong nativehandle, float factor, float units) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glPolygonOffset(factor, units);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glReadPixels(xlong nativehandle, int x, int y, int width, int height, int format, int type, xbyte *  pixels) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glReadPixels(x, y, width, height, format, type, pixels);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glReleaseShaderCompiler(xlong nativehandle) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glReleaseShaderCompiler();
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glRenderbufferStorage(xlong nativehandle, int target, int internalformat, int width, int height) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glRenderbufferStorage(target, internalformat, width, height);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glSampleCoverage(xlong nativehandle, float value, bool invert) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glSampleCoverage(value, invert);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glScissor(xlong nativehandle, int x, int y, int width, int height) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glScissor(x, y, width, height);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glShaderBinary(xlong nativehandle, int n, const int *  shaders, int binaryformat, const xbyte *  binary, int length) {
#ifdef QT_OPENGL_ES_2
    ((QOpenGLFunctions_ES2*)nativehandle)->glShaderBinary(n, (GLuint*)shaders, binaryformat, binary, length);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glShaderSource(xlong nativehandle, int shader, int count, xstring string, const int *  length) {
#ifdef QT_OPENGL_ES_2
	const GLchar * fa [] = { (const GLchar *)string };
    ((QOpenGLFunctions_ES2*)nativehandle)->glShaderSource(shader, count, &fa[0], length);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glStencilFunc(xlong nativehandle, int func, int ref, int mask) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glStencilFunc(func, ref, mask);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glStencilFuncSeparate(xlong nativehandle, int face, int func, int ref, int mask) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glStencilFuncSeparate(face, func, ref, mask);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glStencilMask(xlong nativehandle, int mask) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glStencilMask(mask);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glStencilMaskSeparate(xlong nativehandle, int face, int mask) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glStencilMaskSeparate(face, mask);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glStencilOp(xlong nativehandle, int fail, int zfail, int zpass) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glStencilOp(fail, zfail, zpass);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glStencilOpSeparate(xlong nativehandle, int face, int fail, int zfail, int zpass) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glStencilOpSeparate(face, fail, zfail, zpass);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glTexImage2D(xlong nativehandle, int target, int level, int internalformat, int width, int height, int border, int format, int type, const xbyte *  pixels) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glTexParameterf(xlong nativehandle, int target, int pname, float param) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glTexParameterf(target, pname, param);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glTexParameterfv(xlong nativehandle, int target, int pname, const float *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glTexParameterfv(target, pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glTexParameteri(xlong nativehandle, int target, int pname, int param) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glTexParameteri(target, pname, param);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glTexParameteriv(xlong nativehandle, int target, int pname, const int *  params) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glTexParameteriv(target, pname, params);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glTexSubImage2D(xlong nativehandle, int target, int level, int xoffset, int yoffset, int width, int height, int format, int type, const xbyte *  pixels) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform1f(xlong nativehandle, int location, float x) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform1f(location, x);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform1fv(xlong nativehandle, int location, int count, const float *  v) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform1fv(location, count, v);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform1i(xlong nativehandle, int location, int x) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform1i(location, x);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform1iv(xlong nativehandle, int location, int count, const int *  v) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform1iv(location, count, v);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform2f(xlong nativehandle, int location, float x, float y) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform2f(location, x, y);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform2fv(xlong nativehandle, int location, int count, const float *  v) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform2fv(location, count, v);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform2i(xlong nativehandle, int location, int x, int y) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform2i(location, x, y);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform2iv(xlong nativehandle, int location, int count, const int *  v) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform2iv(location, count, v);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform3f(xlong nativehandle, int location, float x, float y, float z) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform3f(location, x, y, z);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform3fv(xlong nativehandle, int location, int count, const float *  v) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform3fv(location, count, v);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform3i(xlong nativehandle, int location, int x, int y, int z) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform3i(location, x, y, z);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform3iv(xlong nativehandle, int location, int count, const int *  v) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform3iv(location, count, v);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform4f(xlong nativehandle, int location, float x, float y, float z, float w) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform4f(location, x, y, z, w);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform4fv(xlong nativehandle, int location, int count, const float *  v) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform4fv(location, count, v);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform4i(xlong nativehandle, int location, int x, int y, int z, int w) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform4i(location, x, y, z, w);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniform4iv(xlong nativehandle, int location, int count, const int *  v) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniform4iv(location, count, v);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniformMatrix2fv(xlong nativehandle, int location, int count, bool transpose, const float *  value) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniformMatrix2fv(location, count, transpose, value);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniformMatrix3fv(xlong nativehandle, int location, int count, bool transpose, const float *  value) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniformMatrix3fv(location, count, transpose, value);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUniformMatrix4fv(xlong nativehandle, int location, int count, bool transpose, const float *  value) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUniformMatrix4fv(location, count, transpose, value);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glUseProgram(xlong nativehandle, int program) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glUseProgram(program);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glValidateProgram(xlong nativehandle, int program) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glValidateProgram(program);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glVertexAttrib1f(xlong nativehandle, int indx, float x) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glVertexAttrib1f(indx, x);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glVertexAttrib1fv(xlong nativehandle, int indx, const float *  values) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glVertexAttrib1fv(indx, values);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glVertexAttrib2f(xlong nativehandle, int indx, float x, float y) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glVertexAttrib2f(indx, x, y);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glVertexAttrib2fv(xlong nativehandle, int indx, const float *  values) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glVertexAttrib2fv(indx, values);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glVertexAttrib3f(xlong nativehandle, int indx, float x, float y, float z) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glVertexAttrib3f(indx, x, y, z);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glVertexAttrib3fv(xlong nativehandle, int indx, const float *  values) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glVertexAttrib3fv(indx, values);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glVertexAttrib4f(xlong nativehandle, int indx, float x, float y, float z, float w) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glVertexAttrib4f(indx, x, y, z, w);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glVertexAttrib4fv(xlong nativehandle, int indx, const float *  values) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glVertexAttrib4fv(indx, values);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glVertexAttribPointer(xlong nativehandle, int indx, int size, int type, bool normalized, int stride, const xbyte *  ptr) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glVertexAttribPointer(indx, size, type, normalized, stride, ptr);
#else


#endif
}


XNLEXPORT void XI_CDECL qfn_ES2_glViewport(xlong nativehandle, int x, int y, int width, int height) {
#ifdef QT_OPENGL_ES_2
	((QOpenGLFunctions_ES2*)nativehandle)->glViewport(x, y, width, height);
#else


#endif
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
	if (strcmp(name, "createQSObject") == 0) return (void*)& createQSObject;
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
	if (strcmp(name, "long_int4") == 0) return (void*)& long_int4;
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
	if (strcmp(name, "long_object_string_int") == 0) return (void*)& long_object_string_int;
    if (strcmp(name, "pointer_intlong2") == 0) return (void*)& pointer_intlong2;
    if (strcmp(name, "createPObject") == 0) return (void*)& createPObject;
    if (strcmp(name, "createQPObject") == 0) return (void*)& createQPObject;

	if (strcmp(name, "qfn_glBindTexture") == 0) return (void*)& qfn_glBindTexture;
	if (strcmp(name, "qfn_glBlendFunc") == 0) return (void*)& qfn_glBlendFunc;
	if (strcmp(name, "qfn_glClear") == 0) return (void*)& qfn_glClear;
	if (strcmp(name, "qfn_glClearColor") == 0) return (void*)& qfn_glClearColor;
	if (strcmp(name, "qfn_glClearStencil") == 0) return (void*)& qfn_glClearStencil;
	if (strcmp(name, "qfn_glColorMask") == 0) return (void*)& qfn_glColorMask;
	if (strcmp(name, "qfn_glCopyTexImage2D") == 0) return (void*)& qfn_glCopyTexImage2D;
	if (strcmp(name, "qfn_glCopyTexSubImage2D") == 0) return (void*)& qfn_glCopyTexSubImage2D;
	if (strcmp(name, "qfn_glCullFace") == 0) return (void*)& qfn_glCullFace;
	if (strcmp(name, "qfn_glDeleteTextures") == 0) return (void*)& qfn_glDeleteTextures;
	if (strcmp(name, "qfn_glDepthFunc") == 0) return (void*)& qfn_glDepthFunc;
	if (strcmp(name, "qfn_glDepthMask") == 0) return (void*)& qfn_glDepthMask;
	if (strcmp(name, "qfn_glDisable") == 0) return (void*)& qfn_glDisable;
	if (strcmp(name, "qfn_glDrawArrays") == 0) return (void*)& qfn_glDrawArrays;
	if (strcmp(name, "qfn_glDrawElements") == 0) return (void*)& qfn_glDrawElements;
	if (strcmp(name, "qfn_glEnable") == 0) return (void*)& qfn_glEnable;
	if (strcmp(name, "qfn_glFinish") == 0) return (void*)& qfn_glFinish;
	if (strcmp(name, "qfn_glFlush") == 0) return (void*)& qfn_glFlush;
	if (strcmp(name, "qfn_glFrontFace") == 0) return (void*)& qfn_glFrontFace;
	if (strcmp(name, "qfn_glGenTextures") == 0) return (void*)& qfn_glGenTextures;
	if (strcmp(name, "qfn_glGetBooleanv") == 0) return (void*)& qfn_glGetBooleanv;
	if (strcmp(name, "qfn_glGetError") == 0) return (void*)& qfn_glGetError;
	if (strcmp(name, "qfn_glGetFloatv") == 0) return (void*)& qfn_glGetFloatv;
	if (strcmp(name, "qfn_glGetIntegerv") == 0) return (void*)& qfn_glGetIntegerv;
	if (strcmp(name, "qfn_glGetString") == 0) return (void*)& qfn_glGetString;
	if (strcmp(name, "qfn_glGetTexParameterfv") == 0) return (void*)& qfn_glGetTexParameterfv;
	if (strcmp(name, "qfn_glGetTexParameteriv") == 0) return (void*)& qfn_glGetTexParameteriv;
	if (strcmp(name, "qfn_glHint") == 0) return (void*)& qfn_glHint;
	if (strcmp(name, "qfn_glIsEnabled") == 0) return (void*)& qfn_glIsEnabled;
	if (strcmp(name, "qfn_glIsTexture") == 0) return (void*)& qfn_glIsTexture;
	if (strcmp(name, "qfn_glLineWidth") == 0) return (void*)& qfn_glLineWidth;
	if (strcmp(name, "qfn_glPixelStorei") == 0) return (void*)& qfn_glPixelStorei;
	if (strcmp(name, "qfn_glPolygonOffset") == 0) return (void*)& qfn_glPolygonOffset;
	if (strcmp(name, "qfn_glReadPixels") == 0) return (void*)& qfn_glReadPixels;
	if (strcmp(name, "qfn_glScissor") == 0) return (void*)& qfn_glScissor;
	if (strcmp(name, "qfn_glStencilFunc") == 0) return (void*)& qfn_glStencilFunc;
	if (strcmp(name, "qfn_glStencilMask") == 0) return (void*)& qfn_glStencilMask;
	if (strcmp(name, "qfn_glStencilOp") == 0) return (void*)& qfn_glStencilOp;
	if (strcmp(name, "qfn_glTexImage2D") == 0) return (void*)& qfn_glTexImage2D;
	if (strcmp(name, "qfn_glTexParameterf") == 0) return (void*)& qfn_glTexParameterf;
	if (strcmp(name, "qfn_glTexParameterfv") == 0) return (void*)& qfn_glTexParameterfv;
	if (strcmp(name, "qfn_glTexParameteri") == 0) return (void*)& qfn_glTexParameteri;
	if (strcmp(name, "qfn_glTexParameteriv") == 0) return (void*)& qfn_glTexParameteriv;
	if (strcmp(name, "qfn_glTexSubImage2D") == 0) return (void*)& qfn_glTexSubImage2D;
	if (strcmp(name, "qfn_glViewport") == 0) return (void*)& qfn_glViewport;
	if (strcmp(name, "qfn_glActiveTexture") == 0) return (void*)& qfn_glActiveTexture;
	if (strcmp(name, "qfn_glAttachShader") == 0) return (void*)& qfn_glAttachShader;
	if (strcmp(name, "qfn_glBindAttribLocation") == 0) return (void*)& qfn_glBindAttribLocation;
	if (strcmp(name, "qfn_glBindBuffer") == 0) return (void*)& qfn_glBindBuffer;
	if (strcmp(name, "qfn_glBindFramebuffer") == 0) return (void*)& qfn_glBindFramebuffer;
	if (strcmp(name, "qfn_glBindRenderbuffer") == 0) return (void*)& qfn_glBindRenderbuffer;
	if (strcmp(name, "qfn_glBlendColor") == 0) return (void*)& qfn_glBlendColor;
	if (strcmp(name, "qfn_glBlendEquation") == 0) return (void*)& qfn_glBlendEquation;
	if (strcmp(name, "qfn_glBlendEquationSeparate") == 0) return (void*)& qfn_glBlendEquationSeparate;
	if (strcmp(name, "qfn_glBlendFuncSeparate") == 0) return (void*)& qfn_glBlendFuncSeparate;
	if (strcmp(name, "qfn_glBufferData") == 0) return (void*)& qfn_glBufferData;
	if (strcmp(name, "qfn_glBufferSubData") == 0) return (void*)& qfn_glBufferSubData;
	if (strcmp(name, "qfn_glCheckFramebufferStatus") == 0) return (void*)& qfn_glCheckFramebufferStatus;
	if (strcmp(name, "qfn_glClearDepthf") == 0) return (void*)& qfn_glClearDepthf;
	if (strcmp(name, "qfn_glCompileShader") == 0) return (void*)& qfn_glCompileShader;
	if (strcmp(name, "qfn_glCompressedTexImage2D") == 0) return (void*)& qfn_glCompressedTexImage2D;
	if (strcmp(name, "qfn_glCompressedTexSubImage2D") == 0) return (void*)& qfn_glCompressedTexSubImage2D;
	if (strcmp(name, "qfn_glCreateProgram") == 0) return (void*)& qfn_glCreateProgram;
	if (strcmp(name, "qfn_glCreateShader") == 0) return (void*)& qfn_glCreateShader;
	if (strcmp(name, "qfn_glDeleteBuffers") == 0) return (void*)& qfn_glDeleteBuffers;
	if (strcmp(name, "qfn_glDeleteFramebuffers") == 0) return (void*)& qfn_glDeleteFramebuffers;
	if (strcmp(name, "qfn_glDeleteProgram") == 0) return (void*)& qfn_glDeleteProgram;
	if (strcmp(name, "qfn_glDeleteRenderbuffers") == 0) return (void*)& qfn_glDeleteRenderbuffers;
	if (strcmp(name, "qfn_glDeleteShader") == 0) return (void*)& qfn_glDeleteShader;
	if (strcmp(name, "qfn_glDepthRangef") == 0) return (void*)& qfn_glDepthRangef;
	if (strcmp(name, "qfn_glDetachShader") == 0) return (void*)& qfn_glDetachShader;
	if (strcmp(name, "qfn_glDisableVertexAttribArray") == 0) return (void*)& qfn_glDisableVertexAttribArray;
	if (strcmp(name, "qfn_glEnableVertexAttribArray") == 0) return (void*)& qfn_glEnableVertexAttribArray;
	if (strcmp(name, "qfn_glFramebufferRenderbuffer") == 0) return (void*)& qfn_glFramebufferRenderbuffer;
	if (strcmp(name, "qfn_glFramebufferTexture2D") == 0) return (void*)& qfn_glFramebufferTexture2D;
	if (strcmp(name, "qfn_glGenBuffers") == 0) return (void*)& qfn_glGenBuffers;
	if (strcmp(name, "qfn_glGenerateMipmap") == 0) return (void*)& qfn_glGenerateMipmap;
	if (strcmp(name, "qfn_glGenFramebuffers") == 0) return (void*)& qfn_glGenFramebuffers;
	if (strcmp(name, "qfn_glGenRenderbuffers") == 0) return (void*)& qfn_glGenRenderbuffers;
	if (strcmp(name, "qfn_glGetActiveAttrib") == 0) return (void*)& qfn_glGetActiveAttrib;
	if (strcmp(name, "qfn_glGetActiveUniform") == 0) return (void*)& qfn_glGetActiveUniform;
	if (strcmp(name, "qfn_glGetAttachedShaders") == 0) return (void*)& qfn_glGetAttachedShaders;
	if (strcmp(name, "qfn_glGetAttribLocation") == 0) return (void*)& qfn_glGetAttribLocation;
	if (strcmp(name, "qfn_glGetBufferParameteriv") == 0) return (void*)& qfn_glGetBufferParameteriv;
	if (strcmp(name, "qfn_glGetFramebufferAttachmentParameteriv") == 0) return (void*)& qfn_glGetFramebufferAttachmentParameteriv;
	if (strcmp(name, "qfn_glGetProgramiv") == 0) return (void*)& qfn_glGetProgramiv;
	if (strcmp(name, "qfn_glGetProgramInfoLog") == 0) return (void*)& qfn_glGetProgramInfoLog;
	if (strcmp(name, "qfn_glGetRenderbufferParameteriv") == 0) return (void*)& qfn_glGetRenderbufferParameteriv;
	if (strcmp(name, "qfn_glGetShaderiv") == 0) return (void*)& qfn_glGetShaderiv;
	if (strcmp(name, "qfn_glGetShaderInfoLog") == 0) return (void*)& qfn_glGetShaderInfoLog;
	if (strcmp(name, "qfn_glGetShaderPrecisionFormat") == 0) return (void*)& qfn_glGetShaderPrecisionFormat;
	if (strcmp(name, "qfn_glGetShaderSource") == 0) return (void*)& qfn_glGetShaderSource;
	if (strcmp(name, "qfn_glGetUniformfv") == 0) return (void*)& qfn_glGetUniformfv;
	if (strcmp(name, "qfn_glGetUniformiv") == 0) return (void*)& qfn_glGetUniformiv;
	if (strcmp(name, "qfn_glGetUniformLocation") == 0) return (void*)& qfn_glGetUniformLocation;
	if (strcmp(name, "qfn_glGetVertexAttribfv") == 0) return (void*)& qfn_glGetVertexAttribfv;
	if (strcmp(name, "qfn_glGetVertexAttribiv") == 0) return (void*)& qfn_glGetVertexAttribiv;
	if (strcmp(name, "qfn_glGetVertexAttribPointerv") == 0) return (void*)& qfn_glGetVertexAttribPointerv;
	if (strcmp(name, "qfn_glIsBuffer") == 0) return (void*)& qfn_glIsBuffer;
	if (strcmp(name, "qfn_glIsFramebuffer") == 0) return (void*)& qfn_glIsFramebuffer;
	if (strcmp(name, "qfn_glIsProgram") == 0) return (void*)& qfn_glIsProgram;
	if (strcmp(name, "qfn_glIsRenderbuffer") == 0) return (void*)& qfn_glIsRenderbuffer;
	if (strcmp(name, "qfn_glIsShader") == 0) return (void*)& qfn_glIsShader;
	if (strcmp(name, "qfn_glLinkProgram") == 0) return (void*)& qfn_glLinkProgram;
	if (strcmp(name, "qfn_glReleaseShaderCompiler") == 0) return (void*)& qfn_glReleaseShaderCompiler;
	if (strcmp(name, "qfn_glRenderbufferStorage") == 0) return (void*)& qfn_glRenderbufferStorage;
	if (strcmp(name, "qfn_glSampleCoverage") == 0) return (void*)& qfn_glSampleCoverage;
	if (strcmp(name, "qfn_glShaderBinary") == 0) return (void*)& qfn_glShaderBinary;
	if (strcmp(name, "qfn_glShaderSource") == 0) return (void*)& qfn_glShaderSource;
	if (strcmp(name, "qfn_glStencilFuncSeparate") == 0) return (void*)& qfn_glStencilFuncSeparate;
	if (strcmp(name, "qfn_glStencilMaskSeparate") == 0) return (void*)& qfn_glStencilMaskSeparate;
	if (strcmp(name, "qfn_glStencilOpSeparate") == 0) return (void*)& qfn_glStencilOpSeparate;
	if (strcmp(name, "qfn_glUniform1f") == 0) return (void*)& qfn_glUniform1f;
	if (strcmp(name, "qfn_glUniform1fv") == 0) return (void*)& qfn_glUniform1fv;
	if (strcmp(name, "qfn_glUniform1i") == 0) return (void*)& qfn_glUniform1i;
	if (strcmp(name, "qfn_glUniform1iv") == 0) return (void*)& qfn_glUniform1iv;
	if (strcmp(name, "qfn_glUniform2f") == 0) return (void*)& qfn_glUniform2f;
	if (strcmp(name, "qfn_glUniform2fv") == 0) return (void*)& qfn_glUniform2fv;
	if (strcmp(name, "qfn_glUniform2i") == 0) return (void*)& qfn_glUniform2i;
	if (strcmp(name, "qfn_glUniform2iv") == 0) return (void*)& qfn_glUniform2iv;
	if (strcmp(name, "qfn_glUniform3f") == 0) return (void*)& qfn_glUniform3f;
	if (strcmp(name, "qfn_glUniform3fv") == 0) return (void*)& qfn_glUniform3fv;
	if (strcmp(name, "qfn_glUniform3i") == 0) return (void*)& qfn_glUniform3i;
	if (strcmp(name, "qfn_glUniform3iv") == 0) return (void*)& qfn_glUniform3iv;
	if (strcmp(name, "qfn_glUniform4f") == 0) return (void*)& qfn_glUniform4f;
	if (strcmp(name, "qfn_glUniform4fv") == 0) return (void*)& qfn_glUniform4fv;
	if (strcmp(name, "qfn_glUniform4i") == 0) return (void*)& qfn_glUniform4i;
	if (strcmp(name, "qfn_glUniform4iv") == 0) return (void*)& qfn_glUniform4iv;
	if (strcmp(name, "qfn_glUniformMatrix2fv") == 0) return (void*)& qfn_glUniformMatrix2fv;
	if (strcmp(name, "qfn_glUniformMatrix3fv") == 0) return (void*)& qfn_glUniformMatrix3fv;
	if (strcmp(name, "qfn_glUniformMatrix4fv") == 0) return (void*)& qfn_glUniformMatrix4fv;
	if (strcmp(name, "qfn_glUseProgram") == 0) return (void*)& qfn_glUseProgram;
	if (strcmp(name, "qfn_glValidateProgram") == 0) return (void*)& qfn_glValidateProgram;
	if (strcmp(name, "qfn_glVertexAttrib1f") == 0) return (void*)& qfn_glVertexAttrib1f;
	if (strcmp(name, "qfn_glVertexAttrib1fv") == 0) return (void*)& qfn_glVertexAttrib1fv;
	if (strcmp(name, "qfn_glVertexAttrib2f") == 0) return (void*)& qfn_glVertexAttrib2f;
	if (strcmp(name, "qfn_glVertexAttrib2fv") == 0) return (void*)& qfn_glVertexAttrib2fv;
	if (strcmp(name, "qfn_glVertexAttrib3f") == 0) return (void*)& qfn_glVertexAttrib3f;
	if (strcmp(name, "qfn_glVertexAttrib3fv") == 0) return (void*)& qfn_glVertexAttrib3fv;
	if (strcmp(name, "qfn_glVertexAttrib4f") == 0) return (void*)& qfn_glVertexAttrib4f;
	if (strcmp(name, "qfn_glVertexAttrib4fv") == 0) return (void*)& qfn_glVertexAttrib4fv;
	if (strcmp(name, "qfn_glVertexAttribPointer") == 0) return (void*)& qfn_glVertexAttribPointer;

	if (strcmp(name, "qfn_glReadBuffer") == 0) return (void*)& qfn_glReadBuffer;
	if (strcmp(name, "qfn_glDrawRangeElements") == 0) return (void*)& qfn_glDrawRangeElements;
	if (strcmp(name, "qfn_glTexImage3D") == 0) return (void*)& qfn_glTexImage3D;
	if (strcmp(name, "qfn_glTexSubImage3D") == 0) return (void*)& qfn_glTexSubImage3D;
	if (strcmp(name, "qfn_glCopyTexSubImage3D") == 0) return (void*)& qfn_glCopyTexSubImage3D;
	if (strcmp(name, "qfn_glCompressedTexImage3D") == 0) return (void*)& qfn_glCompressedTexImage3D;
	if (strcmp(name, "qfn_glCompressedTexSubImage3D") == 0) return (void*)& qfn_glCompressedTexSubImage3D;
	if (strcmp(name, "qfn_glGenQueries") == 0) return (void*)& qfn_glGenQueries;
	if (strcmp(name, "qfn_glDeleteQueries") == 0) return (void*)& qfn_glDeleteQueries;
	if (strcmp(name, "qfn_glIsQuery") == 0) return (void*)& qfn_glIsQuery;
	if (strcmp(name, "qfn_glBeginQuery") == 0) return (void*)& qfn_glBeginQuery;
	if (strcmp(name, "qfn_glEndQuery") == 0) return (void*)& qfn_glEndQuery;
	if (strcmp(name, "qfn_glGetQueryiv") == 0) return (void*)& qfn_glGetQueryiv;
	if (strcmp(name, "qfn_glGetQueryObjectuiv") == 0) return (void*)& qfn_glGetQueryObjectuiv;
	if (strcmp(name, "qfn_glUnmapBuffer") == 0) return (void*)& qfn_glUnmapBuffer;
	if (strcmp(name, "qfn_glGetBufferPointerv") == 0) return (void*)& qfn_glGetBufferPointerv;
	if (strcmp(name, "qfn_glDrawBuffers") == 0) return (void*)& qfn_glDrawBuffers;
	if (strcmp(name, "qfn_glUniformMatrix2x3fv") == 0) return (void*)& qfn_glUniformMatrix2x3fv;
	if (strcmp(name, "qfn_glUniformMatrix3x2fv") == 0) return (void*)& qfn_glUniformMatrix3x2fv;
	if (strcmp(name, "qfn_glUniformMatrix2x4fv") == 0) return (void*)& qfn_glUniformMatrix2x4fv;
	if (strcmp(name, "qfn_glUniformMatrix4x2fv") == 0) return (void*)& qfn_glUniformMatrix4x2fv;
	if (strcmp(name, "qfn_glUniformMatrix3x4fv") == 0) return (void*)& qfn_glUniformMatrix3x4fv;
	if (strcmp(name, "qfn_glUniformMatrix4x3fv") == 0) return (void*)& qfn_glUniformMatrix4x3fv;
	if (strcmp(name, "qfn_glBlitFramebuffer") == 0) return (void*)& qfn_glBlitFramebuffer;
	if (strcmp(name, "qfn_glRenderbufferStorageMultisample") == 0) return (void*)& qfn_glRenderbufferStorageMultisample;
	if (strcmp(name, "qfn_glFramebufferTextureLayer") == 0) return (void*)& qfn_glFramebufferTextureLayer;
	if (strcmp(name, "qfn_glMapBufferRange") == 0) return (void*)& qfn_glMapBufferRange;
	if (strcmp(name, "qfn_glFlushMappedBufferRange") == 0) return (void*)& qfn_glFlushMappedBufferRange;
	if (strcmp(name, "qfn_glBindVertexArray") == 0) return (void*)& qfn_glBindVertexArray;
	if (strcmp(name, "qfn_glDeleteVertexArrays") == 0) return (void*)& qfn_glDeleteVertexArrays;
	if (strcmp(name, "qfn_glGenVertexArrays") == 0) return (void*)& qfn_glGenVertexArrays;
	if (strcmp(name, "qfn_glIsVertexArray") == 0) return (void*)& qfn_glIsVertexArray;
	if (strcmp(name, "qfn_glGetIntegeri_v") == 0) return (void*)& qfn_glGetIntegeri_v;
	if (strcmp(name, "qfn_glBeginTransformFeedback") == 0) return (void*)& qfn_glBeginTransformFeedback;
	if (strcmp(name, "qfn_glEndTransformFeedback") == 0) return (void*)& qfn_glEndTransformFeedback;
	if (strcmp(name, "qfn_glBindBufferRange") == 0) return (void*)& qfn_glBindBufferRange;
	if (strcmp(name, "qfn_glBindBufferBase") == 0) return (void*)& qfn_glBindBufferBase;
	if (strcmp(name, "qfn_glTransformFeedbackVaryings") == 0) return (void*)& qfn_glTransformFeedbackVaryings;
	if (strcmp(name, "qfn_glGetTransformFeedbackVarying") == 0) return (void*)& qfn_glGetTransformFeedbackVarying;
	if (strcmp(name, "qfn_glVertexAttribIPointer") == 0) return (void*)& qfn_glVertexAttribIPointer;
	if (strcmp(name, "qfn_glGetVertexAttribIiv") == 0) return (void*)& qfn_glGetVertexAttribIiv;
	if (strcmp(name, "qfn_glGetVertexAttribIuiv") == 0) return (void*)& qfn_glGetVertexAttribIuiv;
	if (strcmp(name, "qfn_glVertexAttribI4i") == 0) return (void*)& qfn_glVertexAttribI4i;
	if (strcmp(name, "qfn_glVertexAttribI4ui") == 0) return (void*)& qfn_glVertexAttribI4ui;
	if (strcmp(name, "qfn_glVertexAttribI4iv") == 0) return (void*)& qfn_glVertexAttribI4iv;
	if (strcmp(name, "qfn_glVertexAttribI4uiv") == 0) return (void*)& qfn_glVertexAttribI4uiv;
	if (strcmp(name, "qfn_glGetUniformuiv") == 0) return (void*)& qfn_glGetUniformuiv;
	if (strcmp(name, "qfn_glGetFragDataLocation") == 0) return (void*)& qfn_glGetFragDataLocation;
	if (strcmp(name, "qfn_glUniform1ui") == 0) return (void*)& qfn_glUniform1ui;
	if (strcmp(name, "qfn_glUniform2ui") == 0) return (void*)& qfn_glUniform2ui;
	if (strcmp(name, "qfn_glUniform3ui") == 0) return (void*)& qfn_glUniform3ui;
	if (strcmp(name, "qfn_glUniform4ui") == 0) return (void*)& qfn_glUniform4ui;
	if (strcmp(name, "qfn_glUniform1uiv") == 0) return (void*)& qfn_glUniform1uiv;
	if (strcmp(name, "qfn_glUniform2uiv") == 0) return (void*)& qfn_glUniform2uiv;
	if (strcmp(name, "qfn_glUniform3uiv") == 0) return (void*)& qfn_glUniform3uiv;
	if (strcmp(name, "qfn_glUniform4uiv") == 0) return (void*)& qfn_glUniform4uiv;
	if (strcmp(name, "qfn_glClearBufferiv") == 0) return (void*)& qfn_glClearBufferiv;
	if (strcmp(name, "qfn_glClearBufferuiv") == 0) return (void*)& qfn_glClearBufferuiv;
	if (strcmp(name, "qfn_glClearBufferfv") == 0) return (void*)& qfn_glClearBufferfv;
	if (strcmp(name, "qfn_glClearBufferfi") == 0) return (void*)& qfn_glClearBufferfi;
	if (strcmp(name, "qfn_glGetStringi") == 0) return (void*)& qfn_glGetStringi;
	if (strcmp(name, "qfn_glCopyBufferSubData") == 0) return (void*)& qfn_glCopyBufferSubData;
	if (strcmp(name, "qfn_glGetUniformIndices") == 0) return (void*)& qfn_glGetUniformIndices;
	if (strcmp(name, "qfn_glGetActiveUniformsiv") == 0) return (void*)& qfn_glGetActiveUniformsiv;
	if (strcmp(name, "qfn_glGetUniformBlockIndex") == 0) return (void*)& qfn_glGetUniformBlockIndex;
	if (strcmp(name, "qfn_glGetActiveUniformBlockiv") == 0) return (void*)& qfn_glGetActiveUniformBlockiv;
	if (strcmp(name, "qfn_glGetActiveUniformBlockName") == 0) return (void*)& qfn_glGetActiveUniformBlockName;
	if (strcmp(name, "qfn_glUniformBlockBinding") == 0) return (void*)& qfn_glUniformBlockBinding;
	if (strcmp(name, "qfn_glDrawArraysInstanced") == 0) return (void*)& qfn_glDrawArraysInstanced;
	if (strcmp(name, "qfn_glDrawElementsInstanced") == 0) return (void*)& qfn_glDrawElementsInstanced;
	if (strcmp(name, "qfn_glFenceSync") == 0) return (void*)& qfn_glFenceSync;
	if (strcmp(name, "qfn_glIsSync") == 0) return (void*)& qfn_glIsSync;
	if (strcmp(name, "qfn_glDeleteSync") == 0) return (void*)& qfn_glDeleteSync;
	if (strcmp(name, "qfn_glClientWaitSync") == 0) return (void*)& qfn_glClientWaitSync;
	if (strcmp(name, "qfn_glWaitSync") == 0) return (void*)& qfn_glWaitSync;
	if (strcmp(name, "qfn_glGetInteger64v") == 0) return (void*)& qfn_glGetInteger64v;
	if (strcmp(name, "qfn_glGetSynciv") == 0) return (void*)& qfn_glGetSynciv;
	if (strcmp(name, "qfn_glGetInteger64i_v") == 0) return (void*)& qfn_glGetInteger64i_v;
	if (strcmp(name, "qfn_glGetBufferParameteri64v") == 0) return (void*)& qfn_glGetBufferParameteri64v;
	if (strcmp(name, "qfn_glGenSamplers") == 0) return (void*)& qfn_glGenSamplers;
	if (strcmp(name, "qfn_glDeleteSamplers") == 0) return (void*)& qfn_glDeleteSamplers;
	if (strcmp(name, "qfn_glIsSampler") == 0) return (void*)& qfn_glIsSampler;
	if (strcmp(name, "qfn_glBindSampler") == 0) return (void*)& qfn_glBindSampler;
	if (strcmp(name, "qfn_glSamplerParameteri") == 0) return (void*)& qfn_glSamplerParameteri;
	if (strcmp(name, "qfn_glSamplerParameteriv") == 0) return (void*)& qfn_glSamplerParameteriv;
	if (strcmp(name, "qfn_glSamplerParameterf") == 0) return (void*)& qfn_glSamplerParameterf;
	if (strcmp(name, "qfn_glSamplerParameterfv") == 0) return (void*)& qfn_glSamplerParameterfv;
	if (strcmp(name, "qfn_glGetSamplerParameteriv") == 0) return (void*)& qfn_glGetSamplerParameteriv;
	if (strcmp(name, "qfn_glGetSamplerParameterfv") == 0) return (void*)& qfn_glGetSamplerParameterfv;
	if (strcmp(name, "qfn_glVertexAttribDivisor") == 0) return (void*)& qfn_glVertexAttribDivisor;
	if (strcmp(name, "qfn_glBindTransformFeedback") == 0) return (void*)& qfn_glBindTransformFeedback;
	if (strcmp(name, "qfn_glDeleteTransformFeedbacks") == 0) return (void*)& qfn_glDeleteTransformFeedbacks;
	if (strcmp(name, "qfn_glGenTransformFeedbacks") == 0) return (void*)& qfn_glGenTransformFeedbacks;
	if (strcmp(name, "qfn_glIsTransformFeedback") == 0) return (void*)& qfn_glIsTransformFeedback;
	if (strcmp(name, "qfn_glPauseTransformFeedback") == 0) return (void*)& qfn_glPauseTransformFeedback;
	if (strcmp(name, "qfn_glResumeTransformFeedback") == 0) return (void*)& qfn_glResumeTransformFeedback;
	if (strcmp(name, "qfn_glGetProgramBinary") == 0) return (void*)& qfn_glGetProgramBinary;
	if (strcmp(name, "qfn_glProgramBinary") == 0) return (void*)& qfn_glProgramBinary;
	if (strcmp(name, "qfn_glProgramParameteri") == 0) return (void*)& qfn_glProgramParameteri;
	if (strcmp(name, "qfn_glInvalidateFramebuffer") == 0) return (void*)& qfn_glInvalidateFramebuffer;
	if (strcmp(name, "qfn_glInvalidateSubFramebuffer") == 0) return (void*)& qfn_glInvalidateSubFramebuffer;
	if (strcmp(name, "qfn_glTexStorage2D") == 0) return (void*)& qfn_glTexStorage2D;
	if (strcmp(name, "qfn_glTexStorage3D") == 0) return (void*)& qfn_glTexStorage3D;
	if (strcmp(name, "qfn_glGetInternalformativ") == 0) return (void*)& qfn_glGetInternalformativ;
	if (strcmp(name, "qfn_glDispatchCompute") == 0) return (void*)& qfn_glDispatchCompute;
	if (strcmp(name, "qfn_glDispatchComputeIndirect") == 0) return (void*)& qfn_glDispatchComputeIndirect;
	if (strcmp(name, "qfn_glDrawArraysIndirect") == 0) return (void*)& qfn_glDrawArraysIndirect;
	if (strcmp(name, "qfn_glDrawElementsIndirect") == 0) return (void*)& qfn_glDrawElementsIndirect;
	if (strcmp(name, "qfn_glFramebufferParameteri") == 0) return (void*)& qfn_glFramebufferParameteri;
	if (strcmp(name, "qfn_glGetFramebufferParameteriv") == 0) return (void*)& qfn_glGetFramebufferParameteriv;
	if (strcmp(name, "qfn_glGetProgramInterfaceiv") == 0) return (void*)& qfn_glGetProgramInterfaceiv;
	if (strcmp(name, "qfn_glGetProgramResourceIndex") == 0) return (void*)& qfn_glGetProgramResourceIndex;
	if (strcmp(name, "qfn_glGetProgramResourceName") == 0) return (void*)& qfn_glGetProgramResourceName;
	if (strcmp(name, "qfn_glGetProgramResourceiv") == 0) return (void*)& qfn_glGetProgramResourceiv;
	if (strcmp(name, "qfn_glGetProgramResourceLocation") == 0) return (void*)& qfn_glGetProgramResourceLocation;
	if (strcmp(name, "qfn_glUseProgramStages") == 0) return (void*)& qfn_glUseProgramStages;
	if (strcmp(name, "qfn_glActiveShaderProgram") == 0) return (void*)& qfn_glActiveShaderProgram;
	if (strcmp(name, "qfn_glCreateShaderProgramv") == 0) return (void*)& qfn_glCreateShaderProgramv;
	if (strcmp(name, "qfn_glBindProgramPipeline") == 0) return (void*)& qfn_glBindProgramPipeline;
	if (strcmp(name, "qfn_glDeleteProgramPipelines") == 0) return (void*)& qfn_glDeleteProgramPipelines;
	if (strcmp(name, "qfn_glGenProgramPipelines") == 0) return (void*)& qfn_glGenProgramPipelines;
	if (strcmp(name, "qfn_glIsProgramPipeline") == 0) return (void*)& qfn_glIsProgramPipeline;
	if (strcmp(name, "qfn_glGetProgramPipelineiv") == 0) return (void*)& qfn_glGetProgramPipelineiv;
	if (strcmp(name, "qfn_glProgramUniform1i") == 0) return (void*)& qfn_glProgramUniform1i;
	if (strcmp(name, "qfn_glProgramUniform2i") == 0) return (void*)& qfn_glProgramUniform2i;
	if (strcmp(name, "qfn_glProgramUniform3i") == 0) return (void*)& qfn_glProgramUniform3i;
	if (strcmp(name, "qfn_glProgramUniform4i") == 0) return (void*)& qfn_glProgramUniform4i;
	if (strcmp(name, "qfn_glProgramUniform1ui") == 0) return (void*)& qfn_glProgramUniform1ui;
	if (strcmp(name, "qfn_glProgramUniform2ui") == 0) return (void*)& qfn_glProgramUniform2ui;
	if (strcmp(name, "qfn_glProgramUniform3ui") == 0) return (void*)& qfn_glProgramUniform3ui;
	if (strcmp(name, "qfn_glProgramUniform4ui") == 0) return (void*)& qfn_glProgramUniform4ui;
	if (strcmp(name, "qfn_glProgramUniform1f") == 0) return (void*)& qfn_glProgramUniform1f;
	if (strcmp(name, "qfn_glProgramUniform2f") == 0) return (void*)& qfn_glProgramUniform2f;
	if (strcmp(name, "qfn_glProgramUniform3f") == 0) return (void*)& qfn_glProgramUniform3f;
	if (strcmp(name, "qfn_glProgramUniform4f") == 0) return (void*)& qfn_glProgramUniform4f;
	if (strcmp(name, "qfn_glProgramUniform1iv") == 0) return (void*)& qfn_glProgramUniform1iv;
	if (strcmp(name, "qfn_glProgramUniform2iv") == 0) return (void*)& qfn_glProgramUniform2iv;
	if (strcmp(name, "qfn_glProgramUniform3iv") == 0) return (void*)& qfn_glProgramUniform3iv;
	if (strcmp(name, "qfn_glProgramUniform4iv") == 0) return (void*)& qfn_glProgramUniform4iv;
	if (strcmp(name, "qfn_glProgramUniform1uiv") == 0) return (void*)& qfn_glProgramUniform1uiv;
	if (strcmp(name, "qfn_glProgramUniform2uiv") == 0) return (void*)& qfn_glProgramUniform2uiv;
	if (strcmp(name, "qfn_glProgramUniform3uiv") == 0) return (void*)& qfn_glProgramUniform3uiv;
	if (strcmp(name, "qfn_glProgramUniform4uiv") == 0) return (void*)& qfn_glProgramUniform4uiv;
	if (strcmp(name, "qfn_glProgramUniform1fv") == 0) return (void*)& qfn_glProgramUniform1fv;
	if (strcmp(name, "qfn_glProgramUniform2fv") == 0) return (void*)& qfn_glProgramUniform2fv;
	if (strcmp(name, "qfn_glProgramUniform3fv") == 0) return (void*)& qfn_glProgramUniform3fv;
	if (strcmp(name, "qfn_glProgramUniform4fv") == 0) return (void*)& qfn_glProgramUniform4fv;
	if (strcmp(name, "qfn_glProgramUniformMatrix2fv") == 0) return (void*)& qfn_glProgramUniformMatrix2fv;
	if (strcmp(name, "qfn_glProgramUniformMatrix3fv") == 0) return (void*)& qfn_glProgramUniformMatrix3fv;
	if (strcmp(name, "qfn_glProgramUniformMatrix4fv") == 0) return (void*)& qfn_glProgramUniformMatrix4fv;
	if (strcmp(name, "qfn_glProgramUniformMatrix2x3fv") == 0) return (void*)& qfn_glProgramUniformMatrix2x3fv;
	if (strcmp(name, "qfn_glProgramUniformMatrix3x2fv") == 0) return (void*)& qfn_glProgramUniformMatrix3x2fv;
	if (strcmp(name, "qfn_glProgramUniformMatrix2x4fv") == 0) return (void*)& qfn_glProgramUniformMatrix2x4fv;
	if (strcmp(name, "qfn_glProgramUniformMatrix4x2fv") == 0) return (void*)& qfn_glProgramUniformMatrix4x2fv;
	if (strcmp(name, "qfn_glProgramUniformMatrix3x4fv") == 0) return (void*)& qfn_glProgramUniformMatrix3x4fv;
	if (strcmp(name, "qfn_glProgramUniformMatrix4x3fv") == 0) return (void*)& qfn_glProgramUniformMatrix4x3fv;
	if (strcmp(name, "qfn_glValidateProgramPipeline") == 0) return (void*)& qfn_glValidateProgramPipeline;
	if (strcmp(name, "qfn_glGetProgramPipelineInfoLog") == 0) return (void*)& qfn_glGetProgramPipelineInfoLog;
	if (strcmp(name, "qfn_glBindImageTexture") == 0) return (void*)& qfn_glBindImageTexture;
	if (strcmp(name, "qfn_glGetBooleani_v") == 0) return (void*)& qfn_glGetBooleani_v;
	if (strcmp(name, "qfn_glMemoryBarrier") == 0) return (void*)& qfn_glMemoryBarrier;
	if (strcmp(name, "qfn_glMemoryBarrierByRegion") == 0) return (void*)& qfn_glMemoryBarrierByRegion;
	if (strcmp(name, "qfn_glTexStorage2DMultisample") == 0) return (void*)& qfn_glTexStorage2DMultisample;
	if (strcmp(name, "qfn_glGetMultisamplefv") == 0) return (void*)& qfn_glGetMultisamplefv;
	if (strcmp(name, "qfn_glSampleMaski") == 0) return (void*)& qfn_glSampleMaski;
	if (strcmp(name, "qfn_glGetTexLevelParameteriv") == 0) return (void*)& qfn_glGetTexLevelParameteriv;
	if (strcmp(name, "qfn_glGetTexLevelParameterfv") == 0) return (void*)& qfn_glGetTexLevelParameterfv;
	if (strcmp(name, "qfn_glBindVertexBuffer") == 0) return (void*)& qfn_glBindVertexBuffer;
	if (strcmp(name, "qfn_glVertexAttribFormat") == 0) return (void*)& qfn_glVertexAttribFormat;
	if (strcmp(name, "qfn_glVertexAttribIFormat") == 0) return (void*)& qfn_glVertexAttribIFormat;
	if (strcmp(name, "qfn_glVertexAttribBinding") == 0) return (void*)& qfn_glVertexAttribBinding;
	if (strcmp(name, "qfn_glVertexBindingDivisor") == 0) return (void*)& qfn_glVertexBindingDivisor;

	if (strcmp(name, "qfn_1_0_glViewport") == 0) return (void*)& qfn_1_0_glViewport;
	if (strcmp(name, "qfn_1_0_glDepthRange") == 0) return (void*)& qfn_1_0_glDepthRange;
	if (strcmp(name, "qfn_1_0_glIsEnabled") == 0) return (void*)& qfn_1_0_glIsEnabled;
	if (strcmp(name, "qfn_1_0_glGetTexLevelParameteriv") == 0) return (void*)& qfn_1_0_glGetTexLevelParameteriv;
	if (strcmp(name, "qfn_1_0_glGetTexLevelParameterfv") == 0) return (void*)& qfn_1_0_glGetTexLevelParameterfv;
	if (strcmp(name, "qfn_1_0_glGetTexParameteriv") == 0) return (void*)& qfn_1_0_glGetTexParameteriv;
	if (strcmp(name, "qfn_1_0_glGetTexParameterfv") == 0) return (void*)& qfn_1_0_glGetTexParameterfv;
	if (strcmp(name, "qfn_1_0_glGetTexImage") == 0) return (void*)& qfn_1_0_glGetTexImage;
	if (strcmp(name, "qfn_1_0_glGetString") == 0) return (void*)& qfn_1_0_glGetString;
	if (strcmp(name, "qfn_1_0_glGetIntegerv") == 0) return (void*)& qfn_1_0_glGetIntegerv;
	if (strcmp(name, "qfn_1_0_glGetFloatv") == 0) return (void*)& qfn_1_0_glGetFloatv;
	if (strcmp(name, "qfn_1_0_glGetError") == 0) return (void*)& qfn_1_0_glGetError;
	if (strcmp(name, "qfn_1_0_glGetDoublev") == 0) return (void*)& qfn_1_0_glGetDoublev;
	if (strcmp(name, "qfn_1_0_glGetBooleanv") == 0) return (void*)& qfn_1_0_glGetBooleanv;
	if (strcmp(name, "qfn_1_0_glReadPixels") == 0) return (void*)& qfn_1_0_glReadPixels;
	if (strcmp(name, "qfn_1_0_glReadBuffer") == 0) return (void*)& qfn_1_0_glReadBuffer;
	if (strcmp(name, "qfn_1_0_glPixelStorei") == 0) return (void*)& qfn_1_0_glPixelStorei;
	if (strcmp(name, "qfn_1_0_glPixelStoref") == 0) return (void*)& qfn_1_0_glPixelStoref;
	if (strcmp(name, "qfn_1_0_glDepthFunc") == 0) return (void*)& qfn_1_0_glDepthFunc;
	if (strcmp(name, "qfn_1_0_glStencilOp") == 0) return (void*)& qfn_1_0_glStencilOp;
	if (strcmp(name, "qfn_1_0_glStencilFunc") == 0) return (void*)& qfn_1_0_glStencilFunc;
	if (strcmp(name, "qfn_1_0_glLogicOp") == 0) return (void*)& qfn_1_0_glLogicOp;
	if (strcmp(name, "qfn_1_0_glBlendFunc") == 0) return (void*)& qfn_1_0_glBlendFunc;
	if (strcmp(name, "qfn_1_0_glFlush") == 0) return (void*)& qfn_1_0_glFlush;
	if (strcmp(name, "qfn_1_0_glFinish") == 0) return (void*)& qfn_1_0_glFinish;
	if (strcmp(name, "qfn_1_0_glEnable") == 0) return (void*)& qfn_1_0_glEnable;
	if (strcmp(name, "qfn_1_0_glDisable") == 0) return (void*)& qfn_1_0_glDisable;
	if (strcmp(name, "qfn_1_0_glDepthMask") == 0) return (void*)& qfn_1_0_glDepthMask;
	if (strcmp(name, "qfn_1_0_glColorMask") == 0) return (void*)& qfn_1_0_glColorMask;
	if (strcmp(name, "qfn_1_0_glStencilMask") == 0) return (void*)& qfn_1_0_glStencilMask;
	if (strcmp(name, "qfn_1_0_glClearDepth") == 0) return (void*)& qfn_1_0_glClearDepth;
	if (strcmp(name, "qfn_1_0_glClearStencil") == 0) return (void*)& qfn_1_0_glClearStencil;
	if (strcmp(name, "qfn_1_0_glClearColor") == 0) return (void*)& qfn_1_0_glClearColor;
	if (strcmp(name, "qfn_1_0_glClear") == 0) return (void*)& qfn_1_0_glClear;
	if (strcmp(name, "qfn_1_0_glDrawBuffer") == 0) return (void*)& qfn_1_0_glDrawBuffer;
	if (strcmp(name, "qfn_1_0_glTexImage2D") == 0) return (void*)& qfn_1_0_glTexImage2D;
	if (strcmp(name, "qfn_1_0_glTexImage1D") == 0) return (void*)& qfn_1_0_glTexImage1D;
	if (strcmp(name, "qfn_1_0_glTexParameteriv") == 0) return (void*)& qfn_1_0_glTexParameteriv;
	if (strcmp(name, "qfn_1_0_glTexParameteri") == 0) return (void*)& qfn_1_0_glTexParameteri;
	if (strcmp(name, "qfn_1_0_glTexParameterfv") == 0) return (void*)& qfn_1_0_glTexParameterfv;
	if (strcmp(name, "qfn_1_0_glTexParameterf") == 0) return (void*)& qfn_1_0_glTexParameterf;
	if (strcmp(name, "qfn_1_0_glScissor") == 0) return (void*)& qfn_1_0_glScissor;
	if (strcmp(name, "qfn_1_0_glPolygonMode") == 0) return (void*)& qfn_1_0_glPolygonMode;
	if (strcmp(name, "qfn_1_0_glPointSize") == 0) return (void*)& qfn_1_0_glPointSize;
	if (strcmp(name, "qfn_1_0_glLineWidth") == 0) return (void*)& qfn_1_0_glLineWidth;
	if (strcmp(name, "qfn_1_0_glHint") == 0) return (void*)& qfn_1_0_glHint;
	if (strcmp(name, "qfn_1_0_glFrontFace") == 0) return (void*)& qfn_1_0_glFrontFace;
	if (strcmp(name, "qfn_1_0_glCullFace") == 0) return (void*)& qfn_1_0_glCullFace;
	if (strcmp(name, "qfn_1_0_glTranslatef") == 0) return (void*)& qfn_1_0_glTranslatef;
	if (strcmp(name, "qfn_1_0_glTranslated") == 0) return (void*)& qfn_1_0_glTranslated;
	if (strcmp(name, "qfn_1_0_glScalef") == 0) return (void*)& qfn_1_0_glScalef;
	if (strcmp(name, "qfn_1_0_glScaled") == 0) return (void*)& qfn_1_0_glScaled;
	if (strcmp(name, "qfn_1_0_glRotatef") == 0) return (void*)& qfn_1_0_glRotatef;
	if (strcmp(name, "qfn_1_0_glRotated") == 0) return (void*)& qfn_1_0_glRotated;
	if (strcmp(name, "qfn_1_0_glPushMatrix") == 0) return (void*)& qfn_1_0_glPushMatrix;
	if (strcmp(name, "qfn_1_0_glPopMatrix") == 0) return (void*)& qfn_1_0_glPopMatrix;
	if (strcmp(name, "qfn_1_0_glOrtho") == 0) return (void*)& qfn_1_0_glOrtho;
	if (strcmp(name, "qfn_1_0_glMultMatrixd") == 0) return (void*)& qfn_1_0_glMultMatrixd;
	if (strcmp(name, "qfn_1_0_glMultMatrixf") == 0) return (void*)& qfn_1_0_glMultMatrixf;
	if (strcmp(name, "qfn_1_0_glMatrixMode") == 0) return (void*)& qfn_1_0_glMatrixMode;
	if (strcmp(name, "qfn_1_0_glLoadMatrixd") == 0) return (void*)& qfn_1_0_glLoadMatrixd;
	if (strcmp(name, "qfn_1_0_glLoadMatrixf") == 0) return (void*)& qfn_1_0_glLoadMatrixf;
	if (strcmp(name, "qfn_1_0_glLoadIdentity") == 0) return (void*)& qfn_1_0_glLoadIdentity;
	if (strcmp(name, "qfn_1_0_glFrustum") == 0) return (void*)& qfn_1_0_glFrustum;
	if (strcmp(name, "qfn_1_0_glIsList") == 0) return (void*)& qfn_1_0_glIsList;
	if (strcmp(name, "qfn_1_0_glGetTexGeniv") == 0) return (void*)& qfn_1_0_glGetTexGeniv;
	if (strcmp(name, "qfn_1_0_glGetTexGenfv") == 0) return (void*)& qfn_1_0_glGetTexGenfv;
	if (strcmp(name, "qfn_1_0_glGetTexGendv") == 0) return (void*)& qfn_1_0_glGetTexGendv;
	if (strcmp(name, "qfn_1_0_glGetTexEnviv") == 0) return (void*)& qfn_1_0_glGetTexEnviv;
	if (strcmp(name, "qfn_1_0_glGetTexEnvfv") == 0) return (void*)& qfn_1_0_glGetTexEnvfv;
	if (strcmp(name, "qfn_1_0_glGetPolygonStipple") == 0) return (void*)& qfn_1_0_glGetPolygonStipple;
	if (strcmp(name, "qfn_1_0_glGetPixelMapusv") == 0) return (void*)& qfn_1_0_glGetPixelMapusv;
	if (strcmp(name, "qfn_1_0_glGetPixelMapuiv") == 0) return (void*)& qfn_1_0_glGetPixelMapuiv;
	if (strcmp(name, "qfn_1_0_glGetPixelMapfv") == 0) return (void*)& qfn_1_0_glGetPixelMapfv;
	if (strcmp(name, "qfn_1_0_glGetMaterialiv") == 0) return (void*)& qfn_1_0_glGetMaterialiv;
	if (strcmp(name, "qfn_1_0_glGetMaterialfv") == 0) return (void*)& qfn_1_0_glGetMaterialfv;
	if (strcmp(name, "qfn_1_0_glGetMapiv") == 0) return (void*)& qfn_1_0_glGetMapiv;
	if (strcmp(name, "qfn_1_0_glGetMapfv") == 0) return (void*)& qfn_1_0_glGetMapfv;
	if (strcmp(name, "qfn_1_0_glGetMapdv") == 0) return (void*)& qfn_1_0_glGetMapdv;
	if (strcmp(name, "qfn_1_0_glGetLightiv") == 0) return (void*)& qfn_1_0_glGetLightiv;
	if (strcmp(name, "qfn_1_0_glGetLightfv") == 0) return (void*)& qfn_1_0_glGetLightfv;
	if (strcmp(name, "qfn_1_0_glGetClipPlane") == 0) return (void*)& qfn_1_0_glGetClipPlane;
	if (strcmp(name, "qfn_1_0_glDrawPixels") == 0) return (void*)& qfn_1_0_glDrawPixels;
	if (strcmp(name, "qfn_1_0_glCopyPixels") == 0) return (void*)& qfn_1_0_glCopyPixels;
	if (strcmp(name, "qfn_1_0_glPixelMapusv") == 0) return (void*)& qfn_1_0_glPixelMapusv;
	if (strcmp(name, "qfn_1_0_glPixelMapuiv") == 0) return (void*)& qfn_1_0_glPixelMapuiv;
	if (strcmp(name, "qfn_1_0_glPixelMapfv") == 0) return (void*)& qfn_1_0_glPixelMapfv;
	if (strcmp(name, "qfn_1_0_glPixelTransferi") == 0) return (void*)& qfn_1_0_glPixelTransferi;
	if (strcmp(name, "qfn_1_0_glPixelTransferf") == 0) return (void*)& qfn_1_0_glPixelTransferf;
	if (strcmp(name, "qfn_1_0_glPixelZoom") == 0) return (void*)& qfn_1_0_glPixelZoom;
	if (strcmp(name, "qfn_1_0_glAlphaFunc") == 0) return (void*)& qfn_1_0_glAlphaFunc;
	if (strcmp(name, "qfn_1_0_glEvalPoint2") == 0) return (void*)& qfn_1_0_glEvalPoint2;
	if (strcmp(name, "qfn_1_0_glEvalMesh2") == 0) return (void*)& qfn_1_0_glEvalMesh2;
	if (strcmp(name, "qfn_1_0_glEvalPoint1") == 0) return (void*)& qfn_1_0_glEvalPoint1;
	if (strcmp(name, "qfn_1_0_glEvalMesh1") == 0) return (void*)& qfn_1_0_glEvalMesh1;
	if (strcmp(name, "qfn_1_0_glEvalCoord2fv") == 0) return (void*)& qfn_1_0_glEvalCoord2fv;
	if (strcmp(name, "qfn_1_0_glEvalCoord2f") == 0) return (void*)& qfn_1_0_glEvalCoord2f;
	if (strcmp(name, "qfn_1_0_glEvalCoord2dv") == 0) return (void*)& qfn_1_0_glEvalCoord2dv;
	if (strcmp(name, "qfn_1_0_glEvalCoord2d") == 0) return (void*)& qfn_1_0_glEvalCoord2d;
	if (strcmp(name, "qfn_1_0_glEvalCoord1fv") == 0) return (void*)& qfn_1_0_glEvalCoord1fv;
	if (strcmp(name, "qfn_1_0_glEvalCoord1f") == 0) return (void*)& qfn_1_0_glEvalCoord1f;
	if (strcmp(name, "qfn_1_0_glEvalCoord1dv") == 0) return (void*)& qfn_1_0_glEvalCoord1dv;
	if (strcmp(name, "qfn_1_0_glEvalCoord1d") == 0) return (void*)& qfn_1_0_glEvalCoord1d;
	if (strcmp(name, "qfn_1_0_glMapGrid2f") == 0) return (void*)& qfn_1_0_glMapGrid2f;
	if (strcmp(name, "qfn_1_0_glMapGrid2d") == 0) return (void*)& qfn_1_0_glMapGrid2d;
	if (strcmp(name, "qfn_1_0_glMapGrid1f") == 0) return (void*)& qfn_1_0_glMapGrid1f;
	if (strcmp(name, "qfn_1_0_glMapGrid1d") == 0) return (void*)& qfn_1_0_glMapGrid1d;
	if (strcmp(name, "qfn_1_0_glMap2f") == 0) return (void*)& qfn_1_0_glMap2f;
	if (strcmp(name, "qfn_1_0_glMap2d") == 0) return (void*)& qfn_1_0_glMap2d;
	if (strcmp(name, "qfn_1_0_glMap1f") == 0) return (void*)& qfn_1_0_glMap1f;
	if (strcmp(name, "qfn_1_0_glMap1d") == 0) return (void*)& qfn_1_0_glMap1d;
	if (strcmp(name, "qfn_1_0_glPushAttrib") == 0) return (void*)& qfn_1_0_glPushAttrib;
	if (strcmp(name, "qfn_1_0_glPopAttrib") == 0) return (void*)& qfn_1_0_glPopAttrib;
	if (strcmp(name, "qfn_1_0_glAccum") == 0) return (void*)& qfn_1_0_glAccum;
	if (strcmp(name, "qfn_1_0_glIndexMask") == 0) return (void*)& qfn_1_0_glIndexMask;
	if (strcmp(name, "qfn_1_0_glClearIndex") == 0) return (void*)& qfn_1_0_glClearIndex;
	if (strcmp(name, "qfn_1_0_glClearAccum") == 0) return (void*)& qfn_1_0_glClearAccum;
	if (strcmp(name, "qfn_1_0_glPushName") == 0) return (void*)& qfn_1_0_glPushName;
	if (strcmp(name, "qfn_1_0_glPopName") == 0) return (void*)& qfn_1_0_glPopName;
	if (strcmp(name, "qfn_1_0_glPassThrough") == 0) return (void*)& qfn_1_0_glPassThrough;
	if (strcmp(name, "qfn_1_0_glLoadName") == 0) return (void*)& qfn_1_0_glLoadName;
	if (strcmp(name, "qfn_1_0_glInitNames") == 0) return (void*)& qfn_1_0_glInitNames;
	if (strcmp(name, "qfn_1_0_glRenderMode") == 0) return (void*)& qfn_1_0_glRenderMode;
	if (strcmp(name, "qfn_1_0_glSelectBuffer") == 0) return (void*)& qfn_1_0_glSelectBuffer;
	if (strcmp(name, "qfn_1_0_glFeedbackBuffer") == 0) return (void*)& qfn_1_0_glFeedbackBuffer;
	if (strcmp(name, "qfn_1_0_glTexGeniv") == 0) return (void*)& qfn_1_0_glTexGeniv;
	if (strcmp(name, "qfn_1_0_glTexGeni") == 0) return (void*)& qfn_1_0_glTexGeni;
	if (strcmp(name, "qfn_1_0_glTexGenfv") == 0) return (void*)& qfn_1_0_glTexGenfv;
	if (strcmp(name, "qfn_1_0_glTexGenf") == 0) return (void*)& qfn_1_0_glTexGenf;
	if (strcmp(name, "qfn_1_0_glTexGendv") == 0) return (void*)& qfn_1_0_glTexGendv;
	if (strcmp(name, "qfn_1_0_glTexGend") == 0) return (void*)& qfn_1_0_glTexGend;
	if (strcmp(name, "qfn_1_0_glTexEnviv") == 0) return (void*)& qfn_1_0_glTexEnviv;
	if (strcmp(name, "qfn_1_0_glTexEnvi") == 0) return (void*)& qfn_1_0_glTexEnvi;
	if (strcmp(name, "qfn_1_0_glTexEnvfv") == 0) return (void*)& qfn_1_0_glTexEnvfv;
	if (strcmp(name, "qfn_1_0_glTexEnvf") == 0) return (void*)& qfn_1_0_glTexEnvf;
	if (strcmp(name, "qfn_1_0_glShadeModel") == 0) return (void*)& qfn_1_0_glShadeModel;
	if (strcmp(name, "qfn_1_0_glPolygonStipple") == 0) return (void*)& qfn_1_0_glPolygonStipple;
	if (strcmp(name, "qfn_1_0_glMaterialiv") == 0) return (void*)& qfn_1_0_glMaterialiv;
	if (strcmp(name, "qfn_1_0_glMateriali") == 0) return (void*)& qfn_1_0_glMateriali;
	if (strcmp(name, "qfn_1_0_glMaterialfv") == 0) return (void*)& qfn_1_0_glMaterialfv;
	if (strcmp(name, "qfn_1_0_glMaterialf") == 0) return (void*)& qfn_1_0_glMaterialf;
	if (strcmp(name, "qfn_1_0_glLineStipple") == 0) return (void*)& qfn_1_0_glLineStipple;
	if (strcmp(name, "qfn_1_0_glLightModeliv") == 0) return (void*)& qfn_1_0_glLightModeliv;
	if (strcmp(name, "qfn_1_0_glLightModeli") == 0) return (void*)& qfn_1_0_glLightModeli;
	if (strcmp(name, "qfn_1_0_glLightModelfv") == 0) return (void*)& qfn_1_0_glLightModelfv;
	if (strcmp(name, "qfn_1_0_glLightModelf") == 0) return (void*)& qfn_1_0_glLightModelf;
	if (strcmp(name, "qfn_1_0_glLightiv") == 0) return (void*)& qfn_1_0_glLightiv;
	if (strcmp(name, "qfn_1_0_glLighti") == 0) return (void*)& qfn_1_0_glLighti;
	if (strcmp(name, "qfn_1_0_glLightfv") == 0) return (void*)& qfn_1_0_glLightfv;
	if (strcmp(name, "qfn_1_0_glLightf") == 0) return (void*)& qfn_1_0_glLightf;
	if (strcmp(name, "qfn_1_0_glFogiv") == 0) return (void*)& qfn_1_0_glFogiv;
	if (strcmp(name, "qfn_1_0_glFogi") == 0) return (void*)& qfn_1_0_glFogi;
	if (strcmp(name, "qfn_1_0_glFogfv") == 0) return (void*)& qfn_1_0_glFogfv;
	if (strcmp(name, "qfn_1_0_glFogf") == 0) return (void*)& qfn_1_0_glFogf;
	if (strcmp(name, "qfn_1_0_glColorMaterial") == 0) return (void*)& qfn_1_0_glColorMaterial;
	if (strcmp(name, "qfn_1_0_glClipPlane") == 0) return (void*)& qfn_1_0_glClipPlane;
	if (strcmp(name, "qfn_1_0_glVertex4sv") == 0) return (void*)& qfn_1_0_glVertex4sv;
	if (strcmp(name, "qfn_1_0_glVertex4s") == 0) return (void*)& qfn_1_0_glVertex4s;
	if (strcmp(name, "qfn_1_0_glVertex4iv") == 0) return (void*)& qfn_1_0_glVertex4iv;
	if (strcmp(name, "qfn_1_0_glVertex4i") == 0) return (void*)& qfn_1_0_glVertex4i;
	if (strcmp(name, "qfn_1_0_glVertex4fv") == 0) return (void*)& qfn_1_0_glVertex4fv;
	if (strcmp(name, "qfn_1_0_glVertex4f") == 0) return (void*)& qfn_1_0_glVertex4f;
	if (strcmp(name, "qfn_1_0_glVertex4dv") == 0) return (void*)& qfn_1_0_glVertex4dv;
	if (strcmp(name, "qfn_1_0_glVertex4d") == 0) return (void*)& qfn_1_0_glVertex4d;
	if (strcmp(name, "qfn_1_0_glVertex3sv") == 0) return (void*)& qfn_1_0_glVertex3sv;
	if (strcmp(name, "qfn_1_0_glVertex3s") == 0) return (void*)& qfn_1_0_glVertex3s;
	if (strcmp(name, "qfn_1_0_glVertex3iv") == 0) return (void*)& qfn_1_0_glVertex3iv;
	if (strcmp(name, "qfn_1_0_glVertex3i") == 0) return (void*)& qfn_1_0_glVertex3i;
	if (strcmp(name, "qfn_1_0_glVertex3fv") == 0) return (void*)& qfn_1_0_glVertex3fv;
	if (strcmp(name, "qfn_1_0_glVertex3f") == 0) return (void*)& qfn_1_0_glVertex3f;
	if (strcmp(name, "qfn_1_0_glVertex3dv") == 0) return (void*)& qfn_1_0_glVertex3dv;
	if (strcmp(name, "qfn_1_0_glVertex3d") == 0) return (void*)& qfn_1_0_glVertex3d;
	if (strcmp(name, "qfn_1_0_glVertex2sv") == 0) return (void*)& qfn_1_0_glVertex2sv;
	if (strcmp(name, "qfn_1_0_glVertex2s") == 0) return (void*)& qfn_1_0_glVertex2s;
	if (strcmp(name, "qfn_1_0_glVertex2iv") == 0) return (void*)& qfn_1_0_glVertex2iv;
	if (strcmp(name, "qfn_1_0_glVertex2i") == 0) return (void*)& qfn_1_0_glVertex2i;
	if (strcmp(name, "qfn_1_0_glVertex2fv") == 0) return (void*)& qfn_1_0_glVertex2fv;
	if (strcmp(name, "qfn_1_0_glVertex2f") == 0) return (void*)& qfn_1_0_glVertex2f;
	if (strcmp(name, "qfn_1_0_glVertex2dv") == 0) return (void*)& qfn_1_0_glVertex2dv;
	if (strcmp(name, "qfn_1_0_glVertex2d") == 0) return (void*)& qfn_1_0_glVertex2d;
	if (strcmp(name, "qfn_1_0_glTexCoord4sv") == 0) return (void*)& qfn_1_0_glTexCoord4sv;
	if (strcmp(name, "qfn_1_0_glTexCoord4s") == 0) return (void*)& qfn_1_0_glTexCoord4s;
	if (strcmp(name, "qfn_1_0_glTexCoord4iv") == 0) return (void*)& qfn_1_0_glTexCoord4iv;
	if (strcmp(name, "qfn_1_0_glTexCoord4i") == 0) return (void*)& qfn_1_0_glTexCoord4i;
	if (strcmp(name, "qfn_1_0_glTexCoord4fv") == 0) return (void*)& qfn_1_0_glTexCoord4fv;
	if (strcmp(name, "qfn_1_0_glTexCoord4f") == 0) return (void*)& qfn_1_0_glTexCoord4f;
	if (strcmp(name, "qfn_1_0_glTexCoord4dv") == 0) return (void*)& qfn_1_0_glTexCoord4dv;
	if (strcmp(name, "qfn_1_0_glTexCoord4d") == 0) return (void*)& qfn_1_0_glTexCoord4d;
	if (strcmp(name, "qfn_1_0_glTexCoord3sv") == 0) return (void*)& qfn_1_0_glTexCoord3sv;
	if (strcmp(name, "qfn_1_0_glTexCoord3s") == 0) return (void*)& qfn_1_0_glTexCoord3s;
	if (strcmp(name, "qfn_1_0_glTexCoord3iv") == 0) return (void*)& qfn_1_0_glTexCoord3iv;
	if (strcmp(name, "qfn_1_0_glTexCoord3i") == 0) return (void*)& qfn_1_0_glTexCoord3i;
	if (strcmp(name, "qfn_1_0_glTexCoord3fv") == 0) return (void*)& qfn_1_0_glTexCoord3fv;
	if (strcmp(name, "qfn_1_0_glTexCoord3f") == 0) return (void*)& qfn_1_0_glTexCoord3f;
	if (strcmp(name, "qfn_1_0_glTexCoord3dv") == 0) return (void*)& qfn_1_0_glTexCoord3dv;
	if (strcmp(name, "qfn_1_0_glTexCoord3d") == 0) return (void*)& qfn_1_0_glTexCoord3d;
	if (strcmp(name, "qfn_1_0_glTexCoord2sv") == 0) return (void*)& qfn_1_0_glTexCoord2sv;
	if (strcmp(name, "qfn_1_0_glTexCoord2s") == 0) return (void*)& qfn_1_0_glTexCoord2s;
	if (strcmp(name, "qfn_1_0_glTexCoord2iv") == 0) return (void*)& qfn_1_0_glTexCoord2iv;
	if (strcmp(name, "qfn_1_0_glTexCoord2i") == 0) return (void*)& qfn_1_0_glTexCoord2i;
	if (strcmp(name, "qfn_1_0_glTexCoord2fv") == 0) return (void*)& qfn_1_0_glTexCoord2fv;
	if (strcmp(name, "qfn_1_0_glTexCoord2f") == 0) return (void*)& qfn_1_0_glTexCoord2f;
	if (strcmp(name, "qfn_1_0_glTexCoord2dv") == 0) return (void*)& qfn_1_0_glTexCoord2dv;
	if (strcmp(name, "qfn_1_0_glTexCoord2d") == 0) return (void*)& qfn_1_0_glTexCoord2d;
	if (strcmp(name, "qfn_1_0_glTexCoord1sv") == 0) return (void*)& qfn_1_0_glTexCoord1sv;
	if (strcmp(name, "qfn_1_0_glTexCoord1s") == 0) return (void*)& qfn_1_0_glTexCoord1s;
	if (strcmp(name, "qfn_1_0_glTexCoord1iv") == 0) return (void*)& qfn_1_0_glTexCoord1iv;
	if (strcmp(name, "qfn_1_0_glTexCoord1i") == 0) return (void*)& qfn_1_0_glTexCoord1i;
	if (strcmp(name, "qfn_1_0_glTexCoord1fv") == 0) return (void*)& qfn_1_0_glTexCoord1fv;
	if (strcmp(name, "qfn_1_0_glTexCoord1f") == 0) return (void*)& qfn_1_0_glTexCoord1f;
	if (strcmp(name, "qfn_1_0_glTexCoord1dv") == 0) return (void*)& qfn_1_0_glTexCoord1dv;
	if (strcmp(name, "qfn_1_0_glTexCoord1d") == 0) return (void*)& qfn_1_0_glTexCoord1d;
	if (strcmp(name, "qfn_1_0_glRectsv") == 0) return (void*)& qfn_1_0_glRectsv;
	if (strcmp(name, "qfn_1_0_glRects") == 0) return (void*)& qfn_1_0_glRects;
	if (strcmp(name, "qfn_1_0_glRectiv") == 0) return (void*)& qfn_1_0_glRectiv;
	if (strcmp(name, "qfn_1_0_glRecti") == 0) return (void*)& qfn_1_0_glRecti;
	if (strcmp(name, "qfn_1_0_glRectfv") == 0) return (void*)& qfn_1_0_glRectfv;
	if (strcmp(name, "qfn_1_0_glRectf") == 0) return (void*)& qfn_1_0_glRectf;
	if (strcmp(name, "qfn_1_0_glRectdv") == 0) return (void*)& qfn_1_0_glRectdv;
	if (strcmp(name, "qfn_1_0_glRectd") == 0) return (void*)& qfn_1_0_glRectd;
	if (strcmp(name, "qfn_1_0_glRasterPos4sv") == 0) return (void*)& qfn_1_0_glRasterPos4sv;
	if (strcmp(name, "qfn_1_0_glRasterPos4s") == 0) return (void*)& qfn_1_0_glRasterPos4s;
	if (strcmp(name, "qfn_1_0_glRasterPos4iv") == 0) return (void*)& qfn_1_0_glRasterPos4iv;
	if (strcmp(name, "qfn_1_0_glRasterPos4i") == 0) return (void*)& qfn_1_0_glRasterPos4i;
	if (strcmp(name, "qfn_1_0_glRasterPos4fv") == 0) return (void*)& qfn_1_0_glRasterPos4fv;
	if (strcmp(name, "qfn_1_0_glRasterPos4f") == 0) return (void*)& qfn_1_0_glRasterPos4f;
	if (strcmp(name, "qfn_1_0_glRasterPos4dv") == 0) return (void*)& qfn_1_0_glRasterPos4dv;
	if (strcmp(name, "qfn_1_0_glRasterPos4d") == 0) return (void*)& qfn_1_0_glRasterPos4d;
	if (strcmp(name, "qfn_1_0_glRasterPos3sv") == 0) return (void*)& qfn_1_0_glRasterPos3sv;
	if (strcmp(name, "qfn_1_0_glRasterPos3s") == 0) return (void*)& qfn_1_0_glRasterPos3s;
	if (strcmp(name, "qfn_1_0_glRasterPos3iv") == 0) return (void*)& qfn_1_0_glRasterPos3iv;
	if (strcmp(name, "qfn_1_0_glRasterPos3i") == 0) return (void*)& qfn_1_0_glRasterPos3i;
	if (strcmp(name, "qfn_1_0_glRasterPos3fv") == 0) return (void*)& qfn_1_0_glRasterPos3fv;
	if (strcmp(name, "qfn_1_0_glRasterPos3f") == 0) return (void*)& qfn_1_0_glRasterPos3f;
	if (strcmp(name, "qfn_1_0_glRasterPos3dv") == 0) return (void*)& qfn_1_0_glRasterPos3dv;
	if (strcmp(name, "qfn_1_0_glRasterPos3d") == 0) return (void*)& qfn_1_0_glRasterPos3d;
	if (strcmp(name, "qfn_1_0_glRasterPos2sv") == 0) return (void*)& qfn_1_0_glRasterPos2sv;
	if (strcmp(name, "qfn_1_0_glRasterPos2s") == 0) return (void*)& qfn_1_0_glRasterPos2s;
	if (strcmp(name, "qfn_1_0_glRasterPos2iv") == 0) return (void*)& qfn_1_0_glRasterPos2iv;
	if (strcmp(name, "qfn_1_0_glRasterPos2i") == 0) return (void*)& qfn_1_0_glRasterPos2i;
	if (strcmp(name, "qfn_1_0_glRasterPos2fv") == 0) return (void*)& qfn_1_0_glRasterPos2fv;
	if (strcmp(name, "qfn_1_0_glRasterPos2f") == 0) return (void*)& qfn_1_0_glRasterPos2f;
	if (strcmp(name, "qfn_1_0_glRasterPos2dv") == 0) return (void*)& qfn_1_0_glRasterPos2dv;
	if (strcmp(name, "qfn_1_0_glRasterPos2d") == 0) return (void*)& qfn_1_0_glRasterPos2d;
	if (strcmp(name, "qfn_1_0_glNormal3sv") == 0) return (void*)& qfn_1_0_glNormal3sv;
	if (strcmp(name, "qfn_1_0_glNormal3s") == 0) return (void*)& qfn_1_0_glNormal3s;
	if (strcmp(name, "qfn_1_0_glNormal3iv") == 0) return (void*)& qfn_1_0_glNormal3iv;
	if (strcmp(name, "qfn_1_0_glNormal3i") == 0) return (void*)& qfn_1_0_glNormal3i;
	if (strcmp(name, "qfn_1_0_glNormal3fv") == 0) return (void*)& qfn_1_0_glNormal3fv;
	if (strcmp(name, "qfn_1_0_glNormal3f") == 0) return (void*)& qfn_1_0_glNormal3f;
	if (strcmp(name, "qfn_1_0_glNormal3dv") == 0) return (void*)& qfn_1_0_glNormal3dv;
	if (strcmp(name, "qfn_1_0_glNormal3d") == 0) return (void*)& qfn_1_0_glNormal3d;
	if (strcmp(name, "qfn_1_0_glNormal3bv") == 0) return (void*)& qfn_1_0_glNormal3bv;
	if (strcmp(name, "qfn_1_0_glNormal3b") == 0) return (void*)& qfn_1_0_glNormal3b;
	if (strcmp(name, "qfn_1_0_glIndexsv") == 0) return (void*)& qfn_1_0_glIndexsv;
	if (strcmp(name, "qfn_1_0_glIndexs") == 0) return (void*)& qfn_1_0_glIndexs;
	if (strcmp(name, "qfn_1_0_glIndexiv") == 0) return (void*)& qfn_1_0_glIndexiv;
	if (strcmp(name, "qfn_1_0_glIndexi") == 0) return (void*)& qfn_1_0_glIndexi;
	if (strcmp(name, "qfn_1_0_glIndexfv") == 0) return (void*)& qfn_1_0_glIndexfv;
	if (strcmp(name, "qfn_1_0_glIndexf") == 0) return (void*)& qfn_1_0_glIndexf;
	if (strcmp(name, "qfn_1_0_glIndexdv") == 0) return (void*)& qfn_1_0_glIndexdv;
	if (strcmp(name, "qfn_1_0_glIndexd") == 0) return (void*)& qfn_1_0_glIndexd;
	if (strcmp(name, "qfn_1_0_glEnd") == 0) return (void*)& qfn_1_0_glEnd;
	if (strcmp(name, "qfn_1_0_glEdgeFlagv") == 0) return (void*)& qfn_1_0_glEdgeFlagv;
	if (strcmp(name, "qfn_1_0_glEdgeFlag") == 0) return (void*)& qfn_1_0_glEdgeFlag;
	if (strcmp(name, "qfn_1_0_glColor4usv") == 0) return (void*)& qfn_1_0_glColor4usv;
	if (strcmp(name, "qfn_1_0_glColor4us") == 0) return (void*)& qfn_1_0_glColor4us;
	if (strcmp(name, "qfn_1_0_glColor4uiv") == 0) return (void*)& qfn_1_0_glColor4uiv;
	if (strcmp(name, "qfn_1_0_glColor4ui") == 0) return (void*)& qfn_1_0_glColor4ui;
	if (strcmp(name, "qfn_1_0_glColor4ubv") == 0) return (void*)& qfn_1_0_glColor4ubv;
	if (strcmp(name, "qfn_1_0_glColor4ub") == 0) return (void*)& qfn_1_0_glColor4ub;
	if (strcmp(name, "qfn_1_0_glColor4sv") == 0) return (void*)& qfn_1_0_glColor4sv;
	if (strcmp(name, "qfn_1_0_glColor4s") == 0) return (void*)& qfn_1_0_glColor4s;
	if (strcmp(name, "qfn_1_0_glColor4iv") == 0) return (void*)& qfn_1_0_glColor4iv;
	if (strcmp(name, "qfn_1_0_glColor4i") == 0) return (void*)& qfn_1_0_glColor4i;
	if (strcmp(name, "qfn_1_0_glColor4fv") == 0) return (void*)& qfn_1_0_glColor4fv;
	if (strcmp(name, "qfn_1_0_glColor4f") == 0) return (void*)& qfn_1_0_glColor4f;
	if (strcmp(name, "qfn_1_0_glColor4dv") == 0) return (void*)& qfn_1_0_glColor4dv;
	if (strcmp(name, "qfn_1_0_glColor4d") == 0) return (void*)& qfn_1_0_glColor4d;
	if (strcmp(name, "qfn_1_0_glColor4bv") == 0) return (void*)& qfn_1_0_glColor4bv;
	if (strcmp(name, "qfn_1_0_glColor4b") == 0) return (void*)& qfn_1_0_glColor4b;
	if (strcmp(name, "qfn_1_0_glColor3usv") == 0) return (void*)& qfn_1_0_glColor3usv;
	if (strcmp(name, "qfn_1_0_glColor3us") == 0) return (void*)& qfn_1_0_glColor3us;
	if (strcmp(name, "qfn_1_0_glColor3uiv") == 0) return (void*)& qfn_1_0_glColor3uiv;
	if (strcmp(name, "qfn_1_0_glColor3ui") == 0) return (void*)& qfn_1_0_glColor3ui;
	if (strcmp(name, "qfn_1_0_glColor3ubv") == 0) return (void*)& qfn_1_0_glColor3ubv;
	if (strcmp(name, "qfn_1_0_glColor3ub") == 0) return (void*)& qfn_1_0_glColor3ub;
	if (strcmp(name, "qfn_1_0_glColor3sv") == 0) return (void*)& qfn_1_0_glColor3sv;
	if (strcmp(name, "qfn_1_0_glColor3s") == 0) return (void*)& qfn_1_0_glColor3s;
	if (strcmp(name, "qfn_1_0_glColor3iv") == 0) return (void*)& qfn_1_0_glColor3iv;
	if (strcmp(name, "qfn_1_0_glColor3i") == 0) return (void*)& qfn_1_0_glColor3i;
	if (strcmp(name, "qfn_1_0_glColor3fv") == 0) return (void*)& qfn_1_0_glColor3fv;
	if (strcmp(name, "qfn_1_0_glColor3f") == 0) return (void*)& qfn_1_0_glColor3f;
	if (strcmp(name, "qfn_1_0_glColor3dv") == 0) return (void*)& qfn_1_0_glColor3dv;
	if (strcmp(name, "qfn_1_0_glColor3d") == 0) return (void*)& qfn_1_0_glColor3d;
	if (strcmp(name, "qfn_1_0_glColor3bv") == 0) return (void*)& qfn_1_0_glColor3bv;
	if (strcmp(name, "qfn_1_0_glColor3b") == 0) return (void*)& qfn_1_0_glColor3b;
	if (strcmp(name, "qfn_1_0_glBitmap") == 0) return (void*)& qfn_1_0_glBitmap;
	if (strcmp(name, "qfn_1_0_glBegin") == 0) return (void*)& qfn_1_0_glBegin;
	if (strcmp(name, "qfn_1_0_glListBase") == 0) return (void*)& qfn_1_0_glListBase;
	if (strcmp(name, "qfn_1_0_glGenLists") == 0) return (void*)& qfn_1_0_glGenLists;
	if (strcmp(name, "qfn_1_0_glDeleteLists") == 0) return (void*)& qfn_1_0_glDeleteLists;
	if (strcmp(name, "qfn_1_0_glCallLists") == 0) return (void*)& qfn_1_0_glCallLists;
	if (strcmp(name, "qfn_1_0_glCallList") == 0) return (void*)& qfn_1_0_glCallList;
	if (strcmp(name, "qfn_1_0_glEndList") == 0) return (void*)& qfn_1_0_glEndList;
	if (strcmp(name, "qfn_1_0_glNewList") == 0) return (void*)& qfn_1_0_glNewList;

	if (strcmp(name, "qfn_1_1_glViewport") == 0) return (void*)& qfn_1_1_glViewport;
	if (strcmp(name, "qfn_1_1_glDepthRange") == 0) return (void*)& qfn_1_1_glDepthRange;
	if (strcmp(name, "qfn_1_1_glIsEnabled") == 0) return (void*)& qfn_1_1_glIsEnabled;
	if (strcmp(name, "qfn_1_1_glGetTexLevelParameteriv") == 0) return (void*)& qfn_1_1_glGetTexLevelParameteriv;
	if (strcmp(name, "qfn_1_1_glGetTexLevelParameterfv") == 0) return (void*)& qfn_1_1_glGetTexLevelParameterfv;
	if (strcmp(name, "qfn_1_1_glGetTexParameteriv") == 0) return (void*)& qfn_1_1_glGetTexParameteriv;
	if (strcmp(name, "qfn_1_1_glGetTexParameterfv") == 0) return (void*)& qfn_1_1_glGetTexParameterfv;
	if (strcmp(name, "qfn_1_1_glGetTexImage") == 0) return (void*)& qfn_1_1_glGetTexImage;
	if (strcmp(name, "qfn_1_1_glGetString") == 0) return (void*)& qfn_1_1_glGetString;
	if (strcmp(name, "qfn_1_1_glGetIntegerv") == 0) return (void*)& qfn_1_1_glGetIntegerv;
	if (strcmp(name, "qfn_1_1_glGetFloatv") == 0) return (void*)& qfn_1_1_glGetFloatv;
	if (strcmp(name, "qfn_1_1_glGetError") == 0) return (void*)& qfn_1_1_glGetError;
	if (strcmp(name, "qfn_1_1_glGetDoublev") == 0) return (void*)& qfn_1_1_glGetDoublev;
	if (strcmp(name, "qfn_1_1_glGetBooleanv") == 0) return (void*)& qfn_1_1_glGetBooleanv;
	if (strcmp(name, "qfn_1_1_glReadPixels") == 0) return (void*)& qfn_1_1_glReadPixels;
	if (strcmp(name, "qfn_1_1_glReadBuffer") == 0) return (void*)& qfn_1_1_glReadBuffer;
	if (strcmp(name, "qfn_1_1_glPixelStorei") == 0) return (void*)& qfn_1_1_glPixelStorei;
	if (strcmp(name, "qfn_1_1_glPixelStoref") == 0) return (void*)& qfn_1_1_glPixelStoref;
	if (strcmp(name, "qfn_1_1_glDepthFunc") == 0) return (void*)& qfn_1_1_glDepthFunc;
	if (strcmp(name, "qfn_1_1_glStencilOp") == 0) return (void*)& qfn_1_1_glStencilOp;
	if (strcmp(name, "qfn_1_1_glStencilFunc") == 0) return (void*)& qfn_1_1_glStencilFunc;
	if (strcmp(name, "qfn_1_1_glLogicOp") == 0) return (void*)& qfn_1_1_glLogicOp;
	if (strcmp(name, "qfn_1_1_glBlendFunc") == 0) return (void*)& qfn_1_1_glBlendFunc;
	if (strcmp(name, "qfn_1_1_glFlush") == 0) return (void*)& qfn_1_1_glFlush;
	if (strcmp(name, "qfn_1_1_glFinish") == 0) return (void*)& qfn_1_1_glFinish;
	if (strcmp(name, "qfn_1_1_glEnable") == 0) return (void*)& qfn_1_1_glEnable;
	if (strcmp(name, "qfn_1_1_glDisable") == 0) return (void*)& qfn_1_1_glDisable;
	if (strcmp(name, "qfn_1_1_glDepthMask") == 0) return (void*)& qfn_1_1_glDepthMask;
	if (strcmp(name, "qfn_1_1_glColorMask") == 0) return (void*)& qfn_1_1_glColorMask;
	if (strcmp(name, "qfn_1_1_glStencilMask") == 0) return (void*)& qfn_1_1_glStencilMask;
	if (strcmp(name, "qfn_1_1_glClearDepth") == 0) return (void*)& qfn_1_1_glClearDepth;
	if (strcmp(name, "qfn_1_1_glClearStencil") == 0) return (void*)& qfn_1_1_glClearStencil;
	if (strcmp(name, "qfn_1_1_glClearColor") == 0) return (void*)& qfn_1_1_glClearColor;
	if (strcmp(name, "qfn_1_1_glClear") == 0) return (void*)& qfn_1_1_glClear;
	if (strcmp(name, "qfn_1_1_glDrawBuffer") == 0) return (void*)& qfn_1_1_glDrawBuffer;
	if (strcmp(name, "qfn_1_1_glTexImage2D") == 0) return (void*)& qfn_1_1_glTexImage2D;
	if (strcmp(name, "qfn_1_1_glTexImage1D") == 0) return (void*)& qfn_1_1_glTexImage1D;
	if (strcmp(name, "qfn_1_1_glTexParameteriv") == 0) return (void*)& qfn_1_1_glTexParameteriv;
	if (strcmp(name, "qfn_1_1_glTexParameteri") == 0) return (void*)& qfn_1_1_glTexParameteri;
	if (strcmp(name, "qfn_1_1_glTexParameterfv") == 0) return (void*)& qfn_1_1_glTexParameterfv;
	if (strcmp(name, "qfn_1_1_glTexParameterf") == 0) return (void*)& qfn_1_1_glTexParameterf;
	if (strcmp(name, "qfn_1_1_glScissor") == 0) return (void*)& qfn_1_1_glScissor;
	if (strcmp(name, "qfn_1_1_glPolygonMode") == 0) return (void*)& qfn_1_1_glPolygonMode;
	if (strcmp(name, "qfn_1_1_glPointSize") == 0) return (void*)& qfn_1_1_glPointSize;
	if (strcmp(name, "qfn_1_1_glLineWidth") == 0) return (void*)& qfn_1_1_glLineWidth;
	if (strcmp(name, "qfn_1_1_glHint") == 0) return (void*)& qfn_1_1_glHint;
	if (strcmp(name, "qfn_1_1_glFrontFace") == 0) return (void*)& qfn_1_1_glFrontFace;
	if (strcmp(name, "qfn_1_1_glCullFace") == 0) return (void*)& qfn_1_1_glCullFace;
	if (strcmp(name, "qfn_1_1_glIndexubv") == 0) return (void*)& qfn_1_1_glIndexubv;
	if (strcmp(name, "qfn_1_1_glIndexub") == 0) return (void*)& qfn_1_1_glIndexub;
	if (strcmp(name, "qfn_1_1_glIsTexture") == 0) return (void*)& qfn_1_1_glIsTexture;
	if (strcmp(name, "qfn_1_1_glGenTextures") == 0) return (void*)& qfn_1_1_glGenTextures;
	if (strcmp(name, "qfn_1_1_glDeleteTextures") == 0) return (void*)& qfn_1_1_glDeleteTextures;
	if (strcmp(name, "qfn_1_1_glBindTexture") == 0) return (void*)& qfn_1_1_glBindTexture;
	if (strcmp(name, "qfn_1_1_glTexSubImage2D") == 0) return (void*)& qfn_1_1_glTexSubImage2D;
	if (strcmp(name, "qfn_1_1_glTexSubImage1D") == 0) return (void*)& qfn_1_1_glTexSubImage1D;
	if (strcmp(name, "qfn_1_1_glCopyTexSubImage2D") == 0) return (void*)& qfn_1_1_glCopyTexSubImage2D;
	if (strcmp(name, "qfn_1_1_glCopyTexSubImage1D") == 0) return (void*)& qfn_1_1_glCopyTexSubImage1D;
	if (strcmp(name, "qfn_1_1_glCopyTexImage2D") == 0) return (void*)& qfn_1_1_glCopyTexImage2D;
	if (strcmp(name, "qfn_1_1_glCopyTexImage1D") == 0) return (void*)& qfn_1_1_glCopyTexImage1D;
	if (strcmp(name, "qfn_1_1_glPolygonOffset") == 0) return (void*)& qfn_1_1_glPolygonOffset;
	if (strcmp(name, "qfn_1_1_glGetPointerv") == 0) return (void*)& qfn_1_1_glGetPointerv;
	if (strcmp(name, "qfn_1_1_glDrawElements") == 0) return (void*)& qfn_1_1_glDrawElements;
	if (strcmp(name, "qfn_1_1_glDrawArrays") == 0) return (void*)& qfn_1_1_glDrawArrays;
	if (strcmp(name, "qfn_1_1_glTranslatef") == 0) return (void*)& qfn_1_1_glTranslatef;
	if (strcmp(name, "qfn_1_1_glTranslated") == 0) return (void*)& qfn_1_1_glTranslated;
	if (strcmp(name, "qfn_1_1_glScalef") == 0) return (void*)& qfn_1_1_glScalef;
	if (strcmp(name, "qfn_1_1_glScaled") == 0) return (void*)& qfn_1_1_glScaled;
	if (strcmp(name, "qfn_1_1_glRotatef") == 0) return (void*)& qfn_1_1_glRotatef;
	if (strcmp(name, "qfn_1_1_glRotated") == 0) return (void*)& qfn_1_1_glRotated;
	if (strcmp(name, "qfn_1_1_glPushMatrix") == 0) return (void*)& qfn_1_1_glPushMatrix;
	if (strcmp(name, "qfn_1_1_glPopMatrix") == 0) return (void*)& qfn_1_1_glPopMatrix;
	if (strcmp(name, "qfn_1_1_glOrtho") == 0) return (void*)& qfn_1_1_glOrtho;
	if (strcmp(name, "qfn_1_1_glMultMatrixd") == 0) return (void*)& qfn_1_1_glMultMatrixd;
	if (strcmp(name, "qfn_1_1_glMultMatrixf") == 0) return (void*)& qfn_1_1_glMultMatrixf;
	if (strcmp(name, "qfn_1_1_glMatrixMode") == 0) return (void*)& qfn_1_1_glMatrixMode;
	if (strcmp(name, "qfn_1_1_glLoadMatrixd") == 0) return (void*)& qfn_1_1_glLoadMatrixd;
	if (strcmp(name, "qfn_1_1_glLoadMatrixf") == 0) return (void*)& qfn_1_1_glLoadMatrixf;
	if (strcmp(name, "qfn_1_1_glLoadIdentity") == 0) return (void*)& qfn_1_1_glLoadIdentity;
	if (strcmp(name, "qfn_1_1_glFrustum") == 0) return (void*)& qfn_1_1_glFrustum;
	if (strcmp(name, "qfn_1_1_glIsList") == 0) return (void*)& qfn_1_1_glIsList;
	if (strcmp(name, "qfn_1_1_glGetTexGeniv") == 0) return (void*)& qfn_1_1_glGetTexGeniv;
	if (strcmp(name, "qfn_1_1_glGetTexGenfv") == 0) return (void*)& qfn_1_1_glGetTexGenfv;
	if (strcmp(name, "qfn_1_1_glGetTexGendv") == 0) return (void*)& qfn_1_1_glGetTexGendv;
	if (strcmp(name, "qfn_1_1_glGetTexEnviv") == 0) return (void*)& qfn_1_1_glGetTexEnviv;
	if (strcmp(name, "qfn_1_1_glGetTexEnvfv") == 0) return (void*)& qfn_1_1_glGetTexEnvfv;
	if (strcmp(name, "qfn_1_1_glGetPolygonStipple") == 0) return (void*)& qfn_1_1_glGetPolygonStipple;
	if (strcmp(name, "qfn_1_1_glGetPixelMapusv") == 0) return (void*)& qfn_1_1_glGetPixelMapusv;
	if (strcmp(name, "qfn_1_1_glGetPixelMapuiv") == 0) return (void*)& qfn_1_1_glGetPixelMapuiv;
	if (strcmp(name, "qfn_1_1_glGetPixelMapfv") == 0) return (void*)& qfn_1_1_glGetPixelMapfv;
	if (strcmp(name, "qfn_1_1_glGetMaterialiv") == 0) return (void*)& qfn_1_1_glGetMaterialiv;
	if (strcmp(name, "qfn_1_1_glGetMaterialfv") == 0) return (void*)& qfn_1_1_glGetMaterialfv;
	if (strcmp(name, "qfn_1_1_glGetMapiv") == 0) return (void*)& qfn_1_1_glGetMapiv;
	if (strcmp(name, "qfn_1_1_glGetMapfv") == 0) return (void*)& qfn_1_1_glGetMapfv;
	if (strcmp(name, "qfn_1_1_glGetMapdv") == 0) return (void*)& qfn_1_1_glGetMapdv;
	if (strcmp(name, "qfn_1_1_glGetLightiv") == 0) return (void*)& qfn_1_1_glGetLightiv;
	if (strcmp(name, "qfn_1_1_glGetLightfv") == 0) return (void*)& qfn_1_1_glGetLightfv;
	if (strcmp(name, "qfn_1_1_glGetClipPlane") == 0) return (void*)& qfn_1_1_glGetClipPlane;
	if (strcmp(name, "qfn_1_1_glDrawPixels") == 0) return (void*)& qfn_1_1_glDrawPixels;
	if (strcmp(name, "qfn_1_1_glCopyPixels") == 0) return (void*)& qfn_1_1_glCopyPixels;
	if (strcmp(name, "qfn_1_1_glPixelMapusv") == 0) return (void*)& qfn_1_1_glPixelMapusv;
	if (strcmp(name, "qfn_1_1_glPixelMapuiv") == 0) return (void*)& qfn_1_1_glPixelMapuiv;
	if (strcmp(name, "qfn_1_1_glPixelMapfv") == 0) return (void*)& qfn_1_1_glPixelMapfv;
	if (strcmp(name, "qfn_1_1_glPixelTransferi") == 0) return (void*)& qfn_1_1_glPixelTransferi;
	if (strcmp(name, "qfn_1_1_glPixelTransferf") == 0) return (void*)& qfn_1_1_glPixelTransferf;
	if (strcmp(name, "qfn_1_1_glPixelZoom") == 0) return (void*)& qfn_1_1_glPixelZoom;
	if (strcmp(name, "qfn_1_1_glAlphaFunc") == 0) return (void*)& qfn_1_1_glAlphaFunc;
	if (strcmp(name, "qfn_1_1_glEvalPoint2") == 0) return (void*)& qfn_1_1_glEvalPoint2;
	if (strcmp(name, "qfn_1_1_glEvalMesh2") == 0) return (void*)& qfn_1_1_glEvalMesh2;
	if (strcmp(name, "qfn_1_1_glEvalPoint1") == 0) return (void*)& qfn_1_1_glEvalPoint1;
	if (strcmp(name, "qfn_1_1_glEvalMesh1") == 0) return (void*)& qfn_1_1_glEvalMesh1;
	if (strcmp(name, "qfn_1_1_glEvalCoord2fv") == 0) return (void*)& qfn_1_1_glEvalCoord2fv;
	if (strcmp(name, "qfn_1_1_glEvalCoord2f") == 0) return (void*)& qfn_1_1_glEvalCoord2f;
	if (strcmp(name, "qfn_1_1_glEvalCoord2dv") == 0) return (void*)& qfn_1_1_glEvalCoord2dv;
	if (strcmp(name, "qfn_1_1_glEvalCoord2d") == 0) return (void*)& qfn_1_1_glEvalCoord2d;
	if (strcmp(name, "qfn_1_1_glEvalCoord1fv") == 0) return (void*)& qfn_1_1_glEvalCoord1fv;
	if (strcmp(name, "qfn_1_1_glEvalCoord1f") == 0) return (void*)& qfn_1_1_glEvalCoord1f;
	if (strcmp(name, "qfn_1_1_glEvalCoord1dv") == 0) return (void*)& qfn_1_1_glEvalCoord1dv;
	if (strcmp(name, "qfn_1_1_glEvalCoord1d") == 0) return (void*)& qfn_1_1_glEvalCoord1d;
	if (strcmp(name, "qfn_1_1_glMapGrid2f") == 0) return (void*)& qfn_1_1_glMapGrid2f;
	if (strcmp(name, "qfn_1_1_glMapGrid2d") == 0) return (void*)& qfn_1_1_glMapGrid2d;
	if (strcmp(name, "qfn_1_1_glMapGrid1f") == 0) return (void*)& qfn_1_1_glMapGrid1f;
	if (strcmp(name, "qfn_1_1_glMapGrid1d") == 0) return (void*)& qfn_1_1_glMapGrid1d;
	if (strcmp(name, "qfn_1_1_glMap2f") == 0) return (void*)& qfn_1_1_glMap2f;
	if (strcmp(name, "qfn_1_1_glMap2d") == 0) return (void*)& qfn_1_1_glMap2d;
	if (strcmp(name, "qfn_1_1_glMap1f") == 0) return (void*)& qfn_1_1_glMap1f;
	if (strcmp(name, "qfn_1_1_glMap1d") == 0) return (void*)& qfn_1_1_glMap1d;
	if (strcmp(name, "qfn_1_1_glPushAttrib") == 0) return (void*)& qfn_1_1_glPushAttrib;
	if (strcmp(name, "qfn_1_1_glPopAttrib") == 0) return (void*)& qfn_1_1_glPopAttrib;
	if (strcmp(name, "qfn_1_1_glAccum") == 0) return (void*)& qfn_1_1_glAccum;
	if (strcmp(name, "qfn_1_1_glIndexMask") == 0) return (void*)& qfn_1_1_glIndexMask;
	if (strcmp(name, "qfn_1_1_glClearIndex") == 0) return (void*)& qfn_1_1_glClearIndex;
	if (strcmp(name, "qfn_1_1_glClearAccum") == 0) return (void*)& qfn_1_1_glClearAccum;
	if (strcmp(name, "qfn_1_1_glPushName") == 0) return (void*)& qfn_1_1_glPushName;
	if (strcmp(name, "qfn_1_1_glPopName") == 0) return (void*)& qfn_1_1_glPopName;
	if (strcmp(name, "qfn_1_1_glPassThrough") == 0) return (void*)& qfn_1_1_glPassThrough;
	if (strcmp(name, "qfn_1_1_glLoadName") == 0) return (void*)& qfn_1_1_glLoadName;
	if (strcmp(name, "qfn_1_1_glInitNames") == 0) return (void*)& qfn_1_1_glInitNames;
	if (strcmp(name, "qfn_1_1_glRenderMode") == 0) return (void*)& qfn_1_1_glRenderMode;
	if (strcmp(name, "qfn_1_1_glSelectBuffer") == 0) return (void*)& qfn_1_1_glSelectBuffer;
	if (strcmp(name, "qfn_1_1_glFeedbackBuffer") == 0) return (void*)& qfn_1_1_glFeedbackBuffer;
	if (strcmp(name, "qfn_1_1_glTexGeniv") == 0) return (void*)& qfn_1_1_glTexGeniv;
	if (strcmp(name, "qfn_1_1_glTexGeni") == 0) return (void*)& qfn_1_1_glTexGeni;
	if (strcmp(name, "qfn_1_1_glTexGenfv") == 0) return (void*)& qfn_1_1_glTexGenfv;
	if (strcmp(name, "qfn_1_1_glTexGenf") == 0) return (void*)& qfn_1_1_glTexGenf;
	if (strcmp(name, "qfn_1_1_glTexGendv") == 0) return (void*)& qfn_1_1_glTexGendv;
	if (strcmp(name, "qfn_1_1_glTexGend") == 0) return (void*)& qfn_1_1_glTexGend;
	if (strcmp(name, "qfn_1_1_glTexEnviv") == 0) return (void*)& qfn_1_1_glTexEnviv;
	if (strcmp(name, "qfn_1_1_glTexEnvi") == 0) return (void*)& qfn_1_1_glTexEnvi;
	if (strcmp(name, "qfn_1_1_glTexEnvfv") == 0) return (void*)& qfn_1_1_glTexEnvfv;
	if (strcmp(name, "qfn_1_1_glTexEnvf") == 0) return (void*)& qfn_1_1_glTexEnvf;
	if (strcmp(name, "qfn_1_1_glShadeModel") == 0) return (void*)& qfn_1_1_glShadeModel;
	if (strcmp(name, "qfn_1_1_glPolygonStipple") == 0) return (void*)& qfn_1_1_glPolygonStipple;
	if (strcmp(name, "qfn_1_1_glMaterialiv") == 0) return (void*)& qfn_1_1_glMaterialiv;
	if (strcmp(name, "qfn_1_1_glMateriali") == 0) return (void*)& qfn_1_1_glMateriali;
	if (strcmp(name, "qfn_1_1_glMaterialfv") == 0) return (void*)& qfn_1_1_glMaterialfv;
	if (strcmp(name, "qfn_1_1_glMaterialf") == 0) return (void*)& qfn_1_1_glMaterialf;
	if (strcmp(name, "qfn_1_1_glLineStipple") == 0) return (void*)& qfn_1_1_glLineStipple;
	if (strcmp(name, "qfn_1_1_glLightModeliv") == 0) return (void*)& qfn_1_1_glLightModeliv;
	if (strcmp(name, "qfn_1_1_glLightModeli") == 0) return (void*)& qfn_1_1_glLightModeli;
	if (strcmp(name, "qfn_1_1_glLightModelfv") == 0) return (void*)& qfn_1_1_glLightModelfv;
	if (strcmp(name, "qfn_1_1_glLightModelf") == 0) return (void*)& qfn_1_1_glLightModelf;
	if (strcmp(name, "qfn_1_1_glLightiv") == 0) return (void*)& qfn_1_1_glLightiv;
	if (strcmp(name, "qfn_1_1_glLighti") == 0) return (void*)& qfn_1_1_glLighti;
	if (strcmp(name, "qfn_1_1_glLightfv") == 0) return (void*)& qfn_1_1_glLightfv;
	if (strcmp(name, "qfn_1_1_glLightf") == 0) return (void*)& qfn_1_1_glLightf;
	if (strcmp(name, "qfn_1_1_glFogiv") == 0) return (void*)& qfn_1_1_glFogiv;
	if (strcmp(name, "qfn_1_1_glFogi") == 0) return (void*)& qfn_1_1_glFogi;
	if (strcmp(name, "qfn_1_1_glFogfv") == 0) return (void*)& qfn_1_1_glFogfv;
	if (strcmp(name, "qfn_1_1_glFogf") == 0) return (void*)& qfn_1_1_glFogf;
	if (strcmp(name, "qfn_1_1_glColorMaterial") == 0) return (void*)& qfn_1_1_glColorMaterial;
	if (strcmp(name, "qfn_1_1_glClipPlane") == 0) return (void*)& qfn_1_1_glClipPlane;
	if (strcmp(name, "qfn_1_1_glVertex4sv") == 0) return (void*)& qfn_1_1_glVertex4sv;
	if (strcmp(name, "qfn_1_1_glVertex4s") == 0) return (void*)& qfn_1_1_glVertex4s;
	if (strcmp(name, "qfn_1_1_glVertex4iv") == 0) return (void*)& qfn_1_1_glVertex4iv;
	if (strcmp(name, "qfn_1_1_glVertex4i") == 0) return (void*)& qfn_1_1_glVertex4i;
	if (strcmp(name, "qfn_1_1_glVertex4fv") == 0) return (void*)& qfn_1_1_glVertex4fv;
	if (strcmp(name, "qfn_1_1_glVertex4f") == 0) return (void*)& qfn_1_1_glVertex4f;
	if (strcmp(name, "qfn_1_1_glVertex4dv") == 0) return (void*)& qfn_1_1_glVertex4dv;
	if (strcmp(name, "qfn_1_1_glVertex4d") == 0) return (void*)& qfn_1_1_glVertex4d;
	if (strcmp(name, "qfn_1_1_glVertex3sv") == 0) return (void*)& qfn_1_1_glVertex3sv;
	if (strcmp(name, "qfn_1_1_glVertex3s") == 0) return (void*)& qfn_1_1_glVertex3s;
	if (strcmp(name, "qfn_1_1_glVertex3iv") == 0) return (void*)& qfn_1_1_glVertex3iv;
	if (strcmp(name, "qfn_1_1_glVertex3i") == 0) return (void*)& qfn_1_1_glVertex3i;
	if (strcmp(name, "qfn_1_1_glVertex3fv") == 0) return (void*)& qfn_1_1_glVertex3fv;
	if (strcmp(name, "qfn_1_1_glVertex3f") == 0) return (void*)& qfn_1_1_glVertex3f;
	if (strcmp(name, "qfn_1_1_glVertex3dv") == 0) return (void*)& qfn_1_1_glVertex3dv;
	if (strcmp(name, "qfn_1_1_glVertex3d") == 0) return (void*)& qfn_1_1_glVertex3d;
	if (strcmp(name, "qfn_1_1_glVertex2sv") == 0) return (void*)& qfn_1_1_glVertex2sv;
	if (strcmp(name, "qfn_1_1_glVertex2s") == 0) return (void*)& qfn_1_1_glVertex2s;
	if (strcmp(name, "qfn_1_1_glVertex2iv") == 0) return (void*)& qfn_1_1_glVertex2iv;
	if (strcmp(name, "qfn_1_1_glVertex2i") == 0) return (void*)& qfn_1_1_glVertex2i;
	if (strcmp(name, "qfn_1_1_glVertex2fv") == 0) return (void*)& qfn_1_1_glVertex2fv;
	if (strcmp(name, "qfn_1_1_glVertex2f") == 0) return (void*)& qfn_1_1_glVertex2f;
	if (strcmp(name, "qfn_1_1_glVertex2dv") == 0) return (void*)& qfn_1_1_glVertex2dv;
	if (strcmp(name, "qfn_1_1_glVertex2d") == 0) return (void*)& qfn_1_1_glVertex2d;
	if (strcmp(name, "qfn_1_1_glTexCoord4sv") == 0) return (void*)& qfn_1_1_glTexCoord4sv;
	if (strcmp(name, "qfn_1_1_glTexCoord4s") == 0) return (void*)& qfn_1_1_glTexCoord4s;
	if (strcmp(name, "qfn_1_1_glTexCoord4iv") == 0) return (void*)& qfn_1_1_glTexCoord4iv;
	if (strcmp(name, "qfn_1_1_glTexCoord4i") == 0) return (void*)& qfn_1_1_glTexCoord4i;
	if (strcmp(name, "qfn_1_1_glTexCoord4fv") == 0) return (void*)& qfn_1_1_glTexCoord4fv;
	if (strcmp(name, "qfn_1_1_glTexCoord4f") == 0) return (void*)& qfn_1_1_glTexCoord4f;
	if (strcmp(name, "qfn_1_1_glTexCoord4dv") == 0) return (void*)& qfn_1_1_glTexCoord4dv;
	if (strcmp(name, "qfn_1_1_glTexCoord4d") == 0) return (void*)& qfn_1_1_glTexCoord4d;
	if (strcmp(name, "qfn_1_1_glTexCoord3sv") == 0) return (void*)& qfn_1_1_glTexCoord3sv;
	if (strcmp(name, "qfn_1_1_glTexCoord3s") == 0) return (void*)& qfn_1_1_glTexCoord3s;
	if (strcmp(name, "qfn_1_1_glTexCoord3iv") == 0) return (void*)& qfn_1_1_glTexCoord3iv;
	if (strcmp(name, "qfn_1_1_glTexCoord3i") == 0) return (void*)& qfn_1_1_glTexCoord3i;
	if (strcmp(name, "qfn_1_1_glTexCoord3fv") == 0) return (void*)& qfn_1_1_glTexCoord3fv;
	if (strcmp(name, "qfn_1_1_glTexCoord3f") == 0) return (void*)& qfn_1_1_glTexCoord3f;
	if (strcmp(name, "qfn_1_1_glTexCoord3dv") == 0) return (void*)& qfn_1_1_glTexCoord3dv;
	if (strcmp(name, "qfn_1_1_glTexCoord3d") == 0) return (void*)& qfn_1_1_glTexCoord3d;
	if (strcmp(name, "qfn_1_1_glTexCoord2sv") == 0) return (void*)& qfn_1_1_glTexCoord2sv;
	if (strcmp(name, "qfn_1_1_glTexCoord2s") == 0) return (void*)& qfn_1_1_glTexCoord2s;
	if (strcmp(name, "qfn_1_1_glTexCoord2iv") == 0) return (void*)& qfn_1_1_glTexCoord2iv;
	if (strcmp(name, "qfn_1_1_glTexCoord2i") == 0) return (void*)& qfn_1_1_glTexCoord2i;
	if (strcmp(name, "qfn_1_1_glTexCoord2fv") == 0) return (void*)& qfn_1_1_glTexCoord2fv;
	if (strcmp(name, "qfn_1_1_glTexCoord2f") == 0) return (void*)& qfn_1_1_glTexCoord2f;
	if (strcmp(name, "qfn_1_1_glTexCoord2dv") == 0) return (void*)& qfn_1_1_glTexCoord2dv;
	if (strcmp(name, "qfn_1_1_glTexCoord2d") == 0) return (void*)& qfn_1_1_glTexCoord2d;
	if (strcmp(name, "qfn_1_1_glTexCoord1sv") == 0) return (void*)& qfn_1_1_glTexCoord1sv;
	if (strcmp(name, "qfn_1_1_glTexCoord1s") == 0) return (void*)& qfn_1_1_glTexCoord1s;
	if (strcmp(name, "qfn_1_1_glTexCoord1iv") == 0) return (void*)& qfn_1_1_glTexCoord1iv;
	if (strcmp(name, "qfn_1_1_glTexCoord1i") == 0) return (void*)& qfn_1_1_glTexCoord1i;
	if (strcmp(name, "qfn_1_1_glTexCoord1fv") == 0) return (void*)& qfn_1_1_glTexCoord1fv;
	if (strcmp(name, "qfn_1_1_glTexCoord1f") == 0) return (void*)& qfn_1_1_glTexCoord1f;
	if (strcmp(name, "qfn_1_1_glTexCoord1dv") == 0) return (void*)& qfn_1_1_glTexCoord1dv;
	if (strcmp(name, "qfn_1_1_glTexCoord1d") == 0) return (void*)& qfn_1_1_glTexCoord1d;
	if (strcmp(name, "qfn_1_1_glRectsv") == 0) return (void*)& qfn_1_1_glRectsv;
	if (strcmp(name, "qfn_1_1_glRects") == 0) return (void*)& qfn_1_1_glRects;
	if (strcmp(name, "qfn_1_1_glRectiv") == 0) return (void*)& qfn_1_1_glRectiv;
	if (strcmp(name, "qfn_1_1_glRecti") == 0) return (void*)& qfn_1_1_glRecti;
	if (strcmp(name, "qfn_1_1_glRectfv") == 0) return (void*)& qfn_1_1_glRectfv;
	if (strcmp(name, "qfn_1_1_glRectf") == 0) return (void*)& qfn_1_1_glRectf;
	if (strcmp(name, "qfn_1_1_glRectdv") == 0) return (void*)& qfn_1_1_glRectdv;
	if (strcmp(name, "qfn_1_1_glRectd") == 0) return (void*)& qfn_1_1_glRectd;
	if (strcmp(name, "qfn_1_1_glRasterPos4sv") == 0) return (void*)& qfn_1_1_glRasterPos4sv;
	if (strcmp(name, "qfn_1_1_glRasterPos4s") == 0) return (void*)& qfn_1_1_glRasterPos4s;
	if (strcmp(name, "qfn_1_1_glRasterPos4iv") == 0) return (void*)& qfn_1_1_glRasterPos4iv;
	if (strcmp(name, "qfn_1_1_glRasterPos4i") == 0) return (void*)& qfn_1_1_glRasterPos4i;
	if (strcmp(name, "qfn_1_1_glRasterPos4fv") == 0) return (void*)& qfn_1_1_glRasterPos4fv;
	if (strcmp(name, "qfn_1_1_glRasterPos4f") == 0) return (void*)& qfn_1_1_glRasterPos4f;
	if (strcmp(name, "qfn_1_1_glRasterPos4dv") == 0) return (void*)& qfn_1_1_glRasterPos4dv;
	if (strcmp(name, "qfn_1_1_glRasterPos4d") == 0) return (void*)& qfn_1_1_glRasterPos4d;
	if (strcmp(name, "qfn_1_1_glRasterPos3sv") == 0) return (void*)& qfn_1_1_glRasterPos3sv;
	if (strcmp(name, "qfn_1_1_glRasterPos3s") == 0) return (void*)& qfn_1_1_glRasterPos3s;
	if (strcmp(name, "qfn_1_1_glRasterPos3iv") == 0) return (void*)& qfn_1_1_glRasterPos3iv;
	if (strcmp(name, "qfn_1_1_glRasterPos3i") == 0) return (void*)& qfn_1_1_glRasterPos3i;
	if (strcmp(name, "qfn_1_1_glRasterPos3fv") == 0) return (void*)& qfn_1_1_glRasterPos3fv;
	if (strcmp(name, "qfn_1_1_glRasterPos3f") == 0) return (void*)& qfn_1_1_glRasterPos3f;
	if (strcmp(name, "qfn_1_1_glRasterPos3dv") == 0) return (void*)& qfn_1_1_glRasterPos3dv;
	if (strcmp(name, "qfn_1_1_glRasterPos3d") == 0) return (void*)& qfn_1_1_glRasterPos3d;
	if (strcmp(name, "qfn_1_1_glRasterPos2sv") == 0) return (void*)& qfn_1_1_glRasterPos2sv;
	if (strcmp(name, "qfn_1_1_glRasterPos2s") == 0) return (void*)& qfn_1_1_glRasterPos2s;
	if (strcmp(name, "qfn_1_1_glRasterPos2iv") == 0) return (void*)& qfn_1_1_glRasterPos2iv;
	if (strcmp(name, "qfn_1_1_glRasterPos2i") == 0) return (void*)& qfn_1_1_glRasterPos2i;
	if (strcmp(name, "qfn_1_1_glRasterPos2fv") == 0) return (void*)& qfn_1_1_glRasterPos2fv;
	if (strcmp(name, "qfn_1_1_glRasterPos2f") == 0) return (void*)& qfn_1_1_glRasterPos2f;
	if (strcmp(name, "qfn_1_1_glRasterPos2dv") == 0) return (void*)& qfn_1_1_glRasterPos2dv;
	if (strcmp(name, "qfn_1_1_glRasterPos2d") == 0) return (void*)& qfn_1_1_glRasterPos2d;
	if (strcmp(name, "qfn_1_1_glNormal3sv") == 0) return (void*)& qfn_1_1_glNormal3sv;
	if (strcmp(name, "qfn_1_1_glNormal3s") == 0) return (void*)& qfn_1_1_glNormal3s;
	if (strcmp(name, "qfn_1_1_glNormal3iv") == 0) return (void*)& qfn_1_1_glNormal3iv;
	if (strcmp(name, "qfn_1_1_glNormal3i") == 0) return (void*)& qfn_1_1_glNormal3i;
	if (strcmp(name, "qfn_1_1_glNormal3fv") == 0) return (void*)& qfn_1_1_glNormal3fv;
	if (strcmp(name, "qfn_1_1_glNormal3f") == 0) return (void*)& qfn_1_1_glNormal3f;
	if (strcmp(name, "qfn_1_1_glNormal3dv") == 0) return (void*)& qfn_1_1_glNormal3dv;
	if (strcmp(name, "qfn_1_1_glNormal3d") == 0) return (void*)& qfn_1_1_glNormal3d;
	if (strcmp(name, "qfn_1_1_glNormal3bv") == 0) return (void*)& qfn_1_1_glNormal3bv;
	if (strcmp(name, "qfn_1_1_glNormal3b") == 0) return (void*)& qfn_1_1_glNormal3b;
	if (strcmp(name, "qfn_1_1_glIndexsv") == 0) return (void*)& qfn_1_1_glIndexsv;
	if (strcmp(name, "qfn_1_1_glIndexs") == 0) return (void*)& qfn_1_1_glIndexs;
	if (strcmp(name, "qfn_1_1_glIndexiv") == 0) return (void*)& qfn_1_1_glIndexiv;
	if (strcmp(name, "qfn_1_1_glIndexi") == 0) return (void*)& qfn_1_1_glIndexi;
	if (strcmp(name, "qfn_1_1_glIndexfv") == 0) return (void*)& qfn_1_1_glIndexfv;
	if (strcmp(name, "qfn_1_1_glIndexf") == 0) return (void*)& qfn_1_1_glIndexf;
	if (strcmp(name, "qfn_1_1_glIndexdv") == 0) return (void*)& qfn_1_1_glIndexdv;
	if (strcmp(name, "qfn_1_1_glIndexd") == 0) return (void*)& qfn_1_1_glIndexd;
	if (strcmp(name, "qfn_1_1_glEnd") == 0) return (void*)& qfn_1_1_glEnd;
	if (strcmp(name, "qfn_1_1_glEdgeFlagv") == 0) return (void*)& qfn_1_1_glEdgeFlagv;
	if (strcmp(name, "qfn_1_1_glEdgeFlag") == 0) return (void*)& qfn_1_1_glEdgeFlag;
	if (strcmp(name, "qfn_1_1_glColor4usv") == 0) return (void*)& qfn_1_1_glColor4usv;
	if (strcmp(name, "qfn_1_1_glColor4us") == 0) return (void*)& qfn_1_1_glColor4us;
	if (strcmp(name, "qfn_1_1_glColor4uiv") == 0) return (void*)& qfn_1_1_glColor4uiv;
	if (strcmp(name, "qfn_1_1_glColor4ui") == 0) return (void*)& qfn_1_1_glColor4ui;
	if (strcmp(name, "qfn_1_1_glColor4ubv") == 0) return (void*)& qfn_1_1_glColor4ubv;
	if (strcmp(name, "qfn_1_1_glColor4ub") == 0) return (void*)& qfn_1_1_glColor4ub;
	if (strcmp(name, "qfn_1_1_glColor4sv") == 0) return (void*)& qfn_1_1_glColor4sv;
	if (strcmp(name, "qfn_1_1_glColor4s") == 0) return (void*)& qfn_1_1_glColor4s;
	if (strcmp(name, "qfn_1_1_glColor4iv") == 0) return (void*)& qfn_1_1_glColor4iv;
	if (strcmp(name, "qfn_1_1_glColor4i") == 0) return (void*)& qfn_1_1_glColor4i;
	if (strcmp(name, "qfn_1_1_glColor4fv") == 0) return (void*)& qfn_1_1_glColor4fv;
	if (strcmp(name, "qfn_1_1_glColor4f") == 0) return (void*)& qfn_1_1_glColor4f;
	if (strcmp(name, "qfn_1_1_glColor4dv") == 0) return (void*)& qfn_1_1_glColor4dv;
	if (strcmp(name, "qfn_1_1_glColor4d") == 0) return (void*)& qfn_1_1_glColor4d;
	if (strcmp(name, "qfn_1_1_glColor4bv") == 0) return (void*)& qfn_1_1_glColor4bv;
	if (strcmp(name, "qfn_1_1_glColor4b") == 0) return (void*)& qfn_1_1_glColor4b;
	if (strcmp(name, "qfn_1_1_glColor3usv") == 0) return (void*)& qfn_1_1_glColor3usv;
	if (strcmp(name, "qfn_1_1_glColor3us") == 0) return (void*)& qfn_1_1_glColor3us;
	if (strcmp(name, "qfn_1_1_glColor3uiv") == 0) return (void*)& qfn_1_1_glColor3uiv;
	if (strcmp(name, "qfn_1_1_glColor3ui") == 0) return (void*)& qfn_1_1_glColor3ui;
	if (strcmp(name, "qfn_1_1_glColor3ubv") == 0) return (void*)& qfn_1_1_glColor3ubv;
	if (strcmp(name, "qfn_1_1_glColor3ub") == 0) return (void*)& qfn_1_1_glColor3ub;
	if (strcmp(name, "qfn_1_1_glColor3sv") == 0) return (void*)& qfn_1_1_glColor3sv;
	if (strcmp(name, "qfn_1_1_glColor3s") == 0) return (void*)& qfn_1_1_glColor3s;
	if (strcmp(name, "qfn_1_1_glColor3iv") == 0) return (void*)& qfn_1_1_glColor3iv;
	if (strcmp(name, "qfn_1_1_glColor3i") == 0) return (void*)& qfn_1_1_glColor3i;
	if (strcmp(name, "qfn_1_1_glColor3fv") == 0) return (void*)& qfn_1_1_glColor3fv;
	if (strcmp(name, "qfn_1_1_glColor3f") == 0) return (void*)& qfn_1_1_glColor3f;
	if (strcmp(name, "qfn_1_1_glColor3dv") == 0) return (void*)& qfn_1_1_glColor3dv;
	if (strcmp(name, "qfn_1_1_glColor3d") == 0) return (void*)& qfn_1_1_glColor3d;
	if (strcmp(name, "qfn_1_1_glColor3bv") == 0) return (void*)& qfn_1_1_glColor3bv;
	if (strcmp(name, "qfn_1_1_glColor3b") == 0) return (void*)& qfn_1_1_glColor3b;
	if (strcmp(name, "qfn_1_1_glBitmap") == 0) return (void*)& qfn_1_1_glBitmap;
	if (strcmp(name, "qfn_1_1_glBegin") == 0) return (void*)& qfn_1_1_glBegin;
	if (strcmp(name, "qfn_1_1_glListBase") == 0) return (void*)& qfn_1_1_glListBase;
	if (strcmp(name, "qfn_1_1_glGenLists") == 0) return (void*)& qfn_1_1_glGenLists;
	if (strcmp(name, "qfn_1_1_glDeleteLists") == 0) return (void*)& qfn_1_1_glDeleteLists;
	if (strcmp(name, "qfn_1_1_glCallLists") == 0) return (void*)& qfn_1_1_glCallLists;
	if (strcmp(name, "qfn_1_1_glCallList") == 0) return (void*)& qfn_1_1_glCallList;
	if (strcmp(name, "qfn_1_1_glEndList") == 0) return (void*)& qfn_1_1_glEndList;
	if (strcmp(name, "qfn_1_1_glNewList") == 0) return (void*)& qfn_1_1_glNewList;
	if (strcmp(name, "qfn_1_1_glPushClientAttrib") == 0) return (void*)& qfn_1_1_glPushClientAttrib;
	if (strcmp(name, "qfn_1_1_glPopClientAttrib") == 0) return (void*)& qfn_1_1_glPopClientAttrib;
	if (strcmp(name, "qfn_1_1_glPrioritizeTextures") == 0) return (void*)& qfn_1_1_glPrioritizeTextures;
	if (strcmp(name, "qfn_1_1_glAreTexturesResident") == 0) return (void*)& qfn_1_1_glAreTexturesResident;
	if (strcmp(name, "qfn_1_1_glVertexPointer") == 0) return (void*)& qfn_1_1_glVertexPointer;
	if (strcmp(name, "qfn_1_1_glTexCoordPointer") == 0) return (void*)& qfn_1_1_glTexCoordPointer;
	if (strcmp(name, "qfn_1_1_glNormalPointer") == 0) return (void*)& qfn_1_1_glNormalPointer;
    if (strcmp(name, "qfn_1_1_glInterleavedArrays") == 0) return (void*)& qfn_1_1_glInterleavedArrays;
	if (strcmp(name, "qfn_1_1_glIndexPointer") == 0) return (void*)& qfn_1_1_glIndexPointer;
	if (strcmp(name, "qfn_1_1_glEnableClientState") == 0) return (void*)& qfn_1_1_glEnableClientState;
	if (strcmp(name, "qfn_1_1_glEdgeFlagPointer") == 0) return (void*)& qfn_1_1_glEdgeFlagPointer;
	if (strcmp(name, "qfn_1_1_glDisableClientState") == 0) return (void*)& qfn_1_1_glDisableClientState;
	if (strcmp(name, "qfn_1_1_glColorPointer") == 0) return (void*)& qfn_1_1_glColorPointer;
	if (strcmp(name, "qfn_1_1_glArrayElement") == 0) return (void*)& qfn_1_1_glArrayElement;

	if (strcmp(name, "qfn_ES2_glActiveTexture") == 0) return (void*)& qfn_ES2_glActiveTexture;
	if (strcmp(name, "qfn_ES2_glAttachShader") == 0) return (void*)& qfn_ES2_glAttachShader;
	if (strcmp(name, "qfn_ES2_glBindAttribLocation") == 0) return (void*)& qfn_ES2_glBindAttribLocation;
	if (strcmp(name, "qfn_ES2_glBindBuffer") == 0) return (void*)& qfn_ES2_glBindBuffer;
	if (strcmp(name, "qfn_ES2_glBindFramebuffer") == 0) return (void*)& qfn_ES2_glBindFramebuffer;
	if (strcmp(name, "qfn_ES2_glBindRenderbuffer") == 0) return (void*)& qfn_ES2_glBindRenderbuffer;
	if (strcmp(name, "qfn_ES2_glBindTexture") == 0) return (void*)& qfn_ES2_glBindTexture;
	if (strcmp(name, "qfn_ES2_glBlendColor") == 0) return (void*)& qfn_ES2_glBlendColor;
	if (strcmp(name, "qfn_ES2_glBlendEquation") == 0) return (void*)& qfn_ES2_glBlendEquation;
	if (strcmp(name, "qfn_ES2_glBlendEquationSeparate") == 0) return (void*)& qfn_ES2_glBlendEquationSeparate;
	if (strcmp(name, "qfn_ES2_glBlendFunc") == 0) return (void*)& qfn_ES2_glBlendFunc;
	if (strcmp(name, "qfn_ES2_glBlendFuncSeparate") == 0) return (void*)& qfn_ES2_glBlendFuncSeparate;
	if (strcmp(name, "qfn_ES2_glBufferData") == 0) return (void*)& qfn_ES2_glBufferData;
	if (strcmp(name, "qfn_ES2_glBufferSubData") == 0) return (void*)& qfn_ES2_glBufferSubData;
	if (strcmp(name, "qfn_ES2_glCheckFramebufferStatus") == 0) return (void*)& qfn_ES2_glCheckFramebufferStatus;
	if (strcmp(name, "qfn_ES2_glClear") == 0) return (void*)& qfn_ES2_glClear;
	if (strcmp(name, "qfn_ES2_glClearColor") == 0) return (void*)& qfn_ES2_glClearColor;
	if (strcmp(name, "qfn_ES2_glClearDepthf") == 0) return (void*)& qfn_ES2_glClearDepthf;
	if (strcmp(name, "qfn_ES2_glClearStencil") == 0) return (void*)& qfn_ES2_glClearStencil;
	if (strcmp(name, "qfn_ES2_glColorMask") == 0) return (void*)& qfn_ES2_glColorMask;
	if (strcmp(name, "qfn_ES2_glCompileShader") == 0) return (void*)& qfn_ES2_glCompileShader;
	if (strcmp(name, "qfn_ES2_glCompressedTexImage2D") == 0) return (void*)& qfn_ES2_glCompressedTexImage2D;
	if (strcmp(name, "qfn_ES2_glCompressedTexSubImage2D") == 0) return (void*)& qfn_ES2_glCompressedTexSubImage2D;
	if (strcmp(name, "qfn_ES2_glCopyTexImage2D") == 0) return (void*)& qfn_ES2_glCopyTexImage2D;
	if (strcmp(name, "qfn_ES2_glCopyTexSubImage2D") == 0) return (void*)& qfn_ES2_glCopyTexSubImage2D;
	if (strcmp(name, "qfn_ES2_glCreateProgram") == 0) return (void*)& qfn_ES2_glCreateProgram;
	if (strcmp(name, "qfn_ES2_glCreateShader") == 0) return (void*)& qfn_ES2_glCreateShader;
	if (strcmp(name, "qfn_ES2_glCullFace") == 0) return (void*)& qfn_ES2_glCullFace;
	if (strcmp(name, "qfn_ES2_glDeleteBuffers") == 0) return (void*)& qfn_ES2_glDeleteBuffers;
	if (strcmp(name, "qfn_ES2_glDeleteFramebuffers") == 0) return (void*)& qfn_ES2_glDeleteFramebuffers;
	if (strcmp(name, "qfn_ES2_glDeleteProgram") == 0) return (void*)& qfn_ES2_glDeleteProgram;
	if (strcmp(name, "qfn_ES2_glDeleteRenderbuffers") == 0) return (void*)& qfn_ES2_glDeleteRenderbuffers;
	if (strcmp(name, "qfn_ES2_glDeleteShader") == 0) return (void*)& qfn_ES2_glDeleteShader;
	if (strcmp(name, "qfn_ES2_glDeleteTextures") == 0) return (void*)& qfn_ES2_glDeleteTextures;
	if (strcmp(name, "qfn_ES2_glDepthFunc") == 0) return (void*)& qfn_ES2_glDepthFunc;
	if (strcmp(name, "qfn_ES2_glDepthMask") == 0) return (void*)& qfn_ES2_glDepthMask;
	if (strcmp(name, "qfn_ES2_glDepthRangef") == 0) return (void*)& qfn_ES2_glDepthRangef;
	if (strcmp(name, "qfn_ES2_glDetachShader") == 0) return (void*)& qfn_ES2_glDetachShader;
	if (strcmp(name, "qfn_ES2_glDisable") == 0) return (void*)& qfn_ES2_glDisable;
	if (strcmp(name, "qfn_ES2_glDisableVertexAttribArray") == 0) return (void*)& qfn_ES2_glDisableVertexAttribArray;
	if (strcmp(name, "qfn_ES2_glDrawArrays") == 0) return (void*)& qfn_ES2_glDrawArrays;
	if (strcmp(name, "qfn_ES2_glDrawElements") == 0) return (void*)& qfn_ES2_glDrawElements;
	if (strcmp(name, "qfn_ES2_glEnable") == 0) return (void*)& qfn_ES2_glEnable;
	if (strcmp(name, "qfn_ES2_glEnableVertexAttribArray") == 0) return (void*)& qfn_ES2_glEnableVertexAttribArray;
	if (strcmp(name, "qfn_ES2_glFinish") == 0) return (void*)& qfn_ES2_glFinish;
	if (strcmp(name, "qfn_ES2_glFlush") == 0) return (void*)& qfn_ES2_glFlush;
	if (strcmp(name, "qfn_ES2_glFramebufferRenderbuffer") == 0) return (void*)& qfn_ES2_glFramebufferRenderbuffer;
	if (strcmp(name, "qfn_ES2_glFramebufferTexture2D") == 0) return (void*)& qfn_ES2_glFramebufferTexture2D;
	if (strcmp(name, "qfn_ES2_glFrontFace") == 0) return (void*)& qfn_ES2_glFrontFace;
	if (strcmp(name, "qfn_ES2_glGenBuffers") == 0) return (void*)& qfn_ES2_glGenBuffers;
	if (strcmp(name, "qfn_ES2_glGenerateMipmap") == 0) return (void*)& qfn_ES2_glGenerateMipmap;
	if (strcmp(name, "qfn_ES2_glGenFramebuffers") == 0) return (void*)& qfn_ES2_glGenFramebuffers;
	if (strcmp(name, "qfn_ES2_glGenRenderbuffers") == 0) return (void*)& qfn_ES2_glGenRenderbuffers;
	if (strcmp(name, "qfn_ES2_glGenTextures") == 0) return (void*)& qfn_ES2_glGenTextures;
	if (strcmp(name, "qfn_ES2_glGetActiveAttrib") == 0) return (void*)& qfn_ES2_glGetActiveAttrib;
	if (strcmp(name, "qfn_ES2_glGetActiveUniform") == 0) return (void*)& qfn_ES2_glGetActiveUniform;
	if (strcmp(name, "qfn_ES2_glGetAttachedShaders") == 0) return (void*)& qfn_ES2_glGetAttachedShaders;
	if (strcmp(name, "qfn_ES2_glGetAttribLocation") == 0) return (void*)& qfn_ES2_glGetAttribLocation;
	if (strcmp(name, "qfn_ES2_glGetBooleanv") == 0) return (void*)& qfn_ES2_glGetBooleanv;
	if (strcmp(name, "qfn_ES2_glGetBufferParameteriv") == 0) return (void*)& qfn_ES2_glGetBufferParameteriv;
	if (strcmp(name, "qfn_ES2_glGetError") == 0) return (void*)& qfn_ES2_glGetError;
	if (strcmp(name, "qfn_ES2_glGetFloatv") == 0) return (void*)& qfn_ES2_glGetFloatv;
	if (strcmp(name, "qfn_ES2_glGetFramebufferAttachmentParameteriv") == 0) return (void*)& qfn_ES2_glGetFramebufferAttachmentParameteriv;
	if (strcmp(name, "qfn_ES2_glGetIntegerv") == 0) return (void*)& qfn_ES2_glGetIntegerv;
	if (strcmp(name, "qfn_ES2_glGetProgramiv") == 0) return (void*)& qfn_ES2_glGetProgramiv;
	if (strcmp(name, "qfn_ES2_glGetProgramInfoLog") == 0) return (void*)& qfn_ES2_glGetProgramInfoLog;
	if (strcmp(name, "qfn_ES2_glGetRenderbufferParameteriv") == 0) return (void*)& qfn_ES2_glGetRenderbufferParameteriv;
	if (strcmp(name, "qfn_ES2_glGetShaderiv") == 0) return (void*)& qfn_ES2_glGetShaderiv;
	if (strcmp(name, "qfn_ES2_glGetShaderInfoLog") == 0) return (void*)& qfn_ES2_glGetShaderInfoLog;
	if (strcmp(name, "qfn_ES2_glGetShaderPrecisionFormat") == 0) return (void*)& qfn_ES2_glGetShaderPrecisionFormat;
	if (strcmp(name, "qfn_ES2_glGetShaderSource") == 0) return (void*)& qfn_ES2_glGetShaderSource;
	if (strcmp(name, "qfn_ES2_glGetString") == 0) return (void*)& qfn_ES2_glGetString;
	if (strcmp(name, "qfn_ES2_glGetTexParameterfv") == 0) return (void*)& qfn_ES2_glGetTexParameterfv;
	if (strcmp(name, "qfn_ES2_glGetTexParameteriv") == 0) return (void*)& qfn_ES2_glGetTexParameteriv;
	if (strcmp(name, "qfn_ES2_glGetUniformfv") == 0) return (void*)& qfn_ES2_glGetUniformfv;
	if (strcmp(name, "qfn_ES2_glGetUniformiv") == 0) return (void*)& qfn_ES2_glGetUniformiv;
	if (strcmp(name, "qfn_ES2_glGetUniformLocation") == 0) return (void*)& qfn_ES2_glGetUniformLocation;
	if (strcmp(name, "qfn_ES2_glGetVertexAttribfv") == 0) return (void*)& qfn_ES2_glGetVertexAttribfv;
	if (strcmp(name, "qfn_ES2_glGetVertexAttribiv") == 0) return (void*)& qfn_ES2_glGetVertexAttribiv;
	if (strcmp(name, "qfn_ES2_glGetVertexAttribPointerv") == 0) return (void*)& qfn_ES2_glGetVertexAttribPointerv;
	if (strcmp(name, "qfn_ES2_glHint") == 0) return (void*)& qfn_ES2_glHint;
	if (strcmp(name, "qfn_ES2_glIsBuffer") == 0) return (void*)& qfn_ES2_glIsBuffer;
	if (strcmp(name, "qfn_ES2_glIsEnabled") == 0) return (void*)& qfn_ES2_glIsEnabled;
	if (strcmp(name, "qfn_ES2_glIsFramebuffer") == 0) return (void*)& qfn_ES2_glIsFramebuffer;
	if (strcmp(name, "qfn_ES2_glIsProgram") == 0) return (void*)& qfn_ES2_glIsProgram;
	if (strcmp(name, "qfn_ES2_glIsRenderbuffer") == 0) return (void*)& qfn_ES2_glIsRenderbuffer;
	if (strcmp(name, "qfn_ES2_glIsShader") == 0) return (void*)& qfn_ES2_glIsShader;
	if (strcmp(name, "qfn_ES2_glIsTexture") == 0) return (void*)& qfn_ES2_glIsTexture;
	if (strcmp(name, "qfn_ES2_glLineWidth") == 0) return (void*)& qfn_ES2_glLineWidth;
	if (strcmp(name, "qfn_ES2_glLinkProgram") == 0) return (void*)& qfn_ES2_glLinkProgram;
	if (strcmp(name, "qfn_ES2_glPixelStorei") == 0) return (void*)& qfn_ES2_glPixelStorei;
	if (strcmp(name, "qfn_ES2_glPolygonOffset") == 0) return (void*)& qfn_ES2_glPolygonOffset;
	if (strcmp(name, "qfn_ES2_glReadPixels") == 0) return (void*)& qfn_ES2_glReadPixels;
	if (strcmp(name, "qfn_ES2_glReleaseShaderCompiler") == 0) return (void*)& qfn_ES2_glReleaseShaderCompiler;
	if (strcmp(name, "qfn_ES2_glRenderbufferStorage") == 0) return (void*)& qfn_ES2_glRenderbufferStorage;
	if (strcmp(name, "qfn_ES2_glSampleCoverage") == 0) return (void*)& qfn_ES2_glSampleCoverage;
	if (strcmp(name, "qfn_ES2_glScissor") == 0) return (void*)& qfn_ES2_glScissor;
	if (strcmp(name, "qfn_ES2_glShaderBinary") == 0) return (void*)& qfn_ES2_glShaderBinary;
	if (strcmp(name, "qfn_ES2_glShaderSource") == 0) return (void*)& qfn_ES2_glShaderSource;
	if (strcmp(name, "qfn_ES2_glStencilFunc") == 0) return (void*)& qfn_ES2_glStencilFunc;
	if (strcmp(name, "qfn_ES2_glStencilFuncSeparate") == 0) return (void*)& qfn_ES2_glStencilFuncSeparate;
	if (strcmp(name, "qfn_ES2_glStencilMask") == 0) return (void*)& qfn_ES2_glStencilMask;
	if (strcmp(name, "qfn_ES2_glStencilMaskSeparate") == 0) return (void*)& qfn_ES2_glStencilMaskSeparate;
	if (strcmp(name, "qfn_ES2_glStencilOp") == 0) return (void*)& qfn_ES2_glStencilOp;
	if (strcmp(name, "qfn_ES2_glStencilOpSeparate") == 0) return (void*)& qfn_ES2_glStencilOpSeparate;
	if (strcmp(name, "qfn_ES2_glTexImage2D") == 0) return (void*)& qfn_ES2_glTexImage2D;
	if (strcmp(name, "qfn_ES2_glTexParameterf") == 0) return (void*)& qfn_ES2_glTexParameterf;
	if (strcmp(name, "qfn_ES2_glTexParameterfv") == 0) return (void*)& qfn_ES2_glTexParameterfv;
	if (strcmp(name, "qfn_ES2_glTexParameteri") == 0) return (void*)& qfn_ES2_glTexParameteri;
	if (strcmp(name, "qfn_ES2_glTexParameteriv") == 0) return (void*)& qfn_ES2_glTexParameteriv;
	if (strcmp(name, "qfn_ES2_glTexSubImage2D") == 0) return (void*)& qfn_ES2_glTexSubImage2D;
	if (strcmp(name, "qfn_ES2_glUniform1f") == 0) return (void*)& qfn_ES2_glUniform1f;
	if (strcmp(name, "qfn_ES2_glUniform1fv") == 0) return (void*)& qfn_ES2_glUniform1fv;
	if (strcmp(name, "qfn_ES2_glUniform1i") == 0) return (void*)& qfn_ES2_glUniform1i;
	if (strcmp(name, "qfn_ES2_glUniform1iv") == 0) return (void*)& qfn_ES2_glUniform1iv;
	if (strcmp(name, "qfn_ES2_glUniform2f") == 0) return (void*)& qfn_ES2_glUniform2f;
	if (strcmp(name, "qfn_ES2_glUniform2fv") == 0) return (void*)& qfn_ES2_glUniform2fv;
	if (strcmp(name, "qfn_ES2_glUniform2i") == 0) return (void*)& qfn_ES2_glUniform2i;
	if (strcmp(name, "qfn_ES2_glUniform2iv") == 0) return (void*)& qfn_ES2_glUniform2iv;
	if (strcmp(name, "qfn_ES2_glUniform3f") == 0) return (void*)& qfn_ES2_glUniform3f;
	if (strcmp(name, "qfn_ES2_glUniform3fv") == 0) return (void*)& qfn_ES2_glUniform3fv;
	if (strcmp(name, "qfn_ES2_glUniform3i") == 0) return (void*)& qfn_ES2_glUniform3i;
	if (strcmp(name, "qfn_ES2_glUniform3iv") == 0) return (void*)& qfn_ES2_glUniform3iv;
	if (strcmp(name, "qfn_ES2_glUniform4f") == 0) return (void*)& qfn_ES2_glUniform4f;
	if (strcmp(name, "qfn_ES2_glUniform4fv") == 0) return (void*)& qfn_ES2_glUniform4fv;
	if (strcmp(name, "qfn_ES2_glUniform4i") == 0) return (void*)& qfn_ES2_glUniform4i;
	if (strcmp(name, "qfn_ES2_glUniform4iv") == 0) return (void*)& qfn_ES2_glUniform4iv;
	if (strcmp(name, "qfn_ES2_glUniformMatrix2fv") == 0) return (void*)& qfn_ES2_glUniformMatrix2fv;
	if (strcmp(name, "qfn_ES2_glUniformMatrix3fv") == 0) return (void*)& qfn_ES2_glUniformMatrix3fv;
	if (strcmp(name, "qfn_ES2_glUniformMatrix4fv") == 0) return (void*)& qfn_ES2_glUniformMatrix4fv;
	if (strcmp(name, "qfn_ES2_glUseProgram") == 0) return (void*)& qfn_ES2_glUseProgram;
	if (strcmp(name, "qfn_ES2_glValidateProgram") == 0) return (void*)& qfn_ES2_glValidateProgram;
	if (strcmp(name, "qfn_ES2_glVertexAttrib1f") == 0) return (void*)& qfn_ES2_glVertexAttrib1f;
	if (strcmp(name, "qfn_ES2_glVertexAttrib1fv") == 0) return (void*)& qfn_ES2_glVertexAttrib1fv;
	if (strcmp(name, "qfn_ES2_glVertexAttrib2f") == 0) return (void*)& qfn_ES2_glVertexAttrib2f;
	if (strcmp(name, "qfn_ES2_glVertexAttrib2fv") == 0) return (void*)& qfn_ES2_glVertexAttrib2fv;
	if (strcmp(name, "qfn_ES2_glVertexAttrib3f") == 0) return (void*)& qfn_ES2_glVertexAttrib3f;
	if (strcmp(name, "qfn_ES2_glVertexAttrib3fv") == 0) return (void*)& qfn_ES2_glVertexAttrib3fv;
	if (strcmp(name, "qfn_ES2_glVertexAttrib4f") == 0) return (void*)& qfn_ES2_glVertexAttrib4f;
	if (strcmp(name, "qfn_ES2_glVertexAttrib4fv") == 0) return (void*)& qfn_ES2_glVertexAttrib4fv;
	if (strcmp(name, "qfn_ES2_glVertexAttribPointer") == 0) return (void*)& qfn_ES2_glVertexAttribPointer;
	if (strcmp(name, "qfn_ES2_glViewport") == 0) return (void*)& qfn_ES2_glViewport;
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
