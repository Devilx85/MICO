#include "MCFunc.h"
#include "MCFuncLibCore.h"
#include <iostream>
#include <fstream>



MCFuncLibCore::MCFuncLibCore()
{
    //ctor
}
void MCFuncLibCore::RegFunc(MCFuncRegister * reg)
{

    MCFunc* _f_a_plus = new MCFunc();
    _f_a_plus->name = "+";
    _f_a_plus->templ->data_type = "FUNC";
    _f_a_plus->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_a_plus->templ->AddParam("COMP","+","REQ");
    _f_a_plus->templ->AddParam("ANY","VALUE2","CSQ","NUMC");
    reg->pos_func = _f_a_plus;
    _f_a_plus->func_ref = &_A_ARITH;
    reg->AddFunc(_f_a_plus);

    MCFunc* _f_a_minus = new MCFunc();
    _f_a_minus->name = "-";
    _f_a_minus->templ->data_type = "FUNC";
    _f_a_minus->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_a_minus->templ->AddParam("COMP","-","REQ");
    _f_a_minus->templ->AddParam("ANY","VALUE2","CSQ","NUMC");
    _f_a_minus->func_ref = &_A_ARITH;
    reg->neg_func = _f_a_minus;
    reg->AddFunc(_f_a_minus);

    MCFunc* _f_a_minus_sh = new MCFunc();
    _f_a_minus_sh->name = "N";
    _f_a_minus_sh->templ->data_type = "FUNC";
    _f_a_minus_sh->templ->AddParam("COMP","-","REQ");
    _f_a_minus_sh->templ->AddParam("ANY","VALUE1","CSQ","NUMC");
    _f_a_minus_sh->func_ref = &_A_ARITH;
    reg->AddFunc(_f_a_minus_sh);

    MCFunc* _f_a_div = new MCFunc();
    _f_a_div->name = "/";
    _f_a_div->calc_order = 0;
    _f_a_div->templ->data_type = "FUNC";
    _f_a_div->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_a_div->templ->AddParam("COMP","/","REQ");
    _f_a_div->templ->AddParam("ANY","VALUE2","CSQ","NUMC");
    _f_a_div->func_ref = &_A_ARITH;
    reg->AddFunc(_f_a_div);

    MCFunc* _f_a_multi = new MCFunc();
    _f_a_multi->name = "*";
    _f_a_multi->calc_order = 0;
    _f_a_multi->templ->data_type = "FUNC";
    _f_a_multi->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_a_multi->templ->AddParam("COMP","*","REQ");
    _f_a_multi->templ->AddParam("ANY","VALUE2","CSQ","NUMC");
    _f_a_multi->func_ref = &_A_ARITH;
    reg->AddFunc(_f_a_multi);

    MCFunc* _f_a_eq = new MCFunc();
    _f_a_eq->name = "=";
    _f_a_eq->templ->data_type = "FUNC";
    _f_a_eq->templ->AddParam("ANY","VALUE1","REQ");
    _f_a_eq->templ->AddParam("COMP","=","REQ");
    _f_a_eq->templ->AddParam("ANY","VALUE2","CSQ");
    _f_a_eq->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_eq);

    MCFunc* _f_a_bg = new MCFunc();
    _f_a_bg->name = ">";
    _f_a_bg->templ->data_type = "FUNC";
    _f_a_bg->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_a_bg->templ->AddParam("COMP",">","REQ");
    _f_a_bg->templ->AddParam("ANY","VALUE2","CSQ","NUMC");
    _f_a_bg->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_bg);

    MCFunc* _f_a_sm = new MCFunc();
    _f_a_sm->name = "<";
    _f_a_sm->templ->data_type = "FUNC";
    _f_a_sm->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_a_sm->templ->AddParam("COMP","<","REQ");
    _f_a_sm->templ->AddParam("ANY","VALUE2","CSQ","NUMC");
    _f_a_sm->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_sm);

    MCFunc* _f_a_smeq = new MCFunc();
    _f_a_smeq->name = "<=";
    _f_a_smeq->templ->data_type = "FUNC";
    _f_a_smeq->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_a_smeq->templ->AddParam("COMP","<=","REQ");
    _f_a_smeq->templ->AddParam("ANY","VALUE2","CSQ","NUMC");
    _f_a_smeq->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_smeq);

    MCFunc* _f_a_bgeq = new MCFunc();
    _f_a_bgeq->name = ">=";
    _f_a_bgeq->templ->data_type = "FUNC";
    _f_a_bgeq->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_a_bgeq->templ->AddParam("COMP",">=","REQ");
    _f_a_bgeq->templ->AddParam("ANY","VALUE2","CSQ","NUMC");
    _f_a_bgeq->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_bgeq);

     MCFunc* _f_a_noneq = new MCFunc();
    _f_a_noneq->name = "<>";
    _f_a_noneq->templ->data_type = "FUNC";
    _f_a_noneq->templ->AddParam("ANY","VALUE1","REQ");
    _f_a_noneq->templ->AddParam("COMP","<>","REQ");
    _f_a_noneq->templ->AddParam("ANY","VALUE2","CSQ");
    _f_a_noneq->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_noneq);

    MCFunc* _f_a_logand = new MCFunc();
    _f_a_logand->name = "AND";
    _f_a_logand->templ->data_type = "FUNC";
    _f_a_logand->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_a_logand->templ->AddParam("COMP","AND","REQ");
    _f_a_logand->templ->AddParam("ANY","VALUE2","REQ","NUMC");
    _f_a_logand->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_logand);

     MCFunc* _f_a_logor = new MCFunc();
    _f_a_logor->name = "OR";
    _f_a_logor->templ->data_type = "FUNC";
    _f_a_logor->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_a_logor->templ->AddParam("COMP","OR","REQ");
    _f_a_logor->templ->AddParam("ANY","VALUE2","REQ","NUMC");
    _f_a_logor->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_logor);

    MCFunc* _f_a_lognot = new MCFunc();
    _f_a_lognot->name = "NOT";
    _f_a_lognot->templ->data_type = "FUNC";
    _f_a_lognot->templ->AddParam("COMP","NOT","REQ");
    _f_a_lognot->templ->AddParam("ANY","VALUE2","REQ","NUMC");
    _f_a_lognot->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_lognot);

    MCFunc* _f_a_logempty = new MCFunc();
    _f_a_logempty->name = "EMPTY";
    _f_a_logempty->templ->data_type = "FUNC";
    _f_a_logempty->templ->AddParam("COMP","EMPTY","REQ");
    _f_a_logempty->templ->AddParam("ANY","VALUE2","REQ","NUMC");
    _f_a_logempty->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_logempty);


    /*COMP**********************************************/
     MCFunc* _f_var = new MCFunc();
    _f_var->name = MCVar::simple_type;
    _f_var->templ->data_type = "FUNC";
    _f_var->templ->AddParam("COMP","VAR","REQ");
    _f_var->templ->AddParam("NAME","VARNAME","REQ");
    _f_var->templ->AddParam("COMP","VALUE","OPT");
    _f_var->templ->AddParam("ANY","VARVALUE","OPTC");
    _f_var->templ->AddParam("COMP","TYPE","OPT");
    _f_var->templ->AddParam("NAME","TYPENAME","OPTC");
    _f_var->templ->AddParam("COMP","OF","OPT");
    _f_var->templ->AddParam("NAME","ARRAYTYPE","OPTC");
    _f_var->func_ref = &_VAR;
    reg->AddFunc(_f_var);

     MCFunc* _f_out = new MCFunc();
    _f_out->name = "OUT";
    _f_out->templ->data_type = "FUNC";
    _f_out->templ->AddParam("COMP","OUT","REQ");
    _f_out->templ->AddParam("COMP","SPACED","OPT","ADD");
    _f_out->templ->AddParam("ANY","VALUE","SEQ");
    _f_out->func_ref = &_OUT;
    reg->AddFunc(_f_out);

    MCFunc* _f_concat = new MCFunc();
    _f_concat->name = "CONCAT";
    _f_concat->templ->data_type = "FUNC";
    _f_concat->templ->AddParam("COMP","CONCAT","REQ");
    _f_concat->templ->AddParam("COMP","SPACED","OPT","ADD");
    _f_concat->templ->AddParam("ANY","VALUE","SEQ");
    _f_concat->func_ref = &_CONCAT;
    reg->AddFunc(_f_concat);

    MCFunc* _f_do_times = new MCFunc();
    _f_do_times->name = "DO";
    _f_do_times->templ->data_type = "FUNC";
    _f_do_times->templ->AddParam("COMP","DO","REQ");
    _f_do_times->templ->AddParam("ANY","VALUE","REQ","NUMC");
    _f_do_times->templ->AddParam("COMP","TIMES","REQ");
    _f_do_times->func_ref = &_DO_TIMES;
    reg->AddFunc(_f_do_times);

    MCFunc* _f_for = new MCFunc();
    _f_for->name = "FOR";
    _f_for->templ->data_type = "FUNC";
    _f_for->templ->AddParam("COMP","FOR","REQ");
    _f_for->templ->AddParam("VAR","VAR","REQ");
    _f_for->templ->AddParam("COMP","FROM","REQ");
    _f_for->templ->AddParam("ANY","VALUE1","REQ","NUMC");
    _f_for->templ->AddParam("COMP","TO","REQ");
    _f_for->templ->AddParam("ANY","VALUE2","REQ","NUMC");
    _f_for->func_ref = &_FOR;
    reg->AddFunc(_f_for);

    MCFunc* _f_if = new MCFunc();
    _f_if->name = "IF";
    _f_if->templ->data_type = "FUNC";
    _f_if->templ->AddParam("COMP","IF","REQ");
    _f_if->templ->AddParam("ANY","VALUE","REQ");
    _f_if->func_ref = &_IF;
    reg->AddFunc(_f_if);

    MCFunc* _f_type_def = new MCFunc();
    _f_type_def->name = "TYPE DEF";
    _f_type_def->templ->data_type = "FUNC";
    _f_type_def->templ->AddParam("COMP","TYPE","REQ");
    _f_type_def->templ->AddParam("COMP","DEF","REQ");
    _f_type_def->templ->AddParam("NAME","TYPENAME","REQ");
    _f_type_def->templ->AddParam("COMP","EXTENDS","OPT");
    _f_type_def->templ->AddParam("NAME","EXTNAME","OPTC");
    _f_type_def->func_ref = &_TYPE_DEF;
    reg->AddFunc(_f_type_def);


     MCFunc* _f_set = new MCFunc();
    _f_set->name = "SET";
    _f_set->templ->data_type = "FUNC";
    _f_set->templ->AddParam("COMP","SET","REQ");
    _f_set->templ->AddParam("VAR","VARNAME","REQ");
    _f_set->templ->AddParam("ANY","VARVALUE","REQ");
    _f_set->func_ref = &_SET;
    reg->AddFunc(_f_set);

     MCFunc* _f_set2 = new MCFunc();
    _f_set2->name = ":=";
    _f_set2->templ->data_type = "FUNC";
    _f_set2->templ->AddParam("VAR","VARNAME","REQ");
    _f_set2->templ->AddParam("COMP",":=","REQ");
    _f_set2->templ->AddParam("ANY","VARVALUE","REQ");
    _f_set2->func_ref = &_SET;
    reg->AddFunc(_f_set2);

     MCFunc* _f_add_item = new MCFunc();
    _f_add_item->name = "ADD ITEM";
    _f_add_item->templ->data_type = "FUNC";
    _f_add_item->templ->AddParam("COMP","ADD","REQ");
    _f_add_item->templ->AddParam("COMP","ITEM","REQ");
    _f_add_item->templ->AddParam("VAR","VARNAME","REQ");
    _f_add_item->func_ref = &_ADD_ITEM;
    reg->AddFunc(_f_add_item);

     MCFunc* _f_def_func = new MCFunc();
    _f_def_func->name = "DEF FUNC";
    _f_def_func->templ->data_type = "FUNC";
    _f_def_func->templ->AddParam("COMP","FUNC","REQ");
    _f_def_func->templ->AddParam("COMP","DEF","REQ");
    _f_def_func->templ->AddParam("NAME","FNAME","REQ");
    _f_def_func->templ->AddParam("NAME","VALUE","SEQ");
    _f_def_func->func_ref = &_DEF_FUNC;
    reg->AddFunc(_f_def_func);



    MCFunc* _f_call_func = new MCFunc();
    _f_call_func->name = "CALL FUNC";
    _f_call_func->templ->data_type = "FUNC";
    _f_call_func->templ->AddParam("COMP","CALL","REQ");
    _f_call_func->templ->AddParam("COMP","FUNC","REQ");
    _f_call_func->templ->AddParam("NAME","FNAME","REQ");
    _f_call_func->templ->AddParam("ANY","VALUE","SEQ");
    _f_call_func->templ->AddParam("COMP","OUT","OPT");
    _f_call_func->templ->AddParam("VAR","REF","SEQ");
    _f_call_func->func_ref = &_CALL_FUNC;
    reg->AddFunc(_f_call_func);
    reg->call_func = _f_call_func;

    MCFunc* _f_len = new MCFunc();
    _f_len->name = "LEN";
    _f_len->templ->data_type = "FUNC";
    _f_len->templ->AddParam("COMP","LEN","REQ");
    _f_len->templ->AddParam("VAR","VARNAME","REQ");
    _f_len->func_ref = &_LEN;
    reg->AddFunc(_f_len);

    MCFunc* _f_mytype = new MCFunc();
    _f_mytype->name = "MYTYPE";
    _f_mytype->templ->data_type = "FUNC";
    _f_mytype->templ->AddParam("COMP","MYTYPE","REQ");
    _f_mytype->templ->AddParam("VAR","VARNAME","REQ");
    _f_mytype->func_ref = &_MYTYPE;
    reg->AddFunc(_f_mytype);

    MCFunc* _f_ce = new MCFunc();
    _f_ce->name = "CE";
    _f_ce->templ->data_type = "FUNC";
    _f_ce->templ->AddParam("COMP","CE","REQ");
    _f_ce->templ->AddParam("VAR","VARNAME","REQ");
    _f_ce->func_ref = &_CE;
    reg->AddFunc(_f_ce);

    MCFunc* _f_savetofile = new MCFunc();
    _f_savetofile->name = "SAVE TO FILE";
    _f_savetofile->templ->data_type = "FUNC";
    _f_savetofile->templ->AddParam("COMP","SAVE","REQ");
    _f_savetofile->templ->AddParam("ANY","VALUE","REQ");
    _f_savetofile->templ->AddParam("COMP","TO","REQ");
    _f_savetofile->templ->AddParam("COMP","FILE","REQ");
    _f_savetofile->templ->AddParam("ANY","FILENAME","REQ");
    _f_savetofile->func_ref = &_SAVETOFILE;
    reg->AddFunc(_f_savetofile);

    MCFunc* _f_loadfromfile = new MCFunc();
    _f_loadfromfile->name = "LOAD FROM FILE";
    _f_loadfromfile->templ->data_type = "FUNC";
    _f_loadfromfile->templ->AddParam("COMP","LOAD","REQ");
    _f_loadfromfile->templ->AddParam("VAR","VARNAME","REQ");
    _f_loadfromfile->templ->AddParam("COMP","FROM","REQ");
    _f_loadfromfile->templ->AddParam("COMP","FILE","REQ");
    _f_loadfromfile->templ->AddParam("ANY","FILENAME","REQ");
    _f_loadfromfile->func_ref = &_LOADFROMFILE;
    reg->AddFunc(_f_loadfromfile);

/* TYPE FUNCTIONS ********************************************************************************
*************************************************************************************************/

    MCFunc* _f_type_of = new MCFunc();
    _f_type_of->name = "TYPE OF";
    _f_type_of->func_type = "TYPE";
    _f_type_of->templ->data_type = "FUNC";
    _f_type_of->templ->AddParam("NAME","NAME","REQ");
    _f_type_of->templ->AddParam("COMP","TYPE","REQ");
    _f_type_of->templ->AddParam("COMP","OF","REQ");
    _f_type_of->templ->AddParam("NAME","TYPENAME","REQ");
    _f_type_of->func_ref = &_TYPE_OF;
    reg->AddFunc(_f_type_of);

    MCFunc* _f_def_method = new MCFunc();
    _f_def_method->name = "DEF FUNC";
    _f_def_method->func_type = "TYPE";
    _f_def_method->templ->data_type = "FUNC";
    _f_def_method->templ->AddParam("COMP","METHOD","REQ");
    _f_def_method->templ->AddParam("COMP","DEF","REQ");
    _f_def_method->templ->AddParam("NAME","FNAME","REQ");
    _f_def_method->templ->AddParam("NAME","VALUE","SEQ");
    _f_def_method->func_ref = &_DEF_METHOD;
    reg->AddFunc(_f_def_method);

}



MCFuncLibCore::~MCFuncLibCore()
{
    //dtor
}

/*FUNCTIONS*/

 MCRet* _VAR(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
     MCRet* RET = new MCRet();
     MCFParams* name = params->GetParam("VARNAME");
     MCFParams* typeof = params->GetParam("ARRAYTYPE");

     std::string v_name = name->ref_line->data;
     std::string v_value = "";
     MCFParams* var_value = params->GetParam("VARVALUE");
     if(var_value!=NULL)
     v_value = var_value->value->ret_data;
     std::string error_text = "";
     MCVar* cr_var;
     std::string var_type = MCVar::simple_type;
     std::string array_type = MCVar::simple_type;

     MCFParams* vtype = params->GetParam("TYPENAME");
     if(vtype!=NULL)
           {
             var_type = vtype->ref_line->data;
             if(var_type!="ARRAY" && typeof!=NULL)
             {
                MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_NOT_FOUND,"","ERROR","You can not specify item type of non-array object " + v_name,-100);
                return RET;
             }
           }
            else
           {
             if(typeof!=NULL)
             {
                MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_NOT_FOUND,"","ERROR","You can not specify item type of non-array object " + v_name,-100);
                return RET;
             }
           }

     if(var_type=="ARRAY" && typeof!=NULL )
        {
            if( types->FindSibling(typeof->ref_line->data,types) == NULL)
            {
                MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_NOT_FOUND,"","ERROR","Type of item not found " + typeof->ref_line->data,-100);
                return RET;
            }
            array_type = typeof->ref_line->data;
        }

     int res = vars->CreateVar(v_name,var_type,v_value,types,error_text,cr_var);

     if(var_type=="ARRAY")
        {
            cr_var->array_type = array_type;
        }

     if(res==-1)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_VAR_EXIST,"","ERROR","Object already exists " + v_name + " : " + error_text,-100);
        return RET;

     }else
     if(res==-2)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_NOT_FOUND,"","ERROR","Can not find all types for " + v_name+ " : " + error_text,-100);
        return RET;

     }
    if(res==-3)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_NAME_NOT_ALLOWED,"","ERROR","Name is not allowed : " + v_name,-100);
        return RET;
     }
     return RET;
 }
  MCRet* _SET(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {

     MCFParams* name = params->GetParam("VARNAME");
     MCFParams* var_value = params->GetParam("VARVALUE");
     if(name->value->ref_var->data_type!=MCVar::simple_type)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_PROTECTED_VALUE,"","ERROR","Can not assign value for type " + name->value->ref_var->data_type + " in line [" + engine->cur_code->data +  "]",-100);
        return RET;
     }
     std::string v_value = var_value->value->ret_data;
     std::string error_text = "";
     name->value->ref_var->data = v_value;

    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
 }
  MCRet* _CE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {

     MCFParams* name = params->GetParam("VARNAME");
     std::string error_txt = name->value->ref_var->SetValue("");
     if(error_txt!="")
        return engine->RetCreate(engine->_C_F_PROTECTED_VALUE,"ERROR","",error_txt  + " in line [" + engine->cur_code->data +  "]" ,0);
    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
 }
 MCRet* _MYTYPE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {

    MCFParams* name = params->GetParam("VARNAME");
    MCRet* RET = engine->RetCreate(0,name->value->ref_var->extended_type,"","",0);
    return RET;
 }
   MCRet* _LEN(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {

     MCFParams* varname = params->GetParam("VARNAME");
     MCVar* var = varname->value->ref_var;
     std::string v_len = "0";
     if(var->data_type=="ARRAY")
     {
         v_len = std::to_string(var->children.size());

     }
     else

     {
         v_len = std::to_string(var->data.size());
     }

    MCRet* RET = engine->RetCreate(0,v_len,"VALUE","",0);
    return RET;
 }

 MCRet* _OUT(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
     MCRet* RET = new MCRet();
     MCFParams* spaced = params->GetParam("SPACED");
     bool is_spaced = false;
     if(spaced!=NULL)
        is_spaced = true;
     for (std::vector<MCDataNode *>::iterator it = params->children.begin() ; it != params->children.end(); ++it)
     {
        MCFParams* param =(MCFParams*) *it;
        if(is_spaced)
             RET->bufout  =  RET->bufout  + " ";
        RET->bufout = RET->bufout + param->value->ret_data;
     }
     RET->ret_type = "OUT";
     return RET;
 }

 MCRet* _SAVETOFILE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {

     MCFParams* text = params->GetParam("VALUE");
     std::string val_to_save = text->value->ret_data;
     MCFParams* fname = params->GetParam("FILENAME");
     std::string filename = fname->value->ret_data;

     std::ofstream out(filename);
     out << val_to_save;
     out.close();
     MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;

 }
 MCRet* _LOADFROMFILE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {

     MCFParams* toload = params->GetParam("VARNAME");
     MCFParams* fname = params->GetParam("FILENAME");
     std::string filename = fname->value->ret_data;
     std::ifstream ifs(filename);
     std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
     std::string error_txt = toload->value->ref_var->SetValue(content);
     if(error_txt!="")
        return engine->RetCreate(engine->_C_F_PROTECTED_VALUE,"ERROR","",error_txt  + " in line [" + engine->cur_code->data +  "]" ,0);

     MCRet* RET = engine->RetCreate(0,content,"","",0);
     return RET;

 }

 MCRet* _CONCAT(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
     MCRet* RET = new MCRet();
    MCFParams* spaced = params->GetParam("SPACED");
     bool is_spaced = false;
     if(spaced!=NULL)
        is_spaced = true;

     for (std::vector<MCDataNode *>::iterator it = params->children.begin() ; it != params->children.end(); ++it)
     {
        MCFParams* param =(MCFParams*) *it;
        if(is_spaced)
            RET->ret_data = RET->ret_data + " ";
        RET->ret_data = RET->ret_data + param->value->ret_data;
     }
     RET->ret_type = "VALUE";
     return RET;
 }
  MCRet* _IF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
     MCRet* RET = new MCRet();
     MCFParams* var_value = params->GetParam("VALUE");
     std::string v_value = "";
     v_value = var_value->value->ret_data;
     MCRet* RET_INT = engine->CastNumc(v_value);
     if(RET_INT->code<0)
            return RET_INT;
     double res = RET_INT->ret_nr;
     delete RET_INT;
     if(res==1)
     {
        MCRet* RES = engine->EvaluateLine(line,vars,types);

        if(RES != NULL)
        if(RES->code < 0 || RES->stop_code != 0)
            return RES;
        delete RES;
     }

     RET->ret_type = "VALUE";
     return RET;
 }
 MCRet* _DO_TIMES(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
     MCRet* RET = new MCRet();
     MCFParams* var_value = params->GetParam("VALUE");
     double cycles = var_value->value->ret_nr;
     engine->inner_cycle_counter = 0;
     for(int ic=0;ic<cycles;ic++)
     {
        engine->inner_cycle_counter ++;
        MCRet* RES = engine->EvaluateLine(line,vars,types);

        if(RES == NULL)
            continue;

        if(RES->code < 0 || RES->stop_code != 0)
            return RES;

        delete RES;
     }
     RET->ret_type = "VALUE";
     return RET;
 }
MCRet* _FOR(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{
     MCRet* RET = new MCRet();

     MCFParams* var_value1 = params->GetParam("VALUE1");
     double from = var_value1->value->ret_nr;

     MCFParams* var_value2 = params->GetParam("VALUE2");
     double to = var_value2->value->ret_nr;

     MCFParams* var_value = params->GetParam(MCVar::simple_type);
     MCVar* var_counter = var_value->value->ref_var;
     if(var_counter->data_type!=MCVar::simple_type)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_PROTECTED_VALUE,"","ERROR","Can not assign value for type " + var_counter->data_type + " in line [" + engine->cur_code->data +  "]",-100);
        return RET;
     }
     if(from<to)
     {
         engine->inner_cycle_counter = 0;
         for(int ic=from;ic<to+1;ic++)
        {
         engine->inner_cycle_counter ++;
        var_counter->data = std::to_string(ic);
        MCRet* RES = engine->EvaluateLine(line,vars,types);

        if(RES == NULL)
            continue;

        if(RES->code < 0 || RES->stop_code != 0)
            return RES;

        delete RES;


        }

     }else
     {
        engine->inner_cycle_counter = 0;
        for(int ic=from;ic>to-1;ic--)
        {
        engine->inner_cycle_counter ++;
        var_counter->data = std::to_string(ic);
        MCRet* RES = engine->EvaluateLine(line,vars,types);
        if(RES == NULL)
            continue;

        if(RES->code < 0 || RES->stop_code != 0)
            return RES;

        delete RES;


        }
     }
     RET->ret_type = "VALUE";
     return RET;

}
MCRet* _A_ARITH(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{
     MCRet* RET = new MCRet();
     MCFParams* var_value1 = params->GetParam("VALUE1");
     if(func->name == "N")
     {
        double val1 = var_value1->value->ret_nr;
        val1 = -val1;
        RET->ret_data = std::to_string(val1);

        RET->ret_data.erase ( RET->ret_data.find_last_not_of('0') + 1, std::string::npos );
        if(RET->ret_data[RET->ret_data.length()-1]=='.')
            RET->ret_data = RET->ret_data.erase(RET->ret_data.length()-1,1);

        RET->ret_type = "VALUE";
        return RET;
     }

     MCFParams* var_value2 = params->GetParam("VALUE2");
     double val1 = var_value1->value->ret_nr;
     double val2 = var_value2->value->ret_nr;

     if(func->name == "+")
     {
        RET->ret_data = std::to_string(val1+val2);

     }else
     if(func->name  == "-")
     {
        RET->ret_data = std::to_string(val1-val2);
     }else
     if(func->name  == "/")
     {
        RET->ret_data = std::to_string(val1/val2);
     }else
    if(func->name  == "*")
     {
        RET->ret_data = std::to_string(val1*val2);
     }

     RET->ret_data.erase ( RET->ret_data.find_last_not_of('0') + 1, std::string::npos );

     if(RET->ret_data[RET->ret_data.length()-1]=='.')
        RET->ret_data = RET->ret_data.erase(RET->ret_data.length()-1,1);

     RET->ret_type = "VALUE";
     return RET;

}

MCRet* _A_COMP(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{
     MCRet* RET = new MCRet();

     MCFParams* var_value2 = params->GetParam("VALUE2");
     std::string v_value2 = "";
     v_value2 = var_value2->value->ret_data;

     if(func->name == "NOT")
     {
        if(v_value2=="0")
            RET->ret_data = "1";
        else
            RET->ret_data = "0";
        RET->ret_type = "VALUE";
        return RET;
     }else
    if(func->name == "EMPTY")
     {
        if(v_value2=="")
            RET->ret_data = "1";
        else
            RET->ret_data = "0";
        RET->ret_type = "VALUE";
        return RET;
     }

     MCFParams* var_value1 = params->GetParam("VALUE1");
     std::string v_value1 = "";
     v_value1 = var_value1->value->ret_data;

     if(func->name  == "AND")
     {


        if(v_value1=="1" && v_value2 == "1")
            RET->ret_data = "1";
        else
            RET->ret_data = "0";

        RET->ret_type = "VALUE";
        return RET;
     }else
     if(func->name  == "OR")
     {


        if(v_value1=="1" || v_value2=="1")
            RET->ret_data = "1";
        else
            RET->ret_data = "0";

        RET->ret_type = "VALUE";
        return RET;
     }else
     if(func->name  == "=")
     {


        if(v_value1==v_value2)
            RET->ret_data = "1";
        else
            RET->ret_data = "0";

        RET->ret_type = "VALUE";
        return RET;
     }else
     if(func->name  == "<>")
     {


        if(v_value1!=v_value2)
            RET->ret_data = "1";
        else
            RET->ret_data = "0";

        RET->ret_type = "VALUE";
        return RET;
     }

     double val1 = var_value1->value->ret_nr;
     double val2 = var_value2->value->ret_nr;



     if(func->name == "<")
     {
        if(val1<val2)
            RET->ret_data = "1";
        else
            RET->ret_data = "0";
     }else
     if(func->name  == ">")
     {
        if(val1>val2)
            RET->ret_data = "1";
        else
            RET->ret_data = "0";
     }else
    if(func->name  == ">=")
     {
        if(val1>=val2)
            RET->ret_data = "1";
        else
            RET->ret_data = "0";
     }
    if(func->name  == "<=")
     {
        if(val1<=val2)
            RET->ret_data = "1";
        else
            RET->ret_data = "0";
     }

     RET->ret_type = "VALUE";
     return RET;

}
 MCRet* _TYPE_DEF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
     MCRet* RET = new MCRet();
     MCFParams* name = params->GetParam("TYPENAME");
     std::string v_name = name->ref_line->data;
     std::string error_text = "";
     std::string type_cr = "TYPE";
     MCFParams* extname = params->GetParam("EXTNAME");
     bool extends_type = false;
     if(extname!=NULL)
     {
        extends_type = true;
        type_cr = extname->ref_line->data;

     }
     MCVar* cr_var;

     int res = types->CreateVar(v_name,type_cr,"",types,error_text,cr_var,extends_type);
     if(res==-1)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_EXIST,"","ERROR","Type already exists " + v_name+ " : " + error_text,-100);
        return RET;

     }else
     if(res==-2)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_NOT_FOUND,"","ERROR","Can not find all types for " + v_name+ " : " + error_text,-100);
        return RET;

     }
     if(res==-3)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_NAME_NOT_ALLOWED,"","ERROR","Name is not allowed " + v_name+ " : " + error_text,-100);
        return RET;

     }
    MCRet* RES = engine->EvaluateLine(line,vars,cr_var,"TYPE");
    if(RES != NULL)
        if(RES->code < 0 || RES->stop_code != 0)
            {
                return RES;

            }

    delete RES;

    return RET;
 }
 MCRet* _TYPE_OF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
     if(types->data=="[GLOBAL]")
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_GLOBAL_TYPE,"","ERROR","Components could be defined only in types",-100);
        return RET;
     }

     MCFParams* vname = params->GetParam("NAME");
     std::string v_name = vname->ref_line->data;
     MCFParams* tname = params->GetParam("TYPENAME");
     std::string t_name = tname->ref_line->data;
     std::string error_text = "";
     MCVar* cr_var;
     int res = types->CreateVar(v_name,t_name,"",engine->type_scope,error_text,cr_var);
     if(res==-1)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_EXIST,"","ERROR","Type already exists " + v_name+ " : " + error_text,-100);
        return RET;

     }else
     if(res==-2)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_NOT_FOUND,"","ERROR","Can not find all types for " + v_name+ " : " + error_text,-100);
        return RET;

     }

    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
 }
  MCRet* _ADD_ITEM(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
     std::string index = "";
     MCFParams* vname = params->GetParam("VARNAME");
     if(vname->value->ref_var->data_type !="ARRAY")
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_NON_ARRAY,"","ERROR","You can not use as array object " + vname->value->ref_var->var_name,-100);
        return RET;
     }

     std::string error_text = "";
     MCVar* cr_var;
     int res = vname->value->ref_var->CreateArrayItem("","",engine->type_scope,error_text,cr_var);

     if(res==-1)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_EXIST,"","ERROR","index already exists " + index+ " : " + error_text,-100);
        return RET;

     }else
     if(res==-2)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_NOT_FOUND,"","ERROR","Can not find all types for " + vname->value->ref_var->var_name+ " : " + error_text,-100);
        return RET;

     }

    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
 }
 MCRet* _DEF_FUNC(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
     MCFParams* fname = params->GetParam("FNAME");

     if(engine->func_scope->FindSibling(fname->ref_line->data,engine->func_scope)!=NULL)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_FUNC_EXIST,"","ERROR","Function already exists " + fname->ref_line->data,-100);
        return RET;
     }

     MCVar* Func = NULL;
     std::string error_txt="";
     int res = engine->func_scope->CreateVar(fname->ref_line->data,"FUNC","",types,error_txt,Func);

    if(res!=0)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_NAME_NOT_ALLOWED,"","ERROR","Can not create object : " + fname->ref_line->data,-100);
        return RET;
     }

     Func->line_ref = line;
     int parser = 0;

     MCVar* pfunc = NULL;

     for (std::vector<MCDataNode *>::iterator it = params->children.begin() ; it != params->children.end(); ++it)
     {
        MCFParams* param =(MCFParams*) *it;
        if(param->ref_vline->data!="VALUE")
            continue;

        if(param->ref_line->data == "TYPED" )
        {
            if(pfunc!=NULL)
            {
                ++it;
                if(it == params->children.end())
                {
                     MCRet* RET = engine->RetCreate(engine->_C_F_INCOMPLETE_DEF,"","ERROR","Incomplete definition of parameter " + pfunc->var_name + " : " + error_txt,-100);
                     return RET;
                }
                MCFParams* next_param =(MCFParams*) *it;

                if(!pfunc->is_ref &&  next_param->ref_line->data!=MCVar::simple_type )
                {
                    MCRet* RET = engine->RetCreate(engine->_C_F_INCOMPLETE_DEF,"","ERROR","Non-VAR types allowed only as references, use OUT keyword " + pfunc->var_name + " : " + error_txt,-100);
                     //delete Func;
                     return RET;
                }
                pfunc->data_class = next_param->ref_line->data;
                continue;
            }

        }


        if(param->ref_line->data == "OUT" )
        {
            parser = 1;
            continue;
        }


            int res = Func->CreateVar(param->ref_line->data,MCVar::simple_type,"",types,error_txt,pfunc);
             if(res==-1)
            {
                MCRet* RET = engine->RetCreate(engine->_C_F_VAR_EXIST,"","ERROR","Parameter already exist " + param->ref_line->data + " : " + error_txt,-100);
                return RET;
            }

        if(parser==1)
            pfunc->is_ref = true;
        pfunc->data_class = MCVar::simple_type;
     }

    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
 }
  MCRet* _DEF_METHOD(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
    if(types->data=="[GLOBAL]")
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_GLOBAL_TYPE,"","ERROR","Components could be defined only in types",-100);
        return RET;
     }

     MCFParams* fname = params->GetParam("FNAME");

     if(types->FindSibling(fname->ref_line->data,types)!=NULL)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_FUNC_EXIST,"","ERROR","Function already exists " + fname->ref_line->data,-100);
        return RET;
     }

     MCVar* Func = NULL;
     std::string error_txt="";
     int res = types->CreateVar(fname->ref_line->data,"FUNC","",types,error_txt,Func);

     if(res!=0)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_NAME_NOT_ALLOWED,"","ERROR","Can not create object : " + fname->ref_line->data,-100);
        return RET;
     }

     Func->line_ref = line;
     int parser = 0;
     MCVar* pfunc = NULL;

     for (std::vector<MCDataNode *>::iterator it = params->children.begin() ; it != params->children.end(); ++it)
     {
        MCFParams* param =(MCFParams*) *it;
        if(param->ref_vline->data!="VALUE")
            continue;

        if(param->ref_line->data == "TYPED" )
        {
            if(pfunc!=NULL)
            {
                ++it;
                if(it == params->children.end())
                {
                     MCRet* RET = engine->RetCreate(engine->_C_F_INCOMPLETE_DEF,"","ERROR","Incomplete definition of parameter " + pfunc->var_name + " : " + error_txt,-100);
                     //delete Func;
                     return RET;
                }
                MCFParams* next_param =(MCFParams*) *it;
                if(!pfunc->is_ref &&  next_param->ref_line->data!=MCVar::simple_type )
                {
                    MCRet* RET = engine->RetCreate(engine->_C_F_INCOMPLETE_DEF,"","ERROR","Non-VAR types allowed only as references, use OUT keyword " + pfunc->var_name + " : " + error_txt,-100);
                     //delete Func;
                     return RET;
                }
                pfunc->data_class = next_param->ref_line->data;
                continue;
            }

        }

        if(param->ref_line->data == "OUT" )
        {
            parser = 1;
            continue;
        }


            int res = Func->CreateVar(param->ref_line->data,MCVar::simple_type,"",types,error_txt,pfunc);
             if(res==-1)
            {
                MCRet* RET = engine->RetCreate(engine->_C_F_VAR_EXIST,"","ERROR","Parameter already exist " + param->ref_line->data + " : " + error_txt,-100);
                return RET;
            }

        if(parser==1)
            pfunc->is_ref = true;

        pfunc->data_class = MCVar::simple_type;

     }

    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
 }
 MCRet* _CALL_FUNC(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
 {
     MCFParams* f_name = params->GetParam("FNAME");
     MCVar* Func = NULL;
     std::string fname = f_name->ref_line->data;

     if(f_name->ref_line->data_type=="METHOD")
     {
         std::string err_txt = "";
         int err_int = 0;
         Func = vars->FindVar(fname,vars,err_txt,err_int);

     }else
     {
         Func = engine->func_scope->FindSibling(f_name->ref_line->data,engine->func_scope);
     }

     if(Func==NULL)
     {
        MCRet* RET = engine->RetCreate(engine->_C_F_FUNC_EXIST,"","ERROR","Function does not exists " + fname,-100);
        return RET;
     }

     std::string error_txt="";

     int var_c  = Func->children.size();
     int var_cc = 0;



     for (std::vector<MCDataNode *>::iterator it = params->children.begin() ; it != params->children.end(); ++it)
     {
        MCFParams* param =(MCFParams*) *it;

        if(param->ref_line->data == fname)
            continue;

        var_cc++;

        if(var_cc>var_c)
        {
        MCRet* RET = engine->RetCreate(engine->_C_F_FUNC_PARAM_ERROR,"","ERROR","Unknown parameter " + param->ref_line->data + " in " + fname,-100);
        return RET;
        }

        MCVar* pfunc = (MCVar*) Func->children.at(var_cc-1);
        if( pfunc->is_ref && param->value->ref_var == NULL)
        {
            MCRet* RET = engine->RetCreate(engine->_C_F_FUNC_PARAM_ERROR,"","ERROR","OUT parameter needs LVALUE " + param->ref_line->data + " in " + fname,-100);
            return RET;
        }
        if(pfunc->data_class!=MCVar::simple_type && param->value->ref_var == NULL )
        {
            MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_MISMATCH,"","ERROR","Parameter has incorrect type VALUE/VAR when " + pfunc->data_class + " needed in  " + fname,-100);
            return RET;
        }
        if(param->value->ref_var !=NULL  && pfunc->data_class != param->value->ref_var->data_type )
        {
            MCRet* RET = engine->RetCreate(engine->_C_F_TYPE_MISMATCH,"","ERROR","Parameter has incorrect type " + param->value->ref_var->data_type + " when " + pfunc->data_class + " needed in  " + fname,-100);
            return RET;
        }

     }

     if(var_cc != var_c)
     {
            MCRet* RET = engine->RetCreate(engine->_C_F_FUNC_PARAM_ERROR,"","ERROR","Not all parameters are provided (" + std::to_string(var_cc)  + ") to " + fname,-100);
            return RET;
     }


     MCVar* lvar_scope = new MCVar();


     var_cc = 0;

     for (std::vector<MCDataNode *>::iterator it = params->children.begin() ; it != params->children.end(); ++it)
     {
        MCFParams* param =(MCFParams*) *it;

        if(param->ref_line->data == fname)
            continue;


        var_cc++;

        MCVar* pfunc = (MCVar*)  Func->children.at(var_cc-1);

        MCVar* actvar = NULL;
        std::string error_txt;

        lvar_scope->CreateVar(pfunc->var_name,MCVar::simple_type, param->value->ret_data,types,error_txt,actvar);

       if(pfunc->is_ref)
        {
            actvar->data_type = "REF";
            actvar->refvar = param->value->ref_var;
        }



     }

    MCVar* actvar = NULL;
    if(f_name->ref_line->data_type=="METHOD")
    {
         lvar_scope->CreateVar("This",MCVar::simple_type, "",types,error_txt,actvar);
         actvar->data_type = "REF";
         actvar->refvar =(MCVar*)  Func->parent;
    }

    MCRet* RES = engine->EvaluateLine(Func->line_ref,lvar_scope,types);
    if(RES != NULL)
        if(RES->code < 0 || RES->stop_code != 0)
            {
                return RES;

            }

    delete RES;
    delete lvar_scope;

    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
 }
