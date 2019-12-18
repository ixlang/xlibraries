#-------------------------------------------------
#
# Project created by QtCreator 2018-08-18T18:52:47
#
#-------------------------------------------------

QT       += core gui printsupport qml xml network sql uitools androidextras

TARGET = QXLibrary
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QXLIBRARY_LIBRARY

unix {
    QTDIR = E:\Qt512\Qt5.12.0\5.12.0\android_arm64_v8a
}

QMAKE_CXXFLAGS_RELEASE += -Os

CONFIG += c++11


QMAKE_CFLAGS += -fPIC

INCLUDEPATH += $$QTDIR/include
INCLUDEPATH += $$QTDIR/include/Qt4Qt5

SOURCES += QxLibrary.cpp\
        QXApplication.cpp\
        xid.cpp

HEADERS += QXApplication.h\
        qxlibrary_global.h 


INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

DEFINES += MOBILE_APP=1

LIBS += -L$$QTDIR/lib/ -lqscintilla2_qt5
PRE_TARGETDEPS += $$QTDIR/lib/libqscintilla2_qt5.a

LIBS += -L$$QTDIR/lib/ -lQtSolutions_PropertyBrowser-head
PRE_TARGETDEPS += $$QTDIR/lib/libQtSolutions_PropertyBrowser-head.a


CONFIG += mobility
MOBILITY =
