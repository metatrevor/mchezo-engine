#ifndef LOG_HPP
#define LOG_HPP

#include <cstddef>
#include <string>
#include <iostream>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Log
{
public:
    static Log *Instance();

    static void Info(std::string message, ...);

    static std::string IntToString(int value);

    static void Error(std::string message);

    static std::string GetSDLError();

    static std::string GetSDLIMGError();

    static std::string GetSDLTTFError();

    static void Destroy();

private:
    Log()
    { }

    ~Log()
    { Destroy(); }

    Log(Log const &)
    { };

    Log &operator=(Log const &)
    { };

    void Print(std::string message);

    static Log *m_instance;
};

#endif
