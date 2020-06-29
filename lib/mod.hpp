#ifndef TEMPLATE_HPP
#include "../template.hpp"
#endif

/**
 * MOD
 */
namespace mod {
using longlong = long long;

longlong pow(longlong a, longlong n, longlong m) {
  if (n == 0)
    return 1;
  if (n & 1)
    return ((a % m) * pow(a, n - 1, m)) % m;
  auto b = pow(a, n / 2, m);
  return (b * b) % m;
}
longlong inv(longlong a, longlong p) { return pow(a, p - 2, p); }

struct ModCache {
  ModCache(int N, longlong mod) : M(mod), fact(N + 1), finv(N + 1) {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i)
      fact[i] = (fact[i - 1] * i) % M;
    finv[N] = inv(fact[N], M);
    for (int i = N; i > 0; --i)
      finv[i - 1] = (finv[i] * i) % M;
  }
  longlong const M;
  vec<longlong> fact;
  vec<longlong> finv;
  longlong comb(longlong n, longlong m) const {
    if (m < 0 || n < m)
      return 0;
    return (fact[n] * ((finv[m] * finv[n - m]) % M)) % M;
  }
  longlong perm(longlong n, longlong m) const {
    if (m < 0 || n < m)
      return 0;
    return (fact[n] * finv[n - m]) % M;
  }
};
} // namespace mod
using mod::inv;
using mod::ModCache;
using mod::pow;
/* end of MOD */