#include "machinesubmoduleremove.h"

// Required
namespace hdtoolbox
{

MachineSubModuleRemove::MachineSubModuleRemove() :
    ModuleBase(HDTB_MACHINE_REMOVE,
               "Machine SubModule - Remove",
               "The sub-module that handles the remove command for"
               "the Machine Module")
{
    commands.insert(
                HDTBMapItem
                ("domain", HDTB_MACHINE_CMD_DOMAIN)
                );

    commands.insert(
                HDTBMapItem
                ("workgroup", HDTB_MACHINE_CMD_WORKGROUP)
                );

    commands.insert(
                HDTBMapItem
                ("account", HDTB_MACHINE_CMD_UNAME)
                );
}

HDTBReturnItem MachineSubModuleRemove::processRequest(std::vector<std::string> args)
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

    case HDTB_MACHINE_CMD_DOMAIN:
        if (args.size() != 3)
        {
            ri.message = "No domain name given";
            return ri;
        }
        else
        {
#ifdef _WIN32
                ri = remDomain(args[2]);
#elif __APPLE__
                ri.message = "Operation not supported on MAC OS";
#else
                ri.message = "Unknown OS, operation not supported";
#endif
        }
        break;

    case HDTB_MACHINE_CMD_WORKGROUP:
            ri = remWorkGroup();
        break;

    case HDTB_MACHINE_CMD_UNAME:
        if (args.size() != 3)
        {
            ri.message = "No account name given";
            return ri;
        }
        else
        {
            ri = remAccount(args[2]);
        }
        break;

    default:
        break;
    }

    return ri;
}

HDTBReturnItem MachineSubModuleRemove::remDomain(std::string domain)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Remove from domain : " << domain << std::endl;

    std::string username, password;

    std::cout << std::endl << "Administrator Username : ";
    std::cin >> username;

    std::cout << std::endl << "Administrator Password : ";
    std::cin >> password;
    std::cout << domain << " " << username << " " << password << std::endl;

    //Set the execution policy
    system("start powershell.exe Set-ExecutionPolicy Bypass \n");

    std::string exec = ("start powershell.exe lib\\machine\\removeDomain.ps1 " + domain + " " + username + " " + password + "\n" );
    system(exec.c_str());
    return ri;
}

HDTBReturnItem MachineSubModuleRemove::remWorkGroup()
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

#ifdef _WIN32
    //Set the execution policy
    system("start powershell.exe Set-ExecutionPolicy Bypass \n");

    std::string exec = ("start powershell.exe lib\\machine\\editWorkgroup.ps1 HDTBGROUP\n" );
    system(exec.c_str());

    ri.retCode = HDTB_RETURN_GOOD;

#else
    ri.message = "Only supported on Windows OS";
#endif
    return ri;
}

HDTBReturnItem MachineSubModuleRemove::remAccount(std::string account)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

 #ifdef _WIN32

    std::cout << std::endl << "Remove account : " << account << std::endl;
    std::string removeUser = "net user " + account + " /del";

    system(removeUser.c_str());

    ri.retCode = HDTB_RETURN_GOOD;

#elif __APPLE__

    //Apple has a weird way of removing users with dscl
    //Avoiding for now

    ri.message = "Not yet created"

#endif
    return ri;

}

}

