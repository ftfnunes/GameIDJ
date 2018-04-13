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

    static void SetLayerHeight(int layer, float height);
    static Vec2 GetRenderPosition(int layer, Vec2 absolutePos);
    static void SetCameraHeight(float height);

    static Vec2 pos;
    static Vec2 speed;
private:
    static GameObject *focus;
    static float cameraHeight;
    static unordered_map<int, float> layerHeights;
};


#endif //T1_CAMERA_H
