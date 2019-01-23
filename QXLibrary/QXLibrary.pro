#-------------------------------------------------
#
# Project created by QtCreator 2018-11-07T02:24:05
#
#-------------------------------------------------

QT       += core gui uitools

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QTDIR = /Users/cadaqs/qt512/macos_x64_static
TARGET = QXLibrary
TEMPLATE = lib
CONFIG += qscintilla2
macx{
TEMPLATE = lib
CONFIG += dll  c++11
QMAKE_LFLAGS += -shared
}
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


SOURCES += \
        QXLibrary/QxLibrary.cpp\
        QXLibrary/QXApplication.cpp\
        QXLibrary/xid.cpp
HEADERS += \
        QXLibrary/QXApplication.h\
        QXLibrary/qxlibrary_global.h 

macx {
    QMAKE_POST_LINK = install_name_tool -change libqscintilla2_qt$${QT_MAJOR_VERSION}.13.dylib $$[QT_INSTALL_LIBS]/libqscintilla2_qt$${QT_MAJOR_VERSION}.13.dylib $(TARGET)
}

INCLUDEPATH += $$QTDIR/include/Qt4Qt5

macx: LIBS += -L$$QTDIR/lib/ -lqscintilla2_qt5
macx: PRE_TARGETDEPS += $$QTDIR/lib/libqscintilla2_qt5.a

macx: LIBS += -L$$QTDIR/lib/ -lQtSolutions_PropertyBrowser-head
macx: PRE_TARGETDEPS += $$QTDIR/lib/libQtSolutions_PropertyBrowser-head.a

macx: LIBS += -L$$QTDIR/plugins/platforms/ -lqcocoa
macx: PRE_TARGETDEPS += $$QTDIR/plugins/platforms/libqcocoa.a

macx: LIBS += -L$$QTDIR/lib/ -lQt5MacExtras

macx: PRE_TARGETDEPS += $$QTDIR/lib/libQt5MacExtras.a
