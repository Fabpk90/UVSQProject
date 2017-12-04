#ifndef CONTROLLER
#define CONTROLLER

void Play(const char *filename);
ArrowType getArrow(POINT arrowInput);
Slider *initFromFile(const char *filename);

#endif
