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
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    history.push(args);

    // Make sure commands are given, and if they are if there are enough
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
                ri = addToDomain(args[2]);
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
            ri = addToWorkGroup(args[2]);
        }
        break;

    case HDTB_MACHINE_CMD_ADMINISTRATOR:
        if (args.size() != 3)
        {
            ri.message = "No admin name given";
            return ri;
        }
        else
        {
            ri = addAnAdministrator(args[2]);
        }
        break;

    default:
        break;
    }

    return ri;

}

/*

                Add the machine to a domain

*/
HDTBReturnItem MachineSubModuleAdd::addToDomain(std::string domain)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    ri.message = "None";

#ifdef _WIN32
    std::cout << " DOMAIN : " << domain;

    ri.message = "Not yet created - script being made by Tyler";
#else
    ri.message = "Only supported on Windows OS";
#endif
    return ri;
}

/*

                Add the machine to a workgroup

*/
HDTBReturnItem MachineSubModuleAdd::addToWorkGroup(std::string group)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);
    ri.message = "None";

#ifdef _WIN32
    std::cout << std::endl << "Add to group : " << group << std::endl;

    ri.message = "Not yet created - script being made by Tyler";
#else
    ri.message = "Only supported on Windows OS";
#endif
    return ri;
}

/*

                Add an administrator

*/
HDTBReturnItem MachineSubModuleAdd::addAnAdministrator(std::string accountName)
{
    HDTBReturnItem ri(HDTB_RETURN_BAD, HDTB_DEFAULT_MESSAGE);

#ifdef _WIN32

    // Come up with a better password, generate something
    std::string createUser = "net user /add " + accountName + " hdtb8675309";
    std::string addUser = "net localgroup administrators " + accountName + " /add";

    system(createUser);
    system(addUser);

#elif __APPLE__

    system( ("dscl . -create /Users/" + accountName).c_str() );
    system( ("dscl . -create /Users/" + accountName + " UserShell /bin/bash").c_str() );
    system( ("dscl . -create /Users/" + accountName + " RealName 'HDTBAdmin'").c_str() );
    system( ("dscl . -create /Users/" + accountName + " UniqueID '1010'").c_str() );
    system( ("dscl . -create /Users/" + accountName + " PrimaryGroupID 80").c_str() );
    system( ("dscl . -create /Users/" + accountName + " NFSHomeDirectory /Users/" + accountName).c_str()  );

#endif

    std::cout << std::endl << "Created admin user : " << accountName << std::endl;
    return ri;
}

}

