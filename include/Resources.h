//
// Created by ftfnunes on 29/03/18.
//

#ifndef T1_RESOURCEMANAGER_H
#define T1_RESOURCEMANAGER_H

#include <iostream>
#include <unordered_map>
#include <memory>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

using namespace std;
class Resources {
public:
    static shared_ptr<SDL_Texture> GetImage(string file);
    static void ClearImages();

    static shared_ptr<Mix_Music> GetMusic(string file);
    static void ClearMusics();

    static shared_ptr<Mix_Chunk> GetSound(string file);
    static void ClearSounds();

private:
    static unordered_map<string, shared_ptr<SDL_Texture>> imageTable;
    static unordered_map<string, shared_ptr<Mix_Music>> musicTable;
    static unordered_map<string, shared_ptr<Mix_Chunk>> soundTable;

};


#endif //T1_RESOURCEMANAGER_H
