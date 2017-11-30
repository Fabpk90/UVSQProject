#ifndef CONTROLLER
#define CONTROLLER

#include "../Util/constants.h"
#include "../Util/gridStruct.h"

void Play(const char *filename);
ArrowType getArrow(POINT arrowInput);
Slider *initFromFile(const char *filename);

#endif
