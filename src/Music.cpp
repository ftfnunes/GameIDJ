#include <iostream>
#include <Log.h>
#include <Game.h>

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Music.h"


Music::Music() {
    music = nullptr;
}

Music::Music(string file) {
    music = nullptr;
    Open(file);
}

void Music::Play(int times) {
    if (music != nullptr) {
        Mix_PlayMusic(music, times);
    } else {
        throw "No music loaded";
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    music = Mix_LoadMUS((ASSETS_PATH + file).c_str());

    if (music == nullptr) {
        throw "error loading music: " + file;
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}

Music::~Music() {
    Stop(0);
    Mix_FreeMusic(music);
}