#ifndef HDTB_NETWORKMODULE_H
#define HDTB_NETWORKMODULE_H


// Required
#include "../../core/datatypes.h"
#include "../framework/_modules/modulebase.h"
namespace hdtoolbox
{

class NetworkModule : public ModuleBase
{
public:
    NetworkModule();

    HDTBReturnItem processRequest(std::vector<std::string>);

private:

    HDTBReturnItem displayIP();

};

}
#endif // HDTB_NETWORKMODULE_H
