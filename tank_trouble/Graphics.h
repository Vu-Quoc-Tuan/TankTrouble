#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED

#include"Settings.h"

class Graphics
{
public:
    Graphics();
    ~Graphics();

    void setforbackground();
    void set_rect(const int &x, const int &y) {rect_.x=x; rect_.y=y;}
    SDL_Rect get_rect_() const {return rect_;}

    SDL_Texture* get_texture () const {return texture;}

    bool Loadimage_base(const char *filename,SDL_Renderer* screen);
    void render (SDL_Renderer* des);
    void Free();

protected:
    SDL_Texture* texture;
    SDL_Rect rect_;
};

#endif // GRAPHICS_H_INCLUDED
