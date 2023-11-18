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
    throw_if(begin > endExclusive, "invalid Accumurate::partial_sum range");
    throw_if(begin > acc.size(), "invalid Accumurate::partial_sum range");
    return (endExclusive == 0 ? T{} : acc[endExclusive - 1]) -
           (begin == 0 ? T{} : acc[begin - 1]);
  }
  T accumulate(int endExclusive) const {
    throw_if(endExclusive < 0, "invalid Accumurate::accumulate range");
    throw_if(endExclusive > acc.size(), "invalid Accumurate::sum range");
    return endExclusive == 0 ? T{} : acc[endExclusive - 1];
  }
  size_t size() const { return acc.size(); }
  bool empty() const { return acc.size() == 0; }
  vec<T> acc;
};

#endif
/* end of ACCUMULATE */