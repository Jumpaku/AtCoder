/**
 * DP
 */
#ifndef JUMPAKU_DP_HPP
#define JUMPAKU_DP_HPP

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

namespace dp {

template <class Key, class Val> struct ICache {
  virtual tuple<Val const &, bool> get(Key const &key) const = 0;
  virtual void set(Key const &key, Val const &val) = 0;
};
template <class Key, class Val> struct CacheU : ICache<Key, Val> {
  u_map<Key, Val> cache;
  CacheU() : cache(2e6) {}
  tuple<Val const &, bool> get(Key const &key) const override {
    auto found = this->cache.find(key);
    return found != cache.end() ? tuple<Val const &, bool>(found->second, true)
                                : tuple<Val const &, bool>(Val{}, false);
  }
  void set(Key const &key, Val const &val) override { this->cache[key] = val; }
};
template <class Val> struct CacheV1 : ICache<tuple<ll>, Val> {
  using Key = tuple<ll>;
  CacheV1(ll n) : cache(n), cached(n) {}
  vec<Val> cache;
  vec<bool> cached;
  tuple<Val const &, bool> get(Key const &key) const override {
    auto const &[i] = key;
    return tuple<Val const &, bool>(cached[i], cache[i]);
  }
  void set(Key const &key, Val const &val) override {
    auto const &[i] = key;
    this->cache[i] = val;
    this->cached[i] = true;
  }
};
template <class Val> struct CacheV2 : ICache<tuple<ll, ll>, Val> {
  using Key = tuple<ll, ll>;
  CacheV2(ll n0, ll n1) : cache(n0, vec<Val>(n1)), cached(n0, vec<bool>(n1)) {}
  vec<vec<Val>> cache;
  vec<vec<bool>> cached;
  tuple<Val const &, bool> get(Key const &key) const override {
    auto const &[i, j] = key;
    return tuple<Val const &, bool>(cached[i][j], cache[i][j]);
  }
  void set(Key const &key, Val const &val) override {
    auto const &[i, j] = key;
    this->cache[i][j] = val;
    this->cached[i][j] = true;
  }
}; // namespace dp
template <class Val> struct CacheV3 : ICache<tuple<ll, ll, ll>, Val> {
  using Key = tuple<ll, ll, ll>;
  CacheV3(ll n0, ll n1, ll n2)
      : cache(n0, vec<vec<Val>>(n1, vec<Val>(n2))),
        cached(n0, vec<vec<bool>>(n1, vec<bool>(n2))) {}
  vec<vec<vec<Val>>> cache;
  vec<vec<vec<bool>>> cached;
  tuple<Val const &, bool> get(Key const &key) const override {
    auto const &[i, j, k] = key;
    return tuple<Val const &, bool>(cached[i][j][k], cache[i][j][k]);
  }
  void set(Key const &key, Val const &val) override {
    auto const &[i, j, k] = key;
    this->cache[i][j][k] = val;
    this->cached[i][j][k] = true;
  }
};

} // namespace dp
using dp::CacheU;
using dp::CacheV1;
using dp::CacheV2;
using dp::CacheV3;

#endif
/* end of DP */

/**
using Key;
using Val;
using Cache;
using Data;
struct DP {
  DP(Data data, Cache cache) : data(data), cache(cache) {}
  Data data;
  Cache cache;
  // define dp by following function
  Val f(Key const &key) {
    // base case
    return Val();
    // use cached ans
    if (auto const &[ans, ok] = cache.get(key); ok) {
      return ans;
    }
    // compute recursively
    Val ans;
    // cache ans
    cache.set(key, ans);
    return ans;
  }
};
//*/