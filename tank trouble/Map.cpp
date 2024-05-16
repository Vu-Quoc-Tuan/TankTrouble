#include "Map.h"

void MapObject::load_map(int map_type)
{
    std::ifstream file;

    if(map_type==1){
        file.open("Map/map1.txt");
        game_map_.file_name_="Map/map1.txt";
    } else {
        file.open("Map/map01.txt");
        game_map_.file_name_="Map/map01.txt";
    }

    if(file.is_open()){
        game_map_.max_x_=0;
        game_map_.max_y_=0;

        for(int i=tile_startY;i<tile_endY;i++){
            for(int j=tile_startX;j<tile_endX;j++){
                int val;
                file>>val;
                game_map_.tile[i][j]=val;
                if (val > 0) {
                    if (j > game_map_.max_x_) game_map_.max_x_ = j;
                    if (i > game_map_.max_y_) game_map_.max_y_ = i;
                }
            }
        }
        game_map_.start_x_=90;
        game_map_.start_y_=45;

        game_map_.max_x_ = 795;
        game_map_.max_y_ = 645;

        file.close();
    }
}


void MapObject::load_title(SDL_Renderer* screen)
{
        temp.Loadimage_base("Map/Wal/1.png",screen);
}

void MapObject::drawmap(SDL_Renderer* screen)
{

  int map_x=6;
  int map_y=3;


    for(int i=game_map_.start_y_;i<game_map_.max_y_;i+= TILE_SIZE){
        map_y=i/ TILE_SIZE;
        for(int j=game_map_.start_x_;j<game_map_.max_x_ ;j+= TILE_SIZE){
                map_x=j/ TILE_SIZE;
            if (game_map_.tile[map_y][map_x] > 0)
              {
                temp.set_rect(j,i);
                temp.render(screen);
              }
        }
    }
}
