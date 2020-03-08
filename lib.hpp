#include "template.cpp"
#include <bits/stdc++.h>

/*********************************************************************/
/* GEOM ------------------------------------------------------------ */
/*********************************************************************/
namespace geom {
using OS = std::ostream;
template <class T> struct Vec final {
  T x;
  T y;
  T z;
  Vec(T x = T(), T y = T(), T z = T()) : x(x), y(y), z(z) {}
  Vec(tuple<T> const &t) : Vec(get<0>(t)) {}
  Vec(tuple<T, T> const &t) : Vec(get<0>(t), get<1>(t)) {}
  Vec(tuple<T, T, T> const &t) : Vec(get<0>(t), get<1>(t), get<2>(t)) {}
  Vec(Vec<T> const &v) = default;
  Vec(Vec<T> &&v) = default;
  T dot(Vec<T> const &v) const { return x * v.x + y * v.y + z * v.z; }
  T sq() const { return dot(*this); }
  double norm2() const { return sqrt(sq()); }
  T norm1() const { return x + y + z; }
  Vec<T> cross(Vec<T> const &v) const {
    return Vec(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }
  Vec<T> &operator=(Vec<T> const &v) = default;
  Vec<T> &operator=(Vec<T> &&v) = default;
  Vec<T> operator*(T const &a) const { return Vec<T>(a * x, a * y, a * z); }
  Vec<T> operator+(Vec<T> const &v) const {
    return Vec<T>(x + v.x, y + v.y, z + v.z);
  }
  Vec<T> &operator+=(Vec<T> const &v) { return *this = *this + v; }
  Vec<T> &operator-=(Vec<T> const &v) { return *this += -v; }
  Vec<T> &operator*=(T const &a) { return *this = *this * a; }
  Vec<T> &operator/=(double const &a) { return *this = *this / a; }
};
template <class T> Vec<T> operator*(T const &a, Vec<T> const &v) {
  return v * a;
}
template <class T> Vec<T> operator/(Vec<T> const &v, double const &a) {
  return v * (1 / a);
}
template <class T> Vec<T> operator+(Vec<T> const &v) { return v; }
template <class T> Vec<T> operator-(Vec<T> const &v) { return v * -1; }
template <class T> Vec<T> operator-(Vec<T> const &u, Vec<T> const &v) {
  return u + -v;
}
template <class T> bool operator==(Vec<T> const &u, Vec<T> const &v) {
  return u.x == v.x && u.y == v.y && u.z == v.z;
}
template <class T> bool operator!=(Vec<T> const &u, Vec<T> const &v) {
  return !(u == v);
}
template <class T> OS &operator<<(OS &o, Vec<T> const &v) {
  return o << "Vec(" << v.x << "," << v.y << "," << v.z << ")";
}

template <class T> struct Pt final {
  T x;
  T y;
  T z;
  Pt(T x = T(), T y = T(), T z = T()) : x(x), y(y), z(z) {}
  Pt(tuple<T> const &t) : Pt(get<0>(t)) {}
  Pt(tuple<T, T> const &t) : Pt(get<0>(t), get<1>(t)) {}
  Pt(tuple<T, T, T> const &t) : Pt(get<0>(t), get<1>(t), get<2>(t)) {}
  Pt(Vec<T> const &v) : Pt(v.x, v.y, v.z) {}
  Pt(Pt<T> const &p) = default;
  Pt(Pt<T> &&p) = default;
  Vec<T> vec() const { return Vec<T>(x, y, z); }
  Pt<T> lerp(T const &t, Pt<T> const &p) const {
    return Pt((1 - t) * vec() + t * p.vec());
  }
  Pt<T> &operator=(Pt<T> const &v) = default;
  Pt<T> &operator=(Pt<T> &&v) = default;
  Pt<T> operator+(Vec<T> const &v) const { return Pt(vec() + v); }
  Vec<T> operator-(Pt<T> const &p) const { return vec() - p.vec(); }
  Pt<T> &operator+=(Vec<T> const &v) { return *this = *this + v; }
  Pt<T> &operator-=(Vec<T> const &v) { return *this += -v; }
  T dist1(Pt<T> const &p) const { return (*this - p).norm1(); }
  double dist2(Pt<T> const &p) const { return (*this - p).norm2(); }
  T distSq(Pt<T> const &p) const { return (*this - p).sq(); }
};
template <class T> Pt<T> operator+(Vec<T> const &v, Pt<T> const &p) {
  return p + v;
}
template <class T> Pt<T> operator-(Pt<T> const &p, Vec<T> const &v) {
  return p + -v;
}
template <class T> bool operator==(Pt<T> const &p, Pt<T> const &q) {
  return p.x == q.x && p.y == q.y && p.z == q.z;
}
template <class T> bool operator!=(Pt<T> const &p, Pt<T> const &q) {
  return !(p == q);
}
template <class T> OS &operator<<(OS &o, Pt<T> const &p) {
  return o << "Pt(" << p.x << "," << p.y << "," << p.z << ")";
}
} // namespace geom
using Vec_ll = geom::Vec<long long int>;
using Vec_d = geom::Vec<double>;
using Pt_ll = geom::Vec<long long int>;
using Pt_d = geom::Vec<double>;

/*********************************************************************/
/* MOD ------------------------------------------------------------- */
/*********************************************************************/
namespace mod {
ll pow(ll a, ll n, ll m) {
  if (n == 0)
    return 1;
  if (n & 1)
    return ((a % m) * pow(a, n - 1, m)) % m;
  auto b = pow(a, n / 2, m);
  return (b * b) % m;
}
ll inv(ll a, ll p) { return pow(a, p - 2, p); }
template <ll N, ll M> struct Factrial {
  Factrial() {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i)
      fact[i] = (fact[i - 1] * i) % M;
    finv[N] = inv(fact[N], M);
    for (int i = N; i > 0; --i)
      finv[i - 1] = (finv[i] * i) % M;
  }
  array<ll, N + 1> fact;
  array<ll, N + 1> finv;
  ll comb(ll n, ll m) const {
    if (m < 0 || n < m)
      return 0LL;
    return (fact[n] * ((finv[m] * finv[n - m]) % M)) % M;
  }
};
} // namespace mod
using mod::Factrial;
using mod::inv;
using mod::pow;