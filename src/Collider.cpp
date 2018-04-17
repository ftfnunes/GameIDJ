//
// Created by ftfnunes on 17/04/18.
//

#include "Collider.h"


Collider::Collider(GameObject &associated, Vec2 scale, Vec2 offset) : Component(associated),
                                                                      scale(scale),
                                                                      offset(offset) {
}

void Collider::Update(float dt) {
    box.w = associated.box.w*scale.x;
    box.h = associated.box.h*scale.y;

    box += offset.RotateDeg(associated.angleDeg);
}

void Collider::Render() {}

bool Collider::Is(string type) {
    return type == COLLIDER_TYPE;
}

void Collider::SetScale(Vec2 scale) {
    this->scale = scale;
}

void Collider::SetOffset(Vec2 offset) {
    this->offset = offset;
}

