#!/bin/bash

VALIDATE_GEN="./validate_gen_main"
EXEC_MAIN="./main"
VALIDATE="./validate_main"
#VALIDATE_GEN="python3 ./validate_gen.py"
#EXEC_MAIN="python3 ./main.py"
#VALIDATE="python3 ./validate.py"

VALIDATIONS=100

for I in `seq $VALIDATIONS`
do
    echo -n "SEED=$I : "
    $VALIDATE_GEN $I > ./tmp/validate.in
    $EXEC_MAIN < ./tmp/validate.in > ./tmp/validate.out || ( echo "Runtime Error" && false ) || break
    cat ./tmp/validate.in ./tmp/validate.out | $VALIDATE || ( echo "Wrong Answer" && false ) || break
done

#SEED=1
#./validate_gen $SEED > ./tmp/validate.in; $EXEC_MAIN < ./tmp/validate.in > ./tmp/validate.out; cat ./tmp/validate.in ./tmp/validate.out | $VALIDATE || break
