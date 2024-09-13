#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
using namespace std;

void HanoiTower(int kol, int sour, int end, int helper) {
	if (kol == 1) {
		cout << "���������� " << kol << " ���� c " << sour << " �� " << end << " ��������\n";
		return;
	}
	HanoiTower(kol - 1, sour, helper, end);
	cout << "���������� " << kol << " ���� c " << sour << " �� " << end << " ��������\n";
	HanoiTower(kol - 1, helper, end, sour);
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n, k, i;
	cout << "������� ���������� ������\n";
	cin >> n;
	cout << "������� ��������, � �������� ����� �������������\n";
	cin >> i;
	while (i < 1 || i > 3) {
		cout << "������������ ����! ��������� ������� 1, 2, 3\n���������� �����\n";
		cin >> i;
	}
	cout << "������� ��������, �� ������� ����� �������������\n";
	cin >> k;
	while ((k < 1 || k > 3) || k == i) {
		cout << "������������ ����! ��������� ������� 1, 2, 3\n���������� �����\n";
		cin >> k;
	}
	for (int j = 1; j <= 3; j++) {
		if (j != k && j != i) {
			HanoiTower(n, i, k, j);
		}
	}
}