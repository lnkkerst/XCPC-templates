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

// 权值线段树
struct Tree {
#define ls getLs(u)
#define rs getRs(u)

private:
  // n 是最多元素总数，[mi, ma] 是值域
  int n;
  int mi, ma;
  vector<int> a, sum;
  vector<int> lson, rson;
  int cnt = 1;

  int getLs(int u) {
    if (!lson[u]) {
      lson[u] = ++cnt;
    }
    return lson[u];
  }

  int getRs(int u) {
    if (!rson[u]) {
      rson[u] = ++cnt;
    }
    return rson[u];
  }

  void pushdown(int u, int len) {
    a[ls] += a[u];
    a[rs] += a[u];
    sum[ls] += a[u] * ((len + 1) >> 1);
    sum[rs] += a[u] * (len >> 1);
    a[u] = 0;
  }

  void pushup(int u) { sum[u] = sum[ls] + sum[rs]; }

  void add(int l, int r, int L, int R, int x, int u) {
    int len = r - l + 1;
    if (l >= L && r <= R) {
      a[u] += x;
      sum[u] += len * x;
      return;
    }
    if (a[u]) {
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
      return sum[u];
    }
    if (a[u]) {
      pushdown(u, len);
    }
    int mid = ((r - l) >> 1) + l, res = 0;
    if (L <= mid) {
      res += query(l, mid, L, R, ls);
    }
    if (R > mid) {
      res += query(mid + 1, r, L, R, rs);
    }
    return res;
  }

public:
  Tree(int _n, int _mi, int _ma) : n(_n), mi(_mi), ma(_ma) {
    a = sum = lson = rson = vector<int>((_n + 2) * 2);
  }

  void add(int l, int r, int x) { return add(mi, ma, l, r, x, 1); }

  int query(int l, int r) { return query(mi, ma, l, r, 1); }

#undef ls
#undef rs
};

void solve() {
  int n;
  cin >> n;
  int mi = -2e7, ma = 2e7;
  Tree tr(n * 50, mi, ma);

  // 前驱后继操作用 multiset 维护
  multiset<int> b;
  auto rank = [&](int x) {
    int l = mi, r = ma;
    while (l < r) {
      int mid = ((r - l + 1) >> 1) + l;
      int rk = tr.query(mi, mid - 1) + 1;
      if (rk > x) {
        r = mid - 1;
      } else {
        l = mid;
      }
    }
    return *b.lower_bound(l);
  };
  while (n--) {
    int op, x;
    cin >> op >> x;
    if (op == 1) {
      tr.add(x, x, 1);
      b.insert(x);
    } else if (op == 2) {
      tr.add(x, x, -1);
      b.erase(b.find(x));
    } else if (op == 3) {
      cout << tr.query(mi, x - 1) + 1 << endl;
    } else if (op == 4) {
      cout << rank(x) << endl;
    } else if (op == 5) {
      cout << *(--b.lower_bound(x)) << endl;
    } else if (op == 6) {
      cout << *b.lower_bound(x + 1) << endl;
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
