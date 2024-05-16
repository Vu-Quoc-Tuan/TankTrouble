#ifndef KIT_H_INCLUDED
#define KIT_H_INCLUDED

#include"Settings.h"
#include"Graphics.h"
#include"Map.h"
#include"Extend.h"



class item : public Graphics
{
public:
    item();
    ~item(){;}

    bool load_image_item(SDL_Renderer* screen);
    void show_item (SDL_Renderer* screen);

    void set_distination(const Map& map_data);


    void set_type();
    int get_type() const {return type;}


private:
    int type;
};


#endif // KIT_H_INCLUDED
