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
MCFParams* MCFParams::PutParam(std::string name,MCDataNode* param,MCDataNode* vparam,bool indep)
{
    MCFParams * line = new MCFParams();
    line->param_name = name;
    line->ref_line = param;
    line->ref_vline = vparam;
    line->is_independent = indep;
    children.push_back(line);
    return line;
}
void MCFParams::ClearIndependents()
{
    for (std::vector<MCDataNode *>::iterator it = children.begin() ; it != children.end(); ++it)
    {
        MCFParams * line=(MCFParams*) *it;
        if(line->is_independent)
            {
                delete line->ref_line;
                delete line->ref_vline;

            }
    }

}
MCFParams::~MCFParams()
{
    //dtor
    ClearIndependents();
    if(value!=NULL)
        delete value;
}
