//
// Created by ftfnunes on 16/04/18.
//

#include <Sprite.h>
#include <PenguinCannon.h>
#include <Game.h>
#include <InputManager.h>
#include "PenguinBody.h"

PenguinBody *PenguinBody::player = nullptr;

PenguinBody::PenguinBody(GameObject &associated) : Component(associated), speed(Vec2()), linearSpeed(0), angle(0), hp(50)  {
    associated.AddComponent(new Sprite(associated, "img/penguin.png"));

    player = this;
    associatedPtr = shared_ptr<GameObject>(&associated);
}

PenguinBody::~PenguinBody() {
    player = nullptr;
}


void PenguinBody::Update(float dt) {
    if (hp <= 0) {
        associated.RequestDelete();
        (*pCannon).RequestDelete();
    } else {
        auto inputManager = InputManager::GetInstance();

        if (inputManager.IsKeyDown(LEFT_ARROW_KEY)) {
            angle -= BODY_ANGULAR_SPEED*dt;
        } else if (inputManager.IsKeyDown(RIGHT_ARROW_KEY)) {
            angle += BODY_ANGULAR_SPEED*dt;
        }

        associated.angleDeg = angle;

        auto acceleration = 0.0;
        if (linearSpeed <= MAX_SPEED || linearSpeed >= -MAX_SPEED) {
            if (inputManager.IsKeyDown(UP_ARROW_KEY)) {
                acceleration = ACCELERATION;
            } else if (inputManager.IsKeyDown(DOWN_ARROW_KEY)) {
                acceleration = -ACCELERATION;
            }
        } else {
            linearSpeed = MAX_SPEED;
        }

        auto deltaSpeed = acceleration*dt;
        auto deltaPos = linearSpeed*dt + deltaSpeed*(dt/2);
        linearSpeed += deltaSpeed;

        speed = Vec2(linearSpeed, 0).RotateDeg(angle);
        associated.box += Vec2(deltaPos, 0).RotateDeg(angle);
    }
}

void PenguinBody::Render() {}

bool PenguinBody::Is(string type) {
    return type == BODY_TYPE;
}

void PenguinBody::Start() {
    auto cannonObject = new GameObject();
    auto cannon = new PenguinCannon(*cannonObject, weak_ptr<GameObject>(associatedPtr));
    cannonObject->AddComponent(cannon);
    pCannon = shared_ptr<GameObject>(cannonObject);

    Game::GetInstance().GetState().AddObject(cannonObject);
}
