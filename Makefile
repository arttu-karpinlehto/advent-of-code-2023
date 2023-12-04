CXX = g++

CFLAGS = -std=gnu++20
EXTRAFLAGS = -fdiagnostics-color=always -g
#EXTRAFLAGS = -O3

SRCS := $(wildcard day*.cpp)
OBJS := $(SRCS:.cpp=.o)

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
	${CXX} ${CFLAGS} ${EXTRAFLAGS} -pipe -c $< -o $@

.PHONY: unit_test
unit_test: unit_test_driver.o ${OBJS}
	echo ${OBJS}
	${CXX} $^

.PHONY: clean
clean:
	rm *.o
