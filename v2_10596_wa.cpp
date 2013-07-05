#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<int> > Graph;

inline void dfs(const Graph & g, int u, vector<bool> & visited) {
  visited[u] = true;
  for (int i = 0; i  < g[u].size(); i++) {
    int v = g[u][i];
    if (!visited[v]) {
      dfs(g, v, visited);
    }
  }
}

inline bool isolated(int u, const vector<int> & out, const vector<int> & in) {
  return !out[u] && !in[u];
}

//Whether all edges are "connected", not all vertices.
inline bool edge_connected(const Graph & g, const vector<int> & out, const vector<int> & in) {
  vector<bool> visited(g.size());
  int i;
  for (i = 0; i < g.size(); i++) {
    if (!isolated(i, out, in))
      break;
  }
  if (i == g.size()) //If no edges at all, we consider it as true
    return true;
  dfs(g, i, visited);
  for (i = 0; i < g.size(); i++) {
    if (!visited[i] && !isolated(i, out, in))
      break;
  }
  return i == g.size();
}

inline bool one_walk(const Graph & g, const vector<int> & out, const vector<int> & in) {
  bool ok = false;
  if (edge_connected(g, out, in)) {
    int i;
    for (i = 0; i < g.size(); i++) {
      if (out[i] != in[i])
        break;
    }
    ok = (i == g.size());
  }
  return ok;
}

int main() {
  int n, r;
  while (cin >> n >> r) {
    Graph g(n);
    vector<int> out(n);
    vector<int> in(n);
    int i;
    for (i = 0; i < r; i++) {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
      out[u]++;
      in[v]++;
    }
    cout << (one_walk(g, out, in) ? "Possible" : "Not Possible") << endl;
  }
  return 0;
}
