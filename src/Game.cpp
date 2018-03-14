#include <iostream>
#define INCLUDE_SDL_IMAGE
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"
#include "Game.h"

using namespace std;

Game::Game(string title, int width, int height) {
    if (Game::instance != nullptr) {
        Game::instance = this;

        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0) {
            //TODO: LOG ERROR
        }

        // Initialize SDL_IMG
        if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) != (IMG_INIT_JPG | IMG_INIT_PNG)) {
            //TODO: LOG ERROR
        }

        // Initialize SDL_MIXER
        if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG) {
            //TODO: LOG ERROR
        }
        if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0) {
            //TODO: LOG ERROR
        }
        Mix_AllocateChannels(32);

        // Create SDL_Window
        window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                  width, height, 0);
        if (window == nullptr) {
            //TODO: LOG ERROR
        }

        // Create SDL_Renderer
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == nullptr) {
            //TODO: LOG ERROR
        }

        //Initialize state
        state = new State();
    } else {
        //TODO: LOG ERROR (2 instances of game class)
    }
}

Game::~Game() {
    delete state;

    // Destroy window and renderer
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    // Destroy SDL_Mixer
    Mix_CloseAudio();
    Mix_Quit();

    // Destroy SDL_Img
    IMG_Quit();
}

State* Game::GetState() {
    return state;
}

void Game::Run() {
    State *state = GetState();
    while (state->QuitRequested()) {
        state->Update(0);
        state->Render();
        SDL_RenderPresent(renderer);
        SDL_Delay(33);
    }
}

SDL_Renderer* Game::GetRenderer() {
    return renderer;
}

Game *Game::GetInstance() {
    if (Game::instance == nullptr) {
        return new Game(GAME_NAME, WIDTH, HEIGHT);
    }

    return Game::instance;
}