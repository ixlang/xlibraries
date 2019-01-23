#-------------------------------------------------
#
# Project created by QtCreator 2018-08-18T18:52:47
#
#-------------------------------------------------

QT       += core gui

TARGET = QXLibrary
TEMPLATE = lib

unix:!macx{
    contains(TARGET_ARCH, x86_64) {
        QTDIR = /home/cadaqs/Qt5.9.1/5.9.1/Qt5.9.1_linux_gcc_x64_static_fc
    } else {
        QTDIR = /home/cadaqs/qt5.12/5.9.1/linux_gcc_x64_static
#/home/cadaqs/Qt5.12/5.9.1/gcc_x86_static
    }
}

QMAKE_CXXFLAGS_RELEASE += -Os
CONFIG += dll
DEFINES += QXLIBRARY_LIBRARY
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

INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

unix: PRE_TARGETDEPS += $$QTDIR/lib/libQt5Core.a
unix: PRE_TARGETDEPS += $$QTDIR/lib/libQt5Gui.a

unix: LIBS += -L$$QTDIR/lib/ -lQt5Widgets

INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

unix: PRE_TARGETDEPS += $$QTDIR/lib/libQt5Widgets.a

unix: LIBS += -L$$QTDIR/lib/ -lqscintilla2_qt5

INCLUDEPATH += $$QTDIR/include
DEPENDPATH += $$QTDIR/include

unix: PRE_TARGETDEPS += $$QTDIR/lib/libqscintilla2_qt5.a

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
