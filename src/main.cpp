#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <cstdio>

#include "../include/constants.h"
#include "../include/debug.h"
#include "../include/glutCallbacks.h"
#include "../include/platform.h"
#include "../libs/tinyxml2/tinyxml2.h"
#include "_main.h"

void init() {
    glClearColor(0.f, 0.f, 0.f, 1.f);

    glMatrixMode(GL_PROJECTION);
    glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, WINDOW_HEIGHT, -WINDOW_HEIGHT, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

bool svgIsRect(const char* tag) { return !strcmp(tag, "rect"); }
bool svgIsCircle(const char* tag) { return !strcmp(tag, "circle"); }

bool svgIsTag(const char* attr, const char* target) {
    return !strcmp(attr, target);
}

void loadArena(char* file) {
    printf("attempting to load arena from file %s\n", file);
    FILE* filePointer = fopen(file, "rb");

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
                context->getGameRef()->addPlatform(p);
            }
            if (svgIsTag(currentNode->Attribute("fill"), SVG_PLAYABLE_AREA)) {
                // Platform* p0 =
                //     new Platform(currentNode->IntAttribute("x"),
                //                  currentNode->IntAttribute("y") - 1,
                //                  currentNode->IntAttribute("width"), 1);
                // Platform* p1 =
                //     new Platform(currentNode->IntAttribute("x") - 1,
                //                  currentNode->IntAttribute("y") + 1, 1,
                //                  currentNode->IntAttribute("height") + 1);
                // context->getGameRef()->addPlatform(p0);
                // context->getGameRef()->addPlatform(p1);
            }
        } else if (svgIsCircle(currentNode->Name())) {
            if (svgIsTag(currentNode->Attribute("fill"), SVG_PLAYER)) {
                context->getGameRef()->createPlayer(
                    currentNode->IntAttribute("cx"),
                    currentNode->IntAttribute("cy"),
                    currentNode->IntAttribute("r"));
            }
        }
        currentNode = currentNode->NextSiblingElement();
    }
    fclose(filePointer);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("Usage: %s <arena file>\n", argv[0]);
        return 1;
    }

    static const char* header =
        "\n\n########################################################## \n\
#                 Mario Shooter 2D                       # \n\
#        %s        # \n\
#        compiled at %s           # \n\
########################################################## \
            \n\n";
    printf(header, GIT_HASH, COMPILE_TIME);

    context = new GlobalCtx(WINDOW_WIDTH, WINDOW_HEIGHT);

    loadArena(argv[1]);

    setupGlut(argc, argv);
    init();

    glutMainLoop();

    delete (context);
    return 0;
}