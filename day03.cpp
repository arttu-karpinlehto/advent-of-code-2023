/***
Advent of Code 2023 - Day 3: Gear Ratios

Part 1

You and the Elf eventually reach a gondola lift station; he says the
gondola lift will take you up to the water source, but this is as far as he
can bring you. You go inside.

It doesn't take long to find the gondolas, but there seems to be a problem:
they're not moving.

"Aaah!"

You turn around to see a slightly-greasy Elf with a wrench and a look of
surprise. "Sorry, I wasn't expecting anyone! The gondola lift isn't working
right now; it'll still be a while before I can fix it." You offer to help.

The engineer explains that an engine part seems to be missing from the
engine, but nobody can figure out which one. If you can add up all the part
numbers in the engine schematic, it should be easy to work out which part
is missing.

The engine schematic (your puzzle input) consists of a visual
representation of the engine. There are lots of numbers and symbols you
don't really understand, but apparently any number adjacent to a symbol,
even diagonally, is a "part number" and should be included in your sum.
(Periods (.) do not count as a symbol.)

Here is an example engine schematic:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, two numbers are not part numbers because they are not
adjacent to a symbol: 114 (top right) and 58 (middle right). Every other
number is adjacent to a symbol and so is a part number; their sum is 4361.

Of course, the actual engine schematic is much larger. What is the sum of
all of the part numbers in the engine schematic?

Part 2

The engineer finds the missing part and installs it in the engine! As the
engine springs to life, you jump in the closest gondola, finally ready to
ascend to the water source.

You don't seem to be going very fast, though. Maybe something is still
wrong? Fortunately, the gondola has a phone labeled "help", so you pick it
up and the engineer answers.

Before you can explain the situation, she suggests that you look out the
window. There stands the engineer, holding a phone in one hand and waving
with the other. You're going so slowly that you haven't even left the
station. You exit the gondola.

The missing part wasn't the only issue - one of the gears in the engine is
wrong. A gear is any * symbol that is adjacent to exactly two part numbers.
Its gear ratio is the result of multiplying those two numbers together.

This time, you need to find the gear ratio of every gear and add them all
up so that the engineer can figure out which gear needs to be replaced.

Consider the same engine schematic again:

467..114..
...*......
..35..633.
......#...
617*......
.....+.58.
..592.....
......755.
...$.*....
.664.598..

In this schematic, there are two gears. The first is in the top left; it
has part numbers 467 and 35, so its gear ratio is 16345. The second gear is
in the lower right; its gear ratio is 451490. (The * adjacent to 617 is not
a gear because it is only adjacent to one part number.) Adding up all of
the gear ratios produces 467835.

What is the sum of all of the gear ratios in your engine schematic?

***/

// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <vector>
#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <cassert>

#include "aoc.h"

// Engine parts are stored with their coordinates in the engine.
struct enginepart {
	int x, y;
	char symbol;
};

// Part numbers are stored with a bounding box that extends one
// column and one line around the number.
// +---+
// |123|
// +---+
struct partnumber {
	int number;
	struct {
		int x0, y0, x1, y1;
	} box;

	partnumber(int n, int x, int y) : number(n) {
		assert(n <= 99999);	// We handle only 5 digit part numbers.
		size_t len = 1 + (n > 9 ? 1 : 0) + (n > 99 ? 1 : 0) + (n > 999 ? 1 : 0) + (n > 9999 ? 1 : 0);
		box.x0 = x - (x > 0 ? 1 : 0);
		box.x1 = x + len;
		box.y0 = y - (y > 0 ? 1 : 0);
		box.y1 = y + 1;
	}

	// Returns true when enginepart coordinates hit the bounding box.
	bool isadjacent(const enginepart& ep) const {
		if ((ep.x < box.x0) || (ep.x > box.x1)) return false;
		if ((ep.y < box.y0) || (ep.y > box.y1)) return false;
		return true;
	}
};


long day03(int puzzle_part, std::istream& puzzle_input)
{
	long sum = 0;	// Solution stored here.

	std::vector<partnumber> partnumbers;
	std::vector<enginepart> engineparts;

	// Parse each line of puzzle input.
	int y = 0;
	for (std::string line; std::getline(puzzle_input, line); ++y) {
		for (int x = 0; auto c = line[x]; ++x) {
			if ('.' == c) continue;
			if (isdigit(c)) {
				// Extract the number from position x and store into partnumbers list.
				auto end = line.find_first_not_of("0123456789", x);
				if (std::string::npos == end) end = line.length();	// Catch numbers that are at the very end of line.
				auto num = std::stoi(line.substr(x, end - x));
				partnumbers.push_back(partnumber(num, x, y));
				if (debug) std::cout << "Part number: " << num << " at " << x << "," << y << std::endl;
				x = end - 1;	// -1 because of ++x // potential bug location here
			} else {
				// Store the engine part into the list.
				engineparts.push_back({x, y, c});
				if (debug) std::cout << "Engine part: " << c << " at " << x << "," << y << std::endl;
			}
		}
	}

	if (1 == puzzle_part) {
		// For part 1, iterate through all part numbers.
		// Add them to the sum if there is an adjacent engine part.
		for (const auto& pn_it : partnumbers) {
			for (const auto& ep_it : engineparts) {
				if (true == pn_it.isadjacent(ep_it)) {
					sum += pn_it.number;
					break;
				}
			}
		}
	} else {
		// For part 2, iterate through all engine parts.
		// For each gear (*), look for two adjacent part numbers
		// and add their product to the sum.
		for (const auto& ep_it : engineparts) {
			if ('*' == ep_it.symbol) {
				int first = -1;	// negative value for "value not set"
				int second = -1;
				for (const auto& pn_it : partnumbers) {
					if (true == pn_it.isadjacent(ep_it)) {
						if (-1 == first) {
							first = pn_it.number;
						} else if (-1 == second) {
							second = pn_it.number;
							sum += first * second;
							break;
						}
					}
				}
			}
		}
	}

	if (debug) std::cout << "Sum: " << sum << std::endl;

	return sum;
}

/*
Like many AoC puzzles, this is about how do you store the input data
so that it is most convenient to process.
This code could use some optimisations; iterating over both lists
is crude, but at least with these data sizes it's not a performance issue.
Part numbers and engine parts could be mapped with y so that seeking
adjacent parts would be faster (initial code actually had that but it
added complexity and arguably no visible benefit).
*/
