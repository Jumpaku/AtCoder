/**
 * INTEGERS
 */
#ifndef JUMPAKU_MOD_HPP
#define JUMPAKU_MOD_HPP

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#include "atcoder.hpp"
#endif

namespace integers {

ll g(ll l, ll r, ll K) {
  //(l>=0,r]にあるKの倍数
  return r / K - l / K;
}

ll f(ll l, ll r, ll K) {
  //[l,r]にあるKの倍数
  if (r < 0)
    return g(-r - 1, -l, K);
  if (l > 0)
    return g(l - 1, r, K);
  return g(0, r, K) + g(0, -l, K) + 1;
}
/**
 * [A, B)内のKの倍数の個数
 */
ll countMultiplesIn(ll A, ll B, ll K) { return f(A, B - 1, K); }
} // namespace integers

using integers::countMultiplesIn;
#endif
/* end of INTEGERS */