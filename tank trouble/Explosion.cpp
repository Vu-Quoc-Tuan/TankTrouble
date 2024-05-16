#include "Explosion.h"

Explosion::Explosion()
{
    weight_frame=0;
    height_frame=0;
    frame_=0;
}

bool Explosion::load_ex(SDL_Renderer* screen)
{
    bool res= Graphics::Loadimage_base("Image/kit/explosion.png",screen);
    weight_frame=rect_.w/5;
    height_frame=rect_.h;
    return res;
}

void Explosion::set_clip()
{
    if(height_frame>0 && weight_frame>0)
    {
        for(int i=0;i<5;i++)
        {
            frame_clip[i].x=i*weight_frame;
            frame_clip[i].y=0;
            frame_clip[i].w=weight_frame;
            frame_clip[i].h=height_frame;
        }
    }
}

void Explosion::Show_ex(SDL_Renderer* screen)
{
    frame_++;
    frame_=frame_%5;
    SDL_Rect renderquad={rect_.x,rect_.y,weight_frame,height_frame};
    SDL_Rect* currentclip= &frame_clip[frame_];
    SDL_RenderCopy(screen,texture,currentclip,&renderquad);
}
