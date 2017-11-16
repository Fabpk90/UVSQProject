#include <uvsqgraphics.h>

#include "constants.h"

#include "renderer.h"

//draws the rows and the cols of the map
//After drawing the basic grid, it call the function to draw walls
void drawMap(int height, int width)
{
	//used do draw the line of the map
	POINT p1,p2;
	int i;
	COULEUR c;
	c = couleur_RGB(0, 0, 0);
	affiche_auto_off();	
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
	affiche_all();
	affiche_auto_on();
	
	free(wall);
}

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
