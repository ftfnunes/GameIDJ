#ifndef T1_GAMEOBJECT_H
#define T1_GAMEOBJECT_H

#include <vector>
#include <memory>
#include "Rect.h"
#include "Component.h"

using namespace std;

class GameObject {
public:
    GameObject();
    ~GameObject();

    void Update(float dt);
    void Render();
    bool IsDead();
    void Start();
    void RequestDelete();
    void AddComponent(Component* cpt);
    void RemoveComponent(Component* cpt);
    Component *GetComponent(string type);
    Rect box;
private:
    vector<unique_ptr<Component>> components;
    bool isDead;
    bool started;
};

#endif //T1_GAMEOBJECT_H
