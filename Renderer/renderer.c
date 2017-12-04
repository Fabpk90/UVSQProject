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

		drawCircle(slider->goalPos, COLOR_GOAL, CONST_PIXELSCALE / 2);
    drawCircle(slider->player.position, COLOR_PLAYER, CONST_PIXELSCALE / 2);
}

//draws the rows and the cols of the map
//After drawing the basic grid, it call the function to draw walls
void drawMap(Slider * slider)
{
    //used do draw the line of the map
    POINT p1, p2;
    int i;

    p1.x = 0;
    p2.x = slider->resolution.x;
    //draws rows
    for (i = 0; i <= slider->resolution.y / CONST_PIXELSCALE; i++) {
	p1.y = p2.y = (i + 1) * 32;
	draw_line(p1, p2, noir);
    }
    p1.y = 0;
    p2.y = slider->resolution.y;
    //draws cols
    for (i = 0; i <= slider->resolution.x / CONST_PIXELSCALE; i++) {
	p1.x = p2.x = (i + 1) * 32;
	draw_line(p1, p2, noir);
    }
}

//draws walls according to their direction
//cycle thru the list, stops when NULL
void drawWalls(Wall * walls, uint nbWalls)
{
    POINT p1, p2;
    int i;
    COULEUR c;

    c = couleur_RGB(255, 0, 0);

    for (i = 0; i < nbWalls; i++) {
	p1.x = p2.x = walls[i].position.x * CONST_PIXELSCALE;
	p1.y = p2.y = walls[i].position.y * CONST_PIXELSCALE;

	drawWall(p1, p2, walls[i].direction);
    }
}

void drawWall(POINT p1, POINT p2, WallDirection direction)
{
	updateWallFromDirection(&p1, &p2, direction);
p1.x--;
p1.y--;
 draw_fill_rectangle(p1, p2,  COLOR_WALL);
}

void updateWallFromDirection(POINT * p1, POINT * p2,
			     WallDirection direction)
{
    switch (direction) {
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

void drawCircle(POINT position, COULEUR color, int radius)
{
	//translate the position
	position.x *= CONST_PIXELSCALE;
	position.y *= CONST_PIXELSCALE;

	//center of the case
	position.x += CONST_PIXELSCALE / 2;
	position.y += CONST_PIXELSCALE / 2;

	draw_fill_circle(position, radius, color);

}
