#include <iostream>
#include <Windows.h>
#include <vector>

using namespace std;
int n;
double alpha;
double beta;
int koliter;
double procIspar;
double kolPheromonesFromOneAnt;
int kolAnts = 20;
vector<vector<int>> matrix;
vector<vector<double>> pheromones;


double calculatePathLength(const vector<int>& path) {
	double length = 0.0;
	for (int i = 0; i < path.size() - 1; i++) {
		length += matrix[path[i]][path[i + 1]];
	}
	length += matrix[path.back()][path[0]];
	return length;
}

void changePheromones(const vector<vector<int>>& paths) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			pheromones[i][j] *= (1 - procIspar);
		}
	}

	for (const auto& path : paths) {
		double length = calculatePathLength(path);
		for (int i = 0; i < path.size() - 1; i++) {
			pheromones[path[i]][path[i + 1]] += kolPheromonesFromOneAnt / length;
			pheromones[path[i + 1]][path[i]] += kolPheromonesFromOneAnt / length;
		}
		pheromones[path.back()][path[0]] += kolPheromonesFromOneAnt / length; 
		pheromones[path[0]][path.back()] += kolPheromonesFromOneAnt / length; 
	}
}

int main() {
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите количество городов\n";
	cin >> n;
	cout << "Введите расстояния до городов в виде матрицы смежности(значение расстояния должно быть > 0)\n";
	for (int i = 0; i < n; i++) {
		vector<int> buf(n);
		for (int j = 0; j < n; j++) {
			cin >> buf[j];
		}
		matrix.push_back(buf);
	}
	cout << "Введите значение альфа\n";
	cin >> alpha;
	cout << "Введите значение бета\n";
	cin >> beta;
	cout << "Введите количество итераций\n";
	cin >> koliter;
	cout << "Введите количество феромонов на каждом ребре в виде матрицы смежности(если в ту же самую клетку, то введите 0)\n";
	for (int i = 0; i < n; i++) {
		vector<double> buf(n);
		for (int j = 0; j < n; j++) {
			cin >> buf[j];
		}
		pheromones.push_back(buf);
	}
	cout << "Введите коэффициент испарения феромонов за цикл(<1)\n";
	cin >> procIspar;
	cout << "Введите количество феромонов, оставляемое одним муравьем\n";
	cin >> kolPheromonesFromOneAnt;

	int thebestlength = 10000000;
	vector<int> thebestpath(n);
	for (int iter = 0; iter < koliter; iter++) {
		vector<vector<int>> paths(kolAnts, vector<int>(n));
		for (int cur_ant = 0; cur_ant < kolAnts; cur_ant++) {
			vector<bool> visited(n, false);
			int startCity = rand() % n;
			paths[cur_ant][0] = startCity;
			visited[startCity] = true;

			for (int phase = 1; phase < n; phase++) {
				int currentCity = paths[cur_ant][phase - 1];
				double totalProbability = 0.0;
				vector<double> probabilities(n, 0.0);

				for (int cur_city = 0; cur_city < n; cur_city++) {
					if (!visited[cur_city] && matrix[currentCity][cur_city] > 0) {
						probabilities[cur_city] = pow(pheromones[currentCity][cur_city], alpha) *
							pow(1.0 / matrix[currentCity][cur_city], beta);
						totalProbability += probabilities[cur_city];
					}
				}

				double randomValue = (double)rand() / RAND_MAX * totalProbability;
				for (int cur_city = 0; cur_city < n; cur_city++) {
					if (!visited[cur_city] && matrix[currentCity][cur_city] > 0) {
						randomValue -= probabilities[cur_city];
						if (randomValue <= 0) {
							paths[cur_ant][phase] = cur_city;
							visited[cur_city] = true;
							break;
						}
					}
				}
			}
		}
		double bestLength = 10000000;
		vector<int> bestPath;
		for (const auto& path : paths) {
			double length = calculatePathLength(path);
			if (length < bestLength) {
				bestLength = length;
				bestPath = path;
			}
		}
		if (thebestlength > bestLength) {
			thebestlength = bestLength;
			for (int k = 0; k < n; k++) {
				thebestpath[k] = bestPath[k];
			}
		}
		cout << "Текущая итерация " << iter + 1 << '\n';
		cout << "Лучший путь: ";
		for (int city : thebestpath) {
			cout << city + 1 << " ";
		}
		cout << "\nДлина пути: " << thebestlength << '\n';
		changePheromones(paths);
	}
}