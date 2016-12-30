#ifndef MCRET_H
#define MCRET_H
#include <string>
#include "MCVar.h"

class MCRet
{
    public:
        MCRet();
        virtual ~MCRet();
        int code=0;
        int stop_code = 0;
        std::string bufout = "";
        std::string ret_type = "";
        std::string ret_data = "";
        MCVar* ref_var = NULL;
        double ret_nr = 0;
    protected:

    private:
};

#endif // MCRET_H
