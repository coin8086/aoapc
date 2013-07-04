#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class Node {
public:
  Node(int v) : value(v), left(0), right(0) {}

  int value;
  Node * left;
  Node * right;
};

Node * build_tree(const int * in, const int * post, int len) {
  if (!len)
    return 0;
  int v = post[len - 1];
  int i;
  for (i = 0; i < len; i++) {
    if (in[i] == v)
      break;
  }
  int len_left = i;
  int len_right = len - len_left - 1;
  Node * n = new Node(v);
  n->left = build_tree(in, post, len_left);
  n->right = build_tree(in + len_left + 1, post + len_left, len_right);
  return n;
}

inline void del_tree(Node * root) {
  if (root->left)
    del_tree(root->left);
  if (root->right)
    del_tree(root->right);
  delete root;
}

void back_track(Node * node, int sum, int & min, int & value) {
  int s = sum + node->value;
  if (!node->left && !node->right) {
    if (s < min) {
      min = s;
      value = node->value;
    }
    else if (s == min && value > node->value) {
      value = node->value;
    }
  }
  else {
    if (node->left)
      back_track(node->left, s, min, value);
    if (node->right)
      back_track(node->right, s, min, value);
  }
}

inline int leaf_on_min_path(const vector<int> & in, vector<int> & post) {
  Node * root = build_tree(&in[0], &post[0], in.size());
  int min = INT_MAX;
  int v;
  back_track(root, 0, min, v);
  del_tree(root);
  return v;
}

inline vector<int> str_to_ints(const string & str) {
  vector<int> r;
  r.reserve(10000);
  istringstream is(str);
  int v;
  while (is >> v) {
    r.push_back(v);
  }
  return r;
}

int main() {
  string line1, line2;
  while (getline(cin, line1) && getline(cin, line2)) {
    vector<int> inorder = str_to_ints(line1);
    vector<int> postorder = str_to_ints(line2);
    cout << leaf_on_min_path(inorder, postorder) << endl;
  }
  return 0;
}
