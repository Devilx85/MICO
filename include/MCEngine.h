#ifndef MCENGINE_H
#define MCENGINE_H
#include <vector>
#include <MCCodeLine.h>
#include "MCRet.h"
#include "MCFuncRegister.h"
#include "MCFuncLibCore.h"

class MCEngine
{
    public:
        MCEngine();
        virtual ~MCEngine();
        MCCodeLine *code;
        MCCodeLine *cur_code;
        std::string out_buffer = "";
        int LoadString(std::string data);
        void PrintCode(MCCodeLine * xcode, int lev = 0 );
        void PrintLines(MCCodeLine * xcode, int lev = 0 );
        MCFuncRegister* fregister;
        MCFuncLibCore* clib;
        MCRet* Run();
        MCRet* CastNumc(std::string value);
        bool is_number(const std::string& s);
        MCRet* RetCreate(int pcode,std::string pdata,std::string ptype,std::string pbufout,int pstop_code);
        int inner_cycle_counter = 0;
        MCVar* var_scope;
        MCVar* type_scope;
        MCVar* func_scope;

        bool check_exec_time = true;
        long long exec_time=0;

        int const _C_NO_REQ_PARAM = -1000;
        int const _C_F_NOTFOUND = -1001;
        int const _C_F_UNKNOWN_ELEM = -1002;
        int const _C_F_UNKNOWN_ELEM_END = -1003;
        int const _C_F_CAST_ERROR = -1004;
        int const _C_F_DATA_NOT_RECIEVED = -1004;
        int const _C_F_LVALUE_REQ = -1005;
        int const _C_F_EMPTY_ELEM = -1006;
        int const _C_F_TYPE_EXIST = -1007;
        int const _C_F_TYPE_NOT_FOUND = -1008;
        int const _C_F_VAR_EXIST = -1007;
        int const _C_F_VAR_NOT_FOUND = -1008;
        int const _C_F_GLOBAL_TYPE = -1009;
        int const _C_F_NON_ARRAY = -1010;
        int const _C_F_INVALID_INDEX = -1011;
        int const _C_F_FUNC_EXIST = -1012;
        int const _C_F_FUNC_NOT_FOUND = -1013;
        int const _C_F_FUNC_PARAM_ERROR = -1014;
        int const _C_F_PROTECTED_VALUE = -1015;
        int const _C_F_NAME_NOT_ALLOWED = -1016;
        int const _C_F_INCOMPLETE_DEF = -1017;
        int const _C_F_TYPE_MISMATCH = -1018;

        MCRet* EvaluateLine(MCCodeLine * line, MCVar* xvar_scope, MCVar* xtype_scope,std::string func_type = "FUNC");
    protected:
        MCRet* SubExpressionRender(MCCodeLine * line,MCVar* xvar_scope,MCVar* xtype_scope);
        int LineToCode(MCCodeLine * line , std::string data);
        MCRet* RenderLine(MCCodeLine * line,MCVar* xvar_scope,MCVar* xtype_scope,std::string func_type  = "FUNC");
    private:
};

#endif // MCENGINE_H
