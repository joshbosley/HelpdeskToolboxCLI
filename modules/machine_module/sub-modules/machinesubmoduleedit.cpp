#include "machinesubmoduleedit.h"

// Required
namespace hdtoolbox
{

MachineSubModuleEdit::MachineSubModuleEdit() :
    ModuleBase(HDTB_MACHINE_EDIT,
               "Machine SubModule - Edit",
               "The sub-module that handles the edit command for"
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
                ("uac", HDTB_MACHINE_CMD_UAC)
                );

    commands.insert(
                HDTBMapItem
                ("cname", HDTB_MACHINE_CMD_CNAME)
                );
}

HDTBReturnItem MachineSubModuleEdit::processRequest(std::vector<std::string> args)
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
        return errorHandler.generateGenericError("Unknown command");
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
            return editDomain(args[2]);
        }
        break;

    case HDTB_MACHINE_CMD_WORKGROUP:
        if (args.size() != 3)
        {
            return errorHandler.generateGenericError("No workgroup given");
        }
        else
        {
#ifdef _WIN32
            return editWorkGroup(args[2]);
#else
            return errorHandler.generateGenericError("OS not supported");
#endif
        }
        break;

    case HDTB_MACHINE_CMD_UAC:
#ifdef _WIN32
        if (args.size() != 3)
        {
            return errorHandler.generateGenericError("No state given <on/off>");
        }
        else
        {
            return editUAC(args[2]);
        }
#else
            return errorHandler.generateGenericError("OS not supported");
#endif
        break;

    case HDTB_MACHINE_CMD_CNAME:
        if (args.size() != 3)
        {
            return errorHandler.generateGenericError("No name given");
        }
        else
        {
            return editComputerName(args[2]);
        }
        break;
    default:
        break;
    }

    return errorHandler.generateGenericError("Uncaught return");
}

HDTBReturnItem MachineSubModuleEdit::editDomain(std::string domain)
{
    std::cout << " DOMAIN : " << domain;

    std::string username, password;
    std::cout << std::endl << "Administrator Username : ";
    std::cin >> username;

    std::cout << std::endl << "Administrator Password : ";
    std::cin >> password;

#ifdef _WIN32

    std::string exec = ("start powershell.exe -ExecutionPolicy Bypass -File lib\\machine\\editDomain.ps1 " + domain + " " + username + " " + password + "\n" );
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

    // Make sure to leave current domain
    system("sudo dsconfigad -leave");

    // Get hostname
    char hn[150];
    std::memset(hn, 0, 150);
    gethostname(hn, 150);
    std::string hostName = hn;

    // Create command
    std::string exec = ("dsconfigad -add "      + domain   +
                           " -username "        + username +
                           " -password "        + password +
                           " -computer "        + hostName +
                           " -localhome enable -useuncpath enable -groups Domain Admins, Domain Users, -alladmins enable");
    // Execute command
    system(exec.c_str());

    // Exit
    std::cout << "Command executed" << std::endl;
    return errorHandler.generateGenericError("[UNDER CONSTRUCTION] - add domain command executed.");
#endif
}

HDTBReturnItem MachineSubModuleEdit::editWorkGroup(std::string workgroup)
{
    std::cout << std::endl << "Change to workgroup : " << workgroup << std::endl;

    std::string exec = ("start powershell.exe -ExecutionPolicy Bypass -File lib\\machine\\editWorkgroup.ps1 " + workgroup + "\n" );
    system(exec.c_str());
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

HDTBReturnItem MachineSubModuleEdit::editUAC(std::string state)
{
    std::cout << std::endl << "Change state to : " << state << std::endl;

    std::string exec = ("start lib\\machine\\editUAC.bat " + state + "\n");
    system(exec.c_str());

    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

HDTBReturnItem MachineSubModuleEdit::editComputerName(std::string name)
{
#ifdef _WIN32

    std::string exec = ("start powershell.exe -ExecutionPolicy Bypass -File lib\\machine\\editCname.ps1 " + name + "\n" );
    system(exec.c_str());

    return HDTBReturnItem(HDTB_RETURN_GOOD, "");

#elif __APPLE__
    sethostname(name.c_str(), name.length());
    return errorHandler.generateGenericError("Not yet fully tested");
#endif
}

}

