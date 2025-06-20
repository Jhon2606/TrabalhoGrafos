#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 101
#define NAO_VISITADO -1
#define INICIO 0

typedef struct No {
	int canal;
	struct No* prox;
} No;

typedef struct Fila {
	int itens[MAX];
	int inicio, fim;
} Fila;

void adicionarAresta(int de, int para, No* grafo[]);
void montandoGrafo(No* grafo[], bool proibido[]);
void entradaCanais(int* canalAtual, int* canalDestino, bool proibido[], int* qtdProibidos);
int bLargura(int origem, int destino, No* grafo[], bool proibido[]);
void iniciarFila(Fila *f);
bool filaVazia(Fila* f);
void insereFila(Fila *f, int valor);
int removeDaFila(Fila *f);
void liberarGrafo(No* grafo[]);
void ImprimirGrafo(No* grafo[]);

int main() {
	No* grafo[MAX] = {NULL};
	bool proibido[MAX] = {false};
	int canalAtual, canalDestino, qtdProibidos;


	entradaCanais(&canalAtual, &canalDestino, proibido, &qtdProibidos);
	printf("Canal atual: %d\n", canalAtual);
	printf("Canal destino: %d\n", canalDestino);
	printf("Canais proibidos:\n");

	for(int i = 1; i <=100; i++) {
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

void adicionarAresta(int de, int para, No* grafo[]) {
	No* novo = malloc(sizeof(No));
	novo->canal = para;
	novo->prox = grafo[de];
	grafo[de] = novo;
}

void montandoGrafo(No* grafo[], bool proibido[]) {
	int destino;
	for(int i = 1; i <=100; i++) {
		if(proibido[i]) continue;

		destino = (i == 100)? 1 : i + 1;
		if(!proibido[destino]) adicionarAresta(i, destino, grafo);

		destino = (i == 1)? 100 : i - 1;
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

void entradaCanais(int* canalAtual, int* canalDestino, bool proibido[], int* qtdProibidos) {

	scanf("%d %d %d", canalAtual, canalDestino, qtdProibidos);

	for(int i = 1; i <= 100; i++) {
		proibido[i] = false;
	}
	for(int i = 0; i < *qtdProibidos; i++) {
		int canal;
		scanf("%d", &canal);
		if (canal < 1 || canal > 100) {
			printf("Canal invalido: %d\n", canal);
			continue;
		}
		proibido[canal] = true;
	}
}

int bLargura(int origem, int destino, No* grafo[], bool proibido[]) {
	int distancia[MAX];
	for(int i = 0; i < MAX; i++) {
		distancia[i] = NAO_VISITADO;
	}

	distancia[origem] = INICIO;

	Fila f;
	iniciarFila(&f);
	insereFila(&f, origem);

	while(!filaVazia(&f)) {
		int atual = removeDaFila(&f);
		No* adjacente = grafo[atual];
		while (adjacente!=NULL) {
			int vizinho = adjacente->canal;
			if(distancia[vizinho] == NAO_VISITADO && !proibido[vizinho]) {
				distancia[vizinho] = distancia[atual] + 1;
				insereFila(&f, vizinho);
				if(destino == vizinho) {
					return distancia[destino];
				}
			}
			adjacente = adjacente->prox;
		}

	}
	return -1;
}

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
void ImprimirGrafo(No* grafo[]) {
	for(int i = 1; i <=100; i++) {
		printf("Canal %d:", i);
		No* atual = grafo[i];
		while (atual != NULL) {
			printf("-> %d", atual->canal);
			atual = atual->prox;
		}
		printf("\n");
	}
}