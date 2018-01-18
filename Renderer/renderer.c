#include <uvsqgraphics.h>

#include "../Util/constants.h"
#include "renderer.h"

void drawMap(Slider * slider);
void drawWalls(Wall * walls, uint nbWalls);

void updateWallFromDirection(POINT * p1, POINT * p2,
			     WallDirection direction);

void drawGame(Slider * slider)
{
    drawMap(slider);
    drawWalls(slider->walls, slider->nbWalls);

		drawCircle(slider->goalPos, COLOR_GOAL, CONST_PIXELSCALE_HALF);
    drawCircle(slider->player.position, COLOR_PLAYER, CONST_PIXELSCALE_HALF);
}

//draws the rows and the cols of the map
//After drawing the basic grid, it call the function to draw walls
void drawMap(Slider * slider)
{
    //used do draw the line of the map
    POINT p1, p2;
    int i, sliderY, sliderX;
		sliderY = slider->resolution.y >> CONST_PIXELSCALE_BITS;
		sliderX = slider->resolution.x >> CONST_PIXELSCALE_BITS;
    p1.x = 0;
    p2.x = slider->resolution.x;
    //draws rows
    for (i = 0; i <= sliderY; i++)
		{
			p1.y = p2.y = (i + 1) << CONST_PIXELSCALE_BITS;
			draw_line(p1, p2, noir);
    }
    p1.y = 0;
    p2.y = slider->resolution.y;
    //draws cols
    for (i = 0; i <= sliderX; i++)
		{
			p1.x = p2.x = (i + 1) << CONST_PIXELSCALE_BITS;
			draw_line(p1, p2, noir);
    }
}

//draws walls according to their direction
//cycle thru the list
void drawWalls(Wall * walls, uint nbWalls)
{
    POINT p1, p2;
    int i;

    for (i = 0; i < nbWalls; i++)
		{
			p1.x = p2.x = walls[i].position.x << CONST_PIXELSCALE_BITS;
			p1.y = p2.y = walls[i].position.y << CONST_PIXELSCALE_BITS;

			drawWall(p1, p2, walls[i].direction);
    }
}

//draw correctly all the walls
void drawWall(POINT p1, POINT p2, WallDirection direction)
{
	updateWallFromDirection(&p1, &p2, direction);
	//for walls' thickness
	p1.x--;
	p1.y--;
 	draw_fill_rectangle(p1, p2,  COLOR_WALL);
}

//arrange the walls accoding to their direction
void updateWallFromDirection(POINT * p1, POINT * p2,
			     WallDirection direction)
{
    switch (direction)
		{
		    case WALLDOWN:
					p2->x += CONST_PIXELSCALE;
				break;
		    case WALLLEFT:
					p2->y += CONST_PIXELSCALE;
				break;
		    case WALLRIGHT:
					p2->x += CONST_PIXELSCALE;
					p1->x = p2->x;

					p2->y += CONST_PIXELSCALE;
				break;
		    case WALLUP:
					p2->y += CONST_PIXELSCALE;
					p1->y = p2->y;

					p2->x += CONST_PIXELSCALE;
				break;
    }
}

//Draws a simple circle, used for both player and goal
void drawCircle(POINT position, COULEUR color, int radius)
{
	//translate the position
	position.x <<= CONST_PIXELSCALE_BITS;
	position.y <<= CONST_PIXELSCALE_BITS;

	//center of the case
	position.x += CONST_PIXELSCALE_HALF;
	position.y += CONST_PIXELSCALE_HALF;

	draw_fill_circle(position, radius, color);
}
