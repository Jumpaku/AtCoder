

#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#ifdef JUMPAKU_LOCAL
//#define _GLIBCXX_DEBUG
#endif

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
#include <memory>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// Utility
using std::get;
using std::make_pair;
using std::make_tuple;
using std::make_unique;
using std::stold;
using std::stoll;
using std::operator""s;
using std::abs;

// Types
using std::bitset;
using std::deque;
using std::list;
using std::multiset;
using std::pair;
using std::tuple;
using ll = /** __int128; //*/ std::int_fast64_t;
using lf = long double;
using str = std::string;
template <class V, class H = std::hash<V>>
using u_multiset = std::unordered_multiset<V, H>;
template <class V, class H = std::hash<V>>
using u_set = std::unordered_set<V, H>;
template <class K, class V, class H = std::hash<K>>
using u_multimap = std::unordered_multimap<K, V, H>;
template <class K, class V, class H = std::hash<K>>
using u_map = std::unordered_map<K, V, H>;
template <class T> using vec = std::vector<T>;
template <class V, class C = std::less<V>>
using priority_queue = std::priority_queue<V, vec<V>, C>;
using vecl = vec<ll>;
using vecf = vec<lf>;
using vecs = vec<str>;
template <class V> using u_graph = u_map<V, u_set<V>>;
using v_graph = vec<vec<int>>;
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
using std::fill;
using std::find_if;
using std::for_each;
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

namespace utils {
str to_string(__int128 const &x) { return std::to_string((long long)x); }
template <class T> T clamp(T const &v, T const &l, T const &h) {
  return min(h, max(l, v));
}
ll gcd(ll p, ll q) { return (q == 0) ? p : gcd(q, p % q); }
ll lcm(ll p, ll q) { return p / gcd(q, p) * q; }
ll sign(ll x) { return ll{x < 0 ? -1 : x > 0 ? 1 : 0}; }
ll pow(ll x, ll n) {
  if (n == 0)
    return 1;
  if (n & 1)
    return x * pow(x, n - 1);
  auto b = pow(x, n / 2);
  return b * b;
}
bool odd(ll n) { return n & 1; }
bool even(ll n) { return !odd(n); }
bool imply(bool p, bool q) { return !p || q; }
bool iff(bool p, bool q) { return p == q; }
} // namespace utils
using std::to_string;
using utils::clamp;
using utils::even;
using utils::gcd;
using utils::iff;
using utils::imply;
using utils::lcm;
using utils::odd;
using utils::sign;
using utils::to_string;

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
  return i >> p.first >> p.second;
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
OS &operator<<(OS &o, __int128 const &x) { return o << (long long int)x; }
template <class F, class S> OS &operator<<(OS &o, pair<F, S> const &p) {
  return o << p.first << ":" << p.second;
}
template <class... Ts, size_t... I>
OS &tuple_out(OS &o, tuple<Ts...> const &t, std::index_sequence<I...>) {
  return out_join(o, ",", get<I>(t)...);
}
template <class... Ts> OS &operator<<(OS &o, tuple<Ts...> const &t) {
  return tuple_out(o << "(", t, std::make_index_sequence<sizeof...(Ts)>())
         << ")";
}

template <class T> struct Joiner {
  str const pre;
  str const post;
  str const sep;
  vec<T> const container;
  template <class Itr>
  Joiner(Itr const &begin, Itr const &end, str const &sep, str const &pre,
         str const &post)
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
auto join(Itr const &b, Itr const &e, str const &sep = ""s,
          str const &pre = ""s, str const &post = ""s) {
  using T = typename std::iterator_traits<Itr>::value_type;
  return Joiner<T>(b, e, sep, pre, post);
}
template <class C, std::enable_if_t<!std::is_same_v<C, str> &&
                                        (decltype(std::begin(std::declval<C>()),
                                                  std::end(std::declval<C>()),
                                                  std::true_type{})::value),
                                    std::nullptr_t> = nullptr>
OS &operator<<(OS &o, C const &a) {
  return o << join(std::begin(a), std::end(a), ",", "[", "]");
}
} // namespace io
using std::cin;
using std::cout;
void init_io() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  cout << std::fixed << std::setprecision(15);
};
auto input = [](auto &... a) { io::in(cin, a...); };
auto print = [](auto const &... a) { io::out_join(cout, " ", a...) << "\n"; };
#ifdef JUMPAKU_DEBUG
auto dump = [](auto const &... a) {
  io::out_join(std::cerr, " "s, a...) << "\n";
};
#else
auto dump = [](auto const &...) {};
#endif
using io::join;

// Hash
namespace hashcode {
template <class... Ts> size_t hash_args(size_t h, Ts const &... ts);
size_t hash_args(size_t h) { return h; }
template <class T, class... Ts>
size_t hash_args(size_t h, T const &t, Ts const &... ts) {
  constexpr std::hash<T> hasher;
  return hash_args(((h << 10) - h) ^ hasher(t), ts...);
}
template <class... Ts, size_t... I>
size_t hash_tuple(tuple<Ts...> const &t, std::index_sequence<I...>) {
  return hash_args(17, get<I>(t)...);
}
} // namespace hashcode
namespace std {
#if __GNUC__ != 9 || defined(__STRICT_ANSI__)
template <> struct hash<__int128> {
  size_t operator()(__int128 const &t) const {
    return (t & 0xffffffff) ^ ((t >> 63) & 0xffffffff);
  }
};
#endif
template <class... Ts> struct hash<tuple<Ts...>> {
  size_t operator()(tuple<Ts...> const &t) const {
    size_t h = hashcode::hash_tuple(t, std::index_sequence_for<Ts...>());
    return h ^ (h >> 32);
  }
};
template <class T> struct hash<u_set<T>> {
  size_t operator()(u_set<T> const &t) const {
    constexpr std::hash<T> hasher;
    return accumulate(
        t.begin(), t.end(), (size_t)0,
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
  using iterator_category = std::random_access_iterator_tag;
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
    iterator(iterator const &) = default;
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
template <class F> auto seq(ll n, F const &f) {
  using T = decltype(f(std::declval<ll>()));
  return ranges::seq<T>(0LL, n, f);
}

#include <chrono>
class stopwatch {
#ifdef JUMPAKU_DEBUG
  using Clock = std::chrono::high_resolution_clock;
  using Duration = Clock::duration;
  using TimePoint = Clock::time_point;
  bool isRunning;
  Duration total_duration;
  TimePoint last_lap;
  double castToSeconds(Duration const &d) const {
    return 1e-9 *
           std::chrono::duration_cast<std::chrono::nanoseconds>(d).count();
  }

public:
  stopwatch() : isRunning(false), total_duration(std::chrono::nanoseconds{0}){};
  void reset() {
    isRunning = false;
    total_duration = std::chrono::nanoseconds{0};
    std::cerr << "=DEBUG= Stopwatch::reset()\n";
  }
  void start() {
    auto current = Clock::now();
    if (isRunning)
      return;
    isRunning = true;
    last_lap = current;
    std::cerr << "=DEBUG= Stopwatch::start()\n";
  }
  void restart() {
    last_lap = Clock::now();
    total_duration = std::chrono::nanoseconds{0};
    isRunning = true;
    std::cerr << "=DEBUG= Stopwatch::restart()\n";
  }
  void stop() {
    auto current = Clock::now();
    if (!isRunning)
      return;
    isRunning = false;
    total_duration += current - last_lap;
    std::cerr << "=DEBUG= Stopwatch::stop()\n";
  }
  double lap() {
    auto current = Clock::now();
    if (isRunning) {
      total_duration += current - last_lap;
      last_lap = current;
    }
    auto seconds = castToSeconds(total_duration);
    std::cerr << "=DEBUG= Stopwatch::lap()  : " << seconds << "[s]\n";
    return seconds;
  }
#else
public:
  void start() {}
  void reset() {}
  void restart() {}
  void stop() {}
  double lap() { return 0.0; }
#endif
};

constexpr lf PI = 3.141592653589793238462643383279502884L;
constexpr ll MOD = 1e9 + 7;

#endif /* TEMPLATE_HPP */

/**
// DP Definition
using Data = struct {};
using Key = tuple<>;
using Value = ll;
using Cache = u_map<Key, Value>;
struct DP {
  Data data;
  Cache cache;
  DP(Data const &data) : data(data), cache((ll)1e6) {}
  Value compute(Key const &key) {
    if (IS_INITIAL)
      return INITIAL_VALUE;
    if (auto found = cache.find(key); found != cache.end())
      return found->second;
    return cache[key] = RECURSION_CALL(this->compute(Key{}));
  }
};
// DP Call
/*
  DP dp(Data{});
  print(dp.compute(Key{}));
*/
