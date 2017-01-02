#include "MCFTemplate.h"

MCFTemplate::MCFTemplate()
{
    //ctor
}
void MCFTemplate::AddParam(int ptype,std::string pvalue,int pformal,int pclass)
{
    MCDataNode *param = new MCDataNode();
    param->e_type = ptype;
    param->data = pvalue;
    param->ef_type = pformal;
    param->dc_type = pclass;
    if(pformal==_C_T_REQ && ptype==_C_T_COMP)
        req_count++;
    expressions.push_back(param);
}
MCFTemplate::~MCFTemplate()
{
    //dtor
}
