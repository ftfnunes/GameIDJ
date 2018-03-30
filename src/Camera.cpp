//
// Created by ftfnunes on 29/03/18.
//

#include <InputManager.h>
#include <Game.h>
#include "Camera.h"

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject *Camera::focus = nullptr;


void Camera::Follow(GameObject *newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if (focus != nullptr) {
        pos = Vec2(focus->box.x - WIDTH/2, focus->box.y - HEIGHT/2);
    } else {
        auto inputManager = InputManager::GetInstance();

        speed = Vec2();
        if (inputManager.IsKeyDown(LEFT_ARROW_KEY)) {
            speed = Vec2(CAMERA_SPEED*dt, 0).Rotate(M_PI);
        } else if (inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
            speed = Vec2(CAMERA_SPEED*dt, 0).Rotate(M_PI/2);
        } else if (inputManager.IsKeyDown(UP_ARROW_KEY)) {
            speed = Vec2(CAMERA_SPEED*dt, 0).Rotate(-M_PI/2);
        } else if (inputManager.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed = Vec2(CAMERA_SPEED*dt, 0);
        }
        pos += speed;
    }
}
