#include <uvsqgraphics.h>

#include "constants.h"

#include "renderer.h"


void drawGame(int height, int width)
{
	affiche_auto_off();	
	
	drawMap(height, width);
	
	POINT p1, p2;
	
	p1.x = p1.y = 3;
	p2.x = p2.y = 5;
	
	drawPlayernGoal(p1,p2);
	
	affiche_all();
	affiche_auto_on();
}

//draws the rows and the cols of the map
//After drawing the basic grid, it call the function to draw walls
void drawMap(int height, int width)
{
	//used do draw the line of the map
	POINT p1,p2;
	int i;
	COULEUR c;
	c = couleur_RGB(0, 0, 0);

	p1.x = 0;
	p2.x = width;
	//draws rows
	for(i = 0; i <= height / CONST_PIXELSCALE; i++)
	{	
		p1.y =p2.y = (i +1) * 32;
		draw_line(p1, p2, c);
	}
	p1.y = 0;
	p2.y = height;
	//draws cols
	for(i = 0; i <= width / CONST_PIXELSCALE; i++)
	{	
		p1.x = p2.x = (i +1) * 32;
		draw_line(p1, p2, c);
	}
	
	WallList *wall = malloc(sizeof(WallList));
	
	wall->wall.position.x = 3;
	wall->wall.position.y = 3;
	
	wall->wall.direction = UP;
	wall->next = NULL;
	
	drawWalls(wall);

	
	free(wall);
}

//draws walls according to their direction
//cycle thru the list, stops when NULL
void drawWalls(WallList *walls)
{
	POINT p1, p2;
	int i;
	COULEUR c;
	
	WallList *wallIterator = walls;
	
	c = couleur_RGB(255, 0, 0);
	
	while(wallIterator != NULL)
	{
		p1.x = p2.x = walls->wall.position.x * CONST_PIXELSCALE;
		p1.y = p2.y = walls->wall.position.y * CONST_PIXELSCALE;
		
		switch(walls->wall.direction)
		{
			case DOWN:
				p1.x -= CONST_PIXELSCALE;
			break;
			
			case LEFT:	
				p2.y += CONST_PIXELSCALE;
			break;
			
			case RIGHT:
				p2.x += CONST_PIXELSCALE;
				p1.x = p2.x;
				
				p2.y += CONST_PIXELSCALE;
			break;
			
			case UP:
				p2.y += CONST_PIXELSCALE;
				p1.y = p2.y;
				
				p2.x += CONST_PIXELSCALE;
			break;
		}
		draw_line(p1, p2, c);
		wallIterator = wallIterator->next;
	}
}

void drawPlayernGoal(POINT player, POINT goal)
{
	COULEUR cPlayer, cGoal;
	
	cPlayer = couleur_RGB(0, 0, 255);
	cGoal = couleur_RGB(0, 255, 0);
	
	player.x *= CONST_PIXELSCALE;
	player.y *= CONST_PIXELSCALE;
	
	goal.x *= CONST_PIXELSCALE;
	goal.y *= CONST_PIXELSCALE;
	
	player.x += CONST_PIXELSCALE / 2;
	player.y += CONST_PIXELSCALE / 2;
	
	goal.x += CONST_PIXELSCALE / 2;
	goal.y += CONST_PIXELSCALE / 2;
	
	draw_fill_circle(player, CONST_PIXELSCALE / 2, cPlayer);
	draw_fill_circle(goal, CONST_PIXELSCALE / 2, cGoal);
	
}
