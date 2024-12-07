#include <iostream>
#include <Windows.h>
#include <vector> 
#include <string>

using namespace std;

double knapsack(const vector<int>& weights, const vector<double>& values, const vector<string>& items, int capacity, vector<string>& selectedItems) {
  int n = values.size();

  vector<vector<double>> dp(n + 1, vector<double>(capacity + 1, 0.0));

  for (int i = 1; i <= n; ++i) {
    for (int w = 0; w <= capacity; ++w) {
      if (weights[i - 1] <= w) {
        if (values[i - 1] + dp[i - 1][w - weights[i - 1]] > dp[i - 1][w]) {
          dp[i][w] = values[i - 1] + dp[i - 1][w - weights[i - 1]];
        }
        else {
          dp[i][w] = dp[i - 1][w];
        }
      }
      else {
        dp[i][w] = dp[i - 1][w];
      }
    }
  }

  int w = capacity;
  for (int i = n; i > 0 && dp[i][w] > 0; i--) {
    if (dp[i][w] != dp[i - 1][w]) {
      selectedItems.push_back(items[i - 1]);
      w -= weights[i - 1];
    }
  }
  reverse(selectedItems.begin(), selectedItems.end());
  return dp[n][capacity]; 
}

int main() {
  SetConsoleCP(1251);
  SetConsoleOutputCP(1251);
  int vmest;
  cout << "Введите вместимость рюкзака\n";
  cin >> vmest;
  int n;
  cout << "Введите количество элементов\n";
  cin >> n;
  vector<int> weights;
  vector<double> costs;
  vector<string> names;
  string buf;
  double g;
  for (int i = 0; i < n; i++) {
    cout << "Введите название предмета\n";
    getline(cin, buf);
    getline(cin, buf);
    names.push_back(buf);
    cout << "Введите вес предмета\n";
    cin >> g;
    weights.push_back(g);
    cout << "Введите стоимость предмета\n";
    cin >> g;
    costs.push_back(g);
  }                              
  
  vector<string> items;
  double max_value = knapsack(weights, costs, names, vmest, items);;
  cout << "Максимальная ценность, которую можно получить: " << max_value << '\n';

  cout << "Выбранные товары: ";
  for (const auto& item : items) {
    cout << item << " ";
  }

  return 0;
}