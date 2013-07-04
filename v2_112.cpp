#include <iostream>
#include <cctype>

using namespace std;

class Node {
public:
  int value;
  Node * left;
  Node * right;

  Node(int v) : value(v), left(0), right(0) {}

  void cascade_del() {
    if (left)
      left->cascade_del();
    if (right)
      right->cascade_del();
    delete this;
  }

  static Node * unserialize(istream & is) {
    char d;
    while (isspace(d = is.get()));
    if (d != '(') {
      is.setstate(ios_base::failbit);
      return 0;
    }
    while (isspace(d = is.get()));
    if (d == ')') {
      return 0;
    }
    is.unget();
    int v;
    if (!(is >> v)) {
      return 0;
    }
    Node * n = new Node(v);
    n->left = unserialize(is);  //To be strict, "is" needs some check here
    n->right = unserialize(is); //The same with above.
    while (isspace(d = is.get()));
    if (d != ')') {
      is.setstate(ios_base::failbit);
      n->cascade_del();
      return 0;
    }
    return n;
  }
};

class Tree {
friend istream & operator >>(istream & is, Tree & t) {
  t.clear();
  Node * n = Node::unserialize(is);
  t._root = n;
  return is;
}

public:
  Tree() : _root(0) {}

  ~Tree() { clear(); }

  bool empty() const { return !_root; }

  const Node * root() const { return _root; }

  void clear() {
    if (_root) {
      _root->cascade_del();
      _root = 0;
    }
  }

private:
  Node * _root;
};

bool back_track(const Node * n, int c, int s) {
  bool r = false;
  int nc = n->value + c;
  if (!n->left && !n->right) {
    if (nc == s) {
      r = true;
    }
  }
  else {
    if (n->left)
      r = back_track(n->left, nc, s);
    if (!r && n->right)
      r = back_track(n->right, nc, s);
  }
  return r;
}

inline bool has_sum(const Tree & t, int s) {
  if (t.empty())
    return false;
  int c = 0;
  return back_track(t.root(), c, s);
}

int main() {
  int s;
  Tree t;
  while (cin >> s >> t) {
    cout << (has_sum(t, s) ? "yes" : "no") << endl;
  }
  return 0;
}
