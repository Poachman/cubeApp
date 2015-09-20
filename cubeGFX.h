#include <stdint.h>
#include <cmath>
#include "config.h"

#ifndef cubegfx
#define cubegfx

struct Point {
  uint8_t x,y,z;
  Point() : x(0), y(0), z(0) {}
  Point(uint8_t x,uint8_t y,uint8_t z) : x(x), y(y), z(z) {}
};

struct RGBv {
  uint8_t r,g,b;
  RGBv() : r(0), g(0), b(0) {}
  RGBv(uint8_t R, uint8_t G, uint8_t B) : r(R), g(G), b(B) {}
};

struct HSV {
  uint8_t h,s,v;
  HSV() : h(0), s(0), v(0) {}
  HSV(uint8_t H, uint8_t S, uint8_t V) : h(H), s(S), v(V) {}
};

struct Color {
  HSV hsv;
  RGBv rgb;

  Color() : rgb(RGBv()) {}
  Color(RGBv rgb) : rgb(rgb) {}
  Color(HSV hsv) : hsv(hsv), rgb(this->HSVtoRGB(hsv)) {}

  RGBv HSVtoRGB(HSV in) {
    double h, s, v;
    double r, g, b;

    h = (double)in.h / 255.;
    s = (double)in.s / 255.;
    v = (double)in.v / 255.;

    int i = int(h * 6);
    double f = h * 6 - i;
    double p = v * (1 - s);
    double q = v * (1 - f * s);
    double t = v * (1 - (1 - f) * s);

    switch(i % 6){
        case 0: r = v, g = t, b = p; break;
        case 1: r = q, g = v, b = p; break;
        case 2: r = p, g = v, b = t; break;
        case 3: r = p, g = q, b = v; break;
        case 4: r = t, g = p, b = v; break;
        case 5: r = v, g = p, b = q; break;
    }

    r *= 255;
    g *= 255;
    b *= 255;
    return RGBv((int)r, (int)g, (int)b);
  }
};

enum Plane {XY, YZ, XZ};
enum Axis {X, Y, Z};

class cubeGFX {
public:
  cubeGFX();

    //public functions
  void show();

  Color getVoxel(Point p);
  Color getVoxel(uint8_t x, uint8_t y, uint8_t z);

  void drawVoxel(Point p, Color c);
  void drawVoxel(uint8_t x, uint8_t y, uint8_t z, Color c);
  void drawBackground(Color c);
  void drawLine(Point p, Point q, Color c);
  void drawLine(uint8_t x1, uint8_t y1, uint8_t z1, uint8_t x2, uint8_t y2, uint8_t z2, Color col);
  void drawCircle(Point center, Axis axis, uint8_t radius, Color c, bool filled = false);
  void drawFilledCircle(Point center, Axis axis, uint8_t radius, Color c);
  void drawPlane(Plane plane, uint8_t depth, Color c);
  void drawBox(Point p1, Point p2, Color c, bool filled = false);
  void drawFilledBox(Point p1, Point p2, Color c);
  void drawSphere(Point center, uint8_t radius, Color c, bool filled = false);
  void drawFilledSphere(Point center, uint8_t radius, Color c);
  void drawCube(Point p1, Point p2, Color c, bool filled = false);
  void drawCube(Point center, uint8_t radius, Color c, bool filled = false);
  void drawFilledCube(Point p1, Point p2, Color c);
  void drawFilledCube(Point center, uint8_t radius, Color c);

  uint8_t PIXEL_RGB[NUM_STRIPS * NUM_LEDS_PER_STRIP * 3];

};
#endif
