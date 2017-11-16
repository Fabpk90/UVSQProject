all: start

start: plam.o plim.o ploum.o
	gcc -o testMake plam.o plim.o ploum.o
	
plam.o: plam.c
	gcc -o plam.o -c plam.c -W -Wall
	
plim.o: plim.c
	gcc -o plim.o -c plim.c -W -Wall
	
ploum.o: ploum.c
	gcc -o ploum.o -c ploum.c -W -Wall
