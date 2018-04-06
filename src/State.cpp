#include <Log.h>
#include <TileMap.h>
#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include "Face.h"
#include "GameObject.h"
#include "Sound.h"

State::State() : music("audio/stageState.ogg") {
    quitRequested = false;

    GameObject *bg = new GameObject();
    bg->AddComponent(new Sprite(*bg, "img/ocean.jpg"));
    bg->AddComponent(new CameraFollower(*bg));
    objectArray[0].emplace_back(bg);

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

    quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

    if (inputManager.KeyPress(SPACE_BAR_KEY)) {
        auto objPos = Vec2(inputManager.GetMouseX(), inputManager.GetMouseY()) +
                Vec2(0, 200).Rotate(M_PI*((rand()%1001)/500.0));
        AddObject(objPos.x, objPos.y);
    }

    for ( auto it = objectArray.begin(); it != objectArray.end(); it++) {
        tileMap->RenderLayer()
    }
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

void State::AddObject(int mouseX, int mouseY) {
    GameObject *go = new GameObject();
    Sprite *pSprite = new Sprite(*go, "img/penguinface.png");
    go->box.x = Camera::pos.x + mouseX - go->box.w/2;
    go->box.y = Camera::pos.y + mouseY - go->box.h/2;
    go->AddComponent(pSprite);
    go->AddComponent(new Sound(*go, "audio/boom.wav"));
    go->AddComponent(new Face(*go));

    objectArray.emplace_back(go);
}