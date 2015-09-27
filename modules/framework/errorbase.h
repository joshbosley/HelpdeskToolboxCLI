#ifndef HDTB_ERRORBASE_H
#define HDTB_ERRORBASE_H

#include <map>
#include <stack>
#include <vector>
#include <string>
#include <iomanip>
#include <iostream>

/*

    A simple error reporting class that can be used as-is, or can be
    built on to create custom error handling for your module

*/

namespace hdtoolbox
{

// Structure to handle all of an error's data
struct errorInfo
{
    // Required information
    std::string moduleName;
    int moduleDirectoryCode;

    // Not required, populate to display
    std::stack< std::vector<std::string> > moduleHistory;
    std::vector<std::string> outputMessages;
};

typedef struct errorInfo errInf;

class ErrorBase
{
public:
    ErrorBase();

    void generateOperableError();
    void generateExitError();

};

}

#endif // HDTB_ERRORBASE_H
