#include "Alien.h"

void Alien::Update(float dt) {

}

void Alien::Render() {

}

bool Alien::Is(string type) {
    return false;
}

Alien::Alien(GameObject &associated, int nMinions) : Component(associated) {

}

void Alien::Start() {
    Component::Start();
}
