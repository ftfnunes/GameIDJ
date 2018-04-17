//
// Created by ftfnunes on 05/04/18.
//

#ifndef T1_MINION_H
#define T1_MINION_H

#include "Vec2.h"
#include <memory>

#define MINION_ANG_SPEED M_PI/6
#define ORBIT_RADIUS 100
#define MINION_TYPE "Minion"

#define MINION_BULLET_SPEED 300
#define MINION_BULLET_DISTANCE 600
#define MINION_BULLET_DAMAGE 10

class Minion : public Component {
public:
    Minion(GameObject &associated, weak_ptr<GameObject> alienCenter, float arcOffsetDeg);

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;

    void Shoot(Vec2 target);

private:
    GameObject &alienCenter;
    float arc;
};


#endif //T1_MINION_H
