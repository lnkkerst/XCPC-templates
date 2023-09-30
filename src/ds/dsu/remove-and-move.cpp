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

#define int long long

void solve() {
  int n, m;
  if (!(cin >> n >> m)) {
    exit(0);
  }
  vector<int> fa((n + 1) * 2), sz((n + 1) * 2, 1);
  vector<int> su((n + 1) * 2); // 添加统计大小

  // 初始化
  iota(fa.begin(), fa.begin() + n + 1, n + 1);
  iota(fa.begin() + n + 1, fa.end(), n + 1);
  iota(su.begin() + n + 1, su.end(), 0);

  // 找父亲
  function<int(int)> find = [&](int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
  };

  // 启发式合并（按大小）
  auto merge = [&](int x, int y) {
    int fx = find(x), fy = find(y);
    if (fx == fy) {
      return;
    }
    if (sz[fx] < sz[fy]) {
      swap(fx, fy);
    }
    fa[fy] = fx;
    sz[fx] += sz[fy];
    su[fx] += su[fy];
  };

  // 删除
  auto remove = [&](int x) {
    --sz[find(x)];
    fa[x] = x;
  };

  // 移动
  auto move = [&](int x, int y) {
    auto fx = find(x), fy = find(y);
    if (fx == fy) {
      return;
    }
    fa[x] = fy;
    --sz[fx], ++sz[fy];
    su[fx] -= x, su[fy] += x;
  };

  while (m--) {
    int q;
    cin >> q;
    if (q == 1) {
      int x, y;
      cin >> x >> y;
      merge(x, y);
    } else if (q == 2) {
      int x, y;
      cin >> x >> y;
      move(x, y);
    } else if (q == 3) {
      int x;
      cin >> x;
      int fx = find(x);
      cout << sz[fx] << ' ' << su[fx] << endl;
    }
  }
}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  while (true) {
    solve();
  }
}
