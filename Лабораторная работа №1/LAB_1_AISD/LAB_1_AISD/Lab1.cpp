#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;

void HanoiTower(int kol, int sour, int end, int helper) {
	if (kol == 1) {
		cout << "Перемещаем " << kol << " диск c " << sour << " на " << end << " стержень\n";
		return;
	}
	HanoiTower(kol - 1, sour, helper, end);
	cout << "Перемещаем " << kol << " диск c " << sour << " на " << end << " стержень\n";
	HanoiTower(kol - 1, helper, end, sour);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n, k, i;
	cout << "Введите количество дисков\n";
	cin >> n;
	cout << "Введите стержень, с которого будем перекладывать\n";
	cin >> i;
	while (i < 1 || i > 3) {
		cout << "Некорректный ввод! Возможные стержни 1, 2, 3\nПопробуйте снова\n";
		cin >> i;
	}
	cout << "Введите стержень, на который будем перекладывать\n";
	cin >> k;
	while ((k < 1 || k > 3) || k == i) {
		cout << "Некорректный ввод! Возможные стержни 1, 2, 3\nПопробуйте снова\n";
		cin >> k;
	}
	for (int j = 1; j <= 3; j++) {
		if (j != k && j != i) {
			HanoiTower(n, i, k, j);
		}
	}
}