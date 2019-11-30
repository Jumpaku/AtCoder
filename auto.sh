#!/bin/bash

N=10
COMMAND="./main"

make main
g++ -std=c++14 -O2 -Wall -o ./gen ./gen.cpp

g++ -std=c++14 -O2 -Wall -o ./test ./test.cpp
for X in `seq $N`
do
    ./gen > ./tmp/gen_data
    cat ./tmp/gen_data
    "$COMMAND" < ./tmp/gen_data > ./tmp/out0
    ./test < ./tmp/gen_data > ./tmp/out1
    diff ./tmp/out0 ./tmp/out1
done

#g++ -std=c++14 -O2 -Wall -o ./check ./check.cpp
#for X in `seq $N`
#do
#    ./gen > ./tmp/gen_data
#    cat tmp/gen_data
#    ./main < ./tmp/gen_data | ./check
#done
