#include "Graphics.h"

Graphics::Graphics()
    {
        texture=NULL;
        rect_.x=0;
        rect_.y=0;
        rect_.w=0;
        rect_.h=0;
    }

Graphics::~Graphics()
    {
        Free();
    }

bool Graphics::Loadimage_base(const char *filename,SDL_Renderer* screen)
    {

        Free();
        texture = IMG_LoadTexture(screen, filename);
        if (texture == NULL){
            std::cerr << "Unable to create texture from " << filename << "! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_QueryTexture(texture, NULL, NULL, &rect_.w, &rect_.h);

        return true;
    }

void Graphics::render(SDL_Renderer* dest)
    {

        SDL_Rect renderquad={rect_.x,rect_.y,rect_.w,rect_.h};
        SDL_RenderCopy(dest,texture,NULL,&renderquad);
    }

void Graphics::Free()
    {
        if(texture!=NULL){
        SDL_DestroyTexture(texture);
        texture=NULL;
        rect_.h=0;
        rect_.w=0;
        }
    }

void Graphics::setforbackground()
    {
        SDL_Rect temp={0,0,SCREEN_WIDTH,SCREEN_HEIGHT};
        rect_=temp;
    }
