#include "machinemodule.h"

namespace hdtoolbox
{

MachineModule::MachineModule() :
ModuleBase(HDTB_CODE_MACHINE,
           "Machine Module",
           "A module to do most machine editing")
{
    commands.insert(
                HDTBMapItem
                ("add", HDTB_MACHINE_ADD)
                );

    commands.insert(
                HDTBMapItem
                ("edit", HDTB_MACHINE_EDIT)
                );

    commands.insert(
                HDTBMapItem
                ("remove", HDTB_MACHINE_REMOVE)
                );

    commands.insert(
                HDTBMapItem
                ("perform", HDTB_MACHINE_PERFORM)
                );

    commands.insert(
                HDTBMapItem
                ("get", HDTB_MACHINE_GET)
                );
}

HDTBReturnItem MachineModule::processRequest(std::vector<std::string> args)
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

    case HDTB_MACHINE_ADD:

        // Remove first arg - No longer required
        args.erase(args.begin());

        // Call sub-module's processRequest function;
        ri = add.processRequest(args);
        break;

    case HDTB_MACHINE_EDIT:
        ri.message = "NOT YET CREATED";
        break;

    case HDTB_MACHINE_REMOVE:
        ri.message = "NOT YET CREATED";
        break;

    case HDTB_MACHINE_PERFORM:
        ri.message = "NOT YET CREATED";
        break;

    case HDTB_MACHINE_GET:
        ri.message = "NOT YET CREATED";
        break;

    default:
        break;
    }

    return ri;
}

}
