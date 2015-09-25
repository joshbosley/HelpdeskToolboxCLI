TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    core/boxcore.cpp \
    modules/modulebase.cpp \
    modules/helpmodule.cpp

HEADERS += \
    core/boxcore.h \
    modules/modulebase.h \
    modules/modulebox.h \
    modules/helpmodule.h \
    modules/moduledirectory.h \
    modules/returnitem.h \
    modules/returncodes.h

DISTFILES += \
    work.todo

