#ifndef MCFTEMPLATE_H
#define MCFTEMPLATE_H

#include <MCDataNode.h>



class MCFTemplate : public MCDataNode
{
public:
    MCFTemplate();
    virtual ~MCFTemplate();
    int req_count = 0;


    void AddParam(int ptype,std::string pvalue,int pformal,int pclass = _C_CF_ANY);
protected:

private:
};

#endif // MCFTEMPLATE_H
