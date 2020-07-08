
# make init: initialize source code, and execute `make clean`
# make clean: remove executable files and sample files 
# make run: compile and execute main
# make debug: compile with #define JUMPAKU_DEBUG and execute `debug_main < debug.in`
# make sample: test main by sample.in 
# make sample_*: test main by samples/*.in
# make run_py: execute main.py
# make debug_py: execute `python3 main.py DEBUG < debug.in`
# make sample_py: test main.py by sample.in 
# make sample_*_py: test main.py by samples/*.in 
# make validate: 


CPP_COMMON_OPTIONS=-std=gnu++17 -O2 -Wall -Wextra -Wno-comment 
WORK_DIR=/home
TASKS_DIR=$(WORK_DIR)/tasks
SCRIPTS_DIR=$(WORK_DIR)/scripts

# Clear
.PHONY: clean
clean:
	rm -rf $(WORK_DIR)/samples/* $(TASKS_DIR)/* $(WORK_DIR)/tmp/* 

# Samples
.PHONY: samples
samples:
	python3 $(SCRIPTS_DIR)/samples.py < $(WORK_DIR)/contest_data.txt

# Tasks
.PHONY: tasks
tasks: samples
	for TASK in `ls $(WORK_DIR)/samples | grep in | sed -e 's/.in//g'`; do echo "task_$$TASK"; $(SCRIPTS_DIR)/task.sh $$TASK; done


# Task
.PHONY: task_%
task_%: 
	$(SCRIPTS_DIR)/task.sh "$*"

# C++
## Run
.PHONY: run_%
run_%: main_%
	$(TASKS_DIR)/$*/bin/main
main_%: $(TASKS_DIR)/%/main.cpp
	g++ $(CPP_COMMON_OPTIONS) -o $(TASKS_DIR)/$*/bin/main $(TASKS_DIR)/$*/main.cpp

## Debug
.PHONY: debug_%
debug_%: debug_main_% $(TASKS_DIR)/%/debug.in
	$(TASKS_DIR)/$*/bin/debug_main < $(TASKS_DIR)/$*/debug.in
debug_main_%: $(TASKS_DIR)/%/main.cpp
	g++ $(CPP_COMMON_OPTIONS) -DJUMPAKU_DEBUG -o $(TASKS_DIR)/$*/bin/debug_main $(TASKS_DIR)/$*/main.cpp

## Test
.PHONY: test_%
test_%: main_% $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans
	$(SCRIPTS_DIR)/test.sh "$*" "$(TASKS_DIR)/$*/bin/main"

## Submit
.PHONY: submit_%
submit_%: main_% $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans
	$(SCRIPTS_DIR)/test.sh "$*" "$(TASKS_DIR)/$*/bin/main" && \
	python3 $(SCRIPTS_DIR)/submit.py $* cplusplus $(TASKS_DIR)/$*/main.cpp < $(WORK_DIR)/contest_data.txt
.PHONY: submit_force_%
submit_force_%: main_% $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans
	$(SCRIPTS_DIR)/test.sh "$*" "$(TASKS_DIR)/$*/bin/main" || \
	python3 $(SCRIPTS_DIR)/submit.py $* cplusplus $(TASKS_DIR)/$*/main.cpp < $(WORK_DIR)/contest_data.txt

## Validate
validate_main_%: $(TASKS_DIR)/%/validate.cpp
	g++ $(CPP_COMMON_OPTIONS) -o $(TASKS_DIR)/$*/bin/validate_main $(TASKS_DIR)/$*/validate.cpp
generate_main_%: $(TASKS_DIR)/%/generate.cpp
	g++ $(CPP_COMMON_OPTIONS) -o $(TASKS_DIR)/$*/bin/generate_main $(TASKS_DIR)/$*/generate.cpp
.PHONY: validate_%
validate_%: generate_main_% main_% validate_main_%
	$(SCRIPTS_DIR)/validate.sh "$(TASKS_DIR)/$*/bin/generate_main" "$(TASKS_DIR)/$*/bin/main" "$(TASKS_DIR)/$*/bin/validate_main"

# Python3
## Run
.PHONY: run_%_py
run_%_py: $(TASKS_DIR)/%/main.py
	python3 $(TASKS_DIR)/$*/main.py

## Debug
.PHONY: debug_%_py
debug_%_py: $(TASKS_DIR)/%/main.py $(TASKS_DIR)/%/debug.in
	python3 $(TASKS_DIR)/$*/main.py DEBUG < $(TASKS_DIR)/$*/debug.in

## Test
.PHONY: test_%_py
test_%_py: $(TASKS_DIR)/%/main.py $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans
	$(SCRIPTS_DIR)/test.sh "$*" "python3 $(TASKS_DIR)/$*/main.py"

## Submit
.PHONY: submit_%_py
submit_%_py: $(TASKS_DIR)/%/main.py $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans
	$(SCRIPTS_DIR)/test.sh "$*" "python3 $(TASKS_DIR)/$*/main.py" && \
	python3 $(SCRIPTS_DIR)/submit.py $* python3 $(TASKS_DIR)/$*/main.py < $(WORK_DIR)/contest_data.txt
.PHONY: submit_force_%_py
submit_force_%_py: main_% $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans
	$(SCRIPTS_DIR)/test.sh "$*" "python3 $(TASKS_DIR)/$*/main.py" || \
	python3 $(SCRIPTS_DIR)/submit.py $* python3 $(TASKS_DIR)/$*/main.py < $(WORK_DIR)/contest_data.txt

## Validate
validate_%_py: $(TASKS_DIR)/%/generate.py $(TASKS_DIR)/%/main.py $(TASKS_DIR)/%/validate.py
	$(SCRIPTS_DIR)/validate.sh "python3 $(TASKS_DIR)/$*/generate.py" "python3 $(TASKS_DIR)/$*/main.py" "python3 $(TASKS_DIR)/$*/validate.py"
