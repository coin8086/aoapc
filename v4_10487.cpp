#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

inline int closer(int a, int b, int c) {
  return abs(a - c) <= abs(b - c) ? a : b;
}

int closest_sum(const vector<int> & nums, int sum) {
  typedef vector<int>::const_iterator It;
  It up = upper_bound(nums.begin(), nums.end(), sum);
  if (up == nums.begin())
    return nums[0] + nums[1];
  int s;
  if (up == nums.end())
    s = INT_MAX;
  else
    s = *up + nums.front();
  while (true) {
    --up;
    int r = sum - *up;
    It lw = lower_bound(nums.begin(), nums.end(), r);
    if (lw >= up) {
      if (lw == up && lw != nums.begin())
        s = closer(s, *lw + *(lw - 1), sum);
      else if (lw == nums.end())
        s = *(lw - 1) + *(lw - 2);
      break;
    }
    s = closer(s, *lw + *up, sum);
    if (lw != nums.begin())
      s = closer(s, *(lw - 1) + *up, sum);
  }
  return s;
}

int main() {
  int n = 0;
  int c = 0;
  while (cin >> n && n) {
    int i;
    vector<int> nums;
    nums.reserve(n);
    for (i = 0; i < n; i++) {
      int num;
      cin >> num;
      nums.push_back(num);
    }
    sort(nums.begin(), nums.end());
    int m;
    cin >> m;
    cout << "Case " << ++c << ":" << endl;
    for (i = 0; i < m; i++) {
      int sum;
      cin >> sum;
      cout << "Closest sum to " << sum << " is " << closest_sum(nums, sum) << "." << endl;
    }
  }
  return 0;
}
