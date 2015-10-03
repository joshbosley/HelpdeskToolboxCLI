#ifndef HDTB_NETWORKMODULE_H
#define HDTB_NETWORKMODULE_H

#include "networkdirectory.h"
#include "../../core/datatypes.h"
#include "../framework/_modules/modulebase.h"

namespace hdtoolbox
{

class NetworkModule : public ModuleBase
{
public:
    NetworkModule();

    HDTBReturnItem processRequest(std::vector<std::string>);

private:

    HDTBReturnItem ping(std::string ip, std::string count);
    HDTBReturnItem reset();
    HDTBReturnItem blast();
    HDTBReturnItem knock();
    HDTBReturnItem comm();

};

}
#endif // HDTB_NETWORKMODULE_H
