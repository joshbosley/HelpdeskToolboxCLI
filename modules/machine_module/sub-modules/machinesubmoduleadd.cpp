#include "machinesubmoduleadd.h"

// Required
namespace hdtoolbox
{

MachineSubModuleAdd::MachineSubModuleAdd() :
    ModuleBase(HDTB_MACHINE_ADD,
               "Machine SubModule - Add",
               "The sub-module that handles the add command for"
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
                ("admin", HDTB_MACHINE_CMD_ADMINISTRATOR)
                );
}

HDTBReturnItem MachineSubModuleAdd::processRequest(std::vector<std::string> args)
{
    history.push(args);

    // Make sure commands are given, and if they are if there are enough
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

#ifdef _WIN32
            ri = addToDomain(args[2]);

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
            return addToWorkGroup(args[2]);
#elif __APPLE__
            return errorHandler.generateGenericError("OS not yet supported");
#else
            return errorHandler.generateGenericError("OS not supported");
#endif

        }
        break;

    case HDTB_MACHINE_CMD_ADMINISTRATOR:
        if (args.size() != 3)
        {
            return errorHandler.generateGenericError("No admin name given");
        }
        else
        {
            return addAnAdministrator(args[2]);
        }
        break;

    default:
        break;
    }

    return errorHandler.generateGenericError("Uncaught return");
}

/*

                Add the machine to a domain

*/
HDTBReturnItem MachineSubModuleAdd::addToDomain(std::string domain)
{
    // Wont reach here if not _WIN32

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

    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

/*

                Add the machine to a workgroup

*/
HDTBReturnItem MachineSubModuleAdd::addToWorkGroup(std::string workgroup)
{
    std::cout << std::endl << "Add to workgroup : " << workgroup << std::endl;

    //Set the execution policy
    system("start powershell.exe Set-ExecutionPolicy Bypass \n");

    std::string exec = ("start powershell.exe lib\\machine\\editWorkgroup.ps1 " + workgroup + "\n" );
    system(exec.c_str());
    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

/*

                Add an administrator

*/
HDTBReturnItem MachineSubModuleAdd::addAnAdministrator(std::string accountName)
{
#ifdef _WIN32

    // Come up with a better password, generate something
    std::string createUser = "net user /add " + accountName + " hdtb8675309";
    std::string addUser = "net localgroup administrators " + accountName + " /add";

    system(createUser.c_str());
    system(addUser.c_str());

    std::cout << "Your password is : " << "hdtb8675309" << std::endl;

#elif __APPLE__

    system( ("dscl . -create /Users/" + accountName).c_str() );
    system( ("dscl . -create /Users/" + accountName + " UserShell /bin/bash").c_str() );
    system( ("dscl . -create /Users/" + accountName + " RealName 'HDTBAdmin'").c_str() );
    system( ("dscl . -create /Users/" + accountName + " UniqueID '1010'").c_str() );
    system( ("dscl . -create /Users/" + accountName + " PrimaryGroupID 80").c_str() );
    system( ("dscl . -create /Users/" + accountName + " NFSHomeDirectory /Users/" + accountName).c_str()  );

#endif

    return HDTBReturnItem(HDTB_RETURN_GOOD, "");
}

}

