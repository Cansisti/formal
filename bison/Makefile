SOURCE := $(wildcard ./src/*.cpp)

all: src/math.l src/math.y
	bison -d -o build/math.tab.c src/math.y
	flex -o build/lex.yy.c src/math.l
	g++ -Isrc -std=c++17 -Wall -g $(SOURCE) build/math.tab.c build/lex.yy.c -o build/math -ll