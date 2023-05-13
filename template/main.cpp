

#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "header.hpp"

#endif /* TEMPLATE_HPP */

void solve();

int main(int, char *[]) {
  init_io();
  ll t = 1;
  /** input(t); /**/
  while (t--)
    solve();
  std::cout.flush();
}

void validate() {
#ifdef JUMPAKU_DEBUG
  dump("---------- Valitdate ----------");
  ll expected = 0;
  dump_vars(expected);
  if (!true) {
    exitRE(1);
  }
#endif
}

void solve() {
  input();
  validate();
  print();
}
