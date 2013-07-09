#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main() {
  int N = 0;
  cin >> N;
  for (int i = 0; i < N; i++) {
    if (i)
      cout << endl;
    int n, h;
    cin >> n >> h;
    string s(n - h, '0');
    s.reserve(n);
    for (int j = 0; j < h; j++)
      s.push_back('1');
    do {
      cout << s << endl;
    } while (next_permutation(s.begin(), s.end()));
  }
  return 0;
}
