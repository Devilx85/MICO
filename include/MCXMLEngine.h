#ifndef MCXMLENGINE_H
#define MCXMLENGINE_H
#include "../../pugixml-master/src/pugixml.hpp"
#include "MCRet.h"
#include "MCEngine.h"

class MCXMLEngine
{
public:
    MCXMLEngine();
    virtual ~MCXMLEngine();

    MCRet* LoadString(std::string xml,MCVar* ret_var,MCEngine* Engine);
    MCRet* ExploreNodes(pugi::xml_node node,MCVar* ret_var,MCEngine* Engine);
protected:

private:
};

#endif // MCXMLENGINE_H
