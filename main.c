#include <uvsqgraphics.h>

#include "renderer.h"

int main () {
    init_graphics (800,600);
	fill_screen(blanc);	
    
    drawGame(600, 800);
    
// Attente de l'appui sur la touche Echap pour terminer
    wait_escape();
    exit(0);
}
