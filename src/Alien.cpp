#include <Sprite.h>
#include <InputManager.h>
#include "Alien.h"

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {
    auto sprite = new Sprite(associated, "img/alien.png");
    associated.AddComponent(sprite);

    hp = 30;
    speed = Vec2(0, 0);
}

void Alien::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        
    }
}

void Alien::Render() {

}

bool Alien::Is(string type) {
    return false;
}

void Alien::Start() {
    Component::Start();
}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) {

}

Alien::~Alien() {}
