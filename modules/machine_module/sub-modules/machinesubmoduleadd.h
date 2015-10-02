#ifndef MACHINESUBMODULEADD_H
#define MACHINESUBMODULEADD_H

// Machine handle codes
#include "../machinemoduledirectory.h"

// Required
#include "../../../core/datatypes.h"
#include "../../framework/_modules/modulebase.h"


// Required
namespace hdtoolbox
{

class MachineSubModuleAdd : public ModuleBase
{
public:
    MachineSubModuleAdd();

    // Required
    HDTBReturnItem processRequest(std::vector<std::string>);

private:

    HDTBReturnItem addToDomain(std::string);
    HDTBReturnItem addToWorkGroup(std::string);
    HDTBReturnItem addAnAdministrator(std::string);
};

}

#endif // MACHINESUBMODULEADD_H
