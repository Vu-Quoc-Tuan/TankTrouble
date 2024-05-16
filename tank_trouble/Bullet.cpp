#include "Bullet.h"

BulletObject::BulletObject()
{
  //  x_value=0;
  //  y_value=0;
    is_move=false;
    start_time = std::chrono::high_resolution_clock::now();
    angle_bullet=0;

    type_bullet=normal;
    angle_change=0;
    life_rocket=0;
}

bool BulletObject::load_image_bullet(SDL_Renderer* screen)
{
    bool temp;
    if(type_bullet==rocket){
        temp=Graphics::Loadimage_base("Image/bullet/rocket.png",screen);

    }else if(type_bullet==laser){
        temp=Graphics::Loadimage_base("Image/bullet/lazer.png",screen);
    }else{
        temp=Graphics::Loadimage_base("Image/bullet/bullet1.png",screen);
    }
    return temp;
}

void BulletObject::control_bullet(const Map& map_data, int targetX, int targetY)
{
    if(type_bullet==laser)
    {
        through_wall();

    }else if(type_bullet==rocket)
    {
        movent(map_data, targetX, targetY);
//          find_anyone(map_data, targetX, targetY);

    }else {
        Bouncing_bullet(map_data);
    }
}

void BulletObject::through_wall()
{
    float radians=angle_bullet*PI/ 180.0f;
    rect_.x-=sin(radians)*BULLET_SPEED;
    rect_.y+=cos(radians)*BULLET_SPEED;
}

//đang
void BulletObject::find_anyone(const Map& map_data, int targetX, int targetY)
{
    if(std::sqrt((targetX-rect_.x)*(targetX-rect_.x)+(targetY-rect_.y)*(targetY-rect_.y))>=300) return;

    path.clear();

    bool visited[tile_endY][tile_endX] = {{false}};
    std::vector<std::vector<std::pair<int, int>>> parent(tile_endY, std::vector<std::pair<int, int>>(tile_endX));
    int tempX[4] = {0, 0, -1, 1};
    int tempY[4] = {-1, 1, 0, 0};
    std::queue<std::pair<int, int>> wait;
    wait.push({rect_.y / TILE_SIZE, rect_.x / TILE_SIZE});

    while (!wait.empty()) {
        std::pair<int, int> top = wait.front();
        wait.pop();
        visited[top.first][top.second] = true;

        if(top.first==targetY/TILE_SIZE && top.second==targetX/TILE_SIZE) break;

        for (int i = 0; i < 4; i++) {
            int i1 = top.first + tempY[i];
            int j1 = top.second + tempX[i];

            if (i1 >= tile_startY && i1 < tile_endY && j1 >= tile_startX && j1 < tile_endX) {
                if (map_data.tile[i1][j1] == 0 &&!visited[i1][j1]) {
                    parent[i1][j1] = std::make_pair(top.first, top.second);
                    wait.push({i1, j1});
                }
            }
        }
    }


    std::pair<int, int> Newcurrent = {targetY/TILE_SIZE, targetX/TILE_SIZE};
    while (Newcurrent.first >= tile_startY && Newcurrent.first < tile_endY && Newcurrent.second >= tile_startX && Newcurrent.second < tile_endX && Newcurrent!= std::make_pair(rect_.y/TILE_SIZE, rect_.x/TILE_SIZE)) {
        path.push_back(Newcurrent);
        Newcurrent = parent[Newcurrent.first][Newcurrent.second];
    }

    std::reverse(path.begin(), path.end()); // Lật ngược chuỗi để có thứ tự từ start đến end


}
void BulletObject::movent(const Map& map_data, int targetX, int targetY)
{
    life_rocket++;
    if(life_rocket==100) is_move=false;

    float speed = 0.8 * BULLET_SPEED;
    getAngle(map_data, targetX, targetY);

    angle_bullet=angle_bullet+angle_change;
    float radians = angle_bullet*PI/180;

    rect_.x -= sin(radians) * speed;
    rect_.y += cos(radians) * speed;
}

void BulletObject::getAngle(const Map& map_data, int targetX, int targetY)
{
    find_anyone(map_data, targetX, targetY);
    int mouse_angle = 0;

    if (path.empty()) {
        mouse_angle = (int)(atan2(rect_.y - targetY, rect_.x - targetX) * 180.0f / PI);
    } else {

        std::pair<int,int> nextPos = path.front();
        float dentaY=nextPos.first-rect_.y/TILE_SIZE;
        float dentaX=nextPos.second-rect_.x/TILE_SIZE;

        float yOffset=0;
        float xOffset=0;

          if (dentaY == 1)
          {
            yOffset = TILE_SIZE/3;
            xOffset = TILE_SIZE/3;

          } else if (dentaY == -1)
          {
            yOffset = -TILE_SIZE/3;
            xOffset = -TILE_SIZE/3;

          } else if (dentaX == 1)
          {
            yOffset = -TILE_SIZE/3;
            xOffset = TILE_SIZE/3;

          } else
          {
            yOffset = TILE_SIZE/3;
            xOffset = -TILE_SIZE/3;
          }

          mouse_angle = (int)(atan2(rect_.y - (nextPos.first*TILE_SIZE+TILE_SIZE/2+yOffset), rect_.x- (nextPos.second*TILE_SIZE+TILE_SIZE/2+xOffset))* 180/ PI);
    }

    if (mouse_angle < 0) {
        mouse_angle += 360;
    }
    mouse_angle += 90;
    mouse_angle = mouse_angle % 360;
    if (angle_bullet < 0) {
        angle_bullet += 360;
    }
    angle_bullet = angle_bullet % 360;

    float a = (mouse_angle - angle_bullet);
    float b = (mouse_angle - angle_bullet + 360);
    float c = (mouse_angle - angle_bullet - 360);
    float d;
    if (abs(a) < abs(b) && abs(a) < abs(c)) {
        d = a;
    } else if (abs(b) < abs(a) && abs(b) < abs(c)) {
        d = b;
    } else {
        d = c;
    }
    if (d < 0) {
        angle_change = -ROTATION_SPEED;
    } else {
        angle_change = ROTATION_SPEED;
    }
}



void BulletObject::Bouncing_bullet(const Map& map_data)
{
  float radians = angle_bullet * PI / 180.0f;


  float newx = rect_.x - sin(radians) * BULLET_SPEED;
  float newy = rect_.y + cos(radians) * BULLET_SPEED;

//kiểm tra vc
  bool quit=false;//sửa lỗi dính tường

  bool collided_x = false;
  bool collided_y = false;
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      int map_x = (int)newx / TILE_SIZE + i;
      int map_y = (int)newy / TILE_SIZE + j;

      if (map_x >= tile_startX && map_x < tile_endX && map_y >= tile_startY && map_y < tile_endY) {
        if (map_data.tile[map_y][map_x] > 0) {
          SDL_Rect Wall = { map_x * TILE_SIZE, map_y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
          SDL_Rect bullet1={newx,rect_.y,rect_.w,rect_.h};
          SDL_Rect bullet2={rect_.x,newy,rect_.w,rect_.h};

          //trục y
          if (detail::check_insize(bullet1, Wall)) {
           // b_sound.PlayBounce();
            collided_x = true;
            angle_bullet = (-angle_bullet + 360) - (i * (BULLET_SPEED / TILE_SIZE) * 90);
            angle_bullet = fmodf(angle_bullet, 360.0f);
            break;
          }

          //trục x
          if (detail::check_insize(bullet2, Wall)) {
            //b_sound.PlayBounce();
            collided_y = true;
            if (angle_bullet < 180) {
              angle_bullet = abs(-angle_bullet + 180) - (j * (BULLET_SPEED / TILE_SIZE) * 90);
            } else {
              angle_bullet = abs(-angle_bullet + 540) - (j * (BULLET_SPEED / TILE_SIZE) * 90);
              quit=true;
            }
            angle_bullet = fmodf(angle_bullet, 360.0f);
            break;
          }
        }
      }
    }
    if(quit) break;
  }

//update
  if (!collided_x) {
    rect_.x = newx;
  }
  if (!collided_y) {
    rect_.y = newy;
  }
}


void BulletObject::time_bullet(const int count_time)
{
    auto current_time = std::chrono::high_resolution_clock::now();

    // Tính toán thời gian đã trôi qua
    std::chrono::duration<float> elapsed_time = current_time - start_time;

    if(elapsed_time.count()>=count_time) {
            is_move=false;
    }
}

void BulletObject::render_bullet(SDL_Renderer* screen)
{
    SDL_Rect renderquad = {rect_.x, rect_.y, rect_.w, rect_.h};
    SDL_RenderCopyEx(screen, texture, NULL,&renderquad, angle_bullet+90, NULL, SDL_FLIP_NONE);
}
