// =----------------------------------------------------------=
// =                           AVISO:                         =
// =                   MODIFIQUE ESTE ARQUIVO!                =
// = Aqui, você deve implementar, obrigatoriamente, essas     =
// = duas funções:                                            =
// =     - `a_menor_que_b`: deve retornar quando uma string   =
// =        é menor que a outra (ambos com o mesmo tamanho);  =
// =     - `external_sort`: aqui, você deverá implementar o   =
// =        seu trabalho. Ordene os registros em `input_file` =
// =        e escreva-os em `output_file`, usando somente     =
// =        `memory` KB de memória.                           =
// =                                                          =
// = Instruções:                                              =
// =     - use a função `mathias_malloc` ao invés de          =
// =       `malloc`;                                          =
// =     - use a função `mathias_free` ao invés de `free`;    =
// =     - lembre-se que você tem somente `memory` KB de      =
// =       memória;                                           =
// =     - note que a sua implementação de `a_menor_que_b`    =
// =       afetará o resultado da verificação da resposta.    =
// =                                                          =
// = Dicas:                                                   =
// =     - você pode usar a sua função `a_menor_que_b` em     =
// =       sua implementação da função `external_sort`;       =
// =                                                          =
// =                      BOM TRABALHO!                       =
// =----------------------------------------------------------=

#include <stdio.h>
#include "mem.h"

// Parâmetros:
//     - a: uma cadeia de caracteres de tamanho `len`;
//     - b: uma cadeia de caracteres de tamanho `len`;
//     - len: o tamanho (quantidade de bytes) de `a` e `b`.
// Essa função deve retornar 1, se `a` é menor que `b` (`a` deve vir antes de `b` no
// arquivo), e 0 caso contrário.
// Ela também é usada para verificação da ordenação! Então, se você implementá-la
// erroneamente, a verificação também estará errada! 
int a_menor_que_b(char* a, char* b, int len) {

	for (int i = 0; i < len; i++) {
		// retorna primeira diferenca
		if (a[i] < b[i]) return 1;
		if (a[i] > b[i]) return 0;
	}

	// strings iguais: retorna 0
	return 0;
}

// troca duas strings
void swap(char* a, char* b, int tam) {
	for (int i = 0; i < tam; i++) {
		char tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	}
}

// bubble sort: O(n^2)
void bubble(char** v, int size, int line_size) {
	while (--size) {
		int changed = 0;
		for (int i = 0; i < size; i++)
			if (!a_menor_que_b(v[i], v[i + 1], line_size)) {
				swap(v[i], v[i + 1], line_size);
				changed = 1;
			}
		if (!changed) break;
	}
}
// Parâmetros:
//     - input_file: o nome do arquivo com os registros de entrada;
//     - output_file: o nome do arquivo com os registros de entrada ordenados;
//     - memory: o limite de memória a ser usado.
// Essa função deverá ler todos registros do arquivo `input_file`, ordená-los e
// escrevê-los em `output_file`, usando memória menor ou igual a `memory`. Lembre-se
// de fechar todos os arquivos que você usar por aqui!!
void external_sort(const char* input_file, const char* output_file, unsigned int memory) {

	// abrea arquivos
	FILE* in = fopen(input_file, "r");
	FILE* out = fopen(output_file, "w");

	// le tamanho das linhas
	int line_size; fscanf(in, "%d%*c", &line_size);
	fprintf(out, "%d\n", line_size);

	// calcula memoria maxima disponivel
	line_size++;
	long long max_bytes = 1000 * (long long) memory;
	int max_lines = max_bytes / line_size;

	max_bytes -= sizeof(char*) * max_lines;
	max_lines = max_bytes / line_size;

	// usa no maximo 100 strings
	if (max_lines < 2 || max_lines > 100) max_lines = 100;

	// abre fitas
	FILE* f1 = fopen("f1.txt", "w");
	FILE* f2 = fopen("f2.txt", "w");
	FILE* f3 = fopen("f3.txt", "w");

	// aloca memoria
	char** v = mathias_malloc(max_lines * sizeof(char*));
	for (int i = 0; i < max_lines; i++) v[i] = mathias_malloc(line_size * sizeof(char));

	// fase de criacao dos blocos ordenados
	
	int alterna = 1;
	while (1) {

		// le 'size' linhas
		int size = 0;
		while (size < max_lines && fscanf(in, "%[^\n]%*c", v[size]) != EOF) size++;

		// fim do arquivo
		if (size == 0) break;

		// ordena internamente o bloco
		bubble(v, size, line_size);

		// coloca bloco ordenado na fita
		for (int i = 0; i < size; i++) {
			if (alterna) fprintf(f1, "%s\n", v[i]);
			else fprintf(f2, "%s\n", v[i]);
		}
		
		alterna = !alterna;
	}

	// tamanho atual dos blocos
	int tam = max_lines;

	// abre fitas para leitura
	fclose(f1); f1 = fopen("f1.txt", "r");
	fclose(f2); f2 = fopen("f2.txt", "r");

	// fase de intercalacao
	
	while (1) {

		// quantidade que foi pega de cada fita para criar o bloco
		int tam1 = 0, tam2 = 0;

		// r1, r2: usados para saber quando os arquivos terminaram
		int r1 = fscanf(f1, "%[^\n]%*c", v[0]);
		int r2 = fscanf(f2, "%[^\n]%*c", v[1]);

		// junta os blocos das fitas 1 e 2 para a fita 3
		while (r1 != EOF || r2 != EOF) {

			// fim do bloco
			if ((tam1 == tam && tam2 == tam) || (tam1 == tam && r2 == EOF)
					|| (tam2 == tam && r1 == EOF)) tam1 = tam2 = 0;

			if (r1 == EOF || tam1 == tam) { 		// bloco da fita 1 terminou -> pega da 2
				fprintf(f3, "%s\n", v[1]);
				tam2++;
				r2 = fscanf(f2, "%[^\n]%*c", v[1]);
			} else if (r2 == EOF || tam2 == tam) { 	// bloco da fita 2 terminou -> pega da 1
				fprintf(f3, "%s\n", v[0]);
				tam1++;
				r1 = fscanf(f1, "%[^\n]%*c", v[0]);
			} else { 							// senao -> pega da menor
				if (a_menor_que_b(v[0], v[1], line_size)) {
					fprintf(f3, "%s\n", v[0]);
					tam1++;
					r1 = fscanf(f1, "%[^\n]%*c", v[0]);
				} else {
					fprintf(f3, "%s\n", v[1]);
					tam2++;
					r2 = fscanf(f2, "%[^\n]%*c", v[1]);
				}
			}
		}

		// tamanho passa a ser o dobro
		tam *= 2;

		// reabre os arquivos da forma correta
		fclose(f1); f1 = fopen("f1.txt", "w");
		fclose(f2); f2 = fopen("f2.txt", "w");
		fclose(f3); f3 = fopen("f3.txt", "r");

		// redistribui os blocos nas fitas 1 e 2
		
		alterna = 1;
		int done = 1;
		tam1 = 0; // tamanho atual do bloco que vamos colocar na fita 1 ou 2
		while (fscanf(f3, "%[^\n]%*c", v[0]) != EOF) {

			// fim do bloco: alterna a fita
			if (++tam1 > tam) {
				alterna = !alterna;
				done = 0;
				tam1 = 1;
			}

			// coloca na fita
			if (alterna) fprintf(f1, "%s\n", v[0]);
			else fprintf(f2, "%s\n", v[0]);
		}

		// reabre os arquivos da forma correta
		fclose(f1); f1 = fopen("f1.txt", "r");
		fclose(f2); f2 = fopen("f2.txt", "r");
		fclose(f3); f3 = fopen("f3.txt", "w");

		// terminou de ordenar
		if (done) break;
	}

	// coloca no arquivo de saida
	while (fscanf(f1, "%[^\n]%*c", v[0]) != EOF) fprintf(out, "%s\n", v[0]);

	// libera memoria e apaga arquivos
	fclose(f1); remove("f1.txt");
	fclose(f2); remove("f2.txt");
	fclose(f3); remove("f3.txt");
	fclose(in);
	fclose(out);
	for (int i = 0; i < max_lines; i++) mathias_free(v[i]);
	mathias_free(v);
}
