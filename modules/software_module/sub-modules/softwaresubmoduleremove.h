#ifndef SOFTWARESUBMODULEREMOVE_H
#define SOFTWARESUBMODULEREMOVE_H

#include "../softwaremoduledirectory.h"

// Required
#include "../../../core/datatypes.h"
#include "../../framework/_modules/modulebase.h"

namespace hdtoolbox
{

class SoftwareSubModuleRemove : public ModuleBase
{
public:
    SoftwareSubModuleRemove();

    // Required
    HDTBReturnItem processRequest(std::vector<std::string>);

private:

    HDTBReturnItem removeJava();
    HDTBReturnItem removeKACE();
    HDTBReturnItem removeAvira();
};

}

#endif // SOFTWARESUBMODULEREMOVE

