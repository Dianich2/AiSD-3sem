#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;
#define INF 2147483647

void Floid_Vorshell(vector<vector<int>> D, vector<vector<int>> S, int n) {
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					S[i][j] = S[i][k];
				}
			}
		}
	}
	cout << "Матрица D\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << D[i][j] << " ";
		}
		cout << '\n';
	}
	cout << "Матрица S\n";
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << S[i][j] << " ";
		}
		cout << '\n';
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<vector<int>> D = {
		{0, 28, 21, 59, 12, 27},
		{7, 0, 24, INF, 21, 9},
		{9, 32, 0, 13, 11, INF},
		{8, INF, 5, 0, 16, INF},
		{14, 13, 15, 10, 0, 22},
		{15, 18, INF, INF, 6, 0}
	};
	vector<vector<int>> S = {
		{0, 2, 3, 4, 5, 6},
		{1, 0, 3, 4, 5, 6},
		{1, 2, 0, 4, 5, 6},
		{1, 2, 3, 0, 5, 6},
		{1, 2, 3, 4, 0, 6},
		{1, 2, 3, 4, 5, 0}
	};

	Floid_Vorshell(D, S, 6);
}