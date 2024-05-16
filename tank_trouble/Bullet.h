#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "Graphics.h"
#include "Map.h"
#include "Extend.h"
#include <chrono>
#include <queue>
#include "Sound.h"

const float MIN_DISTANCE_FROM_SPAWN_POINT = 20.0f;

class BulletObject : public Graphics
{
public:
    BulletObject();
    ~BulletObject(){;}

    bool load_image_bullet(SDL_Renderer* screen);
    void render_bullet(SDL_Renderer* screen);
    void control_bullet(const Map& map_data,int targetX, int targetY);// control all;
    void time_bullet(const int count_time);

    void Bouncing_bullet(const Map& map_data);
    void through_wall();

    //rocket
    void find_anyone(const Map& map_data,int targetX, int targetY);
    void movent(const Map& map_data ,int targetX, int targetY);
    void getAngle(const Map& map_data,int targetX, int targetY);


    void set_move (const bool& status) {is_move=status;}
    bool get_move () const {return is_move;}

    void set_angle_bullet(const int& value) { angle_bullet=value;
                                              spawn_x_=rect_.x;
                                              spawn_y_=rect_.y;}
    void set_type_bullet (const int& value) {type_bullet  = value;}
    int get_type_bullet() const {return type_bullet;}


    float getDistanceFromSpawnPoint() const {
        return std::sqrt(std::pow(rect_.x - spawn_x_, 2) + std::pow(rect_.y - spawn_y_, 2));
    }

private:
    int spawn_x_;
    int spawn_y_;

    bool is_move;
    int bulletcheck;
    int angle_bullet;

    int type_bullet;
    int life_rocket;

    std::chrono::high_resolution_clock::time_point start_time;
    std::vector<std::pair<int, int>> path;

    int angle_change;
};


#endif // BULLET_H_INCLUDED
