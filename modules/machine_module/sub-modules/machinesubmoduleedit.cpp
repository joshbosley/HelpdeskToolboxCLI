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
#ifdef _WIN32
            return editDomain(args[2]);
#elif __APPLE__
            return errorHandler.generateGenericError("OS not yet supported");
#else
            return errorHandler.generateGenericError("OS not supported");
#endif
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

    case HDTB_MACHINE_CMD_IE:
#ifdef _WIN32
        if (args.size() != 3)
        {
            return errorHandler.generateGenericError("No version given <10/11>");
        }
        else
        {
            return editIE(args[2]);
        }
#else
        return errorHandler.generateGenericError("OS not supported");
#endif
        break;

    default:
        break;
    }

    return errorHandler.generateGenericError("Uncaught return");
}

HDTBReturnItem MachineSubModuleEdit::editDomain(std::string domain)
{
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
    HDTB_UNUSED(domain);
    return errorHandler.generateGenericError("OS not supported");
#endif
}

HDTBReturnItem MachineSubModuleEdit::editWorkGroup(std::string workgroup)
{
    std::cout << std::endl << "Change to workgroup : " << workgroup << std::endl;

    //Set the execution policy
    system("start powershell.exe Set-ExecutionPolicy Bypass \n");

    std::string exec = ("start powershell.exe lib\\machine\\editWorkgroup.ps1 " + workgroup + "\n" );
    system(exec.c_str());

    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

HDTBReturnItem MachineSubModuleEdit::editUAC(std::string state)
{
    std::cout << std::endl << "Change state to : " << state << std::endl;
    return errorHandler.generateGenericError("Not yet created");
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

#elif __APPLE__
    HDTB_UNUSED(name);
    return errorHandler.generateGenericError("OS not yet supported ");
#endif
    return ri;

}

HDTBReturnItem MachineSubModuleEdit::editIE(std::string version)
{
    std::cout << std::endl << "Change version to : " << version << std::endl;
    return errorHandler.generateGenericError("Not yet created");
}

}

