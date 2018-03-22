#include "TileSet.h"
#include "GameObject.h"

TileSet::TileSet(int tileWidth, int tileHeight, string file) : tileWidth(tileWidth),
                                                               tileHeight(tileHeight),
                                                               tileSet(*new GameObject(), file) {
    columns = tileSet.GetWidth() / tileWidth;
    rows = tileSet.GetHeight() / tileHeight;
}

void TileSet::RenderTile(unsigned int index, float x, float y) {
    int maxRange = columns*rows;
    if (index < 0 && index > maxRange-1) {
        throw "indice " + to_string(index) + " esta fora dos limites [0," + to_string(maxRange) +"].";
    }

    int column = index % columns;
    int row = index / columns;

    tileSet.SetClip(column*tileWidth, row*tileHeight, tileWidth, tileHeight);
    tileSet.Render();
}

int TileSet::GetTileHeight() {
    return tileHeight;
}

int TileSet::GetTileWidth() {
    return tileWidth;
}
