#!/bin/sh

COMMAND="$1"
if [ -n "$2" ]; then
  INPUT="$2.in"
  OUTPUT="$2.out"
  ANSWER="$2.ans"
else
  INPUT="sample.in"
  INPUT="sample.out"
  ANSWER="sample.ans"
fi

mkdir -p ./tmp/
rm ./tmp/*
cat $INPUT | awk 'BEGIN { RS = ""; FS = "\n" }; { for (i = 1; i <= NF; i++){ print $i >> "tmp/"NR} }; END { print NR >> "tmp/N" }'


N=`cat ./tmp/N`
: >| $OUTPUT

echo "-- Out: ----------"
for i in `seq $N`;
do
  $COMMAND < "./tmp/$i" | tee -a $OUTPUT
done

echo "-- Ans: ----------"
cat $ANSWER

echo "-- Diff: ---------"
diff -Z -B $OUTPUT $ANSWER
