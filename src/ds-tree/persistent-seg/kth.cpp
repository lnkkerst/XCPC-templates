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
struct Tree {
  int cnt;
  vector<int> su, ls, rs;
  Tree(int n): cnt(0) {
    n = (n + 1) << 5;
    su = ls = rs = vector<int>(n);
  };
  int build(int l, int r) {
    ++cnt;
    su[cnt] = 0;
    int mid = (l + r) >> 1;
    if (l < r) {
      ls[cnt] = build(l, mid), rs[cnt] = build(mid + 1, r);
    }
    return cnt;
  }
  int update(int pre, int l, int r, int x) {
    int rt = ++cnt;
    ls[rt] = ls[pre];
    rs[rt] = rs[pre];
    su[rt] = su[pre] + 1;
    if (l < r) {
      int mid = (l + r) >> 1;
      if (x <= mid) {
        ls[rt] = update(ls[pre], l, mid, x);
      } else {
        rs[rt] = update(rs[pre], mid + 1, r, x);
      }
    }
    return rt;
  }
  int query(int a, int b, int l, int r, int k) {
    if (l >= r) {
      return l;
    }
    int t = su[ls[b]] - su[ls[a]];
    int mid = (l + r) >> 1;
    if (t >= k) {
      return query(ls[a], ls[b], l, mid, k);
    } else {
      return query(rs[a], rs[b], mid + 1, r, k - t);
    }
  }
};

void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> a(n), rt(n + 1);
  Tree tr(n);
  for (auto &i : a) {
    cin >> i;
  }
  auto b = a;
  sort(b.begin(), b.end());
  b.erase(unique(b.begin(), b.end()), b.end());
  rt[0] = tr.build(1, b.size());
  auto getId = [&](int x) {
    return lower_bound(b.begin(), b.end(), x) - b.begin();
  };
  for (int i = 1; i <= n; ++i) {
    rt[i] = tr.update(rt[i - 1], 1, b.size(), getId(a[i - 1]) + 1);
  }
  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    int pos = tr.query(rt[l - 1], rt[r], 1, b.size(), k);
    cout << b[pos - 1] << endl;
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
