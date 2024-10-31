#include <iostream>
#include <Windows.h>
#include <vector>
using namespace std;

void increasingSubsequence(int n, vector<int> a) {
	vector<int> count(n, 0);
	count[0] = 1;
	vector<int> prev(n, -1);
	for (int i = 1; i < n; i++) {
		for (int j = 0; j < i; j++) {
			if (a[i] > a[j]) {
				if (count[j] + 1 >= count[i]) {
					count[i] = count[j] + 1;
					prev[i] = j;
				}
			}
		}
	}
	int max_i = 0;
	int pos = -1;
	for (int i = 0; i < n; i++) {
		if (max_i <= count[i]) {
			max_i = count[i];
			pos = i;
		}
	}
	vector<int> r;
	cout << "Наибольшее число элементов в подпоследовательности = " << max_i << '\n';
	while (pos != -1) {
		r.push_back(a[pos]);
		max_i = a[pos];
		pos = prev[pos];
	}
	reverse(r.begin(), r.end());
	for (int i = 0; i < r.size(); i++) {
		cout << r[i] << ' ';
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n;
	cin >> n;
	while (n <= 0) {
		cout << "Некорректный ввод\nПопробуйте снова\n";
		cin >> n;
	}
	int k;
	vector<int> a;
	for (int i = 0; i < n; i++) {
		cin >> k;
		a.push_back(k);
	}
	increasingSubsequence(n, a);
}