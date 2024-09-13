#include <iostream>
#include <Windows.h>
#include <vector>
#include <stack>
#include <queue>
#include <map>
using namespace std;

void BFS(vector<vector<int>> matrix, int start) { 
	queue<int> q;
	vector<bool> t(matrix[0].size(), false);
	q.push(start);
	while (!q.empty()) { 
		int cur = q.front();
		q.pop();
		if (t[cur]) {
			continue;
		}
		cout << "Посещаем вершину с номером " << cur + 1 << '\n';
		t[cur] = true;
		for (int i = 0; i < matrix[cur].size(); i++) {
			if (matrix[cur][i] == 1 && !t[i]) {
				q.push(i);
			}
		}
	}
	cout << '\n';
}

void BFS(vector<pair<int, int>> listOfEdges, int start, int size) { 
	queue<int> q;
	vector<bool> t(size, false);
	q.push(start);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (t[cur]) {
			continue;
		}
		cout << "Посещаем вершину с номером " << cur + 1 << '\n';
		t[cur] = true;
		for (const auto& p: listOfEdges) {
			if (p.first == cur && !t[p.second]) {
				q.push(p.second);
			}
		}
	}
	cout << '\n';
}

void BFS(map<int, vector<int>> listOfAdjacencies, int start, int size) { 
	queue<int> q;
	vector<bool> t(size, false);
	q.push(start);
	while (!q.empty()) {
		int cur = q.front();
		q.pop();
		if (t[cur]) {
			continue;
		}
		cout << "Посещаем вершину с номером " << cur + 1 << '\n';
		t[cur] = true;
		for (const auto& p : listOfAdjacencies[cur]) {
			if (!t[p]) {
				q.push(p);
			}
		}
	}
	cout << '\n';
}


void DFS(vector<vector<int>> matrix, int start) { 
	stack<int> s;
	vector<bool> t(matrix[0].size(), false);
	s.push(start);
	while (!s.empty()) {
		int cur = s.top();
		s.pop();
		if (t[cur]) {
			continue;
		}
		cout << "Посещаем вершину с номером " << cur + 1 << '\n';
		t[cur] = true;
		for (int i = 0; i < matrix[cur].size(); i++) {
			if (matrix[cur][i] == 1 && !t[i]) {
				s.push(i);
			}
		}
	}
	cout << '\n';
}

void DFS(vector<pair<int, int>> listOfEdges, int start, int size) { 
	stack<int> s;
	vector<bool> t(size, false);
	s.push(start);
	while (!s.empty()) {
		int cur = s.top();
		s.pop();
		if (t[cur]) {
			continue;
		}
		cout << "Посещаем вершину с номером " << cur + 1 << '\n';
		t[cur] = true;
		for (const auto& p : listOfEdges) {
			if (p.first == cur && !t[p.second]) {
				s.push(p.second);
			}
		}
	}
	cout << '\n';
}

void DFS(map<int, vector<int>> listOfAdjacencies, int start, int size) { 
	stack<int> s;
	vector<bool> t(size, false);
	s.push(start);
	while (!s.empty()) {
		int cur = s.top();
		s.pop();
		if (t[cur]) {
			continue;
		}
		cout << "Посещаем вершину с номером " << cur + 1 << '\n';
		t[cur] = true;
		for (const auto& p : listOfAdjacencies[cur]) {
			if (!t[p]) {
				s.push(p);
			}
		}
	}
	cout << '\n';
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	vector<vector<int>> matrix = {
		{0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
		{1, 0, 0, 0, 0, 0, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
		{1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
		{0, 0, 0, 1, 1, 0, 0, 0, 1, 0},
		{0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
		{0, 1, 1, 0, 0, 0, 1, 0, 0, 0},
		{0, 0, 0, 1, 0, 1, 0, 0, 0, 1},
		{0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	};

	vector<pair<int, int>> listOfEdges = {
		{0, 1}, {0, 4}, {1, 0}, {1, 6}, {1, 7}, {2, 7}, {3, 5}, {3, 8},
		{4, 0}, {4, 5}, {5, 4}, {5, 3}, {5, 8}, {6, 1}, {6, 7}, {7, 1},
		{7, 2}, {7, 6}, {8, 3}, {8, 5}, {8, 9}, {9, 8}
	};

	 map<int, vector <int>> listOfAdjacencies = {
		{0,{1, 4}}, {1,{0, 6, 7}}, {2,{7}}, {3,{5, 8}}, {4,{0, 5}}, {5,{3, 4, 8}}, {6,{1, 7}},
		{7,{1, 2, 6}}, {8,{3, 5, 9}}, {9, {8}}
	};
	 int n;
	 cout << "Введите значение стартовой вершины\n";
	 cin >> n;
	 while (n < 1 || n > 10) {
		 cout << "Некорректный ввод\nПопробуйте снова\n";
		 cin >> n;
	 }
	 BFS(matrix, n - 1);
	 BFS(listOfEdges, n - 1, 10);
	 BFS(listOfAdjacencies, n - 1, 10);

	 DFS(matrix, n - 1);
	 DFS(listOfEdges, n - 1, 10);
	 DFS(listOfAdjacencies, n - 1, 10);
}