#include <iostream>
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"
#include "Component.h"

using namespace std;

#ifndef SPRITE_CLASS
#define SPRITE_CLASS

#define SPRITE_TYPE "Sprite"

class Sprite : public Component {
public:
    Sprite(GameObject &associated);
    explicit Sprite(GameObject &associated, string file);
    ~Sprite() override;

    void Update(float dt);
    bool Is(string type);

    void Open(string file);
    void SetClip(int x, int y, int w, int h);
    void Render();
    void Render(float x, float y, float w, float h);
    int GetWidth();
    int GetHeight();
    bool IsOpen();
private:
    SDL_Texture *texture;
    int width;
    int height;
    SDL_Rect clipRect;
};

#endif