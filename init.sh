#!/bin/sh

: >| debug.in
: >| test_sample.in
: >| test_sample.ans

cat ./template_head.cpp >| ./main.cpp
cat ./template_head.cpp >| ./validate.cpp
cat ./template_head.cpp >| ./validate_gen.cpp

echo "\n\
int main() {\n\
  input();\n\
  dump();\n\
  print();\n\
}\n\
" >> ./main.cpp
echo "\n\
int main() {\n\
  if (true) return print(\"OK\"), 0;\n\
  else return print(\"NG\"), 1;\n\
}\n\
" >> ./validate.cpp
echo "\n\
int main(int argc, char const *argv[]) {\n\
  auto seed = (argc > 1) ? stoll(argv[1]) : random_device{}();\n\
  mt19937 e{seed};\n\
  using dist_u = uniform_int_distribution<ll>;\n\
\n\
  // ll N = 20;\n\
  // auto u = dist_u{1, N};\n\
  // ll K = u(e);\n\
}\n\
" >> ./validate_gen.cpp

cat ./template_head.py >| ./main.py
cat ./template_head.py >| ./validate.py
cat ./template_head.py >| ./validate_gen.py


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
