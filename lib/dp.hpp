/**
 * DP
 */
#ifndef JUMPAKU_DP_HPP
#define JUMPAKU_DP_HPP

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#endif

#include <memory>
namespace dp {

template <class Val> using Ptr = std::shared_ptr<Val>;
template <class Val> using GetReturn = tuple<Ptr<Val>, bool>;
template <class Key, class Val> struct ICache {
  virtual GetReturn<Val> get(Key const &key) const = 0;
  virtual void set(Key const &key, Val const &val) = 0;
};
template <class Key, class Val> struct CacheU : ICache<Key, Val> {
  u_map<Key, Ptr<Val>> cache;
  CacheU() : cache(2e6) {}
  GetReturn<Val> get(Key const &key) const override {
    auto found = this->cache.find(key);
    return found != cache.end() ? GetReturn<Val>(found->second, true)
                                : GetReturn<Val>(nullptr, false);
  }
  void set(Key const &key, Val const &val) override {
    this->cache[key] = std::make_shared<Val>(val);
  }
};
template <class Val> struct CacheV1 : ICache<tuple<ll>, Val> {
  using Key = tuple<ll>;
  CacheV1(ll n) : cache(n) {}
  vec<Ptr<Val>> cache;
  GetReturn<Val> get(Key const &key) const override {
    auto const &[i] = key;
    return GetReturn<Val>(cache[i], cache[i] != nullptr);
  }
  void set(Key const &key, Val const &val) override {
    auto const &[i] = key;
    this->cache[i] = std::make_shared<Val>(val);
  }
};
template <class Val> struct CacheV2 : ICache<tuple<ll, ll>, Val> {
  using Key = tuple<ll, ll>;
  CacheV2(ll n0, ll n1) : cache(n0, vec<Ptr<Val>>(n1)) {}
  vec<vec<Ptr<Val>>> cache;
  GetReturn<Val> get(Key const &key) const override {
    auto const &[i, j] = key;
    return GetReturn<Val>(cache[i][j], cache[i][j] != nullptr);
  }
  void set(Key const &key, Val const &val) override {
    auto const &[i, j] = key;
    this->cache[i][j] = std::make_shared<Val>(val);
  }
}; // namespace dp
template <class Val> struct CacheV3 : ICache<tuple<ll, ll, ll>, Val> {
  using Key = tuple<ll, ll, ll>;
  CacheV3(ll n0, ll n1, ll n2)
      : cache(n0, vec<vec<Ptr<Val>>>(n1, vec<Ptr<Val>>(n2))) {}
  vec<vec<vec<Ptr<Val>>>> cache;
  GetReturn<Val> get(Key const &key) const override {
    auto const &[i, j, k] = key;
    return GetReturn<Val>(cache[i][j][k], cache[i][j][k] != nullptr);
  }
  void set(Key const &key, Val const &val) override {
    auto const &[i, j, k] = key;
    this->cache[i][j][k] = std::make_shared<Val>(val);
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
using Key = tuple<ll>;
using Val = ll;
using Cache = CacheU<Key, Val>;
using Data = struct {};
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
      return *ans;
    }
    // compute recursively
    Val ans;
    // cache ans
    cache.set(key, ans);
    return ans;
  }
};
//*/