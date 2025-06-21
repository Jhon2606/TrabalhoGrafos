all: main.o fila.o grafo.o
	gcc main.o fila.o grafo.o -o main

main.o: main.c grafo.h fila.h
	gcc -c main.c

fila.o: fila.c fila.h
	gcc -c fila.c

grafo.o: grafo.c grafo.h fila.h
	gcc -c grafo.c

clean:
	rm -rf *.o main

run: main
	./main < $(ARQUIVO)