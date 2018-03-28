#include <memory>
#include <vector>
#include "Sprite.h"
#include "Music.h"

#ifndef STATE_CLASS
#define STATE_CLASS

class State {
  public:
    State();
    ~State();
    bool QuitRequested();
    void LoadAssets();
    void Update(float dt);
    void Render();
  private:
    void Input();
    void AddObject(int mouseX, int mouseY);
    Music music;
    bool quitRequested;
    vector<unique_ptr<GameObject>> objectArray;
};

#endif
