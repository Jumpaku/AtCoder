#!/bin/sh

: >| test_sample.out
echo "Out:"
for i in `seq $1`;
do
  ./main | tee -a test_sample.out
done

echo "Diff:"
diff ./test_sample.out ./test_sample.ans

echo "Done."
