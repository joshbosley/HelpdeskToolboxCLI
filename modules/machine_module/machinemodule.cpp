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

    case HDTB_MACHINE_ADD:

        // Remove first arg - No longer required
        args.erase(args.begin());

        // Call sub-module's processRequest function;
        return add.processRequest(args);
        break;

    case HDTB_MACHINE_EDIT:
        // Remove first arg - No longer required
        args.erase(args.begin());

        return edit.processRequest(args);
        break;

    case HDTB_MACHINE_REMOVE:
        // Remove first arg - No longer required
        args.erase(args.begin());

        return remove.processRequest(args);
        break;

    case HDTB_MACHINE_PERFORM:
        // Remove first arg - No longer required
        args.erase(args.begin());

        return perform.processRequest(args);
        break;

    case HDTB_MACHINE_GET:
        // Remove first arg - No longer required
        args.erase(args.begin());

        return get.processRequest(args);
        break;

    default:
        break;
    }

    return errorHandler.generateGenericError("Uncaught return");
}

}
