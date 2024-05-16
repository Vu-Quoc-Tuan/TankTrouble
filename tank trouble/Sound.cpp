#include "Sound.h"

Sound::Sound()
{
    Intro=Mix_LoadMUS("Sound/intro.mp3");

    Fire =Mix_LoadWAV("Sound/Fire.mp3");

    Click=Mix_LoadWAV("Sound/Click.mp3");
    Spawn=Mix_LoadWAV("Sound/Powerup Spawn.mp3");
    Collect=Mix_LoadWAV("Sound/Powerup Collect.mp3");

    T_dead=Mix_LoadWAV("Sound/Explosion.mp3");
    Th_dead=Mix_LoadWAV("Sound/...");

    Outtro=Mix_LoadMUS("Sound/outro.mp3");

    Mix_Volume(-1,10);
}

Sound::~Sound()
{
    Mix_FreeMusic(Intro);
    Mix_FreeChunk(Fire);
    Mix_FreeChunk(T_dead);
    Mix_FreeChunk(Th_dead);
    Mix_FreeChunk(Collect);
    Mix_FreeChunk(Spawn);
    Mix_FreeChunk(Click);
    Mix_FreeMusic(Outtro);

    Intro=NULL;
    Fire=NULL;
    T_dead=NULL;
    Th_dead=NULL;
    Outtro=NULL;
}
