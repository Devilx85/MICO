#ifndef MCVAR_H
#define MCVAR_H

#include <MCDataNode.h>
#include <MCCodeLine.h>
#include <vector>
#include <map>

class MCFParams;
class MCCodeLine;

class MCVar : public MCDataNode

{
public:
    MCVar();
    virtual ~MCVar();
    static std::vector<std::string> meta_types;
    static std::vector<std::string> dyn_types;
    static std::string simple_type;
    std::string var_name;
    std::string long_name;
    std::string asoc_index;
    int num_index;

    bool is_system = false;
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
    MCVar* GetVarIndexInt(int pindex,MCVar* pparent);
    int CreateArrayItem(std::string pindex,std::string pvalue,MCVar* type_scope,std::string &error_text,MCVar* &cr_var);
    MCVar* GetVarIndexMove(std::string pindex,MCVar* pparent,int moveIdx);
    void CopyChildren(MCVar* from,MCVar* to);
    bool DeleteChildIndex(int pindex);
    bool DeleteChildPIndex(std::string pindex);
    void SetAsocVar(std::string pinex,MCVar* var);
    void ReindexChildren();
    bool IsDynamic();
    bool MoveNext();
    bool MovePrev();
    bool SetIndex(int i);
    bool SetFirst();
    bool SetLast();
    bool IsLast();
    bool IsFirst();
    //std::map<std::string,MCVar*> ch_asoc_array;
    std::vector<std::pair<std::string,MCVar*>> ch_asoc_array;
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
