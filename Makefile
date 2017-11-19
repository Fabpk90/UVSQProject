all: run

run: compile
	./Slider

compile: renderer.o controller.o  playerController.o main.o 
	gcc -o Slider main.o renderer.o controller.o playerController.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf
	
#ajouter les headers corrects
main.o: main.c controller.h
	gcc -o main.o -c `sdl-config --cflags` main.c -W -Wall

renderer.o: renderer.c renderer.h constants.h gridStruct.h
	gcc -o renderer.o -c `sdl-config --cflags` renderer.c
	
controller.o: controller.c controller.h constants.h gridStruct.h playerController.h
	gcc -o controller.o -c `sdl-config --cflags` controller.c
	
playerController.o: playerController.c playerController.h constants.h gridStruct.h
	gcc -o playerController.o -c `sdl-config --cflags` playerController.c

#NomDuFichier.o: NomDuFichier.c NomDuFichier.h
#	gcc -o NomDuFichier.o -c `sdl-config --cflags` NomDuFichier.c
# Penser à ajouter le fichier aussi au main (dépendance), si include du .h

clean:
	rm -rf *.o

mrproper: clean
	rm -rf Slider
