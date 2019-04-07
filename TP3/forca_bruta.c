#include <stdio.h>
#include <stdlib.h>

#include "adj_list.h"

// funcao para ler a entrada
int** le(int* n, int* m) {
	scanf("%d %d", n, m);

	// vetor de arestas
	int** aresta = malloc((*m) * sizeof(int*));
	for (int i = 0; i < *m; i++)
		aresta[i] = malloc(2 * sizeof(int));

	// le as arestas
	for (int i = 0; i < *m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		aresta[i][0] = a;
		aresta[i][1] = b;
	}

	return aresta;
}

void libera(int n, int m, int** aresta, int* grau, int** g) {
	for (int i = 0; i < m; i++)
		free(aresta[i]);
	free(aresta);

	free(grau);

	for (int i = 0; i < n; i++)
		free(g[i]);
	free(g);
}

// checa se a coloracao eh valida
int check(int n, int m, int* grau, int** g, int* cor) {
	// percorre o grafo
	for (int i = 0; i < n; i++)
		for (int j = 0; j < grau[i]; j++)
			// se dois vertices adjacentes tem
			// a mesma cor, retorna 0
			if (cor[i] == cor[g[i][j]]) return 0;

	return 1;
}

// tenta colorir o grafo utilizando k cores
int try(int p, int k, int n, int m, int* grau, int** g, int* cor) {
	// todos os vertices ja foram coloridos ->
	// checa a coloracao
	if (p == n) return check(n, m, grau, g, cor);

	// colore o vertice atual e tenta colorir os proximos
	for (int i = 0; i < k; i++) {
		cor[p] = i;
		if (try(p + 1, k, n, m, grau, g, cor)) return 1;
	}
	return 0;
}

int solve(int n, int m, int* grau, int** g, int* cor) {
	int k = 1;

	// aumenta o numero de cores ate conseguir
	while (!try(0, k, n, m, grau, g, cor)) k++;

	return k;
}

// printa a resposta
void printa(int k, int n, int* cor) {
	FILE* f1 = fopen("rodada.txt", "w");
	FILE* f2 = fopen("alocacao.txt", "w");

	// printa
	fprintf(f1, "%d\n", k);

	for (int i = 0; i < n; i++)
		fprintf(f2, "%d %d\n", i + 1, cor[i] + 1);

	fclose(f1); fclose(f2);
}

int main() {
	int n, m;
	int** aresta = le(&n, &m);

	int* grau = get_grau(n, m, aresta);
	int** g = get_adj_list(n, m, aresta, grau);

	int cor[n];
	int k = solve(n, m, grau, g, cor);

	printa(k, n, cor);

	libera(n, m, aresta, grau, g);

	return 0;
}
