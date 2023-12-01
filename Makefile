CXX = g++

CFLAGS = -fdiagnostics-color=always\
		-std=gnu++20

SRCS := $(wildcard *.cpp)
OBJS := $(wildcard day*.o)

TODAY = $(shell date +'%d')

.PHONY: all
all: aoc2023 runtoday

.PHONY: runtoday
runtoday: aoc2023 day${TODAY}-input.txt
	@./aoc2023 ${TODAY} 1 || true
	@./aoc2023 ${TODAY} 2 || true

aoc2023: aocmain.o ${OBJS}
	${CXX} $^ -o $@

%.o: %.cpp aoc.h
	${CXX} ${CFLAGS} -pipe -g -c $< -o $@

.PHONY: unit_test
unit_test: unit_test_driver.o ${OBJS}
	${CXX} $^

