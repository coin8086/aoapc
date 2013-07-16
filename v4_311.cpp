#include <iostream>
#include <vector>

using namespace std;

//Fill available spaces in twos and ones with available packets
inline void fill(vector<int> & packets, int twos, int ones) {
  if (packets[2] >= twos)
    packets[2] -= twos;
  else {
    ones += (twos - packets[2]) * 4;
    packets[2] = 0;
  }
  if (packets[1] >= ones)
    packets[1] -= ones;
  else
    packets[1] = 0;
}

int min_parcels(vector<int> & packets) {
  int total = packets[6];

  total += packets[5];
  int ones = packets[5] * 11;
  fill(packets, 0, ones);

  total += packets[4];
  int twos = packets[4] * 5;
  fill(packets, twos, 0);

  total += packets[3] / 4;
  int threes = packets[3] % 4;
  if (threes) {
    total++;
    switch (threes) {
      case 3:
        fill(packets, 1, 5);
        break;
      case 2:
        fill(packets, 3, 6);
        break;
      case 1:
        fill(packets, 5, 7);
        break;
    }
  }

  total += packets[2] / 9;
  twos = packets[2] % 9;
  if (twos) {
    total++;
    ones = (9 - twos) * 4;
    fill(packets, 0, ones);
  }

  total += packets[1] / 36;
  if (packets[1] % 36)
    total++;
  return total;
}

int main() {
  while (true) {
    int c = 0;
    vector<int> packets(7);
    for (int i = 1; i < 7; i++) {
      cin >> packets[i];
      if (!packets[i])
        c++;
    }
    if (c == 6)
      break;
    cout << min_parcels(packets) << endl;
  }
  return 0;
}
