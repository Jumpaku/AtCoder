#pragma once

#include "io.hpp"

// Init
void init_io() {}

std::istream &operator>>(std::istream &i, __int128 &x) {
  long long int xx;
  i >> xx;
  x = xx;
  return i;
}
std::ostream &operator<<(std::ostream &os, __int128_t const &v) {
  if (v >= 1000000000000000000) {
    os << (long long)(v / 1000000000000000000)
       << (long long)(v % 1000000000000000000);
  } else {
    os << (long long)v;
  }
  return os;
}