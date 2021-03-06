#include "MCFunc.h"
#include "MCFuncLibCore.h"
#include "MCXMLEngine.h"
#include "MCConst.h"
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
    _f_a_plus->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_a_plus->templ->AddParam(_C_T_COMP,"+",_C_T_REQ);
    _f_a_plus->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    reg->pos_func = _f_a_plus;
    _f_a_plus->func_ref = &_A_ARITH;
    reg->AddFunc(_f_a_plus);

    MCFunc* _f_a_minus = new MCFunc();
    _f_a_minus->name = "-";
    _f_a_minus->templ->data_type = "FUNC";
    _f_a_minus->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_a_minus->templ->AddParam(_C_T_COMP,"-",_C_T_REQ);
    _f_a_minus->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    _f_a_minus->func_ref = &_A_ARITH;
    reg->neg_func = _f_a_minus;
    reg->AddFunc(_f_a_minus);

    MCFunc* _f_a_minus_sh = new MCFunc();
    _f_a_minus_sh->name = "N";
    _f_a_minus_sh->templ->data_type = "FUNC";
    _f_a_minus_sh->templ->AddParam(_C_T_COMP,"-",_C_T_REQ);
    _f_a_minus_sh->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_CSQ,_C_T_NUMC);
    _f_a_minus_sh->func_ref = &_A_ARITH;
    reg->AddFunc(_f_a_minus_sh);

    MCFunc* _f_a_div = new MCFunc();
    _f_a_div->name = "/";
    _f_a_div->calc_order = 0;
    _f_a_div->templ->data_type = "FUNC";
    _f_a_div->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_a_div->templ->AddParam(_C_T_COMP,"/",_C_T_REQ);
    _f_a_div->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    _f_a_div->func_ref = &_A_ARITH;
    reg->AddFunc(_f_a_div);

    MCFunc* _f_a_multi = new MCFunc();
    _f_a_multi->name = "*";
    _f_a_multi->calc_order = 0;
    _f_a_multi->templ->data_type = "FUNC";
    _f_a_multi->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_a_multi->templ->AddParam(_C_T_COMP,"*",_C_T_REQ);
    _f_a_multi->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    _f_a_multi->func_ref = &_A_ARITH;
    reg->AddFunc(_f_a_multi);

    MCFunc* _f_a_eq = new MCFunc();
    _f_a_eq->name = "=";
    _f_a_eq->templ->data_type = "FUNC";
    _f_a_eq->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ);
    _f_a_eq->templ->AddParam(_C_T_COMP,"=",_C_T_REQ);
    _f_a_eq->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ);
    _f_a_eq->calc_order = 0;
    _f_a_eq->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_eq);

    MCFunc* _f_a_bg = new MCFunc();
    _f_a_bg->name = ">";
    _f_a_bg->templ->data_type = "FUNC";
    _f_a_bg->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_a_bg->templ->AddParam(_C_T_COMP,">",_C_T_REQ);
    _f_a_bg->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    _f_a_bg->calc_order = 0;
    _f_a_bg->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_bg);

    MCFunc* _f_a_sm = new MCFunc();
    _f_a_sm->name = "<";
    _f_a_sm->templ->data_type = "FUNC";
    _f_a_sm->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_a_sm->templ->AddParam(_C_T_COMP,"<",_C_T_REQ);
    _f_a_sm->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    _f_a_sm->calc_order = 0;
    _f_a_sm->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_sm);

    MCFunc* _f_a_smeq = new MCFunc();
    _f_a_smeq->name = "<=";
    _f_a_smeq->templ->data_type = "FUNC";
    _f_a_smeq->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_a_smeq->templ->AddParam(_C_T_COMP,"<=",_C_T_REQ);
    _f_a_smeq->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    _f_a_smeq->calc_order = 0;
    _f_a_smeq->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_smeq);

    MCFunc* _f_a_bgeq = new MCFunc();
    _f_a_bgeq->name = ">=";
    _f_a_bgeq->templ->data_type = "FUNC";
    _f_a_bgeq->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_a_bgeq->templ->AddParam(_C_T_COMP,">=",_C_T_REQ);
    _f_a_bgeq->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    _f_a_bgeq->calc_order = 0;
    _f_a_bgeq->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_bgeq);

    MCFunc* _f_a_noneq = new MCFunc();
    _f_a_noneq->name = "<>";
    _f_a_noneq->templ->data_type = "FUNC";
    _f_a_noneq->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ);
    _f_a_noneq->templ->AddParam(_C_T_COMP,"<>",_C_T_REQ);
    _f_a_noneq->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ);
    _f_a_noneq->calc_order = 0;
    _f_a_noneq->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_noneq);

    MCFunc* _f_a_logand = new MCFunc();
    _f_a_logand->name = "AND";
    _f_a_logand->templ->data_type = "FUNC";
    _f_a_logand->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_a_logand->templ->AddParam(_C_T_COMP,"AND",_C_T_REQ);
    _f_a_logand->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    _f_a_logand->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_logand);

    MCFunc* _f_a_logor = new MCFunc();
    _f_a_logor->name = "OR";
    _f_a_logor->templ->data_type = "FUNC";
    _f_a_logor->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_a_logor->templ->AddParam(_C_T_COMP,"OR",_C_T_REQ);
    _f_a_logor->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    _f_a_logor->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_logor);

    MCFunc* _f_a_lognot = new MCFunc();
    _f_a_lognot->name = "NOT";
    _f_a_lognot->templ->data_type = "FUNC";
    _f_a_lognot->templ->AddParam(_C_T_COMP,"NOT",_C_T_REQ);
    _f_a_lognot->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_CSQ,_C_T_NUMC);
    _f_a_lognot->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_lognot);

    MCFunc* _f_a_logempty = new MCFunc();
    _f_a_logempty->name = "EMPTY";
    _f_a_logempty->templ->data_type = "FUNC";
    _f_a_logempty->templ->AddParam(_C_T_COMP,"EMPTY",_C_T_REQ);
    _f_a_logempty->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_REQ,_C_T_NUMC);
    _f_a_logempty->func_ref = &_A_COMP;
    reg->AddFunc(_f_a_logempty);


    /*COMP**********************************************/
    MCFunc* _f_var = new MCFunc();
    _f_var->name = MCVar::simple_type;
    _f_var->templ->data_type = "FUNC";
    _f_var->templ->AddParam(_C_T_COMP,"VAR",_C_T_REQ);
    _f_var->templ->AddParam(_C_T_NAME,"VARNAME",_C_T_REQ);
    _f_var->templ->AddParam(_C_T_COMP,"VALUE",_C_T_OPT);
    _f_var->templ->AddParam(_C_T_ANY,"VARVALUE",_C_T_OPTC);
    _f_var->templ->AddParam(_C_T_COMP,"TYPE",_C_T_OPT);
    _f_var->templ->AddParam(_C_T_NAME,"TYPENAME",_C_T_OPTC);
    _f_var->templ->AddParam(_C_T_COMP,"OF",_C_T_OPT);
    _f_var->templ->AddParam(_C_T_NAME,"ARRAYTYPE",_C_T_OPTC);
    _f_var->func_ref = &_VAR;
    reg->AddFunc(_f_var);

    MCFunc* _f_out = new MCFunc();
    _f_out->name = "OUT";
    _f_out->templ->data_type = "FUNC";
    _f_out->templ->AddParam(_C_T_COMP,"OUT",_C_T_REQ);
    _f_out->templ->AddParam(_C_T_COMP,"SPACED",_C_T_OPT,_C_DC_ADD);
    _f_out->templ->AddParam(_C_T_ANY,"VALUE",_C_T_SEQ);
    _f_out->func_ref = &_OUT;
    reg->AddFunc(_f_out);

    MCFunc* _f_concat = new MCFunc();
    _f_concat->name = "CONCAT";
    _f_concat->templ->data_type = "FUNC";
    _f_concat->templ->AddParam(_C_T_COMP,"CONCAT",_C_T_REQ);
    _f_concat->templ->AddParam(_C_T_COMP,"SPACED",_C_T_OPT,_C_DC_ADD);
    _f_concat->templ->AddParam(_C_T_ANY,"VALUE",_C_T_SEQ);
    _f_concat->func_ref = &_CONCAT;
    reg->AddFunc(_f_concat);

    MCFunc* _f_do_times = new MCFunc();
    _f_do_times->name = "DO";
    _f_do_times->templ->data_type = "FUNC";
    _f_do_times->templ->AddParam(_C_T_COMP,"DO",_C_T_REQ);
    _f_do_times->templ->AddParam(_C_T_ANY,"VALUE",_C_T_REQ,_C_T_NUMC);
    _f_do_times->templ->AddParam(_C_T_COMP,"TIMES",_C_T_REQ);
    _f_do_times->func_ref = &_DO_TIMES;
    reg->AddFunc(_f_do_times);

    MCFunc* _f_for = new MCFunc();
    _f_for->name = "FOR";
    _f_for->templ->data_type = "FUNC";
    _f_for->templ->AddParam(_C_T_COMP,"FOR",_C_T_REQ);
    _f_for->templ->AddParam(_C_T_VAR,"VAR",_C_T_REQ);
    _f_for->templ->AddParam(_C_T_COMP,"FROM",_C_T_REQ);
    _f_for->templ->AddParam(_C_T_ANY,"VALUE1",_C_T_REQ,_C_T_NUMC);
    _f_for->templ->AddParam(_C_T_COMP,"TO",_C_T_REQ);
    _f_for->templ->AddParam(_C_T_ANY,"VALUE2",_C_T_REQ,_C_T_NUMC);
    _f_for->func_ref = &_FOR;
    reg->AddFunc(_f_for);

    MCFunc* _f_loop = new MCFunc();
    _f_loop->name = "LOOP";
    _f_loop->templ->data_type = "FUNC";
    _f_loop->templ->AddParam(_C_T_COMP,"LOOP",_C_T_REQ);
    _f_loop->templ->AddParam(_C_T_VAR,"VAR",_C_T_REQ);
    _f_loop->templ->AddParam(_C_T_COMP,"BY",_C_T_OPT);
    _f_loop->templ->AddParam(_C_T_NAME,"NODENAME",_C_T_OPTC);
    _f_loop->func_ref = &_LOOP;
    reg->AddFunc(_f_loop);


    MCFunc* _f_if = new MCFunc();
    _f_if->name = "IF";
    _f_if->templ->data_type = "FUNC";
    _f_if->templ->AddParam(_C_T_COMP,"IF",_C_T_REQ);
    _f_if->templ->AddParam(_C_T_ANY,"VALUE",_C_T_REQ);
    _f_if->func_ref = &_IF;
    reg->if_func = _f_if;
    reg->AddFunc(_f_if);

    MCFunc* _f_else = new MCFunc();
    _f_else->name = "ELSE";
    _f_else->templ->data_type = "FUNC";
    _f_else->templ->AddParam(_C_T_COMP,"ELSE",_C_T_REQ);
    _f_else->func_ref = &_ELSE;
    reg->AddFunc(_f_else);

    MCFunc* _f_while = new MCFunc();
    _f_while->name = "WHILE";
    _f_while->templ->data_type = "FUNC";
    _f_while->templ->AddParam(_C_T_COMP,"WHILE",_C_T_REQ);
    _f_while->templ->AddParam(_C_T_ANY,"VALUE",_C_T_REQ);
    _f_while->func_ref = &_WHILE;
    reg->AddFunc(_f_while);

    MCFunc* _f_islast = new MCFunc();
    _f_islast->name = "IS LAST";
    _f_islast->templ->data_type = "FUNC";
    _f_islast->templ->AddParam(_C_T_COMP,"IS",_C_T_REQ);
    _f_islast->templ->AddParam(_C_T_COMP,"LAST",_C_T_OPT,_C_DC_ADD);
    _f_islast->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_islast->func_ref = &_ISLASTF;
    reg->AddFunc(_f_islast);

    MCFunc* _f_isfirst = new MCFunc();
    _f_isfirst->name = "IS FIRST";
    _f_isfirst->templ->data_type = "FUNC";
    _f_isfirst->templ->AddParam(_C_T_COMP,"IS",_C_T_REQ);
    _f_isfirst->templ->AddParam(_C_T_COMP,"FIRST",_C_T_OPT,_C_DC_ADD);
    _f_isfirst->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_isfirst->func_ref = &_ISLASTF;
    reg->AddFunc(_f_isfirst);

    MCFunc* _f_setf = new MCFunc();
    _f_setf->name = "SET FIRST";
    _f_setf->templ->data_type = "FUNC";
    _f_setf->templ->AddParam(_C_T_COMP,"SET",_C_T_REQ);
    _f_setf->templ->AddParam(_C_T_COMP,"FIRST",_C_T_OPT,_C_DC_ADD);
    _f_setf->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_setf->func_ref = &_SETFL;
    reg->AddFunc(_f_setf);

    MCFunc* _f_setl = new MCFunc();
    _f_setl->name = "SET LAST";
    _f_setl->templ->data_type = "FUNC";
    _f_setl->templ->AddParam(_C_T_COMP,"SET",_C_T_REQ);
    _f_setl->templ->AddParam(_C_T_COMP,"LAST",_C_T_OPT,_C_DC_ADD);
    _f_setl->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_setl->func_ref = &_SETFL;
    reg->AddFunc(_f_setl);

    MCFunc* _f_moven = new MCFunc();
    _f_moven->name = "MOVE NEXT";
    _f_moven->templ->data_type = "FUNC";
    _f_moven->templ->AddParam(_C_T_COMP,"MOVE",_C_T_REQ);
    _f_moven->templ->AddParam(_C_T_COMP,"NEXT",_C_T_OPT,_C_DC_ADD);
    _f_moven->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_moven->func_ref = &_MOVENP;
    reg->AddFunc(_f_moven);

    MCFunc* _f_movep = new MCFunc();
    _f_movep->name = "MOVE PREV";
    _f_movep->templ->data_type = "FUNC";
    _f_movep->templ->AddParam(_C_T_COMP,"MOVE",_C_T_REQ);
    _f_movep->templ->AddParam(_C_T_COMP,"PREV",_C_T_OPT,_C_DC_ADD);
    _f_movep->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_movep->func_ref = &_MOVENP;
    reg->AddFunc(_f_movep);


    MCFunc* _f_type_def = new MCFunc();
    _f_type_def->name = "TYPE DEF";
    _f_type_def->templ->data_type = "FUNC";
    _f_type_def->templ->AddParam(_C_T_COMP,"TYPE",_C_T_REQ);
    _f_type_def->templ->AddParam(_C_T_COMP,"DEF",_C_T_REQ);
    _f_type_def->templ->AddParam(_C_T_NAME,"TYPENAME",_C_T_REQ);
    _f_type_def->templ->AddParam(_C_T_COMP,"EXTENDS",_C_T_OPT);
    _f_type_def->templ->AddParam(_C_T_NAME,"EXTNAME",_C_T_OPTC);
    _f_type_def->func_ref = &_TYPE_DEF;
    reg->AddFunc(_f_type_def);


    MCFunc* _f_set = new MCFunc();
    _f_set->name = "SET";
    _f_set->templ->data_type = "FUNC";
    _f_set->templ->AddParam(_C_T_COMP,"SET",_C_T_REQ);
    _f_set->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_set->templ->AddParam(_C_T_ANY,"VARVALUE",_C_T_REQ);
    _f_set->func_ref = &_SET;
    reg->AddFunc(_f_set);

    MCFunc* _f_inc = new MCFunc();
    _f_inc->name = "INC";
    _f_inc->templ->data_type = "FUNC";
    _f_inc->templ->AddParam(_C_T_COMP,"INC",_C_T_REQ);
    _f_inc->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_inc->func_ref = &_INC;
    reg->AddFunc(_f_inc);

    MCFunc* _f_set2 = new MCFunc();
    _f_set2->name = ":=";
    _f_set2->templ->data_type = "FUNC";
    _f_set2->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_set2->templ->AddParam(_C_T_COMP,":=",_C_T_REQ);
    _f_set2->templ->AddParam(_C_T_ANY,"VARVALUE",_C_T_REQ);
    _f_set2->func_ref = &_SET;
    reg->AddFunc(_f_set2);

    MCFunc* _f_add_item = new MCFunc();
    _f_add_item->name = "ADD ITEM";
    _f_add_item->templ->data_type = "FUNC";
    _f_add_item->templ->AddParam(_C_T_COMP,"ADD",_C_T_REQ);
    _f_add_item->templ->AddParam(_C_T_COMP,"ITEM",_C_T_REQ);
    _f_add_item->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_add_item->templ->AddParam(_C_T_ANY,"ASINDEX",_C_T_OPT);
    _f_add_item->func_ref = &_ADD_ITEM;
    reg->AddFunc(_f_add_item);

    MCFunc* _f_cr_node = new MCFunc();
    _f_cr_node->name = "CREATE NODE";
    _f_cr_node->templ->data_type = "FUNC";
    _f_cr_node->templ->AddParam(_C_T_COMP,"CREATE",_C_T_REQ);
    _f_cr_node->templ->AddParam(_C_T_COMP,"NODE",_C_T_REQ);
    _f_cr_node->templ->AddParam(_C_T_NAME,"NODENAME",_C_T_REQ);
    _f_cr_node->templ->AddParam(_C_T_COMP,"IN",_C_T_REQ);
    _f_cr_node->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_cr_node->templ->AddParam(_C_T_COMP,"TYPE",_C_T_REQ);
    _f_cr_node->templ->AddParam(_C_T_NAME,"TYPENAME",_C_T_REQ);
    _f_cr_node->func_ref = &_CREATE_NODE;
    reg->AddFunc(_f_cr_node);

    MCFunc* _f_del_node = new MCFunc();
    _f_del_node->name = "DELETE INDEX";
    _f_del_node->templ->data_type = "FUNC";
    _f_del_node->templ->AddParam(_C_T_COMP,"DELETE",_C_T_REQ);
    _f_del_node->templ->AddParam(_C_T_COMP,"INDEX",_C_T_OPT,_C_DC_ADD);
    _f_del_node->templ->AddParam(_C_T_ANY,"INDEXNR",_C_T_OPTC,_C_T_NUMC);
    _f_del_node->templ->AddParam(_C_T_COMP,"NAME",_C_T_OPT,_C_DC_ADD);
    _f_del_node->templ->AddParam(_C_T_ANY,"ASNAME",_C_T_OPTC);
    _f_del_node->templ->AddParam(_C_T_COMP,"IN",_C_T_REQ);
    _f_del_node->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_del_node->func_ref = &_DELETE_NODE;
    reg->AddFunc(_f_del_node);



    MCFunc* _f_def_func = new MCFunc();
    _f_def_func->name = "DEF FUNC";
    _f_def_func->templ->data_type = "FUNC";
    _f_def_func->templ->AddParam(_C_T_COMP,"FUNC",_C_T_REQ);
    _f_def_func->templ->AddParam(_C_T_COMP,"DEF",_C_T_REQ);
    _f_def_func->templ->AddParam(_C_T_NAME,"FNAME",_C_T_REQ);
    _f_def_func->templ->AddParam(_C_T_NAME,"VALUE",_C_T_SEQ);
    _f_def_func->func_ref = &_DEF_FUNC;
    reg->AddFunc(_f_def_func);



    MCFunc* _f_call_func = new MCFunc();
    _f_call_func->name = "CALL FUNC";
    _f_call_func->templ->data_type = "FUNC";
    _f_call_func->templ->AddParam(_C_T_COMP,"CALL",_C_T_REQ);
    _f_call_func->templ->AddParam(_C_T_COMP,"FUNC",_C_T_REQ);
    _f_call_func->templ->AddParam(_C_T_NAME,"FNAME",_C_T_REQ);
    _f_call_func->templ->AddParam(_C_T_ANY,"VALUE",_C_T_SEQ);
    _f_call_func->templ->AddParam(_C_T_COMP,"OUT",_C_T_OPT);
    _f_call_func->templ->AddParam(_C_T_VAR,"REF",_C_T_SEQ);
    _f_call_func->func_ref = &_CALL_FUNC;
    reg->AddFunc(_f_call_func);
    reg->call_func = _f_call_func;

    MCFunc* _f_len = new MCFunc();
    _f_len->name = "LEN";
    _f_len->templ->data_type = "FUNC";
    _f_len->templ->AddParam(_C_T_COMP,"LEN",_C_T_REQ);
    _f_len->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_len->func_ref = &_LEN;
    reg->AddFunc(_f_len);

    MCFunc* _f_mytype = new MCFunc();
    _f_mytype->name = "MYTYPE";
    _f_mytype->templ->data_type = "FUNC";
    _f_mytype->templ->AddParam(_C_T_COMP,"MYTYPE",_C_T_REQ);
    _f_mytype->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_mytype->func_ref = &_MYTYPE;
    reg->AddFunc(_f_mytype);

    MCFunc* _f_myname = new MCFunc();
    _f_myname->name = "MYNAME";
    _f_myname->templ->data_type = "FUNC";
    _f_myname->templ->AddParam(_C_T_COMP,"MYNAME",_C_T_REQ);
    _f_myname->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_myname->func_ref = &_MYNAME;
    reg->AddFunc(_f_myname);

    MCFunc* _f_myindex = new MCFunc();
    _f_myindex->name = "MYINDEX";
    _f_myindex->templ->data_type = "FUNC";
    _f_myindex->templ->AddParam(_C_T_COMP,"MYINDEX",_C_T_REQ);
    _f_myindex->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_myindex->func_ref = &_MYINDEX;
    reg->AddFunc(_f_myindex);

    MCFunc* _f_myaindex = new MCFunc();
    _f_myaindex->name = "MYASINDEX";
    _f_myaindex->templ->data_type = "FUNC";
    _f_myaindex->templ->AddParam(_C_T_COMP,"MYASINDEX",_C_T_REQ);
    _f_myaindex->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_myaindex->func_ref = &_MYASINDEX;
    reg->AddFunc(_f_myaindex);

    MCFunc* _f_ce = new MCFunc();
    _f_ce->name = "CE";
    _f_ce->templ->data_type = "FUNC";
    _f_ce->templ->AddParam(_C_T_COMP,"CE",_C_T_REQ);
    _f_ce->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_SEQ);
    _f_ce->func_ref = &_CE;
    reg->AddFunc(_f_ce);

    MCFunc* _f_ci = new MCFunc();
    _f_ci->name = "CI";
    _f_ci->templ->data_type = "FUNC";
    _f_ci->templ->AddParam(_C_T_COMP,"CI",_C_T_REQ);
    _f_ci->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_ci->func_ref = &_CI;
    reg->AddFunc(_f_ci);

    MCFunc* _f_idx = new MCFunc();
    _f_idx->name = "IDX";
    _f_idx->templ->data_type = "FUNC";
    _f_idx->templ->AddParam(_C_T_COMP,"IDX",_C_T_REQ);
    _f_idx->templ->AddParam(_C_T_ANY,"VALUE",_C_T_REQ);
    _f_idx->func_ref = &_IDX;
    reg->AddFunc(_f_idx);

    MCFunc* _f_savetofile = new MCFunc();
    _f_savetofile->name = "SAVE TO FILE";
    _f_savetofile->templ->data_type = "FUNC";
    _f_savetofile->templ->AddParam(_C_T_COMP,"SAVE",_C_T_REQ);
    _f_savetofile->templ->AddParam(_C_T_ANY,"VALUE",_C_T_REQ);
    _f_savetofile->templ->AddParam(_C_T_COMP,"TO",_C_T_REQ);
    _f_savetofile->templ->AddParam(_C_T_COMP,"FILE",_C_T_REQ);
    _f_savetofile->templ->AddParam(_C_T_ANY,"FILENAME",_C_T_REQ);
    _f_savetofile->func_ref = &_SAVETOFILE;
    reg->AddFunc(_f_savetofile);

    MCFunc* _f_loadfromfile = new MCFunc();
    _f_loadfromfile->name = "LOAD FROM FILE";
    _f_loadfromfile->templ->data_type = "FUNC";
    _f_loadfromfile->templ->AddParam(_C_T_COMP,"LOAD",_C_T_REQ);
    _f_loadfromfile->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_loadfromfile->templ->AddParam(_C_T_COMP,"FROM",_C_T_REQ);
    _f_loadfromfile->templ->AddParam(_C_T_COMP,"FILE",_C_T_REQ);
    _f_loadfromfile->templ->AddParam(_C_T_ANY,"FILENAME",_C_T_REQ);
    _f_loadfromfile->func_ref = &_LOADFROMFILE;
    reg->AddFunc(_f_loadfromfile);

    MCFunc* _f_treeloadfromfile = new MCFunc();
    _f_treeloadfromfile->name = "TREE LOAD FROM FILE";
    _f_treeloadfromfile->templ->data_type = "FUNC";
    _f_treeloadfromfile->templ->AddParam(_C_T_COMP,"TREE",_C_T_REQ);
    _f_treeloadfromfile->templ->AddParam(_C_T_COMP,"LOAD",_C_T_REQ);
    _f_treeloadfromfile->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_treeloadfromfile->templ->AddParam(_C_T_COMP,"FROM",_C_T_REQ);
    _f_treeloadfromfile->templ->AddParam(_C_T_COMP,"FILE",_C_T_REQ);
    _f_treeloadfromfile->templ->AddParam(_C_T_ANY,"FILENAME",_C_T_REQ);
    _f_treeloadfromfile->func_ref = &_TREELOADFROMFILE;
    reg->AddFunc(_f_treeloadfromfile);

    MCFunc* _f_find = new MCFunc();
    _f_find->name = "FIND";
    _f_find->templ->data_type = "FUNC";
    _f_find->templ->AddParam(_C_T_COMP,"FIND",_C_T_REQ);
    _f_find->templ->AddParam(_C_T_COMP,"IN",_C_T_REQ);
    _f_find->templ->AddParam(_C_T_VAR,"VARNAME",_C_T_REQ);
    _f_find->templ->AddParam(_C_T_COMP,"WHERE",_C_T_REQ);
    _f_find->templ->AddParam(_C_T_EXPR,"VALUE",_C_T_REQ);
    _f_find->func_ref = &_FIND;
    reg->AddFunc(_f_find);

    /* TYPE FUNCTIONS ********************************************************************************
    *************************************************************************************************/

    MCFunc* _f_type_of = new MCFunc();
    _f_type_of->name = "TYPE OF";
    _f_type_of->func_type = _C_FT_TYPE;
    _f_type_of->templ->data_type = "FUNC";
    _f_type_of->templ->AddParam(_C_T_NAME,"NAME",_C_T_REQ);
    _f_type_of->templ->AddParam(_C_T_COMP,"TYPE",_C_T_REQ);
    _f_type_of->templ->AddParam(_C_T_COMP,"OF",_C_T_REQ);
    _f_type_of->templ->AddParam(_C_T_NAME,"TYPENAME",_C_T_REQ);
    _f_type_of->func_ref = &_TYPE_OF;
    reg->AddFunc(_f_type_of);

    MCFunc* _f_def_method = new MCFunc();
    _f_def_method->name = "DEF FUNC";
    _f_def_method->func_type = _C_FT_TYPE;
    _f_def_method->templ->data_type = "FUNC";
    _f_def_method->templ->AddParam(_C_T_COMP,"METHOD",_C_T_REQ);
    _f_def_method->templ->AddParam(_C_T_COMP,"DEF",_C_T_REQ);
    _f_def_method->templ->AddParam(_C_T_NAME,"FNAME",_C_T_REQ);
    _f_def_method->templ->AddParam(_C_T_NAME,"VALUE",_C_T_SEQ);
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
            MCRet* RET = engine->RetCreate(_C_F_TYPE_MISMATCH,"","ERROR","You can not specify item type of non-array object " + v_name,-100);
            return RET;
        }
    }
    else
    {
        if(typeof!=NULL)
        {
            MCRet* RET = engine->RetCreate(_C_F_TYPE_MISMATCH,"","ERROR","You can not specify item type of non-array object " + v_name,-100);
            return RET;
        }
    }

    if(var_type=="ARRAY" && typeof!=NULL )
    {
        if( types->FindSibling(typeof->ref_line->data,types) == NULL)
        {
            MCRet* RET = engine->RetCreate(_C_F_TYPE_NOT_FOUND,"","ERROR","Type of item not found " + typeof->ref_line->data,-100);
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
        MCRet* RET = engine->RetCreate(_C_F_VAR_EXIST,"","ERROR","Object already exists " + v_name + " : " + error_text,-100);
        return RET;

    }
    else if(res==-2)
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_NOT_FOUND,"","ERROR","Can not find all types for " + v_name+ " : " + error_text,-100);
        return RET;

    }
    if(res==-3)
    {
        MCRet* RET = engine->RetCreate(_C_F_NAME_NOT_ALLOWED,"","ERROR","Name is not allowed : " + v_name,-100);
        return RET;
    }
    return RET;
}
MCRet* _CREATE_NODE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{
    MCRet* RET = new MCRet();
    MCFParams* var = params->GetParam("VARNAME");
    MCFParams* typeof = params->GetParam("TYPENAME");
    MCFParams* name = params->GetParam("NODENAME");

    if(var->value->ref_var->data_type != "TREE")
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_MISMATCH,"","ERROR","You can not add node to non-TREE type object " + var->value->ref_var->data_type,-100);
        return RET;
    }

    std::string v_name = name->ref_line->data;
    std::string error_text = "";
    MCVar* cr_var;

    MCFParams* vtype = params->GetParam("TYPENAME");
    std::string var_type = typeof->ref_line->data;

    int res = var->value->ref_var->CreateVar(v_name,var_type,"",types,error_text,cr_var);

    if(res==-2)
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_NOT_FOUND,"","ERROR","Can not find all types for " + v_name+ " : " + error_text,-100);
        return RET;

    }
    if(res==-3)
    {
        MCRet* RET = engine->RetCreate(_C_F_NAME_NOT_ALLOWED,"","ERROR","Name is not allowed : " + v_name,-100);
        return RET;
    }



    return RET;
}
MCRet* _DELETE_NODE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{
    MCRet* RET = new MCRet();
    MCFParams* var = params->GetParam("VARNAME");

    if(var->value->ref_var->data_type != "TREE" && var->value->ref_var->data_type != "ARRAY")
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_MISMATCH,"","ERROR","You can not add/delete node/element in non-TREE/ARRAY type object " + var->value->ref_var->data_type,-100);
        return RET;
    }

    MCFParams* C_index = params->GetParam("INDEX");
    MCFParams* C_asindex = params->GetParam("NAME");

    if(C_index!=NULL && C_asindex!=NULL)
    {
        MCRet* RET = engine->RetCreate(_C_F_FUNC_PARAM_ERROR,"","ERROR","You can not delete both name and index!",-100);
        return RET;
    }

    if(C_index==NULL && C_asindex==NULL)
    {
        MCRet* RET = engine->RetCreate(_C_F_FUNC_PARAM_ERROR,"","ERROR","You must complete statement with name or index!",-100);
        return RET;
    }

    MCFParams* index = params->GetParam("INDEXNR");
    bool res = false;

    if(index != NULL)
    {
        int v_index = index->value->ret_nr;
        res = var->value->ref_var->DeleteChildIndex(v_index);
        if(!res)
        {
            MCRet* RET = engine->RetCreate(_C_F_INDEX_NOT_FOUND,"","ERROR","Can not find element or delete element index " + v_index,-100);
            return RET;

        }
    }
    else
    {
        index = params->GetParam("ASNAME");
        std::string v_index = index->value->ret_data;
        res = var->value->ref_var->DeleteChildPIndex(v_index);
        if(!res)
        {
            MCRet* RET = engine->RetCreate(_C_F_INDEX_NOT_FOUND,"","ERROR","Can not find element or delete element index " + v_index,-100);
            return RET;

        }
    }






    return RET;
}
MCRet* _SET(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* name = params->GetParam("VARNAME");
    MCFParams* var_value = params->GetParam("VARVALUE");
    if(name->value->ref_var->data_type!=MCVar::simple_type && name->value->ref_var->data_type!="TREE")
    {
        MCRet* RET = engine->RetCreate(_C_F_PROTECTED_VALUE,"","ERROR","Can not assign value for type " + name->value->ref_var->data_type + " in line [" + engine->cur_code->data +  "]",-100);
        return RET;
    }
    std::string v_value = var_value->value->ret_data;
    std::string error_text = "";
    name->value->ref_var->data = v_value;

    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
}
MCRet* _INC(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* name = params->GetParam("VARNAME");
    MCVar* obj = name->value->ref_var;

    if(obj->data_type!=MCVar::simple_type && obj->data_type!="TREE")
    {
        MCRet* RET = engine->RetCreate(_C_F_PROTECTED_VALUE,"","ERROR","Can not assign value for type " + name->value->ref_var->data_type + " in line [" + engine->cur_code->data +  "]",-100);
        return RET;
    }
    std::string v_value = obj->data;

    MCRet* RET_INT = engine->CastNumc(v_value);
    if(RET_INT->code<0)
    {
        return RET_INT;
    }
    obj->data = std::to_string(RET_INT->ret_nr+1);
    obj->data  = engine->FormatDouble(obj->data);
    delete RET_INT;
    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
}
MCRet* _IDX(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* var_value = params->GetParam("VALUE");
    MCRet* RET = engine->RetCreate(0,"#IDX"+var_value->value->ret_data,"INDEX","",0);
    return RET;
}
MCRet* _CE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    for (std::vector<MCDataNode *>::iterator it = params->children.begin() ; it != params->children.end(); ++it)
    {
        MCFParams* name = (MCFParams*)*it;
        std::string error_txt = name->value->ref_var->SetValue("");
        if(error_txt!="")
            return engine->RetCreate(_C_F_PROTECTED_VALUE,"ERROR","",error_txt  + " in line [" + engine->cur_code->data +  "]",0);

    }

    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
}
MCRet* _CI(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* name = params->GetParam("VARNAME");
    name->value->ref_var->ar_pointer = "";
    MCRet* RET = engine->RetCreate(0,"","","",0);
    return RET;
}
MCRet* _MYTYPE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* name = params->GetParam("VARNAME");
    MCRet* RET = engine->RetCreate(0,name->value->ref_var->extended_type,"","",0);
    return RET;
}
MCRet* _MYNAME(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* name = params->GetParam("VARNAME");
    MCRet* RET = engine->RetCreate(0,name->value->ref_var->var_name,"","",0);
    return RET;
}

MCRet* _MYINDEX(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* name = params->GetParam("VARNAME");
    MCRet* RET = engine->RetCreate(0,std::to_string(name->value->ref_var->num_index),"","",0);
    return RET;
}
MCRet* _MYASINDEX(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* name = params->GetParam("VARNAME");
    MCRet* RET = engine->RetCreate(0,name->value->ref_var->asoc_index,"","",0);
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
    RET->bufout = "";
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
        return engine->RetCreate(_C_F_PROTECTED_VALUE,"ERROR","",error_txt  + " in line [" + engine->cur_code->data +  "]",0);

    MCRet* RET = engine->RetCreate(0,content,"","",0);
    return RET;

}
MCRet* _TREELOADFROMFILE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* toload = params->GetParam("VARNAME");
    MCFParams* fname = params->GetParam("FILENAME");
    if(toload->value->ref_var->data_type!="TREE")
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_MISMATCH,"","ERROR","You can not load XML to non-TREE type object " + toload->value->ref_var->data_type,-100);
        return RET;
    }
    std::string filename = fname->value->ret_data;
    std::ifstream ifs(filename);
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()    ) );

    toload->value->ref_var->SetValue("ROOT");
    MCXMLEngine *eng = new MCXMLEngine();
    MCRet* RET = eng->LoadString(content,toload->value->ref_var,engine);

    delete eng;
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
    }else
    RET->stop_code = 2;
    RET->ret_type = "VALUE";
    return RET;
}
MCRet* _ELSE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{
    if(engine->last_code == 2)
    {

     MCRet* RES = engine->EvaluateLine(line,vars,types);

    if(RES != NULL)
        if(RES->code < 0 || RES->stop_code != 0)
                return RES;
    delete RES;
    }
    MCRet* RET = new MCRet();
    RET->ret_type = "VALUE";
    return RET;
}
MCRet* _WHILE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
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
        RET->stop_code =  1;
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
    for(int ic=0; ic<cycles; ic++)
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

MCRet* _SETFL(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* var_value = params->GetParam("VARNAME");
    MCVar* obj = var_value->value->ref_var;
    if(!obj->IsDynamic())
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_MISMATCH,"","ERROR","You can not move index on non-array/tree object " + obj->data_type,-100);
        return RET;
    }
    bool res = true;
    int xmove = 0;
    if(params->GetParam("LAST")!=NULL)
        xmove = 1;

    if(xmove==0)
        res = obj->SetFirst();
    else
        res =obj->SetLast();

    if(!res)
    {
        MCRet* RET = engine->RetCreate(_C_F_EMPTY_ELEM,"","ERROR","Can not set index on empty/invalid element?" + obj->data_type,-100);
        return RET;
    }

    MCRet* RET = new MCRet();
    RET->ret_type = "VALUE";
    return RET;

}
MCRet* _ISLASTF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* var_value = params->GetParam("VARNAME");
    MCVar* obj = var_value->value->ref_var;
    if(!obj->IsDynamic())
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_MISMATCH,"","ERROR","You can not move index on non-array/tree object " + obj->data_type,-100);
        return RET;
    }
    bool res = true;
    int xmove = 0;
    if(params->GetParam("LAST")!=NULL)
        xmove = 1;

    if(xmove==0)
        res = obj->IsLast();
    else
        res = obj->IsFirst();

    MCRet* RET = new MCRet();

    if(res)
    {
        RET->ret_data = "1";
    }
    else
        RET->ret_data = "0";


    RET->ret_type = "VALUE";
    return RET;

}
MCRet* _MOVENP(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* var_value = params->GetParam("VARNAME");
    MCVar* obj = var_value->value->ref_var;
    if(!obj->IsDynamic())
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_MISMATCH,"","ERROR","You can not move index on non-array/tree object " + obj->data_type,-100);
        return RET;
    }
    bool res = true;
    int xmove = 0;
    if(params->GetParam("PREV")!=NULL)
        xmove = 1;

    if(xmove==0)
        res = obj->MoveNext();
    else
        res =obj->MovePrev();

    MCRet* RET = new MCRet();

    if(res)
    {
        RET->ret_data = "1";
    }
    else
        RET->ret_data = "0";


    RET->ret_type = "VALUE";
    return RET;

}

MCRet* _FIND(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* var_value = params->GetParam("VARNAME");
    MCVar* obj = var_value->value->ref_var;
    MCFParams* node_n = params->GetParam("VALUE");

    bool was = false;
    engine->inner_cycle_counter = 0;
    for (std::vector<MCDataNode *>::iterator it = obj->children.begin() ; it != obj->children.end(); ++it)
    {


        MCVar* param =(MCVar*) *it;
        MCCodeLine * r_line = (MCCodeLine *)node_n->ref_line;
        MCRet* where = engine->RenderLine(r_line,param,types);

        if(where->code < 0 || where->stop_code != 0)
            return where;

        if(where->ret_data=="1")
        {
            engine->var_scope->FindSibling("#PTR",engine->var_scope)->refvar = param;
            engine->inner_cycle_counter ++;
            obj->ar_pointer = param->asoc_index;
            MCRet* RES = engine->EvaluateLine(line,vars,types);
            engine->var_scope->FindSibling("#PTR",engine->var_scope)->refvar = NULL;
            if(RES == NULL)
                continue;

            if(RES->code < 0 || RES->stop_code != 0)
                return RES;

            delete RES;

        }



    }

    MCRet* RET = new MCRet();
    if(!was)
        RET->stop_code = 2;
    RET->ret_type = "VALUE";
    return RET;

}
MCRet* _LOOP(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params)
{

    MCFParams* var_value = params->GetParam("VAR");
    MCVar* obj = var_value->value->ref_var;
    std::string onlyname = "";
    MCFParams* node_n = params->GetParam("NODENAME");
    if(node_n!=NULL)
        onlyname = node_n->ref_line->data;

    engine->inner_cycle_counter = 0;
    for (std::vector<MCDataNode *>::iterator it = obj->children.begin() ; it != obj->children.end(); ++it)
    {

        MCVar* param =(MCVar*) *it;

        if(onlyname!="" && onlyname!=param->var_name)
            continue;
        engine->var_scope->FindSibling("#PTR",engine->var_scope)->refvar = param;
        engine->inner_cycle_counter ++;
        obj->ar_pointer = param->asoc_index;
        MCRet* RES = engine->EvaluateLine(line,vars,types);
        engine->var_scope->FindSibling("#PTR",engine->var_scope)->refvar = NULL;
        if(RES == NULL)
            continue;

        if(RES->code < 0 || RES->stop_code != 0)
            return RES;

        delete RES;



    }

    MCRet* RET = new MCRet();
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
        MCRet* RET = engine->RetCreate(_C_F_PROTECTED_VALUE,"","ERROR","Can not assign value for type " + var_counter->data_type + " in line [" + engine->cur_code->data +  "]",-100);
        return RET;
    }
    if(from<to)
    {
        engine->inner_cycle_counter = 0;
        for(int ic=from; ic<to+1; ic++)
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
    else
    {
        engine->inner_cycle_counter = 0;
        for(int ic=from; ic>to-1; ic--)
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

        RET->ret_data  = engine->FormatDouble(RET->ret_data);

        RET->ret_type = "VALUE";
        return RET;
    }

    MCFParams* var_value2 = params->GetParam("VALUE2");
    double val1 = var_value1->value->ret_nr;
    double val2 = var_value2->value->ret_nr;

    if(func->name == "+")
    {
        RET->ret_data = std::to_string(val1+val2);

    }
    else if(func->name  == "-")
    {
        RET->ret_data = std::to_string(val1-val2);
    }
    else if(func->name  == "/")
    {
        RET->ret_data = std::to_string(val1/val2);
    }
    else if(func->name  == "*")
    {
        RET->ret_data = std::to_string(val1*val2);
    }

    RET->ret_data  = engine->FormatDouble(RET->ret_data);
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
    }
    else if(func->name == "EMPTY")
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
    }
    else if(func->name  == "OR")
    {


        if(v_value1=="1" || v_value2=="1")
            RET->ret_data = "1";
        else
            RET->ret_data = "0";

        RET->ret_type = "VALUE";
        return RET;
    }
    else if(func->name  == "=")
    {


        if(v_value1==v_value2)
            RET->ret_data = "1";
        else
            RET->ret_data = "0";

        RET->ret_type = "VALUE";
        return RET;
    }
    else if(func->name  == "<>")
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
    }
    else if(func->name  == ">")
    {
        if(val1>val2)
            RET->ret_data = "1";
        else
            RET->ret_data = "0";
    }
    else if(func->name  == ">=")
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
        MCRet* RET = engine->RetCreate(_C_F_TYPE_EXIST,"","ERROR","Type already exists " + v_name+ " : " + error_text,-100);
        return RET;

    }
    else if(res==-2)
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_NOT_FOUND,"","ERROR","Can not find all types for " + v_name+ " : " + error_text,-100);
        return RET;

    }
    if(res==-3)
    {
        MCRet* RET = engine->RetCreate(_C_F_NAME_NOT_ALLOWED,"","ERROR","Name is not allowed " + v_name+ " : " + error_text,-100);
        return RET;

    }
    MCRet* RES = engine->EvaluateLine(line,vars,cr_var,_C_FT_TYPE);
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
        MCRet* RET = engine->RetCreate(_C_F_GLOBAL_TYPE,"","ERROR","Components could be defined only in types",-100);
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
        MCRet* RET = engine->RetCreate(_C_F_TYPE_EXIST,"","ERROR","Type already exists " + v_name+ " : " + error_text,-100);
        return RET;

    }
    else if(res==-2)
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_NOT_FOUND,"","ERROR","Can not find all types for " + v_name+ " : " + error_text,-100);
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
        MCRet* RET = engine->RetCreate(_C_F_NON_ARRAY,"","ERROR","You can not use as array object " + vname->value->ref_var->var_name,-100);
        return RET;
    }

    std::string error_text = "";
    MCVar* cr_var;
    int res = vname->value->ref_var->CreateArrayItem("","",engine->type_scope,error_text,cr_var);

    if(res==-1)
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_EXIST,"","ERROR","index already exists " + index+ " : " + error_text,-100);
        return RET;

    }
    else if(res==-2)
    {
        MCRet* RET = engine->RetCreate(_C_F_TYPE_NOT_FOUND,"","ERROR","Can not find all types for " + vname->value->ref_var->var_name+ " : " + error_text,-100);
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
        MCRet* RET = engine->RetCreate(_C_F_FUNC_EXIST,"","ERROR","Function already exists " + fname->ref_line->data,-100);
        return RET;
    }

    MCVar* Func = NULL;
    std::string error_txt="";
    int res = engine->func_scope->CreateVar(fname->ref_line->data,"FUNC","",types,error_txt,Func);

    if(res!=0)
    {
        MCRet* RET = engine->RetCreate(_C_F_NAME_NOT_ALLOWED,"","ERROR","Can not create object : " + fname->ref_line->data,-100);
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
                    MCRet* RET = engine->RetCreate(_C_F_INCOMPLETE_DEF,"","ERROR","Incomplete definition of parameter " + pfunc->var_name + " : " + error_txt,-100);
                    return RET;
                }
                MCFParams* next_param =(MCFParams*) *it;

                if(!pfunc->is_ref &&  next_param->ref_line->data!=MCVar::simple_type )
                {
                    MCRet* RET = engine->RetCreate(_C_F_INCOMPLETE_DEF,"","ERROR","Non-VAR types allowed only as references, use OUT keyword " + pfunc->var_name + " : " + error_txt,-100);
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
            MCRet* RET = engine->RetCreate(_C_F_VAR_EXIST,"","ERROR","Parameter already exist " + param->ref_line->data + " : " + error_txt,-100);
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
        MCRet* RET = engine->RetCreate(_C_F_GLOBAL_TYPE,"","ERROR","Components could be defined only in types",-100);
        return RET;
    }

    MCFParams* fname = params->GetParam("FNAME");

    if(types->FindSibling(fname->ref_line->data,types)!=NULL)
    {
        MCRet* RET = engine->RetCreate(_C_F_FUNC_EXIST,"","ERROR","Function already exists " + fname->ref_line->data,-100);
        return RET;
    }

    MCVar* Func = NULL;
    std::string error_txt="";
    int res = types->CreateVar(fname->ref_line->data,"FUNC","",types,error_txt,Func);

    if(res!=0)
    {
        MCRet* RET = engine->RetCreate(_C_F_NAME_NOT_ALLOWED,"","ERROR","Can not create object : " + fname->ref_line->data,-100);
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
                    MCRet* RET = engine->RetCreate(_C_F_INCOMPLETE_DEF,"","ERROR","Incomplete definition of parameter " + pfunc->var_name + " : " + error_txt,-100);
                    //delete Func;
                    return RET;
                }
                MCFParams* next_param =(MCFParams*) *it;
                if(!pfunc->is_ref &&  next_param->ref_line->data!=MCVar::simple_type )
                {
                    MCRet* RET = engine->RetCreate(_C_F_INCOMPLETE_DEF,"","ERROR","Non-VAR types allowed only as references, use OUT keyword " + pfunc->var_name + " : " + error_txt,-100);
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
            MCRet* RET = engine->RetCreate(_C_F_VAR_EXIST,"","ERROR","Parameter already exist " + param->ref_line->data + " : " + error_txt,-100);
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

    }
    else
    {
        Func = engine->func_scope->FindSibling(f_name->ref_line->data,engine->func_scope);
    }

    if(Func==NULL)
    {
        MCRet* RET = engine->RetCreate(_C_F_FUNC_EXIST,"","ERROR","Function does not exists " + fname,-100);
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
            MCRet* RET = engine->RetCreate(_C_F_FUNC_PARAM_ERROR,"","ERROR","Unknown parameter " + param->ref_line->data + " in " + fname,-100);
            return RET;
        }

        MCVar* pfunc = (MCVar*) Func->children.at(var_cc-1);
        if( pfunc->is_ref && param->value->ref_var == NULL)
        {
            MCRet* RET = engine->RetCreate(_C_F_FUNC_PARAM_ERROR,"","ERROR","OUT parameter needs LVALUE " + param->ref_line->data + " in " + fname,-100);
            return RET;
        }
        if(pfunc->data_class!=MCVar::simple_type && param->value->ref_var == NULL )
        {
            MCRet* RET = engine->RetCreate(_C_F_TYPE_MISMATCH,"","ERROR","Parameter has incorrect type VALUE/VAR when " + pfunc->data_class + " needed in  " + fname,-100);
            return RET;
        }
        if(param->value->ref_var !=NULL  && pfunc->data_class != param->value->ref_var->data_type )
        {
            MCRet* RET = engine->RetCreate(_C_F_TYPE_MISMATCH,"","ERROR","Parameter has incorrect type " + param->value->ref_var->data_type + " when " + pfunc->data_class + " needed in  " + fname,-100);
            return RET;
        }

    }

    if(var_cc != var_c)
    {
        MCRet* RET = engine->RetCreate(_C_F_FUNC_PARAM_ERROR,"","ERROR","Not all parameters are provided (" + std::to_string(var_cc)  + ") to " + fname,-100);
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
