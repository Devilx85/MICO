#ifndef MCFUNCLIBCORE_H
#define MCFUNCLIBCORE_H


#include <IMCFuncLib.h>

class MCRet;
class MCVar;
class MCFunc;
class MCFParams;
class MCEngine;

class MCFuncLibCore : public IMCFuncLib
{
public:
    MCFuncLibCore();
    virtual ~MCFuncLibCore();
    void RegFunc(MCFuncRegister * reg);


protected:

private:
};

MCRet* _IF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _VAR(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _OUT(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _CONCAT(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _DO_TIMES(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _FOR(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _A_ARITH(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _A_COMP(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _TYPE_DEF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _TYPE_OF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _SET(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _ADD_ITEM(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _DEF_FUNC(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _DEF_METHOD(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _CALL_FUNC(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _LEN(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _MYTYPE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _MYNAME(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _SAVETOFILE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _LOADFROMFILE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _TREELOADFROMFILE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _CE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _IDX(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _CREATE_NODE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _DELETE_NODE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _LOOP(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _WHILE(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _SETFL(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _MOVENP(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _ISLASTF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _INC(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _CI(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _MYINDEX(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _MYASINDEX(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
MCRet* _FIND(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
//MCRet* _TYPE_OF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
//MCRet* _TYPE_OF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
//MCRet* _TYPE_OF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
//MCRet* _TYPE_OF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
//MCRet* _TYPE_OF(MCEngine* engine, MCCodeLine* line, MCVar* vars, MCVar* types, MCFunc* func,MCFParams* params);
#endif // MCFUNCLIBCORE_H


