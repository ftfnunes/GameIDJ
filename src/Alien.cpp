#include <Sprite.h>
#include <InputManager.h>
#include <Minion.h>
#include <Game.h>
#include <Camera.h>
#include <Collider.h>
#include <PenguinBody.h>
#include "Alien.h"

int Alien::alienCount = 0;

Alien::Alien(GameObject &associated, int nMinions) : Component(associated), nMinions(nMinions), state(RESTING) {
    auto sprite = new Sprite(associated, "img/alien.png");
    associated.AddComponent(sprite);
    associated.AddComponent(new Collider(associated, Vec2(0.65, 0.6), Vec2(-8, 0)));

    alienCount++;
    hp = 30;
    speed = Vec2(0, 0);
}

void Alien::Update(float dt) {
    if (hp <= 0) {
        associated.RequestDelete();

        auto explosionObj = new GameObject(associated.GetLayer());
        auto explosionSprite = new Sprite(*explosionObj, "img/aliendeath.png", 4, 0.1, 0.4);
        explosionObj->AddComponent(explosionSprite);
        explosionObj->SetCenter(associated.box.Center());
        Game::GetInstance().GetState().AddObject(explosionObj);
    } else {
        auto inputManager = InputManager::GetInstance();

        associated.angleDeg += ALIEN_ROTATION_SPEED*dt;

        if (inputManager.KeyPress(SDLK_u)) {
            if (associated.GetLayer() == 0) {
                associated.SetLayer(1);
            } else {
                associated.SetLayer(0);
            }
        }
        
        if (PenguinBody::player != nullptr) {
            if (state == RESTING) {
                restTimer.Update(dt);

                if (restTimer.Get() > ALIEN_COOLDOWN) {
                    restTimer.Restart();
                    state = MOVING;

                    destination = PenguinBody::player->GetPosition();
                    auto expectedD = destination - associated.box.Center();
                    speed = Vec2(ALIEN_SPEED, 0).Rotate(expectedD.XAngle());
                }
            } else {
                auto expectedD = destination - associated.box.Center();
                auto effectiveD = speed*dt;

                if (expectedD.Module() < effectiveD.Module()) {
                    associated.box += expectedD;

                    auto minionObj = shared_ptr<GameObject>();
                    auto lastDistance = 0.0;
                    auto target = PenguinBody::player->GetPosition();

                    for (auto &it: minionArray) {
                        auto objPtr = it.lock();
                        auto distance = objPtr->box.Center().Distance(target);
                        if (!minionObj || distance < lastDistance) {
                            minionObj = objPtr;
                            lastDistance = distance;
                        }
                    }

                    auto minion = (Minion *) (*minionObj).GetComponent("Minion");

                    state = RESTING;
                    minion->Shoot(target);
                } else {
                    associated.box += effectiveD;
                }
            }
        }
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

Alien::~Alien() {
    for (auto &it : minionArray) {
        (*it.lock()).RequestDelete();
    }
    minionArray.clear();

    alienCount--;
}


void Alien::NotifyCollision(GameObject &other) {
    auto bullet = (Bullet *) other.GetComponent(BULLET_TYPE);

    if (bullet != nullptr && !bullet->TargetsPlayer()) {
        hp -= bullet->GetDamage();
    }
}

int Alien::GetHp() {
    return hp;
}
