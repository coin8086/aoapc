#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Order {
public:
  Order() : start(0), end(0), ps(0) {}
  Order(int s, int e, int n) : start(s), end(e), ps(n) {}
  bool operator <(const Order & ord) const { return start < ord.start; }
  int start;
  int end;
  int ps; //passengers
};

inline int overloaded(int cap, const vector<int> & stat) {
  for (int i = 0; i < stat.size(); i++) {
    if (stat[i] > cap)
      return i;
  }
  return -1;
}

inline int earning(const vector<int> & stat) {
  int s = 0;
  for (int i = 0; i < stat.size(); i++) {
    s += stat[i];
  }
  return s;
}

inline void accept(const Order & order, vector<int> & stat) {
  for (int j = order.start; j < order.end; j++) {
    stat[j] += order.ps;
  }
}

inline void reject(const Order & order, vector<int> & stat) {
  for (int j = order.start; j < order.end; j++) {
    stat[j] -= order.ps;
  }
}

void back_track(int cap, const vector<Order> & orders, vector<int> & stat,
  int & last_rejected, int & max_earning, int & cur_earning)
{
  int i = overloaded(cap, stat);
  if (i == -1) {
    if (cur_earning > max_earning)
      max_earning = cur_earning;
  }
  else {
    vector<int> ns;
    for (int j = last_rejected + 1; j < orders.size(); j++) {
      const Order & order = orders[j];
      if (order.start <= i && order.end > i) {
        ns = stat;
        reject(order, ns);
        int earning = cur_earning - order.ps * (order.end - order.start);
        if (earning > max_earning) { //prune
          back_track(cap, orders, ns, j, max_earning, earning);
        }
      }
    }
  }
}

inline int max_earning(int cap, int stops, const vector<Order> & orders) {
  vector<int> stat(stops); //load of each section
  for (int i = 0; i < orders.size(); i++) {
    accept(orders[i], stat);
  }
  int m = 0;
  int c = earning(stat);
  int last_rejected = -1;
  back_track(cap, orders, stat, last_rejected, m, c);
  return m;
}

int main() {
  int cap, stops, ord;
  vector<Order> orders;
  orders.reserve(22);
  while (cin >> cap >> stops >> ord && cap) {
    orders.clear();
    for (int i = 0; i < ord; i++) {
      int s, e, n;
      cin >> s >> e >> n;
      if (s > e)
        swap(s, e);
      if (s != e)
        orders.push_back(Order(s, e, n));
    }
    sort(orders.begin(), orders.end());
    cout << max_earning(cap, stops, orders) << endl;
  }
  return 0;
}
