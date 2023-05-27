#!/bin/sh

set -eux

TASK_ID=$1

# Task directory
mkdir -p "tasks/${TASK_ID}"

# Source files
cp -r template/* "tasks/${TASK_ID}/"

# Debug input files
rm -f "tasks/${TASK_ID}/debug.in"
{ cat "tasks/${TASK_ID}/"*.in || true; } > "tasks/${TASK_ID}/debug.in"

# main.cpp
echo "#ifndef TEMPLATE_HPP\n#define TEMPLATE_HPP" > "tasks/${TASK_ID}/main.cpp"
cat template/header.hpp >> "tasks/${TASK_ID}/main.cpp"
echo "#endif /* TEMPLATE_HPP */\n" >> "tasks/${TASK_ID}/main.cpp"
cat template/main.cpp \
  | grep -v 'header.hpp' \
  | grep -v 'TEMPLATE_HPP' \
  >> "tasks/${TASK_ID}/main.cpp"

grep "add_executable(main_${TASK_ID} tasks/${TASK_ID}/main.cpp)" < CMakeLists.txt \
  || echo "add_executable(main_${TASK_ID} tasks/${TASK_ID}/main.cpp)" >> CMakeLists.txt
