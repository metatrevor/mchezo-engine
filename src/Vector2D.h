#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>

class Vector2D
{
    public:
        Vector2D(float x, float y);
        Vector2D operator+(const Vector2D &rhs)const;
        Vector2D& operator+=(const Vector2D& rhs);
        Vector2D operator*(float scalar);
        Vector2D operator*=(float scalar);
        Vector2D operator-(const Vector2D& rhs) const;
        Vector2D& operator-=(const Vector2D &rhs);
        Vector2D operator/(float scalar);
        Vector2D operator /=(float scalar);
        float getX();
        float getY();
        void setX(float x);
        void setY(float y);
        float length();
        void normalize();
    private:
        float m_x;
        float m_y;
};

#endif // VECTOR2D_H
