#include <iostream>
#include <Log.h>
#include <Vec2.h>
#include <Rect.h>
#include "Game.h"

int main(int argc, char **argv) {
    try {
        Game::GetInstance().Run();
    } catch (string ex) {
        Log::LogError(ex);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}