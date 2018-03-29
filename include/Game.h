#define INCLUDE_SDL
#include "SDL_include.h"
#include "State.h"

#define ASSETS_PATH "assets/"

#define GAME_NAME "14/0039678"
#define WIDTH 1024
#define HEIGHT 600

#define ASSETS_PATH "assets/"

#ifndef GAME_CLASS
#define GAME_CLASS

class Game {
  public:
    ~Game();
    static Game& GetInstance();
    void Run();
    SDL_Renderer *GetRenderer();
    State& GetState();
  private:
    Game(string title, int width, int height);
    static Game *instance;
    SDL_Window *window;
    SDL_Renderer *renderer;
    State *state;
};

#endif