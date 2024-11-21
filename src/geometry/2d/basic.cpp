// https://github.com/hh2048/XCPC
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

constexpr double EPS = 1e-7;

template <typename T>
struct Point {
  T x, y;
  Point(T _x = T(), T _y = T()): x(_x), y(_y) {}
  template <typename U>
  operator Point<U>() {
    return Point<U>(U(x), U(y));
  }
  Point &operator+=(Point p) & {
    return x += p.x, y += p.y, *this;
  }
  Point &operator+=(T t) & {
    return x += t, y += t, *this;
  }
  Point &operator-=(Point p) & {
    return x -= p.x, y -= p.y, *this;
  }
  Point &operator-=(T t) & {
    return x -= t, y -= t, *this;
  }
  Point &operator*=(T t) & {
    return x *= t, y *= t, *this;
  }
  Point &operator/=(T t) & {
    return x /= t, y /= t, *this;
  }
  Point operator-() const {
    return Point(-x, -y);
  }
  friend Point operator+(Point a, Point b) {
    return a += b;
  }
  friend Point operator+(Point a, T b) {
    return a += b;
  }
  friend Point operator-(Point a, Point b) {
    return a -= b;
  }
  friend Point operator-(Point a, T b) {
    return a -= b;
  }
  friend Point operator*(Point a, T b) {
    return a *= b;
  }
  friend Point operator*(T a, Point b) {
    return b *= a;
  }
  friend Point operator/(Point a, T b) {
    return a /= b;
  }
  friend bool operator<(Point a, Point b) {
    return equal(a.x, b.x) ? a.y < b.y - EPS : a.x < b.x - EPS;
  }
  friend bool operator>(Point a, Point b) {
    return b < a;
  }
  friend bool operator==(Point a, Point b) {
    return !(a < b) && !(b < a);
  }
  friend bool operator!=(Point a, Point b) {
    return !(a == b);
  }
  friend auto &operator>>(istream &is, Point &p) {
    return is >> p.x >> p.y;
  }
  friend auto &operator<<(ostream &os, Point p) {
    return os << "(" << p.x << ", " << p.y << ")";
  }
};

template <class T>
struct Line {
  Point<T> a, b;
  Line(Point<T> a_ = Point<T>(), Point<T> b_ = Point<T>()): a(a_), b(b_) {}
  template <class U>
  operator Line<U>() {
    return Line<U>(Point<U>(a), Point<U>(b));
  }
  friend auto &operator<<(ostream &os, Line l) {
    return os << "<" << l.a << ", " << l.b << ">";
  }
};

void solve() {}

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int t = 1;
  cin >> t;
  while (t--) {
    solve();
  }
}
