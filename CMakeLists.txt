cmake_minimum_required(VERSION 3.9)
project(GameIDJ)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(GameIDJ
        audio/boom.wav
        audio/endStateLose.ogg
        audio/endStateWin.ogg
        audio/stageState.ogg
        bin/Game.o
        bin/Log.o
        bin/Main.o
        bin/Music.o
        bin/Sprite.o
        bin/State.o
        dep/Game.d
        dep/Log.d
        dep/Main.d
        dep/Music.d
        dep/Sprite.d
        dep/State.d
        "font/Call me maybe.ttf"
        "font/License - READ THIS.txt"
        img/alien.png
        img/aliendeath.png
        img/cubngun.png
        img/lose.jpg
        img/minion.png
        img/minionbullet1.png
        img/minionbullet2.png
        img/miniondeath.png
        img/ocean.jpg
        img/penguin.png
        img/penguinbullet.png
        img/penguindeath.png
        img/penguinface.png
        img/tileset.png
        img/title.jpg
        img/win.jpg
        include/Game.h
        include/Log.h
        include/Music.h
        include/SDL_include.h
        include/Sprite.h
        include/State.h
        map/tileMap.txt
        src/Game.cpp
        src/Log.cpp
        src/Main.cpp
        src/Music.cpp
        src/Sprite.cpp
        src/State.cpp
        Makefile)
