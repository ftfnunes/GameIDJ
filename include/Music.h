#include <iostream>
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using namespace std;

class Music {
public:
    Music();
    ~Music();
    Music(string file);
    void Play(int time = -1);
    void Stop(int msToStop = 1500);
    void Open(string file);
    bool isOpen();
private:
    Mix_Music *music;
};
