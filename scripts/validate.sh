#!/bin/bash

GENERATE=$1
EXEC_MAIN=$2
VALIDATE=$3

VALIDATIONS=100

for I in `seq $VALIDATIONS`
do
    echo -n "SEED=$I : "
    $GENERATE $I > ./tmp/validate.in
    $EXEC_MAIN < ./tmp/validate.in > ./tmp/validate.out || ( echo "Runtime Error" && false ) || break
    cat ./tmp/validate.in ./tmp/validate.out | $VALIDATE || ( echo "Wrong Answer" && false ) || break
done

#SEED=1
#./validate_gen $SEED > ./tmp/validate.in; $EXEC_MAIN < ./tmp/validate.in > ./tmp/validate.out; cat ./tmp/validate.in ./tmp/validate.out | $VALIDATE || break
