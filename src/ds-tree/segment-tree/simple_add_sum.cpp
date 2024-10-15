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
struct Tree {
#define ls (u << 1)
#define rs (u << 1 | 1)

  int n;
  vector<int> tag, sum;

  Tree(int _n): n(_n), tag((_n + 2) * 4), sum((_n + 2) * 4) {}
  Tree(const vector<int> &a): Tree(a.size()) {
    function<void(int, int, int)> build = [&](int l, int r, int u) {
      if (l == r) {
        sum[u] = a[l - 1];
        return;
      }
      int mid = (r - l) / 2 + l;
      build(l, mid, ls);
      build(mid + 1, r, rs);
      sum[u] = sum[ls] + sum[rs];
    };
    build(1, n, 1);
  }

  void pushdown(int u, int len) {
    tag[ls] += tag[u];
    tag[rs] += tag[u];
    sum[ls] += tag[u] * ((len + 1) >> 1);
    sum[rs] += tag[u] * (len >> 1);
    tag[u] = 0;
  }

  void pushup(int u) {
    sum[u] = sum[ls] + sum[rs];
  }

  void add(int l, int r, int x, int cl, int cr, int u) {
    int len = cr - cl + 1;
    if (cl >= l && cr <= r) {
      tag[u] += x;
      sum[u] += len * x;
      return;
    }
    if (tag[u]) {
      pushdown(u, len);
    }
    int mid = ((cr - cl) >> 1) + cl;
    if (l <= mid) {
      add(l, r, x, cl, mid, ls);
    }
    if (r > mid) {
      add(l, r, x, mid + 1, cr, rs);
    }
    pushup(u);
  }

  int query(int l, int r, int cl, int cr, int u) {
    int len = cr - cl + 1;
    if (cl >= l && cr <= r) {
      return sum[u];
    }
    if (tag[u]) {
      pushdown(u, len);
    }
    int mid = ((cr - cl) >> 1) + cl, res = 0;
    if (l <= mid) {
      res += query(l, r, cl, mid, ls);
    }
    if (r > mid) {
      res += query(l, r, mid + 1, cr, rs);
    }
    return res;
  }

  void add(int l, int r, int x) {
    return add(l, r, x, 1, n, 1);
  }

  int query(int l, int r) {
    return query(l, r, 1, n, 1);
  }

#undef ls
#undef rs
};

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (auto &x : a) {
    cin >> x;
  }
  Tree tree(a);
  while (m--) {
    int op;
    cin >> op;
    if (op == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      tree.add(l, r, x);
    } else if (op == 2) {
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
