#include "Player.h"

Player::Player()
{
    x_pos_=150;         x_pos2_=200;
    y_pos_=80;          y_pos2_=80;
    x_value_=0;         x_value2_=0;
    y_value_=0;         y_value2_=0;
    angle=0;            angle2=0;
    texture=NULL;       texture2=NULL;
    rect_.x=0;          rect2_.x=0;
    rect_.y=0;          rect2_.y=0;
    rect_.w=0;          rect2_.h=0;
    rect_.h=0;          rect2_.w=0;
    type_bullet=normal; appear=false;
                        type_bullet2=normal;
}

bool Player::Loadimage_main(SDL_Renderer* renderer)
{
    texture = IMG_LoadTexture(renderer, "Image/tank/player11.png");
        if (texture == NULL){
            std::cerr << "Unable to create texture from " << "Image/tank/player11.png" << "! SDL Error: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_QueryTexture(texture, NULL, NULL, &rect_.w, &rect_.h);

    if(appear){
        texture2 = IMG_LoadTexture(renderer, "Image/tank/player12.png");
            if (texture2 == NULL){
                std::cerr << "Unable to create texture from " << "Image/tank/player12.png" << "! SDL Error: " << SDL_GetError() << std::endl;
                return false;
            }

            SDL_QueryTexture(texture2, NULL, NULL, &rect2_.w, &rect2_.h);
    }
    return true;
}

void Player::Update_action(SDL_Renderer* screen, const Map& map_data)
{
    x_value_=0;                             x_value2_=0;
    y_value_=0;                             y_value2_=0;
    float radians = angle * PI / 180.0f;    float radians2 = angle2 * PI / 180.0f;

    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
//xe1
    if (currentKeyStates[SDL_SCANCODE_A] ){
        angle=(angle+ROTATION_SPEED);
        angle= fmodf(angle, 360.0f);
    }
    else if (currentKeyStates[SDL_SCANCODE_D] ){
        angle=(angle-ROTATION_SPEED+360);
        angle= fmodf(angle, 360.0f);
    }

    if (currentKeyStates[SDL_SCANCODE_W] ){
        y_value_+=cos(radians)*TANK_SPEED;
        x_value_-=sin(radians)*TANK_SPEED;
    }
    else if (currentKeyStates[SDL_SCANCODE_S] ){
        y_value_-=cos(radians)*TANK_SPEED;
        x_value_+=sin(radians)*TANK_SPEED;
    }

//xe2
    if (currentKeyStates[SDL_SCANCODE_RIGHT] ){
        angle2=(angle2+ROTATION_SPEED);
        angle2= fmodf(angle2, 360.0f);
    }
    else if (currentKeyStates[SDL_SCANCODE_LEFT] ){
        angle2=(angle2-ROTATION_SPEED+360);
        angle2= fmodf(angle2, 360.0f);
    }

    if (currentKeyStates[SDL_SCANCODE_UP] ){
        y_value2_+=cos(radians2)*TANK_SPEED;
        x_value2_-=sin(radians2)*TANK_SPEED;
    }
    else if (currentKeyStates[SDL_SCANCODE_DOWN] ){
        y_value2_-=cos(radians2)*TANK_SPEED;
        x_value2_+=sin(radians2)*TANK_SPEED;
    }

    checkToMap(map_data);
}

void Player::fire_action( SDL_Renderer* screen, Sound* p_sound)
{
    const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
    float radians = angle * PI / 180.0f;        float radians2 = angle2 * PI / 180.0f;

//xe1
    if(currentKeyStates[SDL_SCANCODE_V]){
        p_sound->PlayFire();
        float mid_x=x_pos_+rect_.w/2-5;
        float mid_y=y_pos_+rect_.h/2-3;
        float heal_y  =y_pos_+rect_.h;
        float bullet_x=-(heal_y-mid_y)*sin(radians)+mid_x;
        float bullet_y=+(heal_y-mid_y)*cos(radians)+mid_y;//tính tọa độ sau góc quay

        BulletObject* bullet_temp=new BulletObject;
        bullet_temp->set_type_bullet(type_bullet);
        bullet_temp->load_image_bullet(screen);
        bullet_temp->set_rect(bullet_x+sin(radians)*BULLET_SPEED*2,bullet_y-cos(radians)*BULLET_SPEED*2);
        bullet_temp->set_move(true);
        bullet_temp->set_angle_bullet(angle);

        if(bullet_list.size()==0) bullet_list.push_back(bullet_temp);
        else delete bullet_temp;
    }

//xe2
    if(appear){
        if(currentKeyStates[SDL_SCANCODE_M]){
            p_sound->PlayFire();
            float mid2_x=x_pos2_+rect2_.w/2-5;
            float mid2_y=y_pos2_+rect2_.h/2-3;
            float heal2_y  =y_pos2_+rect2_.h;
            float bullet2_x=-(heal2_y-mid2_y)*sin(radians2)+mid2_x;
            float bullet2_y=+(heal2_y-mid2_y)*cos(radians2)+mid2_y;//tính tọa độ sau góc quay

            BulletObject* bullet_temp2=new BulletObject;
            bullet_temp2->set_type_bullet(type_bullet2);
            bullet_temp2->load_image_bullet(screen);
            bullet_temp2->set_rect(bullet2_x+sin(radians2)*BULLET_SPEED*2,bullet2_y-cos(radians2)*BULLET_SPEED*2);
            bullet_temp2->set_move(true);
            bullet_temp2->set_angle_bullet(angle2);

            if(bullet_list2.size()==0) bullet_list2.push_back(bullet_temp2);
            else delete bullet_temp2;
        }
    }
}

void Player::checkToMap(const Map& map_data)
{
//xe1
    int x1(0),x2(0),x3(0);
    int y1(0),y2(0),y3(0);

int height_min=rect_.h> TILE_SIZE ? rect_.h : TILE_SIZE;

    x1=(x_pos_+ x_value_)/TILE_SIZE;
    x2=(x_pos_+ x_value_+ rect_.w-1)/TILE_SIZE;

    y1=(y_pos_)/TILE_SIZE;
    y2=(y_pos_+ height_min -1)/TILE_SIZE;
    y3=(y_pos_+ height_min/2 -1)/TILE_SIZE;


    if(x1>=tile_startX && x2<tile_endX && y1>=tile_startY && y2<tile_endY)//max,min của map_data
    {
        if(x_value_>0){

            if(map_data.tile[y1][x2]!=0 || map_data.tile[y2][x2]!=0 || map_data.tile[y3][x2]!=0)
            {
//                x_pos_=x2*TILE_SIZE;
//                x_pos_-=rect_.w+1;
                x_value_=0;
            }
        }else if(x_value_<0){

            if(map_data.tile[y1][x1]!=0 || map_data.tile[y2][x1]!=0 || map_data.tile[y3][x1]!=0)
            {
//                x_pos_=(x1+1)*TILE_SIZE;
                x_value_=0;
            }
        }
    }
int weight_min=rect_.w > TILE_SIZE ? rect_.w : TILE_SIZE;
    x1=(x_pos_)/TILE_SIZE;
    x2=(x_pos_+weight_min)/TILE_SIZE;
    x3=(x_pos_+weight_min/2)/TILE_SIZE;

    y1=(y_pos_+y_value_)/TILE_SIZE;
    y2=(y_pos_+y_value_+rect_.h-1)/TILE_SIZE;

    if(x1>=tile_startX && x2<tile_endX && y1>=tile_startY && y2<tile_endY)
    {
        if(y_value_>0){

            if(map_data.tile[y2][x1]!=0 || map_data.tile[y2][x2]!=0 || map_data.tile[y2][x3]!=0)
            {
//                y_pos_=y2*TILE_SIZE;
//                y_pos_-=rect_.h+1;
                y_value_=0;
            }

        }else if(y_value_<0){

            if(map_data.tile[y1][x1]!=0 || map_data.tile[y1][x2]!=0 || map_data.tile[y1][x3]!=0)
            {
                y_value_=0;
//                y_pos_=(y1+1)*TILE_SIZE;
            }
        }
    }

    x_pos_+=x_value_;
    y_pos_+=y_value_;

    if(x_pos_<0){
        x_pos_=0;
    }
    if(y_pos_<0){
        y_pos_=0;
    }
    if(x_pos_+rect_.w>map_data.max_x_){
        x_pos_=map_data.max_x_-rect_.w-1;
    }
    if(y_pos_+rect_.h>=map_data.max_y_){
        y_pos_=map_data.max_y_-rect_.h-1;
    }

//xe2
    int x1_(0),x2_(0),x3_(0);
    int y1_(0),y2_(0),y3_(0);

int height2_min=rect2_.h > TILE_SIZE ? rect2_.h : TILE_SIZE;

    x1_=(x_pos2_+ x_value2_)/TILE_SIZE;
    x2_=(x_pos2_+ x_value2_+ rect2_.w-1)/TILE_SIZE;

    y1_=(y_pos2_)/TILE_SIZE;
    y2_=(y_pos2_+ height2_min -1)/TILE_SIZE;
    y3_=(y_pos2_+ height2_min/2 -1)/TILE_SIZE;

    if(x1_>=tile_startX && x2_<tile_endX && y1_>=tile_startY && y2_<tile_endY)//max của  map_data
    {
        if(x_value2_>0){

            if(map_data.tile[y1_][x2_]!=0 || map_data.tile[y2_][x2_]!=0 || map_data.tile[y3_][x2_]!=0)
            {
//                x_pos2_=x2_*TILE_SIZE;
//                x_pos2_-=rect2_.w+1;
                x_value2_=0;
            }
        }else if(x_value2_<0){

            if(map_data.tile[y1_][x1_]!=0 || map_data.tile[y2_][x1_]!=0 || map_data.tile[y3_][x1_]!=0)
            {
//                x_pos2_=(x1_+1)*TILE_SIZE;
                x_value2_=0;
            }
        }
    }
int weight2_min=rect2_.w > TILE_SIZE ? rect2_.w : TILE_SIZE;
    x1_=(x_pos2_)/TILE_SIZE;
    x2_=(x_pos2_+weight2_min)/TILE_SIZE;
    x3_=(x_pos2_+weight2_min/2)/TILE_SIZE;

    y1_=(y_pos2_+y_value2_)/TILE_SIZE;
    y2_=(y_pos2_+y_value2_+rect2_.h-1)/TILE_SIZE;

    if(x1_>=tile_startX && x2_<tile_endX && y1_>=tile_startY && y2_<tile_endY)
    {
        if(y_value2_>0){

            if(map_data.tile[y2_][x1_]!=0 || map_data.tile[y2_][x2_]!=0 || map_data.tile[y2_][x3_]!=0)
            {
//                y_pos2_=y2_*TILE_SIZE;
//                y_pos2_-=rect2_.h+1;
                y_value2_=0;
            }

        }else if(y_value2_<0){

            if(map_data.tile[y1_][x1_]!=0 || map_data.tile[y1_][x2_]!=0 || map_data.tile[y1_][x3_]!=0)
            {
                y_value2_=0;
//                y_pos2_=(y1_+1)*TILE_SIZE;
            }
        }
    }

    x_pos2_+=x_value2_;
    y_pos2_+=y_value2_;

    if(x_pos2_<0){
        x_pos2_=0;
    }
    if(y_pos2_<0){
        y_pos2_=0;
    }
    if(x_pos2_+rect2_.w>map_data.max_x_){
        x_pos2_=map_data.max_x_-rect2_.w-1;
    }
    if(y_pos2_+rect2_.h>=map_data.max_y_){
        y_pos2_=map_data.max_y_-rect2_.h-1;
    }

}
void Player::Show(SDL_Renderer* screen)
{
    rect_.x=x_pos_; rect_.y=y_pos_;      rect2_.x=x_pos2_; rect2_.y=y_pos2_;

    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopyEx(screen, texture, NULL,&renderquad, angle, NULL, SDL_FLIP_NONE);

    if(appear){
        SDL_Rect renderquad2 = {rect2_.x, rect2_.y, rect2_.w, rect2_.h};
        SDL_RenderCopyEx(screen, texture2, NULL,&renderquad2, angle2, NULL, SDL_FLIP_NONE);
    }
}

//BulletObject
void Player::draw_bullet(SDL_Renderer* screen,const Map& map_data)
{
    for(int i=0;i<(int)bullet_list.size();i++){
        BulletObject* bullet_now=bullet_list[i];
        if(bullet_now!=NULL){
            if(bullet_now->get_move()){
                bullet_now->control_bullet(map_data, x_pos2_, y_pos2_);
                bullet_now->render_bullet(screen);
                if(type_bullet!=rocket) bullet_now->time_bullet(BULLET_LIFETIME);
            }else{
                delete_bullet(i,1);
            }
        }
    }

    for(int j=0;j<(int)bullet_list2.size();j++){
        BulletObject* bullet2_now=bullet_list2[j];
        if(bullet2_now!=NULL){
            if(bullet2_now->get_move()){
                bullet2_now->control_bullet(map_data, x_pos_,y_pos_);
                bullet2_now->render_bullet(screen);
                if(type_bullet!=rocket) bullet2_now->time_bullet(BULLET_LIFETIME);
            }else{
                delete_bullet(j,2);
            }
        }
    }

}
void Player::delete_bullet(const int& value, const int type)
{
    if(type==1){
        type_bullet=normal;
        int length=bullet_list.size();
        if(length>0 && value<length){
            BulletObject* bullet_temp=bullet_list.at(value);
            bullet_list.erase(bullet_list.begin()+value);
            if(bullet_temp!=NULL){
                delete bullet_temp;
                bullet_temp=NULL;
            }
        }
    }

    if(type==2){
        type_bullet2=normal;
        int length2=bullet_list2.size();
        if(length2>0 && value<length2){
            BulletObject* bullet2_temp=bullet_list2.at(value);
            bullet_list2.erase(bullet_list2.begin()+value);
            if(bullet2_temp!=NULL){
                delete bullet2_temp;
                bullet2_temp=NULL;
            }
        }
    }

}
