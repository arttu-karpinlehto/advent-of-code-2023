/***
Advent of Code 2023 - Day 11: Cosmic Expansion

Part 1

You continue following signs for "Hot Springs" and eventually come across
an observatory. The Elf within turns out to be a researcher studying
cosmic expansion using the giant telescope here.

He doesn't know anything about the missing machine parts; he's only
visiting for this research project. However, he confirms that the hot
springs are the next-closest area likely to have people; he'll even take
you straight there once he's done with today's observation analysis.

Maybe you can help him with the analysis to speed things up?

The researcher has collected a bunch of data and compiled the data into a
single giant image (your puzzle input). The image includes empty space (.)
and galaxies (#). For example:

...#......
.......#..
#.........
..........
......#...
.#........
.........#
..........
.......#..
#...#.....

The researcher is trying to figure out the sum of the lengths of the
shortest path between every pair of galaxies. However, there's a catch:
the universe expanded in the time it took the light from those galaxies to
reach the observatory.

Due to something involving gravitational effects, only some space expands.
In fact, the result is that any rows or columns that contain no galaxies
should all actually be twice as big.

In the above example, three columns and two rows contain no galaxies:

   v  v  v
 ...#......
 .......#..
 #.........
>..........<
 ......#...
 .#........
 .........#
>..........<
 .......#..
 #...#.....
   ^  ^  ^

These rows and columns need to be twice as big; the result of cosmic
expansion therefore looks like this:

....#........
.........#...
#............
.............
.............
........#....
.#...........
............#
.............
.............
.........#...
#....#.......

Equipped with this expanded universe, the shortest path between every pair of galaxies can be found. It can help to assign every galaxy a unique number:

....1........
.........2...
3............
.............
.............
........4....
.5...........
............6
.............
.............
.........7...
8....9.......

In these 9 galaxies, there are 36 pairs. Only count each pair once; order
within the pair doesn't matter. For each pair, find any shortest path
between the two galaxies using only steps that move up, down, left, or
right exactly one . or # at a time. (The shortest path between two
galaxies is allowed to pass through another galaxy.)

For example, here is one of the shortest paths between galaxies 5 and 9:

....1........
.........2...
3............
.............
.............
........4....
.5...........
.##.........6
..##.........
...##........
....##...7...
8....9.......

This path has length 9 because it takes a minimum of nine steps to get
from galaxy 5 to galaxy 9 (the eight locations marked # plus the step onto
galaxy 9 itself). Here are some other example shortest path lengths:

Between galaxy 1 and galaxy 7: 15
Between galaxy 3 and galaxy 6: 17
Between galaxy 8 and galaxy 9: 5

In this example, after expanding the universe, the sum of the shortest
path between all 36 pairs of galaxies is 374.

Expand the universe, then find the length of the shortest path between
every pair of galaxies. What is the sum of these lengths?

Part 2

The galaxies are much older (and thus much farther apart) than the
researcher initially estimated.

Now, instead of the expansion you did before, make each empty row or
column one million times larger. That is, each empty row should be
replaced with 1000000 empty rows, and each empty column should be replaced
with 1000000 empty columns.

(In the example above, if each empty row or column were merely 10 times
larger, the sum of the shortest paths between every pair of galaxies would
be 1030. If each empty row or column were merely 100 times larger, the sum
of the shortest paths between every pair of galaxies would be 8410.
However, your universe will need to expand far beyond these values.)

Starting with the same initial image, expand the universe according to
these new rules, then find the length of the shortest path between every
pair of galaxies. What is the sum of these lengths?

***/

// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <algorithm>
#include <functional>
#include <numeric>
#include <set>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>

#include <cassert>

#include "aoc.h"


// Coordinate location.
struct coord {
	int x;
	int y;

	friend inline bool operator==(const coord& lhs, const coord& rhs) { return ((lhs.x == rhs.x) && (lhs.y == rhs.y)); }
	friend inline coord operator-(const coord& lhs, const coord& rhs) { return { lhs.x - rhs.x, lhs.y - rhs.y }; }
};


template <typename T>
void print_set(std::set<T> s) {
	for (const auto& i : s) {
		std::cout << i << " ";
	}
}

template <typename T>
void print_vec(std::vector<T> v) {
	for (const auto& i : v) {
		std::cout << i << " ";
	}
}

std::set<int> reverse_set(std::set<int> s) {
	std::set<int> n;
	for (int i = 0; i <= *s.rbegin(); ++i) {
		if (!s.contains(i)) {
			n.insert(i);
		}
	}
	return n;
}


int count_galaxies(const std::string s, std::set<int>& cols) {
	int count = 0;
	int col = 0;
	for (const auto& c : s) {
		if ('#' == c) {
			count += 1;
			cols.insert(col);
		}
		col += 1;
	}
	return count;
}


long day11(int puzzle_part, std::istream& puzzle_input)
{
	long total = 0;	// Solution result is stored here.

	std::vector<coord> galaxies;

	// Read puzzle input.
	{
		std::vector<std::string> lines;
		std::set<int> columns;
		for (std::string line; std::getline(puzzle_input, line); ) {
			lines.push_back(line);
			if (0 == count_galaxies(line, columns)) {
				lines.push_back(line);
			}
		}
		auto noncolumns = reverse_set(columns);
		if (debug) std::cout << "Lines: " << lines.size() << " Columns: " << lines[0].length() + noncolumns.size() << std::endl;
		//if (debug) std::cout << "Columns: "; print_set(noncolumns); std::cout << std::endl;
		
		for (auto line_it = lines.begin(); line_it != lines.end(); ++line_it) {
			for (auto col_it = noncolumns.crbegin(); col_it != noncolumns.crend(); ++col_it) {
				line_it->insert(*col_it, ".");
			}
			for (auto i = 0; i < line_it->length(); ++i) {
				if ('#' == line_it->at(i)) {
					galaxies.push_back(coord(i, std::distance(lines.begin(), line_it)));
				}
			}
		}

		if (debug) {
			for (auto s : lines) {
				std::cout << s << "\n";
			}
			for (auto g : galaxies) {
				std::cout << g.x << "," << g.y << "\n";
			}
		}
	}

	// Count distances
	{
		//int count = 0;
		for (auto g_it = galaxies.begin(); g_it != galaxies.end(); ++g_it) {
			for (auto gg_it = g_it + 1; gg_it != galaxies.end(); ++gg_it) {
				//std::cout << "Path: " << std::distance(galaxies.begin(), g_it) + 1 << " -> " << std::distance(galaxies.begin(), gg_it) + 1 << "  ";
				auto d = *gg_it - *g_it;
				//std::cout << d.x << "," << d.y << "\n";
				//count += 1;
				total += std::abs(d.x) + std::abs(d.y);
			}
		}
		//std::cout << "Count: " << count << std::endl;
	}



	if (debug) std::cout << "Total: " << total << std::endl;

	return total;
}


/*

*/
