#include <iostream>
#include <Windows.h>
#include <vector>
#include <map>
#include <algorithm>
#include <set>

using namespace std;
#define INF 2147483647

void AlgoritmPRIMA(vector<vector<int>> matrix, int n, int cur) {
	vector<bool> use(n, false);
	vector<pair<int, int>> tree1;
	vector<int> weight;
	use[cur] = true;
	int check = 0;
	while(check != n){
		int min_dist = INF;
		int u = 0;
		int fir = 0;
		for (int k = 0; k < n; k++) {
			if (use[k] == true) {
				for (int j = 0; j < n; j++) {
					if (!use[j] && matrix[k][j] < min_dist && k != j) {
						min_dist = matrix[k][j];
						u = j;
						fir = k;
					}
				}
			}
		}
		use[u] = true;
		if (fir != u) {
			tree1.push_back({ fir + 1, u + 1 });
			weight.push_back(min_dist);
		}
		check++;
	}
	cout << "Алгоритм Прима\n";
	cout << "Ребра в минимальном остовном дереве:\n";
	int b = 0;
	for (const auto& entry : tree1) {
		cout << "Ребро " << entry.first << " - " << entry.second << ", вес = " << weight[b] << '\n';
		b++;
	}
	cout << '\n';
}




struct Edge {
	int u, v, weight;
};

void Kruskal(int n, vector<Edge>& edges) {
	sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
		return a.weight < b.weight;
		});

	vector<set<int>> components(n);
	for (int i = 0; i < n; ++i) {
		components[i].insert(i);
	}

	vector<Edge> result;

	for (const auto& edge : edges) {
		int u = edge.u;
		int v = edge.v;

		set<int>& comp_u = components[find_if(components.begin(), components.end(),
			[u](const set<int>& s) { return s.count(u); }) - components.begin()];

		set<int>& comp_v = components[find_if(components.begin(), components.end(),
			[v](const set<int>& s) { return s.count(v); }) - components.begin()];

		if (comp_u != comp_v) {
			result.push_back(edge);
			comp_u.insert(comp_v.begin(), comp_v.end()); 
			components.erase(find(components.begin(), components.end(), comp_v)); 
		}
	}
	cout << "Алгоритм Краскала\n";
	cout << "Ребра в минимальном остовном дереве:\n";
	for (const auto& edge : result) {
		cout << edge.u + 1 << " - " << edge.v + 1 << ", вес: " << edge.weight << endl;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<vector<int>> matrix{
		{0, 2, INF, 8, 2, INF, INF, INF},
		{2, 0, 3, 10, 5, INF, INF, INF},
		{INF, 3, 0, INF, 12, INF, INF, 7},
		{8, 10, INF, 0, 14, 3, 1, INF},
		{2, 5, 12, 14, 0, 11, 4, 8},
		{INF, INF, INF, 3, 11, 0, 6, INF},
		{INF, INF, INF, 1, 4, 6, 0, 9},
		{INF, INF, 7, INF, 8, INF, 9, 0}
	};
	int m;
	cin >> m;
	AlgoritmPRIMA(matrix, 8, m - 1);
	vector<Edge> edges;
	for (int i = 0; i < 8; ++i) {
		for (int j = i + 1; j < 8; ++j) { 
			if (matrix[i][j] != 0 && matrix[i][j] != INF) {
				edges.push_back({ i, j, matrix[i][j] });
			}
		}
	}
	Kruskal(8, edges);
}