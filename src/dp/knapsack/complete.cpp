#include <algorithm>
#include <array>
#include <bitset>
#include <cmath>
#include <deque>
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
  int n, m;
  cin >> m >> n;
  vector<int> v(n + 1), w(n + 1);
  vector<int> dp(m + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> w[i] >> v[i];
  }
  for (int i = 1; i <= n; ++i) {
    for (int j = w[i]; j <= m; ++j) {
      dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
    }
  }
  cout << *max_element(dp.begin() + 1, dp.end()) << endl;
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
