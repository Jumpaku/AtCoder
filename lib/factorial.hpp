/**
 * Factorial
 */
#ifndef JUMPAKU_FACTORIAL_HPP
#define JUMPAKU_FACTORIAL_HPP

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#include "atcoder.hpp"
#endif

namespace factorial {

// Factorial<atcoder::modint_static<>> f(1e6);
template <class ModInt> struct Factorial {
  Factorial(int N) : fact(N + 1), finv(N + 1) {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i)
      fact[i] = (fact[i - 1] * i);
    finv[N] = fact[N].inv();
    for (int i = N; i > 0; --i)
      finv[i - 1] = (finv[i] * i);
  }
  vec<ModInt> fact;
  vec<ModInt> finv;
  int comb(int n, int m) const {
    if (m < 0 || n < m)
      return 0;
    return (fact[n] * finv[m] * finv[n - m]).val();
  }
  int comb_with_repetition(int n, int m) const { return comb(n + m - 1, m); }
  int perm(int n, int m) const {
    if (m < 0 || n < m)
      return 0;
    return (fact[n] * finv[n - m]).val();
  }
};
} // namespace factorial

using factorial::Factorial;
#endif
/* end of Factorial */