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
  int n, m, t;
  cin >> n >> m >> t;
  vector<int> w1(n + 1), w2(n + 1);
  for (int i = 1; i <= n; ++i) {
    cin >> w1[i] >> w2[i];
  }
  vector<vector<int>> dp(m + 1, vector<int>(t + 1));
  for (int i = 1; i <= n; ++i) {
    for (int j = m; j >= w1[i]; --j) {
      for (int k = t; k >= w2[i]; --k) {
        dp[j][k] = max(dp[j][k], dp[j - w1[i]][k - w2[i]] + 1);
      }
    }
  }
  cout << dp[m][t] << endl;
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
