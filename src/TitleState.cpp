#include <Sprite.h>
#include <InputManager.h>
#include <Game.h>
#include <StageState.h>
#include <CameraFollower.h>
#include "TitleState.h"

TitleState::TitleState() : State() {
    auto bgObj = new GameObject();
    bgObj->AddComponent(new Sprite(*bgObj, "img/title.jpg"));
    bgObj->AddComponent(new CameraFollower(*bgObj));
    AddObject(bgObj);
}

TitleState::~TitleState() {

}

void TitleState::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    UpdateArray(dt);

    quitRequested = inputManager.QuitRequested() || inputManager.KeyPress(ESCAPE_KEY);
    if (inputManager.KeyPress(SPACE_KEY)) {
        Game::GetInstance().Push(new StageState());
    }
}

void TitleState::Render() {
    RenderArray();
}

void TitleState::Start() {
    StartArray();
}

void TitleState::Pause() {

}

void TitleState::Resume() {

}

void TitleState::LoadAssets() {

}
