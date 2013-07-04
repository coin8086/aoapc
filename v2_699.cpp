#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Node {
public:
  Node(int v) : value(v), left(0), right(0) {}

  int value;
  Node * left;
  Node * right;
};

Node * build_tree(const vector<int> & nodes, int & i) {
  Node * n = 0;
  if (i < nodes.size()) {
    if (nodes[i] == -1) {
      i++;
    }
    else {
      n = new Node(nodes[i]);
      n->left = build_tree(nodes, ++i);
      n->right = build_tree(nodes, i);
    }
  }
  return n;
}

inline void del_tree(Node * root) {
  if (root->left)
    del_tree(root->left);
  if (root->right)
    del_tree(root->right);
  delete root;
}

inline void fall(Node * n, vector<int> & leaves, int idx) {
  leaves[idx] += n->value;
  if (n->left)
    fall(n->left, leaves, idx - 1);
  if (n->right)
    fall(n->right, leaves, idx + 1);
}

vector<int> falling_leaves(const vector<int> & nodes) {
  int i = 0;
  Node * tree = build_tree(nodes, i);
  vector<int> leaves(200);
  fall(tree, leaves, 100);
  del_tree(tree);
  for (i = 0; i < leaves.size(); i++) {
    if (leaves[i])
      break;
  }
  leaves.erase(leaves.begin(), leaves.begin() + i);
  for (i = leaves.size() - 1; i >= 0; i--) {
    if (leaves[i])
      break;
  }
  leaves.erase(leaves.begin() + i + 1, leaves.end());
  return leaves;
}

inline vector<int> str_to_ints(const string & str) {
  vector<int> r;
  r.reserve(1000);
  istringstream is(str);
  int v;
  while (is >> v) {
    r.push_back(v);
  }
  return r;
}

int main() {
  string line;
  int c = 0;
  while (getline(cin, line) && line != "-1") {
    vector<int> nodes = str_to_ints(line);
    vector<int> leaves = falling_leaves(nodes);
    cout << "Case " << ++c << ":" << endl;
    for (int i = 0; i < leaves.size(); i++) {
      if (i)
        cout << ' ';
      cout << leaves[i];
    }
    cout << endl << endl;
  }
  return 0;
}
