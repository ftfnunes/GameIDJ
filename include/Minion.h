//
// Created by ftfnunes on 05/04/18.
//

#ifndef T1_MINION_H
#define T1_MINION_H


#include "GameObject.h"

#define MINION_ANG_SPEED M_PI/6

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
