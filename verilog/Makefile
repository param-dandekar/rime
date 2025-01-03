SOURCES = clock.v buffer.v register.v memory.v test.v
EXEC		= out

default: all

all: build run

build:
	iverilog -o ${EXEC} ${SOURCES}

run:
	vvp ${EXEC}

gtk: run
	gtkwave output.vcd

