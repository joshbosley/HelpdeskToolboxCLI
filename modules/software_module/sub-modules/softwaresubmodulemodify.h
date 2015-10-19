#ifndef SOFTWARESUBMODULEMODIFY_H
#define SOFTWARESUBMODULEMODIFY_H

// Software handle codes
#include "../softwaremoduledirectory.h"

// Required

#include "../../../core/datatypes.h"
#include "../../framework/_modules/modulebase.h"


// Required
namespace hdtoolbox
{
    class SoftwareSubModuleModify : public ModuleBase
    {
        public:
            SoftwareSubModuleModify();

            // Required
            HDTBReturnItem processRequest(std::vector<std::string>);

        private:
            HDTBReturnItem modifyJava();
            HDTBReturnItem modifyIE(std::string);
    };
}
#endif // SOFTWARESUBMODULEMODIFY

