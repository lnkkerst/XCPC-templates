#include <iostream>
using ll = long long;

// ANCHOR: default
template <int mod>
struct ModInt {
  int x;

  ModInt(): x(0) {}

  ModInt(int y): x(y >= 0 ? y : y + mod) {}

  ModInt(ll y): x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

  inline int inc(const int &v) {
    return v >= mod ? v - mod : v;
  }

  inline int dec(const int &v) {
    return v < 0 ? v + mod : v;
  }

  inline ModInt &operator+=(const ModInt &p) {
    x = inc(x + p.x);
    return *this;
  }

  inline ModInt &operator-=(const ModInt &p) {
    x = dec(x - p.x);
    return *this;
  }

  inline ModInt &operator*=(const ModInt &p) {
    x = (int)((ll)x * p.x % mod);
    return *this;
  }

  inline ModInt inverse() const {
    int a = x, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b, std::swap(a -= t * b, b), std::swap(u -= t * v, v);
    }
    return u;
  }

  inline ModInt &operator/=(const ModInt &p) {
    *this *= p.inverse();
    return *this;
  }

  inline ModInt operator-() const {
    return -x;
  }

  inline friend ModInt operator+(const ModInt &lhs, const ModInt &rhs) {
    return ModInt(lhs) += rhs;
  }

  inline friend ModInt operator-(const ModInt &lhs, const ModInt &rhs) {
    return ModInt(lhs) -= rhs;
  }

  inline friend ModInt operator*(const ModInt &lhs, const ModInt &rhs) {
    return ModInt(lhs) *= rhs;
  }

  inline friend ModInt operator/(const ModInt &lhs, const ModInt &rhs) {
    return ModInt(lhs) /= rhs;
  }

  inline bool operator==(const ModInt &p) const {
    return x == p.x;
  }

  inline bool operator!=(const ModInt &p) const {
    return x != p.x;
  }

  inline ModInt qpow(ll n) const {
    ModInt ret(1), mul(x);
    while (n > 0) {
      if (n & 1) {
        ret *= mul;
      }
      mul *= mul, n >>= 1;
    }
    return ret;
  }

  inline friend std::ostream &operator<<(std::ostream &os, const ModInt &p) {
    return os << p.x;
  }

  inline friend std::istream &operator>>(std::istream &is, ModInt &a) {
    ll t;
    is >> t, a = ModInt<mod>(t);
    return is;
  }

  static int get_mod() {
    return mod;
  }

  inline bool operator<(const ModInt &A) const {
    return x < A.x;
  }

  inline bool operator>(const ModInt &A) const {
    return x > A.x;
  }
};
// ANCHOR_END: default
