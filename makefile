PARSER="rime"
LEXER="rime"
COMPILER="rimec"

default: all

all: build

.PHONY: build clean-all clean-build clean-parser debug reconfig parser

build:
	make -C ./build VERBOSE=1
	./assemble.sh

parser:
	bison -d $(PARSER).y
	flex $(LEXER).l
	gcc -o $(COMPILER) $(PARSER).tab.c lex.yy.c -lfl

clean-all: clean-build clean-parser

clean-parser:
	rm -f $(PARSER).tab.* lex.*

clean-build:
	make -C ./build clean

debug:
	cmake -DCMAKE_BUILD_TYPE=Debug ./build
	$(MAKE) build

reconfig:
	rm -rf build
	mkdir build
	cd build && cmake ..
