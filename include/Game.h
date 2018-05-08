#define INCLUDE_SDL

#include <stack>
#include <memory>
#include "SDL_include.h"
#include "State.h"

#define GAME_NAME "Fernando_14/0039678"
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

    State &GetCurrentState();

    void Push(State *state);

    float GetDeltaTime();
  private:
    static Game *instance;

    Game(string title, int width, int height);
    void CalculateDeltaTime();
    State *push();

    State *storedState;
    stack<unique_ptr<State>> stateStack;

    SDL_Window *window;
    SDL_Renderer *renderer;
    int framestart;
    float dt;
};

#endif