#!/bin/sh

WORK_DIR=/home
TEMPLATE_DIR=$WORK_DIR/templates

cat $TEMPLATE_DIR/template.hpp >| $TEMPLATE_DIR/main.cpp
: >| $TEMPLATE_DIR/validate.cpp
: >| $TEMPLATE_DIR/generate.cpp

echo "\n\
void solve();
int main(int, char *[]) {\n\
  init_io();\n\
  ll t = 1;\n\
  /** input(t); /**/\n\
  while (t--)\n\
    solve();\n\
  std::cout.flush();\n\
}\n\
\n\
void solve() {\n\
  input();\n\
  print();\n\
}\n\
" >> $TEMPLATE_DIR/main.cpp
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
" >> $TEMPLATE_DIR/validate.cpp
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
" >> $TEMPLATE_DIR/generate.cpp



cat $TEMPLATE_DIR/template.py >| $TEMPLATE_DIR/main.py
cat $TEMPLATE_DIR/template.py >| $TEMPLATE_DIR/validate.py
cat $TEMPLATE_DIR/template.py >| $TEMPLATE_DIR/generate.py

echo "\n\
S = input()\n\
dump(S)\n\
print(S)\n\
" >> $TEMPLATE_DIR/main.py
echo "\n\
if True:\n\
    print(\"OK\")\n\
    exit(0)\n\
else:\n\
    print(\"NG\")\n\
    exit(1)\n\
" >> $TEMPLATE_DIR/validate.py
echo "\n\
if len(sys.argv) > 1:\n\
    rng.seed(int(sys.argv[1]))\n\
\n\
#N = 20\n\
#K = rng.randint(1, N)\n\
" >> $TEMPLATE_DIR/generate.py
