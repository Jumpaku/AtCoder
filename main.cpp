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
uint64_t xorshift(uint64_t x) {
  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;
  return x;
}
template <class... Ts> uint64_t hash_args(uint64_t h, Ts const &... ts);
uint64_t hash_args(uint64_t h) { return h; }
template <class T, class... Ts>
uint64_t hash_args(uint64_t h, T const &t, Ts const &... ts) {
  constexpr hash<T> hasher;
  uint64_t h = xorshift(hasher(t));
  return hash_args(((h << 19) - h) ^ x, ts...);
}
template <class... Ts, size_t... I>
size_t hash_tuple(tuple<Ts...> const &t, index_sequence<I...>) {
  return hash_args(0x880355f21e6d1965ULL, get<I>(t)...);
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
namespace ranges {
template <class T> struct seq {
  struct iterator {
    using difference_type = ll;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = random_access_iterator_tag;
    seq<T> const *s;
    ll i;
    iterator(seq const *s, ll const &i = 0) : s(s), i(i) {}
    bool operator==(iterator const &itr) const { return i == itr.i; }
    bool operator!=(iterator const &itr) const { return i != itr.i; }
    iterator &operator++() { return *this += 1; }
    iterator operator++(int) { return iterator(s, i++); }
    iterator &operator--() { return *this -= 1; }
    iterator operator--(int) { return iterator(s, i--); }
    iterator operator+(ll const &n) const { return iterator(s, i + n); }
    iterator operator-(ll const &n) const { return iterator(s, i - n); }
    ll operator-(iterator const &itr) const { return i - itr.i; }
    iterator &operator+=(ll const &n) {
      i += n;
      return *this;
    }
    iterator &operator-=(ll const &n) { return *this += (-n); }
    T const operator*() const { return (*s)[i]; }
  };
  function<T(ll)> const f;
  ll const l;
  seq(function<T(ll)> const &f, ll const &l) : f(f), l(l) {}
  iterator begin() const { return iterator(this, 0); }
  iterator end() const { return iterator(this, l); }
  ll size() const { return l; }
  bool empty() const { return size() == 0; }
  template <class F> auto map(F const &g) const {
    return seq<decltype(g(f(declval<ll>())))>(
        [g, f = f](auto i) { return g(f(i)); }, l);
  }
  virtual T operator[](ll i) const { return f(i); }
};
} // namespace ranges

struct range : ranges::seq<ll> {
  ll const begin_;
  range(ll end) : range(0LL, end) {}
  range(ll begin, ll end)
      : seq<ll>([begin](auto i) { return i + begin; }, end - begin),
        begin_(begin) {}
  ll operator[](ll i) const override { return i + begin_; }
};
namespace ranges {
range endless = range(-1LL);
}
range::iterator begin(ll i = 0LL) {
  return range::iterator(&ranges::endless, i);
}
range::iterator end(ll i) { return begin(i); }

template <class T = ll> vector<T> vec(size_t n, T &&init = T()) {
  return vector<T>(n, init);
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

int main() {
  input();
  dump();
  print();
}

