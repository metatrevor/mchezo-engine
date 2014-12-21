#ifndef LAYER_H_
#define LAYER_H_

class Layer
{
public:
    virtual void render()=0;
    virtual void update()=0;

protected:
    virtual ~Layer();
};

#endif
