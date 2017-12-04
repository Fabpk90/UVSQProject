#ifndef FICHIER
#define FICHIER

#include "../Util/gridStruct.h"

void drawGame(Slider * slider);
void drawCircle(POINT position, COULEUR color, int radius);


void drawWall(POINT p1, POINT p2, WallDirection direction);

#endif
