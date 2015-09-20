#include "cubeGFX.h"

#ifndef cubepattern
#define cubepattern
class cubePattern {
public:
  void doFrame();
  cubeGFX cube;
protected:
  int frame = 0;
};
#endif
