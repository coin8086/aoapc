#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<vector<int> > Graph;

//Since the precondition implies that the input graph is a DAG,
//we don't detect circle in dfs.
void dfs(const Graph & g, int u, vector<bool> & visited, vector<int> & r) {
  for (int i = 0; i < g[u].size(); i++) {
    int v = g[u][i];
    if (!visited[v]) {
      visited[v] = true;
      dfs(g, v, visited, r);
    }
  }
  r.push_back(u);
}

vector<int> topo_sort(const Graph & g) {
  vector<int> r;
  r.reserve(g.size());
  vector<bool> visited(g.size());
  for (int i = 1; i < g.size(); i++) {
    if (!visited[i]) {
      visited[i] = true;
      dfs(g, i, visited, r);
    }
  }
  reverse(r.begin(), r.end());
  return r;
}

int main() {
  int n, m;
  while (cin >> n >> m && n) {
    Graph g(n + 1);
    int i;
    for (i = 0; i < m; i++) {
      int u, v;
      cin >> u >> v;
      g[u].push_back(v);
    }
    vector<int> r = topo_sort(g);
    for (i = 0; i < r.size(); i++) {
      if (i)
        cout << ' ';
      cout << r[i];
    }
    cout << endl;
  }
  return 0;
}
