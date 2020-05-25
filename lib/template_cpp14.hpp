#include <algorithm>
#include <bitset>
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// Utility
using std::declval;
using std::enable_if_t;
using std::get;
using std::is_array;
using std::is_same;
using std::iterator_traits;
using std::make_pair;
using std::make_tuple;
using std::random_access_iterator_tag;
using std::stold;
using std::stoll;
using std::to_string;
using std::operator""s;

// Types
using std::bitset;
using std::deque;
using std::list;
using std::multiset;
using std::nullptr_t;
using std::pair;
using std::tuple;
using std::unordered_multimap;
using std::unordered_multiset;
using ll = __int128;
using lf = long double;
using str = std::string;
template <class T> using u_set = std::unordered_set<T>;
template <class T> using vec = std::vector<T>;
using vecl = vec<ll>;
using vecf = vec<lf>;
using vecs = vec<str>;
template <class K, class V> using u_map = std::unordered_map<K, V>;
template <class V> using graph = u_map<V, u_set<V>>;
template <typename _Signature> using fun = std::function<_Signature>;

// Algorithms
using std::accumulate;
using std::all_of;
using std::any_of;
using std::back_inserter;
using std::copy;
using std::copy_if;
using std::count;
using std::count_if;
using std::find_if;
using std::for_each;
using std::index_sequence;
using std::index_sequence_for;
using std::inserter;
using std::lower_bound;
using std::max;
using std::max_element;
using std::min;
using std::min_element;
using std::next_permutation;
using std::none_of;
using std::partial_sum;
using std::remove_if;
using std::replace_if;
using std::reverse;
using std::set_difference;
using std::set_intersection;
using std::set_symmetric_difference;
using std::set_union;
using std::sort;
using std::swap;
using std::transform;
using std::unique;
using std::upper_bound;

namespace io {
// Input
using IS = std::istream;
IS &in(IS &);
IS &in(IS &i) { return i; }
template <class T, class... Ts> IS &in(IS &i, T &a, Ts &... as) {
  return in(i >> a, as...);
}
IS &operator>>(IS &i, __int128 &x) {
  long long int xx;
  i >> xx;
  x = xx;
  return i;
}
template <class V> IS &operator>>(IS &i, vec<V> &a) {
  for (auto &ai : a)
    i >> ai;
  return i;
}
template <class F, class S> IS &operator>>(IS &i, pair<F, S> &p) {
  return in(i, p.first, p.second);
}
template <class... Ts> IS &operator>>(IS &i, tuple<Ts...> &t) {
  return apply([&](auto &... ts) -> IS & { return in(i, ts...); }, t);
}
// Output
using OS = std::ostream;

OS &out_join(OS &o, str const &) { return o; }
template <class T> OS &out_join(OS &o, str const &, T const &a) {
  return o << a;
}
template <class T, class... Ts>
OS &out_join(OS &o, str const &sep, T const &a, Ts const &... as) {
  return out_join(o << a << sep, sep, as...);
}
OS &operator<<(OS &o, __int128 const &x) {
  return o << static_cast<long long int>(x);
}
template <class F, class S> OS &operator<<(OS &o, pair<F, S> const &p) {
  return o << p.first << ":" << p.second;
}
template <class... Ts> OS &operator<<(OS &o, tuple<Ts...> const &t) {
  auto f = [&](auto const &... ts) -> OS & {
    return out_join(o << "(", ",", ts...);
  };
  return apply(f, t) << ")";
}
template <class T> struct Joiner {
  str const pre;
  str const post;
  str const sep;
  vec<T> const container;
  template <class Itr>
  Joiner(Itr begin, Itr end, str const &sep, str const &pre, str const &post)
      : pre(pre), post(post), sep(sep), container(begin, end) {}
};
template <class T> OS &operator<<(OS &o, Joiner<T> const &joiner) {
  auto itr = joiner.container.begin();
  auto end = joiner.container.end();
  o << joiner.pre;
  if (itr != end)
    o << *(itr++);
  while (itr != end)
    o << joiner.sep << *(itr++);
  return o << joiner.post;
}
template <class Itr>
auto join(Itr b, Itr e, str const &sep = ""s, str const &pre = ""s,
          str const &post = ""s) {
  using T = typename iterator_traits<Itr>::value_type;
  return Joiner<T>(b, e, sep, pre, post);
}
template <class C, enable_if_t<!is_same<C, str>::value && !is_array<C>::value,
                               nullptr_t> = nullptr>
OS &operator<<(OS &o, C const &a) {
  return o << join(a.begin(), a.end(), ",", "[", "]");
}
} // namespace io
using std::cerr;
using std::cin;
using std::cout;
auto init_io = []() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cout << std::fixed << std::setprecision(30);
};
auto input = [](auto &... a) { io::in(cin, a...); };
auto print = [](auto const &... a) { io::out_join(cout, " ", a...) << "\n"; };
#ifdef JUMPAKU_DEBUG
auto dump = [](auto const &... a) { io::out_join(cerr, " ", a...) << "\n"; };
#else
auto dump = [](auto const &...) {};
#endif
using io::join;

// Hash
namespace hashcode {
template <class... Ts> ll hash_args(ll h, Ts const &... ts);
ll hash_args(ll h) { return h; }
template <class T, class... Ts>
ll hash_args(ll h, T const &t, Ts const &... ts) {
  constexpr std::hash<T> hasher;
  return hash_args(((h << 19) - h) ^ hasher(t), ts...);
}

template <class... Ts, size_t... I>
ll hash_tuple(tuple<Ts...> const &t, index_sequence<I...>) {
  return hash_args(17, get<I>(t)...);
}
} // namespace hashcode
namespace std {
template <> struct hash<__int128> {
  size_t operator()(__int128 const &t) const {
    auto hasher = std::hash<long long int>{};
    auto h0 = hasher(static_cast<long long int>((t >> 64) & 0xffffffffLL));
    auto h1 = hasher(static_cast<long long int>(t & 0xffffffffLL));
    return h0 ^ h1;
  }
};
template <class... Ts> struct hash<tuple<Ts...>> {
  size_t operator()(tuple<Ts...> const &t) const {
    ll h = hashcode::hash_tuple(t, index_sequence_for<Ts...>());
    return h ^ (h >> 32);
  }
};
template <class T> struct hash<u_set<T>> {
  size_t operator()(u_set<T> const &t) const {
    auto hasher = hash<T>{};
    auto h = (decltype(hash<T>{}(declval<T>())))0;
    h = accumulate(t.begin(), t.end(), h,
                   [&](auto acc, auto const &ti) { return acc + hasher(ti); });
    return h;
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
  iterator_base(ll const &i) : i(i) {}
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
  seq_base(ll b, ll e) : b(b), e(max(b, e)) {}
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
  fun<T(ll)> const f;
  seq(ll b, ll e, fun<T(ll)> const &f) : seq_base<T>(b, e), f(f) {}
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
  range(ll n) : range(0, n) {}
  range(ll b, ll e) : seq_base<ll>(b, e) {}
  iterator begin() const { return iterator(b); }
  iterator end() const { return iterator(e); }
  bool has(ll x) const { return b <= x && x < e; }
  ll operator[](ll i) const { return i + b; }
};
} // namespace ranges
using range = ranges::range;
range::iterator end(ll i) { return range::iterator(i); }
range::iterator begin(ll i = 0) { return range::iterator(i); }
template <class F> auto seq(ll b, ll e, F const &f) {
  using T = decltype(f(declval<ll>()));
  return ranges::seq<T>(b, e, f);
}
template <class F> auto seq(ll n, F const &f) { return seq(0, n, f); }

ll gcd(ll p, ll q) { return (q == 0) ? p : gcd(q, p % q); }
ll lcm(ll p, ll q) { return p / gcd(q, p) * q; }

bool odd(ll n) { return n & 1; }
bool even(ll n) { return !odd(n); }

bool imply(bool p, bool q) { return !p || q; }
bool iff(bool p, bool q) { return p == q; }

constexpr ll MOD = 1e9 + 7;
