#include <Log.h>
#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include "Face.h"
#include "Sound.h"

State::State() : music("audio/stageState.ogg"), tileMap(nullptr), bg(nullptr) {
    quitRequested = false;

    bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "img/ocean.jpg"));
    bg->AddComponent(new CameraFollower(*bg));

    auto mapObject = new GameObject();
    mapObject->box.h = HEIGHT;
    mapObject->box.w = WIDTH;

    auto set = new TileSet(64, 64, "img/tileset.png");
    tileMap = new TileMap(*mapObject, "map/tileMap.txt", set);
    mapObject->AddComponent(tileMap);

    music.Play();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    auto inputManager = InputManager::GetInstance();
    Camera::Update(dt);
    bg->Update(dt);
    quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

    if (inputManager.KeyPress(SPACE_BAR_KEY)) {
        auto objPos = Vec2(inputManager.GetMouseX(), inputManager.GetMouseY()) +
                Vec2(0, 200).Rotate(M_PI*((rand()%1001)/500.0));
        AddObject(objPos.x, objPos.y);
    }

    for (auto &it : objectArray) {
        auto &objects = it.second;

        for (int i = 0; i < objects.size(); ++i) {
            objects[i]->Update(dt);
        }
    }

    for (auto &it: objectArray) {
        auto &objects = it.second;

        for(int i = 0; i < objects.size(); i++) {
            if (objects[i]->IsDead()) {
                objects.erase(objects.begin() + i);
            }
        }
    }
}

void State::Render() {
    bg->Render();
    for (int i = 0; i < tileMap->GetDepth(); i++) {
        auto it = objectArray.find(i);
        tileMap->RenderLayer(i, Camera::pos.x, Camera::pos.y);

        if (it != objectArray.end()) {
            auto &objects = (*it).second;

            for (auto &object : objects) {
                object->Render();
            }
        }
    }
}

bool State::QuitRequested() {
    return quitRequested;
}

State::~State() {
    objectArray.clear();
}

void State::AddObject(int mouseX, int mouseY) {
    auto *go = new GameObject();
    Sprite *pSprite = new Sprite(*go, "img/penguinface.png");
    go->box.x = Camera::pos.x + mouseX - go->box.w/2;
    go->box.y = Camera::pos.y + mouseY - go->box.h/2;
    go->AddComponent(pSprite);
    go->AddComponent(new Sound(*go, "audio/boom.wav"));
    go->AddComponent(new Face(*go));

    objectArray[0].emplace_back(go);
}