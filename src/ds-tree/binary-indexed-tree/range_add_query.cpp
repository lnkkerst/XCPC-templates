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

#define int long long

// ANCHOR: default
struct Tree {
private:
  vector<int> t1, t2;
  int n;

  void add_(int k, int v) {
    int v1 = k * v;
    while (k <= n) {
      t1[k] += v, t2[k] += v1;
      k += lowbit(k);
    }
  }

  int query_(vector<int> &t, int k) {
    int res = 0;
    while (k) {
      res += t[k];
      k -= lowbit(k);
    }
    return res;
  }

public:
  Tree(int _n): t1(_n + 2), t2(_n + 2), n(_n) {}

  static int lowbit(int x) {
    return x & -x;
  }

  // 区间加
  void add(int l, int r, int v) {
    add_(l, v);
    add_(r + 1, -v);
  }

  // 求区间和
  int query(int l, int r) {
    return (r + 1) * query_(t1, r) - l * query_(t1, l - 1)
           - (query_(t2, r) - query_(t2, l - 1));
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  Tree tr(n);
  for (int i = 1; i <= n; ++i) {
    int x;
    cin >> x;
    tr.add(i, i, x);
  }
  while (m--) {
    int q;
    cin >> q;
    if (q == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      tr.add(l, r, x);
    } else if (q == 2) {
      int l, r;
      cin >> l >> r;
      cout << tr.query(l, r) << endl;
    }
  }
}
// ANCHOR_END: default

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  while (t--) {
    solve();
  }
}
