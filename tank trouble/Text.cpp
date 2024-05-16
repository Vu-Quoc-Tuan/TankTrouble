#include "Text.h"

LText::LText()
{
    weight=0;
    height=0;
    mTexture=NULL;

    SDL_Color temp={255,255,255};
    c_text=temp;

    font32 = TTF_OpenFont("font/font.ttf", 32);
    font48 = TTF_OpenFont("font/font.ttf", 48);
}

bool LText::Loadtext(std::string path,SDL_Renderer* screen,int Type_font)
{
    SDL_Surface* temp=NULL;
    if(Type_font==Font3){
        temp=TTF_RenderText_Solid(font32,path.c_str(),c_text);
    }
    else{
        temp=TTF_RenderText_Solid(font48,path.c_str(),c_text);
    }
    if(temp==NULL){
        std::cerr<<"Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError();
    }else{
        mTexture=SDL_CreateTextureFromSurface(screen,temp);
        weight=temp->w;
        height=temp->h;
    }
    SDL_FreeSurface(temp);
    return mTexture!=NULL;
}

void LText::set_color(Uint8 red, Uint8 green, Uint8 blue)
{
    c_text.r=red;
    c_text.g=green;
    c_text.b=blue;
}

void LText::render_text(int x_pos, int y_pos, SDL_Renderer* screen)
{
    if (mTexture == NULL) {
//        std::cerr << "Error: Texture is not loaded!" << std::endl;
        return;
    }

    renderQuad= {x_pos, y_pos, weight,height};
    SDL_RenderCopyEx(screen,mTexture,NULL,&renderQuad,0.0,NULL,SDL_FLIP_NONE);
    free();
}

void LText::free()
{
    if(mTexture!=NULL)
    {
        SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		weight=0;
		height=0;
    }
}
