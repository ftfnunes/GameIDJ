#include <Sprite.h>
#include <InputManager.h>
#include <search.h>
#include "Alien.h"

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {
    auto sprite = new Sprite(associated, "img/alien.png");
    associated.AddComponent(sprite);

    hp = 30;
    speed = Vec2(0, 0);
}

void Alien::Update(float dt) {
    auto inputManager = InputManager::GetInstance();
    auto x = inputManager.getMouseXWithCamera();
    auto y = inputManager.getMouseYWithCamera();

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        taskQueue.push(Action(Action::SHOOT, x, y));
    }
    if (inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
        taskQueue.push(Action(Action::MOVE, x, y));
    }

    if (!taskQueue.empty()) {
        auto action = taskQueue.front();
        
        if (action.type == Action::MOVE) {
            auto dMod = ALIEN_SPEED*dt;
            auto d = Vec2(dMod, 0);
            auto newPos = associated.box + d;

            if (newPos.Center() - associated.box.Center()) {
            }


        } else {

        }
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

Alien::~Alien() {

}
