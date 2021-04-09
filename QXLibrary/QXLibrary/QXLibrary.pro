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
           QTDIR = /home/cadaqs/qt5.12/5.15.2/clang_x86_static_with_opengl
        } else {
           QTDIR = /home/cadaqs/Qt5.9.1/5.15.2/gcc_x86_static_with_opengl
        }
    }
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

unix: LIBS += -L$$QTDIR/lib/ -lQt5Core
unix: LIBS += -L$$QTDIR/lib/ -lQt5Gui


unix: PRE_TARGETDEPS += $$QTDIR/lib/libQt5Core.a
unix: PRE_TARGETDEPS += $$QTDIR/lib/libQt5Gui.a

unix: LIBS += -L$$QTDIR/lib/ -lQt5Widgets
unix: PRE_TARGETDEPS += $$QTDIR/lib/libQt5Widgets.a

unix: LIBS += -L$$QTDIR/lib/ -lfcitxplatforminputcontextplugin

unix: LIBS += -L$$QTDIR/lib/ -lqscintilla2_qt5
unix: PRE_TARGETDEPS += $$QTDIR/lib/libqscintilla2_qt5.a

unix: LIBS += -L$$QTDIR/lib/ -llimereport
unix: PRE_TARGETDEPS += $$QTDIR/lib/liblimereport.a

unix: LIBS += -L$$QTDIR/lib/ -lQtZint
unix: PRE_TARGETDEPS += $$QTDIR/lib/libQtZint.a

unix: LIBS += -L$$QTDIR/lib/ -lQt5DesignerComponents
unix: PRE_TARGETDEPS += $$QTDIR/lib/libQt5DesignerComponents.a

unix: LIBS += -L$$QTDIR/lib/ -lQtitanDocking3_static
unix: PRE_TARGETDEPS += $$QTDIR/lib/libQtitanDocking3_static.a

unix: LIBS += -L$$QTDIR/lib/ -lQtitanBase1_static
unix: PRE_TARGETDEPS += $$QTDIR/lib/libQtitanBase1_static.a

LIBS += -lQt5X11Extras

unix: PRE_TARGETDEPS += $$QTDIR/lib/libfcitxplatforminputcontextplugin.a

win32:CONFIG(release, debug|release): LIBS += -L$$QTDIR/lib/release/ -lQtSolutions_PropertyBrowser-head
else:win32:CONFIG(debug, debug|release): LIBS += -L$$QTDIR/lib/debug/ -lQtSolutions_PropertyBrowser-head
else:unix: LIBS += -L$$QTDIR/lib/ -lQtSolutions_PropertyBrowser-head

INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$QTDIR/lib/release/libQtSolutions_PropertyBrowser-head.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$QTDIR/lib/debug/libQtSolutions_PropertyBrowser-head.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$QTDIR/lib/release/QtSolutions_PropertyBrowser-head.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$QTDIR/lib/debug/QtSolutions_PropertyBrowser-head.lib
else:unix: PRE_TARGETDEPS += $$QTDIR/lib/libQtSolutions_PropertyBrowser-head.a

win32:CONFIG(release, debug|release): LIBS += -L$$QTDIR/lib/release/ -lQt5UiTools
else:win32:CONFIG(debug, debug|release): LIBS += -L$$QTDIR/lib/debug/ -lQt5UiTools
else:unix: LIBS += -L$$QTDIR/lib/ -lQt5UiTools

INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$QTDIR/lib/release/libQt5UiTools.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$QTDIR/lib/debug/libQt5UiTools.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$QTDIR/lib/release/Qt5UiTools.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$QTDIR/lib/debug/Qt5UiTools.lib
else:unix: PRE_TARGETDEPS += $$QTDIR/lib/libQt5UiTools.a


unix: LIBS += -L$$QTDIR/plugins/platforms/ -lqxcb

INCLUDEPATH += $$QTDIR/plugins/platforms
DEPENDPATH += $$QTDIR/plugins/platforms

unix: PRE_TARGETDEPS += $$QTDIR/plugins/platforms/libqxcb.a

#unix:!macx: LIBS += -lxkbcommon


#unix: LIBS += -L$$QTDIR/plugins/mediaservice/ -lqtmedia_audioengine
#unix: PRE_TARGETDEPS += $$QTDIR/plugins/mediaservice/libqtmedia_audioengine.a

unix: LIBS += -L$$QTDIR/plugins/audio/ -lqtaudio_alsa
unix: PRE_TARGETDEPS += $$QTDIR/plugins/audio/libqtaudio_alsa.a

unix: LIBS += -L$$QTDIR/plugins/platforminputcontexts/ -lcomposeplatforminputcontextplugin
unix: PRE_TARGETDEPS += $$QTDIR/plugins/platforminputcontexts/libcomposeplatforminputcontextplugin.a

unix: LIBS += -L$$QTDIR/plugins/platforminputcontexts/ -libusplatforminputcontextplugin
unix: PRE_TARGETDEPS += $$QTDIR/plugins/platforminputcontexts/libibusplatforminputcontextplugin.a

unix: LIBS += -L$$QTDIR/plugins/platforminputcontexts/ -lqtvirtualkeyboardplugin
unix: PRE_TARGETDEPS += $$QTDIR/plugins/platforminputcontexts/libqtvirtualkeyboardplugin.a

unix: LIBS += -L$$QTDIR/qml/QtQuick.2/ -lqtquick2plugin
unix: PRE_TARGETDEPS += $$QTDIR/qml/QtQuick.2/libqtquick2plugin.a

unix: LIBS += -L$$QTDIR/qml/QtQuick/Window.2/ -lwindowplugin
unix: PRE_TARGETDEPS += $$QTDIR/qml/QtQuick/Window.2/libwindowplugin.a

#unix: LIBS += -L$$QTDIR/qml/QtQuick/VirtualKeyboard/Styles/ -lqtvirtualkeyboardstylesplugin
#unix: PRE_TARGETDEPS += $$QTDIR/qml/QtQuick/VirtualKeyboard/Styles/libqtvirtualkeyboardstylesplugin.a

unix: LIBS += -L$$QTDIR/qml/QtQuick/Layouts/ -lqquicklayoutsplugin
unix: PRE_TARGETDEPS += $$QTDIR/qml/QtQuick/Layouts/libqquicklayoutsplugin.a

unix: LIBS += -L$$QTDIR/qml/Qt/labs/folderlistmodel/ -lqmlfolderlistmodelplugin
unix: PRE_TARGETDEPS += $$QTDIR/qml/Qt/labs/folderlistmodel/libqmlfolderlistmodelplugin.a
