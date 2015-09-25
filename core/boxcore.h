#ifndef HDTB_BOXCORE_H
#define HDTB_BOXCORE_H

#include <map>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>
#include <algorithm>

// The modules accessed by user
#include "../modules/modulebox.h"

// The returnable item
#include "../modules/returnitem.h"

// The returnable codes
#include "../modules/returncodes.h"

namespace hdtoolbox
{

// Core operations
class BoxCore
{
public:

    BoxCore();

    void beginHumanInteraction();

private:

    // Our tool box
    moduleBox modBox;

    // For translating arguments to module ids
    std::map<std::string, int> moduleMap;

    // Control the session
    bool session;

    // For saving command history
    std::stack< std::vector<std::string> > history;

    // Process input
    struct returnItem processRequest(std::vector<std::string>);

};

}
#endif // HDTB_BOXCORE_H
