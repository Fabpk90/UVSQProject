#ifndef PLAYER
#define PLAYER

uint8_t movePlayer(Slider * slider, POINT direction);
void addPlay(Player *player, POINT lastPos);
BOOL undoPlay(Player *player);
#endif
