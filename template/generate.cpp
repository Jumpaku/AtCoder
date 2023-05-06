
#include "header.hpp"
#include <random>

using namespace std;
int main(int argc, char const *argv[]) {
  auto seed = (argc > 1) ? stoll(argv[1]) : random_device{}();
  mt19937 e{seed};
  using dist_u = uniform_int_distribution<ll>;

  ll N = 10;
  print(dist_u{0, N}(e));
}

