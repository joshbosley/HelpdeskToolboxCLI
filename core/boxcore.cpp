#include "boxcore.h"

namespace hdtoolbox
{

BoxCore::BoxCore()
{
    session = false;
    moduleHasPrompt = false;

    struct command j("Core", "Init");
    history.push(j);
}

void BoxCore::beginHumanInteraction()
{
    session = true;
    std::string line, temp;
    struct returnItem ri;

    while(session && std::getline(std::cin, line))
    {
        temp = line.substr(line.find_first_of(" \t")+1);

    }
}

returnItem BoxCore::processRequest(command)
{

}

}

