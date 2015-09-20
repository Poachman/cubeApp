#include "cubePattern.h"
#include "cubeGFX.h"

class planes : public cubePattern {
public:
    planes();
    void doFrame();
    Color c = Color(HSV(0,0,0));
};
