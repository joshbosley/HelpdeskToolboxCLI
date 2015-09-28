#include "machinesubmoduleget.h"

namespace hdtoolbox
{

MachineSubModuleGet::MachineSubModuleGet() :
    ModuleBase(HDTB_MACHINE_GET,
               "Machine SubModule - Get",
               "The sub-module that handles the get command for"
               "the Machine Module")
{
    commands.insert(
                HDTBMapItem
                ("mem", HDTB_MACHINE_CMD_RAM)
                );

    commands.insert(
                HDTBMapItem
                ("hdd", HDTB_MACHINE_CMD_HDD)
                );

    commands.insert(
                HDTBMapItem
                ("cpu", HDTB_MACHINE_CMD_CPU)
                );

    commands.insert(
                HDTBMapItem
                ("os", HDTB_MACHINE_CMD_OS)
                );
}

HDTBReturnItem MachineSubModuleGet::processRequest(std::vector<std::string> args)
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

    case HDTB_MACHINE_CMD_RAM:
        ri = getRAM();
        break;

    case HDTB_MACHINE_CMD_HDD:
        ri = getHDD();
        break;

    case HDTB_MACHINE_CMD_CPU:
        ri = getCPU();
        break;

    case HDTB_MACHINE_CMD_OS:
        ri = getOS();
        break;

    default:
        break;
    }

    return ri;
}

HDTBReturnItem MachineSubModuleGet::getRAM()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    ri.message = "Not yet created";
    return ri;
}

HDTBReturnItem MachineSubModuleGet::getHDD()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    ri.message = "Not yet created";
    return ri;
}

HDTBReturnItem MachineSubModuleGet::getCPU()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    ri.message = "Not yet created";
    return ri;
}

HDTBReturnItem MachineSubModuleGet::getOS()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    ri.message = "Not yet created";
    return ri;
}

}
