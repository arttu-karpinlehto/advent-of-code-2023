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


void test_day04() {
	std::stringstream input;
	input <<
"Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53\n\
Card 2: 13 32 20 16 61 | 61 30 68 82 17 32 24 19\n\
Card 3:  1 21 53 59 44 | 69 82 63 72 16 21 14  1\n\
Card 4: 41 92 73 84 69 | 59 84 76 51 58  5 54 83\n\
Card 5: 87 83 26 28 32 | 88 30 70 12 93 22 82 36\n\
Card 6: 31 18 13 56 72 | 74 77 10 23 35 67 36 11";
	assert(13 == day04(1, input));

	input.clear();
	input.seekg(0);	// reset and rewind the stream
	assert(30 == day04(2, input));
}


void test_day05() {
	std::stringstream input;
	input <<
"seeds: 79 14 55 13\n\
\n\
seed-to-soil map:\n\
50 98 2\n\
52 50 48\n\
\n\
soil-to-fertilizer map:\n\
0 15 37\n\
37 52 2\n\
39 0 15\n\
\n\
fertilizer-to-water map:\n\
49 53 8\n\
0 11 42\n\
42 0 7\n\
57 7 4\n\
\n\
water-to-light map:\n\
88 18 7\n\
18 25 70\n\
\n\
light-to-temperature map:\n\
45 77 23\n\
81 45 19\n\
68 64 13\n\
\n\
temperature-to-humidity map:\n\
0 69 1\n\
1 0 69\n\
\n\
humidity-to-location map:\n\
60 56 37\n\
56 93 4";

	assert(35 == day05(1, input));

	input.clear();
	input.seekg(0);	// reset and rewind the stream
	assert(46 == day05(2, input));
}


void test_day06() {
	std::stringstream input;
	input <<
"Time:      7  15   30\n\
Distance:  9  40  200";

	assert(288 == day06(1, input));

	input.clear();
	input.seekg(0);	// reset and rewind the stream
	assert(71503 == day06(2, input));
	//assert(false);
}


void test_day07() {
	std::stringstream input;
	input <<
"32T3K 765\n\
T55J5 684\n\
KK677 28\n\
KTJJT 220\n\
QQQJA 483";

	assert(6440 == day07(1, input));

	input.clear();
	input.seekg(0);	// reset and rewind the stream
	assert(5905 == day07(2, input));
}


void test_day08() {
	std::stringstream input1;
	input1 <<
"RL\n\
\n\
AAA = (BBB, CCC)\n\
BBB = (DDD, EEE)\n\
CCC = (ZZZ, GGG)\n\
DDD = (DDD, DDD)\n\
EEE = (EEE, EEE)\n\
GGG = (GGG, GGG)\n\
ZZZ = (ZZZ, ZZZ)";

	assert(2 == day08(1, input1));

	std::stringstream input2;
	input2 <<
"LLR\n\
\n\
AAA = (BBB, BBB)\n\
BBB = (AAA, ZZZ)\n\
ZZZ = (ZZZ, ZZZ)";

	assert(6 == day08(1, input2));

	std::stringstream input3;
	input3 <<
"LR\n\
\n\
11A = (11B, XXX)\n\
11B = (XXX, 11Z)\n\
11Z = (11B, XXX)\n\
22A = (22B, XXX)\n\
22B = (22C, 22C)\n\
22C = (22Z, 22Z)\n\
22Z = (22B, 22B)\n\
XXX = (XXX, XXX)";

	assert(6 == day08(2, input3));
}
