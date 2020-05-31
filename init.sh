#!/bin/sh

: >| debug.in
: >| sample.in
: >| sample.ans

cat ./template.hpp >| ./main.cpp
: >| ./validate.cpp
: >| ./validate_gen.cpp

echo "\n\
void solve();
int main() {\n\
  init_io();\n\
  ll t = 1;\n\
  /** input(t); /**/\n\
  while (t--)\n\
    solve();\n\
  cout.flush();\n\
}\n\
\n\
void solve() {\n\
  input();\n\
  print();\n\
}\n\
" >> ./main.cpp
echo "\n\
#include \"template.hpp\"\n\
\n\
int main() {\n\
  ll in;
  input();\n\
  ll out;\n\
  input();\n\
  ll ans;\n\
  print();\n\
  if (out == ans)\n\
    return print(\"OK\"), 0;\n\
  else\n\
    return print(\"NG\"), 1;\n\
}\n\
" >> ./validate.cpp
echo "\n\
#include \"template.hpp\"\n\
#include <random>\n\
\n\
using namespace std;\n\
int main(int argc, char const *argv[]) {\n\
  auto seed = (argc > 1) ? stoll(argv[1]) : random_device{}();\n\
  mt19937 e{seed};\n\
  using dist_u = uniform_int_distribution<ll>;\n\
\n\
  ll N = 10;\n\
  print(dist_u{0, N}(e));\n\
}\n\
" >> ./validate_gen.cpp

cat ./template.py >| ./main.py
cat ./template.py >| ./validate.py
cat ./template.py >| ./validate_gen.py


echo "\n\
S = input()\n\
dump(S)\n\
print(S)\n\
" >> ./main.py
echo "\n\
if True:\n\
    print(\"OK\")\n\
    exit(0)\n\
else:\n\
    print(\"NG\")\n\
    exit(1)\n\
" >> ./validate.py
echo "\n\
if len(sys.argv) > 1:\n\
    rng.seed(int(sys.argv[1]))\n\
\n\
#N = 20\n\
#K = rng.randint(1, N)\n\
" >> ./validate_gen.py
