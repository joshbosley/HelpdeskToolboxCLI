#ifndef HDTB_SOFTWAREMODULE_H
#define HDTB_SOFTWAREMODULE_H


#include "softwaremoduledirectory.h"

// Required
#include "../../core/datatypes.h"
#include "../framework/_modules/modulebase.h"

// Sub-modules
#include "sub-modules/softwaresubmoduleinstall.h"
#include "sub-modules/softwaresubmoduleremove.h"
#include "sub-modules/softwaresubmodulemodify.h"

// Required
namespace hdtoolbox
{
    class SoftwareModule : public ModuleBase
    {
        public:
            SoftwareModule();

            HDTBReturnItem processRequest(std::vector<std::string>);

        private:
            SoftwareSubModuleInstall install;
            SoftwareSubModuleRemove remove;
            SoftwareSubModuleModify modify;

    };
}
#endif // HDTB_SOFTWAREMODULE_H

