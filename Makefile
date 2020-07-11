
WORK_DIR=/home
TASKS_DIR=$(WORK_DIR)/tasks
SCRIPTS_DIR=$(WORK_DIR)/scripts
TEMPLATES_DIR=$(WORK_DIR)/templates

CPP_COMMON_OPTIONS=-std=gnu++17 -O2 -Wall -Wextra -Wno-comment 

.DEFAULT_GOAL:=help

.PHONY: help
help:
	@grep -E '^[a-zA-Z_%-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

.PHONY: clean
clean: ### Clean samples, tasks, and temporary directory.
	rm -rf $(WORK_DIR)/samples/* $(TASKS_DIR)/* $(WORK_DIR)/tmp/* 

templates: $(TEMPLATES_DIR)/template.hpp $(TEMPLATES_DIR)/template.py ### Initialize template files.
	$(SCRIPTS_DIR)/templates.sh

.PHONY: samples
samples: ### Download sample inputs and answers (outputs for them).
	rm -f $(WORK_DIR)/samples/*
	python3 $(SCRIPTS_DIR)/samples.py < $(WORK_DIR)/contest_data.txt

.PHONY: tasks
tasks: samples ### Initialize all tasks based on samples.
	for TASK in `ls $(WORK_DIR)/samples | grep in | sed -e 's/.in//g'`; do echo "task_$$TASK"; $(SCRIPTS_DIR)/task.sh $$TASK; done


.PHONY: task_%
task_%: ### Initialize a specified task.
	$(SCRIPTS_DIR)/task.sh "$*"

# C++
.PHONY: run_%
run_%: main_% ### Run a compiled executable file (main).
	$(TASKS_DIR)/$*/bin/main
main_%: $(TASKS_DIR)/%/main.cpp ### Compile a C++ source file (main.cpp).
	g++ $(CPP_COMMON_OPTIONS) -o $(TASKS_DIR)/$*/bin/main $(TASKS_DIR)/$*/main.cpp

.PHONY: debug_% 
debug_%: debug_main_% $(TASKS_DIR)/%/debug.in ### Run a compiled executable file with a debug input.
	$(TASKS_DIR)/$*/bin/debug_main < $(TASKS_DIR)/$*/debug.in
debug_main_%: $(TASKS_DIR)/%/main.cpp ### Compile a C++ source file with JUMPAKU_DEBUG macro.
	g++ $(CPP_COMMON_OPTIONS) -DJUMPAKU_DEBUG -o $(TASKS_DIR)/$*/bin/debug_main $(TASKS_DIR)/$*/main.cpp

.PHONY: test_%
test_%: main_% $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans ### Test a compiled executable file with samples.
	$(SCRIPTS_DIR)/test.sh "$*" "$(TASKS_DIR)/$*/bin/main"

.PHONY: submit_% 
submit_%: main_% $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans ### Submit a C++ source file if the test passed.
	$(SCRIPTS_DIR)/test.sh "$*" "$(TASKS_DIR)/$*/bin/main" && \
	python3 $(SCRIPTS_DIR)/submit.py $* cplusplus $(TASKS_DIR)/$*/main.cpp < $(WORK_DIR)/contest_data.txt
.PHONY: submit_force_%
submit_force_%: main_% $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans ### Submit a C++ source file forcibly.
	$(SCRIPTS_DIR)/test.sh "$*" "$(TASKS_DIR)/$*/bin/main" || \
	python3 $(SCRIPTS_DIR)/submit.py $* cplusplus $(TASKS_DIR)/$*/main.cpp < $(WORK_DIR)/contest_data.txt

validate_main_%: $(TASKS_DIR)/%/validate.cpp ### Compile a C++ source file for validation.
	g++ $(CPP_COMMON_OPTIONS) -o $(TASKS_DIR)/$*/bin/validate_main $(TASKS_DIR)/$*/validate.cpp
generate_main_%: $(TASKS_DIR)/%/generate.cpp ### Compile a C++ source file to generate sample input for validation.
	g++ $(CPP_COMMON_OPTIONS) -o $(TASKS_DIR)/$*/bin/generate_main $(TASKS_DIR)/$*/generate.cpp
.PHONY: validate_%
validate_%: generate_main_% main_% validate_main_% ### Validate compiled executable file with generate sample input.
	$(SCRIPTS_DIR)/validate.sh "$(TASKS_DIR)/$*/bin/generate_main" "$(TASKS_DIR)/$*/bin/main" "$(TASKS_DIR)/$*/bin/validate_main"

# Python3
.PHONY: run_%_py
run_%_py: $(TASKS_DIR)/%/main.py ### Run a Python3 script (main.py).
	python3 $(TASKS_DIR)/$*/main.py

.PHONY: debug_%_py
debug_%_py: $(TASKS_DIR)/%/main.py $(TASKS_DIR)/%/debug.in ### Run a Python3 script with a debug input.
	python3 $(TASKS_DIR)/$*/main.py DEBUG < $(TASKS_DIR)/$*/debug.in

.PHONY: test_%_py
test_%_py: $(TASKS_DIR)/%/main.py $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans ### Test a Python3 script with samples.
	$(SCRIPTS_DIR)/test.sh "$*" "python3 $(TASKS_DIR)/$*/main.py"

.PHONY: submit_%_py
submit_%_py: $(TASKS_DIR)/%/main.py $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans ### Submit a Python3 script if the test passed.
	$(SCRIPTS_DIR)/test.sh "$*" "python3 $(TASKS_DIR)/$*/main.py" && \
	python3 $(SCRIPTS_DIR)/submit.py $* python3 $(TASKS_DIR)/$*/main.py < $(WORK_DIR)/contest_data.txt
.PHONY: submit_force_%_py
submit_force_%_py: main_% $(TASKS_DIR)/%/sample.in $(TASKS_DIR)/%/sample.ans  ### Submit a Python3 script forcibly.
	$(SCRIPTS_DIR)/test.sh "$*" "python3 $(TASKS_DIR)/$*/main.py" || \
	python3 $(SCRIPTS_DIR)/submit.py $* python3 $(TASKS_DIR)/$*/main.py < $(WORK_DIR)/contest_data.txt

validate_%_py: $(TASKS_DIR)/%/generate.py $(TASKS_DIR)/%/main.py $(TASKS_DIR)/%/validate.py ### Validate Python3 script with generate sample input.
	$(SCRIPTS_DIR)/validate.sh "python3 $(TASKS_DIR)/$*/generate.py" "python3 $(TASKS_DIR)/$*/main.py" "python3 $(TASKS_DIR)/$*/validate.py"
