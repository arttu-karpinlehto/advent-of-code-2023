/***
Advent of Code 2023 - 


***/

// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <algorithm>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>

#include "aoc.h"


struct a_to_b {
	long src;
	long dest;
	long len;

	bool match(long i) {
		if ((src <= i) && (i < (src+len))) return true;
		return false;
	}

	long destination(long i) {
		return dest + i - src;
	}
};


long findmatch(const std::vector<a_to_b>& a_to_b_map, long look_for) {
	long result = look_for;
	for (auto m : a_to_b_map) {
		if (m.match(look_for)) {
			result = m.destination(look_for);
			break;
		}
	}
	return result;
}


void readlines(std::istream& puzzle_input, std::vector<a_to_b>& output) {
	for (std::string line; std::getline(puzzle_input, line); ) {
		if (0 == line.length()) break;

		std::stringstream ss;
		ss.str(line);
		std::string s;
		std::getline(ss, s, ' ');
		long dest_start = std::stol(s);
		std::getline(ss, s, ' ');
		long src_start = std::stol(s);
		std::getline(ss, s);
		long len = std::stol(s);
		output.push_back({src_start, dest_start, len});
	}
	return;
}


void skiptoheader(std::istream& puzzle_input, std::string header) {
	std::string line;
	while (std::getline(puzzle_input, line)) {
		if (header == line) break;
	}
	if (debug) std::cout << "Skipped to: " << line << std::endl;
	return;
}


int day05(int puzzle_part, std::istream& puzzle_input)
{
	long lowest = __LONG_MAX__;	// Solution stored here.

	std::set<long> seeds;
	std::vector<a_to_b>	seed_to_soil;
	std::vector<a_to_b>	soil_to_fertilizer;
	std::vector<a_to_b>	fertilizer_to_water;
	std::vector<a_to_b>	water_to_light;
	std::vector<a_to_b>	light_to_temperature;
	std::vector<a_to_b>	temperature_to_humidity;
	std::vector<a_to_b>	humidity_to_location;

	// Parse first line of puzzle input.
	std::string line;
	std::getline(puzzle_input, line);
	std::stringstream ss;
	ss.str(line);
	for (std::string s; std::getline(ss, s, ' '); ) {
		if (isdigit(s[0])) {
			auto n = std::stol(s);
			seeds.insert(n);
		}
	}
	if (debug) {
		std::cout << "Seeds: ";
		for (auto n = seeds.begin(); n != seeds.end(); ++n) std::cout << *n << ",";
		std::cout << std::endl;
	}

	skiptoheader(puzzle_input, "seed-to-soil map:");
	readlines(puzzle_input, seed_to_soil);
	skiptoheader(puzzle_input, "soil-to-fertilizer map:");
	readlines(puzzle_input, soil_to_fertilizer);
	skiptoheader(puzzle_input, "fertilizer-to-water map:");
	readlines(puzzle_input, fertilizer_to_water);
	skiptoheader(puzzle_input, "water-to-light map:");
	readlines(puzzle_input, water_to_light);
	skiptoheader(puzzle_input, "light-to-temperature map:");
	readlines(puzzle_input, light_to_temperature);
	skiptoheader(puzzle_input, "temperature-to-humidity map:");
	readlines(puzzle_input, temperature_to_humidity);
	skiptoheader(puzzle_input, "humidity-to-location map:");
	readlines(puzzle_input, humidity_to_location);

	for (auto seed : seeds) {
		auto loc
		= findmatch(humidity_to_location,
			findmatch(temperature_to_humidity,
				findmatch(light_to_temperature,
					findmatch(water_to_light,
						findmatch(fertilizer_to_water,
							findmatch(soil_to_fertilizer,
								findmatch(seed_to_soil, seed)))))));

		if (debug) std::cout << "Location: " << loc << std::endl;

		lowest = std::min(lowest, loc);
	}

	if (debug) std::cout << "Lowest: " << lowest << std::endl;

	return lowest;
}

/*
*/
