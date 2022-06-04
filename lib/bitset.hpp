/**
 * BITSET
 */
#ifndef JUMPAKU_BITSET_HPP
#define JUMPAKU_BITSET_HPP

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#include "atcoder.hpp"
#endif

struct bitset {
  static constexpr size_t Size = 64;
  using Buf = std::bitset<Size>;
  using Self = bitset;
  Buf buf;
  static bitset one() { return bitset(uint64_t(1)); }
  static bitset zero() { return bitset(uint64_t(0)); }
  bitset(Buf const &buffer = Buf()) : buf(buffer) {}
  bitset(bitset const &) = default;
  bitset(bitset &&) = default;
  Self &operator=(bitset const &) = default;
  Self &operator=(bitset &&) = default;
  Self set(int digit, bool val) const { return {Buf(buf).set(digit, val)}; }
  Self fill_l(size_t n, bool val) const {
    auto out = buf;
    for (auto &&i : range(n))
      out[Size - i - 1] = val;
    return out;
  }
  Self fill_r(size_t n, bool val) const {
    auto out = buf;
    for (auto &&i : range(n))
      out[i] = val;
    return out;
  }
  bool get(int digit) const { return buf.test(digit); }
  size_t size() const { return Size; }
  int cnt(bool val) const { return val ? buf.count() : (Size - buf.count()); }
  int cnt_l(bool val) const {
    int out = 0;
    for (size_t i = Size - 1; i >= 0; --i) {
      if (get(i) == val)
        ++out;
      else
        break;
    }
    return out;
  }
  int cnt_r(bool val) const {
    int out = 0;
    for (size_t i = 0; i < Size; ++i) {
      if (get(i) == val)
        ++out;
      else
        break;
    }
    return out;
  }
  bool any() const { return buf.any(); }
  bool all() const { return buf.all(); };
  bool none() const { return buf.none(); }
  uint64_t u64() const { return buf.to_ullong(); }
  std::string str() const { return buf.to_string(); }
  Self rot_l(int n) const {
    if (n < 0)
      return rot_r(-n);
    return {buf << (n % Size) | buf >> (Size - (n % Size))};
  }
  Self rot_r(int n) const {
    if (n < 0)
      return rot_l(-n);
    return {buf >> (n % Size) | buf << (Size - (n % Size))};
  }
  Self rev() const {
    Buf out;
    for (auto &&i : range(Size))
      out[i] = buf[Size - i - 1];
    return {out};
  }
  size_t left(bool val) const { return Size - 1 - cnt_l(!val); }
  size_t right(bool val) const { return cnt_r(!val); }
  Self operator<<(size_t n) const { return {buf << n}; }
  Self operator>>(size_t n) const { return {buf >> n}; }
  Self operator~() const { return {~buf}; }
  Self operator|(Self const &other) const { return {buf | other.buf}; }
  Self operator&(Self const &other) const { return {buf & other.buf}; }
  Self operator^(Self const &other) const { return {buf ^ other.buf}; }
};
io::OS &operator<<(io::OS &o, bitset const &b) { return o << b.str(); }

#endif
/* end of BITSET */