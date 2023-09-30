

#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "header.hpp"

#endif /* TEMPLATE_HPP */

void solve();

int main(int, char *[]) {
  init_io();
  ll t = 1;
  /** input(t); /**/
  while (t--) {
    try {
      solve();
    } catch (const std::exception &e) {
      std::cerr << "exception " << e.what() << std::endl;
      exit(1);
    }
  }
  std::cout.flush();
}

void solve() {
  //
}
