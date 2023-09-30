#pragma once

#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

// Concepts
template <class C>
concept Iterable = requires(C c) {
                     std::begin(std::declval<C>());
                     std::end(std::declval<C>());
                   };

// ----- Declarations -----

// Init
void init_io();

// Read
template <class T> T read(std::istream &is = std::cin);
template <class... Ts> std::tuple<Ts...> read_t(std::istream &is = std::cin);
template <class E> std::vector<E> read_v(int n0, std::istream &is = std::cin);
template <class E>
std::vector<std::vector<E>> read_v(int n0, int n1, std::istream &is = std::cin);
template <class E>
std::vector<std::vector<std::vector<E>>> read_v(int n0, int n1, int n2,
                                                std::istream &is = std::cin);

// Scanners
std::istream &operator>>(std::istream &is, __int128_t &v);
template <class E>
std::istream &operator>>(std::istream &is, std::vector<E> &v);
template <class T1, class T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &v);
template <class... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &v);

// Print
template <class... Ts> void print_impl(std::ostream &os, Ts... vs);
template <class... Ts> void print(Ts... vs);

template <class... Ts> void dump(Ts const &...vs);
template <class File, class Line, class... Ts>
void dump_vars_impl(File file, Line line, Ts... vs);
template <class V> std::string VAR_FMT(std::string s, V v);
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

// Printers
std::ostream &operator<<(std::ostream &os, __int128_t v);
template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, std::pair<T1, T2> v);
std::ostream &operator<<(std::ostream &os, std::tuple<>);
template <class T0, class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<T0, Ts...> v);
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

template <class E> struct Joiner;
template <class Itr>
Joiner<typename std::iterator_traits<Itr>::value_type>
join(Itr const &b, Itr const &e, std::string const &sep, std::string const &pre,
     std::string const &post);
template <class E> std::ostream &operator<<(std::ostream &os, Joiner<E> v);

// ----- Definitions -----

// Read
template <class T> T read(std::istream &is) {
  T v;
  is >> v;
  expect(is, "fail to read value from input stream");
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, "read\n", v);
#endif
  return v;
}
template <class... Ts> std::tuple<Ts...> read_t(std::istream &is) {
  std::tuple<Ts...> v;
  is >> v;
  expect(is, "fail to read value from input stream");
#ifdef JUMPAKU_DEBUG
  std::apply([&](auto... vs) { print_impl(std::cerr, "read_t\n", vs...); }, v);
#endif
  return v;
}
template <class E> std::vector<E> read_v(std::istream &is, int n0) {
  std::vector<E> V(n0);
  is >> V;
  expect(is, "fail to read value from input stream");
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, "read_v\n", V);
#endif
  return V;
}
template <class E>
std::vector<std::vector<E>> read_v(std::istream &is, int n0, int n1) {
  std::vector<std::vector<E>> V(n0, std::vector<E>(n1));
  is >> V;
  expect(is, "fail to read value from input stream");
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, "read_v\n", V);
#endif
  return V;
}
template <class E>
std::vector<std::vector<std::vector<E>>> read_v(std::istream &is, int n0,
                                                int n1, int n2) {
  std::vector<std::vector<std::vector<E>>> V(
      n0, std::vector<std::vector<E>>(n1, std::vector<E>(n2)));
  is >> V;
  expect(is, "fail to read value from input stream");
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, "read_v\n", V);
#endif
  return V;
}

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

// Print
template <class V> std::string VAR_FMT(std::string s, V v) {
  std::stringstream ss;
  ss << s << "=" << v;
  return ss.str();
}
template <class File, class Line, class... Ts>
void dump_vars_impl(File file, Line line, Ts... vs) {
  std::cerr << "dump_vars " << file << ":" << line << "\n";
  using swallow = std::initializer_list<int>;
  (void)swallow{(void(std::cerr << " " << vs), 0)...};
  std::cerr << std::endl;
}
template <class... Ts> void print_impl(std::ostream &os, Ts... vs) {
  using swallow = std::initializer_list<int>;
  (void)swallow{(void(os << vs << " "), 0)...};
  std::cerr << std::endl;
}
template <class... Ts> void print(Ts... vs) { print_impl(std::cout, vs...); }

template <class... Ts> void dump(Ts const &...vs) {
#ifdef JUMPAKU_DEBUG
  print_impl(std::cerr, vs...);
#endif
}

// Printers
template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, std::pair<T1, T2> v) {
  return os << v.first << ":" << v.second;
}
std::ostream &operator<<(std::ostream &os, std::tuple<>) { return os << "()"; }
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

// ----- CPP -----

// Init
void init_io() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);
  std::cout << std::fixed << std::setprecision(15);
}

std::istream &operator>>(std::istream &i, __int128 &x) {
  long long int xx;
  i >> xx;
  x = xx;
  return i;
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