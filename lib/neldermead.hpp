/**
 * NELDERMEAD
 */
#ifndef JUMPAKU_NELDERMEAD_HPP
#define JUMPAKU_NELDERMEAD_HPP

#ifndef TEMPLATE_HPP
#include "../template/header.hpp"
#endif

namespace neldermead {
template <class X, class F = lf (*)(X)>
X minimize(vec<X> const &init, ll repeat, F const &f) {
  auto x = init;
  for (auto &&i : range(repeat)) {
    sort(x.begin(), x.end(),
         [&](auto const &a, auto const &b) { return f(a) < f(b); });
    X x0 = x[0];
    lf f0 = f(x0);
    X x1 = x[x.size() - 2];
    lf f1 = f(x1);
    X x2 = x[x.size() - 1];
    lf f2 = f(x2);
    dump_vars(i, f0, f1, f2);

    X xO = x0.lerp(0.5, x1);
    lf fO = f(xO);

    X xR = xO.lerp(-1, x2);
    lf fR = f(xR);

    if (f0 <= fR && fR < f1) {
      x.back() = xR;
      continue;
    }
    if (fR < f0) {
      X xE = xO.lerp(2, xR);
      lf fE = f(xE);
      if (fE < fR) {
        x.back() = xE;
      } else {
        x.back() = xR;
      }
      continue;
    }
    if (fR > f1) {
      if (fR < f2) {
        X xC = xO.lerp(0.5, xR);
        lf fC = f(xC);

        if (fC < fR) {
          x.back() = xC;
          continue;
        }
      } else {
        X xC = xO.lerp(0.5, x2);
        lf fC = f(xC);

        if (fC < fR) {
          x.back() = xC;
          continue;
        }
      }
    }

    for (auto &&i : range(1, x.size())) {
      x[i] = x0.lerp(0.5, x[i]);
    }
  }
  return x[0];
}
} // namespace neldermead

#endif
/* end of NELDERMEAD */
