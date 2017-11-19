#include <uvsqgraphics.h>

#include "controller.h"
#include "renderer.h"
#include "playerController.h"

void Play(const char* filename)
{
	Slider *slider = initFromFile(filename);
	ArrowType inputArrow;
	
	init_graphics(slider->resolution.x, slider->resolution.y);
	fill_screen(blanc);

	do {

		drawGame(slider);

		inputArrow = getArrow(get_arrow());

	} while (get_key() != 27);	//escape
}

ArrowType getArrow(POINT arrowInput)
{
	if (arrowInput.x != 0)	//left or right
	{
		if (arrowInput.x > 0)
			return ARROWRIGHT;
		else
			return ARROWLEFT;
	} else {
		if (arrowInput.y > 0)
			return ARROWUP;
		else
			return ARROWDOWN;
	}
}

Slider* initFromFile(const char* filename)
{
	FILE *level = fopen(filename, "r");
	Slider *slider = malloc(sizeof(Slider));
	uint nbWalls = 0, i;
	if (level != NULL) {
		fscanf(level, "%d %d", &slider->resolution.x, &slider->resolution.y);
		fscanf(level, "%d %d", &slider->playerPos.x, &slider->playerPos.y);
		fscanf(level, "%d %d", &slider->goalPos.x, &slider->goalPos.y);
		
		fscanf(level, "%d", &nbWalls);
		slider->walls = NULL;
		if(nbWalls != 0)
		{
			slider->walls = malloc(nbWalls * sizeof(Wall));
		
			for(i = 0; i <= nbWalls; i++)
			{
				fscanf(level, "%d %d", &slider->walls[i].position.x, &slider->walls[i].position.y);
			}
		}
		
		
		fclose(level);
		return slider;
	}
	else
	exit(-1);
}
