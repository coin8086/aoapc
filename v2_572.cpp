#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<char> > Grid;

void dfs(const Grid & g, int i, int j, vector<vector<bool> > & visited) {
  if (g[i][j] != '@' || visited[i][j])
    return;
  visited[i][j] = true;
  dfs(g, i - 1, j - 1, visited); dfs(g, i - 1, j, visited); dfs(g, i - 1, j + 1, visited);
  dfs(g, i, j - 1, visited);                                dfs(g, i, j + 1, visited);
  dfs(g, i + 1, j - 1, visited); dfs(g, i + 1, j, visited); dfs(g, i + 1, j + 1, visited);
}

int deposits(const Grid & g) {
  int c = 0;
  vector<vector<bool> > visited(g.size(), vector<bool>(g[0].size()));
  for (int i = 1; i < g.size() - 1; i++) {
    for (int j = 1; j < g[0].size() - 1; j++) {
      if (g[i][j] == '@' && !visited[i][j]) {
        c++;
        dfs(g, i, j, visited);
      }
    }
  }
  return c;
}

int main() {
  int m, n;
  while (cin >> m >> n && m && n) {
    Grid g;
    g.reserve(m + 2);
    g.push_back(vector<char>(n + 2, '*'));
    for (int i = 0; i < m; i++) {
      vector<char> row;
      row.reserve(n + 2);
      row.push_back('*');
      for (int j = 0; j < n; j++) {
        char ch;
        cin >> ch;
        row.push_back(ch);
      }
      row.push_back('*');
      g.push_back(row);
    }
    g.push_back(vector<char>(n + 2, '*'));
    cout << deposits(g) << endl;
  }
  return 0;
}
