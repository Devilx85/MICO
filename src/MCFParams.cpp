#include "MCFParams.h"

MCFParams::MCFParams()
{
    //ctor
    value = new MCRet();
}
MCFParams* MCFParams::GetParam(std::string name)
{
    for (std::vector<MCDataNode *>::iterator it = children.begin() ; it != children.end(); ++it)
    {
        MCFParams * line=(MCFParams*) *it;
        if(line->param_name==name)
            return line;
    }
    return NULL;
}
MCFParams* MCFParams::PutParam(std::string name,MCDataNode* param,MCDataNode* vparam)
{
    MCFParams * line = new MCFParams();
    line->param_name = name;
    line->ref_line = param;
    line->ref_vline = vparam;
    children.push_back(line);
    return line;
}
MCFParams::~MCFParams()
{
    //dtor
}
