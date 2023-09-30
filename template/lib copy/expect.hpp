#pragma once
#include <boost/stacktrace.hpp>
#include <sstream>
#include <string>
// Assertion
#define expect(expr, msg)                                                      \
  [&](bool ok) {                                                               \
    if (!ok)                                                                   \
      expect_impl(#expr, __FILE__, __LINE__, msg);                             \
  }(static_cast<bool>(expr))

template <class Expr, class File, class Line>
void expect_impl(Expr const &expr, File const &file, Line const &line,
                 std::string const &msg);

// ----- Definitions -----
template <class Expr, class File, class Line>
void expect_impl(Expr const &expr, File const &file, Line const &line,
                 std::string const &msg) {
  std::stringstream ss;
  ss << "expect_fail: " << file << ":" << line << ":\n " << msg << ": " << expr
     << "\n"
     << boost::stacktrace::stacktrace();

  throw std::runtime_error(ss.str());
}
