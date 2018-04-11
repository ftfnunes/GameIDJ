//
// Created by ftfnunes on 29/03/18.
//

#include <InputManager.h>
#include <Game.h>
#include "Camera.h"

Vec2 Camera::pos = Vec2();
Vec2 Camera::speed = Vec2();
GameObject *Camera::focus = nullptr;
unordered_map<int, float> Camera::modifiers;


void Camera::Follow(GameObject *newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if (focus != nullptr) {
        auto center = focus->box.Center();
        pos = Vec2(center.x - WIDTH/2, center.y - HEIGHT/2);
    } else {
        auto inputManager = InputManager::GetInstance();

        speed = Vec2();
        if (inputManager.IsKeyDown(LEFT_ARROW_KEY)) {
            speed = Vec2(-CAMERA_SPEED*dt, 0);
        } else if (inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
            speed = Vec2(0, CAMERA_SPEED*dt);
        } else if (inputManager.IsKeyDown(UP_ARROW_KEY)) {
            speed = Vec2(0, -CAMERA_SPEED*dt);
        } else if (inputManager.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed = Vec2(CAMERA_SPEED*dt, 0);
        }
        pos += speed;
    }
}

void Camera::SetModifier(int layer, float modifier) {
    modifiers[layer] = modifier;
}

Vec2 Camera::GetPosWithModifier(int layer) {
    auto it = modifiers.find(layer);

    return it == modifiers.end() ? pos : pos*((*it).second);
}
