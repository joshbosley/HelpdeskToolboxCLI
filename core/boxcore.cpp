#include "boxcore.h"

namespace hdtoolbox
{

BoxCore::BoxCore()
{
    session = false;
    moduleHasPrompt = false;
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
        /*
                TODO:
                Handle return codes

        */
    }
}

returnItem BoxCore::processRequest(std::vector<std::string> args)
{
    struct returnItem ri('G', "None");

    std::cout << "Processing request arguments : " << std::endl;

    std::for_each(
                    args.cbegin(),
                    args.cend(),
                    [] (std::string s) {std::cout << s << std::endl;}
                );

    return ri;
}

}

