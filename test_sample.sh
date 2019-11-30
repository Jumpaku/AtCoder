#!/bin/sh

: >| test_sample.out
for i in `seq $1`;
do
  ./main | tee -a test_sample.out
done
