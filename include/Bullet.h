#ifndef T1_BULLET_H
#define T1_BULLET_H


#include <GameObject.h>
#include <Vec2.h>

#define BULLET_TYPE "Bullet"

class Bullet : public Component {
public:
    Bullet(GameObject &associated,
           float angle,
           float speed,
           int damage,
           float maxDistance,
           string sprite,
           int frameCount,
           float frameTime);

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;

    int GetDamage();

private:
    Vec2 speed;
    float distanceLeft;
    int damage;
};


#endif //T1_BULLET_H
