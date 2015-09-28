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
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    history.push(args);

    // Make sure commands are given
    if(args.size() == 1)
    {
        // Call to super class
        displayAvailableCommands();

        ri.message = "No commands given";
        return ri;
    }

    // Make sure command exists
    if(commands.find(args[1]) == commands.end())
    {
        // Call to super class
        displayAvailableCommands();

        ri.retCode = HDTB_RETURN_BAD;
        ri.message = "Command not found";
        return ri;
    }

    //Handle command
    switch(commands[args[1]])
    {

    case HDTB_MACHINE_CMD_DOMAIN:
        ri = cleanup();
        break;

    case HDTB_MACHINE_CMD_COPY:
        if (args.size() != 4)
        {
            ri.message = "Copy requires a source, and a destination.";
            return ri;
        }
        else
        {
            ri = copy(args[2], args[3]);
        }

        break;

    case HDTB_MACHINE_CMD_WUPDATE:
        if(HDTB_OS == "WIN_OS")
            ri = winupdate();
        else
            ri.message = "Operation is windows specific.";
        break;

    case HDTB_MACHINE_CMD_SCRUB:
        ri = scrub();
        break;

    default:
        break;
    }

    return ri;
}

HDTBReturnItem MachineSubModulePerform::cleanup()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Perform cleanup... " << std::endl;

    ri.message = "Not yet created";
    return ri;
}

HDTBReturnItem MachineSubModulePerform::copy(std::string src, std::string dest)
{
    // Need to handle different platforms

    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Copy from :" << src << " to :" << dest << std::endl;

    ri.message = "Not yet created";
    return ri;
}

HDTBReturnItem MachineSubModulePerform::winupdate()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Launch windows update" << std::endl;

    ri.message = "Not yet created";
    return ri;
}

HDTBReturnItem MachineSubModulePerform::scrub()
{
    // Double check to make sure user wants to do this.
    // Handle each platform

    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Perform scrub" << std::endl;

    ri.message = "Not yet created";
    return ri;
}

}
