#!/bin/sh

set -eux

TASK_COUNT=$(jq '.tasks | length' <atcoder.json)

for TASK_IDX in $(seq 0 "$(( ${TASK_COUNT} - 1 ))" ); do
  TASK=$(jq -r ".tasks[${TASK_IDX}].task" <atcoder.json)

  # Task directory
  mkdir -p "tasks/${TASK}"

  # Sample inputs
  INPUT_COUNT=$(jq ".tasks[${TASK_IDX}].input | length" <atcoder.json)
  for INPUT_IDX in $(seq 0 "$(( ${INPUT_COUNT} - 1 ))"); do
    INPUT=$(jq -r ".tasks[${TASK_IDX}].input[${INPUT_IDX}]" <atcoder.json)
    echo "${INPUT}" > "tasks/${TASK}/${INPUT_IDX}.in"
  done

  # Answers for sample inputs
  ANSWER_COUNT=$(jq ".tasks[${TASK_IDX}].answer | length" <atcoder.json)
  for ANSWER_IDX in $(seq 0 "$(( ${ANSWER_COUNT} - 1 ))"); do
    ANSWER=$(jq -r ".tasks[${TASK_IDX}].answer[${ANSWER_IDX}]" <atcoder.json)
    echo "${ANSWER}" > "tasks/${TASK}/${ANSWER_IDX}.ans"
  done

  sh tools/task.sh "${TASK}"
done
