#include <Log.h>
#include <Game.h>
#include <InputManager.h>
#include <Camera.h>
#include <CameraFollower.h>
#include <Alien.h>
#include <algorithm>
#include <PenguinBody.h>
#include <Collider.h>
#include <Collision.h>
#include <StageState.h>


StageState::StageState() : backgroundMusic("audio/stageState.ogg"),
                 tileMap(nullptr),
                 bg(nullptr) {

    Camera::SetCameraHeight(5);
    Camera::SetLayerHeight(1, 4.5);

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
    auto alien = new Alien(*alienObject, 5);
    alienObject->AddComponent(alien);
    AddObject(alienObject);

    auto playerObject = new GameObject();
    playerObject->box = Rect(704, 640);
    playerObject->AddComponent(new PenguinBody(*playerObject));
    AddObject(playerObject);

    Camera::Follow(playerObject);

    backgroundMusic.Play();
}

void StageState::LoadAssets() {
}

void StageState::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    Camera::Update(dt);
    bg->Update(dt);

    quitRequested = inputManager.QuitRequested();

    popRequested = inputManager.KeyPress(ESCAPE_KEY);

    UpdateArray(dt);

    for (auto &it: objectLayers) {
        auto &objects = it.second;
        auto colliderArray = new Collider*[objects.size()];
        memset(colliderArray, 0, objects.size()*sizeof(Collider *));
        for (int i = 0; i < objects.size(); ++i) {
            for (int j = i; j < objects.size(); ++j) {
                if (i == 0) {
                    colliderArray[j] = (Collider *)(*objects[j]).GetComponent(COLLIDER_TYPE);
                }
                if (i != 0 && colliderArray[i] == nullptr) {
                    break;
                }

                if (i != j && colliderArray[j] != nullptr && colliderArray[i] != nullptr) {
                    auto angleIRad = 2*M_PI*((*objects[i]).angleDeg/360);
                    auto angleJRad = 2*M_PI*((*objects[j]).angleDeg/360);
                    auto boxI = colliderArray[i]->box;
                    auto boxJ = colliderArray[j]->box;

                    if (Collision::IsColliding(boxI, boxJ, angleIRad, angleJRad)) {
                        (*objects[i]).NotifyCollision((*objects[j]));
                        (*objects[j]).NotifyCollision((*objects[i]));
                    }
                }
            }
        }
    }

    for (auto &it: objectLayers) {
        auto &objects = it.second;

        for(int i = 0; i < objects.size(); i++) {
            if (objects[i]->IsDead()) {
                objects.erase(objects.begin() + i);
            }
        }
    }
    
    if (Alien::alienCount == 0) {
        
    }
}

void StageState::Render() {
    bg->Render();
    for (int i = 0; i < tileMap->GetDepth(); i++) {
        auto it = objectLayers.find(i);
        tileMap->RenderLayer(i);

        if (it != objectLayers.end()) {
            auto &objects = (*it).second;

            for (auto &object : objects) {
                object->Render();
            }
        }
    }
}

StageState::~StageState() {
    objectLayers.clear();
}

void StageState::Start() {
    StartArray();
}

void StageState::Pause() {

}

void StageState::Resume() {

}

