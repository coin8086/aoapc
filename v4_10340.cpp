#include <iostream>
#include <string>

using namespace std;

inline bool all_in_all(const string & s, const string & t) {
  const char * p = s.c_str();
  const char * q = t.c_str();
  while (*p && *q) {
    if (*p == *q)
      ++p;
    ++q;
  }
  return *p == 0;
}

int main() {
  string s, t;
  s.reserve(1024);
  t.reserve(1024);
  while (cin >> s >> t) {
    cout << (all_in_all(s, t) ? "Yes" : "No") << endl;
  }
  return 0;
}
