#include "uvsqgraphics.h"

#include "gridStruct.h"
#include "constants.h"
#include "playerController.h"
#include "vectorUtil.h"

// mouvement, checker les murs dans la même direction
// checker le plus proche et compter les pas
// animation des pas

ArrowType getArrow(POINT arrowInput);
Wall* searchForObstacle(Slider *slider, POINT direction);
void move(Slider * slider, POINT direction);

// pas de récursif ici, la mémoire serait gachée
// iteratif, moche, mais niveau mémoire c'est mieux

int8_t movePlayer(Slider * slider, POINT direction)
{
	int8_t result = -1;
	
	//printf("direction: %d %d\n", direction.x, direction.y);
	
	if(direction.x != 0 || direction.y != 0)
	{
		//if no destination and the player is trying to move
		//we need to search for an obstacle
		if(slider->player.wall == NULL)
			slider->player.wall = searchForObstacle(slider, direction);

		move(slider, slider->player.wall, direction);
		//wall = getBlockingBlock(slider, arrowDirection);
		

		affiche_all();
	}
	
	return result;
}

BOOL isWallOnPath(POINT playerPos, Wall *wall, POINT direction)
{
	if(direction.x > 0)//right
	{
		if(wall->position.y == playerPos.y 
		&& wall->position.x > playerPos.x
		&& (wall->direction ==  WALLRIGHT || wall->direction == WALLLEFT) )
			return true;
	}
	else if (direction.x < 0) //left
	{
		if(wall->position.y == playerPos.y 
		&& wall->position.x < playerPos.x
		&& (wall->direction == WALLRIGHT || wall->direction == WALLLEFT) )
			return true;
	}
	else if(direction.y > 0)//up
	{
		if(wall->position.x == playerPos.x 
		&& wall->position.y > playerPos.y
		&& (wall->direction == WALLUP || wall->direction == WALLDOWN) )
			return true;
	}
	else if (direction.y < 0)//down
	{
		if(wall->position.x == playerPos.x 
		&& wall->position.y < playerPos.y
		&& (wall->direction == WALLUP || wall->direction == WALLDOWN) )
			return true;
	}
	
	return false;
}

Wall* searchForObstacle(Slider *slider, POINT direction)
{
	uint i;
	float distMin = -1, dist = -2;
	Wall *wall = NULL;
	
	for(i = 0; i < slider->nbWalls; i++)
	{
		//check if the wall is in the way
		if(isWallOnPath(slider->player.position, slider->walls[i], direction) == true)
			dist = distance(slider->player.position, slider->walls[i].position);
		
		if(dist < distMin || distMin == -1)
		{
			distMin = dist;
			wall = &slider->walls[i];
		}
			
	}
	
	return wall;
}

// TODO: animation
// move step by step and stops when cannot move
void move(Slider * slider, POINT direction)
{
	POINT p;
	if (slider->player.wall != NULL) 
	{

	} 
	else			// go to the end of the screen
	{
		p=slider->player.position;
		addVec(p, direction);
		
		//test if the animation doesn't exceeds the screen
		if(p.x >= 0 && p.x < (slider->resolution.x / CONST_PIXELSCALE) 
		&& p.y >= 0 && p.y <= (slider->resolution.y / CONST_PIXELSCALE) )
		{
			slider->player.position = p;
		}
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
