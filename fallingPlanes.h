#include "cubePattern.h"
#include "cubeGFX.h"

class fallingPlanes : public cubePattern {
public:
    fallingPlanes();
    void doFrame();
    Color c = Color(HSV(180,255,20));
};
