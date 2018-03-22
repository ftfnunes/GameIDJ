#define INCLUDE_SDL_IMAGE

#include <Game.h>
#include <GameObject.h>

Sprite::Sprite(GameObject &associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, string file) : Component(associated) {
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

    texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), (ASSETS_PATH + file).c_str());
    if (texture == nullptr) {
        throw "Error loading texture from image: " + file;
    }

    SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
    associated.box.h = height;
    associated.box.w = width;

    SetClip(0, 0, width, height);
}

void Sprite::SetClip(int x, int y, int w, int h) {
    clipRect.x = x;
    clipRect.y = y;
    clipRect.w = w;
    clipRect.h = h;
}

void Sprite::Render() {
    Game &game = Game::GetInstance();
    SDL_Rect dstRect = { associated.box.x , associated.box.y, associated.box.w, associated.box.h };
    SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &dstRect);
}

bool Sprite::IsOpen() {
    return texture != nullptr;
}

int Sprite::GetHeight() {
    return height;
}

bool Sprite::Is(string type) {
    return type == SPRITE_TYPE;
}

void Sprite::Update(float dt) {}

int Sprite::GetWidth() {
    return width;
}