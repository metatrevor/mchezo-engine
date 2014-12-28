#ifndef OBJECTPARAMS_H
#define OBJECTPARAMS_H

#include <string>

class ObjectParams
{
public:
    ObjectParams(int x, int y, int width , int height, std::string textureKeyName);
    virtual ~ObjectParams();
    int getX(){return m_x;}
    int getY(){return m_x;}
    int getHeight(){return m_height;}
    int getWidth(){return m_width;}
    std::string getTextureName(){return m_textureKeyName;}
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    std::string m_textureKeyName;
};

#endif // OBJECTPARAMS_H
