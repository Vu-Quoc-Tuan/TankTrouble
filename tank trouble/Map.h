#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "Settings.h"
#include"Graphics.h"

typedef struct Map
{
    int start_x_;
    int start_y_;
    int max_x_;
    int max_y_;
    int tile[50][50]={0};//chx sua
    std::string file_name_;
} Map;
#define MAX_TILES 3
#define tile_startX 6
#define tile_endX 53
#define tile_startY 3
#define tile_endY 43

class MapObject
{
public:
    MapObject(){;}
    ~MapObject(){;}

    void load_map(int map_type);
    void load_title(SDL_Renderer* screen);
    void drawmap(SDL_Renderer*screen);
    Map get_datamap() const {return game_map_;}

private:
    Graphics temp;
    Map game_map_;
};

#endif // MAP_H_INCLUDED
