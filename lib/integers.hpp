/**
 * INTEGERS
 */

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
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
ll countMultiples(ll b, ll e, ll K) { return f(b, e - 1, K); }

/**
 * nCkの計算
 */
ll countCombinations(ll const n, ll const k) {
  if (k < 0 || k > n)
    return 0;
  if (k == n || k == 0)
    return 1;
  if (n == 1)
    return 1;
  if (k > n - k)
    return countCombinations(n, n - k);
  ll ans = n - k + 1;
  for (ll i = 1; i < k; ++i) {
    ans = ans * (n - k + 1 + i) / (i + 1);
  }
  return ans;
}
/**
 * nPkの計算
 */
ll countPermutations(ll const n, ll const k) {
  if (k < 0 || k > n)
    return 0;
  ll ans = n;
  for (ll i = 0; i < k; ++i)
    ans *= n - i;
  return ans;
}

// O(N*log(log(N))), log(N)
vec<int> createPrimes(int const &M) {
  vec<bool> isPrime(M + 1, true);
  isPrime[0] = isPrime[1] = false;
  for (int i = 2; i * i <= M; ++i) {
    if (isPrime[i]) {
      for (int j = i * 2; j <= M; j += i) {
        isPrime[j] = false;
      }
    }
  }
  vec<int> primes;
  auto r = range(2, M + 1);
  copy_if(r.begin(), r.end(), back_inserter(primes),
          [&](auto const &i) { return isPrime[i]; });
  return primes;
}

using longlong = long long;

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

u_map<longlong, longlong> primeFactorize(longlong N) {
  u_map<longlong, longlong> res;
  for (long long a = 2; a * a <= N; ++a) {
    if (N % a != 0)
      continue;
    long long ex = 0; // 指数

    // 割れる限り割り続ける
    while (N % a == 0) {
      ++ex;
      N /= a;
    }

    // その結果を push
    res[a] = ex;
  }

  // 最後に残った数について
  if (N != 1)
    res[N] = 1;
  return res;
}

uint16_t bases[] = {
    15591, 2018,  166,   7429,  8064,  16045, 10503, 4399,  1949,  1295, 2776,
    3620,  560,   3128,  5212,  2657,  2300,  2021,  4652,  1471,  9336, 4018,
    2398,  20462, 10277, 8028,  2213,  6219,  620,   3763,  4852,  5012, 3185,
    1333,  6227,  5298,  1074,  2391,  5113,  7061,  803,   1269,  3875, 422,
    751,   580,   4729,  10239, 746,   2951,  556,   2206,  3778,  481,  1522,
    3476,  481,   2487,  3266,  5633,  488,   3373,  6441,  3344,  17,   15105,
    1490,  4154,  2036,  1882,  1813,  467,   3307,  14042, 6371,  658,  1005,
    903,   737,   1887,  7447,  1888,  2848,  1784,  7559,  3400,  951,  13969,
    4304,  177,   41,    19875, 3110,  13221, 8726,  571,   7043,  6943, 1199,
    352,   6435,  165,   1169,  3315,  978,   233,   3003,  2562,  2994, 10587,
    10030, 2377,  1902,  5354,  4447,  1555,  263,   27027, 2283,  305,  669,
    1912,  601,   6186,  429,   1930,  14873, 1784,  1661,  524,   3577, 236,
    2360,  6146,  2850,  55637, 1753,  4178,  8466,  222,   2579,  2743, 2031,
    2226,  2276,  374,   2132,  813,   23788, 1610,  4422,  5159,  1725, 3597,
    3366,  14336, 579,   165,   1375,  10018, 12616, 9816,  1371,  536,  1867,
    10864, 857,   2206,  5788,  434,   8085,  17618, 727,   3639,  1595, 4944,
    2129,  2029,  8195,  8344,  6232,  9183,  8126,  1870,  3296,  7455, 8947,
    25017, 541,   19115, 368,   566,   5674,  411,   522,   1027,  8215, 2050,
    6544,  10049, 614,   774,   2333,  3007,  35201, 4706,  1152,  1785, 1028,
    1540,  3743,  493,   4474,  2521,  26845, 8354,  864,   18915, 5465, 2447,
    42,    4511,  1660,  166,   1249,  6259,  2553,  304,   272,   7286, 73,
    6554,  899,   2816,  5197,  13330, 7054,  2818,  3199,  811,   922,  350,
    7514,  4452,  3449,  2663,  4708,  418,   1621,  1171,  3471,  88,   11345,
    412,   1559,  194};
bool is_SPRP(uint32_t n, uint32_t a) {
  uint32_t d = n - 1, s = 0;
  while ((d & 1) == 0)
    ++s, d >>= 1;
  uint64_t cur = 1, pw = d;
  while (pw) {
    if (pw & 1)
      cur = (cur * a) % n;
    a = ((uint64_t)a * a) % n;
    pw >>= 1;
  }
  if (cur == 1)
    return true;
  for (uint32_t r = 0; r < s; r++) {
    if (cur == n - 1)
      return true;
    cur = (cur * cur) % n;
  }
  return false;
}
bool is_prime32(uint32_t x) {
  if (x == 2 || x == 3 || x == 5 || x == 7)
    return true;
  if (x % 2 == 0 || x % 3 == 0 || x % 5 == 0 || x % 7 == 0)
    return false;
  if (x < 121)
    return (x > 1);
  uint64_t h = x;
  h = ((h >> 16) ^ h) * 0x45d9f3b;
  h = ((h >> 16) ^ h) * 0x45d9f3b;
  h = ((h >> 16) ^ h) & 255;
  return is_SPRP(x, bases[h]);
}
} // namespace integers
using integers::countMultiples;
using integers::createFactors;
using integers::createPrimes;
using integers::is_prime32;
using integers::primeFactorize;
/* end of INTEGERS */
