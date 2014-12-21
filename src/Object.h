#ifndef OBJECT_H_
#define OBJECT_H_

#include <string>
#include "TextureManager.h"
#include "ObjectParams.h"
#include "Vector2D.h"

class Object
{
public:
   Object(int x, int y, int width, int height, std::string textureName);
   virtual void draw() = 0;
   virtual void update() = 0;
   virtual void clean() = 0;
   Vector2D &getPosition(){return m_position; }
   int getHeight() {return m_height; }
   int getWidth() {return m_width; }
protected:

    int m_width;
    int m_height;
    std::string m_textureKeyName;
    int m_currentFrame;
    int m_currentRow;
    Vector2D m_position;
    Vector2D m_velocity;
    Vector2D m_acceleration;
};

#endif // OBJECT_H_

