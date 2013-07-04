#include <iostream>
#include <string>
#include <queue>
#include <vector>

using namespace std;

inline int to_int(int i, int j) {
  return i * 8 + j;
}

inline int to_int(const string & pos) {
  return to_int(pos[1] - '1', pos[0] - 'a');
}

inline void valid_move(int i, int j, vector<int> & moves) {
  if (i >= 0 && i < 8 && j >= 0 && j < 8) {
    moves.push_back(to_int(i, j));
  }
}

inline vector<int> valid_moves(int p) {
  static int a[] = {1, -1};
  static int b[] = {2, -2};
  int i = p / 8;
  int j = p % 8;
  vector<int> r;
  r.reserve(8);
  for (int m = 0; m < 2; m++) {
    for (int n = 0; n < 2; n++) {
      valid_move(i + a[m], j + b[n], r);
      valid_move(i + b[m], j + a[n], r);
    }
  }
  return r;
}

int knight_moves(const string & start, const string & end) {
  int s = to_int(start);
  int e = to_int(end);
  if (s == e)
    return 0;
  vector<bool> visited(64);
  vector<int> pred(64, -1);
  queue<int> q;
  q.push(s);
  visited[s] = true;
  bool found = false;
  while (!q.empty() && !found) {
    int p = q.front();
    q.pop();
    vector<int> cands = valid_moves(p);
    for (int i = 0; i < cands.size(); i++) {
      int v = cands[i];
      if (!visited[v]) {
        visited[v] = true;
        pred[v] = p;
        if (v == e) {
          found = true;
          break;
        }
        q.push(v);
      }
    }
  }
  int c = 0;
  int p = pred[e];
  while (p != -1) {
    c++;
    p = pred[p];
  }
  return c;
}

int main() {
  string start, end;
  while (cin >> start >> end) {
    cout << "To get from " << start << " to " << end << " takes "
      << knight_moves(start, end) << " knight moves." << endl;
  }
  return 0;
}
