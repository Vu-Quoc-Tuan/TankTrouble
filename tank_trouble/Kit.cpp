#include "Kit.h"

item::item()
{
    type=type_item::rocket;
    rect_.x=450;
    rect_.y=100;
}
bool item::load_image_item(SDL_Renderer* screen)
{
    //Free();
    bool temp=false;
    if(type==laser)
    {
        temp=Graphics::Loadimage_base("Image/kit/Laser.png",screen);
    }else if(type==rocket){
        temp=Graphics::Loadimage_base("Image/kit/Rocket.png", screen);
    }else {
        temp=Graphics::Loadimage_base("Image/kit/Armor.png", screen);
    }
    return temp;
}

void item::set_type()
{
    srand(time(NULL));
    type=rand()%3;
}

void item::set_distination(const Map& map_data)
{
    bool check=false;
        srand(time(NULL));
        int tempx=rand()%706+80;
        int tempy=rand()%601+35;

            rect_.x=tempx;
            rect_.y=tempy;

}

void item::show_item(SDL_Renderer* screen)
{
    SDL_RenderCopy(screen,texture,NULL,&rect_);
}
