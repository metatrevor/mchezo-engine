#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Log.h"
#include "Window.h"
#include <string>
#include <map>

class TextureManager
{
public:
    void init();

    Window *getWindow();

    static TextureManager &instance();

    bool loadTexture(std::string keyName, std::string fileName);

    void drawTexture(std::string keyName, int x, int y, int width, int height,
                     SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawTexture(std::string keyName, SDL_Rect &srcRect, SDL_Rect &dstRect);

    void drawFrame(std::string id, int x, int y, int width, int
    height, int currentRow, int currentFrame,
                   SDL_RendererFlip flip = SDL_FLIP_NONE);

    void drawTile(std::string id, int margin, int spacing, int x, int y, int width,
                  int height, int currentRow,
                  int currentFrame);


    SDL_Texture *getTexture(std::string keyName);

    void deleteTexture(std::string keyName);

    void cleanup();

private:
    TextureManager()
    { } //No construction
    ~TextureManager()
    { }  //No unwanted destruction
    TextureManager(const TextureManager &); //No copy construction
    TextureManager &operator=(const TextureManager &); //No assignment
    Window *m_window;
    std::map<std::string, SDL_Texture *> m_textureMap;
};

#endif // TEXTURE_H
