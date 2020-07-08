#!/bin/sh

WORK_DIR="/home"
TMP_DIR="$WORK_DIR/tmp"
TASK_DIR="$WORK_DIR/tasks/$1"
TEST_IN="$TASK_DIR/sample.in"
TEST_OUT="$TASK_DIR/sample.out"
TEST_ANS="$TASK_DIR/sample.ans"
COMMAND="$2"
echo $COMMAND

mkdir -p $TMP_DIR
rm -rf $TMP_DIR/*
cat $TEST_IN | awk 'BEGIN { RS = ""; FS = "\n" }; { for (i = 1; i <= NF; i++){ print $i >> "/home/tmp/"NR} }; END { print NR >> "/home/tmp/N" }'


N=`cat $TMP_DIR/N`
: >| $TEST_OUT

echo "-- Out: ----------"
for i in `seq $N`;
do
  $COMMAND < "$TMP_DIR/$i" | tee -a $TEST_OUT
  echo ""
done

echo "-- Ans: ----------"
cat $TEST_ANS

echo "-- Diff: ---------"
diff -Z -B $TEST_OUT $TEST_ANS

