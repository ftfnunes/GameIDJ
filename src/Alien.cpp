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
    auto mouseX = inputManager.getMouseXWithCamera();
    auto mouseY = inputManager.getMouseYWithCamera();

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        taskQueue.push(Action(Action::SHOOT, mouseX, mouseY));
    }
    if (inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
        taskQueue.push(Action(Action::MOVE, mouseX, mouseY));
    }

    if (!taskQueue.empty()) {
        auto action = taskQueue.front();

        if (action.type == Action::MOVE) {
            auto dMod = ALIEN_SPEED*dt;
            auto expectedD = Vec2(action.pos.x, action.pos.y) - associated.box.Center();
            auto effectiveD = Vec2(dMod, 0).Rotate(expectedD.XAngle());

            if (expectedD.Module() < effectiveD.Module()) {
                associated.box += expectedD;
                taskQueue.pop();
            } else {
                associated.box += effectiveD;
            }
        } else {
            taskQueue.pop();
        }
    }

    if (hp <= 0) {
        associated.RequestDelete();
    }
}

void Alien::Render() {}

bool Alien::Is(string type) {
    return type == ALIEN_TYPE;
}

void Alien::Start() {}

Alien::Action::Action(Alien::Action::ActionType type, float x, float y) : type(type) {
    pos.x = x;
    pos.y = y;
}

Alien::~Alien() {
    for (auto &it : minionArray) {
        (*it.lock()).RequestDelete();
    }

    minionArray.clear();
}
