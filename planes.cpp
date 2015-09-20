#include "planes.h"

planes::planes() {}

void planes::doFrame() {
    c = Color(HSV(this->frame % 255, 255, 20));
    this->cube.drawPlane(Plane::XY, ((frame / 3 % SIZE) - 1) == -1 ? 15 : (frame / 3 % SIZE) - 1, Color(RGBv(0,0,0)));
    this->cube.drawPlane(Plane::YZ, ((frame / 2 % SIZE) - 1) == -1 ? 15 : (frame / 2 % SIZE) - 1, Color(RGBv(0,0,0)));

    this->cube.drawPlane(Plane::XY, frame / 3 % SIZE, c);
    this->cube.drawPlane(Plane::YZ, frame / 2 % SIZE, c);
    this->frame++;
}
