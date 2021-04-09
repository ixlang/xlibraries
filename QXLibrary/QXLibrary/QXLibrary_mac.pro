#-------------------------------------------------
#
# Project created by QtCreator 2018-08-18T18:52:47
#
#-------------------------------------------------

QT       += core gui printsupport qml xml network designer sql multimedia multimediawidgets opengl

TARGET = QXLibrary
TEMPLATE = lib

unix:!macx{
    contains(QT_ARCH, arm) {
        QTDIR = /media/pi/Backup/qt5.9.1
    }else{
        contains(QT_ARCH, x86_64) {
           QTDIR = /home/cadaqs/qt5.12/5.9.1/linux_gcc_x64_static_with_opengl
        } else {
           QTDIR = /home/cadaqs/Qt5.9.1/5.9.1/gcc_x86_static
        }
    }
}
win32:{
    QTDIR = E:/Qt512/Qt5.12.0/5.15.2
}
QMAKE_LFLAGS += -Wl,-z,defs
QMAKE_CXXFLAGS_RELEASE += -Os
CONFIG += dll
DEFINES += QXLIBRARY_LIBRARY
DEFINES += QTITAN_LIBRARY_STATIC
DEFINES += QTN_NAMESPACE
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

QMAKE_LFLAGS += -shared
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CFLAGS += -fPIC
#QMAKE_LFLAGS += -Xlinker --unresolved-symbols=report-all
#ignore-in-shared-libs
INCLUDEPATH += $$QTDIR/include
INCLUDEPATH += $$QTDIR/include/QtCore
INCLUDEPATH += $$QTDIR/include/QtGui
INCLUDEPATH += $$QTDIR/include/QtANGLE
INCLUDEPATH += $$QTDIR/include/QtWidgets
INCLUDEPATH += $$QTDIR/include/Qt4Qt5
INCLUDEPATH += $$QTDIR/include/QtitanDocking/include

SOURCES += QxLibrary.cpp\
        QXApplication.cpp\
        xid.cpp
HEADERS += QXApplication.h\
        qxlibrary_global.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}

LIBS += -L$$QTDIR/lib/ -lQt5Core
LIBS += -L$$QTDIR/lib/ -lQt5Gui


PRE_TARGETDEPS += $$QTDIR/lib/libQt5Core.a
PRE_TARGETDEPS += $$QTDIR/lib/libQt5Gui.a

LIBS += -L$$QTDIR/lib/ -lQt5Widgets
PRE_TARGETDEPS += $$QTDIR/lib/libQt5Widgets.a

#LIBS += -L$$QTDIR/lib/ -lfcitxplatforminputcontextplugin

LIBS += -L$$QTDIR/lib/ -lqscintilla2_qt5
PRE_TARGETDEPS += $$QTDIR/lib/libqscintilla2_qt5.a

LIBS += -L$$QTDIR/lib/ -llimereport
PRE_TARGETDEPS += $$QTDIR/lib/liblimereport.a

LIBS += -L$$QTDIR/lib/ -lQtZint
PRE_TARGETDEPS += $$QTDIR/lib/libQtZint.a

LIBS += -L$$QTDIR/lib/ -lQt5DesignerComponents
PRE_TARGETDEPS += $$QTDIR/lib/libQt5DesignerComponents.a

LIBS += -L$$QTDIR/lib/ -lQtitanDocking3_static
PRE_TARGETDEPS += $$QTDIR/lib/libQtitanDocking3_static.a

LIBS += -L$$QTDIR/lib/ -lQtitanBase1_static
PRE_TARGETDEPS += $$QTDIR/lib/libQtitanBase1_static.a

LIBS += -lQt5X11Extras

#PRE_TARGETDEPS += $$QTDIR/lib/libfcitxplatforminputcontextplugin.a

LIBS += -L$$QTDIR/lib/ -lQtSolutions_PropertyBrowser-head

INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

PRE_TARGETDEPS += $$QTDIR/lib/libQtSolutions_PropertyBrowser-head.a

LIBS += -L$$QTDIR/lib/ -lQt5UiTools

INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

PRE_TARGETDEPS += $$QTDIR/lib/libQt5UiTools.a


LIBS += -L$$QTDIR/plugins/platforms/ -lqxcb

INCLUDEPATH += $$QTDIR/plugins/platforms
DEPENDPATH += $$QTDIR/plugins/platforms

PRE_TARGETDEPS += $$QTDIR/plugins/platforms/libqxcb.a

#unix:!macx: LIBS += -lxkbcommon


LIBS += -L$$QTDIR/plugins/mediaservice/ -lqtmedia_audioengine
PRE_TARGETDEPS += $$QTDIR/plugins/mediaservice/libqtmedia_audioengine.a

LIBS += -L$$QTDIR/plugins/audio/ -lqtaudio_alsa
PRE_TARGETDEPS += $$QTDIR/plugins/audio/libqtaudio_alsa.a

LIBS += -L$$QTDIR/plugins/platforminputcontexts/ -lcomposeplatforminputcontextplugin
PRE_TARGETDEPS += $$QTDIR/plugins/platforminputcontexts/libcomposeplatforminputcontextplugin.a

LIBS += -L$$QTDIR/plugins/platforminputcontexts/ -libusplatforminputcontextplugin
PRE_TARGETDEPS += $$QTDIR/plugins/platforminputcontexts/libibusplatforminputcontextplugin.a

LIBS += -L$$QTDIR/plugins/platforminputcontexts/ -lqtvirtualkeyboardplugin
PRE_TARGETDEPS += $$QTDIR/plugins/platforminputcontexts/libqtvirtualkeyboardplugin.a

LIBS += -L$$QTDIR/qml/QtQuick.2/ -lqtquick2plugin
PRE_TARGETDEPS += $$QTDIR/qml/QtQuick.2/libqtquick2plugin.a

LIBS += -L$$QTDIR/qml/QtQuick/Window.2/ -lwindowplugin
PRE_TARGETDEPS += $$QTDIR/qml/QtQuick/Window.2/libwindowplugin.a

LIBS += -L$$QTDIR/qml/QtQuick/VirtualKeyboard/Styles/ -lqtvirtualkeyboardstylesplugin
PRE_TARGETDEPS += $$QTDIR/qml/QtQuick/VirtualKeyboard/Styles/libqtvirtualkeyboardstylesplugin.a

LIBS += -L$$QTDIR/qml/QtQuick/Layouts/ -lqquicklayoutsplugin
PRE_TARGETDEPS += $$QTDIR/qml/QtQuick/Layouts/libqquicklayoutsplugin.a

LIBS += -L$$QTDIR/qml/Qt/labs/folderlistmodel/ -lqmlfolderlistmodelplugin
PRE_TARGETDEPS += $$QTDIR/qml/Qt/labs/folderlistmodel/libqmlfolderlistmodelplugin.a
