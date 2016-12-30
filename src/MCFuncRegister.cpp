#include "MCFuncRegister.h"
#include "MCFunc.h"

MCFuncRegister::MCFuncRegister()
{
    //ctor
}
int MCFuncRegister::AddFunc(MCFunc* f)
{
    if(f->func_ref==NULL)
        return -1;
    bool hasreq = false;
    int in = 0;
    for (std::vector<MCDataNode*>::iterator it = f->templ->expressions.begin() ; it != f->templ->expressions.end(); ++it)
    {
        MCDataNode * f_param = *it;
        if(in==0)
        {
            if(f_param->formal_type=="SEQ")
                return -3;
        }

        if(f_param->formal_type=="REQ")
            hasreq = true;
        in++;
    }
    if(hasreq == false)
        return -2;


    reg_funcs.push_back(f);
}
MCFuncRegister::~MCFuncRegister()
{
    //dtor
    for (std::vector<MCFunc*>::iterator it = reg_funcs.begin() ; it != reg_funcs.end(); ++it)
    {
        MCFunc* comp = *it;
        delete comp;
    }
    reg_funcs.clear();
}
