#include <iostream>
#include <Windows.h>
#include <map>
#include <vector>
#include <string>
#include <limits>
using namespace std;
const int INF = 2147483647;
map<char, int> sym = {
	{'A', 0}, {'B', 1}, {'C', 2}, {'D', 3}, {'E', 4},
	{'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}
};

void Dejkstra(int start, vector<vector<int>> matrix) {
	vector<int> dist = { INF, INF, INF, INF, INF, INF, INF, INF, INF };
	vector<bool> visited(9, false);
	int size = matrix.size();
	dist[start] = 0;
	for (int i = 0; i < size - 1; i++) {
		int min_dist = INF;
		int min_v = -1;

		for (int j = 0; j < size; j++) {
			if (!visited[j] && dist[j] < min_dist) {
				min_dist = dist[j];
				min_v = j;
			}
		}

		if (min_v == -1) break;
		visited[min_v] = true;

		for (int j = 0; j < size; j++) {
			if (matrix[min_v][j] != INF) {
				int n_dist = dist[min_v] + matrix[min_v][j];
				if (n_dist < dist[j]) {
					dist[j] = n_dist;
				}
			}
		}
	}
	for (char i = 'A'; i <= 'I'; i++) {
		cout << "Расстояние до вершины " << i << " = "
			<< (dist[sym[i]] == INF ? "бесконечности" : to_string(dist[sym[i]])) << endl;
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<vector<int>> matrix = {
		{0, 7, 10, INF, INF, INF, INF, INF, INF},
		{7, 0, INF, INF, INF, 9, 27, INF, INF},
		{10, INF, 0, INF, 31, 8, INF, INF, INF},
		{INF, INF, INF, 0, 32, INF, INF, 17, 21},
		{INF, INF, 31, 32,0, INF, INF, INF, INF},
		{INF, 9, 8, INF, INF, 0, INF, 11, INF},
		{INF, 27, INF, INF, INF, INF, 0, INF, 15},
		{INF, INF, INF, 17, INF, 11, INF, 0, 15},
		{INF, INF, INF, 21, INF, INF, 15, 15, 0}
	};
	char n;
	cout << "Введите стартовую вершину\n";
	cin >> n;
	while (n < 'A' || n > 'I') {
		cout << "Некорректный ввод\nПопробуйте снова\n";
		cin >> n;
	}
	Dejkstra(sym[n], matrix);
}