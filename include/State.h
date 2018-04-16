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
    void Start();
    weak_ptr<GameObject> AddObject(GameObject *obj);
    weak_ptr<GameObject> AddObject(shared_ptr<GameObject> obj);
    weak_ptr<GameObject> GetObjectPtr(GameObject *obj);
    shared_ptr<GameObject> PopObjectPtr(GameObject *obj);
    void LoadAssets();
    void Update(float dt);
    void Render();
  private:
    Music music;
    bool quitRequested;
    bool started;
    TileMap *tileMap;
    GameObject *bg;
    map<int, vector<shared_ptr<GameObject>>> objectArray;
};

#endif