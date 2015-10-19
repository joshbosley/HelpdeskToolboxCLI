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

#elif __APPLE__
    system("sudo rm ~/Library/Safari/History.plist");
    system("sudo rm ~/Library/Safari/Downloads.plist");
    system("sudo rm ~/Library/Safari/HistoryIndex.sk");
    system("sudo rm ~/Library/Safari/LastSession.plist");
    system("sudo rm ~/Library/Safari/TopSites.plist");
    system("sudo rm -rf ~/Library/Caches/com.apple.safari");

    system("sudo rm -rf ~/.Trash/*");
#endif
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
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

#ifdef _WIN32

    std::string exec = ("start powershell.exe -ExecutionPolicy Bypass -File lib\\machine\\performUpdates.ps1 \n" );
    system(exec.c_str());

    return HDTBReturnItem(HDTB_RETURN_GOOD, "");

#endif
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


}
