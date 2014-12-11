#ifndef WINDOW_H
#define WINDOW_H

#include <SDL2/SDL.h>
#include <string>
#include "Log.h"

class Window
{
public:
    Window(std::string windowTitle, int w, int h);
    inline SDL_Renderer *getRenderer()
    {
        return m_renderer;
    }
    inline int getWidth()
    {
        return m_windowWidth;
    }
    inline int getHeight()
    {
        return m_windowHeight;
    }
    inline void resizeWindow(int w, int h)
    {
        SDL_SetWindowSize(m_window, w, h);
    }
    inline void clearRenderer()
    {
        SDL_RenderClear(m_renderer);
    }
    inline void updateWindow()
    {
        SDL_RenderPresent(m_renderer);
    }
    virtual ~Window();
private:
    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    std::string m_windowTitle;
    int m_windowWidth;
    int m_windowHeight;
};

#endif // WINDOW_H
