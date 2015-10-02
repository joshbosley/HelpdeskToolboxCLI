#ifndef HDTB_SSMODULE_H
#define HDTB_SSMODULE_H

#define HDTB_SS_COMMAND_INSTALL 0
#define HDTB_SS_COMMAND_REMOVE 1
#define HDTB_SS_COMMAND_MODIFY 2

#include "../../core/datatypes.h"
#include "../framework/_modules/modulebase.h"

namespace hdtoolbox
{
    class SSModule : public ModuleBase
    {
        public:
            SSModule();

            HDTBReturnItem processRequest(std::vector<std::string>);

        private:
            HDTBReturnItem performInstall(std::string software);
            HDTBReturnItem performRemove(std::string software);
            HDTBReturnItem performModify(std::string software);


    };
}
#endif // SSMODULE_H
