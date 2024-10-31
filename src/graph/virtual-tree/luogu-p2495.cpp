#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <deque>
#include <format>
#include <functional>
#include <iomanip>
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
void solve() {
  int n;
  cin >> n;
  vector<vector<pair<int, int>>> e(n + 1);
  for (int i = 1; i <= n - 1; ++i) {
    int u, v, w;
    cin >> u >> v >> w;
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }
  int cdfn = 0;
  vector<int> dfn(n + 1);
  vector<vector<int>> fa(n + 1, vector<int>(23));
  auto fad = fa;
  vector<int> dep(n + 1);
  function<void(int, int, int)> dfs_init = [&](int u, int pre, int w) {
    // 记录 dfs 序
    dfn[u] = ++cdfn;
    // 记录倍增父节点
    fa[u][0] = pre;
    // 记录到倍增父节点的边的最小值
    fad[u][0] = w;
    // 记录深度
    dep[u] = dep[pre] + 1;
    // 倍增处理
    for (int i = 1; i <= 20; ++i) {
      fa[u][i] = fa[fa[u][i - 1]][i - 1];
      fad[u][i] = min(fad[u][i - 1], fad[fa[u][i - 1]][i - 1]);
    }
    for (auto [v, w] : e[u]) {
      if (v == pre) {
        continue;
      }
      dfs_init(v, u, w);
    }
  };
  dfs_init(1, 0, 0);
  // 求 LCA
  auto lca = [&](int u, int v) {
    if (dep[u] > dep[v]) {
      swap(u, v);
    }
    int k = dep[v] - dep[u];
    for (int j = 0; k; ++j, k >>= 1) {
      if (k & 1) {
        v = fa[v][j];
      }
    }
    if (v == u) {
      return u;
    }
    for (int j = 20; j >= 0 && v != u; --j) {
      if (fa[u][j] != fa[v][j]) {
        u = fa[u][j];
        v = fa[v][j];
      }
    }
    return fa[u][0];
  };
  // 获取从节点 u 到他的第 k 级祖先路径上权值最小的边
  auto get_fad = [&](int u, int k) {
    int ans = 1e9;
    for (int i = 0; k; ++i, k >>= 1) {
      if (k & 1) {
        ans = min(ans, fad[u][i]);
        u = fa[u][i];
      }
    }
    return ans;
  };
  // 获取从 u 到 v 路径上权值最小的边
  auto get_dis = [&](int u, int v) {
    int lc = lca(u, v);
    return min(get_fad(u, dep[u] - dep[lc]), get_fad(v, dep[v] - dep[lc]));
  };
  int q;
  cin >> q;
  while (q--) {
    int k;
    cin >> k;
    vector<int> h(k + 1);
    // 把根节点插进去，便于后续处理
    h[0] = 1;
    for (int i = 1; i <= k; ++i) {
      cin >> h[i];
    }
    // 第一次按 dfs 序排序
    sort(h.begin() + 1, h.begin() + k + 1, [&](int a, int b) {
      return dfn[a] < dfn[b];
    });
    vector<int> a = {0};
    // 求 dfs 序相邻的节点的 lca，加入虚树点集中
    for (int i = 0; i < k; ++i) {
      a.emplace_back(h[i]);
      a.emplace_back(lca(h[i], h[i + 1]));
    }
    a.emplace_back(h[k]);
    // 第二次按 dfs 序排序
    sort(a.begin() + 1, a.end(), [&](int a, int b) {
      return dfn[a] < dfn[b];
    });
    // 去重
    a.erase(unique(a.begin() + 1, a.end()), a.end());
    int m = a.size() - 1;
    vector<vector<pair<int, int>>> ce(m + 1);
    // 重新分配 id，防止后面数组开大了复杂度退化
    map<int, int> id;
    int cid = 1;
    // 保证根节点还在 1 号
    id[1] = cid;
    auto get_id = [&](int u) {
      if (id.find(u) != id.end()) {
        return id[u];
      }
      return id[u] = ++cid;
    };
    // 虚树连边
    for (int i = 1; i < m; ++i) {
      int u = lca(a[i], a[i + 1]);
      int v = a[i + 1];
      ce[get_id(u)].emplace_back(get_id(v), get_dis(u, v));
      ce[get_id(v)].emplace_back(get_id(u), get_dis(v, u));
    }
    // 标记关键点
    vector<int> b(m + 1);
    for (int i = 1; i <= k; ++i) {
      b[get_id(h[i])] = 1;
    }
    // 问题求解的 DP
    vector<int> dp(m + 1);
    function<void(int, int)> dfs = [&](int u, int pre) {
      for (auto [v, w] : ce[u]) {
        if (v == pre) {
          continue;
        }
        dfs(v, u);
        if (!b[v]) {
          dp[u] += min(dp[v], w);
        } else {
          dp[u] += w;
        }
      }
    };
    dfs(1, 0);
    cout << dp[1] << endl;
  }
}
// ANCHOR_END: default

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  // cin >> t;
  while (t--) {
    solve();
  }
}
