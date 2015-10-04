#include "softwaremodule.h"

namespace hdtoolbox
{
    SoftwareModule::SoftwareModule() :
        ModuleBase(HDTB_CODE_SOFTWARE, "Standard Software Module",
                   "A module to manage software on a machine")
    {
        commands.insert(
                        HDTBMapItem
                        ("install", HDTB_SOFTWARE_INSTALL)
                        );

        commands.insert(
                        HDTBMapItem
                        ("remove", HDTB_SOFTWARE_REMOVE)
                    );

        commands.insert(
                        HDTBMapItem
                        ("modify", HDTB_SOFTWARE_MODIFY)
                        );
    }

    HDTBReturnItem SoftwareModule::processRequest(std::vector<std::string> args)
    {
        history.push(args);

        if (args.size() == 1)
        {
            displayAvailableCommands();

            return errorHandler.generateGenericError("No commands given");
        }

        if (commands.find(args[1]) == commands.end())
        {
            displayAvailableCommands();

            return errorHandler.generateGenericError("Command not found");

        }

        switch(commands[args[1]])
        {
        case HDTB_SOFTWARE_INSTALL:
            args.erase(args.begin());

            return install.processRequest(args);
            break;
        case HDTB_SOFTWARE_REMOVE:
            args.erase(args.begin());

            return remove.processRequest(args);
            break;

        case HDTB_SOFTWARE_MODIFY:
            args.erase(args.begin());

            return modify.processRequest(args);
            break;

        default:
            break;
        }

        return errorHandler.generateGenericError("Uncaught return");
    }
}
