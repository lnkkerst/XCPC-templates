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

void solve() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (auto &i : a) {
    cin >> i;
  }
  // [l, r), 升序
  function<void(int, int)> merge_sort = [&](int l, int r) {
    if (r - l <= 1) {
      return;
    }
    int mid = l + ((r - l) >> 1);
    merge_sort(l, mid);
    merge_sort(mid, r);

    // merge
    vector<int> na;
    int i = l, j = mid;
    while (i < mid && j < r) {
      if (a[j] < a[i]) { // 先比较 a[j] < a[i]，可以保证稳定性
        na.emplace_back(a[j]);
        ++j;
      } else {
        na.emplace_back(a[i]);
        ++i;
      }
    }
    while (i < mid) {
      na.emplace_back(a[i]);
      ++i;
    }
    while (j < r) {
      na.emplace_back(a[j]);
      ++j;
    }
    // swap
    for (int i = l; i < r; ++i) {
      a[i] = na[i - l];
    }
  };
  merge_sort(0, a.size());
  for (auto i : a) {
    cout << i << ' ';
  }
  cout << endl;
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
