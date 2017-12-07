#ifndef GRIDSTRUCT
#define GRIDSTRUCT

typedef struct Vec2{
  int x;
  int y;
}POINT;

typedef enum WallDirection {
    WALLUP = 0,
    WALLRIGHT = 1,
    WALLDOWN = 2,
    WALLLEFT = 3
} WallDirection;

typedef struct Wall {
    POINT position;
    WallDirection direction;
} Wall;

typedef struct Player
{
	POINT position;

	//used for knowing if it has reached his destination
	//if null, no destination
	Wall *wall;
}Player;

typedef struct Slider {
    POINT resolution;
    Wall *walls;
    uint nbWalls;
    Player player;
    POINT goalPos;
} Slider;

#endif
