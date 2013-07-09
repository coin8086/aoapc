#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

inline bool in_order(const vector<int> & a) {
  int i;
  for (i = 0; i < a.size() - 1; i++) {
    if (a[i] > a[i + 1])
      break;
  }
  return i == a.size() - 1;
}

inline void back_track(vector<int> & a, int & c) {
  if (in_order(a)) {
    c++;
  }
  else {
    for (int i = 0; i < a.size() - 1; i++) {
      if (a[i] > a[i + 1]) {
        swap(a[i], a[i + 1]);
        back_track(a, c);
        swap(a[i], a[i + 1]);
      }
    }
  }
}

inline int swap_maps(vector<int> & a) {
  int c = 0;
  if (!in_order(a))
    back_track(a, c);
  return c;
}

int main() {
  int c = 0;
  int n = 0;
  vector<int> a;
  a.reserve(5);
  while (cin >> n && n) {
    a.clear();
    for (int i = 0; i < n; i++) {
      int k;
      cin >> k;
      a.push_back(k);
    }
    cout << "There are " << swap_maps(a) << " swap maps for input data set " << ++c << "." << endl;
  }
  return 0;
}
