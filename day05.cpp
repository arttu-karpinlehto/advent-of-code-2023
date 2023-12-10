/***
Advent of Code 2023 - Day 5: If You Give A Seed A Fertilizer

Part 1

You take the boat and find the gardener right where you were told he would
be: managing a giant "garden" that looks more to you like a farm.

"A water source? Island Island is the water source!" You point out that
Snow Island isn't receiving any water.

"Oh, we had to stop the water because we ran out of sand to filter it
with! Can't make snow with dirty water. Don't worry, I'm sure we'll get
more sand soon; we only turned off the water a few days... weeks... oh
no." His face sinks into a look of horrified realization.

"I've been so busy making sure everyone here has food that I completely
forgot to check why we stopped getting more sand! There's a ferry leaving
soon that is headed over in that direction - it's much faster than your
boat. Could you please go check it out?"

You barely have time to agree to this request when he brings up another.
"While you wait for the ferry, maybe you can help us with our food
production problem. The latest Island Island Almanac just arrived and
we're having trouble making sense of it."

The almanac (your puzzle input) lists all of the seeds that need to be
planted. It also lists what type of soil to use with each kind of seed,
what type of fertilizer to use with each kind of soil, what type of water
to use with each kind of fertilizer, and so on. Every type of seed, soil,
fertilizer and so on is identified with a number, but numbers are reused
by each category - that is, soil 123 and fertilizer 123 aren't necessarily
related to each other.

For example:

seeds: 79 14 55 13

seed-to-soil map:
50 98 2
52 50 48

soil-to-fertilizer map:
0 15 37
37 52 2
39 0 15

fertilizer-to-water map:
49 53 8
0 11 42
42 0 7
57 7 4

water-to-light map:
88 18 7
18 25 70

light-to-temperature map:
45 77 23
81 45 19
68 64 13

temperature-to-humidity map:
0 69 1
1 0 69

humidity-to-location map:
60 56 37
56 93 4

The almanac starts by listing which seeds need to be planted: seeds 79,
14, 55, and 13.

The rest of the almanac contains a list of maps which describe how to
convert numbers from a source category into numbers in a destination
category. That is, the section that starts with seed-to-soil map:
describes how to convert a seed number (the source) to a soil number (the
destination). This lets the gardener and his team know which soil to use
with which seeds, which water to use with which fertilizer, and so on.

Rather than list every source number and its corresponding destination
number one by one, the maps describe entire ranges of numbers that can be
converted. Each line within a map contains three numbers: the destination
range start, the source range start, and the range length.

Consider again the example seed-to-soil map:

50 98 2 52 50 48 The first line has a destination range start of 50, a
source range start of 98, and a range length of 2. This line means that
the source range starts at 98 and contains two values: 98 and 99. The
destination range is the same length, but it starts at 50, so its two
values are 50 and 51. With this information, you know that seed number 98
corresponds to soil number 50 and that seed number 99 corresponds to soil
number 51.

The second line means that the source range starts at 50 and contains 48
values: 50, 51, ..., 96, 97. This corresponds to a destination range
starting at 52 and also containing 48 values: 52, 53, ..., 98, 99. So,
seed number 53 corresponds to soil number 55.

Any source numbers that aren't mapped correspond to the same destination
number. So, seed number 10 corresponds to soil number 10.

So, the entire list of seed numbers and their corresponding soil numbers
looks like this:

seed  soil
0     0
1     1
...   ...
48    48
49    49
50    52
51    53
...   ...
96    98
97    99
98    50
99    51

With this map, you can look up the soil number required for each initial
seed number:

 - Seed number 79 corresponds to soil number 81.
 - Seed number 14 corresponds to soil number 14.
 - Seed number 55 corresponds to soil number 57.
 - Seed number 13 corresponds to soil number 13.

 The gardener and his team want to get started as soon as possible, so
 they'd like to know the closest location that needs a seed. Using these
 maps, find the lowest location number that corresponds to any of the
 initial seeds. To do this, you'll need to convert each seed number
 through other categories until you can find its corresponding location
 number. In this example, the corresponding types are:

 - Seed 79, soil 81, fertilizer 81, water 81, light 74, temperature 78,
   humidity 78, location 82.
 - Seed 14, soil 14, fertilizer 53, water 49, light 42, temperature 42,
   humidity 43, location 43.
 - Seed 55, soil 57, fertilizer 57, water 53, light 46, temperature 82,
   humidity 82, location 86.
 - Seed 13, soil 13, fertilizer 52, water 41, light 34, temperature 34,
   humidity 35, location 35.

 So, the lowest location number in this example is 35.

What is the lowest location number that corresponds to any of the initial
seed numbers?

Part 2

Everyone will starve if you only plant such a small number of seeds.
Re-reading the almanac, it looks like the seeds: line actually describes
ranges of seed numbers.

The values on the initial seeds: line come in pairs. Within each pair, the
first value is the start of the range and the second value is the length
of the range. So, in the first line of the example above:

seeds: 79 14 55 13 This line describes two ranges of seed numbers to be
planted in the garden. The first range starts with seed number 79 and
contains 14 values: 79, 80, ..., 91, 92. The second range starts with seed
number 55 and contains 13 values: 55, 56, ..., 66, 67.

Now, rather than considering four seed numbers, you need to consider a
total of 27 seed numbers.

In the above example, the lowest location number can be obtained from seed
number 82, which corresponds to soil 84, fertilizer 84, water 84, light
77, temperature 45, humidity 46, and location 46. So, the lowest location
number is 46.

Consider all of the initial seed numbers listed in the ranges on the first
line of the almanac. What is the lowest location number that corresponds
to any of the initial seed numbers?

***/

// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <algorithm>
#include <functional>
#include <array>
#include <set>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>

#include <thread>

#include "aoc.h"


// Each something-to-something map is stored in this data structure.
struct a_to_b {
	// Some of these values are pre-calculated for marginally faster execution.
	const long src_begin;
	const long src_end;
	const long offset;

	a_to_b(long s, long d, long l) : src_begin(s), src_end(s + l), offset(d - s) {}

	// If input value matches the source range of this item, return true.
	bool match(const long i) const {
		if (src_begin > i) return false;
		if (src_end <= i) return false;
		return true;
	}

	// Return the destination location for given input,
	// assuming input matches the source range.
	long destination(const long i) const {
		return offset + i;
	}

	// Needed for std::set
	friend inline bool operator<(const a_to_b& lhs, const a_to_b& rhs) { return lhs.src_begin < rhs.src_begin; }
};

// For input value look_for, return the destination value using a_to_b_map.
long findmatch(const std::set<a_to_b>& a_to_b_map, const long look_for) {
	for (const auto& m : a_to_b_map) {
		if (m.match(look_for)) {
			return m.destination(look_for);
		}
	}
	return look_for;
}

// Reads puzzle_input lines and inserts values to given a_to_b set.
void readlines(std::istream& puzzle_input, std::set<a_to_b>& output) {
	for (std::string line; std::getline(puzzle_input, line); ) {
		if (0 == line.length()) break;	// Stop when empty line encountered.

		std::stringstream ss;
		ss.str(line);
		std::string s;
		std::getline(ss, s, ' ');
		long dest_start = std::stol(s);
		std::getline(ss, s, ' ');
		long src_start = std::stol(s);
		std::getline(ss, s);
		long len = std::stol(s);
		output.insert({src_start, dest_start, len});
	}
	return;
}

// Reads puzzle_input and consumes the given header line,
// moving the input pointer to the first line of map values.
void skiptoheader(std::istream& puzzle_input, std::string header) {
	std::string line;
	while (std::getline(puzzle_input, line)) {
		if (header == line) break;
	}
	if (debug) std::cout << "Skipped to: " << line << std::endl;
	return;
}

// This is not used anymore, but would traverse the a_to_b maps
// given in an array to find a location for the seed.
long location(const std::array<std::set<a_to_b>, 7>& abmaps, const long seed) {
	return findmatch(abmaps[6],
	findmatch(abmaps[5],
	findmatch(abmaps[4],
	findmatch(abmaps[3],
	findmatch(abmaps[2],
	findmatch(abmaps[1],
	findmatch(abmaps[0], seed)))))));
}

// All a_to_b maps are global as we use them in rangelowest() function.
std::set<a_to_b>	seed_to_soil;
std::set<a_to_b>	soil_to_fertilizer;
std::set<a_to_b>	fertilizer_to_water;
std::set<a_to_b>	water_to_light;
std::set<a_to_b>	light_to_temperature;
std::set<a_to_b>	temperature_to_humidity;
std::set<a_to_b>	humidity_to_location;

// Finds the lowest location for given seed range.
// The lowest value is both returned and assigned to the calling argument.
long rangelowest(long seed_first, long seed_end, long& lowest) {
	if (debug) std::cout << "Seeds " << seed_first << "-" << seed_end << ": " << seed_end - seed_first << std::endl;

	lowest = __LONG_MAX__;
	for (auto seed = seed_first; seed < seed_end; ++seed) {
		lowest = std::min(lowest, findmatch(humidity_to_location,
			findmatch(temperature_to_humidity,
			findmatch(light_to_temperature,
			findmatch(water_to_light,
			findmatch(fertilizer_to_water,
			findmatch(soil_to_fertilizer,
			findmatch(seed_to_soil, seed))))))));
	}

	if (debug) std::cout << "Lowest: " << lowest << std::endl;
	return lowest;
}


long day05(int puzzle_part, std::istream& puzzle_input)
{
	long lowest = __LONG_MAX__;	// Solution stored here.

	//std::set<long> seeds;	// Seeds were just a set for part 1.
	std::map<long, long>	seedranges;	// For part 2, seed ranges.

	// Array used in threading version.
	//std::array<std::set<a_to_b>, 7> a_to_b_maps;

	// Parse first line of puzzle input, the seeds.
	if (1 == puzzle_part) {
		std::string line;
		std::getline(puzzle_input, line);
		std::stringstream ss;
		ss.str(line);
		for (std::string s; std::getline(ss, s, ' '); ) {
			if (isdigit(s[0])) {
				auto n = std::stol(s);
				seedranges.insert({n, n});
			}
		}
	} else {
		std::string line;
		std::getline(puzzle_input, line);
		std::stringstream ss;
		ss.str(line);
		long n, m;
		bool flippyfloppy = true;
		for (std::string s; std::getline(ss, s, ' '); ) {
			if (isdigit(s[0])) {
				if (flippyfloppy) {
					n = std::stol(s);
				} else {
					m = std::stol(s);
					seedranges.insert({n, n + m - 1});
				}
				flippyfloppy ^= 1;
			}
		}
	}
	if (debug) {
		std::cout << "Seeds: ";
		for (auto n = seedranges.begin(); n != seedranges.end(); ++n) std::cout << n->first << "-" << n->second << ",";
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
	if (debug) std::cout << "Seed ranges: " << seedranges.size() << std::endl;

	long low;	// Dummy, but needed to call rangelowest().
	for (const auto& seedrange : seedranges) {
		lowest = std::min(lowest, rangelowest(seedrange.first, seedrange.second + 1, low));
	}
	// Threaded version, not particularly fast for some reason.
	// long* lows = new long[50];
	// std::thread* threads = new std::thread[50];
	// int t = 0;
	// for (const auto& seedrange : seedranges) {
		// threads[t] = std::thread(rangelowest, seedrange.first, seedrange.second + 1, std::ref(lows[t]));
		// if (debug) std::cout << "Thread " << t << " created." << std::endl;
		// ++t;
	// }
	// for (auto i = 0; i < t; ++i) {
	// 	threads[i].join();
	// 	if (debug) std::cout << "Thread " << i << " ended." << std::endl;
	// 	long low;
	// 	lowest = std::min(lowest, lows[i]);
	// }
	//delete[] threads;
	//delete[] lows;

	if (debug) std::cout << "Lowest: " << lowest << std::endl;

	return lowest;
}

/*
Input parsing was not too complicated, but the large data management in
part 2 was. First implementation part 2 too 32m 21s non-optimised.
Optimised build was much faster, 2m 38s.

Second implementation, 2m 35s. Raw data looping is not that susceptible
for optimisations. There might be some higher math solution to this
puzzle, but I don't have the patience or motivation.

Tried multithreading, but setting up and waiting threads seemed to
generate too much overhead. Also, system thread count is limited
in Linux and the puzzle data generated more than 3 million threads.
Second attempt with threads, only 10 threads but still as slow as
without threads.
*/
