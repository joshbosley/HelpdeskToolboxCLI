#include "networkclient.h"

namespace hdtoolbox
{

NetworkClient::NetworkClient() :
ModuleBase(HDTB_NETWORK_SUB_CLIENT,
           "Network Client Sub Module",
           "A module to provide a network client.")
{
    statusInfo.comm = false;
    statusInfo.blindComm = false;
    statusInfo.connectionSet = false;
    connectionInfo.block = 1024;

    commands.insert(
                HDTBMapItem
                ("setInfo", HDTB_CLIENT_LOAD)
                );
    commands.insert(
                HDTBMapItem
                ("send", HDTB_CLIENT_SEND)
                );
    commands.insert(
                HDTBMapItem
                ("initcomm", HDTB_CLIENT_COMM)
                );
    commands.insert(
                HDTBMapItem
                ("initblindcomm", HDTB_CLIENT_BLIND_COMM)
                );

    commands.insert(
                HDTBMapItem
                ("kill", HDTB_NETWORK_CMD_KILL)
                );
}

HDTBReturnItem NetworkClient::processRequest(std::vector<std::string> args)
{
/*
    std::cout << "ARGUMENTS IN" << std::endl;
    for(std::vector<std::string>::iterator it = args.begin();
        it != args.end(); ++it)
    {
        std::cout << "ARG :" << *it << std::endl;
    }
*/

    history.push(args);

    // Make sure command exists
    if(commands.find(args[0]) == commands.end())
    {
        // Call to super class
        displayAvailableCommands();

        for(std::vector<std::string>::iterator it = args.begin();
            it != args.end(); ++it)
        {
            std::cout << "ARG :" << *it << std::endl;
        }

        return errorHandler.generateGenericError("Unknown command");
    }

    //Handle command
    int c = 0;
    switch(commands[args[0]])
    {

    case HDTB_CLIENT_LOAD:
        if (args.size() != 3)
        {
            std::cout << " CLIENT_LOAD " << std::endl;
            return HDTBReturnItem(HDTB_RETURN_BAD, "not enough args -setinfo <<");
        }

        // Make sure port is int
        if( !( c = atoi(args[2].c_str())) )
            return HDTBReturnItem(HDTB_RETURN_BAD, "invalid port");

        return setConnectionInfo(args[1], c);
        break;

    case HDTB_CLIENT_SEND:
    {
        if (args.size() != 2)
            return HDTBReturnItem(HDTB_RETURN_BAD, "not enough args -fsend");

        HDTBReturnItem t = send(args[2]);
        if(t.retCode == HDTB_RETURN_GOOD)
        {
            if(recieve_data())
            {
                std::cout << "\t Recieved data back from " << connectionInfo.address << std::endl;
                t.message = statusInfo.data_received;
                t.comm = 'R';
            }
            else
            {
                std::cout << "\t Didn't recieve any data back from " << connectionInfo.address << std::endl;
                t.comm = 'N';
            }
            return t;
        }
        else
            return t;

        return send(args[2]);
        break;
    }

    case HDTB_CLIENT_COMM:
        return initiateComms();
        break;

    case HDTB_CLIENT_BLIND_COMM:
        return initiateBlindComms();
        break;

    case HDTB_NETWORK_CMD_KILL:
        return kill();
        break;

    default:
        return errorHandler.generateGenericError("Default accessed in command switch");
        break;
    }
    return errorHandler.generateGenericError("Uncaught return");
}

bool NetworkClient::getConnectionSetState()
{
    return statusInfo.connectionSet;
}

bool NetworkClient::getBlindCommState()
{
    return statusInfo.comm;
}

bool NetworkClient::getCommState()
{
    return statusInfo.blindComm;
}

HDTBReturnItem NetworkClient::setConnectionInfo(std::string address, int port)
{
    if(statusInfo.comm)
        return HDTBReturnItem(HDTB_RETURN_BAD,
                              "Can not process request. Comm currently open");

    if(statusInfo.blindComm)
        return HDTBReturnItem(HDTB_RETURN_BAD,
                              "Can not process request. Blind comm currently open");

#ifdef _WIN32

    std::cout << "WINDOWS NOT YET CODED " << std::endl << "[NetworkClient::setConnectionInfo(std::string address, int port)]" << std::endl;

    return errorHandler.generateGenericError("OS not yet supported");







#else

    // If its already connected, close it.
    if(statusInfo.connectionSet)
        close_current();

    // Set the connection information
    connectionInfo.port = port;
    connectionInfo.address = address;
    connectionInfo.sock = -1;

    //Create socket
    connectionInfo.sock = socket(AF_INET , SOCK_STREAM , 0);
    if (connectionInfo.sock == -1)
        return errorHandler.generateGenericError("Unable to create socket");

    // Make sure address is ip
    // Ignore the warning generated
    if(inet_addr(connectionInfo.address.c_str()) == -1)
    {
        struct hostent * record = gethostbyname(connectionInfo.address.c_str());
        if(record == NULL)
            return errorHandler.generateGenericError("Unable to resolve hostname");

        in_addr * addy = (in_addr * )record->h_addr;
        connectionInfo.address = inet_ntoa(*addy);

        std::cout << "Address resolved to : " << connectionInfo.address << std::endl;
    }

    // If we already have an ip, set the connection
    connectionInfo.addr_in.sin_addr.s_addr = inet_addr( connectionInfo.address.c_str() );
    connectionInfo.addr_in.sin_family = AF_INET;
    connectionInfo.addr_in.sin_port = htons( connectionInfo.port );

    std::cout << "\t Attempting to make connection. This might take a moment " << std::endl;

    // Make the connection
    if (connect(connectionInfo.sock ,
                (struct sockaddr *)&connectionInfo.addr_in ,
                 sizeof(connectionInfo.addr_in)) < 0)
    {
        return errorHandler.generateGenericError("Unable to connect to address");
    }
    else
    {
        // Indicate what was done
        statusInfo.connectionSet = true;
        return HDTBReturnItem(HDTB_RETURN_GOOD, "");
    }
#endif
}

HDTBReturnItem NetworkClient::send(std::string message)
{
    if (!statusInfo.connectionSet)
        return HDTBReturnItem(HDTB_RETURN_BAD, "Connection not setup. [setInfo]");

    if (!send_data(message))
        return errorHandler.generateGenericError("Unable to send data.");
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

HDTBReturnItem NetworkClient::initiateComms()
{
    if (!statusInfo.connectionSet)
        return HDTBReturnItem(HDTB_RETURN_BAD, "Connection not setup. [setInfo]");

#ifdef _WIN32
    return errorHandler.generateGenericError("Not yet created for this platform");
#else
    return errorHandler.generateGenericError("Not yet created for this platform");
#endif
}

HDTBReturnItem NetworkClient::initiateBlindComms()
{
    if (!statusInfo.connectionSet)
        return HDTBReturnItem(HDTB_RETURN_BAD, "Connection not setup. [setInfo]");

#ifdef _WIN32
    return errorHandler.generateGenericError("Not yet created for this platform");
#else
    return errorHandler.generateGenericError("Not yet created for this platform");
#endif
}

HDTBReturnItem NetworkClient::kill()
{
    if(statusInfo.connectionSet)
        close_current();

    if(statusInfo.comm)
        statusInfo.comm = false;

    if(statusInfo.blindComm)
        statusInfo.blindComm = false;

    statusInfo.connectionSet = false;
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

bool NetworkClient::send_data(std::string data)
{
#ifdef _WIN32
    return false;
#else
    //Send some data
    if( ::send(connectionInfo.sock, data.c_str() , strlen( data.c_str() ) , 0) < 0)
        return false;
    return true;
#endif
}

bool NetworkClient::recieve_data()
{
#ifdef _WIN32
    return false;
#else
    // Retrieve a block of data
    char buffer[connectionInfo.block];
    if( recv(connectionInfo.sock, buffer , sizeof(buffer) , 0) < 0)
        return false;

    // Store data and return
    statusInfo.data_received = buffer;
    return true;
#endif
}

void NetworkClient::close_current()
{
#ifdef _WIN32
#else
    close(connectionInfo.sock);
    statusInfo.connectionSet = false;
#endif
}
}

