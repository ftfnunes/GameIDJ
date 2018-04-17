//
// Created by ftfnunes on 16/04/18.
//

#ifndef T1_PENGUINBODY_H
#define T1_PENGUINBODY_H

#include <memory>
#include "GameObject.h"
#include "Vec2.h"

#define ACCELERATION 200
#define MAX_SPEED 500
#define BODY_ANGULAR_SPEED 150
#define BODY_TYPE "PenguinBody"

class PenguinBody : public Component {
public:
    explicit PenguinBody(GameObject &associated);

    ~PenguinBody() override;

    void Start() override;

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;

    static PenguinBody *player;

private:
    // TODO: Faz sentido ser um weak_ptr?
    shared_ptr<GameObject> pCannon;
    shared_ptr<GameObject> associatedPtr;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;
};


#endif //T1_PENGUINBODY_H
