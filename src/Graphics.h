#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "Log.h"
#include "Defines.h"

class Graphics
{

	public:

    Graphics();
    ~Graphics();

         SDL_Surface* LoadImage(std::string filename);

         SDL_Surface* GetDisplay();

         bool DrawTextureOnScreen(SDL_Surface *Surf_Src, int X, int Y);

         bool DrawImage(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int X, int Y);

         bool DrawImage(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int X, int Y, int X2, int Y2, int W, int H);

         void DisplayText(std::string text, SDL_Surface *Surf_Dest, int x, int y, int size,
                                    int fR, int fG, int fB, int bR, int bG, int bB);

         bool MakeTransparent(SDL_Surface *Surf_Dest, int R, int G, int B);

         bool FillSurface(SDL_Surface *Surf_Dest, int R=0, int G=0, int B=0);

         void ClearScreen(int R=0, int G=0, int B=0);

         void UpdateDisplay();

        SDL_Surface* m_backBuffer;

};

#endif
