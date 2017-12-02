#include <uvsqgraphics.h>

#include "controller.h"
#include "../Renderer/renderer.h"
#include "../Controller/playerController.h"

void Play(const char *filename)
{
    Slider *slider = initFromFile(filename);
    uint8_t playerStatus = 0;

    init_graphics(slider->resolution.x, slider->resolution.y);

    do {
	fill_screen(blanc);
	drawGame(slider);

	if (!slider->isMoving)
	    playerStatus = movePlayer(slider, get_arrow());
    }
    while (get_key() != 27 && playerStatus == 0);	//escape

  free(slider->walls);
  free(slider);
}

//Create the approriate file structure, then goes to the editor
//TODO: handle if the player wants to overwrite an existing level
void CreateLevel(int width, int height, const char *filename)
{
  FILE *level = fopen(filename, "w");
  if(level != NULL)
  {
    fclose(level);
  }
  else
  {
    printf("Erreur pendant la création du fichier\n");
    exit(ERROR_CREATING_FILE);
  }
}

Slider* initFromFile(const char *filename)
{
    FILE *level = fopen(filename, "r");
    Slider *slider = malloc(sizeof(Slider));
    uint i;
    if (level != NULL)
    {
		slider->isMoving = 0;
		slider->player.wall = NULL;
		slider->walls = NULL;

		fscanf(level, "%d %d", &slider->resolution.x,
			   &slider->resolution.y);
		slider->resolution.x *= CONST_PIXELSCALE;
		slider->resolution.y *= CONST_PIXELSCALE;

		fscanf(level, "%d %d", &slider->player.position.x, &slider->player.position.y);
		fscanf(level, "%d %d", &slider->goalPos.x, &slider->goalPos.y);

		fscanf(level, "%d", &slider->nbWalls);
		if (slider->nbWalls != 0) {
			slider->walls = malloc(slider->nbWalls * sizeof(Wall));

			for (i = 0; i < slider->nbWalls; i++) {
			fscanf(level, "%d %d %d", &slider->walls[i].position.x,
				   &slider->walls[i].position.y,  &slider->walls[i].direction);

          slider->walls[i].direction /= 3;
			}
		}

		fclose(level);
		return slider;
    }

  printf("Erreur de fichier! %s non valide\n", filename);
  free(slider);
	exit(-1);
}
