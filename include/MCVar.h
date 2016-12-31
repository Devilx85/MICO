#ifndef MCVAR_H
#define MCVAR_H

#include <MCDataNode.h>
#include <MCCodeLine.h>
#include <vector>

class MCFParams;
class MCCodeLine;

class MCVar : public MCDataNode

{
public:
    MCVar();
    virtual ~MCVar();
    static std::vector<std::string> meta_types;
    static std::string simple_type;
    std::string var_name;
    std::string long_name;
    std::string asoc_index;
    std::string extended_type;
    bool is_arrayitem = false;
    std::string array_type = "VAR";
    int CreateVar(std::string pname,std::string ptype,std::string pvalue, MCVar* type_scope,std::string &error_text,MCVar* &cr_var,bool extends_type = false);
    MCVar* GetVar(std::string pname);
    int CopyType(std::string ptype,MCVar* child, MCVar* type_scope,std::string &error_text);
    MCVar* FindVar(std::string pname,MCVar* pparent,std::string &error_text,int &er_type);
    MCVar* FindSibling(std::string pname,MCVar* pparent);
    MCVar* GetVarIndex(std::string pindex,MCVar* pparent);
    bool AllowName(std::string pname);
    std::string GetKey(std::string pname,std::string &key,std::string &afterkey);
    std::string SetValue(std::string val);
    int CreateArrayItem(std::string pindex,std::string pvalue,MCVar* type_scope,std::string &error_text,MCVar* &cr_var);
    void CopyChildren(MCVar* from,MCVar* to);
    int ar_index = 0;
    bool is_ref = false;
    MCCodeLine *line_ref = NULL;
    std::string ar_pointer = "";
    bool refto = false;
    MCVar* refvar = NULL;
    MCVar* refclass = NULL;

protected:

private:
};

#endif // MCVAR_H
