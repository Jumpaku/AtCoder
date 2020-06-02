#ifndef TEMPLATE_HPP
#include "../template.hpp"
#endif

/**
 * INTEGERS
 */
namespace integers {
// O(N*log(log(N))), log(N)
vecl createPrimes(ll const &M) {
  vec<bool> isPrime(M + 1, true);
  isPrime[0] = isPrime[1] = false;
  for (ll i = 2; i * i <= M; ++i) {
    if (isPrime[i]) {
      for (ll j = i * 2; j <= M; j += i) {
        isPrime[j] = false;
      }
    }
  }
  vecl primes;
  for (auto &&i : range(isPrime.size())) {
    if (isPrime[i])
      primes.push_back(i);
  }
  return primes;
}

// N=1e12 => sqrt(N) -> 1e6, 2^{log_{10}(N)} -> 4e3
vecl createFactors(ll const &N) {
  vecl factors;
  for (ll i = 1; i * i <= N; i++) {
    if (N % i == 0) {
      factors.push_back(i);
      if (i != N / i)
        factors.push_back(N / i);
    }
  }
  return factors;
}

u_map<ll, ll> primeFactorize(ll const &N) {
  ll n = N;
  u_map<ll, ll> result;
  for (ll i = 2; i <= n; i++) {
    while (n % i == 0) {
      ++result[i];
      n /= i;
    }
  }
  if (n != 1)
    result[n]++;
  return result;
}
} // namespace integers
using integers::createPrimes, integers::createFactors, integers::primeFactorize;
/* end of INTEGERS */
