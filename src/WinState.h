#ifndef CWINSTATE_H
#define CWINSTATE_H

#include "Defines.h"
#include <SDL2/SDL.h>


class WinState
{

public:
    WinState(Graphics *graphics, StateManager *stateManager);
    bool Run();
    void HandleInput();
    void OnQuit();
    void Pause();
    void OnKeyDown(SDL_Keycode sym, SDL_Keymod mod, Uint16 unicode);
    void LoadResources();
    void getWinner(int winner);

    SDL_Surface *m_grid_o_wins;
    SDL_Surface *m_grid_x_wins;
    SDL_Surface *m_grid_draw_win;

    int m_winner;
};

#endif // CWINSTATE_H
