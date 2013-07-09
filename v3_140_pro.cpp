#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <climits>

using namespace std;

typedef map<char, set<char> > Graph;

bool prune(const Graph & g, const vector<char> & t, vector<int> & c, int i,
  vector<int> & bw, int w)
{
  int m = 0;
  const set<char> & n = g.at(t[i]);
  int j;
  int count = 0;
  for (j = 0; j < c.size(); j++) {
    int k = c[j];
    if (n.count(t[k])) {
      count++;
      int d = c.size() - j;
      if (d >= w)
        break;
      if (d > m)
        m = d;
      if (bw[k] < d)
        bw[k] = d;
    }
  }
  bw[i] = m;
  return j != c.size() || n.size() - count >= w;
}

/*
** Paramters:
** g: Graph
** t: all vertices in dictionary order
** in: whether a vertex is already in c
** c: current permutation, indices of t
** bw: current bandwidth for each vertex
** p: permutation of minimum bandwidth so far, indices of t
** w: minimum bandwidth so far
*/
void back_track(const Graph & g, const vector<char> & t, vector<bool> & in,
  vector<int> & c, vector<int> & bw, vector<int> & p, int & w)
{
  if (c.size() == t.size()) {
    int b = *(max_element(bw.begin(), bw.end()));
    if (b < w) {
      w = b;
      copy(c.begin(), c.end(), p.begin());
    }
  }
  else {
    for (int i = 0; i < t.size(); i++) {
      if (!in[i]) {
        vector<int> nw = bw;
        if (!prune(g, t, c, i, nw, w)) {
          c.push_back(i);
          in[i] = true;
          back_track(g, t, in, c, nw, p, w);
          c.pop_back();
          in[i] = false;
        }
      }
    }
  }
}

int min_bandwidth(const Graph & g, vector<char> & p) {
  Graph::const_iterator it = g.begin();
  vector<char> t;
  t.reserve(g.size());
  for (; it != g.end(); it++) {
    t.push_back(it->first);
  }
  sort(t.begin(), t.end());
  vector<bool> in(g.size());
  vector<int> c;
  c.reserve(g.size());
  vector<int> m(g.size());
  vector<int> bw(g.size());
  int w = INT_MAX;
  back_track(g, t, in, c, bw, m, w);
  p.reserve(m.size());
  for (int i = 0; i < m.size(); i++) {
    p.push_back(t[m[i]]);
  }
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
