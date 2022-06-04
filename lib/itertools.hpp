/**
 * ITERTOOLS
 */

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

namespace itertools {

template <class Itr> struct iterator_base {
  using difference_type = int;
  using value_type = vecl;
  using pointer = vecl *;
  using reference = vecl &;
  using iterator_category = std::forward_iterator_tag;
  vecl values;
  bool isEnd;
  iterator_base(vecl const &values, bool isEnd)
      : values(values), isEnd(isEnd) {}
  bool operator==(Itr const &itr) const { return isEnd == isEnd; }
  bool operator!=(Itr const &itr) const { return isEnd != itr.isEnd; }
  vecl const &operator*() const { return values; }
};

struct Product {
  struct iterator : iterator_base<iterator> {
    vecl sizes;
    iterator(vecl const &values, vecl const &sizes, bool isEnd)
        : iterator_base<iterator>(values, isEnd), sizes(sizes) {}
    iterator &operator++() {
      if (isEnd)
        return *this;
      int n = values.size();
      if (n == 0) {
        isEnd = true;
        return *this;
      }
      for (int i = values.size() - 1; i >= 0; --i) {
        if (values[i] < sizes[i] - 1) {
          ++values[i];
          return *this;
        }
        if (i > 0)
          values[i] = 0;
        else
          isEnd = true;
      }
      return *this;
    }
  };

private:
  vecl sizes;

public:
  Product(vecl const &sizes) : sizes(sizes) {}
  iterator begin() const {
    if (any_of(sizes.begin(), sizes.end(), [](auto s) { return s == 0; }))
      return end();
    return iterator(vecl(sizes.size(), 0), sizes, false);
  }
  iterator end() const { return iterator(vecl{}, sizes, true); }
};

struct Power : Product {
  Power(int const &size, int const &n) : Product(vecl(n, size)) {}
};

struct Permutation {
  struct iterator : iterator_base<iterator> {
    vecl indices;
    vecl cycles;
    iterator(vecl const &values, vecl const &indices, vecl const &cycles,
             bool isEnd)
        : iterator_base<iterator>(values, isEnd), indices(indices),
          cycles(cycles) {}
    iterator &operator++() {
      if (isEnd)
        return *this;
      int n = indices.size();
      int r = cycles.size();
      if (n == r) {
        isEnd = !std::next_permutation(values.begin(), values.end());
        return *this;
      }
      for (int i = r - 1; i >= 0; --i) {
        --cycles[i];
        if (cycles[i] == 0) {
          std::rotate(indices.begin() + i, indices.begin() + i + 1,
                      indices.end());
          cycles[i] = n - i;
        } else {
          int j = cycles[i];
          swap(indices[i], indices[n - j]);
          copy(indices.begin(), indices.begin() + r, values.begin());
          return *this;
        }
      }
      isEnd = true;
      return *this;
    }
  };

private:
  int size;
  int take;
  iterator end_itr = iterator(vecl{}, vecl{}, vecl{}, true);

public:
  Permutation(int const &size, int const &take) : size(size), take(take) {}
  Permutation(int const &size) : Permutation(size, size) {}
  iterator begin() const {
    if (take < 0 || size < take)
      return end();
    vecl values(take);
    std::iota(values.begin(), values.end(), 0);
    vecl indices(size);
    std::iota(indices.begin(), indices.end(), 0);
    vecl cycles(take);
    std::iota(cycles.begin(), cycles.end(), size - take + 1);
    reverse(cycles.begin(), cycles.end());
    return iterator(values, indices, cycles, false);
  }
  iterator end() const { return end_itr; }
};

struct Combination {
  struct iterator : iterator_base<iterator> {
    int size;
    iterator(vecl const &values, int const &size, bool isEnd)
        : iterator_base<iterator>(values, isEnd), size(size) {}
    iterator &operator++() {
      if (isEnd)
        return *this;
      int n = size;
      int r = values.size();
      for (int i = r - 1; i >= 0; --i) {
        if (values[i] != i + n - r) {
          ++values[i];
          for (int j = i + 1; j < r; j++)
            values[j] = values[j - 1] + 1;
          return *this;
        }
      }
      isEnd = true;
      return *this;
    }
  };

private:
  int size;
  int take;

public:
  Combination(int const &size, int const &take) : size(size), take(take) {}
  Combination(int const &size) : Combination(size, take) {}
  iterator begin() const {
    if (take < 0 || size < take)
      return end();
    vecl values(take);
    std::iota(values.begin(), values.end(), 0);
    return iterator(values, size, false);
  }
  iterator end() const { return iterator(vecl{}, size, true); }
};

struct MultiCombination {
  struct iterator : iterator_base<iterator> {
    int size;
    iterator(vecl const &values, int const &size, bool isEnd)
        : iterator_base<iterator>(values, isEnd), size(size) {}
    iterator &operator++() {
      if (isEnd)
        return *this;
      int n = size;
      int r = values.size();
      for (int i = r - 1; i >= 0; --i) {
        if (values[i] != n - 1) {
          int vi = values[i];
          for (int j = i; j < r; j++)
            values[j] = vi + 1;
          return *this;
        }
      }
      isEnd = true;
      return *this;
    }
  };

private:
  int size;
  int take;

public:
  MultiCombination(int const &size, int const &take) : size(size), take(take) {}
  MultiCombination(int const &size) : MultiCombination(size, take) {}
  iterator begin() const {
    if (take < 0 || size < take)
      return end();
    return iterator(vecl(take, 0), size, false);
  }
  iterator end() const { return iterator(vecl{}, size, true); }
};
} // namespace itertools
using itertools::Combination;
using itertools::MultiCombination;
using itertools::Permutation;
using itertools::Power;
using itertools::Product;
/* end of ITERTOOLS */