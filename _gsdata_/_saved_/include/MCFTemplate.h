#ifndef MCFTEMPLATE_H
#define MCFTEMPLATE_H

#include <MCDataNode.h>


class MCFTemplate : public MCDataNode
{
    public:
        MCFTemplate();
        virtual ~MCFTemplate();
        int req_count = 0;
        void AddParam(std::string ptype,std::string pvalue,std::string pformal,std::string pclass = "ANY");
    protected:

    private:
};

#endif // MCFTEMPLATE_H
