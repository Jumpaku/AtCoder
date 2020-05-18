#include "../template.hpp"

/**
 * MOD
 */
namespace mod {
ll pow(ll a, ll n, ll m) {
  if (n == 0)
    return 1;
  if (n & 1)
    return ((a % m) * pow(a, n - 1, m)) % m;
  auto b = pow(a, n / 2, m);
  return (b * b) % m;
}
ll inv(ll a, ll p) { return pow(a, p - 2, p); }
template <ll N, ll M> struct Factrial {
  Factrial() : fact(N + 1), finv(N + 1) {
    fact[0] = 1;
    for (int i = 1; i <= N; ++i)
      fact[i] = (fact[i - 1] * i) % M;
    finv[N] = inv(fact[N], M);
    for (int i = N; i > 0; --i)
      finv[i - 1] = (finv[i] * i) % M;
  }
  vecl fact;
  vecl finv;
  ll comb(ll n, ll m) const {
    if (m < 0 || n < m)
      return 0LL;
    return (fact[n] * ((finv[m] * finv[n - m]) % M)) % M;
  }
};
} // namespace mod
using mod::Factrial, mod::inv, mod::pow;
/* end of MOD */