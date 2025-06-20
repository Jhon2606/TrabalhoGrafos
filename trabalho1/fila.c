#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

void iniciarFila(Fila *f) {
    f->inicio = 0;
    f->fim = 0;
}

bool filaVazia(Fila* f) {
    return f->inicio == f->fim;
}

void insereFila(Fila *f, int valor) {
    if(f->fim < MAX) {
        f->itens[f->fim++] = valor;
    } else {
        printf("Erro: fila cheia.\n");
        exit(1);
    }
}

int removeDaFila(Fila *f) {
    return f->itens[f->inicio++];
}
