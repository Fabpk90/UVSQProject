#ifndef CONSTANTS
#define CONSTANTS

#define ERROR_ARGUMENTS -1
#define ERROR_CREATING_FILE -2
#define ERROR_LOADING_WALLS_NB -3
#define ERROR_LOADING_WALLS -4
#define ERROR_LOADING_BASIC_SLIDER -5 //used when the basic info of the slider are corrupted_

#define KEY_EXIT 'Q'
#define KEY_UNDO 'U'

#define KEY_EDITOR_PLAYER 'P'
#define KEY_EDITOR_GOAL 'G'
#define KEY_EDITOR_WALL 'W'
#define KEY_EDITOR_WALL_ROTATION 'R'
#define KEY_EDITOR_SAVE 'S'

#define COLOR_PLAYER bleu
#define COLOR_GOAL vert
#define COLOR_WALL rouge

#define CONST_PIXELSCALE 32
//put the bits val of the pixelscale here
#define CONST_PIXELSCALE_BITS 5
#define CONST_PIXELSCALE_HALF 16 //CONST_PIXELSCALE >> 1

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
