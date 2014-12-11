#include "Graphics.h"


Graphics::Graphics()
{
    m_backBuffer = NULL;

    Log::Info("Initializing TTF");
    TTF_Init();

    Log::Info("Initializing Display");
//    if((m_backBuffer = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT , SCREEN_BPP, SCREEN_FLAGS)) == NULL)
//    {
//        Log::Error("Game::Init - Unable to initialise display ");
//    }
}

Graphics::~Graphics()
{
    TTF_Quit();
    SDL_FreeSurface(m_backBuffer);
}

SDL_Surface* Graphics::LoadImage(std::string filename)
{
    SDL_Surface* Surf_Temp = NULL;
    SDL_Surface* Surf_Return = NULL;

    if((Surf_Temp = IMG_Load(filename.c_str())) == NULL)
    {
        Log::Error("Error Loading Image " + filename);
        return NULL;
    }

//    Surf_Return = SDL_DisplayFormat(Surf_Temp);
    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}

bool Graphics::DrawTextureOnScreen(SDL_Surface *Surf_Src, int X, int Y)
{
    if(Surf_Src == NULL) {
            return false;
        }

        SDL_Rect DestR;
        DestR.x = X;
        DestR.y = Y;
        SDL_BlitSurface(Surf_Src, NULL, m_backBuffer, &DestR);
        return true;
}

bool Graphics::DrawImage(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y)
{
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    return true;
}

bool Graphics::DrawImage(SDL_Surface* Surf_Dest, SDL_Surface* Surf_Src, int X, int Y, int X2, int Y2, int W, int H) {
    if(Surf_Dest == NULL || Surf_Src == NULL) {
        return false;
    }

    SDL_Rect DestR;

    DestR.x = X;
    DestR.y = Y;

    SDL_Rect SrcR;

    SrcR.x = X2;
    SrcR.y = Y2;
    SrcR.w = W;
    SrcR.h = H;

    SDL_BlitSurface(Surf_Src, &SrcR, Surf_Dest, &DestR);

    return true;
}


bool Graphics::MakeTransparent(SDL_Surface* Surf_Dest, int R, int G, int B)
{
    if(Surf_Dest == NULL)
        return false;

//    SDL_SetColorKey(Surf_Dest, (SDL_SRCCOLORKEY | SDL_RLEACCEL) , SDL_MapRGB(Surf_Dest->format, R, G, B));

    return true;
}

void Graphics::ClearScreen(int R, int G, int B)
{
    SDL_FillRect(m_backBuffer, NULL, SDL_MapRGB(m_backBuffer->format, R, G, B));
}


bool Graphics::FillSurface(SDL_Surface *Surf_Dest, int R, int G, int B)
{
    if(Surf_Dest == NULL)
        return false;

    SDL_FillRect(Surf_Dest, NULL, SDL_MapRGB(Surf_Dest->format, R, G, B));

    return true;
}

SDL_Surface *Graphics::GetDisplay()
{
    return m_backBuffer;
}

void Graphics::DisplayText(std::string text, SDL_Surface *Surf_Dest, int x, int y, int size,
							int fR, int fG, int fB, int bR, int bG, int bB)
{
	// Crate a font variable and set its size to the given parameter
    TTF_Font* font = TTF_OpenFont("ARIAL.TTF", size);

    if(font == NULL)
        Log::Error("font is null : ");

    SDL_Color foreground  = { fR, fG, fB, 0};   // text color
    SDL_Color background  = { bR, bG, bB, 0};  // color of what's behind the text

	// This renders the text to a temporary surface. There are more text
	// functions than TTF_RenderText_Shaded(), but this one looks nice.
	SDL_Surface* temp = TTF_RenderText_Shaded(font, text.c_str(), foreground, background);

	// Blit ("Block Image Transfer") the text to the backbuffer
	SDL_Rect destination = { x, y, 0, 0 };
    SDL_BlitSurface(temp, NULL, Surf_Dest, &destination);

	// Always free memory!
	SDL_FreeSurface(temp);

	// Destroy the font variable
	TTF_CloseFont(font);
}

void Graphics::UpdateDisplay()
{
//    SDL_UpdateRect(m_backBuffer, 0, 0, 0, 0);
   //SDL_Flip(m_backBuffer);
}

