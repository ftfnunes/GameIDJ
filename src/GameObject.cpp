#include <algorithm>
#include "GameObject.h"

GameObject::GameObject() : isDead(false), started(false), angleDeg(0) {
}

GameObject::~GameObject() {
    for(auto it = components.rbegin(); it != components.rend(); ++it) {
        (*it).reset();
    }
}

void GameObject::Update(float dt) {
    for(auto it = components.begin(); it != components.end(); ++it) {
        (*it)->Update(dt);
    }
}

void GameObject::Render() {
    for(auto it = components.begin(); it != components.end(); ++it) {
        (*it)->Render();
    }
}

bool GameObject::IsDead() {
    return isDead;
}

void GameObject::RequestDelete() {
    isDead = true;
}

void GameObject::AddComponent(Component *cpt) {
    if (started) {
        cpt->Start();
    }
    components.emplace_back(cpt);
}

void GameObject::RemoveComponent(Component *cpt) {
    unique_ptr<Component>& p = *new unique_ptr<Component>(cpt);
    components.erase(std::remove(components.begin(), components.end(), p), components.end());
}

Component *GameObject::GetComponent(string type) {
    for(auto it = components.begin(); it != components.end(); ++it) {
        if ((*it)->Is(type)) {
            return (*it).get();
        }
    }
    return nullptr;
}

void GameObject::Start() {
    for(auto it = components.begin(); it != components.end(); ++it) {
        (*(*it)).Start();
    }
    started = true;
}
