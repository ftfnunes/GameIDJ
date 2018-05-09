//
// Created by ftfnunes on 09/05/18.
//

#ifndef T1_ENDSTATE_H
#define T1_ENDSTATE_H


#include "State.h"

class EndState : public State {
public:
    EndState();

    ~EndState() override;

    void LoadAssets() override;

    void Update(float dt) override;

    void Render() override;

    void Start() override;

    void Pause() override;

    void Resume() override;
private:
    Music backgroundMusic;
};


#endif //T1_ENDSTATE_H
