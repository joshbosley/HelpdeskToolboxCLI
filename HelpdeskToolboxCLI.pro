TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    core/boxcore.cpp \
    modules/framework/modulebase.cpp \
    modules/help_module/helpmodule.cpp \
    modules/framework/errorbase.cpp \

HEADERS += \
    core/boxcore.h \
    modules/framework/modulebase.h \
    core/modulebox.h \
    modules/moduledirectory.h \
    modules/returnitem.h \
    modules/returncodes.h \
    modules/framework/osinfo.h \
    modules/errorbase.h \
    modules/framework/errorbase.h \
    core/modulebox.h \
    modules/framework/modulebase.h \
    modules/framework/moduledirectory.h \
    modules/framework/osinfo.h \
    modules/framework/returncodes.h \
    modules/framework/returnitem.h \
    modules/help_module/helpmodule.h \
    core/datatypes.h

DISTFILES += \
    work.todo

