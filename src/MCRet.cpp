#include "MCRet.h"

MCRet::MCRet()
{
   code=0;
   stop_code = 0;
   bufout = "";
   ret_type = "";
   ret_data = "";
   ref_var = NULL;
}

MCRet::~MCRet()
{
    //dtor
}
