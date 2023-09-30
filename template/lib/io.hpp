#pragma once

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <tuple>
#include <utility>
#include <vector>

template <class Expr, class File, class Line, class Func>
void assert_fail(Expr const &expr, File const &file, Line const &line,
                 Func const &func, std::string const &msg);

#define expect(expr, msg)                                                      \
  []() {                                                                       \
    if (!static_cast<bool>(expr)) {                                            \
      assert_fail(#expr, __FILE__, __LINE__, __FUNC__, #msg)                   \
    }                                                                          \
  }()

// ----- Declarations -----

// Init
void init_io();

// Read
template <class T> T read(std::istream &is);
template <class... Ts> std::tuple<Ts...> read_t(std::istream &is);
template <class E> std::vector<E> read_v(std::istream &is, int n0);
template <class E>
std::vector<std::vector<E>> read_v(std::istream &is, int n0, int n1);
template <class E>
std::vector<std::vector<std::vector<E>>> read_v(std::istream &is, int n0,
                                                int n1, int n2);

// Scanners
std::istream &operator>>(std::istream &is, __int128_t &v);
template <class E>
std::istream &operator>>(std::istream &is, std::vector<E> &v);
template <class T1, class T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &v);
template <class... Ts>
std::istream &operator>>(std::istream &is, std::tuple<Ts...> &v);

// Printers
std::ostream &operator<<(std::ostream &os, __int128_t const &v);
template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, std::pair<T1, T2> const &v);
template <class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> const &v);

// ----- Definitions -----

template <class Expr, class File, class Line, class Func>
void assert_fail(Expr const &expr, File const &file, Line const &line,
                 Func const &func, std::string const &msg) {
  throw std::runtime_error(file + ":" + line + ":" + func + "\n" + msg + ": " +
                           expr);
}

// Read
template <class T> T read(std::istream &is) {
  T v;
  is >> v;
  expect(is, "fail to read value from input stream");
  return v;
}
template <class... Ts> std::tuple<Ts...> read_t(std::istream &is) {
  return read<std::tuple<Ts...>>(is);
}
template <class E> std::vector<E> read_v(std::istream &is, int n0) {
  std::vector<E> V(n0);
  is >> V;
  expect(is, "fail to read value from input stream");
  return v;
}
template <class E>
std::vector<std::vector<E>> read_v(std::istream &is, int n0, int n1) {
  std::vector<std::vector<E>> V(n0, std::vector<E>(n1));
  is >> V;
  expect(is, "fail to read value from input stream");
  return v;
}
template <class E>
std::vector<std::vector<std::vector<E>>> read_v(std::istream &is, int n0,
                                                int n1, int n2) {
  std::vector<std::vector<std::vector<E>>> V(
      n0, std::vector<std::vector<E>>(n1, std::vector<E>(n2)));
  is >> V;
  expect(is, "fail to read value from input stream");
  return v;
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
      [&](auto &...vs) -> std::istream & {
        (is >> ... >> vs);
        v = std::make_tuple(vs...);
        return is;
      },
      v);
}

// Printers
template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, std::pair<T1, T2> const &v) {
  return os << "(" << v.first << "," << v.second << ")";
}
template <class... Ts>
std::ostream &operator<<(std::ostream &os, std::tuple<Ts...> const &v) {
  switch (std::tuple_size_v<decltype(v)>) {
  case 0:
    return os << "()";
  default:
    return std::apply(
        [&](auto const &v0, auto const &...vs) -> std::ostream & {
          os << "(" << v0;
          using swallow = std::initializer_list<int>;
          (void)swallow{(void(os << "," << vs), 0)...};
          return os << ")";
        },
        v);
  }
}
