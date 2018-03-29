#include <fstream>
#include <Game.h>
#include <GameObject.h>
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
            Rect box = associated.box;
            if (x > -tileSet->GetTileWidth() && x < box.w && y > -tileSet->GetTileHeight() && y < box.h) {
                tileSet->RenderTile(At(i, j, layer), x, y);
            } else {
                break;
            }
        }
    }
}

void TileMap::Render() {
    for (int z = 0; z < mapDepth; ++z) {
       RenderLayer(0, associated.box.x, associated.box.y);
    }
}

void TileMap::Update(float dt) {}

bool TileMap::Is(string type) {
    return type == TILE_MAP_TYPE;
}

int TileMap::GetHeight() {
    return mapHeight;
}

int TileMap::GetWidth() {
    return mapWidth;
}

int TileMap::GetDepth() {
    return mapDepth;
}

void TileMap::Load(string file) {
    ifstream f(ASSETS_PATH + file);
    string line;
    int w, h, d;

    if (f.is_open()) {
        if (!getline(f, line)) {
            throw "Error reading dimensions from " + file;
        }

        if (sscanf(line.c_str(), "%d,%d,%d", &w, &h, &d) != 3) {
            throw "Invalid dimensions on file " + file;
        }

        mapDepth = d;
        mapHeight = h;
        mapWidth = w;

        if (!getline(f, line)) {
            throw "Error while reading from file " + file;
        }

        for (int z = 0; z < d; ++z) {
            for (int i = 0; i < h; ++i) {
                if (!getline(f, line)) {
                    throw "Error while reading from file " + file;
                }
                int j = 0;
                string buff{""};
                for(auto n:line) {
                    if (j == w) break;
                    if(n != ',') buff+=n; else
                    if(!buff.empty()) {
                        int c = atoi(buff.c_str())-1;
                        j++;
                        tileMatrix.push_back(c);
                        buff = "";
                    }
                }
                if(!buff.empty()) tileMatrix.push_back(atoi(buff.c_str())-1);
            }
            if (!getline(f, line) && !line.empty()) {
                throw "Error in file format in " + file;
            }
        }
        cout << "carregado" << endl;
    } else {
        throw "Erro ao abrir o arquivo " + file;
    }
}