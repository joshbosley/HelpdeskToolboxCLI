#ifndef HDTB_RETURNITEM
#define HDTB_RETURNITEM

#include <string>

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

    void operator=(returnItem r)
    {
        this->retCode = r.retCode;
        this->message = r.message;
    }
};

}

#endif // HDTB_RETURNITEM

