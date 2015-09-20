#include "cubePattern.h"
#include "cubeGFX.h"

class fading : public cubePattern {
public:
    fading();
    void doFrame();
    Color c = Color(HSV(0,0,0));
};
