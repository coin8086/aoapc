#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <climits>
#include <cmath>

using namespace std;

typedef map<char, set<char> > Graph;

int bandwidth(const Graph & g, const vector<char> & p) {
  int mm = 0;
  for (int i = 0; i < p.size(); i++) {
    typedef vector<char>::const_iterator It;
    char u = p[i];
    const set<char> & n = g.at(u);
    It pu = find(p.begin(), p.end(), u);
    It pf = find_first_of(p.begin(), p.end(), n.begin(), n.end());
    int m = abs(pu - pf);
    if (n.size() > 1) {
      int m2 = abs(pu - p.begin() -
        (abs(p.rend() - find_first_of(p.rbegin(), p.rend(), n.begin(), n.end())) - 1));
      m = max(m, m2);
    }
    if (m > mm)
      mm = m;
  }
  return mm;
}

int min_bandwidth(const Graph & g, vector<char> & p) {
  Graph::const_iterator it = g.begin();
  vector<char> t;
  t.reserve(g.size());
  p.resize(g.size());
  for (; it != g.end(); it++) {
    t.push_back(it->first);
  }
  sort(t.begin(), t.end());
  int w = INT_MAX;
  do {
    int m = bandwidth(g, t);
    if (m < w) {
      w = m;
      copy(t.begin(), t.end(), p.begin());
    }
  } while (next_permutation(t.begin(), t.end()));
  return w;
}

int main() {
  string line;
  while (getline(cin, line) && line != "#") {
    Graph g;
    int i = 0;
    while (true) {
      char u = line[i++];
      set<char> & n = g[u];
      i++; //skip ':'
      char v;
      while ((v = line[i]) && v != ';') {
        n.insert(v);
        g[v].insert(u);
        i++;
      }
      if (!v)
        break;
      i++; //skip ';'
    }
    vector<char> p;
    int w = min_bandwidth(g, p);
    for (i = 0; i < p.size(); i++) {
      cout << p[i] << ' ';
    }
    cout << "-> " << w << endl;
  }
  return 0;
}
