all: COMPILAR
	./trab4 bb 3 < entrada.txt

COMPILAR:
	gcc -c bb.c
	gcc -c permutas.c
	gcc -c main.c
	gcc bb.o permutas.o main.o -o trab4