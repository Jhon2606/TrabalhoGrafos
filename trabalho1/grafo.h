#ifndef GRAFO_H
#define GRAFO_H

#include <stdbool.h>

#define MAX 101
#define NAO_VISITADO -1
#define INICIO 0

typedef struct No {
    int canal;
    struct No* prox;
} No;

void adicionarAresta(int de, int para, No* grafo[]);
void montandoGrafo(No* grafo[], bool proibido[]);
void entradaCanais(int* canalAtual, int* canalDestino, bool proibido[], int* qtdProibidos);
int bLargura(int origem, int destino, No* grafo[], bool proibido[]);
void liberarGrafo(No* grafo[]);
void ImprimirGrafo(No* grafo[]);

#endif
