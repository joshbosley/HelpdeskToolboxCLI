#include "machinesubmoduleadd.h"

// Required
namespace hdtoolbox
{

MachineSubModuleAdd::MachineSubModuleAdd() :
    ModuleBase(HDTB_MACHINE_ADD,
               "Machine SubModule - Add",
               "The sub-module that handles the add command for"
               "the Machine Module")
{
    commands.insert(
                HDTBMapItem
                ("domain", HDTB_MACHINE_CMD_DOMAIN)
                );

    commands.insert(
                HDTBMapItem
                ("workgroup", HDTB_MACHINE_CMD_WORKGROUP)
                );

    commands.insert(
                HDTBMapItem
                ("admin", HDTB_MACHINE_CMD_ADMINISTRATOR)
                );
}

HDTBReturnItem MachineSubModuleAdd::processRequest(std::vector<std::string> args)
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

        if(HDTB_OS == "WIN_OS")
            ri = addToDomain(args[2]);
        else if (HDTB_OS == "MAC_OS")
            ri.message = "Operation not supported on MAC OS";
        else
            ri.message = "Unknown OS, operation not supported";
        break;

    case HDTB_MACHINE_CMD_WORKGROUP:
        ri = addToWorkGroup(args[2]);
        break;

    case HDTB_MACHINE_CMD_ADMINISTRATOR:
        ri = addAnAdministrator(args[2]);
        break;

    default:
        break;
    }

    return ri;

}

/*

                Add the machine to a domain

*/
HDTBReturnItem MachineSubModuleAdd::addToDomain(std::string domain)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << " DOMAIN : " << domain;

    ri.message = "Not yet created";
    return ri;
}

/*

                Add the machine to a workgroup

*/
HDTBReturnItem MachineSubModuleAdd::addToWorkGroup(std::string group)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Add to group : " << group << std::endl;

    ri.message = "Not yet created";
    return ri;
}

/*

                Add an administrator

*/
HDTBReturnItem MachineSubModuleAdd::addAnAdministrator(std::string accountName)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Add admin : " << accountName << std::endl;

    ri.message = "Not yet created";
    return ri;
}

}

