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
    Sprite *bg;
    Music *music;
    bool quitRequested;
};

#endif
