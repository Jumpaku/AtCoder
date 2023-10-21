

#ifndef TEMPLATE_HPP
#define TEMPLATE_HPP

#include "header.hpp"

#endif /* TEMPLATE_HPP */

void solve();

int main(int, char *[]) {
  {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::cout << std::fixed << std::setprecision(15);
  }

  int t = 1;
  /** input(t); /**/
  while (t--) {
    try {
      solve();
    } catch (const std::exception &e) {
      std::cerr << "\nexception:\n" << e.what() << std::endl;
      exit(1);
    }
  }
  std::cout.flush();
}

void solve() {
  //
}
