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
        break;

    case HDTB_NETWORK_CMD_KNOCK_SEQUENCE:
        break;

    case HDTB_NETWORK_CMD_COMMLINK:
        break;

    default:
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
#ifdef __APPLE__
    return errorHandler.generateGenericError("Under Construction");
#elif _WIN32
    return errorHandler.generateGenericError("Under Construction");
#endif
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
