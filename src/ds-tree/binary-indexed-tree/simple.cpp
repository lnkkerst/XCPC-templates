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

void solve() {
  int n, m;
  cin >> n >> m;
  // 不知道怎么写下标从 0 开始的 TAT
  vector<int> tr(n + 1);

  // 单点加
  auto add = [&](int pos, int val) {
    while (pos <= n) {
      tr[pos] += val;
      pos += pos & -pos;
    }
  };

  // 查前缀和
  auto query = [&](int pos) {
    int res = 0;
    while (pos > 0) {
      res += tr[pos];
      pos -= pos & -pos;
    }
    return res;
  };

  for (int i = 1; i <= n; ++i) {
    int x;
    cin >> x;
    add(i, x);
  }

  while (m--) {
    int q;
    cin >> q;
    if (q == 1) {
      int pos, x;
      cin >> pos >> x;
      add(pos, x);
    } else if (q == 2) {
      int l, r;
      cin >> l >> r;
      cout << query(r) - query(l - 1) << endl;
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
