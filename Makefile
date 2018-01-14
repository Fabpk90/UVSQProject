name=Santoro_Fabrizio
compileFlags=-c -w -O2 `sdl-config --cflags`

#compileFlags=-c -O2 -g -Wall `sdl-config --cflags`


test: clean compile readMe runGame

readMe:
	echo | cat "readMe.txt"

runGame: compile
	./Slider level/

runEditor: compile
	./Slider -c 10 10 level1.slider

compile: renderer.o controller.o playerController.o main.o editorController.o fileManager.o
	gcc  -o Slider main.o obj/editorController.o obj/renderer.o obj/controller.o obj/playerController.o obj/fileManager.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf

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

fileManager.o: Util/fileManager.c
	gcc -o obj/fileManager.o $(compileFlags) Util/fileManager.c

#NomDuFichier.o: NomDuFichier.c NomDuFichier.h
#	gcc -o NomDuFichier.o -c `sdl-config --cflags` NomDuFichier.c
# Penser à ajouter le fichier aussi au main (dépendance), si include du .h

#Penser à add un truc qui remplace "uvsqgraphics" en <> et enlever uvsqcouleur

codingTime:
	geany uvsqgraphics.h level0.slider Makefile  main.c Controller/playerController.c Controller/playerController.h Controller/controller.c Controller/controller.h Controller/wallController.c Controller/wallController.h Renderer/renderer.c Renderer/renderer.h Util/*.h

testReplace:
	sed -i -e 's/<uvsqgraphics.h>/"uvsqgraphics.h"/g' **/*

zipit:
	rm -rf $(name).zip
	mkdir ../$(name)
	cp -r ../UVSQProject ../$(name)
	rm -rf ../$(name)/UVSQProject/.git/
	rm -rf ../$(name)/UVSQProject/.gitignore
	rm -rf ../$(name)/UVSQProject/Slider
	rm -rf ../$(name)/UVSQProject/uvsq*
	sed -i -e 's/"uvsqgraphics.h"/<uvsqgraphics.h>/g' **/*
	#indent -kr *.h
	#indent -kr *.c
	zip -r $(name).zip ../$(name)
	rm -rf ../$(name)

clean:
	rm -rf *.o
	rm -rf obj/*.o
	rm -rf Slider
