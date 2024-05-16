#ifndef SOUND_H_INCLUDED
#define SOUND_H_INCLUDED

#include"Settings.h"

class Sound
{
public:
    Sound();
    ~Sound();

    void Playintro()  {Mix_PlayMusic(Intro,-1);}

    void PlayFire()   {Mix_PlayChannel(0,Fire,0);}
    void PlayBounce() {Mix_PlayChannel(5,Bounce,0);}

    void PlayClick()  {Mix_PlayChannel(1,Click,0);}
    void PlaySpawn()  {Mix_PlayChannel(2,Spawn,0);}
    void PlayCollect(){Mix_PlayChannel(5,Collect,0);}

    void PlayT_dead() {Mix_PlayChannel(3,T_dead,0);}
    void PlayTh_dead(){Mix_PlayChannel(4,Th_dead,0);}

    void PlayOuttro() {Mix_PlayMusic(Outtro,-1);}
    void Haltmusic()  {Mix_HaltMusic();}

    int checkmusic() {return Mix_GetMusicVolume(Intro);}
    void mute () {Mix_Volume(-1, 0);Mix_VolumeMusic(0);}
    void unmute(){Mix_Volume(-1,64);Mix_VolumeMusic(64);}

private:
    Mix_Music* Intro;

    Mix_Chunk* Fire;

    Mix_Chunk* Click;
    Mix_Chunk* Spawn;
    Mix_Chunk* Collect;
    Mix_Chunk* Bounce;

    Mix_Chunk* T_dead;
    Mix_Chunk* Th_dead;

    Mix_Music* Outtro;
};

#endif // SOUND_H_INCLUDED
