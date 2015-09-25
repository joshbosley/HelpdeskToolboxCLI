#ifndef HDTB_BOXCORE_H
#define HDTB_BOXCORE_H

#include <stack>
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

namespace hdtoolbox
{

// For returning process information
struct returnItem
{
    returnItem(char code, std::string message)
    {
        this->retCode = code;
        this->message = message;
    }

    char retCode;
    std::string message;
};

// Core operations
class BoxCore
{
public:

    BoxCore();

    void beginHumanInteraction();

private:

    bool session;

    // Handle when/if a module has hijacked user control
    bool moduleHasPrompt;

    // For saving command history
    std::stack< std::vector<std::string> > history;

    // Process input
    struct returnItem processRequest(std::vector<std::string>);

};

}
#endif // HDTB_BOXCORE_H
