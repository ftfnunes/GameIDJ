#include <Log.h>
#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Alien.h>
#include <algorithm>


State::State() : music("audio/stageState.ogg"),
                 quitRequested(false),
                 started(false),
                 tileMap(nullptr),
                 bg(nullptr) {

    Camera::SetCameraHeight(5);
    Camera::SetLayerHeight(1, 4.3);

    bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "img/ocean.jpg"));
    bg->AddComponent(new CameraFollower(*bg));

    auto mapObject = new GameObject();
    mapObject->box.h = HEIGHT;
    mapObject->box.w = WIDTH;

    auto set = new TileSet(64, 64, "img/tileset.png");
    tileMap = new TileMap(*mapObject, "map/tileMap.txt", set);
    mapObject->AddComponent(tileMap);

    auto alienObject = new GameObject(1);
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
            auto obj = objects[i];
            if (!obj->IsUpdated()) {
                obj->Update(dt);
            }
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
        tileMap->RenderLayer(i);

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

    auto &objects = objectArray[obj->GetLayer()];
    for (auto &object : objects) {
        if (object.get() == obj) {
            return weak_ptr<GameObject>(object);
        }
    }

    return weak_ptr<GameObject>();
}

weak_ptr<GameObject> State::AddObject(GameObject *obj) {
    auto ptr = shared_ptr<GameObject>(obj);

    return AddObject(ptr);
}

weak_ptr<GameObject> State::AddObject(shared_ptr<GameObject> ptr) {

    objectArray[(*ptr).GetLayer()].push_back(ptr);

    if (started && !(*ptr).HasStarted()) {
        (*ptr).Start();
    }

    return weak_ptr<GameObject>(ptr);
}

shared_ptr<GameObject> State::PopObjectPtr(GameObject *obj) {
    auto &layer = objectArray[obj->GetLayer()];

    for (int i = 0; i < layer.size(); ++i) {
        auto object = layer[i];
        if (object.get() == obj) {
            layer.erase(layer.begin() + i);
            return object;
        }
    }

    return shared_ptr<GameObject>();
}

