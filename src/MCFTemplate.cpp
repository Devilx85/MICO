#include "MCFTemplate.h"

MCFTemplate::MCFTemplate()
{
    //ctor
}
void MCFTemplate::AddParam(std::string ptype,std::string pvalue,std::string pformal,std::string pclass)
{
    MCDataNode *param = new MCDataNode();
    param->data_type = ptype;
    param->data = pvalue;
    param->formal_type = pformal;
    param->data_class = pclass;
    if(pformal=="REQ" && ptype=="COMP")
        req_count++;
    expressions.push_back(param);
}
MCFTemplate::~MCFTemplate()
{
    //dtor
}
