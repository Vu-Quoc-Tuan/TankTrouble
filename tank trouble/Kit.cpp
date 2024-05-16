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

void item::set_distination(const Map& map_data) {
    bool position_found = false;
    while (!position_found) {
        int tempx = rand() % 691 + 95;
        int tempy = rand() % 591 + 50;

        int tile_x = tempx / TILE_SIZE;
        int tile_y = tempy / TILE_SIZE;
        if (map_data.tile[tile_y][tile_x] != 1) {
            rect_.x = tempx;
            rect_.y = tempy;
            position_found = true;
        }
    }
}

void item::show_item(SDL_Renderer* screen)
{
    SDL_RenderCopy(screen,texture,NULL,&rect_);
}
