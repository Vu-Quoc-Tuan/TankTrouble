#include "Game.h"


int main(int argc, char *argv[])
{
    SDL_Window* window=SDLWin::initSDL();
    SDL_Renderer* renderer=SDLWin::createRenderer(window);

    Game Mgame;
    Mgame.set_render(renderer);
    Mgame.Start();

    SDLWin::quitSDL(window,renderer);
    return 0;
}
