#ifndef HDTB_HELPMODULE_H
#define HDTB_HELPMODULE_H

// Macros for human readability within help module
#define HDTB_HELP_COMMAND_LIST 0
#define HDTB_HELP_COMMAND_OS 1

/*
        (Step 2)
        Write a module class following the guidlines
        of the helpmodule

        - Ensure namespace hstoolbox
        - All modules must be a subclass of ModuleBase
*/

// Required
#include "../framework/modulebase.h"

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
