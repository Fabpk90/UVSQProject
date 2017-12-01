#include <uvsqgraphics.h>

#include "Controller/controller.h"

int main(int argc, char **argv)
{

	if(argc  >  1)
	{
			if(argc == 2)
		    Play(argv[1]);
	}
	else
	{
		printf("Nombres d'arguments invalide");
		exit(ERROR_ARGUMENTS);
	}
}
