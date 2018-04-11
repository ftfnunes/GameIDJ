//
// Created by ftfnunes on 11/04/18.
//

#ifndef T1_LAYERMODIFIER_H
#define T1_LAYERMODIFIER_H

#define LAYER_MODIFIER_TYPE "LayerModifier"

#include <unordered_map>
#include "Component.h"
#include "Vec2.h"

class LayerModifier : public Component {
public:
    explicit LayerModifier(GameObject &associated);

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;

    void SetModifier(int layer, float modifier);

    Vec2 GetCameraWithModifier(int layer);

private:
    unordered_map<int, float> modifiers;
};


#endif //T1_LAYERMODIFIER_H
