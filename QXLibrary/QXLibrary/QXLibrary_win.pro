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
    QTDIR = E:/Qt512/Qt5.12.0/5.15.2/win64_static
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

LIBS += -L$$QTDIR/lib/ -lQt5Core
LIBS += -L$$QTDIR/lib/ -lQt5Gui


PRE_TARGETDEPS += $$QTDIR/lib/Qt5Core.lib
PRE_TARGETDEPS += $$QTDIR/lib/Qt5Gui.lib

LIBS += -L$$QTDIR/lib/ -lQt5Widgets
PRE_TARGETDEPS += $$QTDIR/lib/Qt5Widgets.lib

#LIBS += -L$$QTDIR/lib/ -lfcitxplatforminputcontextplugin

LIBS += -L$$QTDIR/lib/ -lqscintilla2_qt5
PRE_TARGETDEPS += $$QTDIR/lib/qscintilla2_qt5.lib

LIBS += -L$$QTDIR/lib/ -llimereport
PRE_TARGETDEPS += $$QTDIR/lib/limereport.lib

LIBS += -L$$QTDIR/lib/ -lQtZint
PRE_TARGETDEPS += $$QTDIR/lib/QtZint.lib

LIBS += -L$$QTDIR/lib/ -lQt5DesignerComponents
PRE_TARGETDEPS += $$QTDIR/lib/Qt5DesignerComponents.lib

LIBS += -L$$QTDIR/lib/ -lQtitanDocking3_static
PRE_TARGETDEPS += $$QTDIR/lib/QtitanDocking3_static.lib

LIBS += -L$$QTDIR/lib/ -lQtitanBase1_static
PRE_TARGETDEPS += $$QTDIR/lib/QtitanBase1_static.lib


#PRE_TARGETDEPS += $$QTDIR/lib/fcitxplatforminputcontextplugin.lib

LIBS += -L$$QTDIR/lib/ -lQtSolutions_PropertyBrowser-head

INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

PRE_TARGETDEPS += $$QTDIR/lib/QtSolutions_PropertyBrowser-head.lib

LIBS += -L$$QTDIR/lib/ -lQt5UiTools

INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

PRE_TARGETDEPS += $$QTDIR/lib/Qt5UiTools.lib


LIBS += -L$$QTDIR/plugins/platforms/ -lqwindows

INCLUDEPATH += $$QTDIR/plugins/platforms
DEPENDPATH += $$QTDIR/plugins/platforms

PRE_TARGETDEPS += $$QTDIR/plugins/platforms/qwindows.lib

#unix:!macx: LIBS += -lxkbcommon

PRE_TARGETDEPS += $$QTDIR/lib/qtmain.lib
PRE_TARGETDEPS += $$QTDIR/lib/qscintilla2_qt5.lib
PRE_TARGETDEPS += $$QTDIR/lib/QtSolutions_PropertyBrowser-head.lib
