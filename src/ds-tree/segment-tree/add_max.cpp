#pragma GCC optimize(2)
#include <algorithm>
#include <array>
#include <bitset>
#include <deque>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

#define int long long

// ANCHOR: default
// 维护最大值
struct Tree {
#define ls (u << 1)
#define rs (u << 1 | 1)

private:
  int n;
  vector<int> tag, ma;

  void pushdown(int u, int len) {
    tag[ls] += tag[u];
    tag[rs] += tag[u];
    ma[ls] += tag[u];
    ma[rs] += tag[u];
    tag[u] = 0;
  }

  void pushup(int u) {
    ma[u] = max(ma[ls], ma[rs]);
  }

  void add(int l, int r, int L, int R, int x, int u) {
    int len = r - l + 1;
    if (l >= L && r <= R) {
      tag[u] += x;
      ma[u] += x;
      return;
    }
    if (tag[u]) {
      pushdown(u, len);
    }
    int mid = ((r - l) >> 1) + l;
    if (L <= mid) {
      add(l, mid, L, R, x, ls);
    }
    if (R > mid) {
      add(mid + 1, r, L, R, x, rs);
    }
    pushup(u);
  }

  int query(int l, int r, int L, int R, int u) {
    int len = r - l + 1;
    if (l >= L && r <= R) {
      return ma[u];
    }
    if (tag[u]) {
      pushdown(u, len);
    }
    // 改成最小值的话别忘了改这里 res = 1e9
    int mid = ((r - l) >> 1) + l, res = 0;
    if (L <= mid) {
      res = max(res, query(l, mid, L, R, ls));
    }
    if (R > mid) {
      res = max(res, query(mid + 1, r, L, R, rs));
    }
    return res;
  }

public:
  Tree(int _n): n(_n), tag((_n + 2) * 4), ma((_n + 2) * 4) {}

  void add(int l, int r, int x) {
    return add(1, n, l, r, x, 1);
  }

  int query(int l, int r) {
    return query(1, n, l, r, 1);
  }

#undef ls
#undef rs
};
// ANCHOR_END: default

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
    int op;
    cin >> op;
    if (op == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      tr.add(l, r, x);
    } else if (op == 2) {
      int l, r;
      cin >> l >> r;
      cout << tr.query(l, r) << endl;
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
