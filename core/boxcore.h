#ifndef HDTB_BOXCORE_H
#define HDTB_BOXCORE_H

#include <stack>
#include <string>
#include <iostream>

namespace hdtoolbox
{

// For returning process information
struct returnItem
{
    char retCode;
    std::string message;
};

// Command structure
struct command
{
    command(std::string module, std::string input)
    {
        this->module = module;
        this->input = input;
    }

    std::string module;
    std::string input;
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
    std::stack<struct command> history;

    // Process input
    struct returnItem processRequest(struct command);

};

}
#endif // HDTB_BOXCORE_H
