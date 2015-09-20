#include "fading.h"

fading::fading() {}

void fading::doFrame() {
    c = Color(HSV(this->frame % 255, 255, 20));
    this->cube.drawBackground(c);
    this->frame++;
}
