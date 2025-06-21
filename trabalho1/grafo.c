#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

void entradaCanais(int* canalAtual, int* canalDestino, bool proibido[], int* qtdProibidos) {
    scanf("%d %d %d", canalAtual, canalDestino, qtdProibidos);
    for(int i = 0; i < *qtdProibidos; i++) {
        int canal;
        scanf("%d", &canal);
        if(canal < 1 || canal > 100) {
            printf("Canal invalido: %d\n", canal);
            continue;
        }
        proibido[canal] = true;
    }
}

void montandoGrafo(No* grafo[], bool proibido[]) {
    int destino;
    for(int i = 1; i < MAX; i++) {
        if(proibido[i]) continue;

        destino = (i == 100) ? 1 : i + 1;
        if(!proibido[destino]) adicionarAresta(i, destino, grafo);

        destino = (i == 1) ? 100 : i - 1;
        if(!proibido[destino]) adicionarAresta(i, destino, grafo);

        if(i < 51) {
            destino = i * 2;
            if(!proibido[destino]) adicionarAresta(i, destino, grafo);
        }

        if(i * 3 <= 100) {
            destino = i * 3;
            if(!proibido[destino]) adicionarAresta(i, destino, grafo);
        }

        if(i % 2 == 0) {
            destino = i / 2;
            if(!proibido[destino]) adicionarAresta(i, destino, grafo);
        }
    }
}

void adicionarAresta(int de, int para, No* grafo[]) {
    No* novo = malloc(sizeof(No));
    novo->canal = para;
    novo->prox = grafo[de];
    grafo[de] = novo;
}

int bLargura(int origem, int destino, No* grafo[]) {
    int distancia[MAX];
    for(int i = 0; i < MAX; i++) distancia[i] = NAO_VISITADO;
    distancia[origem] = INICIO;

    Fila f;
    iniciarFila(&f);
    insereFila(&f, origem);

    while(!filaVazia(&f)) {
        int atual = removeDaFila(&f);
        No* adj = grafo[atual];
        while(adj) {
            int vizinho = adj->canal;
            if(distancia[vizinho] == NAO_VISITADO) {
                distancia[vizinho] = distancia[atual] + 1;
                insereFila(&f, vizinho);
                if(vizinho == destino) return distancia[destino];
            }
            adj = adj->prox;
        }
    }
    return NAO_VISITADO;
}

void ImprimirGrafo(No* grafo[]) {
    for(int i = 1; i < MAX; i++) {
        printf("Canal %d:", i);
        No* atual = grafo[i];
        while (atual) {
            printf("-> %d", atual->canal);
            atual = atual->prox;
        }
        printf("\n");
    }
}

void liberarGrafo(No* grafo[]) {
    for (int i = 1; i < MAX; i++) {
        No* atual = grafo[i];
        while (atual) {
            No* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}