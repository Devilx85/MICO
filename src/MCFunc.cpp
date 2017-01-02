#include "MCFunc.h"

MCFunc::MCFunc()
{
    //ctor
    templ = new MCFTemplate();
}

MCFunc::~MCFunc()
{
    //dtor
    templ->Free();
}
