// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <cassert>
#include <sstream>

#include "aoc.h"

// Global flags.
bool debug = true;

void test_day01() {
	std::stringstream input1;
	input1 <<
"1abc2\n\
pqr3stu8vwx\n\
a1b2c3d4e5f\n\
treb7uchet";
	assert(142 == day01(1, input1));

	std::stringstream input2;
	input2 <<
"two1nine\n\
eightwothree\n\
abcone2threexyz\n\
xtwone3four\n\
4nineeightseven2\n\
zoneight234\n\
7pqrstsixteen";
	assert(281 == day01(2, input2));
}
