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

// ANCHOR: default
struct Tree {
  vector<vector<int>> t;
  int n, m;

  Tree(int _n, int _m): n(_n), m(_m), t(_n + 2, vector<int>(_m + 2, 0)) {}

  static int lowbit(int x) {
    return x & -x;
  }

  // 单点加
  void add(int x, int y, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
      for (int j = y; j <= m; j += lowbit(j)) {
        t[i][j] += v;
      }
    }
  }

  // 查询前缀和
  int query(int x, int y) {
    int res = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
      for (int j = y; j > 0; j -= lowbit(j)) {
        res += t[i][j];
      }
    }
    return res;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  Tree tr(n, m);

  // 区间加，维护差分数组时使用
  auto addRange = [&](int x1, int y1, int x2, int y2, int v) {
    tr.add(x1, y1, 1);
    tr.add(x1, y2 + 1, -1);
    tr.add(x2 + 1, y2 + 1, 1);
    tr.add(x2 + 1, y1, -1);
  };

  // 区间查询，维护原数组时使用
  auto queryRange = [&](int x1, int y1, int x2, int y2) {
    return tr.query(x2, y2) - tr.query(x2, y1 - 1) - tr.query(x1 - 1, y2)
           + tr.query(x1 - 1, y1 - 1);
  };

  for (int i = 1; i <= m; ++i) {
    char op;
    cin >> op;
    if (op == 'C') {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      addRange(x1, y1, x2, y2, 1);
    } else if (op == 'Q') {
      int x, y;
      cin >> x >> y;
      cout << tr.query(x, y) % 2 << endl;
    }
  }
}
// ANCHOR_END: default

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
