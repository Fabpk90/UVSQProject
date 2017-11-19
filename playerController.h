#ifndef PLAYER
#define PLAYER

int8_t movePlayer (Slider * slider, ArrowType arrowDirection);
Wall *getBlockingBlock (Slider * slider, ArrowType direction);
uint8_t checkIfGoal (Slider * slider);

void checkWall (Wall * nearestWall, Slider * slider, Wall * wall,
		ArrowType direction);
void move (Slider * slider, Wall * wall, ArrowType direction);

#endif
