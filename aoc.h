#ifndef _AOC_H_
#define _AOC_H_

// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <map>
#include <iostream>

// Global flags.
extern bool	debug;
extern bool	use_colors;

// Function type for day solution.
typedef int (*dayfunction)(int, std::istream& is);
// Global map of day solution functions.
extern std::map<int, dayfunction> day_functions;

// Prototypes.
int day01(int, std::istream&);
int day02(int, std::istream&);
int day03(int, std::istream&);
int day04(int, std::istream&);
int day05(int, std::istream&);
int day06(int, std::istream&);
int day07(int, std::istream&);
int day08(int, std::istream&);
int day09(int, std::istream&);
int day10(int, std::istream&);
int day11(int, std::istream&);
int day12(int, std::istream&);
int day13(int, std::istream&);
int day14(int, std::istream&);
int day15(int, std::istream&);
int day16(int, std::istream&);
int day17(int, std::istream&);
int day18(int, std::istream&);
int day19(int, std::istream&);
int day20(int, std::istream&);
int day21(int, std::istream&);
int day22(int, std::istream&);
int day23(int, std::istream&);
int day24(int, std::istream&);
int day25(int, std::istream&);

#endif /* _AOC_H_ */
