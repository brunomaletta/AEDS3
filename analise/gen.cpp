#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	int n = atoi(argv[1]), m = atoi(argv[2]);
	
	vector<int> v1, v2;
	for (int i = 0; i < n; i++) {
		if (i % 2) v1.push_back(i);
		else v2.push_back(i);
	}

	m = v1.size() * v2.size();
	printf("%d\n%d\n", n, m);

//	srand(time(0));
//	random_shuffle(v.begin(), v.end());

//	for (int i = 0; i < m; i++) {
//		int p = rand() % (v.size());
//		pair<int, int> q = v[p];
//
//		printf("%d %d\n", q.first, q.second);
//
//		v.erase(v.begin() + p);
//	}

//	for (int i = 0; i < m; i++)
//		printf("%d %d\n", v[i].first + 1, v[i].second + 1);

//	for (int i = 0; i < n/2; i++)
//		for (int j = n/2; j < n; j++)
//			printf("%d %d\n", v[i] + 1, v[j] + 1);

	for (int i = 0; i < v1.size(); i++)
		for (int j = 0; j < v2.size(); j++)
			printf("%d %d\n", v1[i] + 1, v2[j] + 1);

	return 0;
}
