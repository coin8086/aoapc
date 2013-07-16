#include <iostream>
#include <vector>
#include <climits>

#define MAX_SIZE 100

using namespace std;

int g[MAX_SIZE + 1][MAX_SIZE + 1];

int max_subrect(int n) {
  int m = INT_MIN;
  int s[MAX_SIZE + 1][MAX_SIZE + 1];
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      int l;
      for (l = j - 1; l <= n; l++) {
        s[i - 1][l] = 0;
      }
      for (l = i - 1; l <= n; l++) {
        s[l][j - 1] = 0;
      }
      for (int h = i; h <= n; h++) {
        for (int k = j; k <= n; k++) {
          s[h][k] = s[h - 1][k] + s[h][k - 1] - s[h - 1][k - 1] + g[h][k];
          if (s[h][k] > m)
            m = s[h][k];
        }
      }
    }
  }
  return m;
}

int main() {
  int n = 0;
  while (cin >> n && n) {
    for (int i = 1; i <= n; i++) {
      for (int j = 1; j <= n; j++) {
        cin >> g[i][j];
      }
    }
    cout << max_subrect(n) << endl;
  }
  return 0;
}
