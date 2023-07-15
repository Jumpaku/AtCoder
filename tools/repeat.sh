#!/bin/sh


if [ $# != 2 ]; then
    echo "positional arguments <count> and <job-command> are required"
    echo "repeats execution of <job-command> <count> times, in which execution the job can take a 1-indexed environment variable LOOP_NUMBER"
    exit 1
fi

set -eux

COUNT=$1
JOB_COMMAND=$2

for LOOP_NUMBER in $(seq "${COUNT}"); do
    export LOOP_NUMBER="${LOOP_NUMBER}"
    sh -c "set -eux; ${JOB_COMMAND}"
done
