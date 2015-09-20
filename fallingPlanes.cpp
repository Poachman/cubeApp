#include "fallingPlanes.h"

fallingPlanes::fallingPlanes() {}

void fallingPlanes::doFrame() {
  int speed = 1;
  this->cube.drawBackground(Color(RGBv(0,0,0)));

  if(this->frame / speed % 90 < 30) {
    if(this->frame / speed % 30 < 15) {
      for(int z = 0; z < 16; z++)
        this->cube.drawLine(Point(0,0,z), Point(this->frame / speed % 15, 15, z), c);
    } else {
      for(int z = 0; z < 16; z++)
        this->cube.drawLine(Point(0,0,z), Point(15, 15 - this->frame / speed % 15, z), c);
    }
  } else if(this->frame / speed % 90 < 60) {
    if(this->frame / speed % 30 < 15) {
      for(int z = 0; z < 16; z++)
        this->cube.drawLine(Point(z,0,0), Point(z, this->frame / speed % 15, 15), c);
    } else {
      for(int z = 0; z < 16; z++)
        this->cube.drawLine(Point(z,0,0), Point(z, 15, 15 - this->frame / speed % 15), c);
    }
  } else {
    if(this->frame / speed % 30 < 15) {
      for(int z = 0; z < 16; z++)
        this->cube.drawLine(Point(0,z,0), Point(15, z, this->frame / speed % 15), c);
    } else {
      for(int z = 0; z < 16; z++)
        this->cube.drawLine(Point(0,z,0), Point(15 - this->frame / speed % 15, z, 15), c);
    }
  }
  this->frame++;
}
