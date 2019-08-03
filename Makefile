
.PHONY: debug
debug: debug_main
	./debug_main < input.txt

debug_main: main.cpp
	g++ -Wall -std=c++14 -DJUMPAKU_DEBUG -o debug_main main.cpp

.PHONY: run
run: a.out input.txt
	./a.out < input.txt

a.out: main.cpp
	g++ -std=c++14 -Wall main.cpp

.PHONY: clean
clean:
	rm ./debug_main ./a.out -f
