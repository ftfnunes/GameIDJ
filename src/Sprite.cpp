#define INCLUDE_SDL_IMAGE

#include <Game.h>
#include <GameObject.h>
#include <Resources.h>
#include <Camera.h>

Sprite::Sprite(GameObject &associated) : Component(associated), scale(Vec2(1, 1)) {
    texture = nullptr;
}

Sprite::Sprite(GameObject &associated, string file) : Sprite(associated) {
    Open(file);
}

Sprite::~Sprite() = default;

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
    SDL_Rect dstRect = { x, y, clipRect.w*scale.x, clipRect.h*scale.y };
    SDL_RenderCopyEx(game.GetRenderer(),
                     texture,
                     &clipRect,
                     &dstRect,
                     associated.angleDeg,
                     nullptr,
                     SDL_FLIP_NONE);
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
    return height*scale.y;
}

bool Sprite::Is(string type) {
    return type == SPRITE_TYPE;
}

void Sprite::Update(float dt) {}

int Sprite::GetWidth() {
    return width*scale.x;
}

void Sprite::SetScaleX(float scaleX, float scaleY) {
    scale.x = scaleX == 0 ? scale.x : scaleX;
    scale.y = scaleY == 0 ? scale.y : scaleY;
    auto &box = associated.box;
    auto center = box.Center();
    box.w = width*scaleX;
    box.h = height*scaleY;
    box.x = center.x - box.w/2;
    box.y = center.y - box.h/2;
}

Vec2 Sprite::GetScale() {
    return scale;
}
