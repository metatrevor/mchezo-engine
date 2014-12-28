#include "ObjectParams.h"

ObjectParams::ObjectParams(int x, int y, int width , int height, std::string textureKeyName)
    :m_x(x), m_y(y), m_width(width), m_height(height), m_textureKeyName(textureKeyName)
{
    //ctor
}

ObjectParams::~ObjectParams()
{
    //dtor
}
