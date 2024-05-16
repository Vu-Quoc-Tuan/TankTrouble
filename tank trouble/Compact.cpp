#include "Compact.h"

//phần Win
void SDLWin::logErrorAndExit(const char* msg, const char* error)
{
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "%s: %s", msg, error);
    SDL_Quit();
}
SDL_Window* SDLWin::initSDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

    SDL_Window* window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                  SDL_WINDOW_SHOWN);
    if (window == nullptr)
            logErrorAndExit("CreateWindow", SDL_GetError());

    if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());
    if(TTF_Init()==-1)
            logErrorAndExit( "SDL_Font error:", TTF_GetError());
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
            logErrorAndExit( "SDL_Video error:", SDL_GetError());
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
            logErrorAndExit( "SDL_Mix error:", Mix_GetError());

    return window;
}
SDL_Renderer* SDLWin::createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    //renderer =
             SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

    if (renderer == nullptr)
             logErrorAndExit("CreateRenderer", SDL_GetError());

    SDL_SetRenderDrawColor(renderer,255,255,255,255);//có thể sửa

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
    SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

    return renderer;
}
void SDLWin::quitSDL(SDL_Window* window, SDL_Renderer* renderer)
{
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


//EXTENSION

bool Extension::pointed_to(int x_pos, int y_pos, SDL_Rect rect)
{
    return rect.x <= x_pos && x_pos <= rect.x + rect.w
        && rect.y <= y_pos && y_pos <= rect.y + rect.h;
}

bool Extension::check_highscore(int score)
{
    std::fstream file ("font/highScore.txt");
    int temp;
    if(file.is_open())
    {
        file>>temp;
        file.close();
        if(temp<score) return true;
        else return false;
    }else{
        std::cerr << "Unable to open file!" << std::endl;
    }
    return false;
}
void Extension::save_score(int score)
{
    std::ofstream delete_file ("font/highScore.txt", std::ofstream::out | std::ofstream::trunc);
    if (delete_file.is_open()) {
        delete_file.close();
    } else {
        std::cerr << "Unable to open file!" << std::endl;
    }

    std::ofstream file ("font/highScore.txt");
    if (file.is_open()) {
        file<<score;
        file.close();
    } else {
        std::cerr << "Unable to open file!" << std::endl;
    }
}
