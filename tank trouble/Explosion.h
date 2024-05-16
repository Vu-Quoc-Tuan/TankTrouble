#ifndef EXPLOSION_H_INCLUDED
#define EXPLOSION_H_INCLUDED

#include "Settings.h"
#include "Graphics.h"

class Explosion : public Graphics
{
public:
    Explosion();
    ~Explosion() {;}

    bool load_ex (SDL_Renderer* screen);
    void Show_ex (SDL_Renderer* screen);

    void set_clip();
private:
    int frame_;
    SDL_Rect frame_clip[6];
    int weight_frame;
    int height_frame;
};
#endif // EXPLOSION_H_INCLUDED
