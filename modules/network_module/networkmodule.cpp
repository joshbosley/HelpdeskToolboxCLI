#include "networkmodule.h"

namespace hdtoolbox
{

NetworkModule::NetworkModule() :
    ModuleBase(HDTB_CODE_NETWORK,
               "Netowrk Module",
               "A network interface module.")
{

    commands.insert(
                HDTBMapItem
                ("ping", HDTB_NETWORK_CMD_PING)
                );

    commands.insert(
                HDTBMapItem
                ("reset", HDTB_NETWORK_CMD_RESET)
                );

    commands.insert(
                HDTBMapItem
                ("send", HDTB_NETOWRK_CMD_REACH)
                );

    commands.insert(
                HDTBMapItem
                ("knock", HDTB_NETWORK_CMD_KNOCK_SEQUENCE)
                );

    commands.insert(
                HDTBMapItem
                ("comm", HDTB_NETWORK_CMD_COMMLINK)
                );

}

HDTBReturnItem NetworkModule::processRequest(std::vector<std::string> args)
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
    if(commands.find(args[1]) == commands.end())
    {
        // Call to super class
        displayAvailableCommands();
        return errorHandler.generateGenericError("Command not found");
    }

    //Handle command
    switch(commands[args[1]])
    {
    case HDTB_NETWORK_CMD_PING:
        if (args.size() != 4)
            return errorHandler.generateGenericError("Usage : ping <address> <count>");

        // Make sure count is int
        if( !(atoi(args[3].c_str())) )
            return errorHandler.generateGenericError("Usage : ping <address> <count> [Count must be an int]");

        // Send data to ping
        return ping(args[2], args[3]);
        break;

    case HDTB_NETWORK_CMD_RESET:
        return reset();
        break;

    case HDTB_NETOWRK_CMD_REACH:
        if (args.size() != 5)
            return errorHandler.generateGenericError("send <destination> <port> <message>");

        if( !(atoi(args[3].c_str())) )
            return  errorHandler.generateGenericError("Invalid port, must be an integer");

        return reach(args[2], args[3], args[4]);
        break;

    case HDTB_NETWORK_CMD_KNOCK_SEQUENCE:
        return knock();
        break;

    case HDTB_NETWORK_CMD_COMMLINK:
        return comm();
        break;

    default:
        break;
    }

    return errorHandler.generateGenericError("Uncaught return");
}

HDTBReturnItem NetworkModule::setupConnection(std::string address, std::string port)
{
    std::vector<std::string> request;
    request.push_back("setInfo");
    request.push_back(address);
    request.push_back(port);

    // Process command
    HDTBReturnItem ri =  netClient.processRequest(request);

    switch(ri.retCode)
    {
    case HDTB_RETURN_GOOD:
        // Double check to make sure connection was set
        if(!netClient.getConnectionSetState())
            return HDTBReturnItem(HDTB_RETURN_BAD,
                                  "Good report, but connection not set");
        // Return good
        return HDTBReturnItem(HDTB_RETURN_GOOD, "");
        break;

    case HDTB_RETURN_BAD:
    {
        // Relay error
        return HDTBReturnItem(HDTB_RETURN_BAD, ri.message);
    }
        break;

    case HDTB_RETURN_EXIT:
        return HDTBReturnItem(HDTB_RETURN_EXIT, "");
        break;

    default:
        errorHandler.generateGenericError("Default reached in human interaction");
        break;
    }
    return errorHandler.generateGenericError("Uncaught return");
}

HDTBReturnItem NetworkModule::ping(std::string ip, std::string count)
{
    std::cout << "Ping : " << ip << " " << count << " time(s)" << std::endl;

#ifdef __APPLE__
    system(("ping -c " + count + " " + ip).c_str());

#elif _WIN32
    system(("ping -n " + count + " " + ip).c_str());
#endif
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

HDTBReturnItem NetworkModule::reset()
{
#ifdef __APPLE__
    system("sudo ifconfig en0 down");
    system("sudo ifconfig en0 up");

#elif _WIN32
    system("ipconfig /release");
    system("ipconfig /renew");
#endif
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

HDTBReturnItem NetworkModule::reach(std::string address, std::string port, std::string message)
{
    std::vector<std::string> req;
    HDTBReturnItem res(HDTB_RETURN_BAD, "");

    // Handle setting up the connection
    HDTBReturnItem ri =  setupConnection(address, port);

    if(ri.retCode == HDTB_RETURN_GOOD)
    {
        req.push_back("send");
        req.push_back(message);
        res = netClient.processRequest(req);

        // Kill the current connection when complete
        req.clear();
        req.push_back("kill");
        netClient.processRequest(req);
        return res;
    }
    else
    {
        return errorHandler.generateGenericError("Could not set up connection - [send]");
    }
    return errorHandler.generateGenericError("Uncaught return");
}

HDTBReturnItem NetworkModule::knock()
{
#ifdef __APPLE__
    return errorHandler.generateGenericError("Under Construction");
#elif _WIN32
    return errorHandler.generateGenericError("Under Construction");
#endif
}

HDTBReturnItem NetworkModule::comm()
{
#ifdef __APPLE__
    return errorHandler.generateGenericError("Under Construction");
#elif _WIN32
    return errorHandler.generateGenericError("Under Construction");
#endif
}

}
