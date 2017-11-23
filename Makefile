name=SantoroFabrizio
compileFlags=-c -Wall `sdl-config --cflags`

all: run

run: compile
	./Slider

compile: renderer.o controller.o  playerController.o main.o 
	gcc -o Slider main.o renderer.o controller.o playerController.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf
	
#ajouter les headers corrects
main.o: main.c controller.h
	gcc -o main.o $(compileFlags) main.c

renderer.o: renderer.c renderer.h constants.h gridStruct.h
	gcc -o renderer.o $(compileFlags) renderer.c
	
controller.o: controller.c controller.h constants.h gridStruct.h playerController.h
	gcc -o controller.o -c $(compileFlags) controller.c
	
playerController.o: playerController.c playerController.h constants.h gridStruct.h
	gcc -o playerController.o $(compileFlags) playerController.c

#NomDuFichier.o: NomDuFichier.c NomDuFichier.h
#	gcc -o NomDuFichier.o -c `sdl-config --cflags` NomDuFichier.c
# Penser à ajouter le fichier aussi au main (dépendance), si include du .h


#Penser à add un truc qui remplace "uvsqgraphics" en <> et enlever uvsqcouleur

zipit:
	rm -rf $(name).zip
	rm -rf Release
	mkdir Release
	cp *c Release
	cp *h Release
	cd Release
	indent -kr *.h
	indent -kr *.c
	cd ..
	cp Makefile Release
	zip $(name).zip Release
	rm -r Release

clean:
	rm -rf *.o
	rm -rf Slider

