cmake_minimum_required(VERSION 3.9)
project(T1)

set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
link_libraries(SDL2 SDL2_image SDL2_ttf SDL2_mixer)
include_directories(/usr/include/SDL2)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

include_directories(BEFORE include)

add_executable(140039678-Fernando src/Game.cpp
                src/Log.cpp
                src/Main.cpp
                src/Music.cpp
                src/Sprite.cpp
                src/State.cpp src/Vec2.cpp include/Vec2.h src/Rect.cpp include/Rect.h src/Component.cpp include/Component.h src/GameObject.cpp include/GameObject.h src/Sound.cpp include/Sound.h src/Face.cpp include/Face.h include/Component.h src/TileSet.cpp include/TileSet.h src/TileMap.cpp include/TileMap.h src/Resources.cpp include/Resources.h)
