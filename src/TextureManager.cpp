#include "TextureManager.h"
#include <string>

TextureManager &TextureManager::instance() {
    static TextureManager m_instance;
    return m_instance;
}

void TextureManager::init() {
    m_window = new Window("Game window", 640, 480);
    if (!IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG) {
        Log::Error("TextureManager : IMG_Init()"
                   + Log::GetSDLError() + Log::GetSDLIMGError());
    }
}

Window *TextureManager::getWindow() {
    return m_window;
}


bool TextureManager::loadTexture(std::string keyName, std::string fileName) {

    Log::Info("Attempting to load: "+fileName);

    SDL_Surface *tempSurface = IMG_Load(fileName.c_str());

    if (tempSurface == NULL) {
        Log::Error("Could not load create surface for " + fileName
                   + Log::GetSDLError() + Log::GetSDLIMGError());
        return false;
    }
    SDL_SetColorKey(tempSurface, SDL_TRUE,
                    SDL_MapRGB(tempSurface->format, 0, 0, 0));
    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(
        m_window->getRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface);

    if ( newTexture == NULL ) {
        Log::Error("Could not load create the texture for " + fileName
                   + Log::GetSDLError() + Log::GetSDLIMGError());
        return false;
    }

    m_textureMap[keyName] = newTexture;

    return true;
}

void TextureManager::drawTexture(std::string keyName,
                                 SDL_Rect& srcRect,
                                 SDL_Rect& dstRect) {
    SDL_RenderCopyEx(m_window->getRenderer(), getTexture(keyName), &srcRect,
                     &dstRect, 0, 0, SDL_FLIP_HORIZONTAL);
}

void TextureManager::drawTexture(std::string keyName, int x, int y,
                                 int width, int height,
                                 SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect dstRect;

    srcRect.x = 0;
    srcRect.y = 0;
    srcRect.w = dstRect.w = width;
    srcRect.h = dstRect.h = height;
    dstRect.x = x;
    dstRect.y = y;

    if (SDL_RenderCopyEx(m_window->getRenderer(), m_textureMap[keyName],
                         &srcRect, &dstRect,
                         0, 0, flip) != 0) {
        Log::Error("SDL_RenderCopyEx for texture " + keyName);
    }
}

void TextureManager::drawFrame(std::string id, int x, int y,
                               int width, int height,
                               int currentRow, int currentFrame,
                               SDL_RendererFlip flip) {
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = width * currentFrame;
    srcRect.y = height * (currentRow - 1);
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    SDL_RenderCopyEx(m_window->getRenderer(), m_textureMap[id],
                     &srcRect, &destRect, 0, 0, flip);
}

SDL_Texture *TextureManager::getTexture(std::string keyName) {
    if (m_textureMap[keyName] == NULL)
        Log::Error(keyName + " is null ");
    return m_textureMap[keyName];
}

void TextureManager::cleanup() {
    IMG_Quit();
}

void TextureManager::deleteTexture(std::string keyName) {
  if (m_textureMap.find(keyName) != m_textureMap.end()) {
        SDL_DestroyTexture(m_textureMap[keyName]);
        m_textureMap[keyName] = NULL;
        m_textureMap.erase(keyName);
    } else {
        Log::Error("The texture " + keyName +" was not found during deleting");
    }
}

void TextureManager::drawTile(std::string id, int margin,
                              int spacing, int x, int y,
                              int width, int height,
                              int currentRow, int currentFrame)
{
    SDL_Rect srcRect;
    SDL_Rect destRect;
    srcRect.x = margin + (spacing + width) * currentFrame;
    srcRect.y = margin + (spacing + height) * currentRow;
    srcRect.w = destRect.w = width;
    srcRect.h = destRect.h = height;
    destRect.x = x;
    destRect.y = y;
    if (SDL_RenderCopyEx(m_window->getRenderer(), m_textureMap[id], &srcRect,
            &destRect, 0, 0, SDL_FLIP_NONE) != 0) {
        Log::Error("SDL_RenderCopyEx for texture " + id + Log::GetSDLError());
    }
}
