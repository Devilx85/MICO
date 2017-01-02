#ifndef MCFUNC_H
#define MCFUNC_H

#include <string>
#include "IMCFuncLib.h"
#include "MCFTemplate.h"
#include "MCVar.h"
#include "MCRet.h"
#include "MCFParams.h"
#include "MCCodeLine.h"
#include "MCEngine.h"

class MCFunc
{
public:
    MCFunc();
    virtual ~MCFunc();
    std::string name = "";
    std::string description = "";
    int func_type = "FUNC";
    int calc_order = 1;

    MCFTemplate * templ = NULL;
    MCRet* (*func_ref)(MCEngine*,MCCodeLine*, MCVar*, MCVar*, MCFunc*,MCFParams*) = NULL;
protected:

private:
};

#endif // MCFUNC_H
