#include <uvsqgraphics.h>

#include "controller.h"
#include "renderer.h"
#include "playerController.h"

void Play(const char *filename)
{
    Slider *slider = initFromFile(filename);

    init_graphics(slider->resolution.x, slider->resolution.y);

    do {
	fill_screen(blanc);
	drawGame(slider);

	if (!slider->isMoving)
	    movePlayer(slider, get_arrow());

    }
    while (get_key() != 27);	//escape
}

Slider *initFromFile(const char *filename)
{
    FILE *level = fopen(filename, "r");
    Slider *slider = malloc(sizeof(Slider));
    uint i;
    if (level != NULL) 
    {
		fscanf(level, "%d %d", &slider->resolution.x,
			   &slider->resolution.y);
		fscanf(level, "%d %d", &slider->player.position.x, &slider->player.position.y);
		fscanf(level, "%d %d", &slider->goalPos.x, &slider->goalPos.y);

		fscanf(level, "%d", &slider->nbWalls);
		slider->walls = NULL;
		if (slider->nbWalls != 0) {
			slider->walls = malloc(slider->nbWalls * sizeof(Wall));

			for (i = 0; i < slider->nbWalls; i++) {
			fscanf(level, "%d %d", &slider->walls[i].position.x,
				   &slider->walls[i].position.y);
			}
		}

		fclose(level);
		return slider;
    } 
    else
	exit(-1);
}
