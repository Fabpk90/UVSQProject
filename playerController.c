#include <uvsqgraphics.h>

#include "gridStruct.h"
#include "constants.h"
#include "playerController.h"
#include "vectorUtil.h"

//pas de récursif ici, la mémoire serait gachée
//iteratif, moche, mais niveau mémoire c'est mieux

int8_t
movePlayer (Slider * slider, ArrowType arrowDirection)
{
  int8_t result = -1;
  Wall *wall;

  wall = getBlockingBlock (slider, arrowDirection);
  move (slider, wall, arrowDirection);

  affiche_all ();
  return result;
}

//cycle thru walls, and see if there is any on the path
//find the nearest blocking block, and goes to it
Wall *
getBlockingBlock (Slider * slider, ArrowType direction)
{

}

void
checkWall (Wall * nearestWall, Slider * slider, Wall * wall,
	   ArrowType direction)
{
  //check if the block is on the way, according to the direction
  /*switch (direction) {
     case ARROWDOWN:
     if (list->wall.position.x == slider->playerPos.x
     && list->wall.position.y - slider->playerPos.y > 0) {
     if (nearestWall != NULL) {
     if (nearestWall->position.y <
     list->wall.position.y)
     nearestWall = &list->wall;
     } else
     nearestWall = &list->wall;
     }
     break;
     } */
}

//TODO: animation
//move step by step and stops when cannot move
void
move (Slider * slider, Wall * wall, ArrowType direction)
{

  slider->playerPos.x += 1;
  /*if (wall != NULL) {

     } else                       // go to the end of the screen
     {

     } */
}
