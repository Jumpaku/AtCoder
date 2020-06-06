
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


CPP_COMMON_OPTIONS=-std=gnu++17 -O2 -Wall -Wextra -Wno-comment -DJUMPAKU_NO_BOOST

.PHONY: init
init: clean init.sh
	./init.sh

.PHONY: clean
clean:
	rm ./debug_main ./main ./a.out ./tmp/* ./samples/* validate_main validate_gen_main ./sample.out -f

.PHONY: sample_gen
sample_gen:
	python3 ./sample_gen.py < ./contest_data.txt

# cpp
.PHONY: debug
debug: debug_main debug.in
	./debug_main < debug.in
debug_main: main.cpp
	g++ $(CPP_COMMON_OPTIONS) -DJUMPAKU_DEBUG -o debug_main main.cpp

.PHONY: run
run: main
	./main
main: main.cpp
	g++ $(CPP_COMMON_OPTIONS) -o main main.cpp


.PHONY: sample
sample: sample.sh main sample.in sample.ans
	./sample.sh "./main" "./sample"
.PHONY: sample_%
sample_%: sample.sh main samples/%.in samples/%.ans
	./sample.sh "./main" "./samples/$*"
	
# python
.PHONY: debug_py
debug_py: main.py debug.in
	pypy3 main.py DEBUG < debug.in

.PHONY: run_py
run_py: main.py
	pypy3 main.py

.PHONY: sample_py
sample_py: sample.sh main.py sample.in sample.ans
	./sample.sh "pypy3 main.py"
.PHONY: sample_%_py
sample_%_py: sample.sh main.py samples/%.in samples/%.ans
	./sample.sh "pypy3 main.py" "samples/$*"

# validate
validate_main: validate.cpp
	g++ $(CPP_COMMON_OPTIONS) -o validate_main validate.cpp
validate_gen_main: validate_gen.cpp
	g++ $(CPP_COMMON_OPTIONS) -o validate_gen_main validate_gen.cpp
.PHONY: validate
validate: validate.sh validate_main validate_gen_main debug_main validate.py validate_gen.py main.py 
	./validate.sh 