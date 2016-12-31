#include "MCDataNode.h"

MCDataNode::MCDataNode()
{
    //ctor
}
void MCDataNode::AddChild(MCDataNode *child)
{
    child->parent = this;
    child->data_namespace = data_namespace;
    children.push_back(child);
}
void MCDataNode::AddAutoExpression()
{

}
void MCDataNode::Free()
{

    std::vector<MCDataNode*>::iterator it;
    for ( it = children.begin(); it != children.end(); )
    {
        MCDataNode* comp = *it;
        if(comp!=NULL)
            delete comp;
        it = children.erase(it);
    }
 //   children.clear();


    for ( it = expressions.begin(); it != expressions.end(); )
    {
        MCDataNode* comp = *it;
        if(comp!=NULL)
            delete comp;
       it = expressions.erase(it);
    }
 //   expressions.clear();



}
MCDataNode::~MCDataNode()
{
    //dtor
    Free();
}
