#ifndef IMCFUNCLIB_H
#define IMCFUNCLIB_H
#include <string>
#include "MCFuncRegister.h"

class IMCFuncLib
{
public:
    std::string name;
    std::string description;
    std::string version;
    virtual void RegFunc(MCFuncRegister * reg) = 0;

protected:

private:
};

#endif // IMCFUNCLIB_H
