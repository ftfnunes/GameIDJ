#include <Sprite.h>
#include <InputManager.h>
#include <Minion.h>
#include <Game.h>
#include "Alien.h"

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), nMinions(nMinions) {
    auto sprite = new Sprite(associated, "img/alien.png");
    associated.AddComponent(sprite);

    hp = 30;
    speed = Vec2(0, 0);
}

void Alien::Update(float dt) {
    auto inputManager = InputManager::GetInstance();
    auto mouseX = inputManager.getMouseXWithCamera();
    auto mouseY = inputManager.getMouseYWithCamera();

    associated.angleDeg += ALIEN_ROTATION_SPEED*dt;

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
            auto minionObj = shared_ptr<GameObject>();
            auto lastDistance = 0.0;

            for (auto &it: minionArray) {
                auto objPtr = it.lock();
                auto &obj = (*objPtr);
                auto distance = obj.box.Center().Distance(Vec2(mouseX, mouseY));
                if (!minionObj || distance < lastDistance) {
                    minionObj = objPtr;
                    lastDistance = distance;
                }
            }

            auto minion = (Minion *) (*minionObj).GetComponent("Minion");

            minion->Shoot(Vec2(mouseX, mouseY));
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

void Alien::Start() {
    for (int i = 0; i < nMinions; ++i) {
        auto minionObj = new GameObject();
        auto objPtr = Game::GetInstance().GetState().AddObject(minionObj);
        auto alienPtr = Game::GetInstance().GetState().GetObjectPtr(&associated);
        minionObj->AddComponent(new Minion(*minionObj, alienPtr, 2*M_PI*(i/(float)nMinions)));
        minionArray.push_back(objPtr);
    }
}

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
