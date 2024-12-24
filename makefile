PARSER="rime"
LEXER="rime"
COMPILER="rimec"

default: all

all: build

.PHONY: build clean-all clean-build clean-compiler debug reconfig compiler

build:
	make -C ./build VERBOSE=1

compiler:
	cd src/${COMPILER} &&\
	bison -d ${PARSER}.y &&\
	flex ${LEXER}.l &&\
	gcc -o ../../${COMPILER} ${PARSER}.tab.c lex.yy.c -lfl

clean-all: clean-build clean-compiler

clean-compiler:
	cd src/${COMPILER} &&\
	rm -f ${PARSER}.tab.* lex.* &&\
	rm -f ${COMPILER}

clean-build:
	make -C ./build clean

debug:
	cmake -DCMAKE_BUILD_TYPE=Debug ./build
	$(MAKE) build

reconfig:
	rm -rf build
	mkdir build
	cd build && cmake ..
