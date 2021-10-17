# AtCoder

Competitive programming environment that supports C++ 14 and Python 3.

1. Open folder in container with VSCode Insiders.
2. Type `make help` to see help.


ac-gen --contest id
ac-submit --problem p
ac-submit_force --problem p

test --work_dir p --entry main
run --in i --out o --work_dir p --src main
debug  --in i --out o --work_dir p --src main

contest/
    data/
        current.id
        arc128/
    a/
        bin/
        test/
            *.in
            *.ans
            *.out
        main.cpp
        main.py