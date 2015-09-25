#ifndef HDTB_MODULEBASE_H
#define HDTB_MODULEBASE_H

#include <vector>
#include <string>
#include <iostream>
#include "returnitem.h"
#include "returncodes.h"
#include "moduledirectory.h"

/*

    Base class for HDTB Modules

*/

namespace hdtoolbox
{

class ModuleBase
{
public:
    ModuleBase(unsigned int id,
               std::string name,
               std::string description);

private:

    unsigned int moduleId;
    std::string moduleName;
    std::string moduleDesc;

};

}

#endif // HDTB_MODULEBASE_H
