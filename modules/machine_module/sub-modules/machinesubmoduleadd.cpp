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
            return addToDomain(args[2]);

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
    std::cout << std::endl << " DOMAIN : " << domain << std::endl;

    // Get admin username and password
    std::string username, password;

    std::cout << std::endl << "Network Administrator Username : ";
    std::cin >> username;

    std::cout << std::endl << "Network Administrator Password : ";
    std::cin >> password;

#ifdef _WIN32
    //Set the execution policy
    system("start powershell.exe Set-ExecutionPolicy Bypass \n");

    std::string exec = ("start powershell.exe lib\\machine\\editDomain.ps1 " + domain + " " + username + " " + password + "\n" );
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

    // Get hostname
    char hn[150];
    std::memset(hn, 0, 150);
    gethostname(hn, 150);
    std::string hostName = hn;

    // Create command
    std::string exec = ("sudo dsconfigad -add " + domain   +
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

