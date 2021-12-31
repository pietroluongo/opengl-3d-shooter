#include "../include/map.h"
#include "../include/constants.h"
#include "../include/globalCtx.h"
#include "../libs/tinyxml2/tinyxml2.h"

#include <cstring>

extern GlobalCtx* context;

bool svgIsRect(const char* tag) { return !strcmp(tag, "rect"); }
bool svgIsCircle(const char* tag) { return !strcmp(tag, "circle"); }

bool svgIsTag(const char* attr, const char* target) {
    return !strcmp(attr, target);
}

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

void Map::loadArena(char* fileName) {
    printf("attempting to load arena from file %s\n", fileName);
    FILE* filePointer = fopen(fileName, "rb");

    tinyxml2::XMLDocument doc;
    doc.LoadFile(filePointer);
    tinyxml2::XMLElement* root = doc.FirstChildElement();
    tinyxml2::XMLElement* currentNode = root->FirstChildElement();

    while (currentNode != NULL) {
        if (svgIsRect(currentNode->Name())) {
            if (svgIsTag(currentNode->Attribute("fill"), SVG_BARRIER)) {
                Platform* p = new Platform(currentNode->IntAttribute("x"),
                                           currentNode->IntAttribute("y"),
                                           currentNode->IntAttribute("width"),
                                           currentNode->IntAttribute("height"));
                context->getGameRef()->getMap()->addPlatform(p);
            }
            if (svgIsTag(currentNode->Attribute("fill"), SVG_PLAYABLE_AREA)) {
                int x, y, w, h;
                x = currentNode->IntAttribute("x");
                y = currentNode->IntAttribute("y");
                w = currentNode->IntAttribute("width");
                h = currentNode->IntAttribute("height");
                Platform* p0 = new Platform(x, y - 1, w, 1);
                Platform* p1 = new Platform(x - 1, y - 1, 1, h + 1);
                Platform* p2 = new Platform(x, y + h, w, 1);
                Platform* p3 = new Platform(x + w, y - 1, 1, h + 1);
                this->addPlatform(p0);
                this->addPlatform(p1);
                this->addPlatform(p2);
                this->addPlatform(p3);
            }
        } else if (svgIsCircle(currentNode->Name())) {
            if (svgIsTag(currentNode->Attribute("fill"), SVG_PLAYER)) {
                context->getGameRef()->createPlayer(
                    currentNode->IntAttribute("cx"),
                    currentNode->IntAttribute("cy"),
                    currentNode->IntAttribute("r"));
            } else if (svgIsTag(currentNode->Attribute("fill"), SVG_ENEMY)) {
                context->getGameRef()->createEnemy(
                    currentNode->IntAttribute("cx"),
                    currentNode->IntAttribute("cy"),
                    currentNode->IntAttribute("r"));
            }
        }
        currentNode = currentNode->NextSiblingElement();
    }
    fclose(filePointer);
}

std::vector<Platform*> Map::getPlatforms() { return this->platforms; }