#include <fstream>
#include <Log.h>
#include "Sprite.h"
#include "Music.h"
#include "State.h"

State::State() {
    quitRequested = false;
    bg = new Sprite("img/ocean.jpg");
    music = new Music("audio/stageState.ogg");
    music->Play();
    Log::LogMessage("State criado");
}

void State::LoadAssets() {
}

void State::Update(float dt) {
    quitRequested = SDL_QuitRequested();
}

void State::Render() {
    bg->Render(0, 0);
}

bool State::QuitRequested() {
    return quitRequested;
}

State::~State() {
    Log::LogMessage("Deletando state");
    delete music;
    delete bg;
}