#include <iostream>
#include <Log.h>

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
        //TODO: Log error
    }
}

void Music::Stop(int msToStop) {
    Mix_FadeOutMusic(msToStop);
}

void Music::Open(string file) {
    music = Mix_LoadMUS(file.c_str());

    if (music == nullptr) {
        Log::LogError("error loading music: " + file);
    }
}

bool Music::IsOpen() {
    return music != nullptr;
}

Music::~Music() {
    Stop(0);
    Mix_FreeMusic(music);
}