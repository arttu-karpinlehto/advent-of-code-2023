#ifndef _AOC_H_
#define _AOC_H_

// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <map>
#include <set>
#include <vector>
#include <iostream>

// Global flags.
extern bool	debug;
extern bool unit_testing;
extern bool	use_colors;

// Some utility stuff.
template <typename T>
void print_set(std::set<T> s)
{
	for (const auto& i : s) {
		std::cout << i << " ";
	}
};

template <typename T>
void print_vec(std::vector<T> v)
{
	for (const auto& i : v) {
		std::cout << i << " ";
	}
};


// Function type for day solution.
typedef long (*dayfunction)(int, std::istream& is);
// Global map of day solution functions.
extern std::map<int, dayfunction> day_functions;

// Prototypes.
long day01(int, std::istream&);
long day02(int, std::istream&);
long day03(int, std::istream&);
long day04(int, std::istream&);
long day05(int, std::istream&);
long day06(int, std::istream&);
long day07(int, std::istream&);
long day08(int, std::istream&);
long day09(int, std::istream&);
long day10(int, std::istream&);
long day11(int, std::istream&);
long day12(int, std::istream&);
long day13(int, std::istream&);
long day14(int, std::istream&);
long day15(int, std::istream&);
long day16(int, std::istream&);
long day17(int, std::istream&);
long day18(int, std::istream&);
long day19(int, std::istream&);
long day20(int, std::istream&);
long day21(int, std::istream&);
long day22(int, std::istream&);
long day23(int, std::istream&);
long day24(int, std::istream&);
long day25(int, std::istream&);

#endif /* _AOC_H_ */
