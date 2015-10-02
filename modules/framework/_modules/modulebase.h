#ifndef HDTB_MODULEBASE_H
#define HDTB_MODULEBASE_H

#include <map>
#include <stack>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iostream>

#include "moduledirectory.h"
#include "../_types/returnitem.h"
#include "../_types/returncodes.h"
#include "../../../core/datatypes.h"

// Error reporter
#include "../_errors/errorbase.h"

// Pre-defined os variables
#include "../_os/osinfo.h"
#include "../_os/osincludes.h"

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

protected:

    // A map to store recognized commands
    HDTBStandardMap commands;

    // For saving command history
    HDTBHistory history;

    // Displaying loaded commands
    HDTBReturnItem displayAvailableCommands();

    // Error Handler
    ErrorBase errorHandler;

private:

    // Module registration information
    unsigned int moduleId;
    std::string moduleName;
    std::string moduleDesc;

};

}

#endif // HDTB_MODULEBASE_H
