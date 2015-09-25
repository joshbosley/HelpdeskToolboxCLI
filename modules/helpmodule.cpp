#include "helpmodule.h"

namespace hdtoolbox
{

// Adding your module id, and information here is required
HelpModule::HelpModule() :
    ModuleBase(HDTB_CODE_HELP,
               "Help Module",
               "A module to provide help.")
{

}

// Process the input, and return a returnItem
struct returnItem HelpModule::processRequest(std::vector<std::string> args)
{
    struct returnItem ri(HDTB_RETURN_BAD, "None");

    if(args.size() == 1)
    {
        std::cout << std::endl <<
                     "<module_name> <commands>"
                  << std::endl;

        ri.retCode = HDTB_RETURN_GOOD;
    }
    else
    {
        // Process remaining commands
    }

    return ri;
}

}
