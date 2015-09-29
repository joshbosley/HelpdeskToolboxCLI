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
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    history.push(args);

    // Make sure commands are given
    if(args.size() == 1)
    {
        // Call to super class
        displayAvailableCommands();

        ri.message = "No commands given";
        return ri;
    }

    // Make sure command exists
    if(commands.find(args[1]) == commands.end())
    {
        // Call to super class
        displayAvailableCommands();

        ri.retCode = HDTB_RETURN_BAD;
        ri.message = "Command not found";
        return ri;
    }

    //Handle command
    switch(commands[args[1]])
    {

    case HDTB_MACHINE_CMD_RAM:
        ri = getRAM();
        break;

    case HDTB_MACHINE_CMD_HDD:
        ri = getHDD();
        break;

    case HDTB_MACHINE_CMD_CPU:
        ri = getCPU();
        break;

    case HDTB_MACHINE_CMD_OS:
        ri = getOS();
        break;

    default:
        break;
    }

    return ri;
}

HDTBReturnItem MachineSubModuleGet::getRAM()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    if(HDTB_OS == "MAC_OS")
    {
        unsigned long long memsize;
        size_t len = sizeof(memsize);
        sysctlbyname("hw.memsize.brand_string", &memsize, &len, NULL, 0);
        std::cout << std::endl << len << " GB" << std::endl;
        ri.retCode = HDTB_RETURN_GOOD;
    }
    else if (HDTB_OS == "WIN_OS")
    {
        std::cout << std::endl << system("wmic memphysical get MaxCapacity")
                  << std::endl;
        ri.retCode = HDTB_RETURN_GOOD;
    }
    else
    {
        ri.message = "OS not supported.";
    }
    return ri;
}

HDTBReturnItem MachineSubModuleGet::getHDD()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    if(HDTB_OS == "MAC_OS")
    {
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
            ri.retCode = HDTB_RETURN_GOOD;
        }
        else
        {
            ri.message = "Could not retrieve disk information on your MAC OS";
        }
    }
    else if (HDTB_OS == "WIN_OS")
    {
        std::cout << std::endl
                  << system("wmic logicaldisk get Name, FreeSpace, Description")
                  << std::endl;
        ri.retCode = HDTB_RETURN_GOOD;
    }
    else
    {
        ri.message = "OS not supported.";
    }
    return ri;
}

HDTBReturnItem MachineSubModuleGet::getCPU()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    if(HDTB_OS == "MAC_OS")
    {
        char buf[100];
        size_t buflen = 100;
        sysctlbyname("machdep.cpu.brand_string", &buf, &buflen, NULL, 0);
        std::cout << std::endl << buf << std::endl;
        ri.retCode = HDTB_RETURN_GOOD;
    }
    else if (HDTB_OS == "WIN_OS")
    {
        std::cout << std::endl << system("wmic cpu get Name") << std::endl;
        ri.retCode = HDTB_RETURN_GOOD;
    }
    else
    {
        ri.message = "OS not supported.";
    }
    return ri;
}

HDTBReturnItem MachineSubModuleGet::getOS()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    if(HDTB_OS == "MAC_OS")
    {
        std::cout << std::endl << system("sw_vers") << std::endl;
        ri.retCode = HDTB_RETURN_GOOD;
    }
    else if (HDTB_OS == "WIN_OS")
    {
        std::cout << std::endl << system("wmic os get Caption, Version") << std::endl;
        ri.retCode = HDTB_RETURN_GOOD;
    }
    else
    {
        ri.message = "OS not supported.";
    }
    return ri;
}

}
