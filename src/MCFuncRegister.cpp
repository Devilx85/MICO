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
            if(f_param->f_type==_C_T_SEQ)
                return -3;
        }

        if(f_param->f_type==_C_T_REQ)
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

    std::vector<MCFunc*>::iterator it;

    for ( it = reg_funcs.begin(); it != reg_funcs.end(); )
    {
        MCFunc* comp = *it;
        if(comp!=NULL)
            delete comp;
        it = reg_funcs.erase(it);
    }



}
