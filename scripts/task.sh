#!/bin/sh

WORK_DIR="/home"
TEMPLATE="$WORK_DIR/templates"
TASK_DIR="$WORK_DIR/tasks/$1"
SAMPLE_IN="$WORK_DIR/samples/$1.in"
SAMPLE_ANS="$WORK_DIR/samples/$1.ans"

mkdir -p $TASK_DIR
rm -rf $TASK_DIR
cp -r $TEMPLATE $TASK_DIR

if [ -e $SAMPLE_IN ]; then
  cat $SAMPLE_IN >> $TASK_DIR/sample.in
else
  : >| $TASK_DIR/sample.in
fi

if [ -e $SAMPLE_ANS ]; then
  cat $SAMPLE_ANS >> $TASK_DIR/sample.ans
else
  : >| $TASK_DIR/sample.ans
fi

cat $TASK_DIR/sample.in >| $TASK_DIR/debug.in
