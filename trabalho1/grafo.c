#include <stdio.h>
#include <stdlib.h>
#include "grafo.h"
#include "fila.h"

void entradaCanais(int* canalAtual, int* canalDestino, bool proibido[], int* qtdProibidos) {
    int leitura = scanf("%d %d %d", canalAtual, canalDestino, qtdProibidos);
    if (leitura != 3) {
        fprintf(stderr, "Erro: formato inválido na primeira linha de entrada.\n");
        exit(1);
    }
    if (*canalAtual < 1 || *canalAtual > 100 || *canalDestino < 1 || *canalDestino > 100) {
        fprintf(stderr, "Erro: canais devem estar entre 1 e 100.\n");
        exit(1);
    }

    if (*qtdProibidos < 0 || *qtdProibidos > 100) {
        fprintf(stderr, "Erro: número de canais proibidos inválido.\n");
        exit(1);
    }

    for (int i = 0; i < *qtdProibidos; i++) {
        int canal;
        if (scanf("%d", &canal) != 1) {
            fprintf(stderr, "leitura incompleta ou inválida dos canais proibidos.\n");
            exit(1);
        }

        if (canal < 1 || canal > 100) {
            fprintf(stderr, "Erro: canal proibido %d está fora do intervalo permitido.\n", canal);
            exit(1);
        }

        proibido[canal] = true;
    }

    if (proibido[*canalAtual]) {
        fprintf(stderr, "Erro: canal atual (%d) não pode ser proibido.\n", *canalAtual);
        exit(1);
    }
}


int existeVizinho(No* lista, int destino) {
    while (lista != NULL) {
        if (lista->canal == destino) return 1;
        lista = lista->prox;
    }
    return 0;
}


void montandoGrafo(No* grafo[], bool proibido[]) {
    int destino;
    for(int i = 1; i < MAX; i++) {
        if(proibido[i]) continue;

        destino = (i == 100) ? 1 : i + 1;
        if(!proibido[destino] && !existeVizinho(grafo[i], destino)) adicionarAresta(i, destino, grafo);

        destino = (i == 1) ? 100 : i - 1;
        if(!proibido[destino] && !existeVizinho(grafo[i], destino)) adicionarAresta(i, destino, grafo);

        if(i < 51) {
            destino = i * 2;
            if(!proibido[destino] && !existeVizinho(grafo[i], destino)) adicionarAresta(i, destino, grafo);
        }

        if(i * 3 <= 100) {
            destino = i * 3;
            if(!proibido[destino] && !existeVizinho(grafo[i], destino)) adicionarAresta(i, destino, grafo);
        }

        if(i % 2 == 0) {
            destino = i / 2;
            if(!proibido[destino] && !existeVizinho(grafo[i], destino)) adicionarAresta(i, destino, grafo);
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
    for (int i = 1; i <= 100; i++) {
        printf("Canal %d:\n", i);
        No* aux = grafo[i];
        while (aux != NULL) {
            int destino = aux->canal;
            if (destino == ((i == 100) ? 1 : i + 1))
                printf("  -> %d (+1)\n", destino);
            else if (destino == ((i == 1) ? 100 : i - 1))
                printf("  -> %d (-1)\n", destino);
            else if (destino == i * 2)
                printf("  -> %d (*2)\n", destino);
            else if (destino == i * 3)
                printf("  -> %d (*3)\n", destino);
            else if (i % 2 == 0 && destino == i / 2)
                printf("  -> %d (/2)\n", destino);
            else
                printf("  -> %d (?)\n", destino);
            aux = aux->prox;
        }
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
        grafo[i] = NULL;
    }
}