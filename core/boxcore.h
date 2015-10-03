#ifndef HDTB_BOXCORE_H
#define HDTB_BOXCORE_H

#include <map>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <iostream>
#include <algorithm>

// HTDB specific datatypes
#include "datatypes.h"

// The modules accessed by user
#include "modulebox.h"

// Pre-defined os variables
#include "../modules/framework/_os/osinfo.h"

// The returnable item
#include "../modules/framework/_types/returnitem.h"

// The returnable codes
#include "../modules/framework/_types/returncodes.h"

// Error machine
#include "../modules/framework/_errors/errorbase.h"

namespace hdtoolbox
{

// Core operations
class BoxCore
{
public:

    BoxCore();

    void beginHumanInteraction();

private:

    std::string prompt;

    // Our tool box
    moduleBox modBox;

    // For translating arguments to module ids
    HDTBStandardMap moduleMap;

    // Control the session
    bool session;

    // Handle Errors
    ErrorBase errHandler;

    // For saving command history
    HDTBHistory history;

    // Process input
    HDTBReturnItem processRequest(std::vector<std::string>);


};

}
#endif // HDTB_BOXCORE_H
