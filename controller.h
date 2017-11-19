#ifndef CONTROLLER
#define CONTROLLER

#include "constants.h"
#include "gridStruct.h"

void Play(const char* filename);
ArrowType getArrow(POINT arrowInput);
Slider* initFromFile(const char* filename);

#endif
