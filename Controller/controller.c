#include <uvsqgraphics.h>

#include "../Util/constants.h"
#include "../Util/gridStruct.h"
#include "../Util/fileManager.h"

#include "controller.h"
#include "../Renderer/renderer.h"
#include "playerController.h"


void freePlays(Player *player);

void getRealPosition(POINT *vec);
void drawHUD(Slider *slider);

POINT convertArrowInPoint(int arrowConst);

BOOL Play(const char *filename)
{
    Slider *slider = initFromFile(filename);
    uint8_t playerStatus = 0;
    char key = -1;
    int arrow = 0;
    POINT p;
    init_graphics(slider->resolution.x, slider->resolution.y);
    affiche_auto_off();
    do
    {
      fill_screen(blanc);
      drawGame(slider);
      drawHUD(slider);
      affiche_all();
      switch(wait_key_arrow_clic(&key, &arrow, &p))
      {
        case EST_FLECHE:
        playerStatus = movePlayer(slider, convertArrowInPoint(arrow));
        break;

        case EST_TOUCHE:
        if(key == KEY_UNDO)
          undoPlay(&slider->player);
        break;
      }
    }
    while (key != KEY_EXIT && playerStatus == PLAYER_STUCK);	//escape or completed level
  freePlays(&slider->player);
  free(slider->walls);
  free(slider);

  if(key == KEY_EXIT)
    return true;
  return false;
}

POINT convertArrowInPoint(int arrowConst)
{
  POINT p;
  switch(arrowConst)
  {
    case FLECHE_GAUCHE:
    p.x = -1;
    p.y = 0;
    break;
    case FLECHE_DROITE:
    p.x = 1;
    p.y = 0;
    break;
    case FLECHE_HAUT:
    p.x = 0;
    p.y = 1;
    break;
    case FLECHE_BAS:
    p.x = 0;
    p.y = -1;
    break;
  }
  return p;
}

void drawHUD(Slider *slider)
{
  POINT posRealPlayer, posRealGoal;

  posRealPlayer = slider->player.position;
  posRealGoal = slider->goalPos;

  getRealPosition(&posRealPlayer);
  getRealPosition(&posRealGoal);

  aff_pol_centre("P", 24, posRealPlayer, rouge);
  aff_pol_centre("G", 24, posRealGoal, rouge);
}


void getRealPosition(POINT *vec)
{
  vec->x *= CONST_PIXELSCALE;
  vec->y *= CONST_PIXELSCALE;

  vec->x += CONST_PIXELSCALE / 2;
  vec->y += CONST_PIXELSCALE / 2;
}
