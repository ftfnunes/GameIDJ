//
// Created by ftfnunes on 29/03/18.
//

#ifndef T1_CAMERA_H
#define T1_CAMERA_H


#include "GameObject.h"
#include <unordered_map>
#define CAMERA_SPEED 600

class Camera {
public:
    static void Follow(GameObject *newFocus);
    static void Unfollow();
    static void Update(float dt);

    static void SetModifier(int layer, float modifier);
    static Vec2 GetPosWithModifier(int layer);

    static Vec2 pos;
    static Vec2 speed;
private:
    static GameObject *focus;
    static unordered_map<int, float> modifiers;
};


#endif //T1_CAMERA_H
