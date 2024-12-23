default: all

all: build

.PHONY: build clean debug reconfig

build:
	make -C ./build VERBOSE=1
	./assemble.sh

clean:
	make -C ./build clean

debug:
	cmake -DCMAKE_BUILD_TYPE=Debug ./build
	$(MAKE) build

reconfig:
	rm -rf build
	mkdir build
	cd build && cmake ..
