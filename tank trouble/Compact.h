#ifndef COMPACT_H_INCLUDED
#define COMPACT_H_INCLUDED

#include "Settings.h"
#include "Graphics.h"
#include "Map.h"
#include "Player.h"
#include "Threat.h"
#include "Kit.h"
#include "Timer.h"
#include "Text.h"
#include "Sound.h"
#include "Explosion.h"

enum OPTION
{
    EXIT_GAME=0,
    HOME     =1,
    HELP     =2,
    REPLAY   =3,
    SINGLEPLAYER=4,
    MULTIPLAYER=5,
    PAUSE    =6,
    RANK     =7,
    CONTINUE =8,

    NO=10
};

namespace SDLWin
{
    void logErrorAndExit(const char* msg, const char* error);
    SDL_Window* initSDL() ;
    SDL_Renderer* createRenderer(SDL_Window* window);
    void quitSDL(SDL_Window* window, SDL_Renderer* renderer);
}

namespace Extension
{
    bool pointed_to(int x_pos, int y_pos, SDL_Rect rect);
    bool check_highscore(int score);
    void save_score(int score);
}

#endif // COMPACT_H_INCLUDED
