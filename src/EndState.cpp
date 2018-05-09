#include <Music.h>
#include <Sprite.h>
#include <CameraFollower.h>
#include <Game.h>
#include <InputManager.h>
#include <TitleState.h>
#include "EndState.h"
#include "GameData.h"
#include "Text.h"

EndState::EndState() : State(), backgroundMusic() {
    string musicFile, bgFile;
    if (GameData::playerVictory) {
        musicFile = "audio/endStateWin.ogg";
        bgFile = "img/win.jpg";
    } else {
        musicFile = "audio/endStateLose.ogg";
        bgFile = "img/lose.jpg";
    }

    backgroundMusic.Open(musicFile);
    auto bgObj = new GameObject();
    bgObj->AddComponent(new Sprite(*bgObj, bgFile));
    bgObj->AddComponent(new CameraFollower(*bgObj));
    AddObject(bgObj);

    auto fontObj = new GameObject(1);
    SDL_Color red = {255, 0, 0, 255};
    fontObj->AddComponent(new Text(*fontObj, "font/Call me maybe.ttf", 40, Text::TextStyle::SOLID, "Press space bar to try again or escape to give up!", red));
    fontObj->box.x = WIDTH/2 - fontObj->box.w/2;
    fontObj->box.y = HEIGHT/2 -100;
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

}

void EndState::Start() {

}

void EndState::Pause() {

}

void EndState::Resume() {

}
