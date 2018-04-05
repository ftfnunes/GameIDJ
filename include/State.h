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
    void Start();
    weak_ptr<GameObject> AddObject(GameObject *obj);
    weak_ptr<GameObject> GetObjectPtr(GameObject *obj);
    void LoadAssets();
    void Update(float dt);
    void Render();
  private:

    bool started;
    Music music;
    bool quitRequested;
    vector<shared_ptr<GameObject>> objectArray;
};

#endif
