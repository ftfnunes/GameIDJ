//
// Created by ftfnunes on 05/04/18.
//

#include <GameObject.h>
#include <Game.h>
#include "Minion.h"
#include "Bullet.h"


Minion::Minion(GameObject &associated,
               weak_ptr<GameObject> alienCenter,
               float arcOffsetDeg) : Component(associated),
                                     alienCenter(alienCenter),
                                     arc(arcOffsetDeg) {
    auto sprite = new Sprite(associated, "img/minion.png");
    auto scale = ((rand() % 501) + 1000) / 1000.0;
    sprite->SetScaleX(scale, scale);
    associated.AddComponent(sprite);

    auto r = Vec2(ORBIT_RADIUS, 0).Rotate(arc);
    auto correctedR = r - Vec2(associated.box.w/2, associated.box.h/2);
    this->associated.box += (*this->alienCenter.lock()).box.Center() + correctedR;
}

void Minion::Update(float dt) {
    if (alienCenter.expired()) {
        associated.RequestDelete();
    } else {
        arc += MINION_ANG_SPEED*dt;
        auto r = Vec2(ORBIT_RADIUS, 0).Rotate(arc);
        associated.angleDeg = r.XAngleDeg();
        auto d = r - associated.box.Center();
        this->associated.box += (*alienCenter.lock()).box.Center() + d;
    }
}

void Minion::Render() {}

bool Minion::Is(string type) {
    return type == MINION_TYPE;
}

void Minion::Shoot(Vec2 target) {
    auto bulletObj = new GameObject();
    auto bullet = new Bullet(*bulletObj,
                             (target - associated.box.Center()).XAngleDeg(),
                             MINION_BULLET_SPEED,
                             MINION_BULLET_DAMAGE,
                             MINION_BULLET_DISTANCE,
                             "img/minionbullet2.png", 3, 0.1);

    auto minionCenter = associated.box.Center();
    bulletObj->AddComponent(bullet);

    bulletObj->box.x = minionCenter.x - bulletObj->box.w/2;
    bulletObj->box.y = minionCenter.y - bulletObj->box.h/2;

    Game::GetInstance().GetState().AddObject(bulletObj);
}
