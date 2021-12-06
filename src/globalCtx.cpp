#include "../include/globalCtx.h"

GlobalCtx::GlobalCtx(GLint w, GLint h) {
    this->windowHeight = h;
    this->windowWidth = w;
}

glivec2 GlobalCtx::getWindowSize() {
    return glivec2(this->windowWidth, this->windowHeight);
}
