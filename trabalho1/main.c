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
    for(int i = 1; i <= 100; i++) {
        if(proibido[i]) {
            printf("Canal %d C é proibido.\n", i);
        }
    }

    montandoGrafo(grafo, proibido);

    int resultado = bLargura(canalAtual, canalDestino, grafo, proibido);
    if (resultado != -1) {
        printf("Menor numero de cliques: %d\n", resultado);
    } else {
        printf("Nao foi possivel alcancar o canal: %d.\n", canalDestino);
    }

    liberarGrafo(grafo);

    return 0;
}