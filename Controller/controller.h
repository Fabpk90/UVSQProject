#ifndef CONTROLLER
#define CONTROLLER

BOOL Play(const char *filename);
ArrowType getArrow(POINT arrowInput);
Slider *initFromFile(const char *filename);

#endif
