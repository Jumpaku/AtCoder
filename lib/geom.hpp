/**
 * GEOM
 */
#ifndef JUMPAKU_GEOM_HPP
#define JUMPAKU_GEOM_HPP

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#endif

namespace geom {

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
  lf norm2() const { return sqrt(sq()); }
  T norm1() const { return abs(x) + abs(y) + abs(z); }
  Vec<T> cross(Vec<T> const &v) const {
    return Vec(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
  }
  lf angle(Vec<T> const &v) const {
    auto const &u = *this;
    return acos(clamp(u.dot(v) / (u.norm2() * v.norm2()), lf(-1.0), lf(1.0)));
  }
  bool parallel(Vec<T> const &v, T const &tolerance = T(0)) const {
    return cross(v).norm2() <= tolerance;
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
  Vec<T> &operator/=(lf const &a) { return *this = *this / a; }
};
template <class T> Vec<T> operator*(T const &a, Vec<T> const &v) {
  return v * a;
}
template <class T> Vec<T> operator/(Vec<T> const &v, lf const &a) {
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
template <class T> io::OS &operator<<(io::OS &o, Vec<T> const &v) {
  using io::operator<<;
  return o << "Vec(" << v.x << ", " << v.y << ", " << v.z << ")";
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
  // (1 - t) * vec() + t * p.vec()
  Pt<T> lerp(T const &t, Pt<T> const &p) const {
    return Pt((1 - t) * vec() + t * p.vec());
  }
  Pt<T> affineCombination(std::vector<std::pair<T, Pt<T>>> const &pairs) const {
    auto c = *this;
    for (auto &&[t, p] : pairs) {
      c += t * (p - *this);
    }
    return c;
  }
  Pt<T> &operator=(Pt<T> const &v) = default;
  Pt<T> &operator=(Pt<T> &&v) = default;
  Pt<T> operator+(Vec<T> const &v) const { return Pt(vec() + v); }
  Vec<T> operator-(Pt<T> const &p) const { return vec() - p.vec(); }
  Pt<T> &operator+=(Vec<T> const &v) { return *this = *this + v; }
  Pt<T> &operator-=(Vec<T> const &v) { return *this += -v; }
  T dist1(Pt<T> const &p) const { return (*this - p).norm1(); }
  lf dist2(Pt<T> const &p) const { return (*this - p).norm2(); }
  T distSq(Pt<T> const &p) const { return (*this - p).sq(); }
  // https://manabitimes.jp/math/933
  Pt<T> project(Pt<T> const &p, Pt<T> const &q) const {
    return p.lerp((q - p).dot(*this - p) / p.distSq(q), q);
  }
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
template <class T> io::OS &operator<<(io::OS &o, Pt<T> const &p) {
  using io::operator<<;
  return o << "Pt(" << p.x << ", " << p.y << ", " << p.z << ")";
}
} // namespace geom

namespace std {
template <> struct hash<geom::Vec<ll>> {
  size_t operator()(geom::Vec<ll> const &t) const {
    return std::hash<tuple<ll, ll, ll>>{}(make_tuple(t.x, t.y, t.z));
  }
};
template <> struct hash<geom::Pt<ll>> {
  size_t operator()(geom::Pt<ll> const &t) const {
    return std::hash<tuple<ll, ll, ll>>{}(make_tuple(t.x, t.y, t.z));
  }
};
} // namespace std

using namespace geom;

#endif
/* end of GEOM */