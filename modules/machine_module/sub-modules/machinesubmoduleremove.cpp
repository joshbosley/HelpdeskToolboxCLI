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

    case HDTB_MACHINE_CMD_DOMAIN:
        if (args.size() != 3)
        {
            return errorHandler.generateGenericError("No domain given");
        }
        else
        {
            return remDomain(args[2]);
        }
        break;

    case HDTB_MACHINE_CMD_WORKGROUP:
#ifdef _WIN32
            return remWorkGroup();
#else
            return errorHandler.generateGenericError("OS not supported");
#endif
        break;

    case HDTB_MACHINE_CMD_UNAME:
        if (args.size() != 3)
        {
            return errorHandler.generateGenericError("No account given");
        }
        else
        {
            return remAccount(args[2]);
        }
        break;

    default:
        break;
    }

    return errorHandler.generateGenericError("Uncaught return");
}

HDTBReturnItem MachineSubModuleRemove::remDomain(std::string domain)
{
    std::cout << std::endl << "Remove from domain : " << domain << std::endl;

#ifdef _WIN32

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
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
#elif __APPLE__

    // Under construction warning flag
    std::string reply;
    std::cout << std::endl
    /*  J  */ << std::endl
    /*  A  */ << "This is under construction. Who knows what will happen. Continue ?  (y/n)"
    /*  B  */ << std::endl
    /*  :) */ << std::endl;
    std::cin >> reply;
    if(reply != "y")
        return errorHandler.generateGenericError("Canceled add domain");

    system("sudo dsconfigad -leave");

    std::cout << "Command executed" << std::endl;
    return errorHandler.generateGenericError("[UNDER CONSTRUCTION] - add domain command executed.");
#endif
}

HDTBReturnItem MachineSubModuleRemove::remWorkGroup()
{
#ifdef _WIN32
    //Set the execution policy
    system("start powershell.exe Set-ExecutionPolicy Bypass \n");

    std::string exec = ("start powershell.exe lib\\machine\\editWorkgroup.ps1 HDTBGROUP\n" );
    system(exec.c_str());

    return HDTBReturnItem(HDTB_RETURN_GOOD, "");

#else
    return errorHandler.generateGenericError("OS not supported");
#endif
}

HDTBReturnItem MachineSubModuleRemove::remAccount(std::string account)
{
 #ifdef _WIN32

    std::cout << std::endl << "Remove account : " << account << std::endl;
    std::string removeUser = "net user " + account + " /del";

    system(removeUser.c_str());

#elif __APPLE__

     //Warning Flag
    std::string reply;
    std::cout << std::endl
    /*  J  */ << std::endl
    /*  A  */ << "Are you in single-user mode? [Hold Command-s at startup]  (y/n)"
    /*  B  */ << std::endl
    /*  :) */ << std::endl;
    std::cin >> reply;
    if(reply != "y")
        return errorHandler.generateGenericError("Must be in single-user mode.");

    // Initiate removal of user
    std::string command  = ("sudo dscl . delete /users/" + account);
    std::string command2 = ("rm -r /users/" + account);
    system(command.c_str());
    system(command2.c_str());
#endif
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

}

