#pragma GCC optimize(2)
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

// ANCHOR: default
void solve() {
  int n;
  cin >> n;
  vector<int> a(n + 10);
  int cnt = 0;
  function<void(int)> pushup = [&](int u) {
    if (u == 1) {
      return;
    }
    int fa = u >> 1;
    if (a[u] < a[fa]) {
      swap(a[u], a[fa]);
      pushup(fa);
    }
  };
  function<void(int)> pushdown = [&](int u) {
    int v = u << 1;
    if (v > cnt) {
      return;
    }
    if ((v | 1) <= cnt && a[v | 1] < a[v]) {
      v |= 1;
    }
    if (a[v] < a[u]) {
      swap(a[v], a[u]);
      pushdown(v);
    }
  };
  auto push = [&](int x) {
    a[++cnt] = x;
    pushup(cnt);
  };
  auto pop = [&]() {
    a[1] = a[cnt--];
    pushdown(1);
  };
  for (int i = 1; i <= n; ++i) {
    int q;
    cin >> q;
    if (q == 1) {
      int x;
      cin >> x;
      push(x);
    } else if (q == 2) {
      cout << a[1] << endl;
    } else {
      pop();
    }
  }
}
// ANCHOR_END: default

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    solve();
  }
}
