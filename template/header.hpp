
// std
#include <algorithm>
#include <deque>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// Boost
#include <boost/stacktrace.hpp>

// Types
using i32 = std::int_fast32_t;
using i64 = std::int_fast64_t;
using i128 = __int128_t;
using ll = /**/ i64; //*/ i128;
using f64 = long double;

using std::deque;
using std::list;
using std::multiset;
using std::pair;
using std::tuple;
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
using vecf = vec<f64>;
using vecs = vec<str>;

// Utils
using std::get;
using std::make_pair;
using std::make_tuple;
using std::operator""s;
using std::abs;
using std::back_inserter;
using std::clamp;
using std::gcd;
using std::inserter;
using std::lcm;
using std::max;
using std::min;
using std::swap;

// Algorithms
using std::accumulate;
using std::partial_sum;
using std::ranges::all_of;
using std::ranges::any_of;
using std::ranges::copy_if;
using std::ranges::count_if;
using std::ranges::find_if;
using std::ranges::lower_bound;
using std::ranges::max_element;
using std::ranges::min_element;
using std::ranges::none_of;
using std::ranges::remove_if;
using std::ranges::reverse;
using std::ranges::sort;
using std::ranges::transform;
using std::ranges::upper_bound;

// Exception
#define throw_if(ng_expr, msg)                                                 \
  throw_if_impl(ng_expr, __FILE__, __LINE__, msg, #ng_expr)
template <class Expr, class File, class Line>
void throw_if_impl(Expr const &ng_expr, File const &file, Line const &line,
                   std::string const &msg, std::string const &ng_expr_str) {
#ifdef JUMPAKU_DEBUG
  if (ng_expr) {
    std::stringstream ss;
    ss << "\nthrow_if:\n\t" << file << ":" << line << ":\n\t" << msg << ": "
       << ng_expr_str << "\n"
       << boost::stacktrace::stacktrace();

    throw std::runtime_error(ss.str());
  }
#endif
}

// Scanner Decralations
template <class E>
std::istream &operator>>(std::istream &is, std::vector<E> &v);
template <class T1, class T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &v);
template <class... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &v);
std::istream &operator>>(std::istream &i, __int128_t &x);

// Printer Decralations
template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, std::pair<T1, T2> v);
std::ostream &operator<<(std::ostream &os, std::tuple<>);
template <class T0, class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<T0, Ts...> v);
template <class E> struct Joiner;
template <class Itr>
Joiner<typename std::iterator_traits<Itr>::value_type>
join(Itr const &b, Itr const &e, std::string const &sep = "",
     std::string const &pre = "", std::string const &post = "");
template <std::ranges::range Range>
Joiner<typename std::ranges::range_value_t<Range>>
join(Range const &r, std::string const &sep = "", std::string const &pre = "",
     std::string const &post = "");
template <class E> std::ostream &operator<<(std::ostream &os, Joiner<E> joiner);
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::vector<Es...> v);
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::list<Es...> v);
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::set<Es...> v);
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::multiset<Es...> v);
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::unordered_set<Es...> v);
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::unordered_multiset<Es...> v);
template <class... KV>
std::ostream &operator<<(std::ostream &os, std::map<KV...> v);
template <class... KV>
std::ostream &operator<<(std::ostream &os, std::multimap<KV...> v);
template <class... KV>
std::ostream &operator<<(std::ostream &os, std::unordered_map<KV...> v);
template <class... KV>
std::ostream &operator<<(std::ostream &os, std::unordered_multimap<KV...> v);
std::ostream &operator<<(std::ostream &os, __int128_t v);

// Read Declarations
template <class T> T read(std::istream &is = std::cin);
template <class... Ts>
std::tuple<Ts...> read_tuple(std::istream &is = std::cin);
template <class E> std::vector<E> read_vec(int n0, std::istream &is = std::cin);
template <class E>
std::vector<std::vector<E>> read_vec(int n0, int n1,
                                     std::istream &is = std::cin);
template <class E>
std::vector<std::vector<std::vector<E>>> read_vec(int n0, int n1, int n2,
                                                  std::istream &is = std::cin);

// Print Declarations
void print_impl(std::ostream &os);
template <class T, class... Ts>
void print_impl(std::ostream &os, T v, Ts... vs);
template <class... Ts> void print(Ts... vs);
template <class... Ts> void dump(Ts const &...vs);

// Debug
template <class V> std::string VAR_FMT(std::string s, V v) {
  std::stringstream ss;
  ss << s << "=" << v;
  return ss.str();
}
template <class File, class Line, class... Ts>
void dump_vars_impl(File file, Line line, Ts... vs) {
  std::cerr << "\ndump_vars:\n\t" << file << ":" << line << "\n\t";
  using swallow = std::initializer_list<int>;
  (void)swallow{(void(std::cerr << " " << vs), 0)...};
  std::cerr << std::endl;
}
#ifdef JUMPAKU_DEBUG
#define DUMP_VARS_APPLY(_1, _2, _3, _4, _5, _6, _7, _8, F, ...) F
#define DUMP_VARS_1(A1) dump_vars_impl(__FILE__, __LINE__, VAR_FMT(#A1, A1))
#define DUMP_VARS_2(A1, A2)                                                    \
  dump_vars_impl(__FILE__, __LINE__, VAR_FMT(#A1, A1), VAR_FMT(#A2, A2))
#define DUMP_VARS_3(A1, A2, A3)                                                \
  dump_vars_impl(__FILE__, __LINE__, VAR_FMT(#A1, A1), VAR_FMT(#A2, A2),       \
                 VAR_FMT(#A3, A3))
#define DUMP_VARS_4(A1, A2, A3, A4)                                            \
  dump_vars_impl(__FILE__, __LINE__, VAR_FMT(#A1, A1), VAR_FMT(#A2, A2),       \
                 VAR_FMT(#A3, A3), VAR_FMT(#A4, A4))
#define DUMP_VARS_5(A1, A2, A3, A4, A5)                                        \
  dump_vars_impl(__FILE__, __LINE__, VAR_FMT(#A1, A1), VAR_FMT(#A2, A2),       \
                 VAR_FMT(#A3, A3), VAR_FMT(#A4, A4), VAR_FMT(#A5, A5))
#define DUMP_VARS_6(A1, A2, A3, A4, A5, A6)                                    \
  dump_vars_impl(__FILE__, __LINE__, VAR_FMT(#A1, A1), VAR_FMT(#A2, A2),       \
                 VAR_FMT(#A3, A3), VAR_FMT(#A4, A4), VAR_FMT(#A5, A5),         \
                 VAR_FMT(#A6, A6))
#define DUMP_VARS_7(A1, A2, A3, A4, A5, A6, A7)                                \
  dump_vars_impl(__FILE__, __LINE__, VAR_FMT(#A1, A1), VAR_FMT(#A2, A2),       \
                 VAR_FMT(#A3, A3), VAR_FMT(#A4, A4), VAR_FMT(#A5, A5),         \
                 VAR_FMT(#A6, A6), VAR_FMT(#A7, A7))
#define DUMP_VARS_8(A1, A2, A3, A4, A5, A6, A7, A8)                            \
  dump_vars_impl(__FILE__, __LINE__, VAR_FMT(#A1, A1), VAR_FMT(#A2, A2),       \
                 VAR_FMT(#A3, A3), VAR_FMT(#A4, A4), VAR_FMT(#A5, A5),         \
                 VAR_FMT(#A6, A6), VAR_FMT(#A7, A7), VAR_FMT(#A8, A8))

#define dump_vars(...)                                                         \
  DUMP_VARS_APPLY(__VA_ARGS__, DUMP_VARS_8, DUMP_VARS_7, DUMP_VARS_6,          \
                  DUMP_VARS_5, DUMP_VARS_4, DUMP_VARS_3, DUMP_VARS_2,          \
                  DUMP_VARS_1)                                                 \
  (__VA_ARGS__)
#else
#define dump_vars(...)
#endif

// Scanners
template <class E>
std::istream &operator>>(std::istream &is, std::vector<E> &v) {
  for (auto &vi : v)
    is >> vi;
  return is;
}
template <class T1, class T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &v) {
  return is >> v.first >> v.second;
}
template <class... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &v) {
  return std::apply(
      [&](auto &...vs) -> std::istream & { return (is >> ... >> vs); }, v);
}
std::istream &operator>>(std::istream &i, __int128_t &x) {
  long long int xx;
  i >> xx;
  x = xx;
  return i;
}

// Printers
template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, std::pair<T1, T2> v) {
  return os << v.first << ":" << v.second;
}
std::ostream &operator<<(std::ostream &os, std::tuple<>) { return os << "()"s; }
template <class T0, class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<T0, Ts...> v) {
  return std::apply(
      [&](auto const &v0, auto const &...vs) -> std::ostream & {
        os << "(" << v0;
        using swallow = std::initializer_list<int>;
        (void)swallow{(void(os << "," << vs), 0)...};
        return os << ")";
      },
      v);
}
template <class E> struct Joiner {
  std::string const pre;
  std::string const post;
  std::string const sep;
  std::vector<E> const container;
  template <class Itr>
  Joiner(Itr const &begin, Itr const &end, std::string const &sep,
         std::string const &pre, std::string const &post)
      : pre(pre), post(post), sep(sep), container(begin, end) {}
};
template <class Itr>
Joiner<typename std::iterator_traits<Itr>::value_type>
join(Itr const &b, Itr const &e, std::string const &sep, std::string const &pre,
     std::string const &post) {
  return Joiner<typename std::iterator_traits<Itr>::value_type>(b, e, sep, pre,
                                                                post);
}
template <std::ranges::range Range>
Joiner<typename std::ranges::range_value_t<Range>>
join(Range const &r, std::string const &sep, std::string const &pre,
     std::string const &post) {
  return Joiner<typename std::ranges::range_value_t<Range>>(
      std::ranges::begin(r), std::ranges::end(r), sep, pre, post);
}
template <class E>
std::ostream &operator<<(std::ostream &os, Joiner<E> joiner) {
  auto itr = joiner.container.begin();
  auto end = joiner.container.end();
  os << joiner.pre;
  if (itr != end)
    os << *(itr++);
  while (itr != end)
    os << joiner.sep << *(itr++);
  return os << joiner.post;
}
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::vector<Es...> v) {
  return os << join(v.begin(), v.end(), ",", "[", "]");
}
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::list<Es...> v) {
  return os << join(v.begin(), v.end(), ",", "[", "]");
}
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::set<Es...> v) {
  return os << join(v.begin(), v.end(), ",", "[", "]");
}
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::multiset<Es...> v) {
  return os << join(v.begin(), v.end(), ",", "[", "]");
}
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::unordered_set<Es...> v) {
  return os << join(v.begin(), v.end(), ",", "[", "]");
}
template <class... Es>
std::ostream &operator<<(std::ostream &os, std::unordered_multiset<Es...> v) {
  return os << join(v.begin(), v.end(), ",", "[", "]");
}
template <class... KV>
std::ostream &operator<<(std::ostream &os, std::map<KV...> v) {
  return os << join(v.begin(), v.end(), ",", "[", "]");
}
template <class... KV>
std::ostream &operator<<(std::ostream &os, std::multimap<KV...> v) {
  return os << join(v.begin(), v.end(), ",", "[", "]");
}
template <class... KV>
std::ostream &operator<<(std::ostream &os, std::unordered_map<KV...> v) {
  return os << join(v.begin(), v.end(), ",", "[", "]");
}
template <class... KV>
std::ostream &operator<<(std::ostream &os, std::unordered_multimap<KV...> v) {
  return os << join(v.begin(), v.end(), ",", "[", "]");
}
std::ostream &operator<<(std::ostream &os, __int128_t v) {
  if (v >= 1000000000000000000) {
    os << (long long)(v / 1000000000000000000)
       << (long long)(v % 1000000000000000000);
  } else {
    os << (long long)v;
  }
  return os;
}

// Read
template <class T> T read(std::istream &is) {
  T v;
  is >> v;
  throw_if(!is, "fail to read value from input stream");
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, "read\n", v);
#endif
  return v;
}
template <class... Ts> std::tuple<Ts...> read_tuple(std::istream &is) {
  std::tuple<Ts...> v;
  is >> v;
  throw_if(!is, "fail to read value from input stream");
#ifdef JUMPAKU_DEBUG
  std::apply(
      [&](auto... vs) { print_impl(std::cerr, "\nread_tuple:\n\t", vs...); },
      v);
#endif
  return v;
}
template <class E> std::vector<E> read_vec(int n0, std::istream &is) {
  std::vector<E> V(n0);
  is >> V;
  throw_if(!is, "fail to read value from input stream");
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, "\nread_vec:\n\t", V);
#endif
  return V;
}
template <class E>
std::vector<std::vector<E>> read_vec(int n0, int n1, std::istream &is) {
  std::vector<std::vector<E>> V(n0, std::vector<E>(n1));
  is >> V;
  throw_if(!is, "fail to read value from input stream");
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, "\nread_vec:\n\t", V);
#endif
  return V;
}
template <class E>
std::vector<std::vector<std::vector<E>>> read_vec(int n0, int n1, int n2,
                                                  std::istream &is) {
  std::vector<std::vector<std::vector<E>>> V(
      n0, std::vector<std::vector<E>>(n1, std::vector<E>(n2)));
  is >> V;
  throw_if(!is, "fail to read value from input stream");
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, "\nread_vec:\n\t", V);
#endif
  return V;
}

// Print
void print_impl(std::ostream &os) {}
template <class T, class... Ts>
void print_impl(std::ostream &os, T v, Ts... vs) {
  os << v;
  using swallow = std::initializer_list<int>;
  (void)swallow{(void(os << " " << vs), 0)...};
  os << "\n";
}
template <class... Ts> void print(Ts... vs) {
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, "\nprint:");
#endif
  print_impl(std::cout, vs...);
}
template <class... Ts> void dump(Ts const &...vs) {
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, "\ndump:\n\t", vs...);
#endif
}

// Utils
template <class T> str to_string(T n) {
  std::stringstream ss;
  ss << n;
  return ss.str();
}
template <class T> T from_string(str s) {
  T v;
  std::stringstream ss(s);
  ss >> v;
  return v;
}
ll sign(ll x) { return (x < 0) ? -1 : (x > 0) ? 1 : 0; }
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
ll floor_div(ll a, ll b);
ll ceil_div(ll a, ll b);
ll floor_div(ll a, ll b) {
  throw_if(b == 0, "Division by 0");

  if (b < 0)
    return floor_div(-a, -b);
  if (a < 0)
    return -ceil_div(-a, b);
  return a / b;
}
ll ceil_div(ll a, ll b) {
  throw_if(b == 0, "Division by 0");

  if (b < 0)
    return ceil_div(-a, -b);
  if (a < 0)
    return -floor_div(-a, b);
  return (a + b - 1) / b;
}

// Hashes
namespace std {
template <class... Ts> struct hash<tuple<Ts...>> {
  size_t operator()(tuple<Ts...> const &t) const {
    return std::apply(
        [&](auto const &...vs) {
          size_t h = 17;
          using swallow = std::initializer_list<int>;
          (void)swallow{
              (void(h = ((h << 8) - h) ^ std::hash<decltype(vs)>{}(vs)), 0)...};
          return h ^ (h >> 32);
        },
        t);
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
template <class T> struct hash<vec<T>> {
  size_t operator()(vec<T> const &t) const {
    constexpr std::hash<T> hasher;
    auto h =
        accumulate(t.begin(), t.end(), (size_t)17, [&](auto h, auto const &ti) {
          return ((h << 5) - h) ^ hasher(ti);
        });
    return h ^ (h >> 32);
  }
};
} // namespace std

// Range
template <class F> struct seq : public std::ranges::view_base {
  using T = std::invoke_result_t<F, ll>;
  struct iterator {
    using difference_type = ll;
    using value_type = T;
    using pointer = T *;
    using reference = T &;
    using iterator_category = std::random_access_iterator_tag;
    iterator(seq<F> *s = nullptr, ll i = 0) : i(i), s(s) {}
    iterator(iterator const &) = default;
    iterator(iterator &&) = default;
    iterator &operator=(iterator const &) = default;
    iterator &operator=(iterator &&) = default;
    T operator*() const { return s->f(i); }
    iterator &operator++() { return ++i, *this; }
    iterator operator++(int) { return iterator(s, i++); }
    iterator &operator--() { return --i, *this; }
    iterator operator--(int) { return iterator(s, i--); }
    iterator &operator+=(ll n) { return i += n, *this; }
    iterator &operator-=(ll n) { return i -= n, *this; }
    iterator operator+(ll n) const { return iterator(s, i + n); }
    iterator operator-(ll n) const { return iterator(s, i - n); }
    T operator[](ll n) const { return s->f(i + n); }
    ll operator-(iterator other) const { return i - other.i; }
    ll operator<(iterator other) const { return i < other.i; }
    ll operator<=(iterator other) const { return i <= other.i; }
    ll operator>(iterator other) const { return i > other.i; }
    ll operator>=(iterator other) const { return i >= other.i; }
    bool operator==(iterator const &other) const { return i == other.i; }
    bool operator!=(iterator const &other) const { return i != other.i; }
    ll i;
    seq<F> *s;
  };
  seq(ll size, F f) : f(f), sz(size) {}
  seq(seq<F> const &) = default;
  seq(seq<F> &&) = default;
  seq<F> &operator=(seq<F> const &) = default;
  seq<F> &operator=(seq<F> &&) = default;
  ll size() const { return max(ll(0), sz); }
  bool empty() const { return size() == 0; }
  T operator[](ll n) const { return f(n); }
  operator bool() const { return !empty(); }
  iterator begin() { return iterator(this, 0); }
  iterator end() { return iterator(this, size()); }
  F f;
  ll sz;
};

struct range : public std::ranges::view_base {
  struct iterator {
    using difference_type = ll;
    using value_type = ll;
    using pointer = ll *;
    using reference = ll &;
    using iterator_category = std::random_access_iterator_tag;
    explicit iterator(ll i = 0) : i(i) {}
    iterator(iterator const &) = default;
    iterator(iterator &&) = default;
    iterator &operator=(iterator const &) = default;
    iterator &operator=(iterator &&) = default;
    ll operator*() const { return i; }
    iterator &operator++() { return ++i, *this; }
    iterator operator++(int) { return iterator(i++); }
    iterator &operator--() { return --i, *this; }
    iterator operator--(int) { return iterator(i--); }
    iterator &operator+=(ll n) { return i += n, *this; }
    iterator &operator-=(ll n) { return i -= n, *this; }
    iterator operator+(ll n) const { return iterator(i + n); }
    iterator operator-(ll n) const { return iterator(i - n); }
    ll operator[](ll n) const { return i + n; }
    ll operator-(iterator other) const { return i - other.i; }
    ll operator<(iterator other) const { return i < other.i; }
    ll operator<=(iterator other) const { return i <= other.i; }
    ll operator>(iterator other) const { return i > other.i; }
    ll operator>=(iterator other) const { return i >= other.i; }
    bool operator==(iterator const &other) const { return i == other.i; }
    bool operator!=(iterator const &other) const { return i != other.i; }
    ll i;
  };
  explicit range(ll size) : b(0), e(size) {}
  range(ll begin, ll end) : b(begin), e(end) {}
  range(range const &) = default;
  range(range &&) = default;
  range &operator=(range const &) = default;
  range &operator=(range &&) = default;
  ll size() const { return max(ll(0), e - b); }
  bool empty() const { return size() == 0; }
  ll operator[](ll n) const { return b + n; }
  operator bool() const { return !empty(); }
  iterator begin() { return iterator(b); }
  iterator end() { return iterator(e); }
  bool has(ll n) const { return b <= n && n < e; }
  ll front() const { return b; }
  ll back() const { return e; }
  ll b;
  ll e;
};

#include <chrono>
class stopwatch {
#ifdef JUMPAKU_DEBUG
  using Clock = std::chrono::high_resolution_clock;
  bool isRunning;
  Clock::duration total_duration;
  Clock::time_point last_lap;

public:
  stopwatch() : isRunning(false), total_duration(std::chrono::nanoseconds{0}){};
  void start() {
    auto current = Clock::now();
    if (isRunning)
      return;
    isRunning = true;
    last_lap = current;
  }
  void stop() {
    auto current = Clock::now();
    if (!isRunning)
      return;
    isRunning = false;
    total_duration += current - last_lap;
  }
  double lap() {
    auto current = Clock::now();
    if (isRunning) {
      total_duration += current - last_lap;
      last_lap = current;
    }
    return 1e-9 *
           std::chrono::duration_cast<std::chrono::nanoseconds>(total_duration)
               .count();
  }
#else
public:
  void start() {}
  void stop() {}
  double lap() { return 0.0; }
#endif
};

/*
void f(int x){
  if ( x <= 0) return;
  static rec_dump_t rec_dump;
  rec_dump_raii raii(rec_dump);
  rec_dump(x);
  f(--x);
}
*/
struct rec_dump_t {
  str indent = "|";
  template <class... Ts> void operator()(Ts const &...a) {
#ifdef JUMPAKU_DEBUG
    print_impl(std::cerr, indent, a...);
#endif
  }
  template <class... Ts> void dump(Ts const &...a) {
#ifdef JUMPAKU_DEBUG
    print_impl(std::cerr, indent, a...);
#endif
  }
};
struct rec_dump_raii {
  rec_dump_t &obj;
  rec_dump_raii(rec_dump_t &obj) : obj(obj) {
#ifdef JUMPAKU_DEBUG
    obj.indent.back() = '-';
    obj.indent.push_back('|');
    obj("entry");
#endif
  }
  ~rec_dump_raii() {
#ifdef JUMPAKU_DEBUG
    obj("return");
    obj.indent.pop_back();
    obj.indent.back() = '|';
#endif
  }
};

constexpr f64 PI = 3.141592653589793238462643383279502884L;

template <class F> void debug_run(F const &f) {
#ifdef JUMPAKU_DEBUG
  f();
#endif
}
