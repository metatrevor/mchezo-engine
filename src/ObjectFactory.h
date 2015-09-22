#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H9

#include <string>
#include <map>
#include "Object.h"
#include "Log.h"

class BaseObjectCreator
{
public:
    virtual Object *createObject() const = 0;

    virtual ~BaseObjectCreator()
    { }
};

class ObjectFactory
{
public:
    bool registerObjectType(std::string objectType, BaseObjectCreator *creator);

    Object *create(std::string objectType);

private:
    std::map<std::string, BaseObjectCreator *> m_objectTemplates;
};

#endif // OBJECTFACTORY_H
