/**
 * JUMPAKU_ATCODER_HPP
 */
#ifndef JUMPAKU_ATCODER_HPP
#define JUMPAKU_ATCODER_HPP

#ifndef TEMPLATE_HPP
#include "../templates/template.hpp"
#endif

vecl sort_cyclic_shifts(str const &s) {
  int n = s.size();
  const int alphabet = 256;
  vecl p(n), c(n), cnt(max(alphabet, n), 0);

  // k=0のソート

  for (int i = 0; i < n; i++) {
    cnt[s[i]]++;
  }
  for (int i = 1; i < alphabet; i++) {
    cnt[i] += cnt[i - 1];
  }
  for (int i = 0; i < n; i++) {
    p[--cnt[s[i]]] = i;
  }
  c[p[0]] = 0;
  int classes = 1;
  for (int i = 1; i < n; i++) {
    if (s[p[i]] != s[p[i - 1]]) {
      classes++;
    }
    c[p[i]] = classes - 1;
  }

  //以下k=1…logn+1の反復をする
  vecl pn(n), cn(n);
  for (int k = 0; (1 << k) < n; ++k) {
    for (int i = 0; i < n; i++) {
      pn[i] = p[i] - (1 << k);
      if (pn[i] < 0) {
        pn[i] += n;
      }
    }
    fill(cnt.begin(), cnt.begin() + classes, 0);
    for (int i = 0; i < n; i++) {
      cnt[c[pn[i]]]++;
    }
    for (int i = 1; i < classes; i++) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; i--) {
      p[--cnt[c[pn[i]]]] = pn[i];
    }
    cn[p[0]] = 0;
    classes = 1;
    for (int i = 1; i < n; i++) {
      pair<int, int> cur = {c[p[i]], c[(p[i] + (1 << k)) % n]};
      pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
      if (cur != prev) {
        ++classes;
      }
      cn[p[i]] = classes - 1;
    }
    c.swap(cn);
  }
  return p;
}
vecl suffix_array_construction(str s) {
  s += "$";
  vecl sorted_shifts = sort_cyclic_shifts(s);
  sorted_shifts.erase(sorted_shifts.begin());
  return sorted_shifts;
}

#endif
/* end of JUMPAKU_ATCODER_HPP */