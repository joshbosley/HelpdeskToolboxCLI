#include "machinesubmoduleperform.h"

// Required
namespace hdtoolbox
{


MachineSubModulePerform::MachineSubModulePerform() :
    ModuleBase(HDTB_MACHINE_PERFORM,
               "Machine SubModule - Perform",
               "The sub-module that handles the perform command for"
               "the Machine Module")
{
    commands.insert(
                HDTBMapItem
                ("cleanup", HDTB_MACHINE_CMD_CLEANUP)
                );

    commands.insert(
                HDTBMapItem
                ("dcopy", HDTB_MACHINE_CMD_COPY)
                );

    commands.insert(
                HDTBMapItem
                ("winupdate", HDTB_MACHINE_CMD_WUPDATE)
                );

    commands.insert(
                HDTBMapItem
                ("scrub", HDTB_MACHINE_CMD_SCRUB)
                );

    commands.insert(
                HDTBMapItem
                ("fixjava", HDTB_MACHINE_CMD_FIXJAVA)
                );
}

HDTBReturnItem hdtoolbox::MachineSubModulePerform::processRequest(std::vector<std::string> args)
{
    history.push(args);

    // Make sure commands are given
    if(args.size() == 1)
    {
        // Call to super class
        displayAvailableCommands();
        return errorHandler.generateGenericError("No commands given");
    }

    // Make sure command exists
    if(commands.find(args[1]) == commands.end())
    {
        // Call to super class
        displayAvailableCommands();
        return errorHandler.generateGenericError("Command not found");
    }

    //Handle command
    switch(commands[args[1]])
    {

    case HDTB_MACHINE_CMD_CLEANUP:
        return cleanup();
        break;

    case HDTB_MACHINE_CMD_COPY:
        if (args.size() != 4)
        {
            return errorHandler.generateGenericError("Requires source and destination");
        }
        else
        {
            return copy(args[2], args[3]);
        }

        break;

    case HDTB_MACHINE_CMD_WUPDATE:
#ifdef _WIN32
            return winupdate();
#else
        return errorHandler.generateGenericError("OS not supported");
#endif
        break;

    case HDTB_MACHINE_CMD_SCRUB:
        return scrub();
        break;

    case HDTB_MACHINE_CMD_FIXJAVA:
        return fixJava();
        break;
    default:
        break;
    }
    return errorHandler.generateGenericError("Uncaught return");
}

HDTBReturnItem MachineSubModulePerform::cleanup()
{
    std::cout << std::endl << "Perform cleanup... " << std::endl;
#ifdef _WIN32
    system("start lib\\machine\\cleanup.bat");
    std::cout << std::endl << "Cleanup complete.." << std::endl;
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");

#elif __APPLE__
    // Do this last
    system("sudo rm -rf ~/.Trash/*");
    return errorHandler.generateGenericError("Not yet fully created");
#endif
}

HDTBReturnItem MachineSubModulePerform::copy(std::string src, std::string dest)
{
    // Need to handle different platforms
    std::cout << std::endl << "Copy from : " << src << " to :" << dest << std::endl;
#ifdef _WIN32
    std::string command = ("xcopy " + src + " " + dest + "/e /h /i");
    system(command.c_str());
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
#elif __APPLE__
    std::string command = ("cp -a " + src + " " + dest);
    system(command.c_str());
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
#else
    return errorHandler.generateGenericError("OS not supported");

#endif
}

HDTBReturnItem MachineSubModulePerform::winupdate()
{
    std::cout << std::endl << "Launch windows update" << std::endl;
    return errorHandler.generateGenericError("Not yet created");
}

HDTBReturnItem MachineSubModulePerform::scrub()
{
#ifdef _WIN32
    system("start lib\\machine\\scrub.bat");
    std::cout << std::endl << "Cleanup complete.." << std::endl;
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
#elif __APPLE__
    return errorHandler.generateGenericError("OS not yet supported");
#else
    return errorHandler.generateGenericError("OS not supported");
#endif
}

HDTBReturnItem MachineSubModulePerform::fixJava()
{
#ifdef _WIN32

    system("start lib\\machine\\fixJava.bat");
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");

#elif __APPLE__
    return errorHandler.generateGenericError("OS not yet supported");
#else
    return errorHandler.generateGenericError("OS not supported");
#endif
}

}
