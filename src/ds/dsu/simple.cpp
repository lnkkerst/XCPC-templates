#pragma GCC optimize(2)
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void solve() {
  int n, m;
  cin >> n >> m;
  vector<int> fa(n + 1);

  // init
  iota(fa.begin(), fa.end(), 0);

  // 找父亲
  function<int(int)> find = [&](int x) {
    return fa[x] == x ? x : fa[x] = find(fa[x]);
  };

  // 合并
  auto merge = [&](int x, int y) { fa[find(x)] = find(y); };

  while (m--) {
    int q, x, y;
    cin >> q >> x >> y;
    if (q == 1) {
      merge(x, y);
    } else {
      cout << ((find(x) == find(y)) ? "Y" : "N") << endl;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  // cin >> t;
  t = 1;
  while (t--) {
    solve();
  }
}
