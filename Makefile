
# make init
# make clean
# make run
# make debug
# make test_sample
# make run_py
# make debug_py
# make test_sample_py
# make validate


.PHONY: init
init: clean init.sh
	./init.sh

.PHONY: clean
clean:
	rm ./debug_main ./main ./a.out  ./tmp/* validate_main validate_gen_main ./test_sample.out -f

# cpp
.PHONY: debug
debug: debug_main debug.in
	./debug_main < debug.in
debug_main: main.cpp
	g++ -std=c++14 -O2 -Wall -Wextra -DJUMPAKU_DEBUG -o debug_main main.cpp

.PHONY: run
run: main
	./main
main: main.cpp
	g++ -std=c++14 -O2 -Wall -Wextra -o main main.cpp

.PHONY: test_sample
test_sample: test_sample.sh main test_sample.in test_sample.ans
	./test_sample.sh "./main"

# python
.PHONY: debug_py
debug_py: main.py debug.in
	pypy3 main.py DEBUG < debug.in

.PHONY: run_py
run_py: main.py
	pypy3 main.py

.PHONY: test_sample_py
test_sample_py: test_sample.sh main.py test_sample.in test_sample.ans
	./test_sample.sh "python3 main.py"


# validate
validate_main: validate.cpp
	g++ -std=c++14 -O2 -Wall -Wextra -o validate_main validate.cpp
validate_gen_main: validate_gen.cpp
	g++ -std=c++14 -O2 -Wall -Wextra -o validate_gen_main validate_gen.cpp
.PHONY: validate
validate: validate.sh validate_main validate_gen_main main validate.py validate_gen.py main.py 
	./validate.sh 