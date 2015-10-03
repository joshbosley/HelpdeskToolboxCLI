#include "boxcore.h"

namespace hdtoolbox
{

BoxCore::BoxCore()
{
#ifdef _WIN32
    system("color 0A");
    SetConsoleTitle(TEXT("Helpdesk Toolbox - Windows Build"));
#elif __APPLE__
    std::cout << HDTB_PUT_RED;
#endif


    session = false;
    prompt = "core >>";

    /*
           (Step 4)
           Register modules into moduleMap
    */

    moduleMap.insert(
                HDTBMapItem
                ("help", HDTB_CODE_HELP)
                );

    // Add new modules below this line

    moduleMap.insert(
                HDTBMapItem
                ("machine", HDTB_CODE_MACHINE)
                );

    moduleMap.insert(
                    HDTBMapItem
                    ("software", HDTB_CODE_SS)
                    );

    moduleMap.insert(
                    HDTBMapItem
                    ("network", HDTB_CODE_NETWORK)
                    );
}

void BoxCore::beginHumanInteraction()
{
    session = true;
    std::string line;
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << "Initiating. Type 'exit' to end session." << std::endl;

    while(session)
    {
        // Give a prompt, and retrieve input
        std::cout << std::endl << prompt << " ";
        std::getline(std::cin, line);

        // Make sure that there was actually some input
        if(line == "" )
            continue;

        // Split input into words
        std::istringstream iss(line);
        std::vector<std::string> args{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}};

        // Add request to history
        history.push(args);

        // See if user wants to exit or clear the screen
        if(args[0] == "exit")
        {
            session = false;
            continue;
        }
        else if(args[0] == "clear")
        {
#ifdef _WIN32
            system("cls");
#else
            system("clear");
#endif
            // Once the clear command has been done, skip processing
            continue;
        }

        // Process request
        ri = processRequest(args);

        // Handle ri by return code
        switch(ri.retCode)
        {
        case HDTB_RETURN_GOOD:
            // Do nothing at the moment if everything is good
            break;

        case HDTB_RETURN_BAD:
            std::cout << std::endl << "[HDTB_RETURN_BAD] : Message > " << ri.message << std::endl;
            break;

        case HDTB_RETURN_EXIT:
            // Return HDTB_RETURN_EXIT from module to initiate exit
            session = false;
            break;

        default:
            errHandler.generateGenericError("Default reached in human interaction");
            break;
        }
    }

    // Exit message.
    std::cout << std::endl << "Exiting. Goodbye. :-]" << std::endl << std::endl;

#ifdef __APPLE__
       std::cout << HDTB_PUT_RESET;
#endif
}

HDTBReturnItem BoxCore::processRequest(std::vector<std::string> args)
{
    // Default return
    HDTBReturnItem ri(HDTB_RETURN_BAD, "None");

    unsigned outputControl = 0;

    // Ensure module key exists within map.
    if(moduleMap.find(args[0]) == moduleMap.end())
    {
        std::cout << "No module triggered by [" << args[0] << "] " << std::endl;
        ri.retCode = HDTB_RETURN_GOOD;
        std::cout << std::endl << "Type 'help me' to figure out what to do. " << std::endl;
    }
    else
    {
        /*
                (Step 5)
                Add module triggers here to this switch statement.

        */

        switch(moduleMap.at(args[0]))
        {

        /*
                    Help Module
        */
        case HDTB_CODE_HELP:

            // Set returnItem to whatever module gives us
            ri = modBox.helpModule.processRequest(args);

            /*
                    Here to break; not required for other modules.
            */
            if(ri.comm == 'M')
            {
                std::cout << std::endl << "Available modules : " << std::endl;

                // List modules [Non-Help module function]
                for(HDTBMapIterator it = moduleMap.begin();
                    it != moduleMap.end(); ++it)
                {
                    // Print off columns of 5
                    if(++outputControl % 5 == true)
                        std::cout << std::endl;

                    // Print module name
                    std::cout << std::setw(10) << it->first;
                }
            }

            std::cout << std::endl;
            break;

        /*
                        Machine Module
        */
        case HDTB_CODE_MACHINE:
            ri = modBox.machineModule.processRequest(args);
            break;

        /*
         *          Example of adding new module
         *
        case HDTB_CODE_<NEWITEM>:
            ri = modBox.NEW_MODULE.processRequest(args);
            break;
        */

        case HDTB_CODE_SS:
            ri = modBox.ssModule.processRequest(args);
            break;

        case HDTB_CODE_NETWORK:
            ri = modBox.networkModule.processRequest(args);
            break;

        default:
            return errHandler.generateGenericError("Default reached in core module switch");
            break;
        }
    }
    return ri;
}
}

