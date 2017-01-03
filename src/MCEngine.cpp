#include "MCEngine.h"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include "MCFParams.h"
#include "MCFunc.h"
#include "MCVar.h"

MCEngine::MCEngine()
{
    //ctor
    code = new MCCodeLine();
    code->data = "";
    code->data_type = "PROGRAM";
    fregister = new MCFuncRegister();
    clib = new MCFuncLibCore();
    clib->RegFunc(fregister);

    //SCOPES
    var_scope =  new MCVar();
    type_scope =  new MCVar();
    func_scope =  new MCVar();

    var_scope->data_type = "[GLOBAL]";
    var_scope->data_namespace = "VARS";
    var_scope->data = "[GLOBAL]";
    type_scope->data_type = "[GLOBAL]";
    type_scope->data_namespace = "TYPES";
    type_scope->data = "[GLOBAL]";
    MCVar *ptr = NULL;
    std::string er_txt = "";
    var_scope->CreateVar("PTR","REF","",type_scope,er_txt,ptr);
    ptr->var_name = "#PTR";
    ptr->is_system = true;
}
MCRet* MCEngine::CastNumc(std::string value)
{
    try
    {
        double i = boost::lexical_cast<double>(value);
        MCRet* RET = RetCreate(0,"","NUMC","",0);
        RET->ret_nr = i;
        return RET;
    }
    catch(...)
    {

        MCRet* RET = RetCreate(_C_F_CAST_ERROR,"","ERROR","Can not cast to int value : " + value,-100);
        return RET;
    }
}


MCRet* MCEngine::Run()
{
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

    start_time = std::chrono::high_resolution_clock::now();

    MCRet* RET = EvaluateLine(code,var_scope,type_scope);

    end_time = std::chrono::high_resolution_clock::now();
    auto elapsed = end_time - start_time;
    exec_time =  std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    last_return = RET;

    return RET;
}

MCRet* MCEngine::EvaluateLine(MCCodeLine * line, MCVar* xvar_scope, MCVar* xtype_scope,int func_type )
{
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;

    for (std::vector<MCDataNode *>::iterator it = line->children.begin() ; it != line->children.end(); ++it)
    {

        MCCodeLine * line=(MCCodeLine*) *it;

        if(line->commented==true)
            continue;

        if(check_exec_time)
        {
            start_time = std::chrono::high_resolution_clock::now();
            line->start_m = start_time;
            line->executed_count ++ ;
        }

        cur_code = line;

        MCRet* ret = RenderLine(line,xvar_scope,xtype_scope,func_type);

        if(ret!= NULL)
        {
            if(ret->bufout!="")
            {
                out_buffer = out_buffer + ret->bufout;
                ret->bufout = "";
            }

            if(ret->stop_code!=0)
            {
                if(check_exec_time)
                {
                    end_time = std::chrono::high_resolution_clock::now();
                    line->end_m =end_time;
                    auto elapsed = end_time - start_time;
                    line->exec_time = line->exec_time + std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
                }
                if(ret->stop_code==1)
                {
                    --it;
                    continue;
                }
                return ret;
            }

            delete ret;
        }

        if(check_exec_time)
        {
            end_time = std::chrono::high_resolution_clock::now();
            line->end_m =end_time;
            auto elapsed = end_time - start_time;
            line->exec_time = line->exec_time + std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
        }

    }
    return RetCreate(0,"","","",0);
}

std::string MCEngine::FormatDouble(std::string dvalue)
{
     dvalue.erase ( dvalue.find_last_not_of('0') + 1, std::string::npos );

    if(dvalue[dvalue.length()-1]=='.')
        dvalue = dvalue.erase(dvalue.length()-1,1);
    return dvalue;
}

bool MCEngine::is_number(const std::string& s)
{
    try
    {
        double x = boost::lexical_cast<double>(s); // double could be anything with >> operator.
        return true;
    }
    catch(...)
    {
        return false;
    }
}
MCRet* MCEngine::RetCreate(int pcode,std::string pdata,std::string ptype,std::string pbufout,int pstop_code)
{
    MCRet* ret = new MCRet();
    ret->code = pcode;
    ret->ret_data = pdata;
    ret->ret_type = ptype;
    ret->bufout = pbufout;
    ret->stop_code = pstop_code;
    if(pcode<0)
    {
        std::string ref_cont = FindLineContent(cur_code->line_id );
        if(ref_cont!="")
            ret->bufout = "\n\r [ERROR!]" + ret->bufout + " refer to line " + std::to_string(cur_code->line_id) + " /" + ref_cont +"/" ;
        else
            ret->bufout = "\n\r [ERROR!]" + ret->bufout + " refer to unknown line " ;
    }
    return ret;
}

MCRet* MCEngine::SubExpressionRender(MCCodeLine * line,MCVar* xvar_scope,MCVar* xtype_scope)
{
    std::string in_data = line->data;

    for (std::vector<MCDataNode *>::iterator it = line->children.begin() ; it != line->children.end(); ++it)
    {
        MCCodeLine * subexpr=(MCCodeLine*) *it;

        if(subexpr->e_type==_C_T_SUBEXPR)
        {
            MCRet* new_ret = RenderLine(subexpr,xvar_scope,xtype_scope);
            if(new_ret->code < 0)
            {
                return new_ret;
            }
            boost::replace_all(in_data, subexpr->formal_type, "[" + new_ret->ret_data + "]");

        }
    }

    return RetCreate(0,in_data,"NAME","",0);
}

MCRet* MCEngine::RenderLine(MCCodeLine * line,MCVar* xvar_scope,MCVar* xtype_scope,int func_type)
{

    //if(line->data_type=="EXPR")
    //    return RenderLine(line,xvar_scope,xtype_scope,func_type);

    int in_params = line->expressions.size();
    int cy_params = 0;
    int detect_reqnr = 0;
    int func_i = -1;
    bool detected = false;
    bool optc_params_ommit = false;
    int optc_params_was = 0;

    MCCodeLine * after_code = NULL; //contains only refs

    if(in_params == 0)
    {
        if(line==NULL || line->data=="")
        {
            MCRet* RET = RetCreate(_C_F_EMPTY_ELEM,"","ERROR","Empty line detected (internal error) ",-100);
            return RET;
        }

        in_params = 1;
        MCCodeLine* auto_param = new MCCodeLine();
        auto_param->data = line->data;
        auto_param->e_type = _C_T_COMP;
        auto_param->line_id = line->line_id;
        line->expressions.push_back(auto_param);
    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if(in_params == 1)
    {

        std::string error_txt = "";
        MCVar* f_var = NULL;
        int er_type = 0;

         MCCodeLine* v_param = (MCCodeLine*) line->expressions.at(0);

        if(line->e_type == _C_T_NUMC || line->e_type == _C_T_STR)
            return RetCreate(0,v_param->data,"VALUE","",0);


        MCRet* RET  = SubExpressionRender(line,xvar_scope,xtype_scope);

        if(RET->code < 0)
        {
            return RET;
        }

        v_param->data = RET->ret_data;
        delete RET;

        if(is_number(v_param->data))
        {
            MCRet* RET = RetCreate(0,v_param->data,"VALUE","",0);
            return RET;
        }
        if(v_param->data == "#I")
        {
            MCRet* RET = RetCreate(0,v_param->data,"VALUE","",0);
            return RET;
        }
        if(boost::starts_with(v_param->data ,"#IDX"))
        {

            MCRet* RET = RetCreate(0,v_param->data,"INDEX","",0);
            return RET;
        }
        if(v_param->data == "#C")
        {
            MCRet* RET = RetCreate(0,std::to_string(inner_cycle_counter),"VALUE","",0);
            return RET;
        }
        if(line->data == "EOL")
        {
            MCRet* RET = RetCreate(0,"\n\r","VALUE","",0);
            return RET;
        }


        f_var = xvar_scope->FindVar(v_param->data,xvar_scope,error_txt,er_type);



        if(f_var!=NULL)
        {
            MCRet* RET = RetCreate(0,f_var->data,"VAR","",0);
            RET->ref_var = f_var;
            return RET;

        }
        else
        {
            if(er_type==-2)
            {
                MCRet* RET = RetCreate(_C_F_NON_ARRAY,"","ERROR","Array usage of non-array object : " + error_txt,-100);
                return RET;
            }
            else if (er_type==-3)
            {
                MCRet* RET = RetCreate(_C_F_INVALID_INDEX,"","ERROR","Invalid index/var  : " +  error_txt,-100);
                return RET;
            }
            else if (er_type==-4)
            {
                MCRet* RET = RetCreate(_C_F_INVALID_INDEX,"","ERROR","Invalid node   : " +  error_txt,-100);
                return RET;
            }
            else if (er_type==-5)
            {
                MCRet* RET = RetCreate(_C_F_INVALID_INDEX,"","ERROR","Invalid ref   : " +  error_txt,-100);
                return RET;
            }
        }

    }

    if(in_params < 3)
    {

        bool ismethod = false;
        MCCodeLine* v_param = (MCCodeLine*) line->expressions.at(0);
        MCVar* F_exists = func_scope->FindSibling(v_param->data,func_scope);

        if(F_exists==NULL)
        {
            std::string er_text = "";
            int er_int = 0;
            F_exists = var_scope->FindVar(v_param->data,var_scope,er_text,er_int);
            if(F_exists!=NULL && F_exists->data_type=="FUNC")
            {
                ismethod = true;

            }
            else
                F_exists = NULL;

        }

        if(F_exists!=NULL)
        {
            //FOUND
            MCFParams* data_params = new  MCFParams();
            MCFParams* fname_p = NULL;
            MCCodeLine* v_fparams = NULL;
            if(line->expressions.size()>1)
            {
                v_fparams = (MCCodeLine*) line->expressions.at(1);
            }

            fname_p = data_params->PutParam("FNAME",v_param,NULL);

            if(ismethod == true)
            {
                //fname_p->ref_line->data = F_exists->data;
                fname_p->ref_line->data_type = "METHOD";
            }

            if(v_fparams!=NULL)
                for (std::vector<MCDataNode*>::iterator it = v_fparams->expressions.begin() ; it != v_fparams->expressions.end(); ++it)
                {
                    MCCodeLine* callparam =( MCCodeLine* ) *it;

                    MCDataNode* newparam = new MCFParams();

                    MCFParams* cr_param = data_params->PutParam("VALUE",newparam,newparam,true);

                    if(callparam->e_type==_C_T_STR)
                    {
                        cr_param->value = RetCreate(0,callparam->data,"VALUE","",0);

                    }
                    else
                    {
                        MCRet* RET = RenderLine(callparam,xvar_scope,xtype_scope,func_type);
                        if(RET->code < 0)
                        {
                            delete data_params;
                            return RET;
                        }
                        cr_param->value = RET;
                    }




                }

            MCRet* RET = fregister->call_func->func_ref(this,line,xvar_scope,xtype_scope,NULL,data_params);

            delete data_params;
            return RET;
        }
    }
    line->fselect_tries = 0;
    int last_detected = 0;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GLOBAL FUNCTIONS CALL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////


    for (std::vector<MCFunc*>::iterator it = fregister->reg_funcs.begin() ; it != fregister->reg_funcs.end(); ++it)
    {
        MCFunc* func = *it;
        if(func_type!=func->func_type)
            continue;

        cy_params = 0;
        detect_reqnr = 0;
        MCCodeLine * last_param = NULL;
        MCFParams* data_params = new  MCFParams();
        optc_params_ommit = false;
        optc_params_was = 0;
        bool try_func = false;


        //CHECK
        if(line->cached_f==-1)
        {
            for (std::vector<MCDataNode *>::iterator it = func->templ->expressions.begin() ; it != func->templ->expressions.end(); ++it)
            {

                MCDataNode * f_param = *it;
                cy_params++;
                if(cy_params > in_params)
                    break;
                MCDataNode * v_param = line->expressions.at(cy_params-1);
                if(f_param->e_type == v_param->e_type && f_param->e_type==_C_T_COMP && f_param->f_type==_C_T_REQ)
                {
                    if(f_param->data == v_param->data)
                    {
                        try_func = true;
                    }
                    else
                    {
                        try_func = false;
                        break;
                    }



                }

            }

            if(!try_func)
                continue;

            line->fselect_tries ++;
        }
        else
        {
            /////////////////////////////CACHED FOUND FUNCTION
            it = fregister->reg_funcs.begin() + line->cached_f;
            func = *it;
        }

        cy_params = 0;
        last_detected = 0;




        for (std::vector<MCDataNode *>::iterator it = func->templ->expressions.begin() ; it != func->templ->expressions.end(); ++it)
        {


            MCDataNode * f_param = *it;
            //IF OMITIING OPTIONAL PARAMETERS
            if(optc_params_ommit == true)
            {
                if(f_param->f_type == _C_T_OPTC)
                {

                    MCDataNode * v_param = line->expressions.at(cy_params-1);

                    if ((it != func->templ->expressions.end()) && (next(it) == func->templ->expressions.end()))
                    {

                        MCRet* RET = RetCreate(_C_F_UNKNOWN_ELEM,"","ERROR","Unknown parameter " + v_param->data + " for function "+func->name,-100);
                        return RET;

                    }

                    //cy_params--;
                    //last_detected--;
                    continue;
                }
                else
                    cy_params--;


            }

            optc_params_ommit = false;
            last_detected++;
            cy_params++;

            if(f_param->f_type==_C_T_SEQ)
            {
                std::string stop_templ = "";

                MCDataNode * next_f_param = NULL;
                ++it;

                if(it != func->templ->expressions.end())
                {
                    next_f_param = *it;
                }

                bool cnt_seq = false;

                while(cy_params <= in_params)
                {


                    MCDataNode * v_param = line->expressions.at(cy_params-1);
                    if(next_f_param !=NULL && v_param->e_type == _C_T_COMP && v_param->data == next_f_param->data)
                    {
                        cnt_seq = true;
                        break;
                    }

                    data_params->PutParam(f_param->data,v_param,f_param);
                    cy_params++;
                    last_detected++;

                }


                if(cnt_seq)
                    continue;


                cy_params--;
                break;
            }


            if(f_param->f_type==_C_T_CSQ)
            {
                if(detect_reqnr == 0)
                {

                    break;
                }
                bool ind = false;
                MCCodeLine * v_param = (MCCodeLine *) line->expressions.at(cy_params-1);

                if(cy_params+1<=in_params && func->calc_order == 1 && func->name != "N")
                {



                    MCCodeLine * next_expres = new MCCodeLine();
                    MCCodeLine * independent_nodes = new MCCodeLine();
                    std::string expr_data = "";
                    int iccter = 0;

                    while(cy_params <= in_params)
                    {
                        MCCodeLine * x_param = (MCCodeLine *) line->expressions.at(cy_params-1);

                        if(func->name == "-")
                        {
                            MCCodeLine * x_param1 = new MCCodeLine();
                            x_param1->e_type = _C_T_COMP;
                            x_param1->data = "-";
                            next_expres->expressions.push_back(x_param1);
                            func = fregister->pos_func;
                            independent_nodes->children.push_back(x_param1);
                        }
                        next_expres->expressions.push_back(x_param);
                        cy_params++;
                        last_detected++;
                    }

                    MCRet* new_ret = RenderLine(next_expres,xvar_scope,xtype_scope);
                    delete independent_nodes;
                    if(new_ret->code < 0)
                        return new_ret;

                    v_param = new MCCodeLine();
                    v_param->data = new_ret->ret_data;
                    v_param->e_type = _C_T_COMP;
                    //ind = true;

                }


                data_params->PutParam(f_param->data,v_param,f_param);

                cy_params++;
                last_detected++;

                if(cy_params <= in_params)
                    after_code = new MCCodeLine();

                while(cy_params <= in_params)
                {

                    MCCodeLine * x_param = (MCCodeLine *) line->expressions.at(cy_params-1);
                    after_code->expressions.push_back(x_param);
                    cy_params++;
                    last_detected++;

                }

                break;

            }

            if(cy_params > in_params)
            {
                if(detect_reqnr == 0)
                {
                    break;
                }

                if(f_param->f_type == _C_T_OPTC && optc_params_was == 0)
                {
                    optc_params_was = 1;
                }
                else
                    optc_params_was = 3;

                if(f_param->f_type == _C_T_REQ || optc_params_was == 1)
                {

                    MCRet* RET = RetCreate(_C_NO_REQ_PARAM,"","ERROR","No required parameter for function "+func->name + " named " + f_param->data,-100);
                    return RET;
                }

                continue;
            }


            MCDataNode * v_param = line->expressions.at(cy_params-1);



            if(f_param->e_type == v_param->e_type || f_param->e_type == _C_T_ANY ||
                    f_param->e_type == _C_T_VAR || f_param->e_type == _C_T_NAME)
            {
                /*NAME*******************************************************************/

                if(f_param->e_type == _C_T_NAME || f_param->e_type == _C_T_VAR)
                    if(v_param->e_type != _C_T_COMP)
                    {
                        break;

                    }
                    else
                    {
                        data_params->PutParam(f_param->data,v_param,f_param);
                        continue;
                    }

                /*COMP*******************************************************************/

                if(f_param->e_type==_C_T_COMP)
                {

                    if(f_param->data != v_param->data)
                    {

                        if(f_param->f_type == _C_T_REQ  || f_param->f_type == _C_T_OPTC)
                        {
                            break;

                        }
                        else
                        {

                            optc_params_ommit = true;
                            continue;
                        }

                    }

                    if(f_param->dc_type == _C_DC_ADD)
                        data_params->PutParam(f_param->data,v_param,f_param);

                    if(f_param->f_type == _C_T_REQ)
                        detect_reqnr++;

                    continue;
                }


                data_params->PutParam(f_param->data,v_param,f_param);
                continue;

            }
            else
            {
                cy_params -- ;
                continue;
            }
        }



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DETECTED FUNCTION CALL
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if(detect_reqnr==func->templ->req_count || line->cached_f != -1)
        {


            int c_expr = line->expressions.size();
            if(c_expr > last_detected)
            {
                std::string elms = "";
                cy_params++;
                while(cy_params <= line->expressions.size())
                {
                    MCDataNode * v_param = line->expressions.at(cy_params-1);
                    elms = elms + " '" + v_param->data + "' ";
                    cy_params++;
                }

                MCRet* RET = RetCreate(_C_F_UNKNOWN_ELEM_END,"","ERROR","Unknown elements " + elms + " in the end of "+func->name + " in line [" + line->data + "]",-100);
                return RET;
            }


            line->cached_f = it - fregister->reg_funcs.begin();


            // FILLLING PARAMETERS
            for (std::vector<MCDataNode*>::iterator it = data_params->children.begin() ; it != data_params->children.end(); ++it)
            {
                MCFParams* x_param =(MCFParams*) *it;
                if(x_param->ref_vline->e_type == _C_T_NAME || x_param->ref_vline->dc_type == _C_DC_ADD  || x_param->is_unvalued == true)
                    continue;

                if(x_param->ref_line->e_type == _C_T_EXPR || x_param->ref_line->e_type == _C_T_COMP)
                {

                    MCRet* RET = RenderLine((MCCodeLine*)x_param->ref_line,xvar_scope,xtype_scope);

                    if(RET->code < 0)
                    {
                        delete data_params;
                        return RET;
                    }
                    x_param->value = RET;

                }
                else if(x_param->ref_line->e_type == _C_T_STR || x_param->ref_line->e_type == _C_T_NUMC  )
                    x_param->value = RetCreate(0,x_param->ref_line->data,"VALUE","",0);


                if(x_param->ref_vline->e_type == _C_T_VAR && x_param->value->ref_var == NULL)
                {
                    MCRet* RET = RetCreate(_C_F_LVALUE_REQ,"","ERROR","LVALUE required in place of "+x_param->ref_vline->data,-100);
                    delete data_params;
                    return RET;
                }




                if(x_param->ref_vline->dc_type == _C_T_NUMC)
                {
                    if(x_param->ref_line->e_type != _C_T_NUMC)
                    {
                        MCRet* RET_INT = CastNumc(x_param->value->ret_data);
                        if(RET_INT->code<0)
                        {
                            delete data_params;
                            return RET_INT;
                        }
                        x_param->value->ret_nr = RET_INT->ret_nr;
                        delete RET_INT;
                    }else
                        x_param->value->ret_nr = x_param->ref_line->num_value;



                }

            }


            //CALL FUNCTION
            MCRet* RET =  func->func_ref(this,line,xvar_scope,xtype_scope,func,data_params);
            delete data_params;

            //CALLING FUNCTIONS OF NON 0 PRIORITY
            if(after_code!=NULL)
            {
                MCDataNode * v_param = new MCDataNode();
                v_param->data = RET->ret_data;
                v_param->e_type = _C_T_COMP;
                delete RET;

                after_code->expressions.insert(after_code->expressions.begin(),v_param);
                MCRet* new_ret = RenderLine(after_code,xvar_scope,xtype_scope);

                delete v_param;
                return new_ret;
            }

            return RET;
        }

        delete data_params;
    }


    return RetCreate(_C_F_NOTFOUND,"","ERROR","Unknown statement  "+line->data + " in [" + cur_code->data + "]",-100);

}
bool MCEngine::ends_with(std::string const & value, std::string const & ending)
{
    if (ending.size() > value.size()) return false;
    return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

int MCEngine::LoadString(std::string data)
{
    char cur;
    std::string line = "";
    std::vector<std::string> lines;

    int li = 0;
    boost::split(lines,data,boost::is_any_of("\n"));
    //std::string  cline= "";

    for (std::vector<std::string>::iterator it = lines.begin() ; it != lines.end(); ++it)
    {
        li = (it - lines.begin()) + 1;

        std::string data = *it;
        //std::cout << std::endl << "Line: " << li << ")" << data;
        boost::trim(data);
        while(ends_with(data,"/&") && it != lines.end())
        {
            ++it;
            li++;
            std::string next_data = *it;
            data = data.substr(0, data.size()-2) + next_data;

        }
        if(data.length()>0)
            for(int ci = 0; ci < data.length(); ci++)
            {
                cur = data[ci];
                if( cur=='\n' || cur=='\r' )
                    continue;

                if(cur==';')
                {
                    boost::trim(line);
                    if(line.length()!=0)
                    {
                        MCTextLine * mtline = new MCTextLine();
                        mtline->text = line;
                        mtline->line_nr = li;
                        mtline->full_line = data;
                        loaded_lines.push_back(mtline);
                        //std::cout << std::endl << li << "Line: " << data;
                    }
                    line = "";
                    continue;
                }
                else if(cur=='{')
                {
                    boost::trim(line);
                    if(line.length()!=0)
                    {
                        MCTextLine * mtline = new MCTextLine();
                        mtline->text = line;
                        mtline->line_nr = li;
                        mtline->full_line = data;
                        loaded_lines.push_back(mtline);
                        //std::cout << std::endl << li << "Line: " << data;
                    }
                    MCTextLine * mtline = new MCTextLine();
                    mtline->text = "BEGIN";
                    mtline->line_nr = li;
                    mtline->full_line = data;
                    loaded_lines.push_back(mtline);
                    //std::cout << std::endl << li << "Line: {" << data;
                    line = "";
                    continue;
                }
                if(cur=='}')
                {
                    boost::trim(line);
                    if(line.length()!=0)
                    {
                        MCTextLine * mtline = new MCTextLine();
                        mtline->text = line;
                        mtline->line_nr = li;
                        mtline->full_line = data;
                        loaded_lines.push_back(mtline);
                        //std::cout << std::endl << li << "Line: }" << data;
                    }
                    MCTextLine * mtline = new MCTextLine();
                    mtline->text = "END";
                    mtline->line_nr = li;
                    mtline->full_line = data;
                    loaded_lines.push_back(mtline);
                    //std::cout << std::endl << li << "Line: " << data;
                    line = "";
                    continue;
                }
                line = line + cur;

            }

    }

    if(line!="")
    {
        return -6;
    }



    line = "";
    MCCodeLine *cursor = code;
    MCCodeLine *new_line = code;
    int rescode = 0;


    for (std::vector<MCTextLine *>::iterator it = loaded_lines.begin() ; it != loaded_lines.end(); ++it)
    {
        MCTextLine * cur_line = *it;

        if(cur_line->text=="BEGIN" )
        {
            if(new_line == NULL)
                return -4;
            cursor = new_line;
            continue;

        }
        else if (cur_line->text=="END")
        {
            if(cursor->parent == NULL)
                return -5;
            cursor  = (MCCodeLine *) cursor->parent;
            continue;
        }

        new_line = new MCCodeLine();
        cursor->AddChild(new_line);
        rescode = LineToCode(new_line,cur_line);
        if(rescode!=0)
            return rescode;
    }

    return 0;
}
void MCEngine::PrintLines(MCCodeLine * xcode,int lev )
{

    std::string tabs = "";
    for(int ci = 0; ci < lev; ci++)
        tabs = tabs  +  " ";

    std::cout  << std::endl;

    for (std::vector<MCDataNode *>::iterator it = xcode->children.begin() ; it != xcode->children.end(); ++it)
    {
        MCCodeLine * line= (MCCodeLine *)*it;
        std::cout << tabs << line->data << " ms " << line->exec_time << " counter " << line->executed_count << " " << "tries to detect " << line->fselect_tries << std::endl;
        PrintLines(line,lev+1);

    }



}
void MCEngine::PrintCode(MCCodeLine * xcode,int lev )
{

    std::string tabs = "";
    for(int ci = 0; ci < lev; ci++)
        tabs = tabs  +  " ";

    std::cout  << std::endl;
    std::cout  << tabs <<  xcode->data_type << ":"  << xcode->data << std::endl;
    std::cout  << tabs << "{" << std::endl;



    for (std::vector<MCDataNode *>::iterator it = xcode->expressions.begin() ; it != xcode->expressions.end(); ++it)
    {
        MCCodeLine * line= (MCCodeLine *)*it;
        std::cout << tabs << line->data_type << ":" << line->data << std::endl;

        std::cout << tabs << "["  << std::endl ;


        PrintCode(line,lev+1);
        std::cout << tabs << "]" << std::endl ;
    }

    for (std::vector<MCDataNode *>::iterator it = xcode->children.begin() ; it != xcode->children.end(); ++it)
    {
        MCCodeLine * line= (MCCodeLine *)*it;
        PrintCode(line,lev+1);

    }


    std::cout << tabs << "}" << std::endl ;
}
int MCEngine::LineToCode(MCCodeLine * line, MCTextLine * xdata)
{
    char cur;
    char last_c;
    bool open_str = false;
    int open_br = 0;
    bool was_expr = false;
    bool was_str = false;
    bool sub_expr = false;

    int res_code = 0;
    std::string data = xdata->text;
    line->line_id = xdata->line_nr;
    std::string cur_line;
    std::string sub_exp_s = "";
    std::vector<std::string> subexpr;
    boost::trim(data);
    line->data = data;
    line->commented = false;
    int line_len = data.length() - 1;


    if(data.length() == 0)
        return -1;


    for(int ci = 0; ci < data.length(); ci++)
    {
        cur = data[ci];

        if(cur==']' && open_br == 0 && open_str==false)
        {
            sub_expr = false;
            subexpr.push_back(sub_exp_s);
            sub_exp_s = "";
        }

        if(sub_expr)
        {
            sub_exp_s = sub_exp_s + cur;
        }

        if(cur=='[' && open_br == 0 && open_str==false)
        {
            sub_expr = true;
        }

        if(cur=='"' && open_br == 0 && sub_expr == false)
        {
            open_str = ! open_str;
            if(open_str==true)
                continue;
            was_str = true;
        }
        if(cur=='(' && open_str==false && sub_expr == false)
        {
            open_br++;
            if(open_br==1)
                continue;
        }

        if( cur==')' && open_str==false && sub_expr == false)
        {
            open_br--;
            if(open_br==0)
                was_expr = true;
        }

        if(open_str == false && open_br == 0  && sub_expr == false && ( cur==' ' ||  line_len == ci ))
        {
            if( last_c == ' ' &&  cur==' ' && was_str == false && was_expr == false )
                continue;

            if(line_len == ci && cur!=' ' && was_str == false && was_expr == false)
                cur_line = cur_line + cur;

            if(cur_line.length()==0)
                continue;

            MCCodeLine * child = new MCCodeLine();

            child->data = cur_line;
            if(cur_line=="//")
                line->commented = true;

            if(was_expr)
            {
                child->e_type = _C_T_EXPR;
                MCTextLine * new_data = new MCTextLine();
                new_data->line_nr = xdata->line_nr;
                new_data->text = cur_line;
                res_code = LineToCode(child,new_data);
                delete new_data;
                if(res_code!=0)
                    return res_code;
            }
            else
            if(was_str)
            {
                child->e_type = _C_T_STR;
            }
            else
            {
                if(is_number(cur_line))
                {
                    child->e_type = _C_T_NUMC;
                    MCRet* RET = CastNumc(cur_line);

                    if(RET->code==0)
                        child->num_value = RET->ret_nr;

                    delete RET;

                }else
                child->e_type = _C_T_COMP;
            }

            //Analyze subexpr
            for (std::vector<std::string>::iterator it = subexpr.begin() ; it != subexpr.end(); ++it)
            {
                std::string  sub_expr= *it;
                MCCodeLine * sub_child = new MCCodeLine();
                sub_child->data = sub_expr;
                sub_child->e_type = _C_T_SUBEXPR;
                sub_child->formal_type = "[" + sub_expr + "]";
                //res_code = LineToCode(sub_child,sub_expr);
                MCTextLine * new_data = new MCTextLine();
                new_data->line_nr = xdata->line_nr;
                new_data->text = sub_expr;
                res_code = LineToCode(sub_child,new_data);
                delete new_data;

                if(res_code!=0)
                    return res_code;

                child->children.push_back(sub_child);
                child->has_subexr = true;
            }

            line->expressions.push_back(child);

            cur_line = "";

            last_c = cur;
            was_expr = false;
            was_str = false;
            subexpr.clear();

            continue;
        }

        if(was_str || was_expr)
            continue;

        cur_line = cur_line + cur;

        if(open_br == 0 && open_str==false)
            last_c = cur;

        was_expr = false;
        was_str = false;

    }

    if(open_str==true)
        return -2;
    if(open_br!=0)
        return -3;

    return 0;
}
MCTextLine* MCEngine::FindLine(int line_id)
{
    for (std::vector<MCTextLine *>::iterator it = loaded_lines.begin() ; it != loaded_lines.end(); ++it)
    {
        MCTextLine * cur_line = *it;
        if(cur_line->line_nr == line_id)
            return cur_line;
    }
    return NULL;
}
std::string MCEngine::FindLineContent(int line_id)
{

    for (std::vector<MCTextLine *>::iterator it = loaded_lines.begin() ; it != loaded_lines.end(); ++it)
    {
        MCTextLine * cur_line = *it;
        if(cur_line->line_nr == line_id)
            return cur_line->full_line;
    }
    return "";
}
MCEngine::~MCEngine()
{
    //dtor
    var_scope->Free();
    type_scope->Free();
    func_scope->Free();
    code->Free();

    delete fregister;

    if(last_return!=NULL)
        delete last_return;

    //Deleting lines
    std::vector<MCTextLine*>::iterator it;
    for ( it = loaded_lines.begin(); it != loaded_lines.end(); )
    {
        MCTextLine* comp = *it;
        if(comp!=NULL)
            delete comp;
        it = loaded_lines.erase(it);
    }
}
