#include "uvsqgraphics.h"

#include "../Util/gridStruct.h"
#include "../Util/constants.h"

#include "editorController.h"
#include "controller.h"

#include "../Renderer/renderer.h"


void handleClick(Slider *slider, EditorAction action, POINT clickPosition, WallDirection wallDir);
void placeWall(POINT position, Slider *slider, WallDirection direction);
void drawMouse(POINT mousePosition, EditorAction action, WallDirection wallDir);

BOOL initSliderPartial(Slider *slider, const char *filename);

//Create the approriate file structure, then goes to the editor
//TODO: handle if the player wants to overwrite an existing level
void CreateLevel(int width, int height, const char *filename)
{
  FILE *level = fopen(filename, "w");
  Slider *slider = malloc(sizeof(Slider));
  if(level != NULL)
  {
    fprintf(level, "%d %d\n", width, height);
    fprintf(level, "0  0\n");
    fprintf(level, "0  0\n");
    fprintf(level, "0\n");

    fclose(level);

    initSliderPartial(slider, filename);

    EditLevel(slider);
  }
  else
  {
    free(slider);
    printf("Erreur pendant la création du fichier\n");
    exit(ERROR_CREATING_FILE);
  }
}

BOOL initSliderPartial(Slider *slider, const char *filename)
{
  FILE *level = fopen(filename, "r");

  if(level != NULL)
  {
    fscanf(level, "%d %d", &slider->resolution.x, &slider->resolution.y);
    slider->resolution.x *= CONST_PIXELSCALE;
    slider->resolution.y *= CONST_PIXELSCALE;

    fscanf(level, "%d %d", &slider->player.position.x, &slider->player.position.y);
    fscanf(level, "%d %d", &slider->goalPos.x, &slider->goalPos.y);

    slider->nbWalls = 0;
    slider->walls = NULL;

    return true;
  }
  return false;
}

//gets the level from the file, then edit
void EditLevel(Slider *slider)
{
  SDL_Event event;
  EditorAction action = 0;
  //action = (action + 1) % (int)PLACINGNONE;
  POINT click, mousePosition;
  BOOL isQuitting = false;
  WallDirection wallDir = 0;

  //SDL_Init(SDL_INIT_VIDEO);

  int keyboard = 0;
  init_graphics(slider->resolution.x, slider->resolution.y);
  affiche_auto_off();

//disable key repeating
SDL_EnableKeyRepeat(0, 1);
  do {
    //if the user clicks
    if(click.x != -1 && click.y != -1)
    {
      printf("yo\n");//handleClick(slider, action, click, wallDir);
    }

    fill_screen(blanc);

    while(SDL_PollEvent(&event))
    {
      switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
            printf("test\n");
          break;
          case SDL_QUIT:
            isQuitting = true;
            break;
            case SDL_KEYDOWN:
              switch( event.key.keysym.sym )
              {
                  case SDLK_ESCAPE:
                  isQuitting = true;
                  break;
                  case SDLK_r:
                  wallDir = (wallDir + 1) % 4;
                  break;
                  case SDLK_w:
                  action = PLACINGWALL;
                  break;
              }
      }
    }
    drawGame(slider);
    drawMouse(mousePosition, action, wallDir);
    affiche_all();

    keyboard = -1;

    SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
    mousePosition.y = abs(mousePosition.y - slider->resolution.y);

      if(keyboard != -1)
      {
          printf("%d\n", keyboard);
      }

  } while(!isQuitting);



  free(slider->walls);
  free(slider);

  SDL_Quit();
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
  mousePosition.x /= CONST_PIXELSCALE;
  mousePosition.y /= CONST_PIXELSCALE;

  switch(action)
  {
    case PLACINGGOAL:
    drawCircle(mousePosition, COLOR_GOAL, CONST_PIXELSCALE / 2 );
    break;

    case PLACINGPLAYER:
        drawCircle(mousePosition, COLOR_PLAYER, CONST_PIXELSCALE / 2 );
        break;

    case PLACINGWALL:
    mousePosition.x *= CONST_PIXELSCALE;
    mousePosition.y *= CONST_PIXELSCALE;
      p2Wall = mousePosition;
      drawWall(mousePosition,p2Wall, wallDir);
    break;
  }
}
