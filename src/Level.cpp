#include "Level.h"

Level::~Level()
{

}


void Level::render()
{
    std::vector<Layer*>::size_type i;
    for (i = 0; i < m_layers.size(); ++i)
    {
        m_layers[i]->render();
    }
}

void Level::update()
{
    std::vector<Layer*>::size_type i;
    for (i = 0; i < m_layers.size(); ++i) {
        m_layers[i]->update();
    }
}

