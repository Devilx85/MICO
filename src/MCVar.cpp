#include "MCVar.h"
#include <boost/algorithm/string.hpp>
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <algorithm>
#include <map>

using namespace std::placeholders;


std::vector<std::string> MCVar::meta_types = boost::assign::list_of("VAR")("TYPE")("REF")("ARRAY")("FUNC")("OBJECT")("TREE");
std::string MCVar::simple_type = "VAR";


MCVar::MCVar()
{
    //ctor
    data_type = simple_type;
    data = "";

}
void MCVar::ReindexChildren()
{

    std::map<std::string,int>  child_idx;
    for (std::vector<MCDataNode *>::iterator it = children.begin() ; it != children.end(); ++it)
    {
        MCVar* var =(MCVar*) *it;
        if ( child_idx.find(var->var_name) == child_idx.end() )
        {
            // not found
            child_idx[var->var_name] = 0;
        }
        else
            child_idx[var->var_name]++;
        var->num_index = child_idx[var->var_name];
    }


}

std::string MCVar::SetValue(std::string val)
{
    if(data_type != MCVar::simple_type && data_type != "TREE")
    {
        return "Can not assign value for type "  + data_type;
    }
    data = val;
    return "";
}

MCVar* MCVar::FindSibling(std::string pname,MCVar* pparent)
{
    auto it = std::find_if(std::begin(pparent->children), std::end(pparent->children),
                           [&pname](const MCDataNode* attr) -> bool
    { return ((MCVar*)attr)->var_name == pname; });

    if (it != pparent->children.end())
    {
        return (MCVar*)*it;
    }
    return NULL;
}

bool MCVar::AllowName(std::string pname)
{
    if(pname.length()==0)
    {
        return false;
    }

    if(!std::isalpha(pname[0]))
    {
        return false;
    }



    return true;

}
std::string MCVar::GetKey(std::string pname,std::string &key,std::string &afterkey)
{
    bool keybeg = false;
    bool aftkey = false;
    key = "";
    std::string name = "";
    afterkey = "";
    for(int ci=0; ci<pname.length(); ci++)
    {
        if(aftkey==true)
        {
            afterkey = afterkey + pname[ci];
            continue;
        }
        if(pname[ci]=='[')
        {
            keybeg = true;
            continue;
        }
        else if(pname[ci]==']')
        {
            keybeg = false;
            aftkey = true;
            continue;
        }
        if(!keybeg)
        {
            name = name + pname[ci];
        }
        else
            key = key + pname[ci];
    }
    return name;
}
MCVar* MCVar::FindVar(std::string pname,MCVar* pparent,std::string &error_text,int &er_type)
{
    MCVar* cur_parent = pparent;
    std::vector<std::string> strs;
    boost::split(strs,pname,boost::is_any_of("."));
    er_type = 0;
    int cyc = 0;
    for (std::vector<std::string>::iterator it = strs.begin() ; it != strs.end(); ++it)
    {
        std::string comp =*it;
        std::string vname = "";
        std::string vkey = "";
        std::string afterkey = "";
        vname = GetKey(comp,vkey,afterkey);
        MCVar* var_f = FindSibling(vname,pparent);
        if(var_f==NULL)
        {
            if(cyc==0)
            {
                error_text = " object not found " + comp;
                er_type = -1;
                return NULL;
            }else
            {
                error_text = " component not found " + comp + " of " + pname;
                er_type = -4;
                return NULL;
            }
        }
        cyc++;
        if(var_f->data_type == "REF")
            {
                if(var_f->refvar==NULL)
                {
                    error_text = "can not use NULL pointer reference "  + pname;
                    er_type = -5;
                    return NULL;
                }
                var_f = var_f->refvar;
            }
        if(vkey!="")
        {
            if(var_f->data_type != "ARRAY" && var_f->data_type != "TREE")
            {
                error_text = "can not use key for non-array object "  + pname;
                er_type = -2;
                return NULL;
            }

            if(vkey=="#I")
            {
                if(pparent->data_type == "TREE" )
                {
                    vkey= pparent->ar_pointer;
                }else
                    vkey = var_f->ar_pointer;
            }

            if(boost::starts_with(vkey, "#IDX"))
            {
                vkey.erase(0, 4);
                int ix = 0;
                try
                {
                    ix = boost::lexical_cast<int>(vkey);
                }
                catch(...)
                {

                    error_text = "can not use as integer key value "  + vkey;
                    er_type = -2;
                    return NULL;
                }
                if(pparent->data_type == "TREE" )
                {
                    var_f = pparent;
                }
                var_f = var_f->GetVarIndexInt(ix,var_f);

            }
            else
            {
                if(pparent->data_type == "TREE" )
                {
                    var_f = pparent;
                }

                var_f = var_f->GetVarIndex(vkey,var_f);

            }

            if(var_f==NULL)
            {
                error_text = " array item not found [" + vkey + "] of " + pname;
                er_type = -3;
                return NULL;
            }
        }
        pparent = var_f;

    }

    return pparent;



}
void MCVar::CopyChildren(MCVar* from,MCVar* to)
{
    for (std::vector<MCDataNode *>::iterator it = from->children.begin() ; it != from->children.end(); ++it)
    {
        MCVar* comp = (MCVar*) *it;
        MCVar* newcomp = new MCVar();
        newcomp->data = comp->data;
        newcomp->data_type = comp->data_type;
        newcomp->data_class = comp->data_class;
        newcomp->var_name = comp->var_name;
        newcomp->is_ref = comp->is_ref;
        to->AddChild(newcomp);
    }
}
int MCVar::CopyType(std::string ptype,MCVar* child, MCVar* type_scope,std::string &error_text)
{
    MCVar* t_var = FindSibling(ptype,type_scope);
    if(t_var == NULL)
    {
        error_text = " unknown type " + ptype;
        return -2;
    }
    child->refclass = t_var;
    child->extended_type = t_var->extended_type;
    //Just check
    for (std::vector<MCDataNode *>::iterator it = t_var->children.begin() ; it != t_var->children.end(); ++it)
    {
        MCVar* comp = (MCVar*) *it;
        MCVar* new_comp = new MCVar();
        new_comp->var_name = comp->var_name;
        MCVar* created_var = NULL;
        int ret = child->CreateVar(comp->var_name,comp->data_type,"",type_scope,error_text,created_var);
        if(ret!=0)
            return ret;
        if(comp->data_type=="FUNC")
        {
            created_var->line_ref = comp->line_ref;
            created_var->data = comp->var_name;
            CopyChildren(comp,created_var);
        }

    }
    return 0;
}
int MCVar::CreateVar(std::string pname,std::string ptype,std::string pvalue,MCVar* type_scope,std::string &error_text,MCVar* &cr_var,bool extends_type)
{

    MCVar* pparent = this;


    MCVar* var_f = FindSibling(pname,pparent);
    if(var_f!=NULL && ptype != "TREE")
    {
        error_text = " object exists " + pname;
        return -1;
    }
    if(!AllowName(pname))
    {
        error_text = " Name is not allowed " + pname;
        return -3;
    }
    MCVar* newvar = new MCVar();
    bool is_object = false;
    if(!(std::find(MCVar::meta_types.begin(), MCVar::meta_types.end(), ptype) != MCVar::meta_types.end()))
    {
        int ret = CopyType(ptype,newvar,type_scope,error_text);
        if(ret!=0)
        {
            delete newvar;
            return ret;
        }

        is_object = true;

    }

    if(is_object)
    {
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        newvar->data = boost::lexical_cast<std::string>(uuid);

    }
    else
    {
        newvar->data = pvalue;
        newvar->extended_type = ptype;
    }

    if(extends_type)
    {
        newvar->data_type = "TYPE";
        newvar->extended_type = extended_type + "/" + ptype;
    }
    else
        newvar->data_type = ptype;

    newvar->var_name = pname;

    AddChild(newvar);
    if(ptype=="TREE")
    {
        newvar->asoc_index = std::to_string(ar_index);
        ar_index++;
        ReindexChildren();

    }
    cr_var = newvar;
    return 0;
}
int MCVar::CreateArrayItem(std::string pindex,std::string pvalue,MCVar* type_scope,std::string &error_text,MCVar* &cr_var)
{


    if(data_type != "ARRAY")
    {
        error_text = " array is the type of " + var_name;
        return -3;
    }

    if(GetVarIndex(pindex,this)!=NULL)
        return -1;

    MCVar* newvar = new MCVar();
    bool is_object = false;
    if(!(std::find(MCVar::meta_types.begin(), MCVar::meta_types.end(), array_type) != MCVar::meta_types.end()))
    {
        int ret = CopyType(array_type,newvar,type_scope,error_text);
        if(ret!=0)
        {
            delete newvar;
            return ret;
        }
        is_object = true;
    }

    if(is_object)
    {
        boost::uuids::uuid uuid = boost::uuids::random_generator()();
        newvar->data = boost::lexical_cast<std::string>(uuid);

    }
    else
        newvar->data = pvalue;

    newvar->data_type = array_type;
    AddChild(newvar);
    if(pindex=="")
    {
        pindex = std::to_string(ar_index);
        ar_index++;
    }
    newvar->var_name = var_name;
    newvar->asoc_index = pindex;
    newvar->is_arrayitem = true;
    ar_pointer = pindex;
    cr_var = newvar;
    ReindexChildren();
    return 0;
}
MCVar* MCVar::GetVar(std::string pname)
{
    for (std::vector<MCDataNode *>::iterator it = children.begin() ; it != children.end(); ++it)
    {
        MCVar* var =(MCVar*) *it;
        if(var->var_name == pname)
            return var;
    }

    return NULL;


}
MCVar* MCVar::GetVarIndex(std::string pindex,MCVar* pparent)
{

    for (std::vector<MCDataNode *>::iterator it = pparent->children.begin() ; it != pparent->children.end(); ++it)
    {
        MCVar* var =(MCVar*) *it;
        if(var->asoc_index == pindex)
            return var;
    }

    return NULL;


}
MCVar* MCVar::GetVarIndexInt(int pindex,MCVar* pparent)
{

    for (std::vector<MCDataNode *>::iterator it = pparent->children.begin() ; it != pparent->children.end(); ++it)
    {
        MCVar* var =(MCVar*) *it;
        if(var->num_index == pindex)
            return var;
    }

    return NULL;


}
MCVar::~MCVar()
{
    //dtor
}
