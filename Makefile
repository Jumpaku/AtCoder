
# make init
# make run
# make debug
# make test_sample N=n

.PHONY: debug
debug: debug_main debug.in
	./debug_main < debug.in
debug_main: main.cpp
	g++ -Wall -std=c++14 -DJUMPAKU_DEBUG -o debug_main main.cpp

.PHONY: run
run: main
	./main
main: main.cpp
	g++ -std=c++14 -O2 -Wall -o main main.cpp

.PHONY: init
init:
	: >| debug.in; : >| test_sample.in; : >| test_sample.ans
.PHONY: test_sample
test_sample: test_sample.sh main test_sample.in test_sample.ans
	./test_sample.sh ${N} < test_sample.in

.PHONY: clean
clean:
	rm ./debug_main ./main ./a.out -f


