//
// Created by ftfnunes on 04/04/18.
//

#ifndef T1_ALIEN_H
#define T1_ALIEN_H


#include <GameObject.h>
#include <queue>
#include <memory>
#include "Vec2.h"
#include "Bullet.h"
#include "Timer.h"

#define ALIEN_TYPE "Alien"
#define ALIEN_SPEED 100
#define ALIEN_ROTATION_SPEED -10
#define ALIEN_COOLDOWN 1

class Alien : public Component {
public:
    explicit Alien(GameObject &associated, int nMinions);
    ~Alien();

    void Start() override;

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;

    void NotifyCollision(GameObject &other) override;

    int GetHp();

    static int alienCount;
private:
    enum AlienState { MOVING, RESTING };

    AlienState state;
    Timer restTimer;
    Vec2 destination;
    Vec2 speed;
    int hp;
    int nMinions;

    vector<weak_ptr<GameObject>> minionArray;
};

#endif //T1_ALIEN_H
