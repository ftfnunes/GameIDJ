#include <GameObject.h>
#include <string>
#include <Sound.h>
#include <zconf.h>
#include <Sprite.h>
#include "Face.h"
#include "Component.h"

Face::Face(GameObject &associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage(int damage) {
    if (hitpoints > 0) {
        hitpoints -= damage;
        if (hitpoints <= 0) {
            auto sound = (Sound *) associated.GetComponent(SOUND_TYPE);
            if (sound != nullptr) {
                sound->Play();
                auto sprite = associated.GetComponent(SPRITE_TYPE);
                if (sprite != nullptr) {
                    associated.RemoveComponent(sprite);
                }
            } else {
                associated.RequestDelete();
            }
        }
    }
}

void Face::Update(float dt) {
    auto sound = (Sound *)associated.GetComponent(SOUND_TYPE);
    if (sound != nullptr && !sound->IsPlaying() && hitpoints <= 0) {
        associated.RequestDelete();
    }
}

void Face::Render() {}

bool Face::Is(string type) {
    return type == FACE_TYPE;
}