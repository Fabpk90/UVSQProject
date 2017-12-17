#include "uvsqgraphics.h"

#include "../Util/constants.h"
#include "../Util/gridStruct.h"

#include "controller.h"
#include "../Renderer/renderer.h"
#include "playerController.h"


void loadWalls(Slider *slider, FILE* level);

void Play(const char *filename)
{
    Slider *slider = initFromFile(filename);
    uint8_t playerStatus = 0;
    init_graphics(slider->resolution.x, slider->resolution.y);
    do
    {
      affiche_auto_off();
	    fill_screen(blanc);
	    drawGame(slider);
	    playerStatus = movePlayer(slider, get_arrow());

      affiche_all();
    }
    while (get_key() != KEY_EXIT && playerStatus == PLAYER_STUCK);	//escape or completed level
  free(slider->walls);
  free(slider);
}

Slider* initFromFile(const char *filename)
{
    FILE *level = fopen(filename, "r");
    Slider *slider = malloc(sizeof(Slider));
    if (level != NULL)
    {
  		slider->player.wall = NULL;
  		slider->walls = NULL;

  		fscanf(level, "%d %d", &slider->resolution.x,
  			   &slider->resolution.y);
  		slider->resolution.x *= CONST_PIXELSCALE;
  		slider->resolution.y *= CONST_PIXELSCALE;

  		fscanf(level, "%d %d", &slider->player.position.x, &slider->player.position.y);
  		fscanf(level, "%d %d", &slider->goalPos.x, &slider->goalPos.y);

      loadWalls(slider, level);

      if(getc(level) != EOF)
      {
        printf("Nombre de murs non valide\n");
        free(slider);
        exit(ERROR_CREATING_WALLS_NB);
      }
  		fclose(level);
  		return slider;
    }

  printf("Erreur de fichier! %s non valide\n", filename);
  free(slider);
	exit(-1);
}

void loadWalls(Slider *slider, FILE* level)
{
  uint i, valRead;
  fscanf(level, "%d", &slider->nbWalls);
  if (slider->nbWalls != 0)
  {
    slider->walls = malloc(slider->nbWalls * sizeof(Wall));
    for (i = 0; i < slider->nbWalls; i++)
    {
      valRead = fscanf(level, "%d %d %d\n", &slider->walls[i].position.x,&slider->walls[i].position.y,  &slider->walls[i].direction);
      if(valRead == 3)
        {
          slider->walls[i].direction /= 3;
        }
      else
      {
          free(slider);
          free(slider->walls);
          printf("Le mur n'est pas valide sur la ligne des murs num : %d \n", i+1);
          exit(ERROR_CREATING_WALLS);
      }
    }
  }
}
