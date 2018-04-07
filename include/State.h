#include <memory>
#include <vector>
#include <map>
#include "Music.h"
#include "TileMap.h"

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
    void AddObject(int mouseX, int mouseY);
    Music music;
    bool quitRequested;
    TileMap *tileMap;
    GameObject *bg;
    map<int, vector<unique_ptr<GameObject>>> objectArray;
};

#endif
