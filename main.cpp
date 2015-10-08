/*
    Authors : Lssu Helpdesk Members
              For a full list of authors, see README.md

    Purpose : The goal of the HelpdeskToolboxCLI is to support the common tasks
              commonly associated with the operations of an I.T help desk.

    License : See "LICENSE" file
*/

#include <iostream>
#include "core/boxcore.h"

int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        hdtoolbox::BoxCore HDCore;
        HDCore.beginHumanInteraction();
    }
    else if(argc == 2)
    {
        hdtoolbox::BoxCore HDCore;
        std::cout << "\tStarting Script Mode " << std::endl;
        HDCore.runAsScript(std::string(argv[1]));
    }
    else
    {
        std::cout << " Invalid arguments " << std::endl
                  << argv[0] << " <filename>" << std::endl;
    }
    return 0;
}

