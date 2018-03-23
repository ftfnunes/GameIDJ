#include <fstream>
#include <Game.h>
#include "TileMap.h"

TileMap::TileMap(GameObject &associated, string file, TileSet *tileSet) : Component(associated),
                                                                          tileSet(tileSet) {
    Load(file);
}

void TileMap::SetTileSet(TileSet *tileSet) {
    this->tileSet = tileSet;
}

int& TileMap::At(int x, int y, int z) {
    int index = x + mapWidth*y + mapWidth*mapHeight*z;
    return tileMatrix[index];
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY) {
    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; ++j) {
            int x = i*tileSet->GetTileWidth() - cameraX;
            int y = j*tileSet->GetTileHeight() - cameraY;
            if (x > -tileSet->GetTileWidth() && y > -tileSet->GetTileHeight()) {
                tileSet->RenderTile(At(i, j, layer), x, y);
            }
        }
    }
}

void TileMap::Load(string file) {
    ifstream f(file);
    string line;
    int w, h, d;

    if (f.is_open()) {
        if (!getline(f, line)) {
            throw "Error reading dimensions from " + file;
        }

        if (sscanf(line.c_str(), "%d,%d,%d", &w, &h, &d) != 3) {
            throw "Invalid dimensions on file " + file;
        }

        for (int i = 0; i < d; ++i) {
            for (int j = 0; j < h; ++j) {
                if (!getline(f, line)) {
                    throw "Error while reading from file " + file;
                }
                string buff{""};
                for(auto n:line) {
                    if(n != ',') buff+=n; else
                    if(n == ',' && buff != "") { tileMatrix.push_back(atoi(buff.c_str())-1); buff = ""; }
                }
                if(buff != "") tileMatrix.push_back(atoi(buff.c_str())-1);
            }
            if (!getline(f, line) && line != "") {
                throw "Error in file format in " + file;
            }
        }
    }
}