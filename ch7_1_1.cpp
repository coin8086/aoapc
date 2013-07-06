#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <cstdlib>

using namespace std;

typedef pair<string, string> Fraction;

inline int to_int(const string & str) {
  return atoi(str.c_str());
}

//Maybe sprintf in cstdio is faster, but it's said better not mix iostream
//and stdio headers. Also, since enumerator doesn't have leading zeros, we
//don't have to care it.
inline string to_str(int n) {
  string i;
  while (n) {
    i.push_back('0' + (n % 10));
    n /= 10;
  }
  reverse(i.begin(), i.end());
  return i;
}

inline bool valid_permutation(const string & str1, const string & str2) {
  vector<bool> present(10);
  int i;
  for (i = 0; i < 5; i++) {
    present[str1[i] - '0'] = true;
    present[str2[i] - '0'] = true;
  }
  for (i = 0; i < 10; i++) {
    if (!present[i])
      break;
  }
  return i == 10;
}

void track_back(string & denominator, int n, vector<Fraction> & r) {
  if (denominator.size() == 5) {
    int d = to_int(denominator);
    string enumerator = to_str(d * n);
    if (enumerator.size() == 5
      && valid_permutation(denominator, enumerator))
    {
      r.push_back(make_pair(enumerator, denominator));
    }
  }
  else {
    for (char ch = '0'; ch <= '9'; ch++) {
      if (denominator.find(ch) == string::npos) {
        denominator.push_back(ch);
        track_back(denominator, n, r);
        denominator.resize(denominator.size() - 1);
      }
    }
  }
}

inline vector<Fraction> divide(int n) {
  string denominator;
  if (n > 9)
    denominator.push_back('0');
  vector<Fraction> r;
  track_back(denominator, n, r);
  return r;
}

int main() {
  int n;
  while (cin >> n) {
    vector<Fraction> r = divide(n);
    if (r.empty())
      cout << "Impossible." << endl;
    else
      for (int i = 0; i < r.size(); i++) {
        Fraction & f = r[i];
        cout << f.first << " / " << f.second << " = " << n << endl;
      }
    cout << endl;
  }
  return 0;
}
