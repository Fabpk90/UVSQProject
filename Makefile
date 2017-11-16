all: run

run: compile
	./Slider

compile: main.o fichier.o
	gcc -o Slider main.o fichier.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf
	
#ajouter les headers corrects
main.o: main.c fichier.h
	gcc -o main.o -c `sdl-config --cflags` main.c -W -Wall

fichier.o: fichier.c fichier.h constants.h gridStruct.h
	gcc -o fichier.o -c `sdl-config --cflags` fichier.c

#NomDuFichier.o: NomDuFichier.c NomDuFichier.h
#	gcc -o NomDuFichier.o -c `sdl-config --cflags` NomDuFichier.c
# Penser à ajouter le fichier aussi au main (dépendance), si include du .h

clean:
	rm -rf *.o

mrproper: clean
	rm -rf Slider
