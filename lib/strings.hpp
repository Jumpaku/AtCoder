/**
 * STRINGS
 */

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#endif

namespace strings {

str format_with_base(ll v, ll b) {
  if (v == 0)
    return "0";
  str res;
  while (v > 0) {
    res += char('0' + v % b);
    v /= b;
  }
  std::reverse(res.begin(), res.end());
  return res;
}
ll parse_with_base(str s, ll b) {
  ll res = 0;
  for (char c : s) {
    throw_if(c < '0' || c >= '0' + b, "Invalid character in base conversion");
    res = res * b + (c - '0');
  }
  return res;
}

bool is_palindrome(str s) {
  auto n = s.size();
  for (auto i : range(n / 2)) {
    if (s[i] != s[n - i - 1])
      return false;
  }
  return true;
}

} // namespace strings
using strings::format_with_base;
using strings::is_palindrome;
using strings::parse_with_base;
/* end of STRINGS */
