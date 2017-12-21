#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#include "uvsqgraphics.h"

#include "Util/constants.h"
#include "Util/gridStruct.h"

#include "Controller/controller.h"
#include "Controller/editorController.h"

int main(int argc, char **argv)
{
	int width = 0, height = 0;
	DIR* directory = NULL;
	struct dirent* fileInDir = NULL;
	char path[255];

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
		else if(argc == 2) //wants to play, first test if level else test if dir
		{
			if(strstr(argv[1], ".slider"))
			{
				Play(argv[1]);
			}
			else
			{
					directory = opendir(argv[1]);
					if(directory != NULL)
					{
						//circle through .slider files
						while ((fileInDir = readdir(directory)) != NULL)
						{
							if (strcmp(".", fileInDir->d_name) && strstr(fileInDir->d_name, ".slider") != NULL)
							{
								strcpy(path, argv[1]);
								strcat(path, fileInDir->d_name);
									//printf("%s\n",path);

									//TODO: add return type to Play, for errors
									Play(path);
							}
						}
						closedir(directory);
					}
					else
					{
						perror("");
					}
			}

		}
		return 0;
	}
	else
	{
		printf("Nombres d'arguments invalides");
		exit(ERROR_ARGUMENTS);
	}

	return 0;
}
