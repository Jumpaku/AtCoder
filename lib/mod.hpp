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
  template <class T> static constexpr T reduce(T const &v, T const &m) {
    if (0 <= v && v < m)
      return v;
    T u = v % m;
    return (u >= 0) ? u : (m + u);
  }
  template <class T> static T &asign(T &x, int const &v, int const &mod) {
    x.m_v = reduce(v, mod);
    return x;
  }
  template <class T> static T &asign(T &x, int &&v, int const &mod) {
    x.m_v = reduce(std::move(v), mod);
    return x;
  }
  template <class T> static T &pre_incl(T &x, int const &mod) {
    ++x.m_v;
    if (x.m_v == mod)
      x.m_v = 0;
    return x;
  }
  template <class T> static T &pre_decl(T &x, int const &mod) {
    if (x.m_v == 0)
      x.m_v = mod;
    x.m_v--;
    return x;
  }
  template <class T> static T post_incl(T &x, int const &mod) {
    T result = x;
    pre_incl(x, mod);
    return result;
  }
  template <class T> static T post_decl(T &x, int const &mod) {
    T result = x;
    pre_decl(x, mod);
    return result;
  }
  template <class T> static T &plusAsign(T &x, int const &v, int const &mod) {
    x.m_v += v;
    if (x.m_v >= mod)
      x.m_v -= mod;
    return x;
  }
  template <class T> static T &minusAsign(T &x, int const &v, int const &mod) {
    x.m_v -= v;
    if (x.m_v < 0)
      x.m_v += mod;
    return x;
  }
  template <class T> static T const &unaryPlus(T const &x, int const &) {
    return x;
  }
  template <class T> static T unaryMinus(T const &x, int const &mod) {
    return T(mod - x.m_v, mod);
  }
  template <class T> static bool equals(T const &x, T const &y) {
    return x.m_v == y.m_v;
  }
  template <class T> static io::OS &out(io::OS &o, T const &x) {
    return o << x.val() << " (mod " << x.mod() << ")";
  }
};
template <class T, class U, class V>
bool constexpr are_operatable_v = std::conditional_t<
    (std::is_same_v<T, V> && std::is_same_v<U, V>) ||
        (std::is_same_v<T, V> && std::is_convertible_v<U, int>) ||
        (std::is_convertible_v<U, int> && std::is_same_v<U, V>),
    std::true_type, std::true_type>::value;

template <int M, std::enable_if_t<(M > 0)> * = nullptr> struct static_llm {
  using This = static_llm;
  static int constexpr mod() { return M; }
  static This &timesAsign(This &x, int const &rhs, int const &mod) {
    unsigned long long int &&prod = static_cast<unsigned long long int>(x.m_v) *
                                    static_cast<unsigned long long int>(rhs);
    x.m_v = static_cast<int>(
        mod_helper::reduce(prod, static_cast<unsigned long long int>(mod)));
    return x;
  }
  static_llm(int const &v = 0) : m_v(mod_helper::reduce(v, mod())) {}
  static_llm(This const &v) = default;
  static_llm(This &&v) = default;
  This &operator=(This const &v) = default;
  This &operator=(This &&v) = default;
  This &operator=(int const &v) { return mod_helper::asign(*this, v, mod()); }
  This &operator=(int &&v) {
    return mod_helper::asign(*this, std::move(v), mod());
  }
  explicit operator int() const { return m_v; }
  friend class mod_helper;
  This &operator++() { return mod_helper::pre_incl(*this, mod()); }
  This &operator--() { return mod_helper::pre_decl(*this, mod()); }
  This operator++(int) { return mod_helper::post_incl(*this, mod()); }
  This operator--(int) { return mod_helper::post_decl(*this, mod()); }
  This &operator+=(const This &rhs) {
    return mod_helper::plusAsign(*this, rhs.m_v, mod());
  }
  This &operator-=(const This &rhs) {
    return mod_helper::minusAsign(*this, rhs.m_v, mod());
  }
  This &operator*=(const This &rhs) {
    return timesAsign(*this, rhs.m_v, mod());
  }
  This &operator+=(const int &rhs) {
    return mod_helper::plusAsign(*this, mod_helper::reduce(rhs, mod()), mod());
  }
  This &operator-=(const int &rhs) {
    return mod_helper::minusAsign(*this, mod_helper::reduce(rhs, mod()), mod());
  }
  This &operator*=(const int &rhs) {
    return timesAsign(*this, mod_helper::reduce(rhs, mod()), mod());
  }
  This operator+() const { return mod_helper::unaryPlus(*this, mod()); }
  This operator-() const { return mod_helper::unaryMinus(*this, mod()); }
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
    return mod_helper::equals(This(lhs), This(rhs));
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
  int m_v;
};

struct dynamic_llm {
  using This = dynamic_llm;
  static void require_positive_mod(int const &x) {
    if (x <= 0)
      throw std::invalid_argument("mod must be positive");
  }
  static void require_same_mod(This const &x, This const &y) {
    require_same_mod(x.mod(), y.mod());
  }
  static void require_same_mod(int const &xMod, int const &yMod) {
    if (xMod != yMod)
      throw std::logic_error("mod minmatch!");
  }
  static unsigned long long int barrett(int const &m) {
    return ((unsigned long long int)(-1)) / m + 1;
  }
  explicit dynamic_llm(int const &m, int const &v)
      : m_v(mod_helper::reduce(v, m)), m_m(m), m_im(barrett(m)) {
    require_positive_mod(m);
  }
  dynamic_llm(This const &v) = default;
  dynamic_llm(This &&v) = default;
  This &operator=(This const &v) = default;
  This &operator=(This &&v) = default;
  This &operator=(int const &v) { return mod_helper::asign(*this, v, mod()); }
  This &operator=(int &&v) {
    return mod_helper::asign(*this, std::move(v), mod());
  }
  explicit operator int() const { return m_v; }
  friend class mod_helper;
  This &operator++() { return mod_helper::pre_incl(*this, mod()); }
  This &operator--() { return mod_helper::pre_decl(*this, mod()); }
  This operator++(int) { return mod_helper::post_incl(*this, mod()); }
  This operator--(int) { return mod_helper::post_decl(*this, mod()); }

  This &operator+=(const This &rhs) {
    require_same_mod(*this, rhs);
    return mod_helper::plusAsign(*this, rhs.m_v, mod());
  }
  This &operator-=(const This &rhs) {
    require_same_mod(*this, rhs);
    return mod_helper::minusAsign(*this, rhs.m_v, mod());
  }
  This &operator*=(const This &rhs) {
    require_same_mod(*this, rhs);
    unsigned long long int z = m_v;
    z *= rhs.m_v;
    unsigned long long int x =
        (unsigned long long int)(((unsigned __int128)(z)*m_im) >> 64);
    unsigned int v = (unsigned int)(z - x * m_m);
    if ((unsigned int)(m_m) <= v)
      v += m_m;
    m_v = v;
    return *this;
  }
  This const &operator+() const { return mod_helper::unaryPlus(*this, mod()); }
  This operator-() const { return mod_helper::unaryMinus(*this, mod()); }

  friend This operator+(const This &lhs, const This &rhs) {
    return This(lhs) += rhs;
  }
  friend This operator-(const This &lhs, const This &rhs) {
    return This(lhs) -= rhs;
  }
  friend This operator*(const This &lhs, const This &rhs) {
    return This(lhs) *= rhs;
  }
  friend bool operator==(const This &lhs, const This &rhs) {
    require_same_mod(lhs, rhs);
    return mod_helper::equals(lhs, rhs);
  }
  friend bool operator!=(const This &lhs, const This &rhs) {
    require_same_mod(lhs, rhs);
    return !(lhs.m_v == rhs.m_v);
  }
  friend io::OS &operator<<(io::OS &o, const This &x) {
    return mod_helper::out(o, x);
  }

  This pow(ll n) const {
    This y = *this, r = This(mod(), 1);
    dump(y, r);
    while (n) {
      if (n & 1)
        r *= y;
      y *= y;
      n >>= 1;
    }
    return r;
  }
  int val() const { return m_v; }
  int const &mod() const { return m_m; }
  This &with_mod(int const &m) {
    require_positive_mod(m);
    m_m = m;
    m_im = barrett(m);
    return *this;
  }

private:
  int m_v;
  int m_m;
  unsigned long long m_im;
};

// template <int P, std::enable_if_t<is_prime_v<P>, std::nullptr_t> = nullptr>
// constexpr Int inv(int const &a) {
//  return pow_mod_constexpr(a, P - 2, P);
//}
template <int P, std::enable_if_t<is_prime_v<P>, std::nullptr_t> = nullptr>
static_llm<P> inv(static_llm<P> const &a) {
  return a.pow(P - 2);
}
dynamic_llm inv(dynamic_llm const &a) {
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
template <int M> std::pair<int, static_llm<M>> gcd_inv(static_llm<M> const &a) {
  auto &&[gcd, inv] = gcd_inv(a.val(), a.val());
  return {gcd, static_llm<M>(inv)};
}
std::pair<int, dynamic_llm> gcd_inv(dynamic_llm const &a) {
  auto &&[gcd, inv] = gcd_inv(a.val(), a.val());
  return {gcd, dynamic_llm(inv, a.mod())};
}
} // namespace mod

template <int M> struct std::hash<mod::static_llm<M>> {
  size_t operator()(mod::static_llm<M> const &t) const { return t.val(); }
};
template <> struct std::hash<mod::dynamic_llm> {
  size_t operator()(mod::dynamic_llm const &t) const {
    return ((t.mod() << 10) - t.mod()) | t.val();
  }
};
using mod::dynamic_llm;
using mod::gcd_inv;
using mod::inv;
using mod::ModCache;
using mod::pow;
using mod::static_llm;
#endif
/* end of MOD */