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

    commands.insert(
                HDTBMapItem
                ("page", HDTB_HELP_COMMAND_PAGE)
                );

    // END REQUIRED

    // Config file for manual pages
    manConfigFile = "./pages/directory.conf";
    loadManualPages();
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
                // Call to super class
                ri = displayAvailableCommands();
                break;

            case HDTB_HELP_COMMAND_ME:
                ri = displayHelpMe();
                break;

            case HDTB_HELP_COMMAND_PAGE:
                if(args.size() == 3)
                    ri = displayManualPage(args[2]);
                else
                {
                    ri.retCode = HDTB_RETURN_BAD;
                    ri.message = "No module name given";
                    return ri;
                }
                break;

            default:
                break;
            }
        }
    }

    return ri;
}

HDTBReturnItem HelpModule::loadManualPages()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    manualPages.clear();

    std::ifstream file;
    std::string manFileName;
    file.open(manConfigFile);

    if(file.is_open())
    {
        // Open config file and get the names of the modules installed
        while(!file.eof())
        {
            // Get file name from config
            std::getline(file, manFileName);

            // Open the file pulled from config
            std::string currLine;
            std::ifstream currManFile;
            std::vector<std::string> manContent;
            currManFile.open("pages/" + manFileName);

            if(currManFile.is_open())
            {
                // Copy its contents into a vector
                while(!currManFile.eof())
                {
                    std::getline(currManFile, currLine);
                    manContent.push_back(currLine);
                }

                // Load it into manualPages
                manualPages.insert(
                            std::pair<std::string, std::vector<std::string>>
                            (manFileName, manContent)
                            );
            }
            else
            {
                ri.message = "Page(s) file not loaded.";
            }
            currManFile.close();
        }
    }
    else
    {
        ri.message = "pages/directory.conf not found. Check your cwd.";
    }
    file.close();
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

HDTBReturnItem HelpModule::displayManualPage(std::string moduleName)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    if(manualPages.size() == 0)
    {
        std::cout << std::endl << "There doesn't appear to be any manual pages. "
                                  "Is the pages folder containing the "
                                  "data within the current working directory?" <<
                     std::endl;
        ri.message = "No manual pages found";
        return ri;
    }

    std::cout << "Requesting manual for " << moduleName << std::endl;
    if(manualPages.find(moduleName) == manualPages.end())
    {
        ri.message = "No manual found for [" + moduleName + "] ";
        return ri;
    }
    else
    {
        std::cout << std::endl << "Showing manual for : [" << moduleName << "]" << std::endl;
        // manualPages.at(moduleName) [returns]-> Vector<string>
        for( std::vector<std::string>::iterator it = manualPages.at(moduleName).begin();
             it < manualPages.at(moduleName).end();
             it++)
        {
            std::cout << *it << std::endl;
        }
        ri.retCode = HDTB_RETURN_GOOD;
    }
    return ri;
}

}
