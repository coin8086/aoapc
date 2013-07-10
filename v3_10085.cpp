#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <utility>
#include <algorithm>

using namespace std;

typedef vector<char> State;
typedef map<int, vector<int> > Graph;

Graph g;

inline void output(const State & s) {
  for (int k = 0; k < 9; k++) {
    int r = k % 3;
    if (r)
      cout << ' ';
    cout << (char)(s[k] + '0');
    if (r == 2)
      cout << endl;
  }
}

//Little endian.
inline int to_int(const State & s) {
  int n = 0;
  for (int i = s.size() - 1; i >= 0; i--) {
    n *= 10;
    n += s[i];
  }
  return n;
}

//Little endian.
inline State to_s(int i) {
  State s;
  s.reserve(9);
  while (i) {
    s.push_back(i % 10);
    i /= 10;
  }
  if (s.size() != 9) //set a leading 0 if necessary
    s.push_back(0);
  return s;
}

inline int blank_pos(const State & s) {
  int k = 0;
  for (; k < 9; k++) {
    if (!s[k])
      break;
  }
  return k;
}

inline vector<State> next_moves(const State & s) {
  vector<State> next;
  next.reserve(4);
  int k = blank_pos(s);
  int i = k / 3;
  int j = k % 3;
  State ns;
  if (i > 0) {
    ns = s;
    swap(ns[k], ns[k - 3]);
    next.push_back(ns);
  }
  if (j > 0) {
    ns = s;
    swap(ns[k], ns[k - 1]);
    next.push_back(ns);
  }
  if (i < 2) {
    ns = s;
    swap(ns[k], ns[k + 3]);
    next.push_back(ns);
  }
  if (j < 2) {
    ns = s;
    swap(ns[k], ns[k + 1]);
    next.push_back(ns);
  }
  return next;
}

void init() {
  char a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
  State st(a, a + 9);
  queue<State> q;
  q.push(st);
  g.insert(make_pair(to_int(st), vector<int>()));
  while (!q.empty()) {
    st = q.front();
    q.pop();
    vector<int> & neighbors = g[to_int(st)];
    vector<State> next = next_moves(st);
    for (int i = 0; i < next.size(); i++) {
      int n = to_int(next[i]);
      neighbors.push_back(n);
      if (!g.count(n)) {
        q.push(next[i]);
        g.insert(make_pair(n, vector<int>()));
      }
    }
  }
}

inline char step(int u, int v) {
  int b1 = blank_pos(to_s(u));
  int b2 = blank_pos(to_s(v));
  if (b2 == b1 + 1)
    return 'R';
  if (b2 == b1 - 1)
    return 'L';
  if (b2 == b1 + 3)
    return 'D';
  return 'U';
}

State most_dist(const State & s, string & path) {
  int ss = to_int(s);
  int u = ss;
  map<int, int> pred;
  set<int> visited;
  queue<int> q;
  q.push(u);
  pred[u] = 0;
  visited.insert(u);
  while (!q.empty()) {
    u = q.front();
    q.pop();
    vector<int> & ns = g.at(u);
    for (int i = 0; i < ns.size(); i++) {
      int v = ns[i];
      if (!visited.count(v)) {
        pred[v] = u;
        visited.insert(v);
        q.push(v);
      }
    }
  }
  State d = to_s(u);
  //rebuild path
  int p = pred[u];
  while (p) {
    path.push_back(step(p, u));
    u = p;
    p = pred[p];
  }
  reverse(path.begin(), path.end());
  return d;
}

int main() {
  init();
  int n = 0;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    State s;
    s.reserve(9);
    for (int j = 0; j < 9; j++) {
      int v;
      cin >> v;
      s.push_back(v);
    }
    string path;
    State d = most_dist(s, path);
    cout << "Puzzle #" << i << endl;
    output(d);
    cout << path << endl << endl;
  }
  return 0;
}
