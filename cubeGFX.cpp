#include "cubeGFX.h"

using namespace std;

cubeGFX::cubeGFX() {

}

Color cubeGFX::getVoxel(Point p) {
  return this->getVoxel(p.x, p.y, p.z);
}

Color cubeGFX::getVoxel(uint8_t x, uint8_t y, uint8_t z) {
  Color col = Color();
  if((x>=0)&&(x<SIZE))
      if((y>=0)&&(y<SIZE))
          if((z>=0)&&(z<SIZE))
          {
              int index=z*256+x*16+y;
              col.rgb.r=PIXEL_RGB[index*3+1];
              col.rgb.g=PIXEL_RGB[index*3];
              col.rgb.b=PIXEL_RGB[index*3+2];
          }
  return col;
}

void cubeGFX::drawVoxel(Point p, Color c) {
  this->drawVoxel(p.x, p.y, p.z, c);
}

void cubeGFX::drawVoxel(uint8_t x, uint8_t y, uint8_t z, Color col) {
    if((x>=0)&&(x<SIZE))
        if((y>=0)&&(y<SIZE))
            if((z>=0)&&(z<SIZE)) {
                int index=z*256+x*16+y;
                PIXEL_RGB[index*3]=col.rgb.g;
                PIXEL_RGB[index*3+1]=col.rgb.r;
                PIXEL_RGB[index*3+2]=col.rgb.b;
            }
}

void cubeGFX::drawBackground(Color c) {
  for (uint8_t x = 0; x < SIZE; x++) {
    for (uint8_t y = 0; y < SIZE; y++) {
      for (uint8_t z = 0; z < SIZE; z++) {
        this->drawVoxel(x, y, z, c);
      }
    }
  }
}

void cubeGFX::drawLine(Point p1, Point p2, Color col) {
  float dx, dy, dz, l, m, n, dx2, dy2, dz2, i, x_inc, y_inc, z_inc, err_1, err_2;
  Point currentPoint = Point(p1.x, p1.y, p1.z);
  dx = p2.x - p1.x;
  dy = p2.y - p1.y;
  dz = p2.z - p1.z;
  x_inc = (dx < 0) ? -1 : 1;
  l = abs(dx);
  y_inc = (dy < 0) ? -1 : 1;
  m = abs(dy);
  z_inc = (dz < 0) ? -1 : 1;
  n = abs(dz);
  dx2 = l * 2;
  dy2 = m * 2;
  dz2 = n * 2;

  if ((l >= m) && (l >= n)) {
    err_1 = dy2 - l;
    err_2 = dz2 - l;
    for (i = 0; i < l; i++) {
      this->drawVoxel(currentPoint, col);
      if (err_1 > 0) {
        currentPoint.y += y_inc;
        err_1 -= dx2;
      }
      if (err_2 > 0) {
        currentPoint.z += z_inc;
        err_2 -= dx2;
      }
      err_1 += dy2;
      err_2 += dz2;
      currentPoint.x += x_inc;
    }
  } else if ((m >= l) && (m >= n)) {
    err_1 = dx2 - m;
    err_2 = dz2 - m;
    for (i = 0; i < m; i++) {
      this->drawVoxel(currentPoint, col);
      if (err_1 > 0) {
        currentPoint.x += x_inc;
        err_1 -= dy2;
      }
      if (err_2 > 0) {
        currentPoint.z += z_inc;
        err_2 -= dy2;
      }
      err_1 += dx2;
      err_2 += dz2;
      currentPoint.y += y_inc;
    }
  } else {
    err_1 = dy2 - n;
    err_2 = dx2 - n;
    for (i = 0; i < n; i++) {
      this->drawVoxel(currentPoint, col);
      if (err_1 > 0) {
        currentPoint.y += y_inc;
        err_1 -= dz2;
      }
      if (err_2 > 0) {
        currentPoint.x += x_inc;
        err_2 -= dz2;
      }
      err_1 += dy2;
      err_2 += dx2;
      currentPoint.z += z_inc;
    }
  }

  this->drawVoxel(currentPoint, col);
}

void cubeGFX::drawLine(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2, Color col) {
  this->drawLine(Point(x1, y1, z1), Point(x2, y2, z2), col);
}

void cubeGFX::drawCircle(Point center, Axis axis, uint8_t radius, Color c, bool filled) {

}

void cubeGFX::drawFilledCircle(Point center, Axis axis, uint8_t radius, Color c) {
  this->drawCircle(center, axis, radius, c, true);
}

void cubeGFX::drawPlane(Plane plane, uint8_t depth, Color c) {
  switch(plane) {
    case XY:
      for(int x=0;x<SIZE;x++) {
        for(int y=0;y<SIZE;y++) {
          this->drawVoxel(x, y, depth, c);
        }
      }
    break;
    case YZ:
      for(int y=0;y<SIZE;y++) {
        for(int z=0;z<SIZE;z++) {
          this->drawVoxel(depth, y, z, c);
        }
      }
    break;
    case XZ:
      for(int x=0;x<SIZE;x++) {
        for(int z=0;z<SIZE;z++) {
          this->drawVoxel(x, depth, z, c);
        }
      }
    break;
  }
}

void cubeGFX::drawBox(Point p1, Point p2, Color c, bool filled) {
    for(int x=p1.x; x < p2.x; x++) {

    }
}

void cubeGFX::drawFilledBox(Point p1, Point p2, Color c) {
  this->drawBox(p1, p2, c, true);
}

void cubeGFX::drawSphere(Point center, uint8_t radius, Color col, bool filled) {
  float res = 30;
  for (float m = 0; m < res; m++)
    for (float n = 0; n < res; n++)
      this->drawVoxel(center.x + radius * sin((float) PI * m / res) * cos((float) 2 * PI * n / res),
        center.y + radius * sin((float) PI * m / res) * sin((float) 2 * PI * n / res),
        center.z + radius * cos((float) PI * m / res),
        col);
}

void cubeGFX::drawFilledSphere(Point center, uint8_t radius, Color c) {

}

void cubeGFX::drawCube(Point p1, Point p2, Color c, bool filled) {

}

void cubeGFX::drawCube(Point center, uint8_t radius, Color c, bool filled) {

}

void cubeGFX::drawFilledCube(Point p1, Point p2, Color c) {

}

void cubeGFX::drawFilledCube(Point center, uint8_t radius, Color c) {

}
