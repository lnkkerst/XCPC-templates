#pragma GCC optimize(2)
#include <ext/rope>
#include <iostream>

using namespace std;
using namespace __gnu_cxx;

void solve() {
  rope<int> s, rs;
  int n, m;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i) {
    s.push_back(i);
    rs.push_back(n - i + 1);
  }
  while (m--) {
    int l, r;
    cin >> l >> r;
    int rl = n - r + 1;
    int rr = n - l + 1;
    --l, --r;
    --rl, --rr;
    auto tmp = s.substr(l, r - l + 1);
    auto rtmp = rs.substr(rl, rr - rl + 1);
    s = s.substr(0, l) + rtmp + s.substr(r + 1, n - r);
    rs = rs.substr(0, rl) + tmp + rs.substr(rr + 1, n - rr);
  }
  for (auto i : s) {
    cout << i << ' ';
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
