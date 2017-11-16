#include <uvsqgraphics.h>

#include "constants.h"

#include "fichier.h"

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
	
	Wall walls[1];
	
	walls[0].position.x = 3;
	walls[0].position.y = 3;
	
	walls[0].direction = 3;
	
	drawWalls(walls, 1);
	affiche_all();
	affiche_auto_on();
}

void drawWalls(Wall *walls, int size)
{
	POINT p1, p2;
	int i;
	COULEUR c;
	
	c = couleur_RGB(255, 0, 0);
	
	for(i = 0; i <= size; i++)
	{
		p1 = p2 = walls[i].position;
		
		switch(walls[i].direction)
		{
			case DOWN:
				
			break;
			
			case LEFT:
			
			break;
			
			case RIGHT:
			
			break;
			
			case UP:
			
			break;
		}
		
		draw_line(p1, p2, c);
	}
	
}
