#ifndef HDTB_MODULEBOX
#define HDTB_MODULEBOX

/*
    (Step 3)
    When a new module is written, include the source below,
    and then insert it into the moduleBox struct.
*/

// BEGIN_MODULES_INCLUDES

#include "../modules/help_module/helpmodule.h"
#include "../modules/machine_module/machinemodule.h"
#include "../modules/software_module/softwaremodule.h"
#include "../modules/network_module/networkmodule.h"

// END_MODULES_INCLUDES

namespace hdtoolbox
{
    struct moduleBox
    {
        HelpModule helpModule;

        // Add modules here!
        MachineModule machineModule;

        SoftwareModule ssModule;

        NetworkModule networkModule;
    };

    typedef struct moduleBox moduleBox;
}

#endif // HDTB_MODULEBOX

