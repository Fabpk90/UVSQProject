#ifndef GRIDSTRUCT
#define GRIDSTRUCT

typedef enum WallDirection
{
  WALLUP = 0,
  WALLRIGHT = 3,
  WALLDOWN = 6,
  WALLLEFT = 9
} WallDirection;

typedef struct Wall
{
  POINT position;
  WallDirection direction;
} Wall;

typedef struct Slider
{
  POINT resolution;
  Wall *walls;
  uint nbWalls;
  POINT playerPos;
  POINT goalPos;
  int8_t isMoving;
} Slider;

#endif
