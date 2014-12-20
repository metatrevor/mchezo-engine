#ifndef ANIMATEDGRAPHIC_H
#define ANIMATEDGRAPHIC_H

#include "Object.h"

class AnimatedGraphic : public Object
{  public:
        AnimatedGraphic(int x, int y, int height, int width, std::string textureKeyName, int animationSpeed);
        void draw();
        void update();
        void clean();
    protected:
    private:
        Vector2D* m_mousePosition;
        int m_animationSpeed;
};

#endif // ANIMATEDGRAPHIC_H
