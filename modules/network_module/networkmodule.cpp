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
                ("blast", HDTB_NETOWRK_CMD_BLAST)
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

    case HDTB_NETOWRK_CMD_BLAST:
        return blast();
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

HDTBReturnItem NetworkModule::setupConnection()
{
    // Make sure somethinf isn't already going on.
    // Get address, and port from user
    std::string addr, port;
    std::cout << "Address: ";
    std::cin >> addr;

    std::cout << "Port: ";
    std::cin >> port;

    std::vector<std::string> request;
    request.push_back("setInfo");
    request.push_back(addr);
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

HDTBReturnItem NetworkModule::blast()
{
    // Handle setting up the connection
    HDTBReturnItem ri =  setupConnection();

    switch(ri.retCode)
    {
    case HDTB_RETURN_GOOD:
    {
        // If connection setup goes well, start blast.
        #ifdef __APPLE__
            return errorHandler.generateGenericError("Blast is Under Construction");
        #elif _WIN32
            return errorHandler.generateGenericError("Blast is Under Construction");
        #endif
    }
        break;

    case HDTB_RETURN_BAD:
        return HDTBReturnItem(HDTB_RETURN_BAD, ri.message);
        break;

    case HDTB_RETURN_EXIT:
        return HDTBReturnItem(HDTB_RETURN_EXIT, "");
        break;

    default:
        return errorHandler.generateGenericError("Default reached in human interaction");
        break;
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
