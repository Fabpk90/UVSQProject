#ifndef FICHIER
#define FICHIER

#include "gridStruct.h"

void drawGame(int height, int width);

void drawMap(int height, int width);
void drawWalls(WallList* walls);

void drawPlayernGoal(POINT player, POINT goal);

#endif
