ASSM_SRC_DIR=src/rime
ASSM_INC_DIR=include/rime

PARSER=parser
LEXER=lexer

PARSER_OUT=${ASSM_SRC_DIR}/${PARSER}.c
LEXER_OUT=${ASSM_SRC_DIR}/${LEXER}.yy.c

ASSM_EXEC=rc

default: all

all: processor assembler

.PHONY: build clean clean-processor clean-assembler debug reconfig

processor:
	cd ./build && cmake --build . --target rime VERBOSE=1

assembler:
	cd ./build && cmake --build . --target rc VERBOSE=1

clean: clean-processor clean-assembler

clean-assembler:
	rm -f ${ASSM_EXEC} ${PARSER_OUT} ${LEXER_OUT}

clean-processor:
	make -C ./build clean

debug:
	cmake -DCMAKE_BUILD_TYPE=Debug ./build
	$(MAKE) build

reconfig:
	rm -rf build
	mkdir build
	cd build && cmake ..
