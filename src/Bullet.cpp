//
// Created by ftfnunes on 07/04/18.
//

#include <Sprite.h>
#include <Collider.h>
#include "Bullet.h"


Bullet::Bullet(GameObject &associated,
               float angle,
               float speed,
               int damage,
               float maxDistance,
               string sprite,
               int frameCount,
               float frameTime) : Component(associated), damage(damage), distanceLeft(maxDistance) {
    associated.AddComponent(new Sprite(associated, sprite, frameCount, frameTime));
    associated.AddComponent(new Collider(associated));
    associated.angleDeg = angle;
    this->speed = Vec2(speed, 0).Rotate((angle/360)*2*M_PI);
}

void Bullet::Update(float dt) {
    auto d = speed*dt;
    auto dModule = d.Module();

    if (dModule < distanceLeft) {
        associated.box += d;
    } else {
        associated.box += Vec2(distanceLeft, 0).Rotate(speed.XAngle());
        associated.RequestDelete();
    }

    distanceLeft -= dModule;
}

void Bullet::Render() {}

bool Bullet::Is(string type) {
    return type == BULLET_TYPE;
}

int Bullet::GetDamage() {
    return damage;
}

