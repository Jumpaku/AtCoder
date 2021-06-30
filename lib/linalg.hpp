/**
 * GEOM
 */

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

namespace linalg {
namespace matrix {

template <class T, size_t R, size_t C> struct SMat {
  vec<T> buffer;
  SMat(SMat<T, R, C> const &) = default;
  SMat(SMat<T, R, C> &&) = default;
  SMat() : buffer(vec<T>(R * C)) {}
  SMat<T, R, C> &operator=(SMat<T, R, C> const &) = default;
  SMat<T, R, C> &operator=(SMat<T, R, C> &&) = default;
  T &operator()(size_t i, size_t j) { return buffer.at(i * C + j); }
  T const &operator()(size_t i, size_t j) const { return buffer.at(i * C + j); }
  SMat<T, C, R> transpose() const {
    SMat<T, C, R> out;
    for (size_t i = 0; i < R; i++)
      for (size_t j = 0; j < C; j++)
        out(j, i) = (*this)(i, j);
    return out;
  }
  size_t rows() const { return R; }
  size_t columns() const { return C; }
};

namespace matrix {
template <size_t D, class T> SMat<T, 1, D> row(vec<T> const &elements) {
  SMat<T, 1, D> out;
  for (size_t i = 0; i < D; i++)
    out(0, i) = (i < elements.size()) ? elements[i] : T(0);
  return out;
}
template <size_t D, class T> SMat<T, D, 1> column(vec<T> const &elements) {
  return row<D, T>(elements).transpose();
}
template <size_t D, class T> SMat<T, D, D> diagonal(vec<T> const &elements) {
  SMat<T, D, D> out;
  for (size_t i = 0; i < D; i++)
    out(i, i) = (i < elements.size()) ? elements[i] : T(0);
  return out;
}
template <size_t D, class T> SMat<T, D, D> identity() {
  return diagonal<D, T>(vec<T>(D, T(1)));
}
template <size_t R, size_t C, class T>
SMat<T, R, C> of(vec<vec<T>> const &elements) {
  SMat<T, R, C> out;
  for (size_t i = 0; i < R; i++)
    for (size_t j = 0; j < C; j++)
      out(i, j) = (i < elements.size() && j < elements[i].size())
                      ? elements[i][j]
                      : T(0);
  return out;
}
} // namespace matrix

template <class T, size_t R, size_t C>
SMat<T, R, C> operator+(SMat<T, R, C> const &m0, SMat<T, R, C> const &m1) {
  SMat<T, R, C> out = m0;
  for (size_t i = 0; i < out.buffer.size(); i++)
    out.buffer[i] += m1.buffer[i];
  return out;
}
template <class T, size_t R, size_t C>
SMat<T, R, C> operator*(T const &a, SMat<T, R, C> const &m) {
  SMat<T, R, C> out = m;
  for (size_t i = 0; i < out.buffer.size(); i++)
    out.buffer[i] *= a;
  return out;
}
template <class T, size_t R, size_t C, size_t C2>
SMat<T, R, C2> operator*(SMat<T, R, C> const &m0, SMat<T, C, C2> const &m1) {
  SMat<T, R, C2> out;
  for (size_t i = 0; i < R; i++)
    for (size_t j = 0; j < C2; j++)
      for (size_t k = 0; k < C; k++)
        out(i, j) += m0(i, k) * m1(k, j);
  return out;
}
template <class T, size_t R, size_t C>
SMat<T, R, C> operator*(SMat<T, R, C> const &m, T const &a) {
  return a * m;
}
template <class T, size_t R, size_t C>
SMat<T, R, C> operator+(SMat<T, R, C> const &m) {
  return m;
}
template <class T, size_t R, size_t C>
SMat<T, R, C> operator-(SMat<T, R, C> const &m) {
  return T(-1) * m;
}
template <class T, size_t R, size_t C>
SMat<T, R, C> operator-(SMat<T, R, C> const &m0, SMat<T, R, C> const &m1) {
  return m0 + -m1;
}
template <class T, size_t R, size_t C>
io::OS &operator<<(io::OS &o, SMat<T, R, C> const &m) {
  using io::operator<<;
  o << "Mat(\n";
  for (size_t i = 0; i < m.rows(); i++) {
    vec<T> mi(m.columns());
    for (size_t j = 0; j < m.columns(); j++)
      mi[j] = m(i, j);
    o << join(mi.begin(), mi.end(), ", ", "  ", ";\n");
  }
  o << ")";
  return o;
}

template <class T> struct DMat {
private:
  size_t rows_;
  size_t columns_;

public:
  vec<T> buffer;
  DMat(DMat<T> const &) = default;
  DMat(DMat<T> &&) = default;
  DMat(size_t const &rows, size_t const &columns)
      : rows_(rows), columns_(columns), buffer(vec<T>(rows * columns)) {}
  DMat<T> &operator=(DMat<T> const &) = default;
  DMat<T> &operator=(DMat<T> &&) = default;
  T &operator()(size_t i, size_t j) { return buffer.at(i * columns() + j); }
  T const &operator()(size_t i, size_t j) const {
    return buffer.at(i * columns() + j);
  }
  DMat<T> transpose() const {
    DMat<T> out(columns, rows);
    for (size_t i = 0; i < rows; i++)
      for (size_t j = 0; j < columns; j++)
        out(j, i) = (*this)(i, j);
    return out;
  }
  size_t rows() const { return rows_; }
  size_t columns() const { return columns_; }
};
namespace matrix {
template <class T>
DMat<T> of(size_t const &rows, size_t const &columns,
           vec<vec<T>> const &elements) {
  DMat<T> out(rows, columns);
  for (size_t i = 0; i < rows; i++)
    for (size_t j = 0; j < columns; j++)
      out(i, j) = (i < elements.size() && j < elements[i].size())
                      ? elements[i][j]
                      : T(0);
  return out;
}
template <class T> DMat<T> row(size_t const &columns, vec<T> const &elements) {
  DMat<T> out(1, columns);
  for (size_t i = 0; i < columns; i++)
    out(0, i) = (i < elements.size()) ? elements[i] : T(0);
  return out;
}
template <class T> DMat<T> column(size_t const &rows, vec<T> const &elements) {
  return row<T>(elements).transpose();
}
template <class T>
DMat<T> diagonal(size_t const &dimension, vec<T> const &elements) {
  DMat<T> out(dimension, dimension);
  for (size_t i = 0; i < dimension; i++)
    out(i, i) = (i < elements.size()) ? elements[i] : T(0);
  return out;
}
template <class T> DMat<T> identity(size_t const &dimension) {
  return diagonal(dimension, vec<T>(dimension, T(1)));
}
} // namespace matrix

template <class T> DMat<T> operator+(DMat<T> const &m0, DMat<T> const &m1) {
  DMat<T> out = m0;
  for (size_t i = 0; i < out.buffer.size(); i++)
    out.buffer[i] += m1.buffer[i];
  return out;
}
template <class T> DMat<T> operator*(T const &a, DMat<T> const &m) {
  DMat<T> out = m;
  for (size_t i = 0; i < out.buffer.size(); i++)
    out.buffer[i] *= a;
  return out;
}
template <class T> DMat<T> operator*(DMat<T> const &m0, DMat<T> const &m1) {
  DMat<T> out(m0.rows(), m1.columns());
  for (size_t i = 0; i < m0.rows(); i++)
    for (size_t j = 0; j < m1.columns(); j++)
      for (size_t k = 0; k < m0.columns(); k++)
        out(i, j) += m0(i, k) * m1(k, j);
  return out;
}
template <class T> DMat<T> operator*(DMat<T> const &m, T const &a) {
  return a * m;
}
template <class T> DMat<T> operator+(DMat<T> const &m) { return m; }
template <class T> DMat<T> operator-(DMat<T> const &m) { return T(-1) * m; }
template <class T> DMat<T> operator-(DMat<T> const &m0, DMat<T> const &m1) {
  return m0 + -m1;
}
template <class T> io::OS &operator<<(io::OS &o, DMat<T> const &m) {
  using io::operator<<;
  o << "Mat(\n";
  for (size_t i = 0; i < m.rows(); i++) {
    vec<T> mi(m.columns());
    for (size_t j = 0; j < m.columns(); j++)
      mi[j] = m(i, j);
    o << join(mi.begin(), mi.end(), ", ", "  ", ";\n");
  }
  o << ")";
  return o;
}

} // namespace matrix
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
  lf dist2(Pt<T> const &p) const { return (*this - p).norm2(); }
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
template <class T> io::OS &operator<<(io::OS &o, Pt<T> const &p) {
  using io::operator<<;
  return o << "Pt(" << p.x << ", " << p.y << ", " << p.z << ")";
}
using Vec_ll = Vec<ll>;
using Vec_lf = Vec<lf>;
using Pt_ll = Pt<ll>;
using Pt_lf = Pt<lf>;

enum class Axis { X, Y, Z };
template <class T> struct Transform;
namespace transform {
template <class T> Transform<T> translate(Vec<T> const &move);
};
template <class T> struct Transform {
  using Mat4 = matrix::SMat<T, 4, 4>;
  using Column4 = matrix::SMat<T, 4, 1>;
  Mat4 m;
  Transform(Mat4 m = Mat4::I()) : m(m) {}
  Transform(Transform<T> const &) = default;
  Transform(Transform<T> &&) = default;
  Transform<T> &operator=(Transform<T> const &) = default;
  Transform<T> &operator=(Transform<T> &&) = default;
  Pt<T> operator()(Pt<T> const &p) const {
    auto result = m * matrix::matrix::column<4, T>({p.x, p.y, p.z, T(1)});
    return Pt<T>(result(0, 0), result(1, 0), result(2, 0));
  };
  Transform<T> andThen(Transform<T> const &succ) const {
    return Transform<T>(succ.m * m);
  }
  Transform<T> at(Pt<T> const &pivot) const {
    auto v = pivot - Pt<T>();
    return transform::translate(-v).andThen(*this).andThen(
        transform::translate(v));
  }
};
namespace transform {
template <class T> Transform<T> identity() { return Transform<T>(); }
template <class T> Transform<T> translate(Vec<T> const &move) {
  return Transform<T>(matrix::matrix::of<4, 4, T>({
      {T(1), T(0), T(0), move.x},
      {T(0), T(1), T(0), move.y},
      {T(0), T(0), T(1), move.z},
      {T(0), T(0), T(0), T(1)},
  }));
}
template <class T>
Transform<T> rotate(Axis const &axis, unsigned const &quarters) {
  auto q = quarters % 4;
  int c = q == 0 ? 1 : q == 2 ? -1 : 0;
  int s = q == 1 ? 1 : q == 3 ? -1 : 0;
  switch (axis) {
  case Axis::X:
    return Transform<T>(matrix::matrix::of<4, 4, T>({
        {T(1), T(0), T(0), T(0)},
        {T(0), T(c), T(-s), T(0)},
        {T(0), T(s), T(c), T(0)},
        {T(0), T(0), T(0), T(1)},
    }));
  case Axis::Y:
    return Transform<T>(matrix::matrix::of<4, 4, T>({
        {T(c), T(0), T(s), T(0)},
        {T(0), T(1), T(0), T(0)},
        {T(-s), T(0), T(c), T(0)},
        {T(0), T(0), T(0), T(1)},
    }));
  case Axis::Z:
    return Transform<T>(matrix::matrix::of<4, 4, T>({
        {T(c), T(-s), T(0), T(0)},
        {T(s), T(c), T(0), T(0)},
        {T(0), T(0), T(1), T(0)},
        {T(0), T(0), T(0), T(1)},
    }));
  default:
    exit(1);
  }
}
template <class T> Transform<T> rotate(Vec<T> const &axis, lf const &radians) {
  auto c = cos(radians);
  auto s = sin(radians);
  auto n = axis / axis.norm2();
  auto x = n.x;
  auto y = n.y;
  auto z = n.z;
  return Transform<T>(matrix::matrix::of<4, 4, T>({
      {
          T(c + x * x * (1 - c)),
          T(x * y * (1 - c) - z * s),
          T(z * x * (1 - c) + y * s),
      },
      {
          T(x * y * (1 - c) + z * s),
          T(c + y * y * (1 - c)),
          T(y * z * (1 - c) - x * s),
      },
      {
          T(z * x * (1 - c) - y * s),
          T(y * z * (1 - c) + x * s),
          T(c + z * z * (1 - c)),
      },
      {T(0), T(0), T(0), T(1)},
  }));
}
template <class T> Transform<T> scale(T const &a) {
  return Transform<T>(matrix::matrix::diagonal<4, T>({a, a, a, T(1)}));
}
} // namespace transform
} // namespace geom
} // namespace linalg

using namespace linalg::matrix;
using namespace linalg::geom;
using linalg::geom::Pt;
using linalg::geom::Vec;

namespace std {
template <> struct hash<linalg::geom::Vec<ll>> {
  size_t operator()(linalg::geom::Vec<ll> const &t) const {
    return std::hash<tuple<ll, ll, ll>>{}(make_tuple(t.x, t.y, t.z));
  }
};
template <> struct hash<linalg::geom::Pt<ll>> {
  size_t operator()(linalg::geom::Pt<ll> const &t) const {
    return std::hash<tuple<ll, ll, ll>>{}(make_tuple(t.x, t.y, t.z));
  }
};
} // namespace std

/* end of GEOM */