//
// Created by ftfnunes on 09/05/18.
//

#include "IntervalTimer.h"

EventTimer::EventTimer(GameObject &associated, float timeLimit, function<void()> callback) : Component(associated),
                                                                                             timer(),
                                                                                             callback(callback),
                                                                                             timeLimit(timeLimit) { }

void EventTimer::Update(float dt) {
    timer.Update(dt);

    if (timer.Get() > timeLimit) {
        callback();
        timer.Restart();
    }
}

void EventTimer::Render() {}

bool EventTimer::Is(string type) {
    return false;
}
