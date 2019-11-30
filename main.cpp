#pragma GCC optimize("O3")
#pragma GCC target("avx")

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
IS &in(IS &i);
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
auto dump = [](auto const &... a) { io::out(cout, a...); };
#else
auto dump = [](auto const &... a) {};
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
  return hash_args(1089283, get<I>(t)...);
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
vector<ll> range(ll const &begin, ll const &end) {
  vector<ll> ret(max(0LL, end - begin));
  iota(ret.begin(), ret.end(), begin);
  return ret;
}
vector<ll> range(ll const &end) { return range(0, end); }
template <class T = ll> vector<T> vec(size_t n, T &&init = T()) {
  return vector<T>(n, init);
}
template <class Itr, class T = typename iterator_traits<Itr>::value_type>
vector<T> vec(Itr begin, Itr end) {
  return vector<T>(begin, end);
}

ll bisect(ll ng, ll ok, fun<bool(ll)> const &is_ok) {
  while (ok - ng > 1) {
    dump(ng, ok);
    ll m = ng + (ok - ng) / 2;
    (is_ok(m) ? ok : ng) = m;
  }
  return ok;
}
ll gcd(ll p, ll q) { return (q == 0) ? p : gcd(q, p % q); }
ll lcm(ll p, ll q) { return p * q / gcd(q, p); }

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
constexpr ll MOD = 1e9 + 7;

int main() {
  str S;
  input(S);
  dump(S);
  print(S);
}
