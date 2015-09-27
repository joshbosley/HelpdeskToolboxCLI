#ifndef HDTB_HELPMODULE_H
#define HDTB_HELPMODULE_H

// Macros for human readability within help module
#define HDTB_HELP_COMMAND_LIST 0
#define HDTB_HELP_COMMAND_OS 1
#define HDTB_HELP_COMMAND_ME 2

/*
        (Step 2)
        Write a module class following the guidlines
        of the helpmodule

        - Ensure namespace hstoolbox
        - All modules must be a subclass of ModuleBase
*/

// Required
#include "../../core/datatypes.h"
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
    HDTBReturnItem processRequest(std::vector<std::string>);

private:

    // Help-module specific calls
    HDTBReturnItem displaySimpleHelp();
    HDTBReturnItem displayCurrentOS();
    HDTBReturnItem displayHelpMe();
};

}

#endif // HDTB_HELPMODULE_H
