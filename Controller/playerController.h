#ifndef PLAYER
#define PLAYER

uint8_t movePlayer(Slider * slider, POINT direction);

void addPlay(Player *player);
BOOL undoPlay(Player *player);
void freePlays(Player *player);

#endif
