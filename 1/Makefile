run: build
	cat input | ./a.out
	cat input | ./b.out
	$(MAKE) clean

build:
	g++ solution1.cpp -o a.out
	g++ solution2.cpp -o b.out

clean:
	@rm a.out
	@rm b.out
