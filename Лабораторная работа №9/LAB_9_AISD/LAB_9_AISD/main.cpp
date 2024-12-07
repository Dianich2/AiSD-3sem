#include <iostream>
#include <Windows.h>
#include <vector>
#include <cmath>
#include <random>

using namespace std;
#define INF 2147483647
vector<vector<int>> matrix;
int n;
int nachpopulation;
int kolScreshch;
double percentMutation;
int kolEvolution;

class Chromosome {
public:
	vector<int> curpath;
	double lengthOfpath;

	Chromosome(int n) {
		for (int i = 0; i < n; i++) {
			curpath.push_back(i);
		}
		random_shuffle(curpath.begin(), curpath.end());
		lengthOfpath = calculateLengthOfPath();
	}

	double calculateLengthOfPath() {
		double curdist = 0;
		for (int i = 0; i < curpath.size(); i++) {
			curdist += matrix[curpath[i]][curpath[(i + 1) % curpath.size()]];
		}
		return curdist;
	}

	static vector<Chromosome> crossover(const Chromosome& first_parent, const Chromosome& second_parent) {
		int size = first_parent.curpath.size();
		vector<Chromosome> child;
		Chromosome children1(size);
		Chromosome children2(size);

		children1.curpath.assign(size, -1);
		children2.curpath.assign(size, -1);

		int crossoverStart = 0;
		int crossoverEnd = rand() % size;
		for (int i = crossoverStart; i <= crossoverEnd; i++) {
			children1.curpath[i] = first_parent.curpath[i];
		}

		int buf = crossoverEnd + 1;
		for (int i = 0; i < size; i++) {
			if (find(children1.curpath.begin(), children1.curpath.end(), second_parent.curpath[i]) == children1.curpath.end()) {
				if (buf < size) { 
					children1.curpath[buf] = second_parent.curpath[i];
					buf++;
				}
			}
		}
		children1.lengthOfpath = children1.calculateLengthOfPath();

		for (int i = crossoverStart; i <= crossoverEnd; i++) {
			children2.curpath[i] = second_parent.curpath[i];
		}

		buf = crossoverEnd + 1;
		for (int i = 0; i < size; i++) {
			if (find(children2.curpath.begin(), children2.curpath.end(), first_parent.curpath[i]) == children2.curpath.end()) {
				if (buf < size) { 
					children2.curpath[buf] = first_parent.curpath[i];
					buf++;
				}
			}
		}
		children2.lengthOfpath = children2.calculateLengthOfPath();

		child.push_back(children1);
		child.push_back(children2);
		return child;
	}

	void mutate() {
		for (int i = 0; i < curpath.size(); i++) {
			if ((rand() / (double)RAND_MAX) < percentMutation) {
				int j = rand() % curpath.size();
				swap(curpath[i], curpath[j]);
			}
		}
		lengthOfpath = calculateLengthOfPath();
	}
};


vector<Chromosome> initPopulation(int n) {
	vector<Chromosome> population;
	for (int i = 0; i < nachpopulation; i++) {
		population.emplace_back(n);
	}
	return population;
}

Chromosome parentSelection(const vector<Chromosome>& population) {
	int parentssize = 10;
	vector<Chromosome> parents;
	for (int i = 0; i < parentssize; i++) {
		parents.push_back(population[rand() % population.size()]);
	}
	return *min_element(parents.begin(), parents.end(), [](const Chromosome& a, const Chromosome& b) {
		return a.lengthOfpath < b.lengthOfpath;
	});
}


void geneticAlgorithm() {
	vector<Chromosome> population = initPopulation(n);
	for (int generation = 0; generation < kolEvolution; generation++) {
		for (int i = 0; i < kolScreshch; i++) {
			Chromosome parent1 = parentSelection(population);
			Chromosome parent2 = parentSelection(population);
			
			vector<Chromosome> offspring = Chromosome::crossover(parent1, parent2);
			offspring[0].mutate();
			offspring[1].mutate();
			population.push_back(offspring[0]);
			population.push_back(offspring[1]);
		}
		sort(population.begin(), population.end(), [](const Chromosome& a, const Chromosome& b) {
			return a.lengthOfpath < b.lengthOfpath;
		});


		vector<Chromosome> newpopulation;
		for (int i = 0; i < population.size() / 2; i++) {
			newpopulation.push_back(population[i]);
		}
		population = newpopulation;

		cout << "\n\nНомер поколения" <<  generation + 1 << '\n';
		Chromosome best = *min_element(population.begin(), population.end(), [](const Chromosome& a, const Chromosome& b) {
			return a.lengthOfpath < b.lengthOfpath;
			});
		cout << "Минимальный путь\n";
		for (int i = 0; i < best.curpath.size(); i++) {
			cout << best.curpath[i] + 1 << ' ';
		}
		cout << '\n';
		cout << "Длина пути = " << best.lengthOfpath << '\n';
	}
}


int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Введите количество городов\n";
	cin >> n;
	cout << "Для каждого города вводите расстояния до других городов\n";
	for (int i = 0; i < n; i++) {
		vector<int> b(n);
		for (int j = 0; j < n; j++) {
			cin >> b[j];
			if (b[j] == -1) {
				b[j] = INF;
			}
		}
		matrix.push_back(b);
	}
	cout << "Введите начальный размер популяции\n";
	cin >> nachpopulation;
	int buf = nachpopulation * 100;
	cout << "Введите количество скрещиваний, которое будет выполняться на каждом цикле\n";
	cin >> kolScreshch;
	cout << "Введите показатель мутации(<= 1)";
	cin >> percentMutation;
	cout << "Введите количество циклов эволюции\n";
	cin >> kolEvolution;
	geneticAlgorithm();
}