TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    core/boxcore.cpp \
    modules/help_module/helpmodule.cpp \
    modules/machine_module/machinemodule.cpp \
    modules/machine_module/sub-modules/machinesubmoduleadd.cpp \
    modules/machine_module/sub-modules/machinesubmoduleedit.cpp \
    modules/machine_module/sub-modules/machinesubmoduleremove.cpp \
    modules/machine_module/sub-modules/machinesubmoduleperform.cpp \
    modules/machine_module/sub-modules/machinesubmoduleget.cpp \
    modules/framework/_errors/errorbase.cpp \
    modules/framework/_modules/modulebase.cpp \
    modules/ss_module/ssmodule.cpp \
    modules/network_module/networkmodule.cpp

HEADERS += \
    core/boxcore.h \
    core/modulebox.h \
    modules/moduledirectory.h \
    modules/returnitem.h \
    modules/returncodes.h \
    modules/errorbase.h \
    modules/framework/errorbase.h \
    core/modulebox.h \
    modules/help_module/helpmodule.h \
    core/datatypes.h \
    modules/machine_module/machinemodule.h \
    modules/machine_module/sub-modules/machinesubmoduleadd.h \
    modules/machine_module/machinemoduledirectory.h \
    modules/machine_module/sub-modules/machinesubmoduleedit.h \
    modules/machine_module/sub-modules/machinesubmoduleremove.h \
    modules/machine_module/sub-modules/machinesubmoduleperform.h \
    modules/machine_module/sub-modules/machinesubmoduleget.h \
    modules/framework/osincludes.h \
    modules/framework/_errors/errorbase.h \
    modules/framework/_modules/modulebase.h \
    modules/framework/_modules/moduledirectory.h \
    modules/framework/_os/osincludes.h \
    modules/framework/_os/osinfo.h \
    modules/framework/_types/returncodes.h \
    modules/framework/_types/returnitem.h \
    modules/ss_module/ssmodule.h \
    modules/network_module/networkmodule.h \
    modules/network_module/networkdirectory.h

DISTFILES += \
    work.todo \
    modules/help_module/pages/directory.conf \
    modules/help_module/pages/machine \
    lib/machine/example \
    lib/machine/adddomain.ps1 \
    lib/machine/adddomainfinal.bat \
    lib/machine/editDomain.ps1 \
    lib/machine/editWorkgroup.ps1 \
    lib/machine/removeDomain.ps1 \
    lib/machine/editCname.ps1 \
    lib/machine/deployment.properties \
    lib/machine/fixJava.bat \
    lib/machine/cleanup.bat \
    modules/help_module/pages/network

