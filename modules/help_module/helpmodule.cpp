#include "helpmodule.h"

namespace hdtoolbox
{

// Adding your module id, and information here is required
HelpModule::HelpModule() :
    ModuleBase(HDTB_CODE_HELP,
               "Help Module",
               "A module to provide help.")
{

    // Populate recognized commands

    // List commands that help will recognize
    commands.insert(
                HDTBMapItem
                ("commands", HDTB_HELP_COMMAND_LIST)
                );

    // Report the current os
    commands.insert(
                HDTBMapItem
                ("os", HDTB_HELP_COMMAND_OS)
                );

    // For when users need a 'special' sort of help
    commands.insert(
                HDTBMapItem
                ("me", HDTB_HELP_COMMAND_ME)
                );
}

// Process the input, and return a returnItem
HDTBReturnItem HelpModule::processRequest(std::vector<std::string> args)
{
    // Create returnItem, and set default state
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    // Add arguments to module input history
    history.push(args);

    // Handle arguments passed in, and make sure to update returnItem

    if(args.size() == 1)
    {
        ri = displaySimpleHelp();
    }
    else
    {
        // Ensure command key exists within map.
        if(commands.find(args[1]) == commands.end())
        {
            // Command not found, set return item to indicate
            ri.retCode = HDTB_RETURN_BAD;
            ri.message = "Command not found";
            return ri;
        }
        else
        {
            switch(commands[args[1]])
            {
            case HDTB_HELP_COMMAND_OS:
                ri = displayCurrentOS();
                break;

            case HDTB_HELP_COMMAND_LIST:
                ri = displayAvailableCommands();
                break;

            case HDTB_HELP_COMMAND_ME:
                ri = displayHelpMe();
                break;

            default:
                break;
            }
        }
    }

    return ri;
}

HDTBReturnItem HelpModule::displayAvailableCommands()
{
    unsigned outputControl = 0;
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    std::cout << std::endl << "Available help commands : " << std::endl;

    for(HDTBMapIterator it = commands.begin();
        it != commands.end(); ++it)
    {
        // Print off columns of 5
        if(++outputControl % 5 == true)
            std::cout << std::endl;

        // Print command name
        std::cout << std::setw(10) << it->first;
    }
    ri.retCode = HDTB_RETURN_GOOD;
    return ri;
}

HDTBReturnItem HelpModule::displaySimpleHelp()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    std::cout << std::endl <<
                 "Example : <module_name> <commands>"
              << std::endl;

    std::cout << std::endl <<
                 "Type 'help commands' to view all help commands"
              << std::endl;

    // Tell boxcore to print modules, and set to good return
    ri.comm = 'M';
    ri.retCode = HDTB_RETURN_GOOD;
    return ri;
}

HDTBReturnItem HelpModule::displayCurrentOS()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    std::cout << std::endl << "Current OS : " << HDTB_OS << std::endl;
    ri.retCode = HDTB_RETURN_GOOD;
    return ri;
}

HDTBReturnItem HelpModule::displayHelpMe()
{
    // Remove this once screen manager is created
    std::cout << std::string( 100, '\n' );

    std::cout << std::endl <<
     "It looks like you could use some help." << std::endl <<
     "In order to do anything, you need to type in the name of the module you want to run"
     " and then input a command, or series of commands for that module to process."
     << std::endl;

    // Return showing the simple help, which will tell the core to show modules
    return displaySimpleHelp();
}

}
