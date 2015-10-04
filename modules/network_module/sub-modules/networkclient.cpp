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
}

HDTBReturnItem NetworkClient::processRequest(std::vector<std::string> args)
{
    history.push(args);

    // Make sure commands are given
    if(args.size() == 1)
    {
        // Call to super class
        displayAvailableCommands();
        return errorHandler.generateGenericError("No commands given");
    }

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
    switch(commands[args[1]])
    {
    case HDTB_CLIENT_LOAD:
    {
        if (args.size() != 3)
            return HDTBReturnItem(HDTB_RETURN_BAD, "not enough args");

        int c = 0;
        // Make sure port is int
        if( !( c = atoi(args[2].c_str())) )
            return HDTBReturnItem(HDTB_RETURN_BAD, "invalid port");

        return setConnectionInfo(args[2], c);
        break;
    }
    case HDTB_CLIENT_SEND:

        if (args.size() != 2)
            return HDTBReturnItem(HDTB_RETURN_BAD, "not enough args");
        return send(args[2]);

        break;
    case HDTB_CLIENT_COMM:
        return initiateComms();
        break;

    case HDTB_CLIENT_BLIND_COMM:
        return initiateBlindComms();
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

    // Set the connection information
    connectionInfo.port = port;
    connectionInfo.address = address;

    // Indicate what was done
    statusInfo.connectionSet = true;

    std::cout << " SETUP " << std::endl;

    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

HDTBReturnItem NetworkClient::send(std::string message)
{
    if (!statusInfo.connectionSet)
        return HDTBReturnItem(HDTB_RETURN_BAD, "Connection not setup. [setInfo]");

#ifdef _WIN32
    HDTB_UNUSED(message);
    return errorHandler.generateGenericError("Not yet created for this platform");
#else
    HDTB_UNUSED(message);
    return errorHandler.generateGenericError("Not yet created for this platform");
#endif
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

}

