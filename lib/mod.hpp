/**
 * MOD
 */
#ifndef JUMPAKU_MOD_HPP
#define JUMPAKU_MOD_HPP

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

namespace mod {
using longlong = long long;

longlong pow(longlong a, longlong n, longlong m) {
  if (n == 0)
    return 1;
  if (n & 1)
    return ((a % m) * pow(a, n - 1, m)) % m;
  auto b = pow(a, n / 2, m);
  return (b * b) % m;
}
longlong inv(longlong a, longlong p) { return pow(a, p - 2, p); }

struct ModCache {
  ModCache(int N, longlong mod) : M(mod), fact(N + 1), finv(N + 1) {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i)
      fact[i] = (fact[i - 1] * i) % M;
    finv[N] = inv(fact[N], M);
    for (int i = N; i > 0; --i)
      finv[i - 1] = (finv[i] * i) % M;
  }
  longlong const M;
  vec<longlong> fact;
  vec<longlong> finv;
  longlong comb(longlong n, longlong m) const {
    if (m < 0 || n < m)
      return 0;
    return (fact[n] * ((finv[m] * finv[n - m]) % M)) % M;
  }
  longlong perm(longlong n, longlong m) const {
    if (m < 0 || n < m)
      return 0;
    return (fact[n] * finv[n - m]) % M;
  }
};

// @param m `1 <= m`
// @return x mod m
constexpr long long safe_mod(long long x, long long m) {
  x %= m;
  if (x < 0)
    x += m;
  return x;
}
// @param n `0 <= n`
// @param m `1 <= m`
// @return `(x ** n) % m`
constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
  if (m == 1)
    return 0;
  unsigned int _m = (unsigned int)(m);
  unsigned long long r = 1;
  unsigned long long y = safe_mod(x, m);
  while (n) {
    if (n & 1)
      r = (r * y) % _m;
    y = (y * y) % _m;
    n >>= 1;
  }
  return r;
}
// Reference:
// M. Forisek and J. Jancina,
// Fast Primality Testing for Integers That Fit into a Machine Word
// @param n `0 <= n`
constexpr bool is_prime_constexpr(int const &n) {
  if (n <= 1)
    return false;
  if (n == 2 || n == 7 || n == 61)
    return true;
  if (n % 2 == 0)
    return false;
  long long d = n - 1;
  while (d % 2 == 0)
    d /= 2;
  for (long long a : {2, 7, 61}) {
    long long t = d;
    long long y = pow_mod_constexpr(a, t, n);
    while (t != n - 1 && y != 1 && y != n - 1) {
      y = y * y % n;
      t <<= 1;
    }
    if (y != n - 1 && t % 2 == 0) {
      return false;
    }
  }
  return true;
}
template <int n> constexpr bool is_prime_v = is_prime_constexpr(n);

struct mod_helper {
  template <class T> static T &pre_inc(T &x) {
    ++x.m_v;
    if (x.m_v == x.umod())
      x.m_v = 0;
    return x;
  }
  template <class T> static T &pre_dec(T &x) {
    if (x.m_v == 0)
      x.m_v = x.umod();
    x.m_v--;
    return x;
  }
  template <class T> static T post_inc(T &x) {
    T result = x;
    pre_inc(x);
    return result;
  }
  template <class T> static T post_dec(T &x) {
    T result = x;
    pre_dec(x);
    return result;
  }
  template <class T> static T &plusAsign(T &x, int const &v) {
    x.m_v += v;
    if (x.m_v >= x.umod())
      x.m_v -= x.umod();
    return x;
  }
  template <class T> static T &minusAsign(T &x, int const &v) {
    x.m_v += x.umod() - v;
    if (x.m_v >= x.umod())
      x.m_v -= x.umod();
    return x;
  }
  template <class T> static T unaryMinus(T const &x) {
    T r = x;
    if (r.m_v == 0)
      return r;
    r.m_v = r.umod() - r.m_v;
    return r;
  }
  template <class T> static io::OS &out(io::OS &o, T const &x) {
    return o << x.val() << "(%" << x.mod() << ")";
  }
  template <class T,
            std::enable_if_t<std::is_integral_v<T>, std::nullptr_t> = nullptr>
  static constexpr T reduce(T const &v, T const &m) {
    if (0 <= v && v < m)
      return v;
    T u = v % m;
    return (u >= 0) ? u : (m + u);
  }
};
template <class T, class U, class V>
bool constexpr are_operatable_v = std::conditional_t<
    (std::is_same_v<T, V> && std::is_same_v<U, V>) ||
        (std::is_same_v<T, V> && std::is_convertible_v<U, int>) ||
        (std::is_convertible_v<U, int> && std::is_same_v<U, V>),
    std::true_type, std::true_type>::value;

template <int M, std::enable_if_t<(M > 0)> * = nullptr> struct static_modint {
  using This = static_modint;
  static int constexpr mod() { return M; }

  static This &timesAsign(This &x, int const &rhs) {
    unsigned long long int &&prod = static_cast<unsigned long long int>(x.m_v) *
                                    static_cast<unsigned long long int>(rhs);
    x.m_v = static_cast<int>(
        mod_helper::reduce(prod, static_cast<unsigned long long int>(x.mod())));
    return x;
  }
  static_modint(int const &v = 0) : m_v(mod_helper::reduce(v, mod())) {}
  static_modint(This const &v) = default;
  static_modint(This &&v) = default;
  This &operator=(This const &v) = default;
  This &operator=(This &&v) = default;
  This &operator=(int const &v) {
    m_v = mod_helper::reduce(v, mod());
    return *this;
  }
  This &operator=(int &&v) {
    m_v = mod_helper::reduce(std::move(v), mod());
    return *this;
  }
  explicit operator int() const { return m_v; }
  friend class mod_helper;
  This &operator++() { return mod_helper::pre_inc(*this); }
  This &operator--() { return mod_helper::pre_dec(*this); }
  This operator++(int) { return mod_helper::post_inc(*this); }
  This operator--(int) { return mod_helper::post_dec(*this); }
  This &operator+=(const This &rhs) {
    return mod_helper::plusAsign(*this, rhs.m_v);
  }
  This &operator-=(const This &rhs) {
    return mod_helper::minusAsign(*this, rhs.m_v);
  }
  This &operator*=(const This &rhs) { return timesAsign(*this, rhs.m_v); }
  This &operator+=(const int &rhs) {
    return mod_helper::plusAsign(*this, mod_helper::reduce(rhs, mod()));
  }
  This &operator-=(const int &rhs) {
    return mod_helper::minusAsign(*this, mod_helper::reduce(rhs, mod()));
  }
  This &operator*=(const int &rhs) {
    return timesAsign(*this, mod_helper::reduce(rhs, mod()));
  }
  This operator+() const { return *this; }
  This operator-() const { return mod_helper::unaryMinus(*this); }
  template <
      class T, class U,
      std::enable_if_t<are_operatable_v<T, U, This>, std::nullptr_t> = nullptr>
  friend This operator+(const T &lhs, const U &rhs) {
    return This(lhs) += rhs;
  }
  template <
      class T, class U,
      std::enable_if_t<are_operatable_v<T, U, This>, std::nullptr_t> = nullptr>
  friend This operator-(const T &lhs, const U &rhs) {
    return This(lhs) -= rhs;
  }
  template <
      class T, class U,
      std::enable_if_t<are_operatable_v<T, U, This>, std::nullptr_t> = nullptr>
  friend This operator*(const T &lhs, const U &rhs) {
    return This(lhs) *= rhs;
  }
  template <
      class T, class U,
      std::enable_if_t<are_operatable_v<T, U, This>, std::nullptr_t> = nullptr>
  friend bool operator==(const T &lhs, const U &rhs) {
    return This(lhs).val() == This(rhs).val();
  }
  template <
      class T, class U,
      std::enable_if_t<are_operatable_v<T, U, This>, std::nullptr_t> = nullptr>
  friend bool operator!=(const T &lhs, const U &rhs) {
    return !(lhs == rhs);
  }
  friend io::OS &operator<<(io::OS &o, const This &x) {
    return mod_helper::out(o, x);
  }
  This pow(ll n) const {
    This y = *this, r = 1;
    while (n) {
      if (n & 1)
        r *= y;
      y *= y;
      n >>= 1;
    }
    return r;
  }
  int val() const { return m_v; }

private:
  static constexpr unsigned int umod() { return (unsigned)M; }
  unsigned int m_v;
};

struct dynamic_modint {
  using This = dynamic_modint;
  static void require_positive_mod(int const &x) {
    if (x <= 0)
      throw std::invalid_argument("mod must be positive");
  }
  static void require_same_mod(This const &x, This const &y) {
    require_same_mod(x.umod(), y.umod());
  }
  static void require_same_mod(int const &xMod, int const &yMod) {
    if (xMod != yMod)
      throw std::logic_error("mod mismatch!");
  }
  static unsigned long long int barrett(int const &m) {
    return ((unsigned long long int)(-1)) / m + 1;
  }
  static This &timesAsign(This &x, int const &rhs) {
    unsigned long long int z = x.m_v;
    z *= x.reduce(rhs);
    x.m_v = x.reduce(z);
    return x;
  }
  dynamic_modint(int const &v, int const &m)
      : m_v(mod_helper::reduce(v, m)), m_m(m), m_im(barrett(m)) {
    require_positive_mod(m_m);
  }
  dynamic_modint(This const &v) = default;
  dynamic_modint(This &&v) = default;
  This &operator=(This const &v) = default;
  This &operator=(This &&v) = default;
  This &operator=(int const &v) {
    m_v = reduce(v);
    return *this;
  }
  This &operator=(int &&v) {
    m_v = reduce(std::move(v));
    return *this;
  }
  explicit operator int() const { return m_v; }
  friend class mod_helper;
  This &operator++() { return mod_helper::pre_inc(*this); }
  This &operator--() { return mod_helper::pre_dec(*this); }
  This operator++(int) { return mod_helper::post_inc(*this); }
  This operator--(int) { return mod_helper::post_dec(*this); }

  This &operator+=(const This &rhs) {
    require_same_mod(*this, rhs);
    return mod_helper::plusAsign(*this, rhs.m_v);
  }
  This &operator+=(const int &rhs) {
    if (rhs < 0)
      return mod_helper::minusAsign(*this, reduce(-rhs));
    return mod_helper::plusAsign(*this, reduce(rhs));
  }
  This &operator-=(const This &rhs) {
    require_same_mod(*this, rhs);
    return mod_helper::minusAsign(*this, rhs.m_v);
  }
  This &operator-=(const int &rhs) {
    if (rhs < 0)
      return mod_helper::plusAsign(*this, reduce(-rhs));
    return mod_helper::minusAsign(*this, reduce(rhs));
  }
  This &operator*=(const This &rhs) {
    require_same_mod(*this, rhs);
    return timesAsign(*this, rhs.m_v);
  }
  This &operator*=(const int &rhs) {
    if (m_v == 0)
      return *this;
    if (rhs < 0) {
      unsigned int x = reduce(-rhs);
      if (x == 0) {
        m_v = 0;
        return *this;
      }
      *this *= x;
      m_v = m_m - m_v;
      return *this;
    }
    return timesAsign(*this, reduce(rhs));
  }
  This const &operator+() const { return *this; }
  This operator-() const { return mod_helper::unaryMinus(*this); }
  template <class U, std::enable_if_t<are_operatable_v<This, U, This>,
                                      std::nullptr_t> = nullptr>
  friend This operator+(const This &lhs, const U &rhs) {
    return This(lhs) += rhs;
  }
  friend This operator+(const int &lhs, const This &rhs) { return rhs + lhs; }
  template <class U, std::enable_if_t<are_operatable_v<This, U, This>,
                                      std::nullptr_t> = nullptr>
  friend This operator-(const This &lhs, const U &rhs) {
    return This(lhs) -= rhs;
  }
  friend This operator-(const int &lhs, const This &rhs) {
    return -(rhs - lhs);
  }
  template <class U, std::enable_if_t<are_operatable_v<This, U, This>,
                                      std::nullptr_t> = nullptr>
  friend This operator*(const This &lhs, const U &rhs) {
    return This(lhs) *= rhs;
  }
  friend This operator*(const int &lhs, const This &rhs) { return rhs * lhs; }
  friend bool operator==(const This &lhs, const This &rhs) {
    require_same_mod(lhs, rhs);
    return lhs.m_v == rhs.m_v;
  }
  friend bool operator==(const This &lhs, const int &rhs) {
    return lhs.m_v == lhs.reduce(rhs);
  }
  friend bool operator==(const int &lhs, const This &rhs) {
    return rhs.reduce(lhs) == rhs.m_v;
  }
  template <
      class T, class U,
      std::enable_if_t<are_operatable_v<T, U, This>, std::nullptr_t> = nullptr>
  friend bool operator!=(const T &lhs, const U &rhs) {
    return !(lhs == rhs);
  }
  friend io::OS &operator<<(io::OS &o, const This &x) {
    return mod_helper::out(o, x);
  }

  This pow(ll n) const {
    This r = *this;
    This y = *this;
    r = 1;
    while (n) {
      if (n & 1)
        r *= y;
      y *= y;
      n >>= 1;
    }
    return r;
  }
  int val() const { return m_v; }
  int mod() const { return m_m; }
  unsigned int umod() const { return m_m; }
  This &with_mod(int const &m) {
    require_positive_mod(m);
    m_m = m;
    m_im = barrett(m);
    return *this;
  }

private:
  unsigned int m_v;
  unsigned int m_m;
  unsigned long long m_im;
  unsigned int reduce(unsigned long long int const &v) const {
    if (v < (unsigned long long int)m_m)
      return v;
    unsigned long long x =
        (unsigned long long)(((unsigned __int128)(v)*m_im) >> 64);
    unsigned int r = (unsigned int)(v - x * m_m);
    if (m_m <= r)
      r += m_m;
    return r;
  }
};

template <int P, std::enable_if_t<is_prime_v<P>, std::nullptr_t> = nullptr>
static_modint<P> inv(static_modint<P> const &a) {
  return a.pow(P - 2);
}
dynamic_modint inv(dynamic_modint const &a) {
  if (!is_prime_constexpr(a.mod()))
    throw std::logic_error("inv with non prime!");
  return a.pow(a.mod() - 2);
}
std::pair<int, int> gcd_inv(int a, int const &mod) {
  a = safe_mod(a, mod);
  if (a == 0)
    return {mod, 0};

  // Contracts:
  // [1] s - m0 * a = 0 (mod b)
  // [2] t - m1 * a = 0 (mod b)
  // [3] s * |m1| + t * |m0| <= b
  long long s = mod, t = a;
  long long m0 = 0, m1 = 1;

  while (t) {
    long long u = s / t;
    s -= t * u;
    m0 -= m1 * u; // |m1 * u| <= |m1| * s <= b

    // [3]:
    // (s - t * u) * |m1| + t * |m0 - m1 * u|
    // <= s * |m1| - t * u * |m1| + t * (|m0| + |m1| * u)
    // = s * |m1| + t * |m0| <= b

    auto tmp = s;
    s = t;
    t = tmp;
    tmp = m0;
    m0 = m1;
    m1 = tmp;
  }
  // by [3]: |m0| <= b/g
  // by g != b: |m0| < b/g
  if (m0 < 0)
    m0 += mod / s;
  return {s, m0};
}
template <class Modint> std::pair<int, Modint> gcd_inv(Modint const &a) {
  Modint r = a;
  auto &&[gcd, inv] = gcd_inv(a.val(), a.mod());
  r = inv;
  return {gcd, r};
}
} // namespace mod

template <int M> struct std::hash<mod::static_modint<M>> {
  size_t operator()(mod::static_modint<M> const &t) const { return t.val(); }
};
template <> struct std::hash<mod::dynamic_modint> {
  size_t operator()(mod::dynamic_modint const &t) const {
    return ((t.mod() << 10) - t.mod()) | t.val();
  }
};
using mod::dynamic_modint;
using mod::gcd_inv;
using mod::inv;
using mod::ModCache;
using mod::pow;
using mod::static_modint;
#endif
/* end of MOD */