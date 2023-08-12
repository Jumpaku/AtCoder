/**
 * FRAC
 */
#ifndef JUMPAKU_FRAC_HPP
#define JUMPAKU_FRAC_HPP

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#include "atcoder.hpp"
#endif

namespace frac {
class Frac {
  ll num;
  ll den;

public:
  /**
   * parse [+-]?[0-9]+(\.[0-9]*)?
   */
  static Frac parse(str s) {
    ll sign = s[0] == '-' ? -1 : 1;
    if (s[0] == '-' || s[0] == '+') {
      s = s.substr(1, s.size());
    }
    auto pos_point = s.find('.');
    if (pos_point == str::npos) {
      return Frac(stoll(s)) * Frac(sign);
    }
    str a = s.substr(0, pos_point);
    str b = s.substr(pos_point + 1, s.size());

    return Frac(sign) *
           (Frac(stoll(a)) + Frac(stoll(b), ::pow(ll(10), b.size())));
  }
  ll const &numerator() const { return num; }
  ll const &denominator() const { return den; }
  Frac(ll const n = 0, ll const d = 1) {
    if (n == 0) {
      num = 0;
      den = 1;
      return;
    }
    ll s = ::sign(n) * ::sign(d);
    ll a = ::abs(n);
    ll b = ::abs(d);
    ll g = gcd_Olog(a, b);
    num = s * a / g;
    den = b / g;
  }
  Frac &operator+=(Frac const &other) {
    return *this = Frac(num * other.den + other.num * den, den * other.den);
  }
  Frac &operator-=(Frac const &other) {
    return *this = Frac(num * other.den - other.num * den, den * other.den);
  }
  Frac &operator*=(Frac const &other) {
    return *this = Frac(num * other.num, den * other.den);
  }
  Frac &operator/=(Frac const &other) {
    return *this = Frac(num * other.den, den * other.num);
  }
  Frac operator+() const { return *this; }
  Frac operator-() const { return -1 * *this; }
  Frac inv() const { return Frac(den, num); }
  Frac pow(ll n) const {
    if (n < 0) {
      return pow(-n).inv();
    }
    return Frac(::pow(num, n), ::pow(den, n));
  }
  Frac abs() const { return Frac(::abs(num), den); }
  ll sign() const { return ::sign(num); }
  ll floor() const {
    return sign() >= 0 ? (num / den) : (sign() * abs().ceil());
  }
  ll ceil() const {
    return sign() >= 0 ? ((num + den - 1) / den) : (sign() * abs().floor());
  }
  bool isInteger() const { return den == 1; }
  lf asFloat() const { return lf(num) / lf(den); }
  bool operator==(Frac const &other) const {
    return num * other.den == other.num * den;
  }
  bool operator<(Frac const &other) const {
    return num * other.den < other.num * den;
  }
  bool operator<=(Frac const &other) const {
    return num * other.den <= other.num * den;
  }
  bool operator!=(Frac const &other) const { return !(*this == other); }
  bool operator>=(Frac const &other) const { return !(*this < other); }
  bool operator>(Frac const &other) const { return !(*this <= other); }
  friend Frac operator+(Frac const &a, Frac const &b) { return Frac(a) += b; }
  friend Frac operator-(Frac const &a, Frac const &b) { return Frac(a) -= b; }
  friend Frac operator*(Frac const &a, Frac const &b) { return Frac(a) *= b; }
  friend Frac operator/(Frac const &a, Frac const &b) { return Frac(a) /= b; }
  friend io::OS &operator<<(io::OS &o, Frac const &r) {
    return (o << "Frac(" << r.numerator() << "/" << r.denominator() << ")");
  }
};
} // namespace frac

namespace std {
template <> struct hash<frac::Frac> {
  size_t operator()(Frac const &r) const {
    return hashcode::hash_args(17, r.numerator(), r.denominator());
  }
};
} // namespace std

using Frac = frac::Frac;

#endif
/* end of FRAC */