#pragma GCC optimize(2)
#include <algorithm>
#include <array>
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <vector>
using namespace std;

void solve() {
  int x;
  priority_queue<int> lq;
  priority_queue<int, vector<int>, greater<int>> rq;
  // 调整对顶堆
  auto adjust = [&](int sz) {
    while (lq.size() < sz && !rq.empty()) {
      lq.push(rq.top());
      rq.pop();
    }
    while (lq.size() > sz) {
      rq.push(lq.top());
      lq.pop();
    }
  };
  // 插入新元素
  auto push = [&](int x) {
    if (lq.empty() || x < lq.top()) {
      lq.push(x);
    } else {
      rq.push(x);
    }
    int mid = (lq.size() + rq.size() + 1) / 2;
    adjust(mid);
  };
  auto pop = [&]() {
    lq.pop();
    int mid = (lq.size() + rq.size() + 1) / 2;
    adjust(mid);
  };
  while (scanf("%d", &x) != EOF) {
    if (x == 0) {
      return;
    }
    if (x == -1) {
      printf("%d\n", lq.top());
      pop();
    } else {
      push(x);
    }
  }
}

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    solve();
  }
}
