
#include "template.hpp"

using namespace std;
int main(int argc, char const *argv[]) {
  auto seed = (argc > 1) ? stoll(argv[1]) : random_device{}();
  mt19937 e{seed};
  using dist_u = uniform_int_distribution<ll>;

  print(dist_u{0, 1}(e));
}

