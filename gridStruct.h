#ifndef GRIDSTRUCT
#define GRIDSTRUCT

typedef enum WallDirection
{
	UP = 0,
	RIGHT = 3,
	DOWN = 6,
	LEFT = 9 
}WallDirection;

typedef struct Wall
{
	POINT position;
	WallDirection direction; //to use with WallDirection
}Wall;

typedef struct WallList
{
	Wall wall;
	struct WallList *next;
}WallList;

typedef struct Slider
{
	WallList *walls;
	uint nbWalls;
}Slider;

#endif
