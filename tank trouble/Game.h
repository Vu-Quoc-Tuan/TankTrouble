#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "Compact.h"

class Game
{
public:
    Game();
    ~Game();

    void Start();
    void set_render(SDL_Renderer* screen);

private:
    //global
    SDL_Renderer* renderer;

    //load
    MapObject game_map;
    Player g_player;

    int hp;

    //dead
    void down_hp();
    void draw_hp();
    void get_point_multiple();

    bool armor1;
    bool armor2;
    Graphics armor_tank[2];
    bool is_dead;

    //threat
    std::vector<Threat_object> list_threat;
    Threat_object spawnMonster();
    void load_threat();
    void delete_threat();

    //item
    std::vector<item> list_item;
    item spawn_item();
    void load_item(const Map& map_data);
    void upgrade();

    //time
    Timer g_time;

    //score
    unsigned int g_score;
    unsigned int score_1;
    unsigned int score_2;
    unsigned int score_value1;
    unsigned int score_value2;

    //sound
    Sound g_sound;

    //text, button
    LText g_text[8];
    Graphics g_button[15];

    //Explosion
    Explosion bomb;

    //Black hole
    Graphics hole[3];
    void flash();
    bool is_flash1;
    bool is_flash2;

    //method
    OPTION Play_single();
    OPTION Play_mutile();
    OPTION End_game ();
    OPTION Show_menu();
    OPTION Show_help();
    OPTION Pause_game();

    void Reset_game ();
};

#endif // GAME_H_INCLUDED
