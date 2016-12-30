#ifndef MCFPARAMS_H
#define MCFPARAMS_H

#include <MCDataNode.h>
#include <MCRet.h>

class MCFParams: public MCDataNode
{
    public:
        MCFParams();
        virtual ~MCFParams();
        std::string param_name;
        bool is_unvalued = false;
        MCDataNode *ref_line = NULL;
        MCDataNode *ref_vline = NULL;
        MCRet * value;
        MCFParams* GetParam(std::string name);
        MCFParams* PutParam(std::string name,MCDataNode* param,MCDataNode* vparam);
    protected:

    private:
};

#endif // MCFPARAMS_H
