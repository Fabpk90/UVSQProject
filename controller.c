#include <uvsqgraphics.h>

#include "controller.h"
#include "renderer.h"
#include "playerController.h"

void
Play (const char *filename)
{
  Slider *slider = initFromFile (filename);
  ArrowType inputArrow;

  init_graphics (slider->resolution.x, slider->resolution.y);

  do
    {
      fill_screen (blanc);
      drawGame (slider);

      inputArrow = getArrow (get_arrow ());

      if (inputArrow != -1 && !slider->isMoving)
	movePlayer (slider, inputArrow);

    }
  while (get_key () != 27);	//escape
  
  free(slider->walls);
  free(slider);
}

ArrowType
getArrow (POINT arrowInput)
{
  if (arrowInput.x != 0)	//left or right
    {
      if (arrowInput.x > 0)
	return ARROWRIGHT;
      else
	return ARROWLEFT;
    }
  else if (arrowInput.y != 0)
    {
      if (arrowInput.y > 0)
	return ARROWUP;
      else
	return ARROWDOWN;
    }
  else
    return -1;
}

Slider *
initFromFile (const char *filename)
{
  FILE *level = fopen (filename, "r");
  Slider *slider = malloc (sizeof (Slider));
  uint i;
  if (level != NULL)
    {
      fscanf (level, "%d %d", &slider->resolution.x, &slider->resolution.y);
      fscanf (level, "%d %d", &slider->playerPos.x, &slider->playerPos.y);
      fscanf (level, "%d %d", &slider->goalPos.x, &slider->goalPos.y);

      fscanf (level, "%d", &slider->nbWalls);
      slider->walls = NULL;
      if (slider->nbWalls != 0)
	{
	  slider->walls = malloc (slider->nbWalls * sizeof (Wall));

	  for (i = 0; i < slider->nbWalls; i++)
	    {
	      fscanf (level, "%d %d", &slider->walls[i].position.x,
		      &slider->walls[i].position.y);
	    }
	}

      fclose (level);
      return slider;
    }
  else
    exit (-1);
}
