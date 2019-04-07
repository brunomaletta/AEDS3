#include <stdio.h>

#include "list.h"

void dfs(List* arestas, char* vis, int k) {
	vis[k] = 1;
	Node N = first(arestas[k]);
	for (int i = 0; i < size(arestas[k]); i++, N = next(N)) {
		// para cada aresta, se o vertice nao foi
		// visitado, chama dfs nele
		if (!vis[val(N)]) dfs(arestas, vis, val(N));
	}
}

int main() {
	int n, m; scanf("%d %d", &n, &m);

	// corner case: grafo vazio
	if (!n) {
		printf("0\n");
		return 0;
	}
	
	// le idades
	int idade[n];
	for (int i = 0; i < n; i++) {
		int id, x; scanf("%d %d", &id, &x);
		idade[id - 1] = x;
	}

	// inicializa lista de adjacencia
	List arestas[n];
	for (int i = 0; i < n; i++) arestas[i] = new_list();

	// le arestas
	for (int i = 0; i < m; i++) {
		int id1, id2; scanf("%d %d", &id1, &id2);
		id1--; id2--;

		// soh adiciona arestas entre pessoas jovens
		if (idade[id1] >= 35 || idade[id2] >= 35) continue;

		append(&arestas[id1], id2);
		append(&arestas[id2], id1);
	}

	int prim; scanf("%d", &prim);

	// inicializa vetor de visitados
	char vis[n];
	for (int i = 0; i < n; i++) vis[i] = 0;

	// dfs no primeiro
	dfs(arestas, vis, prim - 1);

	// conta quantos foram visitados
	int gosta = 0;
	for (int i = 0; i < n; i++) if (vis[i]) gosta++;

	printf("%d\n", gosta);

	// apaga listas
	for (int i = 0; i < n; i++) del(&arestas[i]);
}
