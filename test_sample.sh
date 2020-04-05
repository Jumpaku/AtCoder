#!/bin/sh

COMMAND="$1"

mkdir -p ./tmp/
rm ./tmp/*
cat test_sample.in | awk 'BEGIN { RS = ""; FS = "\n" }; { for (i = 1; i <= NF; i++){ print $i >> "tmp/"NR} }; END { print NR >> "tmp/N" }'


N=`cat ./tmp/N`
: >| test_sample.out

echo "Out:"
for i in `seq $N`;
do
  $COMMAND < "./tmp/$i" | tee -a test_sample.out 
done

echo "Ans:"
cat ./test_sample.ans

echo "Diff:"
diff ./test_sample.out ./test_sample.ans
