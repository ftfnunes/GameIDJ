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
           float frameTime,
           bool targetsPlayer = false);

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;

    void NotifyCollision(GameObject &other) override;

    int GetDamage();

    bool TargetsPlayer();
private:
    Vec2 speed;
    float distanceLeft;
    int damage;
    bool targetsPlayer;
};


#endif //T1_BULLET_H
