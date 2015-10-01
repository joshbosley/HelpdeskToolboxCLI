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

    commands.insert(
                HDTBMapItem
                ("ie", HDTB_MACHINE_CMD_IE)
                );
}

HDTBReturnItem MachineSubModuleEdit::processRequest(std::vector<std::string> args)
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
            if(HDTB_OS == "WIN_OS")
                ri = editDomain(args[2]);
            else if (HDTB_OS == "MAC_OS")
                ri.message = "Operation not supported on MAC OS";
            else
                ri.message = "Unknown OS, operation not supported";
        }
        break;

    case HDTB_MACHINE_CMD_WORKGROUP:
        if (args.size() != 3)
        {
            ri.message = "No workgroup name given";
            return ri;
        }
        else
        {
            ri = editWorkGroup(args[2]);
        }
        break;

    case HDTB_MACHINE_CMD_UAC:
        if (args.size() != 3)
        {
            ri.message = "No state given <on/off>";
            return ri;
        }
        else
        {
            ri = editUAC(args[2]);
        }
        break;

    case HDTB_MACHINE_CMD_CNAME:
        if (args.size() != 3)
        {
            ri.message = "No name given";
            return ri;
        }
        else
        {
            ri = editComputerName(args[2]);
        }
        break;

    case HDTB_MACHINE_CMD_IE:
        if (args.size() != 3)
        {
            ri.message = "No verion given <10/11>";
            return ri;
        }
        else
        {
            ri = editIE(args[2]);
        }
        break;

    default:
        break;
    }

    return ri;
}

HDTBReturnItem MachineSubModuleEdit::editDomain(std::string domain)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
#ifdef _WIN32

    ri.message = "None";

    std::cout << " DOMAIN : " << domain;

    std::string username, password;

    std::cout << std::endl << "Administrator Username : ";
    std::cin >> username;

    std::cout << std::endl << "Administrator Password : ";
    std::cin >> password;
    std::cout << domain << " " << username << " " << password << std::endl;

    //Set the execution policy
    system("start powershell.exe Set-ExecutionPolicy Bypass \n");

    std::string exec = ("start powershell.exe lib\\machine\\editDomain.ps1 " + domain + " " + username + " " + password + "\n" );
    system(exec.c_str());
#else
    ri.message = "Only supported on Windows OS";
#endif
    return ri;
}

HDTBReturnItem MachineSubModuleEdit::editWorkGroup(std::string workgroup)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Change to workgroup : " << workgroup << std::endl;

#ifdef _WIN32
    //Set the execution policy
    system("start powershell.exe Set-ExecutionPolicy Bypass \n");

    std::string exec = ("start powershell.exe lib\\machine\\editWorkgroup.ps1 " + workgroup + "\n" );
    system(exec.c_str());

    ri.retCode = HDTB_RETURN_GOOD;

#else
    ri.message = "Only supported on Windows OS";
#endif
    return ri;
}

HDTBReturnItem MachineSubModuleEdit::editUAC(std::string state)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Change state to : " << state << std::endl;

    ri.message = "Not yet created";
    return ri;

}

HDTBReturnItem MachineSubModuleEdit::editComputerName(std::string name)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

#ifdef _WIN32
    //Set the execution policy
    system("start powershell.exe Set-ExecutionPolicy Bypass \n");

    std::string exec = ("start powershell.exe lib\\machine\\editCname.ps1 " + name + "\n" );
    system(exec.c_str());

    ri.retCode = HDTB_RETURN_GOOD;

#else
    ri.message = "Not yet created for MAC OS";
#endif
    return ri;

}

HDTBReturnItem MachineSubModuleEdit::editIE(std::string version)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

    std::cout << std::endl << "Change version to : " << version << std::endl;

    ri.message = "Not yet created";
    return ri;

}

}

