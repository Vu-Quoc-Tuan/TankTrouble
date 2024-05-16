#ifndef THREAT_H_INCLUDED
#define THREAT_H_INCLUDED

#include "Settings.h"

class Threat_object
{
public:
    Threat_object();
    ~Threat_object(){;}

    bool Loadimage_monster(SDL_Renderer* screen);
    void Show(SDL_Renderer* screen);
    void set_clip();

    void domonster (const int dest_x, const int dest_y);

    void set_destination (const int x, const int y) {x_pos_=x;
                                                     y_pos_=y;}

    SDL_Rect get_rect_threat() const {return renderquad;}

private:

    SDL_Texture * th_texture;
    SDL_Rect th_rect;

    float x_pos_;
    float y_pos_;
    float x_value_;
    float y_value_;

    int height_frame;
    int weight_frame;
    int frame_;
    SDL_Rect frame_clip[9];

    SDL_Rect renderquad;
};

#endif // THREAT_H_INCLUDED
