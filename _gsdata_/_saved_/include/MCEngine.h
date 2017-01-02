#ifndef MCENGINE_H
#define MCENGINE_H
#include <vector>
#include <MCCodeLine.h>
#include "MCRet.h"
#include "MCFuncRegister.h"
#include "MCFuncLibCore.h"
#include "MCTextLine.h"

class MCEngine
{
public:
    MCEngine();
    virtual ~MCEngine();
    MCCodeLine *code;
    MCCodeLine *cur_code; //REF TO CURRENCT NODE
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
    std::vector<MCTextLine *> loaded_lines;
    bool check_exec_time = true;
    long long exec_time=0;
    MCRet* last_return = NULL;

    MCRet* EvaluateLine(MCCodeLine * line, MCVar* xvar_scope, MCVar* xtype_scope,int func_type = _C_FT_FUNC);
    MCTextLine* FindLine(int line_id);
    std::string FindLineContent(int line_id);
protected:
    bool ends_with(std::string const & value, std::string const & ending);
    MCRet* SubExpressionRender(MCCodeLine * line,MCVar* xvar_scope,MCVar* xtype_scope);
    int LineToCode(MCCodeLine * line, MCTextLine * xdata);
    MCRet* RenderLine(MCCodeLine * line,MCVar* xvar_scope,MCVar* xtype_scope,int func_type  = _C_FT_FUNC);
private:
};

#endif // MCENGINE_H
