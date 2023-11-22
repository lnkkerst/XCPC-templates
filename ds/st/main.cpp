#pragma GCC optimize(2)
#include <algorithm>
#include <array>
#include <cmath>
#include <functional>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

int read() {
  int x = 0, f = 1;
  char ch = 0;
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = x * 10 + (ch - '0');
    ch = getchar();
  }
  return x * f;
}

void write(int x) {
  if (x < 0) {
    x = -x;
    putchar('-');
  }
  if (x > 9) {
    write(x / 10);
  }
  putchar(x % 10 + '0');
}

void solve() {
  int n = read(), m = read();
  vector<int> a(n);
  vector<array<int, 20>> f(n);
  for (int i = 0; i < n; ++i) {
    f[i][0] = a[i] = read();
  }
  // init
  for (int j = 1; j < 20; ++j) {
    for (int i = 0; i < n - (1 << j) + 1; ++i) {
      f[i][j] = max(f[i][j - 1], f[i + (1 << (j - 1))][j - 1]);
    }
  }
  while (m--) {
    int l = read(), r = read();
    --l, --r;
    int l2 = log2(r - l + 1);
    write(max(f[l][l2], f[r - (1 << l2) + 1][l2]));
    putchar('\n');
  }
}

int main() {
  int t;
  t = 1;
  while (t--) {
    solve();
  }
}
