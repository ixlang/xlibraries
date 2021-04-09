#pragma once
#include <QObject>
#include "qxlibrary_global.h"


extern XIDENT * methodIdent;

class XUILoader :public  QUiLoader {
	Q_OBJECT
public:
	explicit XUILoader(QObject *parent = Q_NULLPTR) 
		:QUiLoader(parent){

	}

	virtual ~XUILoader() {

	}

	virtual QWidget *createWidget(const QString &className, QWidget *parent = Q_NULLPTR, const QString &name = QString());
};

#if !defined(QT_NO_OPENGL)
class XOpenGLWidget :
	public QOpenGLWidget {
	Q_OBJECT
public:
	explicit XOpenGLWidget(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags()) :
		QOpenGLWidget(parent, f){

	}

	virtual void initializeGL() Q_DECL_OVERRIDE {
		XMetaPtr objectData = (this->property(XHANDLE).GETPROPERTY_VALUE);
		if (objectData != NULL) {
			if (objectData->getObject() != 0) {
				XThread thread;
				gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[QOpenGLWidget_initializeGL].methodId);
			}
		}
	}

	virtual void resizeGL(int w, int h) Q_DECL_OVERRIDE {
		XMetaPtr objectData = (this->property(XHANDLE).GETPROPERTY_VALUE);
		if (objectData != NULL) {
			if (objectData->getObject() != 0) {
				XThread thread;
				gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[QOpenGLWidget_resizeGL].methodId, w, h);
			}
		}
	}

	virtual void paintGL() Q_DECL_OVERRIDE {
		XMetaPtr objectData = (this->property(XHANDLE).GETPROPERTY_VALUE);
		if (objectData != NULL) {
			if (objectData->getObject() != 0) {
				XThread thread;
				gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[QOpenGLWidget_paintGL].methodId);
			}
		}
	}

};
#endif

class XAudioOutput : 
	public QAudioOutput {
	QIODevice * outputdevice = 0;

public:
	XAudioOutput(const QAudioFormat &format = QAudioFormat(), QObject *parent = Q_NULLPTR)
	:QAudioOutput(format, parent){

	}

	bool start() {
		outputdevice = QAudioOutput::start();
		if (outputdevice != 0) {
			outputdevice->open(QIODevice::WriteOnly);
		}
		return outputdevice != 0;
	}

	xlong write(const char * data, int len) {
		if (outputdevice != 0) {
			return outputdevice->write(data, len);
		}
		return 0;
	}

	void stop() {
		if (outputdevice != 0) {
			QAudioOutput::stop();
			outputdevice = 0;
		}
	}

};

class XAudioInput :
	public QAudioInput {
	QIODevice * outputdevice = 0;

public:
	XAudioInput(const QAudioFormat &format = QAudioFormat(), QObject *parent = Q_NULLPTR)
		:QAudioInput(format, parent) {

	}

	bool start() {
		outputdevice = QAudioInput::start();
		if (outputdevice != 0) {
			outputdevice->open(QIODevice::ReadOnly);
		}
		return outputdevice != 0;
	}

	xlong read(char * data, int len) {
		if (outputdevice != 0) {
			return outputdevice->read(data, len);
		}
		return 0;
	}

	void stop() {
		if (outputdevice != 0) {
			QAudioInput::stop();
			outputdevice = 0;
		}
	}

};

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

        XMetaPtr objectData =(act->property(XHANDLE).GETPROPERTY_VALUE);
		QString st = act->objectName();
		if (objectData != NULL) {
			if (objectData->getObject() != 0) {
				XThread thread;
				gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[TRIGGER_ID].methodId);
			}
		}

		return true;
	}

	void on_windowStateChanged(Qt::WindowStates oldState, Qt::WindowStates newState) {
		QMdiSubWindow * obj = qobject_cast <QMdiSubWindow*>(sender());
		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[105].methodId, (xint)oldState, (xint)newState);
				}
			}
		}


	}

	void qmp_notifyIntervalChanged(int milliSeconds) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaObject_notifyIntervalChanged].methodId, milliSeconds);
				}
			}
		}
	}

	void qmp_metaDataAvailableChanged(bool available){
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaObject_metaDataAvailableChanged].methodId, available);
				}
			}
		}
	}

	void qmp_metaDataChanged() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaObject_metaDataChanged].methodId);
				}
			}
		}
	}

	void qmp_availabilityChanged(bool available) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaObject_availabilityChanged].methodId, available);
				}
			}
		}
	}

	void qmp_availabilityChanged(QMultimedia::AvailabilityStatus availability) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaObject_availabilityChanged1].methodId, (xint)availability);
				}
			}
		}
	}

	void qvw_fullScreenChanged(bool fullScreen) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[QVideoWidget_fullScreenChanged].methodId, fullScreen);
				}
			}
		}
	}

	void qao_stateChanged(QAudio::State s) {
		QAudioOutput * obj = qobject_cast <QAudioOutput*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[QAudioOutput_stateChanged].methodId, (xint)s);
				}
			}
		}
	}

	void qao_notify() {
		QAudioOutput * obj = qobject_cast <QAudioOutput*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[QAudioOutput_notify].methodId);
				}
			}
		}
	}
	
	void qow_aboutToCompose() {
#if !defined(QT_NO_OPENGL)
		QOpenGLWidget * obj = qobject_cast <QOpenGLWidget*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[QOpenGLWidget_aboutToCompose].methodId);
				}
			}
		}
#endif
	}

	void qow_frameSwapped() {
#if !defined(QT_NO_OPENGL)
		QOpenGLWidget * obj = qobject_cast <QOpenGLWidget*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[QOpenGLWidget_frameSwapped].methodId);
				}
			}
		}
#endif
	}

	void qow_aboutToResize() {
#if !defined(QT_NO_OPENGL)
		QOpenGLWidget * obj = qobject_cast <QOpenGLWidget*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[QOpenGLWidget_aboutToResize].methodId);
				}
			}
		}
#endif
	}

	void qow_resized() {
#if !defined(QT_NO_OPENGL)
		QOpenGLWidget * obj = qobject_cast <QOpenGLWidget*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[QOpenGLWidget_resized].methodId);
				}
			}
		}
#endif
	}

	void qio_stateChanged(QAudio::State s) {
		QAudioInput * obj = qobject_cast <QAudioInput*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[QAudioInput_stateChanged].methodId, (xint)s);
				}
			}
		}
	}

	void qio_notify() {
		QAudioInput * obj = qobject_cast <QAudioInput*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[QAudioInput_notify].methodId);
				}
			}
		}
	}

	void qvw_brightnessChanged(int brightness) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[QVideoWidget_brightnessChanged].methodId, brightness);
				}
			}
		}
	}

	void qvw_contrastChanged(int contrast) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[QVideoWidget_contrastChanged].methodId, contrast);
				}
			}
		}
	}

	void qvw_hueChanged(int hue) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[QVideoWidget_hueChanged].methodId, hue);
				}
			}
		}
	}

	void qvw_saturationChanged(int saturation) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[QVideoWidget_saturationChanged].methodId, saturation);
				}
			}
		}
	}
	

	void qmp_mediaChanged(const QMediaContent &media) {
		QUrl uri = media.canonicalUrl();
		QObject * obj = qobject_cast <QObject*>(sender());
		QByteArray data = uri.toString().toUtf8();
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_mediaChanged].methodId, (xstring)data.data());
				}
			}
		}
	}

	void qmp_currentMediaChanged(const QMediaContent &media) {
		QUrl uri = media.canonicalUrl();
		QObject * obj = qobject_cast <QObject*>(sender());
		QByteArray data = uri.toString().toUtf8();
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_currentMediaChanged].methodId, (xstring)data.data());
				}
			}
		}
	}

	void qmp_stateChanged(QMediaPlayer::State newState) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_stateChanged].methodId, (xint)newState);
				}
			}
		}
	}

	void qmp_mediaStatusChanged(QMediaPlayer::MediaStatus status) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_mediaStatusChanged].methodId, (xint)status);
				}
			}
		}
	}

	void qmp_durationChanged(qint64 duration) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_durationChanged].methodId, (xlong)duration);
				}
			}
		}
	}

	void qmp_positionChanged(qint64 position) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_positionChanged].methodId, (xlong)position);
				}
			}
		}
	}

	void qmp_volumeChanged(int volume) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_volumeChanged].methodId, volume);
				}
			}
		}
	}

	void qmp_mutedChanged(bool muted) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_mutedChanged].methodId, muted);
				}
			}
		}
	}

	void qmp_audioAvailableChanged(bool available) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_audioAvailableChanged].methodId, available);
				}
			}
		}
	}

	void qmp_videoAvailableChanged(bool videoAvailable) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_videoAvailableChanged].methodId, videoAvailable);
				}
			}
		}
	}

	void qmp_bufferStatusChanged(int percentFilled) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_bufferStatusChanged].methodId, percentFilled);
				}
			}
		}
	}

	void qmp_seekableChanged(bool seekable) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_seekableChanged].methodId, seekable);
				}
			}
		}
	}

	void qmp_playbackRateChanged(qreal rate) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_playbackRateChanged].methodId, (double)rate);
				}
			}
		}
	}

	void qmp_audioRoleChanged(QAudio::Role role) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_audioRoleChanged].methodId, (xint)role);
				}
			}
		}
	}

	void qmp_error(QMediaPlayer::Error error) {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
			XMetaPtr objectData = (obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QMediaPlayer_error].methodId, (xint)error);
				}
			}
		}
	}

	void tritemPressed(QTreeWidgetItem *item, int column) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());
		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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

	void qcw_selectionChanged() {
		QCalendarWidget * obj = qobject_cast <QCalendarWidget*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QCW_SELECTIONCHANGED].methodId);
				}
			}
		}
	}

	void qcw_clicked(const QDate &date) {
		QCalendarWidget * obj = qobject_cast <QCalendarWidget*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QCW_CLICKED].methodId, (xint)date.year(), (xint)date.month(), (xint)date.day());
				}
			}
		}
	}

	void qcw_activated(const QDate &date) {
		QCalendarWidget * obj = qobject_cast <QCalendarWidget*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QCW_ACTIVATED].methodId, (xint)date.year(), (xint)date.month(), (xint)date.day());
				}
			}
		}
	}

	void qcw_currentPageChanged(int year, int month) {
		QCalendarWidget * obj = qobject_cast <QCalendarWidget*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QCW_CURRENTPAGECHANGED].methodId, (xint)year, (xint)month);
				}
			}
		}
	}

	void tritemActivated(QTreeWidgetItem *item, int column) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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

	void qsti_activated(QSystemTrayIcon::ActivationReason reason) {
		QSystemTrayIcon * obj = qobject_cast <QSystemTrayIcon*>(sender());
		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * bc = gs_env->createObject();
					gs_env->setValue(bc, (xint)reason);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QSTI_ACTIVATED].methodId, bc);
					gs_env->dereferenceObject(bc);
				}
			}
		}
	}

	void qtnwt_backRequested() {
#ifndef MOBILE_APP
		WindowTitleBar * obj = qobject_cast <WindowTitleBar*>(sender());
		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QWT_BACKREQUESTED].methodId);
				}
			}
		}
#endif
	}

	void qtnwt_showHelp() { 
#ifndef MOBILE_APP
		WindowTitleBar * obj = qobject_cast <WindowTitleBar*>(sender());
		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QWT_SHOWHELP].methodId);
				}
			}
		}
#endif
	}

	
	void qsti_messageClicked() {
		QSystemTrayIcon * obj = qobject_cast <QSystemTrayIcon*>(sender());
		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QSTI_CLICKED].methodId);
				}
			}
		}
	}

	void tritemChanged(QTreeWidgetItem *item, int column) {
		QTreeWidget * obj = qobject_cast <QTreeWidget*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
#ifndef MOBILE_APP
	void slotGetCallbackData(LimeReport::CallbackInfo info, QVariant& data) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
                    QByteArray btdata = info.columnName.toUtf8();
					XObject * ret = gs_env->Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_DATASOURCEGETCALLBACKDATA].methodId, (xint)info.dataType, (xint)info.index, btdata.data());

					XNLEnv::XDataType ntype =  gs_env->getObjectType(ret);

					switch (ntype) {
					case XNLEnv::t_nilptr:
						data = QVariant();
						break;
					case XNLEnv::t_byte :
					{
						xbyte bv;
						if (gs_env->getByteValue(ret, &bv)) {
							data.setValue(bv);
						}
					}
						break;
					case XNLEnv::t_char :
					{
						xchar bv;
						if (gs_env->getCharValue(ret, &bv)) {
							data.setValue(bv);
						}
					}
						break;
					case XNLEnv::t_short:
					{
						short bv;
						if (gs_env->getShortValue(ret, &bv)) {
							data.setValue(bv);
						}
					}
						break;
					case XNLEnv::t_int:
					{
						xint bv;
						if (gs_env->getIntValue(ret, &bv)) {
							data.setValue(bv);
						}
					}
						break;
					case XNLEnv::t_long:
					{
						xlong bv;
						if (gs_env->getLongValue(ret, &bv)) {
							data.setValue(bv);
						}
					}
						break;
					case XNLEnv::t_double:
					{
						double bv;
						if (gs_env->getDoubleValue(ret, &bv)) {
							data.setValue(bv);
						}
					}
						break;
					case XNLEnv::t_bool:
					{
						bool bv;
						if (gs_env->getBoolValue(ret, &bv)) {
							data.setValue(bv);
						}
					}
						break;
					case XNLEnv::t_string:
					{
						xstring sv;
						int slen;
						if (gs_env->getStringValue(ret, &sv, &slen)) {
							data.setValue(QString::fromUtf8(sv, slen));
						}
					}
						break;
					}
					gs_env->dereferenceObject(ret);
				}
			}
		}
	}

	void slotChangePos(const LimeReport::CallbackInfo::ChangePosType& type, bool& result) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					result = gs_env->bool_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_DATASOURCECHANGEPOS].methodId, (xint)type);
				}
			}
		}
	}
#endif
	void SCN_AUTOCCANCELLED() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_ZOOM_ID].methodId);
				}
			}
		}
	}

	void tetextChanged() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_TEXTEDITCHANGE].methodId);
				}
			}
		}
	}
	void tecursorPositionChanged() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_TEXTEDITPOSCHANGE].methodId);
				}
			}
		}
	}

	void qh_sectionMoved(int logicalIndex, int oldVisualIndex, int newVisualIndex) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QH_SECTIONMOVED].methodId, logicalIndex, oldVisualIndex, newVisualIndex);
				}
			}
		}
	}

	void qh_sectionResized(int logicalIndex, int oldSize, int newSize) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QH_SECTIONRESIZED].methodId, logicalIndex, oldSize, newSize);
				}
			}
		}
	}

	void qh_sectionPressed(int logicalIndex) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QH_SECTIONPRESSED].methodId, logicalIndex);
				}
			}
		}
	}

	void qh_sectionClicked(int logicalIndex) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QH_SECTIONCLICKED].methodId, logicalIndex);
				}
			}
		}
	}

	void qh_sectionEntered(int logicalIndex) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QH_SECTIONENTERED].methodId, logicalIndex);
				}
			}
		}
	}

	void qh_sectionDoubleClicked(int logicalIndex) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QH_SECTIONDOUBLECLICKED].methodId, logicalIndex);
				}
			}
		}
	}

	void qh_sectionCountChanged(int oldCount, int newCount) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QH_SECTIONCOUNTCHANGED].methodId, oldCount, newCount);
				}
			}
		}
	}

	void qh_sectionHandleDoubleClicked(int logicalIndex) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QH_SECTIONHANDLEDOUBLECLICKED].methodId, logicalIndex);
				}
			}
		}
	}

	void qh_geometriesChanged() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QH_GEOMETRIESCHANGED].methodId);
				}
			}
		}
	}

	void qh_sortIndicatorChanged(int logicalIndex, Qt::SortOrder order) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QH_SORTINDICATORCHANGED].methodId, logicalIndex, order);
				}
			}
		}
	}

	void teselectionChanged() {
		QObject * obj = qobject_cast <QObject*>(sender());
		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_TEXTEDITSELCHANGE].methodId);
				}
			}
		}
	}

	void etextChanged(const QString & str) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_EDITSELCHANGE].methodId);
				}
			}
		}
	}
#ifndef MOBILE_APP
	void onValueChanged(QtProperty *property, int val) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);

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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
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
#endif
	void renderStarted() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_REPORTRENDERSTARTED].methodId);
				}
			}
		}
	}
	void renderPageFinished(int renderedPageCount) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					XObject * prop = gs_env->createObject();
					gs_env->setValue(prop, (xint)renderedPageCount);
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_REPORTRENDERPAGEFINISH].methodId, prop);
					gs_env->dereferenceObject(prop);
				}
			}
		}
	}
	void renderFinished() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_REPORTRENDERFINISH].methodId);
				}
			}
		}
	}


	void qtabwidget_currentChanged(int index) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QTABWIDGET_CURRENTCHANGED].methodId, index);
				}
			}
		}
	}

	void qtabwidget_tabCloseRequested(int index) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QTABWIDGET_TABCLOSEREQUESTED].methodId, index);
				}
			}
		}
	}

	void qtabwidget_tabBarClicked(int index) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QTABWIDGET_TABBARCLICKED].methodId, index);
				}
			}
		}
	}

	void qtabwidget_tabBarDoubleClicked(int index) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QTABWIDGET_TABBARDOUBLECLICKED].methodId, index);
				}
			}
		}
	}


	void qtabbar_currentChanged(int index) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QTABBAR_CURRENTCHANGED].methodId, index);
				}
			}
		}
	}

	void qtabbar_tabCloseRequested(int index) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QTABBAR_TABCLOSEREQUESTED].methodId, index);
				}
			}
		}
	}

	void qtabbar_tabMoved(int from, int to) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QTABBAR_TABMOVED].methodId, from, to);
				}
			}
		}
	}

	void qtabbar_tabBarClicked(int index) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QTABBAR_TABBARCLICKED].methodId, index);
				}
			}
		}
	}

	void qtabbar_tabBarDoubleClicked(int index) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_QTABBAR_TABBARDOUBLECLICKED].methodId, index);
				}
			}
		}
	}

	void slider_valueChanged(int value) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_SLIDER_VALUECHANGED].methodId, value);
				}
			}
		}
	}

	void slider_sliderPressed() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_SLIDER_SLIDERPRESSED].methodId);
				}
			}
		}
	}

	void slider_sliderMoved(int position) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_SLIDER_SLIDERMOVED].methodId, position);
				}
			}
		}
	}

	void slider_sliderReleased() {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_SLIDER_SLIDERRELEASED].methodId);
				}
			}
		}
	}

	void slider_rangeChanged(int min, int max) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_SLIDER_RANGECHANGED].methodId, min, max);
				}
			}
		}
	}

	void slider_actionTriggered(int action) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_SLIDER_ACTIONTRIGGERED].methodId, action);
				}
			}
		}
	}

	void ondateTimeChanged(const QDateTime &dateTime) {
		QObject * obj = qobject_cast <QObject*>(sender());

		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_DATETIMECHANGE].methodId, (xlong)dateTime.toMSecsSinceEpoch());
				}
			}
		}
	}

	void ontimeChanged(const QTime &time) {
		QObject * obj = qobject_cast <QObject*>(sender());
		
		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_TIMECHANGE].methodId, (xint)time.hour(), (xint)time.minute(), (xint)time.second(), (xint)time.msec());
				}
			}
		}
	}

	void ondateChanged(const QDate &date) {
		QObject * obj = qobject_cast <QObject*>(sender());
		
		if (obj != 0) {
            XMetaPtr objectData =(obj->property(XHANDLE).GETPROPERTY_VALUE);
			if (objectData != NULL) {
				if (objectData->getObject() != 0) {
					XThread thread;
					gs_env->void_Invoke(thread.getThread(), objectData->getObject(), methodIdent[ON_DATECHANGE].methodId, (xint)date.year(), (xint)date.month(), date.day());
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


	void installMediaObjectAction(QObject * p) {
		QMediaObject * act = (QMediaObject *)p;
		XLINK(act, SIGNAL(notifyIntervalChanged(int)), this, SLOT(qmp_notifyIntervalChanged(int)));
		XLINK(act, SIGNAL(metaDataAvailableChanged(bool)), this, SLOT(qmp_metaDataAvailableChanged(bool)));
		XLINK(act, SIGNAL(metaDataChanged()), this, SLOT(qmp_metaDataChanged(int)));
		XLINK(act, SIGNAL(availabilityChanged(bool)), this, SLOT(qmp_availabilityChanged(bool)));
		XLINK(act, SIGNAL(availabilityChanged(QMultimedia::AvailabilityStatus)), this, SLOT(qmp_availabilityChanged(QMultimedia::AvailabilityStatus)));
	}

	void installQAudioOutputAction(QObject * p) {
		QAudioOutput * qwt = (QAudioOutput*)p;
		XLINK(qwt, SIGNAL(stateChanged(QAudio::State)), this, SLOT(qao_stateChanged(QAudio::State)));
		XLINK(qwt, SIGNAL(notify()), this, SLOT(qao_notify()));
	}

	void installQOpenGLWidgetAction(QObject * p) {
#if !defined(QT_NO_OPENGL)
		QOpenGLWidget * qow = (QOpenGLWidget*)p;
		XLINK(qow, SIGNAL(aboutToCompose()), this, SLOT(qow_aboutToCompose()));
		XLINK(qow, SIGNAL(frameSwapped()), this, SLOT(qow_frameSwapped()));
		XLINK(qow, SIGNAL(aboutToResize()), this, SLOT(qow_aboutToResize()));
		XLINK(qow, SIGNAL(resized()), this, SLOT(qow_resized()));
#endif
	}

	void installQAudioInputAction(QObject * p) {
		QAudioInput * qwt = (QAudioInput*)p;
		XLINK(qwt, SIGNAL(stateChanged(QAudio::State)), this, SLOT(qio_stateChanged(QAudio::State)));
		XLINK(qwt, SIGNAL(notify()), this, SLOT(qio_notify()));
	}

	void installVideoWidgetAction(QObject * p) {
		QVideoWidget * qwt = (QVideoWidget*)p;
		XLINK(qwt, SIGNAL(fullScreenChanged(bool)), this, SLOT(qvw_fullScreenChanged(bool)));
		XLINK(qwt, SIGNAL(brightnessChanged(int)), this, SLOT(qvw_brightnessChanged(int)));
		XLINK(qwt, SIGNAL(contrastChanged(int)), this, SLOT(qvw_contrastChanged(int)));
		XLINK(qwt, SIGNAL(hueChanged(int)), this, SLOT(qvw_hueChanged(int)));
		XLINK(qwt, SIGNAL(saturationChanged(int)), this, SLOT(qvw_saturationChanged(int)));
	}

	void installMediaPlayerAction(QObject * p) {
		QMediaPlayer * act = (QMediaPlayer *)p;
		XLINK(act, SIGNAL(mediaChanged(const QMediaContent &)), this, SLOT(qmp_mediaChanged(const QMediaContent &)));
		XLINK(act, SIGNAL(currentMediaChanged(const QMediaContent &)), this, SLOT(qmp_currentMediaChanged(const QMediaContent &)));
		XLINK(act, SIGNAL(stateChanged(QMediaPlayer::State)), this, SLOT(qmp_stateChanged(QMediaPlayer::State)));
		XLINK(act, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(qmp_mediaStatusChanged(QMediaPlayer::MediaStatus)));
		XLINK(act, SIGNAL(durationChanged(qint64)), this, SLOT(qmp_durationChanged(qint64)));
		XLINK(act, SIGNAL(positionChanged(qint64)), this, SLOT(qmp_positionChanged(qint64)));
		XLINK(act, SIGNAL(volumeChanged(int)), this, SLOT(qmp_volumeChanged(int)));
		XLINK(act, SIGNAL(mutedChanged(bool)), this, SLOT(qmp_mutedChanged(bool)));
		XLINK(act, SIGNAL(audioAvailableChanged(bool)), this, SLOT(qmp_audioAvailableChanged(bool)));
		XLINK(act, SIGNAL(videoAvailableChanged(bool)), this, SLOT(qmp_videoAvailableChanged(bool)));
		XLINK(act, SIGNAL(bufferStatusChanged(int)), this, SLOT(qmp_bufferStatusChanged(int)));
		XLINK(act, SIGNAL(seekableChanged(bool)), this, SLOT(qmp_seekableChanged(bool)));
		XLINK(act, SIGNAL(playbackRateChanged(qreal)), this, SLOT(qmp_playbackRateChanged(qreal)));
		XLINK(act, SIGNAL(audioRoleChanged(QAudio::Role)), this, SLOT(qmp_audioRoleChanged(QAudio::Role)));
		XLINK(act, SIGNAL(error(QMediaPlayer::Error)), this, SLOT(qmp_error(QMediaPlayer::Error)));
	}

	void installAction(QObject * act) {

		XLINK(act, SIGNAL(triggered()), signalMapper, SLOT(map()));
		signalMapper->setMapping(act, act);

		if (setup == false) {
			XLINK(signalMapper, SIGNAL(mapped(QObject*)), this, SLOT(ActionTriggered(QObject*)));
			setup = true;
		}
	}

	void installMdiSubWindowEvent(QObject * mds) {
		XLINK(mds, SIGNAL(windowStateChanged(Qt::WindowStates, Qt::WindowStates)), this, SLOT(on_windowStateChanged(Qt::WindowStates, Qt::WindowStates)));
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

	void installSystemTrayIconEvent(QObject * act) {
		XLINK(act, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(qsti_activated(QSystemTrayIcon::ActivationReason)));
		XLINK(act, SIGNAL(messageClicked()), this, SLOT(qsti_messageClicked()));
	}

	void installWindowTitleEvent(QObject * act) {
		XLINK(act, SIGNAL(backRequested()), this, SLOT(qtnwt_backRequested()));
		XLINK(act, SIGNAL(showHelp()), this, SLOT(qtnwt_showHelp()));
	}

	void installCalendarEvent(QObject * btn) {
		XLINK(btn, SIGNAL(selectionChanged()), this, SLOT(qcw_selectionChanged()));
		XLINK(btn, SIGNAL(clicked(const QDate &)), this, SLOT(qcw_clicked(const QDate &)));
		XLINK(btn, SIGNAL(activated(const QDate &)), this, SLOT(qcw_activated(const QDate &)));
		XLINK(btn, SIGNAL(currentPageChanged(int, int)), this, SLOT(qcw_currentPageChanged(int, int)));
	}

	void installButtonAction(QObject * btn) {
		XLINK(btn, SIGNAL(clicked(bool)), this, SLOT(btnclicked(bool)));
		XLINK(btn, SIGNAL(toggled(bool)), this, SLOT(btntoggled(bool)));
		XLINK(btn, SIGNAL(pressed()), this, SLOT(btnpressed()));
		XLINK(btn, SIGNAL(released()), this, SLOT(btnreleased()));
	}

	void installDateTimeEditAction(QObject * edit) {
		XLINK(edit, SIGNAL(dateTimeChanged(const QDateTime &)), this, SLOT(ondateTimeChanged(const QDateTime &)));
		XLINK(edit, SIGNAL(timeChanged(const QTime &)), this, SLOT(ontimeChanged(const QTime &)));
		XLINK(edit, SIGNAL(dateChanged(const QDate &)), this, SLOT(ondateChanged(const QDate &)));
	}


	void installTabBarAction(QObject * edit) {
		XLINK(edit, SIGNAL(currentChanged(int)), this, SLOT(qtabbar_currentChanged(int)));
		XLINK(edit, SIGNAL(tabCloseRequested(int)), this, SLOT(qtabbar_tabCloseRequested(int)));
		XLINK(edit, SIGNAL(tabMoved(int, int)), this, SLOT(qtabbar_tabMoved(int, int)));
		XLINK(edit, SIGNAL(tabBarClicked(int)), this, SLOT(qtabbar_tabBarClicked(int)));
		XLINK(edit, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(qtabbar_tabBarDoubleClicked(int)));
	}

	void installTabWidgetAction(QObject * edit) {
		XLINK(edit, SIGNAL(currentChanged(int)), this, SLOT(qtabwidget_currentChanged(int)));
		XLINK(edit, SIGNAL(tabCloseRequested(int)), this, SLOT(qtabwidget_tabCloseRequested(int)));
		XLINK(edit, SIGNAL(tabBarClicked(int)), this, SLOT(qtabwidget_tabBarClicked(int)));
		XLINK(edit, SIGNAL(tabBarDoubleClicked(int)), this, SLOT(qtabwidget_tabBarDoubleClicked(int)));
	}

	void installSliderAction(QObject * edit) {
		XLINK(edit, SIGNAL(valueChanged(int)),this, SLOT(slider_valueChanged(int)));
		XLINK(edit, SIGNAL(sliderPressed()), this, SLOT(slider_sliderPressed()));
		XLINK(edit, SIGNAL(sliderMoved(int)), this, SLOT(slider_sliderMoved(int)));
		XLINK(edit, SIGNAL(sliderReleased()), this, SLOT(slider_sliderReleased()));
		XLINK(edit, SIGNAL(rangeChanged(int, int)), this, SLOT(slider_rangeChanged(int, int)));
		XLINK(edit, SIGNAL(actionTriggered(int)), this, SLOT(slider_actionTriggered(int)));
	}

	void installEditAction(QObject * edit) {
		XLINK(edit, SIGNAL(textChanged(const QString &)), this, SLOT(etextChanged(const QString &)));
		XLINK(edit, SIGNAL(textEdited(const QString &)), this, SLOT(etextEdited(const QString &)));
		XLINK(edit, SIGNAL(cursorPositionChanged(int, int)), this, SLOT(ecursorPositionChanged(int, int)));
		XLINK(edit, SIGNAL(returnPressed()), this, SLOT(ereturnPressed()));
		XLINK(edit, SIGNAL(editingFinished()), this, SLOT(eeditingFinished()));
		XLINK(edit, SIGNAL(selectionChanged()), this, SLOT(eselectionChanged()));
	}

	void installTextEditAction(QObject * edit) {
		XLINK(edit, SIGNAL(textChanged()), this, SLOT(tetextChanged()));
		XLINK(edit, SIGNAL(cursorPositionChanged()), this, SLOT(tecursorPositionChanged()));
		XLINK(edit, SIGNAL(selectionChanged()), this, SLOT(teselectionChanged()));
	}

	void installHeaderViewAction(QObject * qh) {
		XLINK(qh, SIGNAL(sectionMoved(int, int, int)), this, SLOT(qh_sectionMoved(int, int, int)));
		XLINK(qh, SIGNAL(sectionResized(int, int, int)), this, SLOT(qh_sectionResized(int, int, int)));
		XLINK(qh, SIGNAL(sectionPressed(int)), this, SLOT(qh_sectionPressed(int)));
		XLINK(qh, SIGNAL(sectionClicked(int)), this, SLOT(qh_sectionClicked(int)));
		XLINK(qh, SIGNAL(sectionEntered(int)), this, SLOT(qh_sectionEntered(int)));
		XLINK(qh, SIGNAL(sectionDoubleClicked(int)), this, SLOT(qh_sectionDoubleClicked(int)));
		XLINK(qh, SIGNAL(sectionCountChanged(int, int)), this, SLOT(qh_sectionCountChanged(int, int)));
		XLINK(qh, SIGNAL(sectionHandleDoubleClicked(int)), this, SLOT(qh_sectionHandleDoubleClicked(int)));
		XLINK(qh, SIGNAL(geometriesChanged()), this, SLOT(qh_geometriesChanged()));
		XLINK(qh, SIGNAL(sortIndicatorChanged(int, Qt::SortOrder)), this, SLOT(qh_sortIndicatorChanged(int, Qt::SortOrder)));
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
#ifndef MOBILE_APP
	void installDatasourceCallback(LimeReport::ICallbackDatasource * qobject) {
		connect(qobject, SIGNAL(getCallbackData(LimeReport::CallbackInfo, QVariant&)), this, SLOT(slotGetCallbackData(LimeReport::CallbackInfo, QVariant&)));
		connect(qobject, SIGNAL(changePos(const LimeReport::CallbackInfo::ChangePosType&, bool&)), this, SLOT(slotChangePos(const LimeReport::CallbackInfo::ChangePosType&, bool&)));
	}
#endif
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

#ifndef MOBILE_APP
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

	void installReportView(LimeReport::ReportEngine * qobject) {
		XLINK(qobject, SIGNAL(renderStarted()), this, SLOT(renderStarted()));
		XLINK(qobject, SIGNAL(renderPageFinished(int)),this, SLOT(renderPageFinished(int)));
		XLINK(qobject, SIGNAL(renderFinished()), this, SLOT(renderFinished()));
	}

	void installVariantPropertyChange(QtVariantPropertyManager*qobject) {
		XLINK(qobject, SIGNAL(valueChanged(QtProperty *, const QVariant &)), this, SLOT(onValueChanged(QtProperty *, const QVariant &)));
		XLINK(qobject, SIGNAL(attributeChanged(QtProperty *,const QString &, const QVariant &)), this, SLOT(onAttributeChanged(QtProperty *,const QString &, const QVariant &)));
	}
#endif
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
