#ifndef FILA_H
#define FILA_H

#include <stdbool.h>

#define MAX 101

typedef struct Fila {
    int itens[MAX];
    int inicio, fim;
} Fila;

void iniciarFila(Fila *f);
bool filaVazia(Fila* f);
void insereFila(Fila *f, int valor);
int removeDaFila(Fila *f);

#endif
