#ifndef HDTB_MODULEBOX
#define HDTB_MODULEBOX

/*
    (Step 3)
    When a new module is written, include the source below,
    and then insert it into the moduleBox struct.
*/

// BEGIN_MODULES_INCLUDES

#include "helpmodule.h"

// END_MODULES_INCLUDES

namespace hdtoolbox
{
    struct moduleBox
    {
        HelpModule helpModule;


    };

    typedef struct moduleBox moduleBox;
}

#endif // HDTB_MODULEBOX

