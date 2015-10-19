#ifndef MACHINESUBMODULEGET_H
#define MACHINESUBMODULEGET_H

// Machine handle codes
#include "../machinemoduledirectory.h"

// Required
#include "../../../core/datatypes.h"
#include "../../framework/_modules/modulebase.h"

namespace hdtoolbox
{

class MachineSubModuleGet : public ModuleBase
{
public:
    MachineSubModuleGet();

    // Required
    HDTBReturnItem processRequest(std::vector<std::string>);

private:

    HDTBReturnItem getRAM();
    HDTBReturnItem getHDD();
    HDTBReturnItem getCPU();
    HDTBReturnItem getOS();
    HDTBReturnItem getNetInfo();
};

}
#endif // MACHINESUBMODULEGET_H
