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
  vector<vector<int>> t1, t2, t3, t4;
  int n, m;

  static int lowbit(int x) {
    return x & -x;
  }

  // 单点加
  void add(int x, int y, int v) {
    for (int i = x; i <= n; i += lowbit(i)) {
      for (int j = y; j <= m; j += lowbit(j)) {
        t1[i][j] += v;
        t2[i][j] += v * x;
        t3[i][j] += v * y;
        t4[i][j] += v * x * y;
      }
    }
  }

  // 查询前缀和
  int query(int x, int y) {
    int res = 0;
    for (int i = x; i > 0; i -= lowbit(i)) {
      for (int j = y; j > 0; j -= lowbit(j)) {
        res += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j]
               - (x + 1) * t3[i][j] + t4[i][j];
      }
    }
    return res;
  }

public:
  Tree(int _n, int _m): n(_n), m(_m) {
    t1 = t2 = t3 = t4 = vector<vector<int>>(_n + 2, vector<int>(_m + 2));
  }

  // 子矩阵加
  void addRange(int x1, int y1, int x2, int y2, int v) {
    add(x1, y1, v);
    add(x1, y2 + 1, -v);
    add(x2 + 1, y1, -v);
    add(x2 + 1, y2 + 1, v);
  }

  // 子矩阵查询
  int queryRange(int x1, int y1, int x2, int y2) {
    return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2)
           + query(x1 - 1, y1 - 1);
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  Tree tree(n, m);

  int op;
  while (cin >> op) {

    if (op == 1) {
      int x1, y1, x2, y2, k;
      cin >> x1 >> y1 >> x2 >> y2 >> k;
      tree.addRange(x1, y1, x2, y2, k);
    } else if (op == 2) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      cout << tree.queryRange(x1, y1, x2, y2) << endl;
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
