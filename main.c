#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "uvsqgraphics.h"

#include "Util/constants.h"
#include "Util/gridStruct.h"

#include "Controller/controller.h"
#include "Controller/editorController.h"

int main(int argc, char **argv)
{
	int width = 0, height = 0;

	if(argc  >  1)
	{
		//test if hte player wants to create a level
		if(strcmp(argv[1], "-c") == 0)
		{
				width = atoi(argv[2]);
				height = atoi(argv[3]);

				if(width > 0 && height > 0)
				{
					CreateLevel(width, height, argv[4]);
				}
				else
				{
					printf("Valeurs de la grille non valides !");
					exit(ERROR_ARGUMENTS);
				}
		}
			if(argc == 2)
		    Play(argv[1]);
		return 0;
	}
	else
	{
		printf("Nombres d'arguments invalide");
		exit(ERROR_ARGUMENTS);
	}
}
