#pragma GCC optimize(2)
#include <algorithm>
#include <array>
#include <bitset>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

struct Tree {
  vector<int> a;
  int n;

  Tree(int _n): a(_n + 2), n(_n) {}

  void add(int pos, int val) {
    while (pos <= n) {
      a[pos] += val;
      pos += pos & -pos;
    }
  }

  int query(int pos) {
    int res = 0;
    while (pos > 0) {
      res += a[pos];
      pos -= pos & -pos;
    }
    return res;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  Tree tr(n);
  for (int last = 0, i = 1; i <= n; ++i) {
    int x;
    cin >> x;
    tr.add(i, x - last);
    last = x;
  }
  while (m--) {
    int q;
    cin >> q;
    if (q == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      tr.add(l, x);
      tr.add(r + 1, -x);
    } else if (q == 2) {
      int pos;
      cin >> pos;
      cout << tr.query(pos) << endl;
    }
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  while (t--) {
    solve();
  }
}
