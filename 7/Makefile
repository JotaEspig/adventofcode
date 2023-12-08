all: a.out b.out

a.out: solution1.cpp
	g++ solution1.cpp -o a.out

b.out: solution2.cpp
	g++ solution2.cpp -o b.out

.PHONY: run1
run1: a.out
	cat input | ./a.out

.PHONY: run2
run2: b.out
	cat input | ./b.out

.PHONY: clean
clean:
	@rm a.out
	@rm b.out
