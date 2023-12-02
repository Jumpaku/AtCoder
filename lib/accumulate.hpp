/**
 * ACCUMULATE
 */
#ifndef JUMPAKU_PARTIAL_SUM_HPP
#define JUMPAKU_PARTIAL_SUM_HPP

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#endif

template <class T> struct Accumulate {
  template <class Itr> explicit Accumulate(Itr begin, Itr end) {
    std::partial_sum(begin, end, back_inserter(acc));
  }
  Accumulate(Accumulate const &) = default;
  Accumulate(Accumulate &&) = default;
  Accumulate &operator=(Accumulate const &) = default;
  Accumulate &operator=(Accumulate &&) = default;
  T partial_sum(int begin, int endExclusive) const {
    throw_if(!(0 <= begin && begin <= endExclusive && endExclusive <= size()),
             "invalid Accumurate::partial_sum range");
    return (endExclusive == 0 ? T{} : acc[endExclusive - 1]) -
           (begin == 0 ? T{} : acc[begin - 1]);
  }
  T accumulate(int endExclusive) const {
    throw_if(!(0 <= endExclusive && endExclusive <= acc.size()),
             "invalid Accumurate::accumulate range");
    return endExclusive == 0 ? T{} : acc[endExclusive - 1];
  }
  size_t size() const { return acc.size(); }
  bool empty() const { return acc.size() == 0; }
  vec<T> acc;
};

template <class T> struct Accumulate2D {
  explicit Accumulate2D(vec<vec<T>> const &arr) {
    ll N = arr.size();
    if (N == 0) {
      return;
    }
    ll M = arr[0].size();
    for (auto &&i : range(N)) {
      throw_if(arr[i].size() != M, "invalid shape: Accumulate2D::Accumulate2D");
      for (auto &&j : range(M)) {
        acc[i][j] = (i == 0 && j == 0) ? (arr[i][j])
                    : (i == 0)         ? (acc[i][j - 1] + arr[i][j])
                    : (j == 0)         ? (acc[i - 1][j] + arr[i][j])
                                       : (acc[i][j - 1] + acc[i - 1][j] -
                                  acc[i - 1][j - 1] + arr[i][j]);
      }
    }

    std::partial_sum(begin, end, back_inserter(acc));
  }
  Accumulate2D(Accumulate2D const &) = default;
  Accumulate2D(Accumulate2D &&) = default;
  Accumulate2D &operator=(Accumulate2D const &) = default;
  Accumulate2D &operator=(Accumulate2D &&) = default;
  T partial_sum(tuple<int, int> begin, tuple<int, int> endExclusive) const {
    auto [i, j] = begin;
    auto [k, l] = endExclusive;
    auto [r, c] = size();
    throw_if(!(0 <= i && i <= k && k <= r),
             "invalid Accumurate::partial_sum range");
    throw_if(!(0 <= j && j <= l && l <= c),
             "invalid Accumurate::partial_sum range");
    return (k == 0 || l == 0)   ? (T{})
           : (i == 0 && j == 0) ? (acc[k - 1][l - 1])
           : (i == 0)           ? (acc[k - 1][l - 1] - acc[k - 1][j - 1])
           : (j == 0)           ? (acc[k - 1][l - 1] - acc[i - 1][l - 1])
                                : (acc[k - 1][l - 1] - acc[k - 1][j - 1] -
                         acc[i - 1][l - 1] + acc[i - 1][j - 1]);
  }
  T accumulate(tuple<int, int> endExclusive) const {
    auto [k, l] = endExclusive;
    auto [r, c] = size();
    throw_if(!(0 <= k && k <= r), "invalid Accumurate::partial_sum range");
    throw_if(!(0 <= l && l <= c), "invalid Accumurate::partial_sum range");
    return (k == 0 || l == 0) ? (T{}) : (acc[k - 1][l - 1]);
  }
  tuple<size_t, size_t> size() const { return {acc.size(), acc[0]}; }
  bool empty() const {
    auto [r, c] = size();
    return r == 0 || c == 0;
  }
  vec<vec<T>> acc;
};

#endif
/* end of ACCUMULATE */