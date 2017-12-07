#ifndef CONSTANTS
#define CONSTANTS

#define ERROR_ARGUMENTS -1
#define ERROR_CREATING_FILE -2
#define ERROR_CREATING_WALLS_NB -3
#define ERROR_CREATING_WALLS -4

#define KEY_EXIT 113 //q


#define COLOR_PLAYER bleu
#define COLOR_GOAL vert
#define COLOR_WALL rouge

#define CONST_PIXELSCALE 32

#define PLAYER_STUCK 0
#define PLAYER_VICTORY 1

typedef enum ArrowType {
    ARROWUP = 0,
    ARROWRIGHT,
    ARROWDOWN,
    ARROWLEFT,
    NONE
} ArrowType;

#endif
