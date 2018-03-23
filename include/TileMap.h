#ifndef T1_TILEMAP_H
#define T1_TILEMAP_H


#include <vector>
#include "Component.h"
#include "TileSet.h"

class TileMap : Component {
public:
    TileMap(GameObject &associated, string file, TileSet *tileSet);

    void Load(string file);
    void SetTileSet(TileSet *tileSet);
    int &At(int x, int y, int z = 0);
    void Render();
    void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);
    int GetWidth();
    int GetHeight();
    int GetDepth;
private:
    vector<int> tileMatrix;
    TileSet *tileSet;
    int mapWidth;
    int mapHeight;
    int mapDepth;

};


#endif //T1_TILEMAP_H
