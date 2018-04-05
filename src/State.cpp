#include <Log.h>
#include <TileMap.h>
#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Alien.h>
#include "GameObject.h"
#include "Sound.h"

State::State() : music("audio/stageState.ogg"), quitRequested(false), started(false) {

    auto bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "img/ocean.jpg"));
    bg->AddComponent(new CameraFollower(*bg));
    objectArray.emplace_back(bg);

    auto map = new GameObject();
    map->box.h = HEIGHT;
    map->box.w = WIDTH;
    auto set = new TileSet(64, 64, "img/tileset.png");
    map->AddComponent(new TileMap(*map, "map/tileMap.txt", set));
    objectArray.emplace_back(map);

    auto alienObject = new GameObject();
    alienObject->box.x = 512;
    alienObject->box.y = 300;
    auto alien = new Alien(*alienObject, 3);
    alienObject->AddComponent(alien);
    objectArray.emplace_back(alienObject);

    music.Play();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    auto inputManager = InputManager::GetInstance();
    Camera::Update(dt);

    quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

    for(int i = 0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for(int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
        }
    }
}

void State::Render() {
    for(auto it = objectArray.begin(); it != objectArray.end(); ++it) {
        (*it)->Render();
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

    for (auto it = objectArray.begin(); it != objectArray.end(); it++) {
        (*(*it)).Start();
    }

    started = true;
}

weak_ptr<GameObject> State::GetObjectPtr(GameObject *obj) {
    for(auto it = objectArray.begin(); it != objectArray.end(); ++it) {
        if ((*it).get() == obj) {
            return weak_ptr<GameObject>(*it);
        }
    }
    return weak_ptr<GameObject>();
}

weak_ptr<GameObject> State::AddObject(GameObject *obj) {
    auto ptr = shared_ptr<GameObject>(obj);
    objectArray.push_back(ptr);

    if (started) {
        (*ptr).Start();
    }

    return weak_ptr<GameObject>(ptr);
}