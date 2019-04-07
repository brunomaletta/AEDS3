#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INF = 0x3f3f3f3f;

typedef struct {
	int d;         // distancia (para ordenar)
	int size;      // tamanho
	char* s;       // string
} string;

typedef struct {
	int f, s;
} pair;

int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int cmp(const void* a, const void* b) {
	string* s1 = (string*) a;
	string* s2 = (string*) b;
	// ordena pela distancia
	if (s1->d != s2->d)
		return s1->d - s2->d;
	// se empata, pela ordem lexicografica
	for (int i = 0; i < max(s1->size, s2->size); i++)
		if (s1->s[i] != s2->s[i])
			return s1->s[i] - s2->s[i];
	
	return s1->size - s2->size;
}

pair pd[110][6010];
int n;
int at; // string atual do dicionario

char q[110];
char x[6010];

int dist(int i, int j) {
	// se o valor ja foi calculado, retorna ele
	if (pd[i][j].s == at) return pd[i][j].f;

	// diferenca entre as posicoes eh maior que
	// n: nao calcula mais
	if (abs(i - j) > n) {
		pd[i][j].s = at;
		return pd[i][j].f = INF;
	}

	// um dos tamanhos eh 0: a distancia eh igual
	// a deletar todos os caracteres da maior string
	if (i * j == 0) {
		pd[i][j].s = at;
		return pd[i][j].f = max(i, j);
	}

	// os ultimos caracteres sao iguais
	if (q[i - 1] == x[j - 1]) {
		pd[i][j].s = at;
		return pd[i][j].f = dist(i - 1, j - 1);
	}

	// remover um caractere de a
	int ret = dist(i - 1, j);
	// remover um caractere de b
	ret = min(ret, dist(i, j - 1));
	// substituir
	ret = min(ret, dist(i - 1, j - 1));

	// armazena e retorna
	pd[i][j].s = at;
	return pd[i][j].f = 1 + ret;
}

// insere palavra no vetor
void add(string* v, int* p, char* a, int d) {
	string b;
	b.size = strlen(a);
	b.d = d;

	b.s = malloc((b.size + 1) * sizeof(char));
	for (int i = 0; i < b.size + 1; i++) b.s[i] = a[i];

	v[(*p)++] = b;
}

int main () {
	int d;
	scanf("%d %d", &d, &n);
	scanf(" %s", q);

	string resp[d]; // vetor de resposta
	int count = 0; // numero de strings na resposta

	for (int i = 0; i < d; i++) {
		// le string
		scanf(" %s", x);

		// calcula distancia;
		at = i + 1;
		int distancia = dist(strlen(q), strlen(x));
		
		// se a distancia eh valida, insere no vetor
		if (distancia <= n) add(resp, &count, x, distancia);
	}

	// ordena resposta
	qsort(resp, count, sizeof(string), cmp);

	// imprime resposta
	for (int i = 0; i < count; i++) printf("%s\n", resp[i].s);

	// libera memoria
	for (int i = 0; i < count; i++) free(resp[i].s);

	return 0;
}
