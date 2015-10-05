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
        // Connection information
        int port, sock, block;
        std::string address;

        // Object connected to
        struct sockaddr_in addr_in;

    } connInfo;

    typedef struct stateInfo
    {
        // Stated of conenction type
        bool comm, blindComm, connectionSet;

        // Data last received from socket
        std::string data_received;
    } stateInfo;

    stateInfo statusInfo;
    connInfo connectionInfo;

    // Methods accessed by process request
    HDTBReturnItem setConnectionInfo(std::string address, int port);
    HDTBReturnItem send(std::string message);
    HDTBReturnItem initiateComms();
    HDTBReturnItem initiateBlindComms();
    HDTBReturnItem kill();

    // Methods accessed by private class methods
    bool send_data(std::string data);
    bool recieve_data();
    void close_current();
};
}
#endif // HDTB_NETWORKCLIENT_H
