#ifndef LAYER_H_
#define LAYER_H_

//Abstract layer class

class Layer
{
public:
    virtual void render()=0;
    virtual void update()=0;

protected:
    virtual ~Layer() {}
};

#endif
