#pragma GCC optimize(2)
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
template <typename T>
std::vector<T> create_nd_vector(T value, size_t size) {
  return std::vector<T>(size);
}

template <typename T, typename... Sizes>
auto create_nd_vector(T value, size_t first, Sizes... sizes) {
  return std::vector<decltype(create_nd_vector<T>(value, sizes...))>(
    first, create_nd_vector<T>(value, sizes...));
}
// ANCHOR_END: default

void solve() {
  int n;
  cin >> n;
  vector<string> a(n + 1);
  auto b = create_nd_vector<int>(n + 1, n + 1, n + 1, n + 1);
  cout << typeid(b).name() << endl;
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
