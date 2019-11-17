flex:
	flex z3.l

build: flex
	g++ main.cpp lex.yy.c -ll -o z3

run: build
	./z3 < test.c > out.c 2> err.log

doxy: build
	./z3 -d < test.c > out.c 2> err.log