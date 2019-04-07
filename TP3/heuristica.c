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

int heur(int n, int* grau, int** g, int* cor, int* ordem) {
	for (int i = 0; i < n; i++) cor[i] = -1;

	int k = 0;

	for (int i = 0; i < n; i++) {
		int u = ordem[i];
		// quais cores estao nos vizinhos de i
		int tem[n];
		for (int j = 0; j < n; j++) tem[j] = 0;

		for (int j = 0; j < grau[u]; j++) {
			int v = g[u][j];
			if (cor[v] != -1) tem[cor[v]] = 1;
		}

		// ve a menor cor que nao tem nos vizinhos
		for (int j = 0; j < n; j++) if (!tem[j]) {
			cor[u] = j;
			if (j + 1 > k) k = j + 1;
			break;
		}
	}

	return k;
}

void shuffle(int n, int * v) {
	for (int i = 0; i < n; i++) {
		int j = rand() % n;

		// troca um par aleatorio
		int tmp = v[i];
		v[i] = v[j];
		v[j] = tmp;
	}
}

int solve(int n, int* grau, int** g, int* cor) {
	// ordem de avaliacao dos vertices
	int ordem[n], ordem_best[n];
	for (int i = 0; i < n; i++) ordem[i] = i;
	for (int i = 0; i < n; i++) ordem_best[i] = i;

	int k_best = 1 << 30;

	for (int i = 0; i < 100; i++) {
		shuffle(n, ordem);
		int k = heur(n, grau, g, cor, ordem);

		if (k < k_best) {
			k_best = k;
			for (int j = 0; j < n; j++)
				ordem_best[j] = ordem[j];
		}
	}

	return heur(n, grau, g, cor, ordem_best);
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
	int k = solve(n, grau, g, cor);

	printa(k, n, cor);

	libera(n, m, aresta, grau, g);

	return 0;
}
