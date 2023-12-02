/***
Advent of Code 2023 - Day 01: Trebuchet?!

Part 1

The newly-improved calibration document consists of lines of text;
each line originally contained a specific calibration value that the
Elves now need to recover. On each line, the calibration value can be
found by combining the first digit and the last digit (in that order)
to form a single two-digit number.

For example:

1abc2
pqr3stu8vwx
a1b2c3d4e5f
treb7uchet

In this example, the calibration values of these four lines are 12,
38, 15, and 77. Adding these together produces 142.

Consider your entire calibration document.
What is the sum of all of the calibration values?

Part Two

Your calculation isn't quite right. It looks like some of the digits are
actually spelled out with letters: one, two, three, four, five, six, seven,
eight, and nine also count as valid "digits".

Equipped with this new information, you now need to find the real first and
last digit on each line. For example:

two1nine
eightwothree
abcone2threexyz
xtwone3four
4nineeightseven2
zoneight234
7pqrstsixteen

In this example, the calibration values are 29, 83, 13, 24, 42, 14, and 76.
Adding these together produces 281.

What is the sum of all of the calibration values?

***/

// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <map>
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

#include "aoc.h"

// This map has the spelled out versions of digits 0-9.
std::map<unsigned int, std::string> numbers = {
	{0,"zero"}, {1,"one"}, {2,"two"}, {3,"three"}, {4,"four"}, {5,"five"}, {6,"six"}, {7,"seven"}, {8,"eight"}, {9,"nine"}
};


int day01(int part, std::istream& puzzle_input)
{
	unsigned long	total = 0;	// Sum of values stored here.

	// Parse each line of puzzle input.
	for (std::string line; std::getline(puzzle_input, line); ) {
		if (debug) std::cout << "Line: " << line << std::endl;

		// First and last numbers of each line.
		int first = -1;	// Negative value means "value not set".
		int last;

		// Iterate over each character of the line.
		for (auto line_it = line.begin(); line_it != line.end(); ++line_it) {
			char c = *line_it;
			if (isdigit(c)) {
				// Every encountered number is the last one of the line.
				last = c - '0';
				if (-1 == first) {
					first = last;	// Set first only when "value not set".
				}
			} else if (part == 2) {
				// In part 2, also consider spelled out numbers.
				// Try to find number strings from the line.
				for (const auto& num : numbers) {	// num = { number, "number" }
					// Length-limited string compare:
					//  line[current position .. +len("number")] == "number"
					if (strncmp(&line[std::distance(line.begin(), line_it)], num.second.c_str(), num.second.length()) == 0) {
						// Again, every encountered number is the last one of the line.
						last = num.first;
						if (-1 == first) {
							first = last;	// Set first only when "value not set".
						}
					}
				}
			}
		}

		if (debug) std::cout << "First: " << first << ", Last: " << last << std::endl;

		unsigned long value = 10 * first + last;
		total += value;
	}

	return total;
}

/*
Day 1 puzzle is very simple as it is line-oriented and the numbers are
single-digit.  In part 1, isdigit() does all the heavy lifting, and in
part 2 the length-limited string compare strncmp() is all we need.

The approach is very brute force, but effective.  Since we iterate over
every character, strncmp() will automatically handle possible edge cases
like 'twone'.  Using regular expressions is just overengineering.

Setting last value on every occurance of a number is also simple and
effective.  Reverse string matching is not necessary.
*/
