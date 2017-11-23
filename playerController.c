#include "uvsqgraphics.h"

#include "gridStruct.h"
#include "constants.h"
#include "playerController.h"
#include "vectorUtil.h"

// mouvement, checker les murs dans la même direction
// checker le plus proche et compter les pas
// animation des pas

void move(Slider * slider, Wall * wall, POINT direction);
ArrowType getArrow(POINT arrowInput);

// pas de récursif ici, la mémoire serait gachée
// iteratif, moche, mais niveau mémoire c'est mieux

int8_t movePlayer(Slider * slider, POINT direction)
{
	int8_t result = -1;
	Wall *wall = NULL;
	
	//printf("direction: %d %d\n", direction.x, direction.y);
	
	if(direction.x != 0 || direction.y != 0)
	{

		//wall = getBlockingBlock(slider, arrowDirection);
		move(slider, wall, direction);

		affiche_all();
	}
	


	return result;
}

// TODO: animation
// move step by step and stops when cannot move
void move(Slider * slider, Wall * wall, POINT direction)
{
	POINT p; p=slider->playerPos;
	addVec(p, direction);
	
	printf("%d %d", p.x, p.y);
	
	if(p.x >= 0 && p.x < (slider->resolution.x / CONST_PIXELSCALE) 
	&& p.y >= 0 && p.y <= (slider->resolution.y / CONST_PIXELSCALE) )
	slider->playerPos = p;
	
	
	if (wall != NULL) {

	} else			// go to the end of the screen
	{

	}
}


ArrowType getArrow(POINT arrowInput)
{
    if (arrowInput.x != 0)	//left or right
    {
	if (arrowInput.x > 0)
	    return ARROWRIGHT;
	else
	    return ARROWLEFT;
    } else if (arrowInput.y != 0) {
	if (arrowInput.y > 0)
	    return ARROWUP;
	else
	    return ARROWDOWN;
    } else
	return NONE;
}
