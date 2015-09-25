#include "modulebase.h"


namespace hdtoolbox
{

ModuleBase::ModuleBase(unsigned int id, std::string name, std::string description)
{
    this->moduleId = id;
    this->moduleName = name;
    this->moduleDesc = description;
}

}
