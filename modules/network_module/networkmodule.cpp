#include "networkmodule.h"

namespace hdtoolbox
{

NetworkModule::NetworkModule() :
    ModuleBase(HDTB_CODE_NETWORK,
               "Netowrk Module",
               "A network interface module.")
{

}

HDTBReturnItem NetworkModule::processRequest(std::vector<std::__1::string>)
{
    return errorHandler.generateGenericError("Under Construction");
}

}
