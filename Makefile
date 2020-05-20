
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
	g++ -std=c++17 -O2 -Wall -Wextra -Wno-comment -DJUMPAKU_DEBUG -o debug_main main.cpp

.PHONY: run
run: main
	./main
main: main.cpp
	g++ -std=c++17 -O2 -Wall -Wextra -Wno-comment -o main main.cpp

.PHONY: sample
sample: sample.sh main sample.in sample.ans
	./sample.sh "./main"
.PHONY: sample_a
sample_a: sample.sh main samples/a.in samples/a.ans
	./sample.sh "./main" "./samples/a"
.PHONY: sample_b
sample_b: sample.sh main samples/b.in samples/b.ans
	./sample.sh "./main" "./samples/b"
.PHONY: sample_c
sample_c: sample.sh main samples/c.in samples/c.ans
	./sample.sh "./main" "./samples/c"
.PHONY: sample_d
sample_d: sample.sh main samples/d.in samples/d.ans
	./sample.sh "./main" "./samples/d"
.PHONY: sample_e
sample_e: sample.sh main samples/e.in samples/e.ans
	./sample.sh "./main" "./samples/e"
.PHONY: sample_f
sample_f: sample.sh main samples/f.in samples/f.ans
	./sample.sh "./main" "./samples/f"

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
.PHONY: sample_a_py
sample_a_py: sample.sh main.py samples/a.in samples/a.ans
	./sample.sh "pypy3 main.py" "samples/a"
.PHONY: sample_b_py
sample_b_py: sample.sh main.py samples/b.in samples/b.ans
	./sample.sh "pypy3 main.py" "samples/b"
.PHONY: sample_c_py
sample_c_py: sample.sh main.py samples/c.in sampls/c.ans
	./sample.sh "pypy3 main.py" "samples/c"
.PHONY: sample_d_py
sample_d_py: sample.sh main.py samples/d.in samples/d.ans
	./sample.sh "pypy3 main.py" "samples/d"
.PHONY: sample_e_py
sample_e_py: sample.sh main.py samples/e.in samples/e.ans
	./sample.sh "pypy3 main.py" "samples/e"
.PHONY: sample_f_py
sample_f_py: sample.sh main.py samples/f.in samples/f.ans
	./sample.sh "pypy3 main.py" "samples/f"


# validate
validate_main: validate.cpp
	g++ -std=c++17 -O2 -Wall -Wextra -Wno-comment -o validate_main validate.cpp
validate_gen_main: validate_gen.cpp
	g++ -std=c++17 -O2 -Wall -Wextra -Wno-comment -o validate_gen_main validate_gen.cpp
.PHONY: validate
validate: validate.sh validate_main validate_gen_main debug_main validate.py validate_gen.py main.py 
	./validate.sh 