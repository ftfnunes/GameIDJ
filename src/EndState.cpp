#include <Music.h>
#include <Sprite.h>
#include <CameraFollower.h>
#include <Game.h>
#include <InputManager.h>
#include <TitleState.h>
#include <Camera.h>
#include "EndState.h"
#include "GameData.h"
#include "Text.h"

EndState::EndState() : State(), backgroundMusic() {
    string musicFile, bgFile, instructions;
    if (GameData::playerVictory) {
        musicFile = "audio/endStateWin.ogg";
        bgFile = "img/win.jpg";
        instructions = "Press space bar to play again or escape to exit!";
    } else {
        musicFile = "audio/endStateLose.ogg";
        bgFile = "img/lose.jpg";
        instructions = "Press space bar to try again or escape to give up!";
    }

    backgroundMusic.Open(musicFile);
    auto bgObj = new GameObject();
    bgObj->AddComponent(new Sprite(*bgObj, bgFile));
    bgObj->AddComponent(new CameraFollower(*bgObj));
    AddObject(bgObj);

    auto fontObj = new GameObject(1);
    SDL_Color red = {255, 0, 0, 255};
    fontObj->AddComponent(new Text(*fontObj, "font/Call me maybe.ttf", 40, Text::TextStyle::SOLID, instructions, red));
    fontObj->box.x = WIDTH/2 - fontObj->box.w/2;
    fontObj->box.y = HEIGHT/2 + 50;
    AddObject(fontObj);

    backgroundMusic.Play();
}

EndState::~EndState() {
}

void EndState::LoadAssets() {
}

void EndState::Update(float dt) {
    auto inputManager = InputManager::GetInstance();

    quitRequested = inputManager.KeyPress(ESCAPE_KEY) || inputManager.QuitRequested();

    if (inputManager.KeyPress(SPACE_KEY)) {
        popRequested = true;
        Game::GetInstance().Push(new TitleState());
    }
}

void EndState::Render() {
    RenderArray();
}

void EndState::Start() {
    Camera::pos = Vec2(0, 0);
    StartArray();
}

void EndState::Pause() {

}

void EndState::Resume() {

}
