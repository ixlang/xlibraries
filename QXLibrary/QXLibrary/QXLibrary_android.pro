#-------------------------------------------------
#
# Project created by QtCreator 2018-08-18T18:52:47
#
#-------------------------------------------------

QT       += core gui printsupport qml xml network sql uitools androidextras multimedia opengl multimediawidgets

TARGET = QXLibrary
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QXLIBRARY_LIBRARY

unix {
    QTDIR = E:\Qt610\5.15.2\android
}

QMAKE_CXXFLAGS_RELEASE += -Os

CONFIG += c++11


QMAKE_CFLAGS += -fPIC

INCLUDEPATH += $$QTDIR/include
INCLUDEPATH += $$QTDIR/include/Qt4Qt5
INCLUDEPATH += $$QTDIR/include/QtMultimediaWidgets
INCLUDEPATH += $$QTDIR/include/QtOpenGL
SOURCES += QxLibrary.cpp\
        QXApplication.cpp\
        xid.cpp

HEADERS += QXApplication.h\
        qxlibrary_global.h 


INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

DEFINES += MOBILE_APP=1


for (abi, ANDROID_ABIS):{
    LIBS += -L$$QTDIR/lib/ -lqscintilla2_qt5_$${abi}
    PRE_TARGETDEPS += $$QTDIR/lib/libqscintilla2_qt5_$${abi}.a
    LIBS += -L$$QTDIR/lib/ -lQtSolutions_PropertyBrowser-head_$${abi}
    PRE_TARGETDEPS += $$QTDIR/lib/libQtSolutions_PropertyBrowser-head_$${abi}.a
}
CONFIG += mobility
MOBILITY += multimedia
MOBILITY =
