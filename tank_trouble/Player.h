#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Graphics.h"
#include "Map.h"
#include "Bullet.h"
#include "Sound.h"

class Player
{
public:
    Player();
    ~Player(){;}

    bool Loadimage_main(SDL_Renderer* screen);
    void Update_action(SDL_Renderer* screen, const Map& map_data);
    void fire_action(SDL_Renderer* screen, Sound* p_sound);
    void checkToMap(const Map &map_data);
    void Show(SDL_Renderer* screen);

    void delete_bullet (const int &value, const int type);
    void draw_bullet (SDL_Renderer* screen,const Map& map_data);

    void set_player2 (const bool value) {appear=value;}

    SDL_Rect get_rect_player1() const {return rect_;}
    void set_rect_player1(float x, float y) {x_pos_ =x; y_pos_=y; angle=0;}
    SDL_Rect get_rect_player2() const {return rect2_;}
    void set_rect_player2(float x, float y) {x_pos2_ =x; y_pos2_=y;angle2=0;}

    void set_type_bullet1(const int& value) {type_bullet=value;}
    void set_type_bullet2(const int& value) {type_bullet2=value;}

    std::vector<BulletObject*> get_list1_() {return bullet_list;}
    std::vector<BulletObject*> get_list2_() {return bullet_list2;}

private:
    float x_pos_;
    float y_pos_;
    float x_value_;
    float y_value_;

    int angle;
    SDL_Texture* texture;
    SDL_Rect rect_;
    std::vector<BulletObject*>bullet_list;
    int type_bullet;

    bool armor1;


    float x_pos2_;
    float y_pos2_;
    float x_value2_;
    float y_value2_;

    int angle2;
    SDL_Texture* texture2;
    SDL_Rect rect2_;
    bool appear;
    std::vector<BulletObject*>bullet_list2;
    int type_bullet2;
};



#endif // PLAYER_H_INCLUDED
