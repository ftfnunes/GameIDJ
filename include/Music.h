#include <iostream>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using namespace std;

#ifndef MUSIC_CLASS
#define MUSIC_CLASS

class Music {
public:
    Music();
    ~Music();
    Music(string file);
    void Play(int times = -1);
    void Stop(int msToStop = 1500);
    void Open(string file);
    bool IsOpen();
private:
    Mix_Music *music;
};

#endif