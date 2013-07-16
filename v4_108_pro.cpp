#include <iostream>
#include <vector>
#include <cstring>
#include <climits>

#define MAX_SIZE 100

using namespace std;

int g[MAX_SIZE][MAX_SIZE];

inline int max_seq(int a[], int n) {
  int maxs = a[0];
  int mins = 0;
  int s = a[0];
  for (int i = 1; i < n; i++) {
    s += a[i];
    int m = s - mins;
    if (m > maxs)
      maxs = m;
    if (s < mins)
      mins = s;
  }
  return maxs;
}

int max_subrect(int n) {
  int m = INT_MIN;
  int s[MAX_SIZE];
  for (int i = 0; i < n; i++) {
    memcpy(s, g[i], n * sizeof(int));
    int ms = max_seq(s, n);
    if (ms > m)
      m = ms;
    for (int j = i + 1; j < n; j++) {
      for (int h = 0; h < n; h++)
        s[h] += g[j][h];
      ms = max_seq(s, n);
      if (ms > m)
        m = ms;
    }
  }
  return m;
}

int main() {
  int n = 0;
  while (cin >> n && n) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> g[i][j];
      }
    }
    cout << max_subrect(n) << endl;
  }
  return 0;
}
