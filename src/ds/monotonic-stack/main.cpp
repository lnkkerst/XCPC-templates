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
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &i : a) {
    cin >> i;
  }
  stack<int> s;
  vector<int> ans(n);
  for (int i = n - 1; i >= 0; --i) {
    while (!s.empty() && a[s.top()] <= a[i]) {
      s.pop();
    }
    ans[i] = s.empty() ? -1 : s.top();
    s.push(i);
  }
  for (auto i : ans) {
    cout << i + 1 << ' ';
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
