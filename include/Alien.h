//
// Created by ftfnunes on 04/04/18.
//

#ifndef T1_ALIEN_H
#define T1_ALIEN_H


#include <GameObject.h>
#include <queue>
#include <memory>
#include "Vec2.h"

class Alien : public Component {
public:
    explicit Alien(GameObject &associated, int nMinions);
    ~Alien();

    void Start() override;

    void Update(float dt) override;

    void Render() override;

    bool Is(string type) override;
private:
    class Action {
        enum ActionType { MOVE, SHOOT };

        Action(ActionType type, float x, float y);

        ActionType type;
        Vec2 pos;
    };

    Vec2 speed;
    int hp;

    queue<Action> taskQueue;
    vector<weak_ptr<GameObject>> minionArray;
};


#endif //T1_ALIEN_H
