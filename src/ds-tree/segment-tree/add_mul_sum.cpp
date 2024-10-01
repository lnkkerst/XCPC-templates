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

int mod;

struct Tree {
#define ls (u << 1)
#define rs (u << 1 | 1)

private:
  int n;
  vector<int> sum, mu, tag;

  void pushup(int u) {
    sum[u] = (sum[ls] + sum[rs]) % mod;
  }

  void pushdown(int l, int r, int u) {
    if (mu[u] != 1) {
      mu[ls] = mu[ls] * mu[u] % mod;
      mu[rs] = mu[rs] * mu[u] % mod;
      tag[ls] = tag[ls] * mu[u] % mod;
      tag[rs] = tag[rs] * mu[u] % mod;
      sum[ls] = sum[ls] * mu[u] % mod;
      sum[rs] = sum[rs] * mu[u] % mod;
      mu[u] = 1;
    }
    int mid = ((r - l) >> 1) + l;
    if (tag[u]) {
      sum[ls] = (sum[ls] + tag[u] * (mid - l + 1)) % mod;
      sum[rs] = (sum[rs] + tag[u] * (r - mid)) % mod;
      tag[ls] = (tag[ls] + tag[u]) % mod;
      tag[rs] = (tag[rs] + tag[u]) % mod;
      tag[u] = 0;
    }
  }

  void mul(int l, int r, int L, int R, int x, int u) {
    if (l >= L && r <= R) {
      mu[u] = mu[u] * x % mod;
      tag[u] = tag[u] * x % mod;
      sum[u] = sum[u] * x % mod;
      return;
    }
    if (mu[u] != 1 || tag[u]) {
      pushdown(l, r, u);
    }
    int mid = ((r - l) >> 1) + l;
    if (mid >= L) {
      mul(l, mid, L, R, x, ls);
    }
    if (mid < R) {
      mul(mid + 1, r, L, R, x, rs);
    }
    pushup(u);
  }

  void add(int l, int r, int L, int R, int x, int u) {
    int len = r - l + 1;
    if (l >= L && r <= R) {
      sum[u] = (sum[u] + x * len % mod) % mod;
      tag[u] = (tag[u] + x) % mod;
      return;
    }
    int mid = ((r - l) >> 1) + l;
    pushdown(l, r, u);
    if (mid >= L) {
      add(l, mid, L, R, x, ls);
    }
    if (mid < R) {
      add(mid + 1, r, L, R, x, rs);
    }
    pushup(u);
  }

  int query(int l, int r, int L, int R, int u) {
    if (l >= L && r <= R) {
      return sum[u];
    }
    int mid = ((r - l) >> 1) + l, res = 0;
    pushdown(l, r, u);
    if (mid >= L) {
      res = (res + query(l, mid, L, R, ls)) % mod;
    }
    if (mid < R) {
      res = (res + query(mid + 1, r, L, R, rs)) % mod;
    }
    return res;
  }

  void build(const vector<int> &a, int l, int r, int u) {
    sum[u] = 0, tag[u] = 0, mu[u] = 1;
    if (l == r) {
      sum[u] = a[l];
      return;
    }
    int mid = ((r - l) >> 1) + l;
    build(a, l, mid, ls);
    build(a, mid + 1, r, rs);
    pushup(u);
  }

public:
  Tree(int _n): n(_n) {
    sum = mu = tag = vector<int>((_n + 2) * 4);
  }

  void add(int l, int r, int x) {
    return add(1, n, l, r, x, 1);
  }

  void mul(int l, int r, int x) {
    return mul(1, n, l, r, x, 1);
  }

  int query(int l, int r) {
    return query(1, n, l, r, 1);
  }

  void build(const vector<int> &a) {
    build(a, 1, n, 1);
  }

#undef ls
#undef rs
};

void solve() {
  int n, m;
  cin >> n >> m >> mod;
  Tree tr(n);
  vector<int> a(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> a[i];
  }
  tr.build(a);
  while (m--) {
    int op;
    cin >> op;
    if (op == 1) {
      int l, r, x;
      cin >> l >> r >> x;
      tr.mul(l, r, x);
    } else if (op == 2) {
      int l, r, x;
      cin >> l >> r >> x;
      tr.add(l, r, x);
    } else if (op == 3) {
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
