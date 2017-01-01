#include "MCTextLine.h"

MCTextLine::MCTextLine()
{
    //ctor
}

MCTextLine::~MCTextLine()
{
    //dtor
    std::vector<MCDataNode*>::iterator it;
    for ( it = children.begin(); it != children.end(); )
    {
        MCDataNode* comp = *it;
        if(comp!=NULL)
            delete comp;
        it = children.erase(it);
    }
}
