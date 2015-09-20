#include "Window.h"

Window::Window(std::string windowTitle, int w ,int h)
    :m_window(NULL),
     m_renderer(NULL),
     m_windowTitle(windowTitle),
     m_windowWidth(w),
     m_windowHeight(h)
{
    m_window = SDL_CreateWindow(m_windowTitle.c_str(),
                                SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED,
                                m_windowWidth,
                                m_windowHeight,
                                SDL_WINDOW_SHOWN
                                );

    if(m_window == NULL)
    {
        Log::Error("Window :" + windowTitle + "could not be created" + Log::GetSDLError());
    }

    m_renderer = SDL_CreateRenderer(m_window, -1,  SDL_RENDERER_ACCELERATED);

    if(m_renderer == NULL)
    {
        Log::Error("Renderer for :" + windowTitle + " could not be created" + Log::GetSDLError());
    }

    SDL_SetRenderDrawColor(m_renderer, 0x00, 0x00, 0x00, 0xFF);
}

Window::~Window()
{
    if(m_renderer != NULL)
    {
        SDL_DestroyRenderer(m_renderer);
        m_renderer = NULL;
    }

    if(m_window != NULL)
    {
        SDL_DestroyWindow(m_window);
        m_window = NULL;
    }
}
