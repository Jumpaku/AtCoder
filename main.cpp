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
template <class T> struct Joiner {
  str const pre;
  str const post;
  str const delim;
  vector<T> const container;
  Joiner(vector<T> v, str const &delim, str const &pre, str const &post)
      : pre(pre), post(post), delim(delim), container(v) {}
};
template <class T> OS &operator<<(OS &o, Joiner<T> const &joiner) {
  auto itr = joiner.container.begin();
  auto end = joiner.container.end();
  o << joiner.pre;
  if (itr != end)
    o << *(itr++);
  while (itr != end)
    o << joiner.delim << *(itr++);
  return o << joiner.post;
}
template <class Itr, class T = typename iterator_traits<Itr>::value_type>
Joiner<T> join(Itr b, Itr e, str const &delim = ""s, str const &pre = ""s,
               str const &post = ""s) {
  return Joiner<T>(vector<T>(b, e), delim, pre, post);
}
template <
    class C,
    class T = typename iterator_traits<typename C::iterator>::value_type,
    typename enable_if<!is_same<C, str>::value, nullptr_t>::type = nullptr>
OS &operator<<(OS &o, C const &a) {
  return o << join(a.begin(), a.end(), ",", "[", "]");
}
} // namespace io
auto input = [](auto &... a) { io::in(cin, a...); };
auto print = [](auto const &... a) { io::out(cout, a...); };
#ifdef JUMPAKU_DEBUG
auto dump = [](auto const &... a) { io::out(cerr, a...); };
#else
auto dump = [](auto const &...) {};
#endif
using io::join;

// Hash
namespace hashcode {
template <class... Ts> uint64_t hash_args(uint64_t h, Ts const &... ts);
uint64_t hash_args(uint64_t h) { return h; }
template <class T, class... Ts>
uint64_t hash_args(uint64_t h, T const &t, Ts const &... ts) {
  constexpr hash<T> hasher;
  return hash_args(((h << 19) - h) ^ hasher(t), ts...);
}
template <class... Ts, size_t... I>
uint64_t hash_tuple(tuple<Ts...> const &t, index_sequence<I...>) {
  return hash_args(17, get<I>(t)...);
}
} // namespace hashcode
namespace std {
template <class... Ts> struct hash<tuple<Ts...>> {
  size_t operator()(tuple<Ts...> const &t) const {
    uint64_t h = hashcode::hash_tuple(t, index_sequence_for<Ts...>());
    return h ^ (h >> 32);
  }
};
} // namespace std

// Range
namespace ranges {
template <class T, class Itr> struct iterator_base {
  using difference_type = ll;
  using value_type = T;
  using pointer = T *;
  using reference = T &;
  using iterator_category = random_access_iterator_tag;
  ll i;
  iterator_base(ll const &i = 0) : i(i) {}
  bool operator==(Itr const &itr) const { return i == itr.i; }
  bool operator!=(Itr const &itr) const { return i != itr.i; }
  ll operator-(Itr const &itr) const { return i - itr.i; }
  Itr operator++(int) { return with(i++); }
  Itr operator--(int) { return with(i--); }
  Itr operator+(ll const &n) const { return with(i + n); }
  Itr operator-(ll const &n) const { return with(i - n); }
  Itr &operator+=(ll const &n) {
    i += n;
    return self();
  }
  Itr &operator-=(ll const &n) { return self() += (-n); }
  Itr &operator++() { return self() += 1; }
  Itr &operator--() { return self() -= 1; }

protected:
  virtual Itr with(ll i) const = 0;
  virtual Itr &self() = 0;
};
template <class T> struct seq_base {
  ll const b;
  ll const e;
  seq_base(ll b, ll e) : b(b), e(e) {}
  ll size() const { return e - b; }
  bool empty() const { return size() == 0; }
};
template <class T> struct seq : seq_base<T> {
  struct iterator : iterator_base<T, iterator> {
    seq<T> const &s;
    iterator(seq<T> const &s, ll const &i)
        : iterator_base<T, iterator>(i), s(s) {}
    iterator with(ll i) const override { return iterator(s, i); }
    iterator &self() override { return *this; }
    T operator*() const { return s[this->i]; }
    iterator &operator=(iterator const &itr) {
      this->i = itr.i;
      return *this;
    }
  };
  function<T(ll)> const f;
  seq(ll b, ll e, function<T(ll)> const &f) : seq_base<T>(b, e), f(f) {}
  iterator begin() const { return iterator(*this, 0); }
  iterator end() const { return iterator(*this, this->size()); }
  T operator[](ll i) const { return f(i + this->b); }
};
struct range : seq_base<ll> {
  struct iterator : iterator_base<ll, iterator> {
    iterator(ll const &i) : iterator_base<ll, iterator>(i) {}
    iterator with(ll i) const override { return iterator(i); }
    iterator &self() override { return *this; }
    ll operator*() const { return i; }
  };
  range(ll n) : range(0LL, n) {}
  range(ll b, ll e) : seq_base<ll>(b, e) {}
  iterator begin() const { return iterator(b); }
  iterator end() const { return iterator(e); }
  ll operator[](ll i) const { return i + b; }
};
} // namespace ranges
using range = ranges::range;
range::iterator end(ll i) { return range::iterator(i); }
range::iterator begin(ll i) { return range::iterator(i); }
template <class F> auto seq(ll b, ll e, F const &f) {
  using T = decltype(f(declval<ll>()));
  return ranges::seq<T>(b, e, f);
}
template <class F> auto seq(ll n, F const &f) { return seq(0, n, f); }
template <class T = ll> vector<T> vec(size_t n, T const &init = T()) {
  return vector<T>(n, init);
}

ll gcd(ll p, ll q) { return (q == 0) ? p : gcd(q, p % q); }
ll lcm(ll p, ll q) { return p / gcd(q, p) * q; }
bool odd(ll n) { return n & 1; }
bool even(ll n) { return !odd(n); }

constexpr ll MOD = 1e9 + 7;

void solve();
int main() {
  ll t = 1;
  /** input(t); /**/
  for ([[maybe_unused]] auto &&i : range(t)) {
    solve();
  }
}

void solve() {
  input();
  print();
}

