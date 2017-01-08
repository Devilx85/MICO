#ifndef MCFUNCREGISTER_H
#define MCFUNCREGISTER_H



#include <vector>
#include <string>

class MCFunc;

class MCFuncRegister
{
public:
    MCFuncRegister();
    virtual ~MCFuncRegister();
    std::vector<MCFunc*> reg_funcs;
    MCFunc* call_func = NULL;
    MCFunc* neg_func = NULL;
    MCFunc* pos_func = NULL;
    int AddFunc(MCFunc* f);
protected:

private:
};

#endif // MCFUNCREGISTER_H
