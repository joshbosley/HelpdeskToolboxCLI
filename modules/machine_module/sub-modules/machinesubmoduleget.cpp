#include "machinesubmoduleget.h"

namespace hdtoolbox
{

MachineSubModuleGet::MachineSubModuleGet() :
    ModuleBase(HDTB_MACHINE_GET,
               "Machine SubModule - Get",
               "The sub-module that handles the get command for"
               "the Machine Module")
{
    commands.insert(
                HDTBMapItem
                ("mem", HDTB_MACHINE_CMD_RAM)
                );

    commands.insert(
                HDTBMapItem
                ("hdd", HDTB_MACHINE_CMD_HDD)
                );

    commands.insert(
                HDTBMapItem
                ("cpu", HDTB_MACHINE_CMD_CPU)
                );

    commands.insert(
                HDTBMapItem
                ("os", HDTB_MACHINE_CMD_OS)
                );
}

HDTBReturnItem MachineSubModuleGet::processRequest(std::vector<std::string> args)
{
    history.push(args);

    // Make sure commands are given
    if(args.size() == 1)
    {
        // Call to super class
        displayAvailableCommands();
        return errorHandler.generateGenericError("No command given");
    }

    // Make sure command exists
    if(commands.find(args[1]) == commands.end())
    {
        // Call to super class
        displayAvailableCommands();
        return errorHandler.generateGenericError("Unknown command");
    }

    //Handle command
    switch(commands[args[1]])
    {

    case HDTB_MACHINE_CMD_RAM:
        return getRAM();
        break;

    case HDTB_MACHINE_CMD_HDD:
        return getHDD();
        break;

    case HDTB_MACHINE_CMD_CPU:
        return getCPU();
        break;

    case HDTB_MACHINE_CMD_OS:
        return getOS();
        break;

    default:
        break;
    }

    return errorHandler.generateGenericError("Uncaught return");
}

HDTBReturnItem MachineSubModuleGet::getRAM()
{
#ifdef __APPLE__
        unsigned long long memsize;
        size_t len = sizeof(memsize);
        sysctlbyname("hw.memsize.brand_string", &memsize, &len, NULL, 0);
        std::cout << std::endl << len << " GB" << std::endl;
        return HDTBReturnItem(HDTB_RETURN_GOOD, "");

#elif _WIN32
        std::cout << std::endl << system("wmic memphysical get MaxCapacity")
                  << std::endl;
        return HDTBReturnItem(HDTB_RETURN_GOOD, "");
#else
    return errorHandler.generateGenericError("OS not supported");
#endif
}

HDTBReturnItem MachineSubModuleGet::getHDD()
{
#ifdef __APPLE__
        char *file = (char*)"/";
        struct statvfs buf;
        if (!statvfs(file, &buf))
        {
            unsigned long disk_size, used, free;
            disk_size = buf.f_blocks * buf.f_bsize;
            free = buf.f_bfree * buf.f_bsize;
            used = disk_size - free;
            std::cout << std::endl
                      << "Total Disk Space : " << std::setw(15) << disk_size << std::endl
                      << "Disk Usage :      " << std::setw(15) << used << std::endl
                      << "Free Space :       " << std::setw(15) << free << std::endl;
            return HDTBReturnItem(HDTB_RETURN_GOOD, "");
        }
        else
        {
            return errorHandler.generateGenericError("Could not retrieve your disk information.");
        }
#elif _WIN32
        std::cout << std::endl
                  << system("wmic logicaldisk get Name, FreeSpace, Description")
                  << std::endl;
        return HDTBReturnItem(HDTB_RETURN_GOOD, "");
#else
    return errorHandler.generateGenericError("OS not supported");
#endif
}

HDTBReturnItem MachineSubModuleGet::getCPU()
{
#ifdef __APPLE__
        char buf[100];
        size_t buflen = 100;
        sysctlbyname("machdep.cpu.brand_string", &buf, &buflen, NULL, 0);
        std::cout << std::endl << buf << std::endl;
        return HDTBReturnItem(HDTB_RETURN_GOOD, "");
#elif _WIN32
        std::cout << std::endl << system("wmic cpu get Name") << std::endl;
        return HDTBReturnItem(HDTB_RETURN_GOOD, "");
#else
    return errorHandler.generateGenericError("OS not supported");
#endif
}

HDTBReturnItem MachineSubModuleGet::getOS()
{
#ifdef __APPLE__
        std::cout << std::endl << system("sw_vers") << std::endl;
        return HDTBReturnItem(HDTB_RETURN_GOOD, "");
#elif _WIN32
        std::cout << std::endl << system("wmic os get Caption, Version") << std::endl;
        return HDTBReturnItem(HDTB_RETURN_GOOD, "");
#else
    return errorHandler.generateGenericError("OS not supported");
#endif
}

}
