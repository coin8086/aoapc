#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Comparer {
public:
  bool operator () (const string & a, const string & b) const {
    const char * s1 = a.c_str();
    const char * s2 = b.c_str();
    const char * p;
    const char * q;
    while (true) {
      p = s1;
      q = s2;
      while (*p && *q) {
        if (*p == *q) {
          ++p, ++q;
        }
        else {
          break;
        }
      }
      if ((*p && *q) || (!*p && !*q)) {
        break;
      }
      else if (*p) { //For strings like "543544" and "543", compare "544" and "543".
        s1 = p;
      }
      else { //For strings like "543" and "543544", compare "543" and "544"
        s2 = q;
      }
    }
    return *p > *q;
  }
};

Comparer cmp;

int main() {
  int n = 0;
  while (cin >> n && n) {
    vector<string> nums;
    string num;
    int i;
    for (i = 0; i < n; i++) {
      cin >> num;
      nums.push_back(num);
    }
    sort(nums.begin(), nums.end(), cmp);
    for (i = 0; i < n; i++)
      cout << nums[i];
    cout << endl;
  }
  return 0;
}
