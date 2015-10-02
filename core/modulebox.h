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
#include "../modules/ss_module/ssmodule.h"

// END_MODULES_INCLUDES

namespace hdtoolbox
{
    struct moduleBox
    {
        HelpModule helpModule;

        // Add modules here!
        MachineModule machineModule;

        SSModule ssModule;
    };

    typedef struct moduleBox moduleBox;
}

#endif // HDTB_MODULEBOX

