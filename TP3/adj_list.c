#include <stdlib.h>

#include "adj_list.h"

int* get_grau(int n, int m, int** aresta) {
	// veor de graus
	int* grau = malloc(n * sizeof(int));
	
	// inicializa como 0
	for (int i = 0; i < n; i++) grau[i] = 0;

	// conta os graus
	for (int i = 0; i < m; i++) {
		grau[aresta[i][0]]++;
		grau[aresta[i][1]]++;
	}

	return grau;
}

int** get_adj_list(int n, int m, int** aresta, int* grau) {
	// quantas arestas ja foram inseridas em cada vertice
	int pos[n];
	for (int i = 0; i < n; i++) pos[i] = 0;

	// lista de adjacencia
	int** adj_list = malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++)
		adj_list[i] = malloc(grau[i] * sizeof(int));

	// poe os valores na lista de adjacencia
	for (int i = 0; i < m; i++) {
		int a = aresta[i][0], b = aresta[i][1];

		adj_list[a][pos[a]++] = b;
		adj_list[b][pos[b]++] = a;
	}

	return adj_list;
}
