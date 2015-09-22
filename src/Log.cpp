#include "Log.h"

Log *Log::m_instance = NULL;

Log *Log::Instance()
{
    if (!m_instance) {
        m_instance = new Log();
    }

    return m_instance;
}

void Log::Destroy()
{
    delete m_instance;
    m_instance = 0;
}

void Log::Print(std::string message)
{
    std::cerr << message << std::endl;
}

void Log::Info(std::string message, ...)
{
    Log::Instance()->Print("\nINFO : " + message + "\n");
}

std::string Log::IntToString(int value)
{
    std::stringstream ss;
    ss << value;
    return ss.str();
}

void Log::Error(std::string message)
{
    Log::Instance()->Print("\nERROR : " + message + "\n");
}

std::string Log::GetSDLError()
{
    std::string message;

    const char *sdl_error = SDL_GetError();

    if (strlen(sdl_error) != 0) {
        message += "\nSDL_Exception: ";
        message += sdl_error;
    }

    return message;
}

std::string Log::GetSDLIMGError()
{

    std::string message;

    const char *img_error = TTF_GetError();

    if (strlen(img_error) != 0) {
        message += "\nIMG_Exception: ";
        message += img_error;
    }

    return message;
}

std::string Log::GetSDLTTFError()
{

    std::string message;

    const char *ttf_error = TTF_GetError();

    if (strlen(ttf_error) != 0) {
        message += "\nTTF_Exception: ";
        message += ttf_error;
    }

    return message;
}
