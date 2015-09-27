#ifndef HDTB_RETURNITEM
#define HDTB_RETURNITEM

#include <string>

namespace hdtoolbox
{

// For returning process information
struct returnItem
{
    // Construct!
    returnItem(char code, std::string message)
    {
        this->retCode = code;
        this->message = message;
    }

    // Communicate action (Usage not required)
    char comm;

    // Handling of return (Required)
    char retCode;

    // Message to display from return
    // (Only required when retCode = HDTB_RETURN_BAD)
    std::string message;

    // Overload to set item equal to another
    void operator=(returnItem r)
    {
        this->comm = r.comm;
        this->retCode = r.retCode;
        this->message = r.message;
    }
};

typedef struct returnItem HDTBReturnItem;

}

#endif // HDTB_RETURNITEM

