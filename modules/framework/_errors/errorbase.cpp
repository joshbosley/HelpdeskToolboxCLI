#include "errorbase.h"

namespace hdtoolbox
{

ErrorBase::ErrorBase()
{

}

void ErrorBase::displayError(std::string message)
{
    std::cout << std::endl << std::endl
              << message
              << std::endl << std::endl;
}

HDTBReturnItem ErrorBase::generateGenericError(std::string message)
{
    return HDTBReturnItem(HDTB_RETURN_BAD, message);
}

}

