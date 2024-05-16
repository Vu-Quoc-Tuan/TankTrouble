#include "Game.h"

Game::Game()
{
//phần button:
    //menu
    g_button[0].set_rect(318,228);//button single
    g_button[1].set_rect(314,328);//button multiple
    g_button[2].set_rect(335,436);//button help
    g_button[3].set_rect(330,562);//button exit
//    g_button[4].set_rect(837,660);//button rank    chux suawr

    //help
    g_button[5].set_rect(0,620);//button return

    //pause
    g_button[6].set_rect(334,297);//button restart
    g_button[7].set_rect(372,366);//button continue
    g_button[8].set_rect(411,296);//button home
    g_button[9].set_rect(493,296);//button music

    //end game
    g_button[10].set_rect(363,283);//button restart
    g_button[11].set_rect(389,377);//button home
    g_button[12].set_rect(394,454);//button exit

    //in match
    g_button[13].set_rect(0,0);//button pause

//phần Text:
    //score in single
    g_text[0].set_color(0,0,0);
    g_text[6].set_color(0,0,0);

    //score in multiple
    g_text[1].set_color(0,0,0);
    g_text[2].set_color(0,0,0);

    //score in end
    g_text[3].set_color(0,0,0);
    g_text[4].set_color(0,0,0);

    //high score
    g_text[5].set_color(0,0,0);
}

Game::~Game()
{
    g_sound.~Sound();
}

void Game::set_render(SDL_Renderer* screen)
{
    renderer=screen;

    g_player.set_player2(true);
    g_player.Loadimage_main(renderer);

    bomb.load_ex(renderer);
    bomb.set_clip();

//armor
    armor_tank[0].Loadimage_base("Image/bullet/armor.png",renderer);
    armor_tank[0].set_rect(829,582);//xanh
    armor_tank[1].Loadimage_base("Image/bullet/armor.png",renderer);
    armor_tank[1].set_rect(14,582);//đỏ

//score
    g_text[4].Loadtext("HIGH SCORE!",renderer,Font3);

// black hold
    hole[0].Loadimage_base("Image/kit/hole1.png",renderer);
    hole[0].set_rect(100,244);
    hole[1].Loadimage_base("Image/kit/hole2.png",renderer);
    hole[1].set_rect(700,210);
}


OPTION Game::Show_menu()
{
    g_sound.Playintro();
    Graphics bgr;
    bgr.Loadimage_base("Image/background/start.png",renderer);
    bgr.setforbackground();

    int status=4;
    int dem=1;
    int mouse_X,mouse_Y;

    OPTION res=OPTION::NO;
    while(res==NO)
    {
        SDL_RenderClear(renderer);

        g_button[0].Loadimage_base("Image/background/button/menu11.png",renderer);
        g_button[1].Loadimage_base("Image/background/button/menu21.png",renderer);
        g_button[2].Loadimage_base("Image/background/button/menu31.png",renderer);
        g_button[3].Loadimage_base("Image/background/button/menu41.png",renderer);
//        g_button[4].Loadimage_base("Image/background/button/menu51.png",renderer);

        while(SDL_PollEvent(&events)!=0)
        {
            switch (events.type)
            {
                case SDL_QUIT:
                    return OPTION::EXIT_GAME;
                case SDL_MOUSEMOTION:
                    mouse_X=events.motion.x;
                    mouse_Y=events.motion.y;
                    dem=1;
                    for(int i=0;i<status;i++)
                    {
                        SDL_Rect temp=g_button[i].get_rect_();
                        if(Extension::pointed_to(mouse_X,mouse_Y,temp))
                        {
                            g_button[i].Loadimage_base(("Image/background/button/menu"+std::to_string(dem)+"2.png").c_str(),renderer);
                        }else{
                            g_button[i].Loadimage_base(("Image/background/button/menu"+std::to_string(dem)+"1.png").c_str(),renderer);
                        }
                        dem++;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    mouse_X=events.motion.x;
                    mouse_Y=events.motion.y;
                    dem=1;
                    for(int i=0;i<status;i++)
                    {
                        SDL_Rect temp=g_button[i].get_rect_();
                        if(Extension::pointed_to(mouse_X,mouse_Y,temp))
                        {
                            g_sound.PlayClick();
                            if(i==0){
                                res= OPTION::SINGLEPLAYER;
                                g_button[0].Loadimage_base("Image/background/button/menu13.png",renderer);
                            }
                            else if(i==1){
                                res= OPTION::MULTIPLAYER;
                                g_button[1].Loadimage_base("Image/background/button/menu23.png",renderer);
                            }
                            else if(i==2){
                                res= OPTION::HELP;
                                g_button[2].Loadimage_base("Image/background/button/menu33.png",renderer);
                            }
                            else if(i==4){
                                res= OPTION::RANK;
                                g_button[4].Loadimage_base("Image/background/button/menu53.png",renderer);
                            }
                            else if(i==3){
                                res= OPTION::EXIT_GAME;
                                g_button[3].Loadimage_base("Image/background/button/menu43.png",renderer);
                            }
                        }else{
                            g_button[i].Loadimage_base(("Image/background/button/menu"+std::to_string(dem)+"1.png").c_str(),renderer);
                        }
                        dem++;
                    }
                    break;
            }
        }
        bgr.render(renderer);
        for(int i=0;i<status;i++) g_button[i].render(renderer);

        SDL_RenderPresent(renderer);
    }
    g_sound.Haltmusic();
    return res;
}

OPTION Game::Show_help()
{
    Graphics i_help;
    i_help.Loadimage_base("Image/background/help.png", renderer);
    i_help.setforbackground();

    int mouse_X,mouse_Y;
    OPTION res=OPTION::NO;

    while (res==NO) {
        SDL_RenderClear(renderer);

        g_button[5].Loadimage_base("Image/background/button/help1.png",renderer);

        while (SDL_PollEvent(&events)!=0) {
            switch (events.type)
            {
                case SDL_QUIT:
                    return OPTION::EXIT_GAME;
                case SDL_MOUSEMOTION:{
                    mouse_X=events.motion.x;
                    mouse_Y=events.motion.y;
                    SDL_Rect temp=g_button[5].get_rect_();

                    if(Extension::pointed_to(mouse_X,mouse_Y,temp))
                    {
                        g_button[5].Loadimage_base("Image/background/button/help2.png",renderer);
                    }else{
                        g_button[5].Loadimage_base("Image/background/button/help1.png",renderer);
                    }
                    break;}

                case SDL_MOUSEBUTTONDOWN:
                    mouse_X=events.button.x;
                    mouse_Y=events.button.y;
                    SDL_Rect temp=g_button[5].get_rect_();

                    if(Extension::pointed_to(mouse_X,mouse_Y,temp))
                    {
                        g_sound.PlayClick();
                        res=OPTION::HOME;
                        g_button[5].Loadimage_base("Image/background/button/help3.png",renderer);
                    }else{
                        g_button[5].Loadimage_base("Image/background/button/help1.png",renderer);
                    }
                    break;
            }
        }
        i_help.render(renderer);
        g_button[5].render(renderer);
        SDL_RenderPresent(renderer);
    }
    return res;
}

OPTION Game::End_game()
{
    g_sound.PlayOuttro();

    if(g_score!=0) g_text[3].Loadtext("GAME OVER",renderer,Font4);
    else {
        if(score_1==5) g_text[3].Loadtext("PLAYER-1 WIN",renderer,Font4);
        else if(score_2==5) g_text[3].Loadtext("PLAYER-2 WIN",renderer,Font4);
        else  g_text[3].Loadtext("GAME OVER",renderer,Font4);
    }

    int status_begin=10;
    int status_end=12;

    int mouse_X, mouse_Y;
    OPTION res=OPTION::NO;

    while(res==NO)
    {

        g_button[10].Loadimage_base("Image/background/button/end11.png",renderer);
        g_button[11].Loadimage_base("Image/background/button/end21.png",renderer);
        g_button[12].Loadimage_base("Image/background/button/end31.png",renderer);

        while(SDL_PollEvent(&events)!=0)
        {
            switch(events.type)
            {
                case SDL_QUIT:
                    return OPTION::EXIT_GAME;
                case SDL_MOUSEMOTION :{
                    mouse_X=events.motion.x;
                    mouse_Y=events.motion.y;
                    int dem=1;

                    for(int i=status_begin;i<=status_end;i++)
                    {
                        SDL_Rect temp=g_button[i].get_rect_();
                        if(Extension::pointed_to(mouse_X,mouse_Y,temp))
                        {
                            g_button[i].Loadimage_base(("Image/background/button/end"+std::to_string(dem)+"2.png").c_str(),renderer);
                        }else{
                            g_button[i].Loadimage_base(("Image/background/button/end"+std::to_string(dem)+"1.png").c_str(),renderer);
                        }
                        dem++;
                    }
                    break;}

                case SDL_MOUSEBUTTONDOWN:
                    mouse_X=events.button.x;
                    mouse_Y=events.button.y;
                    int dem=1;

                    for(int i=status_begin;i<=status_end;i++)
                    {
                        SDL_Rect temp=g_button[i].get_rect_();
                        if(Extension::pointed_to(mouse_X,mouse_Y,temp))/////
                        {
                            g_sound.PlayClick();
                            if(i==10)      {
                                    if(score_1==5 || score_2==5) res=OPTION::MULTIPLAYER;
                                    else res=OPTION::SINGLEPLAYER;
                            }
                            else if(i==11) res=OPTION::HOME;
                            else if(i==12) res=OPTION::EXIT_GAME;
                            g_button[i].Loadimage_base(("Image/background/button/end"+std::to_string(dem)+"3.png").c_str(),renderer);
                        }else{
                            g_button[i].Loadimage_base(("Image/background/button/end"+std::to_string(dem)+"1.png").c_str(),renderer);
                        }
                        dem++;
                    }
                    break;
            }
        }

        g_text[3].render_text(315,223,renderer);

        if(Extension::check_highscore(g_score))
        {
            g_text[4].render_text(650,30,renderer);
            Extension::save_score(g_score);
        }

        for(int i=status_begin;i<=status_end;i++) g_button[i].render(renderer);

        SDL_RenderPresent(renderer);
    }
    g_sound.Haltmusic();
    return res;
}

OPTION Game::Pause_game()
{
    Graphics temp;
    temp.Loadimage_base("Image/background/button/pause.png",renderer);
    temp.set_rect(358,214);

    int status_begin=6;
    int status_end=9;
    int mouse_X, mouse_Y;
    int dem=1;

    OPTION res=OPTION::NO;
    while(res==NO)
    {
        dem=1;
        for(int i=status_begin;i<=status_end;i++){
            g_button[i].Loadimage_base(("Image/background/button/pause"+std::to_string(dem)+"1.png").c_str(),renderer);
            dem++;
        }

        while(SDL_PollEvent(&events)!=0)
        {
            switch(events.type)
            {
                case SDL_QUIT:
                    return OPTION::EXIT_GAME;
                case SDL_MOUSEMOTION :{
                    mouse_X=events.motion.x;
                    mouse_Y=events.motion.y;
                    dem=1;

                    for(int i=status_begin;i<=status_end;i++)
                    {
                        SDL_Rect temp=g_button[i].get_rect_();
                        if(Extension::pointed_to(mouse_X,mouse_Y,temp))
                        {
                            g_button[i].Loadimage_base(("Image/background/button/pause"+std::to_string(dem)+"2.png").c_str(),renderer);
                        }else{
                            g_button[i].Loadimage_base(("Image/background/button/pause"+std::to_string(dem)+"1.png").c_str(),renderer);
                        }
                        dem++;
                    }
                    break;}

                case SDL_MOUSEBUTTONDOWN:
                    mouse_X=events.button.x;
                    mouse_Y=events.button.y;
                    dem=1;

                    for(int i=status_begin;i<=status_end;i++)
                    {
                        SDL_Rect temp=g_button[i].get_rect_();
                        if(Extension::pointed_to(mouse_X,mouse_Y,temp))/////
                        {
                            g_sound.PlayClick();
                            if(i==6)      res=OPTION::REPLAY;
                            else if(i==7) res=OPTION::CONTINUE;
                            else if(i==8) res=OPTION::HOME;
                            else if(i==9) {
                                if(g_sound.checkmusic()>0) g_sound.mute();
                                else g_sound.unmute();
                            }
                            g_button[i].Loadimage_base(("Image/background/button/pause"+std::to_string(dem)+"3.png").c_str(),renderer);
                        }else{
                            g_button[i].Loadimage_base(("Image/background/button/pause"+std::to_string(dem)+"1.png").c_str(),renderer);
                        }
                        dem++;
                    }
                    break;
            }
        }

        temp.render(renderer);
        for(int i=status_begin;i<=status_end;i++)
            g_button[i].render(renderer);

        SDL_RenderPresent(renderer);
    }
    return res;
}

OPTION Game::Play_single()
{
    Reset_game();

    Graphics back_ground;
    back_ground.Loadimage_base("Image/background/multiple.png",renderer);
    back_ground.setforbackground();

    g_player.set_player2(false);

    game_map.load_map(rand() %2);
    game_map.load_title(renderer);
    Map map_data= game_map.get_datamap();

    int mouse_X, mouse_Y;

    int spawnTime=0;
    int itemspawn=0;

//    g_time.Start();

    OPTION res= OPTION::NO;

    while(res==NO)
    {
        int staticks=SDL_GetTicks64();
        g_text[0].Loadtext("SCORE:"+std::to_string(g_score),renderer,Font3);
        g_text[6].Loadtext("HP:"+ std::to_string(hp),renderer,Font3);
        g_button[13].Loadimage_base("Image/background/button/ingame1.png",renderer);


        while(SDL_PollEvent(&events)!=0)
        {
            switch (events.type){
                case SDL_QUIT:
                    return OPTION::EXIT_GAME;
                case SDL_MOUSEMOTION:{
                    mouse_X=events.motion.x;
                    mouse_Y=events.motion.y;

                    SDL_Rect temp=g_button[13].get_rect_();

                    if(Extension::pointed_to(mouse_X,mouse_Y,temp))
                    {
                        g_button[13].Loadimage_base("Image/background/button/ingame2.png",renderer);
                    }else{
                        g_button[13].Loadimage_base("Image/background/button/ingame1.png",renderer);
                    }
                    break;}

                case SDL_MOUSEBUTTONDOWN:
                    mouse_X=events.button.x;
                    mouse_Y=events.button.y;

                    SDL_Rect temp=g_button[13].get_rect_();
                    if(Extension::pointed_to(mouse_X,mouse_Y,temp))
                    {
                        g_sound.PlayClick();
                        OPTION current = Pause_game();
                        if(current==REPLAY)     res= OPTION::SINGLEPLAYER;
                        else if(current==HOME)  res=OPTION::HOME;
                    }

                    break;

            }
            g_player.fire_action(renderer,&g_sound);
        }

        spawnTime++;
        if(spawnTime>60 && list_threat.size()<=7)
        {
            list_threat.push_back(spawnMonster());
            spawnTime=0;
        }
        down_hp();
        itemspawn++;
        if(itemspawn>100 && list_item.size()<=3)
        {
            list_item.push_back(spawn_item());
            itemspawn=0;
        }
        flash();

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);

        back_ground.render(renderer);
        game_map.drawmap(renderer);


        g_text[0].render_text(740,5,renderer);

        load_threat();
        load_item  (map_data);
        upgrade();
        delete_threat();

        hole[0].render(renderer);
        hole[1].render(renderer);

        g_player.draw_bullet(renderer,map_data);
        g_player.Show(renderer);

        g_button[13].render(renderer);

        draw_hp();
        g_text[6].render_text(SCREEN_WIDTH/2-20,18,renderer);

        if(armor1) armor_tank[1].render(renderer);

        SDL_RenderPresent(renderer);
        if(hp<=0) res=End_game();

        int frame_tick=SDL_GetTicks64()-staticks;
        if(frame_tick<1000/FPS){
          SDL_Delay(1000/FPS-frame_tick);
        }

        g_player.Update_action(renderer,map_data);

    }
    return res;
}

OPTION Game::Play_mutile()
{
    Reset_game();

    Graphics back_ground;
    back_ground.Loadimage_base("Image/background/multiple.png",renderer);
    back_ground.setforbackground();

    g_player.set_player2(true);

    game_map.load_map(rand() %2);
    game_map.load_title(renderer);
    Map map_data= game_map.get_datamap();

    int itemspawn=0;
    int mouse_X, mouse_Y;

    OPTION res= OPTION::NO;

    while(res==NO)
    {
        int staticks=SDL_GetTicks64();

        if(score_value1!=0) {
            score_1+=1;
            score_value1=0;
        }
        if(score_value2!=0)
        {
            score_2+=1;
            score_value2=0;
        }
        g_text[1].Loadtext(std::to_string(score_1),renderer,Font3);
        g_text[2].Loadtext(std::to_string(score_2),renderer,Font3);
        g_button[13].Loadimage_base("Image/background/button/ingame1.png",renderer);

        while(SDL_PollEvent(&events)!=0)
        {
            switch (events.type){
                case SDL_QUIT:
                    return OPTION::EXIT_GAME;

                case SDL_MOUSEMOTION:{
                    mouse_X=events.motion.x;
                    mouse_Y=events.motion.y;

                    SDL_Rect temp=g_button[13].get_rect_();

                    if(Extension::pointed_to(mouse_X,mouse_Y,temp))
                    {
                        g_button[13].Loadimage_base("Image/background/button/ingame2.png",renderer);
                    }else{
                        g_button[13].Loadimage_base("Image/background/button/ingame1.png",renderer);
                    }
                    break;}

                case SDL_MOUSEBUTTONDOWN:
                    mouse_X=events.button.x;
                    mouse_Y=events.button.y;

                    SDL_Rect temp=g_button[13].get_rect_();
                    if(Extension::pointed_to(mouse_X,mouse_Y,temp))
                    {
                        g_sound.PlayClick();
                        OPTION current = Pause_game();
                        if(current==REPLAY)     res= OPTION::MULTIPLAYER;
                        else if(current==HOME)  res=OPTION::HOME;
                    }

                    break;

            }
            g_player.fire_action(renderer,&g_sound);
        }

        itemspawn++;
        if(itemspawn>150 && list_item.size()<=3)
        {
            list_item.push_back(spawn_item());
            itemspawn=0;
        }
        flash();

        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);

        back_ground.render(renderer);
        game_map.drawmap(renderer);

        load_item(map_data);
        upgrade();
        hole[0].render(renderer);
        hole[1].render(renderer);

        g_player.draw_bullet(renderer,map_data);
        g_player.Show(renderer);

        g_text[1].render_text(80,647,renderer);
        g_text[2].render_text(782,647,renderer);

        g_button[13].render(renderer);

        if(armor1) armor_tank[1].render(renderer);
        if(armor2) armor_tank[0].render(renderer);

        get_point_multiple();
        SDL_RenderPresent(renderer);
        if(score_1==5 || score_2==5) res=End_game();

        int frame_tick=SDL_GetTicks64()-staticks;
        if(frame_tick<1000/FPS){
          SDL_Delay(1000/FPS-frame_tick);
        }

        g_player.Update_action(renderer,map_data);
        if(is_dead){
            g_player.set_rect_player1(138,75);
            g_player.set_rect_player2(735,585);
            g_player.delete_bullet(0,1);
            g_player.delete_bullet(0,2);
            is_dead=false;
        }
    }
    return res;
}



void Game::Reset_game()
{
    is_dead=false;
    g_score=0;
    score_1=0;
    score_2=0;
    score_value1=0;
    score_value2=0;
    hp= 20;

    g_player.set_type_bullet1(normal);
    g_player.set_type_bullet2(normal);
    g_player.delete_bullet(0,1);
    g_player.delete_bullet(0,2);

    g_player.set_rect_player1(138,75);
    g_player.set_rect_player2(735,585);

    is_flash1=false;
    is_flash2=false;

    armor1=false;
    armor2=false;
    list_item.clear();
    list_threat.clear();
}

void Game::Start()
{
    OPTION current_option=Show_menu();
    do
    {
        switch (current_option)//add setting if it is posible and high score
        {
            case OPTION::EXIT_GAME :
                return;
            case OPTION::HELP :
                current_option=Show_help();
                break;
            case OPTION::HOME :
                //reset lại
                current_option=Show_menu();
                break;
            case OPTION::SINGLEPLAYER :
                Reset_game();
                current_option=Play_single();
                break;
            case OPTION::MULTIPLAYER :
                Reset_game();
                current_option=Play_mutile();
                break;

            default:
                current_option=OPTION::EXIT_GAME;
                break;
        }

    }while(true);
}




void Game::load_item(const Map& map_data)
{
    int i=0;
    for(item &temp: list_item)
    {
        temp.load_image_item(renderer);
        if(
            (map_data.tile[(temp.get_rect_().y-5)/TILE_SIZE][(temp.get_rect_().x-5)/TILE_SIZE]==1 ||
            map_data.tile[(temp.get_rect_().y+temp.get_rect_().h+5)/TILE_SIZE][(temp.get_rect_().x-5)/TILE_SIZE]==1 ||
            map_data.tile[(temp.get_rect_().y-5)/TILE_SIZE][(temp.get_rect_().x+temp.get_rect_().w+5)/TILE_SIZE]==1 ||
            map_data.tile[(temp.get_rect_().y+temp.get_rect_().h+5)/TILE_SIZE][(temp.get_rect_().x+temp.get_rect_().w+5)/TILE_SIZE]==1)
            )
              list_item.erase(list_item.begin()+i);
        temp.show_item(renderer);
        i++;
    }
}

item Game::spawn_item()
{
    g_sound.PlaySpawn();
    item temp;
    temp.set_distination(game_map.get_datamap());
    temp.set_type();
    return temp;
}
void Game::upgrade()
{
    if (!list_item.empty()) {
        for (auto it = list_item.begin(); it!= list_item.end();) {
            if (detail::check_collision(it->get_rect_(), g_player.get_rect_player1())) {
                g_sound.PlayCollect();
                g_player.set_type_bullet1(it->get_type());
                if(it->get_type()==armor) armor1=true;
                it = list_item.erase(it);
            } else if (detail::check_collision(it->get_rect_(), g_player.get_rect_player2())) {
                g_sound.PlayCollect();
                g_player.set_type_bullet2(it->get_type());
                if(it->get_type()==armor) armor2=true;
                it = list_item.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void Game::load_threat()
{
    for(Threat_object &threat: list_threat){
        threat.Loadimage_monster(renderer);
        threat.set_clip();
        threat.domonster(g_player.get_rect_player1().x,g_player.get_rect_player1().y);
        threat.Show(renderer);
    }
}

Threat_object Game::spawnMonster()
{
    Threat_object monster;
    int x = rand() % SCREEN_WIDTH;
    int y = rand() % SCREEN_HEIGHT;
    monster.set_destination(x,y);
    return monster;
}

void Game::delete_threat()
{
    std::vector<BulletObject*> list1 = g_player.get_list1_();

    for (size_t i = 0; i < list_threat.size(); ) {
        Threat_object& temp1 = list_threat.at(i);

        for (size_t j = 0; j < list1.size(); ) {
            BulletObject* temp2 = list1.at(j);

            if (detail::check_collision(temp1.get_rect_threat(), temp2->get_rect_())) {
                g_score++;

                bomb.set_rect(temp2->get_rect_().x,temp2->get_rect_().y);
                bomb.Show_ex(renderer);

                temp2->set_move(false);
                list1.erase(list1.begin() + j);
                list_threat.erase(list_threat.begin() + i);
            } else {
                ++j;
            }
        }

        if (i < list_threat.size()) {
            ++i;
        }
    }
}

void Game::down_hp()
{
    for(int i=0;i<(int)list_threat.size();i++)
    {
        Threat_object temp= list_threat.at(i);
        if(detail::check_insize(temp.get_rect_threat(),g_player.get_rect_player1()))
        {
            if(!armor1) hp-=1;
            armor1=false;
            list_threat.erase(list_threat.begin()+i);
        }
    }
}

void Game::draw_hp()
{
    SDL_Rect line_bar={280,18,360,24};
    SDL_RenderDrawRect(renderer,&line_bar);
    SDL_Rect heal_bar={280,18,hp*18,24};
    SDL_SetRenderDrawColor(renderer,250,0,0,0);
    SDL_RenderFillRect(renderer,&heal_bar);
}

void Game::get_point_multiple()
{
    std::vector<BulletObject*> list1 = g_player.get_list1_();
    std::vector<BulletObject*> list2 = g_player.get_list2_();

    for (size_t j = 0; j < list1.size(); ) {
        BulletObject* temp1 = list1.at(j);

        if(temp1->get_type_bullet()==rocket && detail::get_distance(temp1->get_rect_(), g_player.get_rect_player2())>=300)
        {
            g_sound.PlayT_dead();
            bomb.set_rect(g_player.get_rect_player1().x,g_player.get_rect_player1().y);
            bomb.Show_ex(renderer);

            is_dead=true;

            if(armor1){
                score_2--;
            }
            score_value2++;
            armor1=false;
            g_player.delete_bullet(j,1);
            list1.erase(list1.begin() + j);
        }

        if (detail::check_collision(temp1->get_rect_(), g_player.get_rect_player1())
            && temp1->getDistanceFromSpawnPoint()>MIN_DISTANCE_FROM_SPAWN_POINT) {
            g_sound.PlayT_dead();
            bomb.set_rect(g_player.get_rect_player1().x,g_player.get_rect_player1().y);
            bomb.Show_ex(renderer);

            is_dead=true;

            if(armor1){
                score_2--;
            }
            score_value2++;
            armor1=false;
            g_player.delete_bullet(j,1);
            list1.erase(list1.begin() + j);
        } else if (detail::check_collision(temp1->get_rect_(), g_player.get_rect_player2())
                   && temp1->getDistanceFromSpawnPoint()>MIN_DISTANCE_FROM_SPAWN_POINT) {
            g_sound.PlayT_dead();
            bomb.set_rect(g_player.get_rect_player2().x,g_player.get_rect_player2().y);
            bomb.Show_ex(renderer);

            is_dead=true;

            if(armor2){
                score_1--;
            }
            score_value1++;
            armor2=false;
            g_player.delete_bullet(j,1);
            list1.erase(list1.begin() + j);
        }else j++;
    }
    for (size_t i = 0; i < list2.size(); ) {
        BulletObject* temp2 = list2.at(i);

        if(temp2->get_type_bullet()==rocket && detail::get_distance(temp2->get_rect_(), g_player.get_rect_player1())>=300)
        {
            g_sound.PlayT_dead();
            bomb.set_rect(g_player.get_rect_player2().x,g_player.get_rect_player2().y);
            bomb.Show_ex(renderer);

            is_dead=true;

            if(armor2){
                score_1--;
            }
            score_value1++;
            armor2=false;
            g_player.delete_bullet(i,2);
            list2.erase(list2.begin() + i);
        }

        if (detail::check_collision(temp2->get_rect_(), g_player.get_rect_player1())
            && temp2->getDistanceFromSpawnPoint()>MIN_DISTANCE_FROM_SPAWN_POINT) {
            g_sound.PlayT_dead();
            bomb.set_rect(g_player.get_rect_player1().x,g_player.get_rect_player1().y);
            bomb.Show_ex(renderer);

            is_dead=true;

            if(armor1){
                score_2--;
            }
            score_value2++;
            armor1=false;
            g_player.delete_bullet(i,2);
            list2.erase(list2.begin() + i);
        } else if (detail::check_collision(temp2->get_rect_(), g_player.get_rect_player2())
                   && temp2->getDistanceFromSpawnPoint()>MIN_DISTANCE_FROM_SPAWN_POINT) {
            g_sound.PlayT_dead();
            bomb.set_rect(g_player.get_rect_player2().x,g_player.get_rect_player2().y);
            bomb.Show_ex(renderer);

            is_dead=true;

            if(armor2){
                score_1--;
            }
            score_value1++;
            armor2=false;
            g_player.delete_bullet(i,2);
            list2.erase(list2.begin() + i);
        }else i++;
    }
}

void Game::flash()
{
    if(detail::check_collision(hole[0].get_rect_(),g_player.get_rect_player1())&& !is_flash1)
    {
        is_flash1=true;
        g_player.set_rect_player1(hole[1].get_rect_().x,hole[1].get_rect_().y);
    }
    else if(detail::check_collision(hole[1].get_rect_(),g_player.get_rect_player1())&& !is_flash1)
    {
        is_flash1=true;
        g_player.set_rect_player1(hole[0].get_rect_().x,hole[0].get_rect_().y);
    }else{
        //is_flash1=false;
    }


    if(detail::check_collision(hole[0].get_rect_(),g_player.get_rect_player2())&& !is_flash2)
    {
        is_flash2=true;
        g_player.set_rect_player2(hole[1].get_rect_().x,hole[1].get_rect_().y);
    }
    else if(detail::check_collision(hole[1].get_rect_(),g_player.get_rect_player2())&& !is_flash2)
    {
        is_flash2=true;
        g_player.set_rect_player2(hole[0].get_rect_().x,hole[0].get_rect_().y);
    }else{
        //is_flash2=false;
    }
}
