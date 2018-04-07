#include <Log.h>
#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Alien.h>
#include "Sound.h"


State::State() : music("audio/stageState.ogg"),
                 quitRequested(false),
                 started(false),
                 tileMap(nullptr),
                 bg(nullptr) {

    bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "img/ocean.jpg"));
    bg->AddComponent(new CameraFollower(*bg));

    auto mapObject = new GameObject();
    mapObject->box.h = HEIGHT;
    mapObject->box.w = WIDTH;

    auto set = new TileSet(64, 64, "img/tileset.png");
    tileMap = new TileMap(*mapObject, "map/tileMap.txt", set);
    mapObject->AddComponent(tileMap);

    auto alienObject = new GameObject();
    alienObject->box = Rect(512, 300, 0, 0);
    auto alien = new Alien(*alienObject, 3);
    alienObject->AddComponent(alien);
    AddObject(alienObject);

    music.Play();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    Camera::Update(dt);
    bg->Update(dt);

    quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

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

void State::Start() {
    this->LoadAssets();
    for (auto &objLayer : objectArray) {
        auto &objects = objLayer.second;
        for (int i = 0; i < objects.size(); i++) {
            (*objects[i]).Start();
        }
    }


    started = true;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *obj) {
    for (auto &objLayer : objectArray) {
        auto &objects = objLayer.second;
        for(auto it = objects.begin(); it != objects.end(); ++it) {
            if ((*it).get() == obj) {
                return weak_ptr<GameObject>(*it);
            }
        }
    }

    return weak_ptr<GameObject>();
}



weak_ptr<GameObject> State::AddObject(GameObject *obj, int layer) {
    auto ptr = shared_ptr<GameObject>(obj);
    objectArray[layer].push_back(ptr);

    if (started) {
        (*ptr).Start();
    }

    return weak_ptr<GameObject>(ptr);
}

weak_ptr<GameObject> State::AddObject(GameObject *obj) {
    return AddObject(obj, 0);
}
