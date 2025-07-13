/**
 * PERSISTENT
 */
#ifndef JUMPAKU_PERSISTENT_HPP
#define JUMPAKU_PERSISTENT_HPP

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#include "atcoder.hpp"
#endif

#include <memory>

template <class Elem> struct Stack {
  std::shared_ptr<Stack<Elem>> nx;
  int sz = 0;
  Elem top;

  using Inst = std::shared_ptr<Stack<Elem>>;

  Stack<Elem>(Inst _nx, Elem elem)
      : nx(_nx), sz(Stack<Elem>::size(_nx) + 1), top(elem) {}
  ~Stack<Elem>() = default;

  // cur に pop back した後の状態を取得
  static Inst pop(const Inst &cur) { return cur->nx; }

  // cur に push back した後の状態を取得
  static Inst push(const Inst &cur, const Elem &x) {
    return std::make_shared<Stack<Elem>>(cur, x);
  }

  // 要素数
  static int size(const Inst &cur) { return cur.get() ? cur->sz : 0; }
};

#endif
/* end of PERSISTENT */