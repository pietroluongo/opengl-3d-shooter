#include "../include/map.h"

Map::Map() {}

Map::~Map() {
    for (auto platform : this->platforms) {
        delete (platform);
    }
}

void Map::addPlatform(Platform* platform) {
    this->platforms.push_back(platform);
}

void Map::draw() {
    for (auto platform : this->platforms) {
        platform->draw();
    }
}