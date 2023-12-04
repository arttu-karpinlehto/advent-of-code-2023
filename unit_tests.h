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


void test_day02() {
	std::stringstream input;
	input <<
"Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green\n\
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue\n\
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red\n\
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red\n\
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green";
	assert(8 == day02(1, input));

	input.clear();
	input.seekg(0);	// reset and rewind the stream
	assert(2286 == day02(2, input));
}


void test_day03() {
	std::stringstream input;
	input <<
"467..114..\n\
...*......\n\
..35..633.\n\
......#...\n\
617*......\n\
.....+.58.\n\
..592.....\n\
......755.\n\
...$.*....\n\
.664.598..";
	assert(4361 == day03(1, input));

	input.clear();
	input.seekg(0);	// reset and rewind the stream
	assert(467835 == day03(2, input));
}