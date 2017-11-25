name=SantoroFabrizio
compileFlags=-c -Wall `sdl-config --cflags`

all: run

run: compile
	./Slider

compile: renderer.o controller.o playerController.o main.o 
	gcc -o Slider main.o Renderer/renderer.o Controller/controller.o Controller/playerController.o -luvsqgraphics `sdl-config --libs` -lm -lSDL_ttf
	
#ajouter les headers corrects
main.o: main.c controller.h
	gcc -o main.o $(compileFlags) main.c

renderer.o: Renderer/renderer.c Renderer/renderer.h Util/constants.h Util/gridStruct.h
	gcc -o obj/renderer.o $(compileFlags) Renderer/renderer.c
	
controller.o: Controller/controller.c Controller/controller.h Util/constants.h Util/gridStruct.h Controller/playerController.h
	gcc -o obj/controller.o -c $(compileFlags) Controller/controller.c
	
playerController.o: Controller/playerController.c Controller/playerController.h Util/constants.h Util/gridStruct.h
	gcc -o obj/playerController.o $(compileFlags) Controller/playerController.c

#NomDuFichier.o: NomDuFichier.c NomDuFichier.h
#	gcc -o NomDuFichier.o -c `sdl-config --cflags` NomDuFichier.c
# Penser à ajouter le fichier aussi au main (dépendance), si include du .h


#Penser à add un truc qui remplace "uvsqgraphics" en <> et enlever uvsqcouleur

codingTime: 
	geany main.c
	geany Controller/playerController.c Controller/playerController.h
	geany Controller/xontroller.c Controller/controller.h
	geany Controller/wallController.c Controller/wallController.h
	geany Renderer/renderer.c Renderer/renderer.h
	geany Util/*h

zipit:
	rm -rf ../$(name).zip
	mkdir ../Release
	cp -r ../UVSQProject ../Release
	cd ../Release
	ls -a
	rm -rf ../Release/.git
	indent -kr *.h
	indent -kr *.c
	zip -r $(name).zip ../Release
	rm -rf ../Release

clean:
	rm -rf *.o
	rm -rf Slider

