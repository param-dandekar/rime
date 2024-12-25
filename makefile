ASSM_SRC_DIR=src/rime
ASSM_INC_DIR=include/rime

PARSER=parser
LEXER=lexer

PARSER_OUT=${ASSM_SRC_DIR}/${PARSER}.c
LEXER_OUT=${ASSM_SRC_DIR}/${LEXER}.yy.c

ASSM_EXEC=rc

default: all

all: build

.PHONY: build clean-all clean-build clean-assembler debug reconfig assembler

build:
	make -C ./build VERBOSE=1

assembler:
	bison --output=${PARSER_OUT} --defines=${ASSM_INC_DIR}/${PARSER}.h ${ASSM_SRC_DIR}/${PARSER}.y
	flex --outfile=${LEXER_OUT} ${ASSM_SRC_DIR}/${LEXER}.l ${ASSM_INC_DIR}/${PARSER}.h
	gcc -o ${ASSM_EXEC} -I ${ASSM_INC_DIR} ${PARSER_OUT} ${LEXER_OUT} -lfl

clean-all: clean-build clean-assembler

clean-assembler:
	rm -f ${ASSM_EXEC} ${PARSER_OUT} ${LEXER_OUT}

clean-build:
	make -C ./build clean

debug:
	cmake -DCMAKE_BUILD_TYPE=Debug ./build
	$(MAKE) build

reconfig:
	rm -rf build
	mkdir build
	cd build && cmake ..
