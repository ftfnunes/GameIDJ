#include <Game.h>
#include "Resources.h"

unordered_map<string, SDL_Texture*> Resources::imageTable;
unordered_map<string, Mix_Music*> Resources::musicTable;
unordered_map<string, Mix_Chunk*> Resources::soundTable;

shared_ptr<SDL_Texture> Resources::GetImage(string file) {
    auto it = imageTable.find(file);
    if (it != imageTable.end()) {
        return (*it).second;
    } else {
        auto texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), (ASSETS_PATH + file).c_str());
        if (texture == nullptr) {
            throw "Error loading texture from image: " + file;
        }
        auto txt_ptr = shared_ptr<SDL_Texture>(texture, [] (SDL_Texture *texture) -> {
            SDL_DestroyTexture(texture);
        });
        imageTable.insert(make_pair(file, txt_ptr));
        return txt_ptr;
    }
}

void Resources::ClearImages() {
    for (auto it = imageTable.begin(); it != imageTable.end() ; ++it) {
        auto ptr = (*it).second;
        if (ptr.unique()) {
            imageTable.erase((*it).first);
        }
    }
}

Mix_Music *Resources::GetMusic(string file) {
    auto it = musicTable.find(file);
    if (it != musicTable.end()) {
        return (*it).second;
    } else {
        auto music = Mix_LoadMUS((ASSETS_PATH + file).c_str());
        if (music == nullptr) {
            throw "Error loading backgroundMusic: " + file + ". Reason: " + string(SDL_GetError());
        }

        musicTable.insert(make_pair(file, music));
        return music;
    }
}

void Resources::ClearMusics() {
    for (auto it = musicTable.begin(); it != musicTable.end(); ++it) {
        Mix_FreeMusic((*it).second);
    }
    musicTable.clear();
}

Mix_Chunk *Resources::GetSound(string file) {
    auto it = soundTable.find(file);
    if (it != soundTable.end()) {
        return (*it).second;
    } else {
        auto chunk = Mix_LoadWAV((ASSETS_PATH + file).c_str());
        if (chunk == nullptr) {
            throw "Error loading file: " + file + ". Reason: " + string(SDL_GetError());
        }

        soundTable.insert(make_pair(file, chunk));
        return chunk;
    }
}

void Resources::ClearSounds() {
    for (auto it = soundTable.begin(); it != soundTable.end(); ++it) {
        Mix_FreeChunk((*it).second);
    }
    soundTable.clear();
}
