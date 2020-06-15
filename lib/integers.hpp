#ifndef TEMPLATE_HPP
#include "../template.hpp"
#endif

/**
 * INTEGERS
 */
namespace integers {
using longlong = long long;
// O(N*log(log(N))), log(N)
vec<int> createPrimes(int const &M) {
  vec<bool> isPrime(M + 1, true);
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i * i <= M; ++i) {
    if (isPrime[i]) {
      for (longlong j = i * 2; j <= M; j += i) {
        isPrime[j] = false;
      }
    }
  }
  vec<int> primes;
  for (int i = 0; i < isPrime.size(); ++i) {
    if (isPrime[i])
      primes.push_back(i);
  }
  return primes;
}

// N=1e12 => sqrt(N) -> 1e6, 2^{log_{10}(N)} -> 4e3
vec<longlong> createFactors(longlong const &N) {
  vec<longlong> factors;
  for (longlong i = 1; i * i <= N; i++) {
    if (N % i == 0) {
      factors.push_back(i);
      if (i != N / i)
        factors.push_back(N / i);
    }
  }
  return factors;
}

u_map<longlong, longlong> primeFactorize(longlong const &N) {
  longlong n = N;
  u_map<longlong, longlong> result;
  for (longlong i = 2; i <= n; i++) {
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
using integers::createFactors;
using integers::createPrimes;
using integers::primeFactorize;
/* end of INTEGERS */
