#include "uvsqgraphics.h"

#include "../Util/gridStruct.h"
#include "../Util/constants.h"

#include "editorController.h"
#include "controller.h"

#include "../Renderer/renderer.h"


void handleClick(Slider *slider, EditorAction action, POINT clickPosition, WallDirection wallDir);
void placeWall(POINT position, Slider *slider, WallDirection direction);
void drawMouse(POINT mousePosition, EditorAction action, WallDirection wallDir);

//Create the approriate file structure, then goes to the editor
//TODO: handle if the player wants to overwrite an existing level
void CreateLevel(int width, int height, const char *filename)
{
  FILE *level = fopen(filename, "w");
  if(level != NULL)
  {
    fprintf(level, "%d %d\n", width, height);
    fprintf(level, "0  0\n");
    fprintf(level, "0  0\n");
    fprintf(level, "0\n");

    fclose(level);

    EditLevel(initFromFile(filename));
  }
  else
  {
    printf("Erreur pendant la création du fichier\n");
    exit(ERROR_CREATING_FILE);
  }
}

//gets the level from the file, then edit
void EditLevel(Slider *slider)
{
  EditorAction action = 0;
  //action = (action + 1) % (int)PLACINGNONE;
  POINT click, mousePosition;
  BOOL isQuitting = false;
  WallDirection wallDir = 0;

  int keyboard = get_key();

  init_graphics(slider->resolution.x, slider->resolution.y);
  affiche_auto_off();
  do {
    fill_screen(blanc);
    drawGame(slider);


      switch(keyboard)
      {
        //ESC
        case 27:
          isQuitting = true;
          break;

          //r
          case 114:
          wallDir = (wallDir + 1) % 4;
          break;

          //w
          case 119:
          action = PLACINGWALL;
          break;
      }
    drawMouse(mousePosition, action, wallDir);
    affiche_all();

    keyboard = get_key();

    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    mousePosition.y = abs(mousePosition.y - slider->resolution.y);

    click = get_clic();

    printf("click: %d %d", click.x, click.y);

    //if the user clicks
    if(click.x != -1 && click.y != -1)
    {
      handleClick(slider, action, click, wallDir);
    }

      if(keyboard != -1)
      {
          printf("%d\n", keyboard);
      }

  } while(!isQuitting);
}

//Execute a command according to the action type
void handleClick(Slider *slider, EditorAction action, POINT clickPosition, WallDirection wallDir)
{
  POINT p;
  p.x = clickPosition.x / CONST_PIXELSCALE;
  p.y = clickPosition.y / CONST_PIXELSCALE;

  switch (action) {
    case PLACINGGOAL:
      slider->goalPos = p;
      break;
      case PLACINGPLAYER:
      slider->player.position = p;
      break;
      case PLACINGWALL:
      printf("wall\n");
        placeWall(clickPosition, slider, wallDir);
      break;
  }
}

//TODO: check if the wall is not altready placed
//add the wall to the slider struct
void placeWall(POINT position, Slider *slider, WallDirection direction)
{

  printf("placing wall\n");
  slider->walls = realloc(slider->walls, (slider->nbWalls + 1) * sizeof(Wall));
  slider->nbWalls++;

  slider->walls[slider->nbWalls].position = position;
  slider->walls[slider->nbWalls].direction = direction;
}

//draw a specific thing according to the action
void drawMouse(POINT mousePosition, EditorAction action, WallDirection wallDir)
{
      POINT p2Wall;
  POINT normPos = mousePosition;
  normPos.x /= CONST_PIXELSCALE;
  normPos.y /= CONST_PIXELSCALE;

  switch(action)
  {
    case PLACINGGOAL:
    drawCircle(normPos, COLOR_GOAL, CONST_PIXELSCALE / 2 );
    break;

    case PLACINGPLAYER:
        drawCircle(normPos, COLOR_PLAYER, CONST_PIXELSCALE / 2 );
        break;

    case PLACINGWALL:
    normPos.x *= CONST_PIXELSCALE;
    normPos.y *= CONST_PIXELSCALE;
      p2Wall = normPos;
      drawWall(normPos,p2Wall, wallDir);
    break;
  }
}
