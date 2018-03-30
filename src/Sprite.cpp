#define INCLUDE_SDL_IMAGE

#include <Game.h>
#include <GameObject.h>
#include <Resources.h>
#include <Camera.h>

Sprite::Sprite(GameObject &associated) : Component(associated) {
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, string file) : Component(associated) {
    texture = nullptr;
    Open(file);
}

Sprite::~Sprite() {}

void Sprite::Open(string file) {
    texture = Resources::GetImage(file);

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

void Sprite::Render(float x, float y) {
    Game &game = Game::GetInstance();
    SDL_Rect dstRect = { x, y, clipRect.w, clipRect.h };
    SDL_RenderCopy(game.GetRenderer(), texture, &clipRect, &dstRect);
}

void Sprite::Render() {
    auto box = associated.box;
    auto camera = Camera::pos;
    Render(box.x - camera.x, box.y - camera.y);
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