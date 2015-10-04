#ifndef HDTB_NETWORKCLIENT_H
#define HDTB_NETWORKCLIENT_H

#include "../networkdirectory.h"

#include "../../../core/datatypes.h"
#include "../../framework/_modules/modulebase.h"

namespace hdtoolbox
{
class NetworkClient : public ModuleBase
{
public:
    NetworkClient();

    HDTBReturnItem processRequest(std::vector<std::string>);

    bool getConnectionSetState();
    bool getBlindCommState();
    bool getCommState();

private:

    typedef struct connInfo
    {
        int port;
        std::string address;
    } connInfo;

    typedef struct stateInfo
    {
        bool comm, blindComm, connectionSet;
    } stateInfo;

    stateInfo statusInfo;
    connInfo connectionInfo;

    HDTBReturnItem setConnectionInfo(std::string address, int port);
    HDTBReturnItem send(std::string message);
    HDTBReturnItem initiateComms();
    HDTBReturnItem initiateBlindComms();
};
}
#endif // HDTB_NETWORKCLIENT_H
