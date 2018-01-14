#include <stdlib.h>
#include <uvsqgraphics.h>

#include "../Util/gridStruct.h"
#include "../Util/constants.h"
#include "playerController.h"
#include "../Util/vectorUtil.h"

ArrowType getArrow(POINT arrowInput);
Wall* searchForObstacle(Slider *slider, POINT direction);
void move(Slider * slider, POINT position);

POINT getCorrectPosition(Wall *wall, POINT direction);
POINT getCornerScreen(POINT direction, Slider *slider);

// pas de récursif ici, la mémoire serait gachée
// iteratif, moche, mais niveau mémoire c'est mieux

uint8_t movePlayer(Slider * slider, POINT direction)
{
	Wall *wall = NULL;

	POINT cornerPos;
	cornerPos.x = cornerPos.y = 1;

	if(direction.x != 0 || direction.y != 0)
	{
		//normalisation
		//direction.x /= (direction.x == 0 ? 1 : abs(direction.x));
		//direction.y /= (direction.y == 0 ? 1 : abs(direction.y));

		//if no destination and the player is trying to move
		//we need to search for an obstacle
		wall = searchForObstacle(slider, direction);

		if(wall != NULL)
		{
			cornerPos = getCorrectPosition(wall, direction);
		}
		else
		{
			//if there is no wall, the player need to go to a corner of the screen
			cornerPos = getCornerScreen(direction, slider);
			addVec(cornerPos, slider->player.position);
		}

		move(slider, cornerPos);
		affiche_all();

		if(cmpVec(slider->player.position,slider->goalPos))
			return PLAYER_VICTORY;
	}

		return PLAYER_STUCK;
}

//returns a Vec2 of the cornerPos according to the direction
POINT getCornerScreen(POINT direction, Slider *slider)
{
	POINT p;

p.x = p.y = 0;

	if(direction.x < 0) // left
	{
		p.x = -slider->player.position.x * CONST_PIXELSCALE;
		p.y = 0;
	}
	else if (direction.x > 0)
	{
		p.x = ( (slider->resolution.x -1) - slider->player.position.x * CONST_PIXELSCALE);
		p.y = 0;
	}
	else if(direction.y < 0) // down
	{
		p.x = 0;
		p.y = -slider->player.position.y * CONST_PIXELSCALE;
	}
	else if(direction.y > 0)
	{
		//printf("haut\n");
		p.x = 0;
		p.y = ((slider->resolution.y - 1) - slider->player.position.y * CONST_PIXELSCALE);
	}
	p.x /= CONST_PIXELSCALE;
	p.y /= CONST_PIXELSCALE;
	return p;
}

//returns the correct position of the player colliding on a wall
//needed for the ambigous placements, 0 1 9, 1 1 3, which seems the same but aren't
POINT getCorrectPosition(Wall *wall, POINT direction)
{
	POINT position;
	position = wall->position;

	//the direction is on the opposite direction so-> it need to go at the n-1 position
	if( ((wall->direction + 2) % 4) == getArrow(direction) )
	{
		direction.x = -direction.x;
		direction.y = -direction.y;
		addVec(position, direction);
	}
	return position;
}

//check wether the block ahead is blocking the path
//according to the direction
BOOL isWallOnPath(POINT playerPos, Wall *wall, POINT direction)
{

//the block is on the same position
//we check wether the player is blocked
	if(cmpVec(playerPos, wall->position))
	{
		if((int) getArrow(direction) == wall->direction)
			return true;
		else
			return false;
	}

	if(direction.x > 0)//right
	{
		if(wall->position.y == playerPos.y
		&& wall->position.x >= playerPos.x
		&& (wall->direction ==  WALLRIGHT || wall->direction == WALLLEFT) )
			return true;
	}
	else if (direction.x < 0) //left
	{
		if(wall->position.y == playerPos.y
		&& wall->position.x <= playerPos.x
		&& (wall->direction == WALLRIGHT || wall->direction == WALLLEFT) )
			return true;
	}
	else if(direction.y > 0)//up
	{
		if(wall->position.x == playerPos.x
		&& wall->position.y >= playerPos.y
		&& (wall->direction == WALLUP || wall->direction == WALLDOWN) )
			return true;
	}
	else if (direction.y < 0)//down
	{
		if(wall->position.x == playerPos.x
		&& wall->position.y <= playerPos.y
		&& (wall->direction == WALLUP || wall->direction == WALLDOWN) )
		{
			return true;
		}
	}
	return false;
}

//Returns a pointer to the nearest Obstacle, null if none
Wall* searchForObstacle(Slider *slider, POINT direction)
{
	uint i;
	float distMin = slider->resolution.y, dist = -1;
	Wall *wall = NULL;

	for(i = 0; i < slider->nbWalls; i++)
	{
		//check if the wall is on the way
		if(isWallOnPath(slider->player.position, &slider->walls[i], direction) == true)
		{
			dist = distance(slider->player.position, slider->walls[i].position);

			if(dist < distMin)
			{
				distMin = dist;
				wall = &slider->walls[i];
			}
		}
	}
	return wall;
}

// TODO: animation
// move step by step and stops when cannot move
void move(Slider * slider, POINT position)
{
		//test if the animation doesn't exceeds the screen
		if(position.x >= 0 && position.x <= (slider->resolution.x << CONST_PIXELSCALE_BITS)
		&& position.y >= 0 && position.y <= (slider->resolution.y << CONST_PIXELSCALE_BITS) )
		{
			addPlay(&slider->player);
			slider->player.position = position;
		}
}

void addPlay(Player *player) //push
{
	pilePlays *play = malloc(sizeof(pilePlays));
	if(play != NULL)
	{

		if(player->plays == NULL
			|| !cmpVec(player->position, player->plays->playPosition))
			{
				play->next = player->plays;
				play->playPosition = player->position;
				player->plays = play;
			}
			else
			{
				free(play);
			}

	}
}

BOOL undoPlay(Player *player) //pop
{
	pilePlays *play= NULL;
	if(player->plays != NULL)
	{
		player->position = player->plays->playPosition;
		play = player->plays;
		player->plays = player->plays->next;
		free(play);
		return true;
	}
	else
		return false;
}

//Returns an arrowType according to the input
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
// deallocate the pile of plays
void freePlays(Player *player)
{
  pilePlays *play = NULL;
  while(player->plays != NULL)
  {
     play = player->plays->next;
     free(player->plays);
     player->plays = play;
  }
}
