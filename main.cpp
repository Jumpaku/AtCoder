//#pragma GCC optimize("O3")
//#pragma GCC target("avx")

#include <algorithm>
#include <deque>
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
using std::enable_if_t, std::is_same_v, std::is_array_v, std::declval;
using std::get, std::make_pair, std::make_tuple, std::apply;
using std::iterator_traits, std::random_access_iterator_tag;
using std::stoll, std::stold, std::to_string, std::operator""s;

// Types
using std::deque, std::list, std::multiset, std::unordered_multimap,
    std::unordered_multiset;
using std::nullptr_t, std::pair, std::tuple;
using ll = long long int;
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
using std::accumulate, std::partial_sum;
using std::all_of, std::any_of, std::none_of, std::count_if, std::find_if,
    std::for_each, std::max_element, std::min_element, std::remove_if,
    std::replace_if, std::reverse, std::transform, std::unique, std::sort,
    std::next_permutation, std::swap;
using std::lower_bound, std::upper_bound;
using std::max, std::min, std::clamp, std::lcm, std::gcd;

namespace io {
// Input
using IS = std::istream;
IS &in(IS &);
IS &in(IS &i) { return i; }
template <class T, class... Ts> IS &in(IS &i, T &a, Ts &... as) {
  return in(i >> a, as...);
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

OS &out(OS &o, str const &) { return o; }
template <class T> OS &out(OS &o, str const &, T const &a) { return o << a; }
template <class T, class... Ts>
OS &out(OS &o, str const &sep, T const &a, Ts const &... as) {
  return out(o << a << sep, sep, as...);
}
template <class F, class S> OS &operator<<(OS &o, pair<F, S> const &p) {
  return out(o, ":", p.first, p.second);
}
template <class... Ts> OS &operator<<(OS &o, tuple<Ts...> const &t) {
  auto f = [&](auto const &... ts) -> OS & {
    return out(o << "(", ",", ts...);
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
template <class C, enable_if_t<!is_same_v<C, str> && !is_array_v<C>,
                               nullptr_t> = nullptr>
OS &operator<<(OS &o, C const &a) {
  return o << join(a.begin(), a.end(), ",", "[", "]");
}
} // namespace io
using std::cerr, std::cin, std::cout;
auto init_io = []() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cout << std::fixed << std::setprecision(15);
};
auto input = [](auto &... a) { io::in(cin, a...); };
auto print = [](auto const &... a) { io::out(cout, " ", a...) << "\n"; };
#ifdef JUMPAKU_DEBUG
auto dump = [](auto const &... a) { io::out(cerr, " ", a...) << "\n"; };
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
} // namespace hashcode
namespace std {
template <class... Ts> struct hash<tuple<Ts...>> {
  size_t operator()(tuple<Ts...> const &t) const {
    ll h = apply(
        [&](auto const &... ts) { return hashcode::hash_args(17, ts...); }, t);
    return h ^ (h >> 32);
  }
};
template <class T> struct hash<u_set<T>> {
  size_t operator()(u_set<T> const &t) const {
    auto hasher = std::hash<T>{};
    return accumulate(
        t.begin(), t.end(), (decltype(hasher(declval<T>())))0,
        [&](auto acc, auto const &ti) { return acc + hasher(ti); });
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
  fun<T(ll)> const f;
  seq(ll b, ll e, fun<T(ll)> const &f) : seq_base<T>(b, e), f(f) {}
  iterator begin() const { return iterator(*this, 0); }
  iterator end() const { return iterator(*this, this->size()); }
  T operator[](ll i) const { return f(i + this->b); }
};
template <class F>
seq(ll b, ll e, F const &f)->seq<typename std::invoke_result<F, ll>::type>;

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
  bool contains(ll x) const { return b <= x && x < e; }
  ll operator[](ll i) const { return i + b; }
};
} // namespace ranges
using range = ranges::range;
range::iterator end(ll i) { return range::iterator(i); }
range::iterator begin(ll i = 0LL) { return range::iterator(i); }
template <class F> auto seq(ll n, F const &f) { return ranges::seq(0LL, n, f); }

bool odd(ll n) { return n & 1; }
bool even(ll n) { return !odd(n); }

constexpr ll MOD = 1e9 + 7;

void solve();
int main() {
  init_io();
  ll t = 1;
  /** input(t); /**/
  while(t--)
    solve();
  cout.flush();
}

void solve() {
  input();
  print();
}

