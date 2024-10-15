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

// ANCHOR: default
struct Fenwick {
  int n;
  vector<int> a;
  Fenwick(int _n): n(_n), a(_n + 10) {}
  Fenwick(const vector<int> &arr) {
    n = arr.size();
    a = vector<int>(n + 10);
    // O(n) 建树
    for (int i = 1; i <= n; ++i) {
      a[i] += arr[i - 1];
      int j = i + lowbit(i);
      if (j <= n) {
        a[j] += a[i];
      }
    }
  }
  static int lowbit(int x) {
    return x & -x;
  }
  // 单点加
  void add(int k, int x) {
    while (k <= n) {
      a[k] += x;
      k += lowbit(k);
    }
  }
  // 查询前缀和
  int query(int k) {
    int res = 0;
    while (k > 0) {
      res += a[k];
      k -= lowbit(k);
    }
    return res;
  }
  // 区间查询
  int query(int l, int r) {
    return query(r) - query(l - 1);
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (auto &x : a) {
    cin >> x;
  }
  Fenwick tree(a);
  while (m--) {
    int q;
    cin >> q;
    if (q == 1) {
      int pos, x;
      cin >> pos >> x;
      tree.add(pos, x);
    } else if (q == 2) {
      int l, r;
      cin >> l >> r;
      cout << tree.query(l, r) << endl;
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
