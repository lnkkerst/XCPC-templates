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

struct Splay {
  vector<int> fa, ls, rs, sz, rev;
  int rt;

  Splay(int _n) { fa = ls = rs = sz = rev = vector<int>(_n + 10); }

  void pushup(int u) { sz[u] = sz[ls[u]] + sz[rs[u]] + 1; }

  void pushdown(int u) {
    if (rev[u]) {
      swap(ls[u], rs[u]);
      rev[ls[u]] ^= 1;
      rev[rs[u]] ^= 1;
      rev[u] = 0;
    }
  }

  void rotate(int u, int &v) {
    int y = fa[u], z = fa[y];
    int ca = ls[y] == u ? 1 : 0;
    if (y == v) {
      v = u;
    } else {
      if (ls[z] == y) {
        ls[z] = u;
      } else {
        rs[z] = u;
      }
    }
    if (ca == 0) {
      rs[y] = ls[u];
      fa[rs[y]] = y;
      ls[u] = y;
      fa[y] = u;
      fa[u] = z;
    } else {
      ls[y] = rs[u];
      fa[ls[y]] = y;
      rs[u] = y;
      fa[y] = u;
      fa[u] = z;
    }
    pushup(u);
    pushup(y);
  }

  void splay(int u, int &v) {
    while (u != v) {
      int y = fa[u], z = fa[y];
      if (y != v) {
        if ((ls[y] == u) ^ (ls[z] == y)) {
          rotate(u, v);
        } else {

          rotate(y, v);
        }
      }
      rotate(u, v);
    }
  }

  void build(int l, int r, int u) {
    if (l > r) {
      return;
    }
    int mid = (l + r) / 2;
    if (mid < u) {
      ls[u] = mid;
    } else {
      rs[u] = mid;
    }
    fa[mid] = u;
    sz[mid] = 1;
    if (l == r) {
      return;
    }
    build(l, mid - 1, mid);
    build(mid + 1, r, mid);
    pushup(mid);
  }

  auto build(int l, int r) { return build(l, r, rt); }

  int query(int u, int x) {
    pushdown(u);
    int s = sz[ls[u]];
    if (x == s + 1) {
      return u;
    }
    if (x <= s) {
      return query(ls[u], x);
    } else {
      return query(rs[u], x - s - 1);
    }
  }

  auto query(int x) { return query(rt, x); }

  void reverse(int l, int r) {
    int x = query(rt, l), y = query(rt, r + 2);
    splay(x, rt);
    splay(y, rs[x]);
    int z = ls[y];
    rev[z] ^= 1;
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  Splay tr(n);
  tr.rt = (n + 3) / 2;
  tr.build(1, n + 2);
  for (int i = 1; i <= m; ++i) {
    int l, r;
    cin >> l >> r;
    tr.reverse(l, r);
  }
  for (int i = 2; i <= n + 1; ++i) {
    cout << tr.query(i) - 1 << ' ';
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
