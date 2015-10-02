#ifndef MACHINESUBMODULEREMOVE_H
#define MACHINESUBMODULEREMOVE_H

// Machine handle codes
#include "../machinemoduledirectory.h"

// Required
#include "../../../core/datatypes.h"
#include "../../framework/_modules/modulebase.h"

namespace hdtoolbox
{

class MachineSubModuleRemove : public ModuleBase
{
public:
    MachineSubModuleRemove();

    // Required
    HDTBReturnItem processRequest(std::vector<std::string>);

private:

    HDTBReturnItem remDomain(std::string);
    HDTBReturnItem remWorkGroup();
    HDTBReturnItem remAccount(std::string);
};

}
#endif // MACHINESUBMODULEREMOVE_H
