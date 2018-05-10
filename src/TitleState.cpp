#include <Sprite.h>
#include <InputManager.h>
#include <Game.h>
#include <StageState.h>
#include <CameraFollower.h>
#include <Camera.h>
#include <IntervalTimer.h>
#include <tiff.h>
#include "TitleState.h"
#include "Text.h"

TitleState::TitleState() : State() {
    auto bgObj = new GameObject();
    bgObj->AddComponent(new Sprite(*bgObj, "img/title.jpg"));
    bgObj->AddComponent(new CameraFollower(*bgObj));
    AddObject(bgObj);

    auto fontObj = new GameObject(1);
    SDL_Color red = {255, 0, 0, 255};
    auto text = new Text(*fontObj, "font/Call me maybe.ttf", 40, Text::TextStyle::SOLID, "Press space bar to start!", red);
    fontObj->AddComponent(text);
    auto callback = [text] {
        auto color = text->GetColor();
        color.a = (uint8) (color.a == 255 ? 0 : 255);
        text->SetColor(color);
        text->RemakeTexture();
    };
    fontObj->AddComponent(new EventTimer(*fontObj, 0.6, callback));
    fontObj->box.x = WIDTH/2 - fontObj->box.w/2;
    fontObj->box.y = HEIGHT/2;
    AddObject(fontObj);
}

TitleState::~TitleState() = default;

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
    Camera::pos = Vec2(0, 0);
}

void TitleState::LoadAssets() {

}
