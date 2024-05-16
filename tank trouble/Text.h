#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include"Settings.h"

enum FONT
{
    Font3=0,
    Font4=1
};

class LText
{
public:
    LText();
    ~LText(){;}

    bool Loadtext(std::string path,SDL_Renderer* screen,int Type_font);
    void set_color(Uint8 red, Uint8 green, Uint8 blue);
    void render_text(int x_pos, int y_pos, SDL_Renderer* screen);//

    void free();
    SDL_Rect get_rect() {return renderQuad;}
private:
    TTF_Font* font32;
    TTF_Font* font48;
    SDL_Color c_text;
    SDL_Texture* mTexture;
    SDL_Rect renderQuad;

    unsigned int height;
    unsigned int weight;
};

#endif // TEXT_H_INCLUDED
