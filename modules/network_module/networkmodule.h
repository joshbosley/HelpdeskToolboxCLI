#ifndef HDTB_NETWORKMODULE_H
#define HDTB_NETWORKMODULE_H

#include "networkdirectory.h"
#include "../../core/datatypes.h"
#include "../framework/_modules/modulebase.h"

// Submodules
#include "sub-modules/networkclient.h"

namespace hdtoolbox
{

class NetworkModule : public ModuleBase
{
public:
    NetworkModule();

    HDTBReturnItem processRequest(std::vector<std::string>);

private:

    HDTBReturnItem setupConnection(std::string host, std::string port);

    HDTBReturnItem ping(std::string ip, std::string count);
    HDTBReturnItem reset();
    HDTBReturnItem reach(std::string host, std::string port, std::string message);
    HDTBReturnItem knock();
    HDTBReturnItem comm();
    HDTBReturnItem kill();

    NetworkClient netClient;
};

}
#endif // HDTB_NETWORKMODULE_H
