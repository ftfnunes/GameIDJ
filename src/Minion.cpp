//
// Created by ftfnunes on 05/04/18.
//

#include <Sprite.h>
#include "Minion.h"


Minion::Minion(GameObject &associated,
               weak_ptr<GameObject> alienCenter,
               float arcOffsetDeg) : Component(associated),
                                     alienCenter(*alienCenter.lock()),
                                     arc(arcOffsetDeg) {
    auto sprite = new Sprite(associated, "img/minion.png");
    associated.AddComponent(sprite);

    
}

void Minion::Update(float dt) {

}

void Minion::Render() {

}

bool Minion::Is(string type) {
    return false;
}


void Minion::Shoot(Vec2 target) {

}
