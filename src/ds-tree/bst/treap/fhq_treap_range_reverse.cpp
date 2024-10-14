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

// ANCHOR: default
struct Treap {
  vector<int> p, sz, a, tag, ls, rs;
  int tot = 0, rt = 0;

  Treap(int _n) {
    p = sz = a = tag = ls = rs = vector<int>(_n + 2);
  }

  void pushup(int u) {
    sz[u] = sz[ls[u]] + sz[rs[u]] + 1;
  }

  int newNode(int x) {
    a[++tot] = x, sz[tot] = 1, p[tot] = rand();
    return tot;
  }

  void pushdown(int u) {
    swap(ls[u], rs[u]);
    if (ls[u]) {
      tag[ls[u]] ^= 1;
    }
    if (rs[u]) {
      tag[rs[u]] ^= 1;
    }
    tag[u] = 0;
  }

  int merge(int u, int v) {
    if (!u || !v) {
      return u + v;
    }
    if (p[u] < p[v]) {
      if (tag[u]) {
        pushdown(u);
      }
      rs[u] = merge(rs[u], v);
      pushup(u);
      return u;
    }
    if (tag[v]) {
      pushdown(v);
    }
    ls[v] = merge(u, ls[v]);
    pushup(v);
    return v;
  }

  pair<int, int> split(int u, int x) {
    if (!u) {
      return {0, 0};
    }
    if (tag[u]) {
      pushdown(u);
    }
    pair<int, int> res;
    if (sz[ls[u]] < x) {
      auto tmp = split(rs[u], x - sz[ls[u]] - 1);
      rs[u] = tmp.first;
      res = {u, tmp.second};
    } else {
      auto tmp = split(ls[u], x);
      ls[u] = tmp.second;
      res = {tmp.first, u};
    }
    pushup(u);
    return res;
  }

  void dfs(int u) {
    if (!u) {
      return;
    }
    if (tag[u]) {
      pushdown(u);
    }
    dfs(ls[u]);
    cout << a[u] << ' ';
    dfs(rs[u]);
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  Treap tr(n);
  for (int i = 1; i <= n; ++i) {
    tr.rt = tr.merge(tr.rt, tr.newNode(i));
  }
  for (int i = 1; i <= m; ++i) {
    int l, r;
    cin >> l >> r;
    auto t1 = tr.split(tr.rt, l - 1);
    auto t2 = tr.split(t1.second, r - l + 1);
    tr.tag[t2.first] ^= 1;
    tr.rt = tr.merge(t1.first, tr.merge(t2.first, t2.second));
  }
  tr.dfs(tr.rt);
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
