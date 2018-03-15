#define INCLUDE_SDL_IMAGE

#include <Game.h>
#include <Log.h>
#include "SDL_include.h"
#include "Sprite.h"

Sprite::Sprite() {
    texture = nullptr;
}

Sprite::Sprite(string file) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {
    if (texture != nullptr) {
        SDL_DestroyTexture(texture);
    }
}

void Sprite::Open(string file) {
    if (IsOpen()) {
        SDL_DestroyTexture(texture);
    }

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
    if (texture == nullptr) {
        Log::LogError("Error loading texture from image: " + file);
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render(int x, int y) {
    Game &game = Game::GetInstance();
    SDL_Rect dstRect = { x, y, width, height };
    SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &dstRect);
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

int Sprite::GetHeight() {
    return height;
}

int Sprite::GetWidth() {
    return width;
}