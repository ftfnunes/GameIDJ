#ifndef T1_FACE_H
#define T1_FACE_H

#define FACE_TYPE "Face"

#include "Component.h"

class Face : public Component {
public:
    explicit Face(GameObject &associated);

    void Damage(int damage);

    void Update(float dt) override ;
    void Render() override ;
    bool Is(string type) override ;

private:
    int hitpoints;
};


#endif //T1_FACE_H
