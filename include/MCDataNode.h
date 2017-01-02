#ifndef MCDATANODE_H
#define MCDATANODE_H
#include <vector>
#include <string>

class MCDataNode
{
public:
    MCDataNode();
    virtual ~MCDataNode();
    std::vector<MCDataNode*> children;
    std::vector<MCDataNode*> expressions;

    MCDataNode *parent = NULL;

    std::string data_namespace = "UNKNOWN";
    std::string data = "UNKNOWN";
    std::string data_type = "UNKNOWN";
    std::string formal_type = "UNKNOWN";
    std::string data_class = "UNKNOWN";

    int line_id = 0;

    int e_type = 0;
    int f_type = 0;
    int dc_type = 0;

    double num_value = 0;

    void AddChild(MCDataNode *child);
    void AddAutoExpression();
    void Free();
protected:

private:
};

#endif // MCDATANODE_H
