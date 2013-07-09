#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

/*
** While trying to improve the speed by replacing the next_permutation,
** I only found the pro version is even a little slower! What a sadness!
** But I think the trackback version is useful when considering pruning.
** Also, it can be used to generate Perm(n, m) where n != m. So let's keep it.
*/

typedef vector<pair<char, int> > Stat; //Char and its occurrence count

void back_track(const Stat & stat, int len, vector<int> & in, string & p, int c = 0) {
  if (c == len) {
    cout << p << endl;
  }
  else {
    for (int i = 0; i < stat.size(); i++) {
      if (stat[i].second > in[i]) {
        p[c] = stat[i].first;
        in[i]++;
        back_track(stat, len, in, p, c + 1);
        in[i]--;
      }
    }
  }
}

inline void output_perms(string & s) {
  Stat stat;
  sort(s.begin(), s.end());
  int c = 0;
  char ch = 0;
  for (int i = 0; i <= s.size(); i++) { //Note the trick "i <= s.size()" here
    if (ch != s[i]) {
      if (i) {
        stat.push_back(make_pair(ch, c));
      }
      c = 1;
      ch = s[i];
    }
    else {
      c++;
    }
  }
  vector<int> in(stat.size());
  string p(s.size(), ' ');
  back_track(stat, s.size(), in, p);
  cout << endl;
}

int main() {
  int n = 0;
  cin >> n;
  cin.ignore();
  string p;
  p.reserve(10);
  for (int i = 0; i < n; i++) {
    cin >> p;
    output_perms(p);
  }
  return 0;
}
