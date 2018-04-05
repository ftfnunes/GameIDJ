//
// Created by ftfnunes on 29/03/18.
//

#ifndef T1_CAMERA_H
#define T1_CAMERA_H


#include "GameObject.h"

#define CAMERA_SPEED 600

class Camera {
public:
    static void Follow(GameObject *newFocus);
    static void Unfollow();
    static void Update(float dt);

    static Vec2 pos;
    static Vec2 speed;
private:
    static GameObject *focus;

};


#endif //T1_CAMERA_H
