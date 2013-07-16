#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using namespace std;

int cost(const vector<int> & nums) {
  int c = 0;
  priority_queue<int, vector<int>, greater<int> > q;
  for (int i = 0; i < nums.size(); i++) {
    q.push(nums[i]);
  }
  while (!q.empty()) {
    int a = q.top();
    q.pop();
    if (q.empty())
      break;
    int b = q.top();
    q.pop();
    int s = a + b;
    c += s;
    q.push(s);
  }
  return c;
}

int main() {
  int n;
  vector<int> nums;
  nums.reserve(5000);
  while (cin >> n && n > 0) {
    nums.clear();
    for (int i = 0; i < n; i++) {
      int num;
      cin >> num;
      nums.push_back(num);
    }
    cout << cost(nums) << endl;
  }
  return 0;
}
