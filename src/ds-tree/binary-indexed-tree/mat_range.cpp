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
private:
  vector<vector<int>> t1, t2, t3, t4;
  int n, m;

  static int lowbit(int x) { return x & -x; }

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
        res += (x + 1) * (y + 1) * t1[i][j] - (y + 1) * t2[i][j] -
               (x + 1) * t3[i][j] + t4[i][j];
      }
    }
    return res;
  }

public:
  Tree(int _n, int _m) : n(_n), m(_m) {
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
    return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) +
           query(x1 - 1, y1 - 1);
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  Tree tr(n, m);

  for (int i = 1; i <= m; ++i) {
    char op;
    cin >> op;
    if (op == 'C') {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      tr.addRange(x1, y1, x2, y2, 1);
    } else if (op == 'Q') {
      int x, y;
      cin >> x >> y;
      cout << tr.queryRange(x, y, x, y) % 2 << endl;
    }
  }
}

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
