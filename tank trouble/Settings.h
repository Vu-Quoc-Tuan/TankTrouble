#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<ctime>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <windows.h>

// game setting
const int SCREEN_WIDTH =900;
const int SCREEN_HEIGHT = 700;
#define WINDOW_TITLE  "Tank Trouble"
const int FPS = 60;
#define TILE_SIZE 15


// TANK SETTINGS
#define TANK_SPEED 2
#define ROTATION_SPEED 4
#define BULLET_CAP 5


// BULLET SETTINGS
#define BULLET_SPEED 5
#define BULLET_LIFETIME 3

// THREAT SETTINGS
#define THREAT_SPEED_x 1
#define THREAT_SPEED_y 1

// Define math:
#define PI 3.1415926535897




#endif // SETTINGS_H_INCLUDED
