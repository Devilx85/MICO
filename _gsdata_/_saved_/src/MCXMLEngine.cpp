#include "MCXMLEngine.h"
#include "../../pugixml-master/src/pugixml.hpp"

MCXMLEngine::MCXMLEngine()
{
    //ctor
}
MCRet* MCXMLEngine::LoadString(std::string xml,MCVar* ret_var,MCEngine* Engine)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(xml.c_str());
    if (!result)
    {
        std::string descr = result.description();
        return Engine->RetCreate(_C_F_TRANSLATION_ERROR,"","ERROR","Can not parse XML:"+descr,-100);
    }
    pugi::xml_node xml_node = doc.root();
    ExploreNodes(xml_node,ret_var,Engine);

    return Engine->RetCreate(0,"","","",0);

}
MCRet* MCXMLEngine::ExploreNodes(pugi::xml_node node,MCVar* ret_var,MCEngine* Engine)
{
    std::string er_text = "";
    MCVar * cr_p = NULL;
    for (pugi::xml_attribute attr: node.attributes())
    {
        ret_var->CreateVar(attr.name(),"VAR",attr.value(),Engine->type_scope,er_text,cr_p);

    }

    for (pugi::xml_node child: node.children())
    {
        ret_var->CreateVar(child.name(),"TREE",child.child_value(),Engine->type_scope,er_text,cr_p);
        ExploreNodes(child,cr_p,Engine);
    }

}
MCXMLEngine::~MCXMLEngine()
{
    //dtor
}
