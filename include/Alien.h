//
// Created by ftfnunes on 01/04/18.
//

#ifndef T1_ALIEN_H
#define T1_ALIEN_H


#include <queue>
#include <vector>
#include <memory>
#include "Component.h"
#include "Vec2.h"

class Alien : public Component {
public:
    explicit Alien(GameObject &associated, int nMinions);

    void Update(float dt) override;
    void Start() override;
    void Render() override;
    bool Is(string type) override;

private:
    class Action {
    public:
        enum ActionType {MOVE, SHOOT};
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
