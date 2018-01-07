name=Santoro_Fabrizio
compileFlags=-c -g -Wall `sdl-config --cflags`

test: readMe clean releaseMode compile runGame

releaseMode:
	compileFlags=-c -g `sdl-config --cflags`

all: readMe runGame

readMe:
	echo | cat "readMe.txt"

runGame: compile
	./Slider level/

runEditor: compile
	./Slider -c 10 10 level1.slider

compile: renderer.o controller.o playerController.o main.o editorController.o
	gcc  -o Slider main.o obj/editorController.o obj/renderer.o obj/controller.o obj/playerController.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

#ajouter les headers corrects
main.o: main.c controller.o
	gcc -o main.o $(compileFlags) main.c

renderer.o: Renderer/renderer.c
	gcc -o obj/renderer.o $(compileFlags) Renderer/renderer.c

controller.o: Controller/controller.c
	gcc -o obj/controller.o -c $(compileFlags) Controller/controller.c

playerController.o: Controller/playerController.c
	gcc -o obj/playerController.o $(compileFlags) Controller/playerController.c

editorController.o: Controller/editorController.c
		gcc -o obj/editorController.o $(compileFlags) Controller/editorController.c

#NomDuFichier.o: NomDuFichier.c NomDuFichier.h
#	gcc -o NomDuFichier.o -c `sdl-config --cflags` NomDuFichier.c
# Penser à ajouter le fichier aussi au main (dépendance), si include du .h

#Penser à add un truc qui remplace "uvsqgraphics" en <> et enlever uvsqcouleur

codingTime:
	geany uvsqgraphics.h level0.slider Makefile  main.c Controller/playerController.c Controller/playerController.h Controller/controller.c Controller/controller.h Controller/wallController.c Controller/wallController.h Renderer/renderer.c Renderer/renderer.h Util/*.h

openSdl:
	atom `sdl-config --cflags`

zipit:
	rm -rf $(name).zip
	mkdir Release
	cp -r ../UVSQProject Release
	cd Release
	ls -a
	rm -rf /Release/.git
	indent -kr *.h
	indent -kr *.c
	sed -i 's/"uvsqgraphics.h"/<uvsqgraphics.h>/g' main.c
	zip -r $(name).zip ../Release
	rm -rf ../Release

clean:
	rm -rf *.o
	rm -rf obj/*.o
	rm -rf Slider
