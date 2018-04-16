#include <algorithm>
#include <Game.h>
#include "GameObject.h"

GameObject::GameObject() : GameObject(0) {}


GameObject::GameObject(int layer) : isDead(false),
                                    started(false),
                                    angleDeg(0),
                                    layer(layer) {}

GameObject::~GameObject() {
    for(auto it = components.rbegin(); it != components.rend(); ++it) {
        (*it).reset();
    }

    components.clear();
}

void GameObject::Update(float dt) {
    for(auto it = components.begin(); it != components.end(); ++it) {
        (*it)->Update(dt);
    }

    updated = true;
}

void GameObject::Render() {
    updated = false;
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

int GameObject::GetLayer() {
    return layer;
}

void GameObject::SetLayer(int layer) {
    auto &state = Game::GetInstance().GetState();
    auto obj = state.PopObjectPtr(this);
    this->layer = layer;
    if (obj) {
        state.AddObject(obj);
    }
}

bool GameObject::HasStarted() {
    return started;
}

bool GameObject::IsUpdated() {
    return updated;
}
