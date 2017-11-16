#include <uvsqgraphics.h>

#include "fichier.h"

int main () {
    init_graphics (800,600);
	fill_screen(blanc);	
    
    drawMap(600, 800);
    
// Attente de l'appui sur la touche Echap pour terminer
    wait_escape();
    exit(0);
}
