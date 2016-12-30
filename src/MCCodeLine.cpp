#include "MCCodeLine.h"
#include <vector>

MCCodeLine::MCCodeLine()
{
    //ctor

}

MCCodeLine::~MCCodeLine()
{
    //dtor
    if(cached_data_params!=NULL)
        delete cached_data_params;
}
