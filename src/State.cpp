#include <fstream>
#include <Log.h>
#include "Sprite.h"
#include "Music.h"
#include "State.h"

State::State() : bg("img/ocean.jpg"), music("audio/stageState.ogg") {
    quitRequested = false;
    music.Play();
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg.Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}

State::~State() {
    Log::LogMessage("Deletando state");
}