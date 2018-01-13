#include "uvsqgraphics.h"

#include <errno.h>

#include "../Util/gridStruct.h"
#include "../Util/constants.h"

#include "editorController.h"
#include "controller.h"

#include "../Renderer/renderer.h"


void handleClick(Slider *slider, EditorAction action, POINT clickPosition, WallDirection wallDir);
void handleKeyboard(int key, EditorAction  *action, BOOL *isQuitting, WallDirection *wallDir,
   Slider *slider, const char *filename);
void placeWall(POINT position, Slider *slider, WallDirection direction);
void drawMouse(POINT mousePosition, EditorAction action, WallDirection wallDir);

void saveLevel(Slider *slider, const char *filename);

void initSliderPartial(Slider *slider, int width, int height);

//Create the approriate file structure, then goes to the editor
//TODO: handle if the player wants to overwrite an existing level
void CreateLevel(int width, int height, const char *filename)
{
  Slider *slider = malloc(sizeof(Slider));

    initSliderPartial(slider, width, height);

    EditLevel(slider, filename);
}

void initSliderPartial(Slider *slider, int width, int height)
{
    slider->resolution.x = width >> CONST_PIXELSCALE_BITS;
    slider->resolution.y = height >> CONST_PIXELSCALE_BITS;

    slider->player.position.x = slider->player.position.y = -1;
    slider->goalPos = slider->player.position;

    slider->nbWalls = 0;
    slider->walls = NULL;
}

//gets the level from the file, then edit
void EditLevel(Slider *slider, const char *filename)
{
  EditorAction action = -1;//action = (action + 1) % (int)PLACINGNONE;
  POINT click, mousePosition;
  BOOL isQuitting = false;
  WallDirection wallDir = 0;
  char keyboard = 0;
  int arrow;
  init_graphics(slider->resolution.x, slider->resolution.y);
  affiche_auto_off();
  do {
    fill_screen(blanc);
    drawGame(slider);
    drawMouse(mousePosition, action, wallDir);
    affiche_all();
    click.x = click.y = keyboard = -1;
    wait_key_arrow_clic (&keyboard, &arrow,  &click);
    if(keyboard != -1)
      handleKeyboard(keyboard, &action, &isQuitting, &wallDir, slider, filename);
    else if(click.x != -1)
      handleClick(slider, action, click, wallDir);
  } while(!isQuitting);
  free(slider->walls);
  free(slider);
}

void handleKeyboard(int key, EditorAction  *action, BOOL *isQuitting, WallDirection *wallDir,
  Slider *slider, const char *filename)
{
  switch(key)
  {
    case KEY_EDITOR_WALL:
      *action = PLACINGWALL;
    break;
    case KEY_EDITOR_WALL_ROTATION:
      *wallDir = (*wallDir + 1) % 4;
      break;
    case KEY_EDITOR_PLAYER:
      *action = PLACINGPLAYER;
    break;
    case KEY_EDITOR_GOAL:
      *action = PLACINGGOAL;
    break;
    case KEY_EXIT:
      *isQuitting = true;
    break;
    case KEY_EDITOR_SAVE:
      saveLevel(slider, filename);
    break;
  }
}

//Execute a command according to the action type
void handleClick(Slider *slider, EditorAction action, POINT clickPosition, WallDirection wallDir)
{
  POINT p;
  p.x = clickPosition.x >> CONST_PIXELSCALE_BITS;
  p.y = clickPosition.y >> CONST_PIXELSCALE_BITS;

  switch (action) {
    case PLACINGGOAL:
      slider->goalPos = p;
      break;
      case PLACINGPLAYER:
      slider->player.position = p;
      break;
      case PLACINGWALL:
        placeWall(p, slider, wallDir);
      break;
  }
}

//TODO: check if the wall is not already placed
//add the wall to the slider struct
void placeWall(POINT position, Slider *slider, WallDirection direction)
{
  slider->walls = realloc(slider->walls, (slider->nbWalls + 1) * sizeof(Wall));

  slider->walls[slider->nbWalls].position = position;
  slider->walls[slider->nbWalls].direction = direction;

  slider->nbWalls++;
}

//draw a specific thing according to the action
//useless because of the input handling
void drawMouse(POINT mousePosition, EditorAction action, WallDirection wallDir)
{
      POINT p2Wall;
  mousePosition.x <<= CONST_PIXELSCALE_BITS;
  mousePosition.y <<= CONST_PIXELSCALE_BITS;

  switch(action)
  {
    case PLACINGGOAL:
      drawCircle(mousePosition, COLOR_GOAL, CONST_PIXELSCALE_HALF );
    break;

    case PLACINGPLAYER:
      drawCircle(mousePosition, COLOR_PLAYER, CONST_PIXELSCALE_HALF );
    break;

    case PLACINGWALL:
    mousePosition.x >>= CONST_PIXELSCALE_BITS;
    mousePosition.y >>= CONST_PIXELSCALE_BITS;
      p2Wall = mousePosition;
      drawWall(mousePosition,p2Wall, wallDir);
    break;
  }
}

void saveLevel(Slider *slider, const char *filename)
{
  FILE *level = fopen(filename, "w+");
  int i;
  if (level != NULL)
  {
    fprintf(level, "%d %d\n", slider->resolution.x << CONST_PIXELSCALE_BITS, slider->resolution.y << CONST_PIXELSCALE_BITS);
    fprintf(level, "%d %d\n", slider->player.position.x, slider->player.position.y);
    fprintf(level, "%d %d\n", slider->goalPos.x, slider->goalPos.y);
    fprintf(level, "%d\n", slider->nbWalls);
    for(i = 0; i < slider->nbWalls; i++)
    {
      fprintf(level, "%d %d %d\n", slider->walls[i].position.x, slider->walls[i].position.y,
                                    slider->walls[i].direction * 3);
    }

    printf("Niveau sauvegarde\n");

    fclose(level);
  }
  else
    printf("Erreur de fichier! %s\n", strerror(errno));
}
