#include <GameObject.h>
#include <string>
#include <Sound.h>
#include <zconf.h>
#include <Sprite.h>
#include <InputManager.h>
#include <Camera.h>
#include "Face.h"
#include "Component.h"

Face::Face(GameObject &associated) : Component(associated) {
    hitpoints = 30;
}

void Face::Damage(int damage) {
    hitpoints -= damage;
    if (hitpoints <= 0) {
        auto sound = (Sound *) associated.GetComponent(SOUND_TYPE);
        sound->Play();
        associated.RequestDelete();
    }
}

void Face::Update(float dt) {
    auto inputManager = InputManager::GetInstance();
    auto camera = Camera::pos;
    auto mousePos = Vec2(inputManager.GetMouseX() + camera.x, inputManager.GetMouseY() + camera.y);
    if (inputManager.MousePress(LEFT_MOUSE_BUTTON) && associated.box.Contains(mousePos)) {
        Damage(rand()%10 + 10);
    }
}

void Face::Render() {
}

bool Face::Is(string type) {
    return type == FACE_TYPE;
}