flex:
	flex z2.l

build: flex
	g++ main.cpp lex.yy.c -ll -o z2

run: build
	./z2 < test.xml > out.xml 2> err.log