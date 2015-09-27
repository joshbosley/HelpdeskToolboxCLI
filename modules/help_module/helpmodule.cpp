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
                std::pair<std::string, int>
                ("commands", HDTB_HELP_COMMAND_LIST)
                );

    // Report the current os
    commands.insert(
                std::pair<std::string, int>
                ("os", HDTB_HELP_COMMAND_OS)
                );



}

// Process the input, and return a returnItem
struct returnItem HelpModule::processRequest(std::vector<std::string> args)
{
    // Create returnItem, and set default state
    struct returnItem ri(HDTB_RETURN_BAD, "None");

    // Add arguments to module input history
    history.push(args);

    // Handle arguments passed in, and make sure to update returnItem

    if(args.size() == 1)
    {
        std::cout << std::endl <<
                     "<module_name> <commands>"
                  << std::endl;

        std::cout << std::endl <<
                     "Type 'help commands' to view all help commands"
                  << std::endl;

        // Tell boxcore to print modules, and set to good return
        ri.comm = 'M';
        ri.retCode = HDTB_RETURN_GOOD;
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
            unsigned outputControl = 0;

            switch(commands[args[1]])
            {
            case HDTB_HELP_COMMAND_OS:
                std::cout << std::endl << "Current OS : " << HDTB_OS << std::endl;
                ri.retCode = HDTB_RETURN_GOOD;
                break;

            case HDTB_HELP_COMMAND_LIST:
                std::cout << std::endl << "Available help commands : " << std::endl;

                for(std::map<std::string, int>::iterator it = commands.begin();
                    it != commands.end(); ++it)
                {
                    // Print off columns of 5
                    if(++outputControl % 5 == true)
                        std::cout << std::endl;

                    // Print command name
                    std::cout << std::setw(10) << it->first;
                }
                ri.retCode = HDTB_RETURN_GOOD;
                break;


            default:
                break;
            }
        }
    }

    return ri;
}

}
