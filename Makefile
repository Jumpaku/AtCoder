.DEFAULT_GOAL:=help

CPP_COMMON_OPTIONS=-std=gnu++23 -O2 -Wall -Wextra -Wno-comment -ftrapv -I/usr/include/boost -L/usr/include/boost

.PHONY: help
help: ## Show this help.
	@grep -E '^[a-zA-Z_%-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%s\033[0m\n\t%s\n", $$1, $$2}'

# For arbitrary contest task
.PHONY: task
task: ## Prepare task directories: make task TASK=a
	sh tools/task.sh $(TASK)

.PHONY: debug
debug: ## Debug task: make debug TASK=a
	mkdir -p tasks/$(TASK)/bin
	g++ $(CPP_COMMON_OPTIONS) -DJUMPAKU_DEBUG -o tasks/$(TASK)/bin/main tasks/$(TASK)/main.cpp
	./tasks/$(TASK)/bin/main < tasks/$(TASK)/debug.in

.PHONY: debug_py
debug_py: ## Debug task: make debug_py TASK=a
	mkdir -p tasks/$(TASK)/bin
	python3 ./tasks/$(TASK)/main.py DEBUG < tasks/$(TASK)/debug.in

.PHONY: test
test: ## Check task: make check TASK=a
	mkdir -p tasks/$(TASK)/bin
	g++ $(CPP_COMMON_OPTIONS) -o tasks/$(TASK)/bin/main tasks/$(TASK)/main.cpp
	sh tools/check.sh $(TASK) ./tasks/$(TASK)/bin/main

.PHONY: test_py
test_py: ## Check task: make check_py TASK=a
	mkdir -p tasks/$(TASK)/bin
	sh tools/check.sh $(TASK) "python3 ./tasks/$(TASK)/main.py"

.PHONY: generate
generate: ## Generate debug: make generate TASK=a
	mkdir -p tasks/$(TASK)/bin
	g++ $(CPP_COMMON_OPTIONS) -o tasks/$(TASK)/bin/generate tasks/$(TASK)/generate.cpp
	./tasks/$(TASK)/bin/generate > tasks/$(TASK)/debug.in

.PHONY: generate_py
generate_py: ## Generate debug: make generate_py TASK=a
	mkdir -p tasks/$(TASK)/bin
	python3 ./tasks/$(TASK)/generate.py DEBUG > tasks/$(TASK)/debug.in

.PHONY: clean
clean: ## Remove atcoder.json, tasks/*. Clean up CMakeLists.txt
	rm -rf atcoder.json tasks/*
	sed -i 's|^.*add_executable.*$$||g' CMakeLists.txt
	sed -i '/^$$/d' CMakeLists.txt

# For AtCoder contest
.PHONY: atcoder
atcoder: ## Prepare atcoder contest: make atcoder CONTEST=abc200
	/bin/python3 tools/atcoder.py --contest $(CONTEST) > atcoder.json
	sh tools/tasks.sh

.PHONY: submit
submit: ## Submit source: make submit TASK=a
	make test TASK=$(TASK)
	jq ".tasks[] | select(.task == \"$(TASK)\") | .limit" < atcoder.json
	python3 tools/submit.py --contest=$$(jq -r ".contest" < atcoder.json) --task=$(TASK) --lang=cpp --source=tasks/$(TASK)/main.cpp

.PHONY: submit_py
submit_py: ## Submit source: make submit_py TASK=a
	make test_py TASK=$(TASK)
	jq ".tasks[] | select(.task == \"$(TASK)\") | .limit" < atcoder.json
	python3 tools/submit.py --contest=$$(jq -r ".contest" < atcoder.json) --task=$(TASK) --lang=py --source=tasks/$(TASK)/main.py

.PHONY: submit_force
submit_force: ## Force submit source: make submit_force TASK=a
	make test TASK=$(TASK) || true
	jq ".tasks[] | select(.task == \"$(TASK)\") | .limit" < atcoder.json
	python3 tools/submit.py --contest=$$(jq -r ".contest" < atcoder.json) --task=$(TASK) --lang=cpp --source=tasks/$(TASK)/main.cpp

.PHONY: submit_force_py
submit_force_py: ## Force submit source: make submit_force_py TASK=a
	make test_py TASK=$(TASK) || true
	jq ".tasks[] | select(.task == \"$(TASK)\") | .limit" < atcoder.json
	python3 tools/submit.py --contest=$$(jq -r ".contest" < atcoder.json) --task=$(TASK) --lang=py --source=tasks/$(TASK)/main.py
