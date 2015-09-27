#include "modulebase.h"


namespace hdtoolbox
{

ModuleBase::ModuleBase(unsigned int id, std::string name, std::string description)
{
    this->moduleId = id;
    this->moduleName = name;
    this->moduleDesc = description;
}

HDTBReturnItem ModuleBase::displayAvailableCommands()
{
    unsigned outputControl = 0;
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    std::cout << std::endl << "Available commands for [" << moduleName  << "]" << std::endl;

    for(HDTBMapIterator it = commands.begin();
        it != commands.end(); ++it)
    {
        // Print off columns of 5
        if(++outputControl % 5 == true)
            std::cout << std::endl;

        // Print command name
        std::cout << std::setw(10) << it->first;
    }
    std::cout << std::endl << std::endl;
    ri.retCode = HDTB_RETURN_GOOD;
    return ri;

}

}
