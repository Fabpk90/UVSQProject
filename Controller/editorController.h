#ifndef EDITOR
#define EDITOR

typedef enum EditorAction
{
  PLACINGPLAYER = 0,
  PLACINGGOAL,
  PLACINGWALL,
  PLACINGNONE
}EditorAction;

void CreateLevel(int width, int height, const char *filename);
void EditLevel(Slider *slider, const char *filename);

#endif
