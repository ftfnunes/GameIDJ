//
// Created by ftfnunes on 16/04/18.
//

#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include <Game.h>
#include <Bullet.h>
#include <Collider.h>
#include "PenguinCannon.h"


PenguinCannon::PenguinCannon(GameObject &associated, weak_ptr<GameObject> penguinBody) : Component(associated), pBody(penguinBody), angle(0) {
    associated.AddComponent(new Sprite(associated, "img/cubngun.png"));
    associated.AddComponent(new Collider(associated));
}

void PenguinCannon::Update(float dt) {
    if (pBody.expired()) {
        associated.RequestDelete();
    } else {
        auto bodyCenter = (*pBody.lock()).box.Center();
        auto &box = associated.box;
        box.x = bodyCenter.x - box.w/2;
        box.y = bodyCenter.y - box.h/2;

        auto inputManager = InputManager::GetInstance();
        auto mousePos = Camera::GetClickPosition(associated.GetLayer(), inputManager.GetMouse());

        angle = associated.angleDeg = (mousePos - bodyCenter).XAngleDeg();

        if (inputManager.MousePress(LEFT_MOUSE_BUTTON)) {
            Shoot();
        }
    }
}

void PenguinCannon::Render() {}

bool PenguinCannon::Is(string type) {
    return type == CANNON_TYPE;
}

void PenguinCannon::Shoot() {
    auto bulletObj = new GameObject();
    auto bullet = new Bullet(*bulletObj,
                             angle,
                             PENGUIN_BULLET_SPEED,
                             PENGUIN_BULLET_DAMAGE,
                             PENGUIN_BULLET_DISTANCE,
                             "img/penguinbullet.png", 4, 0.1);

    bulletObj->AddComponent(bullet);

    auto cannonCenter = associated.box.Center();
    auto cannonHole =  Vec2(associated.box.w/2, 0).RotateDeg(angle);

    bulletObj->box.x = cannonCenter.x + - bulletObj->box.w/2;
    bulletObj->box.y = cannonCenter.y - bulletObj->box.h/2;
    bulletObj->box += cannonHole;
    Game::GetInstance().GetState().AddObject(bulletObj);
}

