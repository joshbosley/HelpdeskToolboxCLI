#include "boxcore.h"

namespace hdtoolbox
{

BoxCore::BoxCore()
{
    session = false;

    /*
           (Step 4)
           Register modules into moduleMap
    */

    moduleMap.insert(
                std::pair<std::string, int>
                ("help", HDTB_CODE_HELP));

    // Add new modules below this line

}

void BoxCore::beginHumanInteraction()
{
    session = true;
    std::string line;
    struct returnItem ri('N',"");

    while(session && std::getline(std::cin, line))
    {
        // Split line into words
        std::istringstream iss(line);
        std::vector<std::string> args{
            std::istream_iterator<std::string>{iss},
            std::istream_iterator<std::string>{}};

        // Process request
        ri = processRequest(args);

        // Handle ri by return code
        switch(ri.retCode)
        {
        case HDTB_RETURN_GOOD:
            std::cout << std::endl <<
                         "[COMPLETE]"
                      << std::endl;
            break;

        case HDTB_RETURN_BAD:
            std::cout << "Something bad happened" << std::endl;
            break;

        case HDTB_RETURN_EXIT:
            session = false;
            std::cout << std::endl << "\t Exiting " << std::endl;
            break;
        default:
            break;
        }
    }
}

returnItem BoxCore::processRequest(std::vector<std::string> args)
{
    // Default return
    struct returnItem ri(HDTB_RETURN_BAD, "None");

    // Ensure module key exists within map.
    if(moduleMap.find(args[0]) == moduleMap.end())
    {
        std::cout << "No module triggered by [" << args[0] << "] " << std::endl;
    }
    else
    {
        /*
                (Step 5)
                Add module triggers here to this switch statement.

        */

        switch(moduleMap.at(args[0]))
        {
        case HDTB_CODE_HELP:

            // Set returnItem to whatever module gives us
            ri = modBox.helpModule.processRequest(args);
            break;

        /*
        case HDTB_CODE_<NEWITEM>:
            ri = modBox.NEW_MODULE.processRequest(args);
            break;
        */

        default:
            std::cout << "Default reached in process request. Handle Error" << std::endl;
            break;
        }
    }

    /*
    std::for_each(
                    args.cbegin(),
                    args.cend(),
                    [] (std::string s) {std::cout << s << std::endl;}
                );
    */

    return ri;
}

}

