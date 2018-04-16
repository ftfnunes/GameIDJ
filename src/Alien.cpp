#include <Sprite.h>
#include <InputManager.h>
#include <Minion.h>
#include <Game.h>
#include <Camera.h>
#include "Alien.h"

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), nMinions(nMinions) {
    auto sprite = new Sprite(associated, "img/alien.png");
    associated.AddComponent(sprite);

    hp = 30;
    speed = Vec2(0, 0);
}

void Alien::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    associated.angleDeg += ALIEN_ROTATION_SPEED*dt;

    if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
        auto mousePos = inputManager.GetMouse() + Camera::pos;
        taskQueue.push(Action(Action::SHOOT, mousePos.x, mousePos.y));
    }
    if (inputManager.MousePress(RIGHT_MOUSE_BUTTON)) {
        auto mousePos = Camera::GetClickPosition(associated.GetLayer(), inputManager.GetMouse());
        taskQueue.push(Action(Action::MOVE, mousePos.x, mousePos.y));
    }

    if (inputManager.KeyPress(SDLK_u)) {
        if (associated.GetLayer() == 0) {
            associated.SetLayer(1);
        } else {
            associated.SetLayer(0);
        }
    }

    if (inputManager.KeyPress(SDLK_l)) {
        if (Camera::IsFollowing()) {
            Camera::Unfollow();
        } else {
            Camera::Follow(&associated);
        }
    }

    if (!taskQueue.empty()) {
        auto action = taskQueue.front();

        if (action.type == Action::MOVE) {
            auto dMod = ALIEN_SPEED*dt;
            auto expectedD = action.pos - associated.box.Center();
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
            auto target = Vec2();

            for (auto &it: minionArray) {
                auto objPtr = it.lock();
                auto &obj = (*objPtr);
                auto tgt = Camera::GetClickPosition((*objPtr).GetLayer(), action.pos, false);
                auto distance = obj.box.Center().Distance(tgt);
                if (!minionObj || distance < lastDistance) {
                    minionObj = objPtr;
                    lastDistance = distance;
                    target = tgt;
                }
            }

            auto minion = (Minion *) (*minionObj).GetComponent("Minion");

            minion->Shoot(target);
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
