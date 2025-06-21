#include <stdio.h>
#include <stdbool.h>
#include "grafo.h"
#include "fila.h"

int main() {
    No* grafo[MAX] = {NULL};
    bool proibido[MAX] = {false};
    int canalAtual, canalDestino, qtdProibidos;

    entradaCanais(&canalAtual, &canalDestino, proibido, &qtdProibidos);

    printf("Canal atual: %d\n", canalAtual);
    printf("Canal destino: %d\n", canalDestino);
    printf("Canais proibidos:\n");
    for(int i = 1; i < MAX; i++) {
        if(proibido[i]) {
            printf("%d\n", i);
        }
    }

    montandoGrafo(grafo, proibido);
    printf("Grafo:\n");
    ImprimirGrafo(grafo);

    int resultado = bLargura(canalAtual, canalDestino, grafo);
    if (resultado != NAO_VISITADO) {
        printf("Menor numero de cliques: %d\n", resultado);
    } else {
        printf("Nao foi possivel alcancar o canal: %d.\n", canalDestino);
    }

    liberarGrafo(grafo);

    return 0;
}