#include "ssmodule.h"

namespace hdtoolbox
{
    SSModule::SSModule() :
        ModuleBase(HDTB_CODE_SS, "Standard Software Module",
                   "A module to manage software on a machine")
    {
        commands.insert(
                        HDTBMapItem
                        ("install", HDTB_SS_COMMAND_INSTALL)
                        );

        commands.insert(
                        HDTBMapItem
                        ("remove", HDTB_SS_COMMAND_REMOVE)
                    );

        commands.insert(
                        HDTBMapItem
                        ("modify", HDTB_SS_COMMAND_MODIFY)
                        );
    }

    HDTBReturnItem SSModule::processRequest(std::vector<std::string> args)
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
        case HDTB_SS_COMMAND_INSTALL:
            if (args.size() != 3)
            {
                return errorHandler.generateGenericError("No software name given");

            }
            else
            {
#ifdef _WIN32
                return performInstall(args[2]);
#elif __APPLE__
                return errorHandler.generateGenericError("OS not yet supported");
#endif
            }
            break;

        case HDTB_SS_COMMAND_MODIFY:
            if (args.size() != 3)
            {
                return errorHandler.generateGenericError("No software name given");
            }
            else
            {
#ifdef _WIN32
                return performModify(args[2]);
#elif __APPLE__
                return errorHandler.generateGenericError("OS not yet supported");
#endif
            }
            break;



        case HDTB_SS_COMMAND_REMOVE:
            if (args.size() != 3)
            {
                return errorHandler.generateGenericError("No software name given");
            }
            else
            {
#ifdef _WIN32
                return performRemove(args[2]);
#elif __APPLE__
                return errorHandler.generateGenericError("OS not yet supported");
#endif
            }
            break;

        default:
            break;
        }

        return errorHandler.generateGenericError("Uncaught return");
    }


    HDTBReturnItem SSModule::performInstall(std::string software)
    {
        std::cout << "Software name: " << software.c_str() << std::endl;

        return errorHandler.generateGenericError("Function is yet to be programmed");

    }

    HDTBReturnItem SSModule::performRemove(std::string software)
    {
        std::cout << "Software name: " << software.c_str() << std::endl;

        return errorHandler.generateGenericError("Function is yet to be programmed");

    }

    HDTBReturnItem SSModule::performModify(std::string software)
    {
       std::cout << "Software name: " << software.c_str() << std::endl;

       return errorHandler.generateGenericError("Function is yet to be programmed");
    }


}
