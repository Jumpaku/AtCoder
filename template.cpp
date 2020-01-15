//#pragma GCC optimize("O3")
//#pragma GCC target("avx")

#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

// Types
using ll = long long int;
using str = string;
template <class T> using u_set = unordered_set<T>;
template <class K, class V> using u_map = unordered_map<K, V>;
template <class V> using graph = u_map<V, u_set<V>>;
template <class F,
          typename enable_if<is_function<F>::value, nullptr_t>::type = nullptr>
using fun = function<F>;

namespace io {
// Input
using IS = istream;
IS &in(IS &);
IS &in(IS &i) { return i; }
template <class T, class... Ts> IS &in(IS &i, T &a, Ts &... as) {
  return in(i >> a, as...);
}
template <class V> IS &operator>>(IS &i, vector<V> &a) {
  for_each(a.begin(), a.end(), [&i](auto &e) { i >> e; });
  return i;
}
template <class F, class S> IS &operator>>(IS &i, pair<F, S> &p) {
  return in(i, p.first, p.second);
}
template <class... Ts, size_t... I>
IS &tuple_in(IS &i, tuple<Ts...> &t, index_sequence<I...>) {
  return in(i, get<I>(t)...);
}
template <class... Ts> IS &operator>>(IS &i, tuple<Ts...> &t) {
  return tuple_in(i, t, make_index_sequence<sizeof...(Ts)>());
}
// Output
using OS = ostream;
OS &out(OS &o) { return o << endl; }
template <class T> OS &out(OS &o, T const &a) { return o << a << endl; }
template <class T, class... Ts> OS &out(OS &o, T const &a, Ts const &... as) {
  return out(o << a << " ", as...);
}
template <class F, class S> OS &operator<<(OS &o, pair<F, S> const &p) {
  return o << p.first << ":" << p.second;
}
template <class... Ts> OS &args_out(OS &o, Ts const &... ts);
OS &args_out(OS &o) { return o; }
template <class T> OS &args_out(OS &o, T const &t) { return o << t; }
template <class T0, class T1, class... Ts>
OS &args_out(OS &o, T0 const &t0, T1 const &t1, Ts const &... ts) {
  return args_out(o << t0 << ",", t1, ts...);
}
template <class... Ts, size_t... I>
OS &tuple_out(OS &o, tuple<Ts...> const &t, index_sequence<I...>) {
  return args_out(o, get<I>(t)...);
}
template <class... Ts> OS &operator<<(OS &o, tuple<Ts...> const &t) {
  return tuple_out(o << "(", t, make_index_sequence<sizeof...(Ts)>()) << ")";
}
template <
    class C,
    class T = typename iterator_traits<typename C::iterator>::value_type,
    typename enable_if<!is_same<C, str>::value, nullptr_t>::type = nullptr>
OS &operator<<(OS &o, C const &a) {
  return a.empty() ? (o << "[]") : ([&o, &a]() -> OS & {
    o << "[" << *a.begin();
    for_each(next(a.begin()), a.end(), [&o](auto const &e) { o << "," << e; });
    return o << "]";
  }());
}
} // namespace io
auto input = [](auto &... a) { io::in(cin, a...); };
auto print = [](auto const &... a) { io::out(cout, a...); };
#ifdef JUMPAKU_DEBUG
auto dump = [](auto const &... a) { io::out(cerr, a...); };
#else
auto dump = [](auto const &...) {};
#endif

// Hash
namespace hashcode {
template <class... Ts> size_t hash_args(size_t h, Ts const &... ts);
size_t hash_args(size_t h) { return h; }
template <class T, class... Ts>
size_t hash_args(size_t h, T const &t, Ts const &... ts) {
  return hash_args(((h << 10) - h + hash<T>{}(t)), ts...);
}
template <class... Ts, size_t... I>
size_t hash_tuple(tuple<Ts...> const &t, index_sequence<I...>) {
  return hash_args(17, get<I>(t)...);
}
} // namespace hashcode
namespace std {
template <class... Ts> struct hash<tuple<Ts...>> {
  size_t operator()(tuple<Ts...> const &t) const {
    return hashcode::hash_tuple(t, index_sequence_for<Ts...>());
  }
};
} // namespace std

// Range
template <class T> struct seq;
struct range {
  struct itr {
    using difference_type = ll;
    using value_type = ll;
    using pointer = ll *;
    using reference = ll &;
    using iterator_category = random_access_iterator_tag;
    ll val;
    explicit itr(ll const &val = 0) : val(val) {}
    bool operator==(itr const &itr) const { return val == itr.val; }
    bool operator!=(itr const &itr) const { return val != itr.val; }
    itr &operator++() { return *this += 1; }
    itr operator++(int) { return itr(val++); }
    itr &operator--() { return *this -= 1; }
    itr operator--(int) { return itr(val--); }
    itr operator+(ll const &n) const { return itr(val + n); }
    itr operator-(ll const &n) const { return itr(val - n); }
    ll operator-(itr const &itr) const { return val - itr.val; }
    itr &operator+=(ll const &n) {
      val += n;
      return *this;
    }
    itr &operator-=(ll const &n) { return *this += (-n); }
    ll const &operator*() const { return val; }
  };
  using iterator = itr;
  ll const val_begin;
  ll const val_end;
  range(ll const &end = 0) : range(0, end) {}
  range(ll const &begin, ll const &end) : val_begin(begin), val_end(end) {}
  itr begin() const { return itr(val_begin); }
  itr end() const { return itr(val_end); }
  ll size() const { return val_end - val_begin; }
  bool empty() const { return size() == 0; }
  template <class F> auto map(F const &f) const {
    return seq<decltype(f(declval<ll>()))>(f, *this);
  }
};

// using T = double;
template <class T> struct seq {
  struct itr {
    using difference_type = range::iterator::difference_type;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = random_access_iterator_tag;
    fun<T(ll)> mapper;
    range::itr base;
    itr(fun<T(ll)> const &f, range::itr const &itr = range::itr(0))
        : mapper(f), base(itr) {}
    bool operator==(itr const &itr) const { return base == itr.base; }
    bool operator!=(itr const &itr) const { return base != itr.base; }
    itr &operator++() { return *this += 1; }
    itr operator++(int) { return itr(mapper, base++); }
    itr &operator--() { return *this -= 1; }
    itr operator--(int) { return itr(mapper, base--); }
    itr operator+(ll const &n) const { return itr(mapper, base + n); }
    itr operator-(ll const &n) const { return itr(mapper, base - n); }
    ll operator-(itr const &itr) const { return base - itr.base; }
    itr &operator+=(ll const &n) {
      base += n;
      return *this;
    }
    itr &operator-=(ll const &n) { return *this += (-n); }
    T const operator*() const { return mapper(*base); }
  };
  using iterator = itr;
  fun<T(ll)> const mapper;
  range const domain;
  seq(fun<T(ll)> const &f, range const &r) : mapper(f), domain(r) {}
  itr begin() const { return itr(mapper, domain.begin()); }
  itr end() const { return itr(mapper, domain.end()); }
  ll size() const { return domain.size(); }
  bool empty() const { return domain.empty(); }
  template <class F> auto map(F const &f) const {
    return seq<decltype(f(mapper(declval<ll>())))>(
        [g = mapper, f](auto i) { return f(g(i)); }, domain);
  }
  T operator[](ll i) const { return mapper(i); }
};

ll bisect(ll ng, ll ok, fun<bool(ll)> const &is_ok) {
  while (ok - ng > 1) {
    dump(ng, ok);
    ll m = ng + (ok - ng) / 2;
    (is_ok(m) ? ok : ng) = m;
  }
  return ok;
}

ll gcd(ll p, ll q) { return (q == 0) ? p : gcd(q, p % q); }
ll lcm(ll p, ll q) { return p / gcd(q, p) * q; }

// MOD
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

constexpr ll MOD = 1e9 + 7;
