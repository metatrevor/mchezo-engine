#include "ObjectFactory.h"


bool ObjectFactory::registerObjectType(std::string objectType, BaseObjectCreator *creator)
{
    std::map<std::string, BaseObjectCreator*>::iterator it = m_objectTemplates.find(objectType);
    if(it != m_objectTemplates.end())
    {
        delete creator;
        return false;
    }
    m_objectTemplates[objectType] = creator;
    return true;
}

Object *ObjectFactory::create(std::string objectType)
{
    std::map<std::string, BaseObjectCreator*>::iterator it = m_objectTemplates.find(objectType);
    if(it == m_objectTemplates.end())
    {
      Log::Info("Could not find type : " + objectType);
      return NULL;
    }

    BaseObjectCreator *creator = (*it).second;
    return creator->createObject();
}
