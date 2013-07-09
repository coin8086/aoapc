#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
  int n = 0;
  cin >> n;
  cin.ignore();
  string p;
  p.reserve(10);
  for (int i = 0; i < n; i++) {
    cin >> p;
    sort(p.begin(), p.end());
    do {
      cout << p << endl;
    } while (next_permutation(p.begin(), p.end()));
    cout << endl;
  }
  return 0;
}
