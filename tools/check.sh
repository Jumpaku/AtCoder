#!/bin/sh

set -eux

if [ $# != 2 ]; then
    echo "positional arg TASK_ID and EXEC_CMD are required"
    exit 1
fi

TASK=$1
EXEC_CMD=$2

for INPUT_FILE in $(ls "tasks/${TASK}/"*.in | grep -v debug.in); do
  OUTPUT_FILE=$(echo "${INPUT_FILE}" | sed 's|in$|out|g')
  ANSWER_FILE=$(echo "${INPUT_FILE}" | sed 's|in$|ans|g')
  sh -c "${EXEC_CMD} < ${INPUT_FILE} > ${OUTPUT_FILE}"
  cat "${ANSWER_FILE}"
  cat "${OUTPUT_FILE}"
  diff "${ANSWER_FILE}" "${OUTPUT_FILE}"
done