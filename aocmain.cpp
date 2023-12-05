// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "aoc.h"

// Global flags.
bool debug = false;
bool use_colors = true;

// Add day solution functions in this map.
std::map<int, dayfunction> day_functions = {
	{1, day01}, {2, day02}, {3, day03}, {4, day04}, {5, day05}
};


// AoC main.
int main(int argc, char* argv[])
{
	int AoC_year = 2023;
	int AoC_day = 0;
	int AoC_part = 0;

	// Argument handling.
	if (argc > 2) {
		int day = atoi(argv[1]);
		if ((1 <= day) && (day <= 25)) {
			AoC_day = day;
		}

		int part = atoi(argv[2]);
		if ((part == 1) || (part == 2)) {
			AoC_part = part;
		}

		if (argc > 3) {
			if (std::string(argv[3]) == "debug") {
				debug = true;
			}
		}
	}

	// Title banner, with optional colours.
	int col = AoC_part;
	std::stringstream header;
	std::string blink;
	header << "\n*** Advent of Code " << AoC_year << " Day " << AoC_day << ", Part " << AoC_part << " ***\n";
	if (use_colors) {
		std::cout << "\x1B[1m";
		for (auto c : header.str()) {
			if (c == '*') blink = "5;";
			else blink = "";
			std::cout << "\x1B[" << blink << "3" << col << "m" << c;
			if (col == 1) col = 2;
			else if (col == 2) col = 7;
			else if (col == 7) col = 1;
		}
		std::cout << "\x1B[0m" << std::endl;
	} else {
		std::cout << header.str() << std::endl;
	}

	// Input file and day solution function invocation.
	std::ifstream puzzle_input;
	auto f = day_functions.find(AoC_day);
	int result = 0;
	if (f != day_functions.end()) {
		// Puzzle input file should be named "dayNN-input.txt".
		std::stringstream filename;
		filename << "day" << std::string((AoC_day < 10) ? "0" : "") << AoC_day << "-input.txt";

		if (use_colors) std::cout << "\x1B[34m";
		std::cout << "Puzzle input: " << filename.str() << std::endl;
		if (use_colors) std::cout << "\x1B[0m";

		puzzle_input.open(filename.str());
		if (puzzle_input.is_open()) {
			// Solve the puzzle!
			result = f->second(AoC_part, puzzle_input);
		}

		if (use_colors) std::cout << "\x1B[1;33m";
		std::cout << "Result: ";
		if (use_colors) std::cout << "\x1B[0;33m";
		std::cout << result;
		if (use_colors) std::cout << "\x1B[0m";
		std::cout << std::endl;
	}

	return 0;
}
