#include <bits/stdc++.h>

using namespace std;

int main(int argc, char** argv) {
	if (argc < 4) {
		printf("Argumentos insuficientes\n");
		return 1;
	}

	int beg = atoi(argv[1]);
	int end = atoi(argv[2]);
	int jump = atoi(argv[3]);
	for (int size = beg; size <= end; size += jump) {

		char s[100];
		sprintf(s, "./gen.out %d %d > in.txt", size, 2 * size);
		system(s);

		auto start = std::chrono::high_resolution_clock::now();
		char s2[100];
		sprintf(s, "../tp3fb < in.txt");
		system(s);

		auto finish = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = finish - start;

		cout << size << "," << elapsed.count() << "\n";
	}
	return 0;
}
