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

struct Tree {
  int cnt;
  vector<int> su, ls, rs, a;

  Tree(int n) : cnt(0) {
    n = (n + 1) << 5;
    su = ls = rs = a = vector<int>(n);
  };

  int build(int l, int r) {
    int rt = ++cnt;
    if (l == r) {
      su[rt] = a[l];
      return rt;
    }
    int mid = (l + r) >> 1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid + 1, r);
    return rt;
  }

  int modify(int pre, int l, int r, int x, int u) {
    int rt = ++cnt;
    ls[rt] = ls[pre];
    rs[rt] = rs[pre];
    su[rt] = su[pre];
    if (l == r) {
      su[rt] = x;
      return rt;
    }
    int mid = (l + r) >> 1;
    if (u <= mid) {
      ls[rt] = modify(ls[pre], l, mid, x, u);
    }
    if (u > mid) {
      rs[rt] = modify(rs[pre], mid + 1, r, x, u);
    }
    return rt;
  }

  int query(int rt, int l, int r, int u) {
    if (l == r) {
      return su[rt];
    }
    int mid = (l + r) >> 1;
    if (u <= mid) {
      return query(ls[rt], l, mid, u);
    } else {
      return query(rs[rt], mid + 1, r, u);
    }
  }
};

void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> rt(q + 1);
  Tree tr(n);
  for (int i = 1; i <= n; ++i) {
    cin >> tr.a[i];
  }
  rt[0] = tr.build(1, n);
  for (int i = 1; i <= q; ++i) {
    int pre, op;
    cin >> pre >> op;
    if (op == 1) {
      int pos, x;
      cin >> pos >> x;
      rt[i] = tr.modify(rt[pre], 1, n, x, pos);
    } else if (op == 2) {
      int pos;
      cin >> pos;
      cout << tr.query(rt[pre], 1, n, pos) << endl;
      rt[i] = rt[pre];
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
