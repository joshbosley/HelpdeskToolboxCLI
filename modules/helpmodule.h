#ifndef HDTB_HELPMODULE_H
#define HDTB_HELPMODULE_H

/*
        (Step 2)
        Write a module class following the guidlines
        of the helpmodule

        - Ensure namespace hstoolbox
        - All modules must be a subclass of ModuleBase
*/

// Required
#include "modulebase.h"

// Required
namespace hdtoolbox
{

// Subclass creation required
class HelpModule : public ModuleBase
{
public:

    HelpModule();

    // Required
    struct returnItem processRequest(std::vector<std::string>);
};

}

#endif // HDTB_HELPMODULE_H
