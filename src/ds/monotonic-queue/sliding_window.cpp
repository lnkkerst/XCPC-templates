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

// ANCHOR: default
void solve() {
  int n, k;
  cin >> n >> k;
  vector<int> a(n);
  for (auto &i : a) {
    cin >> i;
  }
  // 滑动窗口最值
  auto calc = [&](function<bool(int, int)> cmp) {
    deque<int> q;
    for (int i = 0; i < k; ++i) {
      while (!q.empty() && cmp(a[i], a[q.back()])) {
        q.pop_back();
      }
      q.push_back(i);
    }
    cout << a[q.front()] << ' ';
    for (int i = k; i < n; ++i) {
      while (!q.empty() && cmp(a[i], a[q.back()])) {
        q.pop_back();
      }
      q.push_back(i);
      while (q.front() <= i - k) {
        q.pop_front();
      }
      cout << a[q.front()] << ' ';
    }
    cout << endl;
  };
  calc(less_equal<>());    // 最小值
  calc(greater_equal<>()); // 最大值
}
// ANCHOR_END: default

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t;
  t = 1;
  while (t--) {
    solve();
  }
}
