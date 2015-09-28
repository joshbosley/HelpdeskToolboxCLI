#include "machinesubmoduleremove.h"

// Required
namespace hdtoolbox
{

MachineSubModuleRemove::MachineSubModuleRemove() :
    ModuleBase(HDTB_MACHINE_REMOVE,
               "Machine SubModule - Remove",
               "The sub-module that handles the remove command for"
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
                ("account", HDTB_MACHINE_CMD_UNAME)
                );
}

HDTBReturnItem MachineSubModuleRemove::processRequest(std::vector<std::string> args)
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
        if (args.size() != 3)
        {
            ri.message = "No domain name given";
            return ri;
        }
        else
        {
            if(HDTB_OS == "WIN_OS")
                ri = remDomain(args[2]);
            else if (HDTB_OS == "MAC_OS")
                ri.message = "Operation not supported on MAC OS";
            else
                ri.message = "Unknown OS, operation not supported";
        }
        break;

    case HDTB_MACHINE_CMD_WORKGROUP:
        if (args.size() != 3)
        {
            ri.message = "No workgroup name given";
            return ri;
        }
        else
        {
            ri = remWorkGroup(args[2]);
        }
        break;

    case HDTB_MACHINE_CMD_UNAME:
        if (args.size() != 3)
        {
            ri.message = "No account name given";
            return ri;
        }
        else
        {
            ri = remAccount(args[2]);
        }
        break;

    default:
        break;
    }

    return ri;
}

HDTBReturnItem MachineSubModuleRemove::remDomain(std::string domain)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Remove from domain : " << domain << std::endl;

    ri.message = "Not yet created";
    return ri;
}

HDTBReturnItem MachineSubModuleRemove::remWorkGroup(std::string workgroup)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Remove from workgroup : " << workgroup << std::endl;

    ri.message = "Not yet created";
    return ri;
}

HDTBReturnItem MachineSubModuleRemove::remAccount(std::string account)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Remove account : " << account << std::endl;

    ri.message = "Not yet created";
    return ri;
}

}

