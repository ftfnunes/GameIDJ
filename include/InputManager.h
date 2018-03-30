//
// Created by ftfnunes on 29/03/18.
//

#ifndef T1_INPUTMANAGER_H
#define T1_INPUTMANAGER_H


#include <unordered_map>
#define INCLUDE_SDL
#include "SDL_include.h"

#define NUM_MOUSE_BUTTONS 6
#define LEFT_ARROW_KEY      SDLK_LEFT
#define RIGHT_ARROW_KEY     SDLK_RIGHT
#define UP_ARROW_KEY        SDLK_UP
#define DOWN_ARROW_KEY      SDLK_DOWN
#define SPACE_BAR_KEY       SDLK_SPACE
#define ESCAPE_KEY          SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON   SDL_BUTTON_LEFT



using namespace std;

class InputManager {
public:
    InputManager();
    ~InputManager() = default;

    void Update();
    bool KeyPress(int key);
    bool KeyRelease(int key);
    bool IsKeyDown(int key);

    bool MousePress(int button);
    bool MouseRelease(int button);
    bool IsMouseDown(int button);

    int GetMouseX();
    int GetMouseY();

    bool QuitRequested();

    static InputManager &GetInstance();
private:
    bool mouseState[NUM_MOUSE_BUTTONS];
    int mouseUpdate[NUM_MOUSE_BUTTONS];

    unordered_map<int, bool> keyState;
    unordered_map<int, int> keyUpdate;

    bool quitRequested;
    int updateCounter;

    int mouseX;
    int mouseY;
};


#endif //T1_INPUTMANAGER_H