#ifndef SOFTWARESUBMODULEINSTALL_H
#define SOFTWARESUBMODULEINSTALL_H

// Software handle codes
#include "../softwaremoduledirectory.h"

// Required
#include "../../../core/datatypes.h"
#include "../../framework/_modules/modulebase.h"


// Required
namespace hdtoolbox
{
    class SoftwareSubModuleInstall : public ModuleBase
    {
        public:
            SoftwareSubModuleInstall();

            // Required
            HDTBReturnItem processRequest(std::vector<std::string>);

        private:
            HDTBReturnItem installJava();
            HDTBReturnItem installKACE();
            HDTBReturnItem installAvira();

    };
}
#endif // SOFTWARESUBMODULEINSTALL

