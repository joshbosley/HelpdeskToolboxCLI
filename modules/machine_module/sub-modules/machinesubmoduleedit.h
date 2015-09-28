#ifndef MACHINESUBMODULEEDIT_H
#define MACHINESUBMODULEEDIT_H

// Machine handle codes
#include "../machinemoduledirectory.h"

// Required
#include "../../../core/datatypes.h"
#include "../../framework/modulebase.h"

namespace hdtoolbox
{

class MachineSubModuleEdit : public ModuleBase
{
public:
    MachineSubModuleEdit();

    // Required
    HDTBReturnItem processRequest(std::vector<std::string>);

private:

    HDTBReturnItem editDomain(std::string);
    HDTBReturnItem editWorkGroup(std::string);
    HDTBReturnItem editUAC(std::string);
    HDTBReturnItem editComputerName(std::string);
    HDTBReturnItem editIE(std::string);
};

}
#endif // MACHINESUBMODULEEDIT_H
