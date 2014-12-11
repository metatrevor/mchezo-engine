#ifndef OBJECTPARAMS_H
#define OBJECTPARAMS_H

#include <string>

class ObjectParams
{
public:
    ObjectParams(int x, int y, int width , int height, std::string textureKeyName);
    virtual ~ObjectParams();
private:
    int x;
    int y;
    int width;
    int height;
    std::string textureKeyName;
};

#endif // OBJECTPARAMS_H
