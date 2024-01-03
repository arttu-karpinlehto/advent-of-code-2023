/***
Advent of Code 2023 - Day 10: Pipe Maze

Part 1

You use the hang glider to ride the hot air from Desert Island all the way
up to the floating metal island. This island is surprisingly cold and
there definitely aren't any thermals to glide on, so you leave your hang
glider behind.

You wander around for a while, but you don't find any people or animals.
However, you do occasionally find signposts labeled "Hot Springs" pointing
in a seemingly consistent direction; maybe you can find someone at the hot
springs and ask them where the desert-machine parts are made.

The landscape here is alien; even the flowers and trees are made of metal.
As you stop to admire some metal grass, you notice something metallic
scurry away in your peripheral vision and jump into a big pipe! It didn't
look like any animal you've ever seen; if you want a better look, you'll
need to get ahead of it.

Scanning the area, you discover that the entire field you're standing on
is densely packed with pipes; it was hard to tell at first because they're
the same metallic silver color as the "ground". You make a quick sketch of
all of the surface pipes you can see (your puzzle input).

The pipes are arranged in a two-dimensional grid of tiles:

 - | is a vertical pipe connecting north and south.
 - - is a horizontal pipe connecting east and west.
 - L is a 90-degree bend connecting north and east.
 - J is a 90-degree bend connecting north and west.
 - 7 is a 90-degree bend connecting south and west.
 - F is a 90-degree bend connecting south and east.
 - . is ground; there is no pipe in this tile.
 - S is the starting position of the animal; there is a pipe on this tile,
   but your sketch doesn't show what shape the pipe has.

Based on the acoustics of the animal's scurrying, you're confident the
pipe that contains the animal is one large, continuous loop.

For example, here is a square loop of pipe:

.....
.F-7.
.|.|.
.L-J.
.....

If the animal had entered this loop in the northwest corner, the sketch
would instead look like this:

.....
.S-7.
.|.|.
.L-J.
.....

In the above diagram, the S tile is still a 90-degree F bend: you can tell
because of how the adjacent pipes connect to it.

Unfortunately, there are also many pipes that aren't connected to the
loop! This sketch shows the same loop as above:

-L|F7
7S-7|
L|7||
-L-J|
L|-JF

In the above diagram, you can still figure out which pipes form the main
loop: they're the ones connected to S, pipes those pipes connect to, pipes
those pipes connect to, and so on. Every pipe in the main loop connects to
its two neighbors (including S, which will have exactly two pipes
connecting to it, and which is assumed to connect back to those two
pipes).

Here is a sketch that contains a slightly more complex main loop:

..F7.
.FJ|.
SJ.L7
|F--J
LJ...

Here's the same example sketch with the extra, non-main-loop pipe tiles
also shown:

7-F7-
.FJ|7
SJLL7
|F--J
LJ.LJ

If you want to get out ahead of the animal, you should find the tile in
the loop that is farthest from the starting position. Because the animal
is in the pipe, it doesn't make sense to measure this by direct distance.
Instead, you need to find the tile that would take the longest number of
steps along the loop to reach from the starting point - regardless of
which way around the loop the animal went.

In the first example with the square loop:

.....
.S-7.
.|.|.
.L-J.
.....

You can count the distance each tile in the loop is from the starting
point like this:

.....
.012.
.1.3.
.234.
.....

In this example, the farthest point from the start is 4 steps away.

Here's the more complex loop again:

..F7.
.FJ|.
SJ.L7
|F--J
LJ...

Here are the distances for each tile on that loop:

..45.
.236.
01.78
14567
23...

Find the single giant loop starting at S. How many steps along the loop
does it take to get from the starting position to the point farthest from
the starting position?

Part 2

You quickly reach the farthest point of the loop, but the animal never
emerges. Maybe its nest is within the area enclosed by the loop?

To determine whether it's even worth taking the time to search for such a
nest, you should calculate how many tiles are contained within the loop.
For example:

...........
.S-------7.
.|F-----7|.
.||.....||.
.||.....||.
.|L-7.F-J|.
.|..|.|..|.
.L--J.L--J.
...........

The above loop encloses merely four tiles - the two pairs of . in the
southwest and southeast (marked I below). The middle . tiles (marked O
below) are not in the loop. Here is the same loop again with those regions
marked:

...........
.S-------7.
.|F-----7|.
.||OOOOO||.
.||OOOOO||.
.|L-7OF-J|.
.|II|O|II|.
.L--JOL--J.
.....O.....

In fact, there doesn't even need to be a full tile path to the outside for
tiles to count as outside the loop - squeezing between pipes is also
allowed! Here, I is still within the loop and O is still outside the loop:

..........
.S------7.
.|F----7|.
.||OOOO||.
.||OOOO||.
.|L-7F-J|.
.|II||II|.
.L--JL--J.
..........

In both of the above examples, 4 tiles are enclosed by the loop.

Here's a larger example:

.F----7F7F7F7F-7....
.|F--7||||||||FJ....
.||.FJ||||||||L7....
FJL7L7LJLJ||LJ.L-7..
L--J.L7...LJS7F-7L7.
....F-J..F7FJ|L7L7L7
....L7.F7||L7|.L7L7|
.....|FJLJ|FJ|F7|.LJ
....FJL-7.||.||||...
....L---J.LJ.LJLJ...

The above sketch has many random bits of ground, some of which are in the
loop (I) and some of which are outside it (O):

OF----7F7F7F7F-7OOOO
O|F--7||||||||FJOOOO
O||OFJ||||||||L7OOOO
FJL7L7LJLJ||LJIL-7OO
L--JOL7IIILJS7F-7L7O
OOOOF-JIIF7FJ|L7L7L7
OOOOL7IF7||L7|IL7L7|
OOOOO|FJLJ|FJ|F7|OLJ
OOOOFJL-7O||O||||OOO
OOOOL---JOLJOLJLJOOO

In this larger example, 8 tiles are enclosed by the loop.

Any tile that isn't part of the main loop can count as being enclosed by
the loop. Here's another example with many bits of junk pipe lying around
that aren't connected to the main loop at all:

FF7FSF7F7F7F7F7F---7
L|LJ||||||||||||F--J
FL-7LJLJ||||||LJL-77
F--JF--7||LJLJ7F7FJ-
L---JF-JLJ.||-FJLJJ7
|F|F-JF---7F7-L7L|7|
|FFJF7L7F-JF7|JL---7
7-L-JL7||F7|L7F-7F7|
L.L7LFJ|||||FJL7||LJ
L7JLJL-JLJLJL--JLJ.L

Here are just the tiles that are enclosed by the loop marked with I:

FF7FSF7F7F7F7F7F---7
L|LJ||||||||||||F--J
FL-7LJLJ||||||LJL-77
F--JF--7||LJLJIF7FJ-
L---JF-JLJIIIIFJLJJ7
|F|F-JF---7IIIL7L|7|
|FFJF7L7F-JF7IIL---7
7-L-JL7||F7|L7F-7F7|
L.L7LFJ|||||FJL7||LJ
L7JLJL-JLJLJL--JLJ.L

In this last example, 10 tiles are enclosed by the loop.

Figure out whether you have time to search for the nest by calculating the
area within the loop. How many tiles are enclosed by the loop?

***/

// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <algorithm>
#include <functional>
#include <numeric>
#include <bitset>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>

#include <cassert>

// Precessing graphics library.
#include "p8g.hpp"

#include "aoc.h"


// Coordinate location.
struct coord {
	int x;
	int y;

	friend inline bool operator==(const coord& lhs, const coord& rhs) { return ((lhs.x == rhs.x) && (lhs.y == rhs.y)); }
};

// Four cardinal directions.
enum dir {
	North, East, South, West
};

// Return the opposite cardinal direction.
dir opposite(dir d) {
	if (North == d) return South;
	if (South == d) return North;
	if (West == d) return East;
	if (East == d) return West;
	throw "Unthinkable Error";
}

// Each map tile is stored in this data structure.
struct maptile {
	enum {
		G,		// ground, no pipe
		N_S, E_W, N_E, N_W, S_W, S_E,	// pipes
		START	// start location, unknown pipe type
	} tile;
	bool north = false, south = false, east = false, west = false;	// true, if pipe extends to this direction
	bool is_start = false;		// true, if tile is start location
	bool is_end = false;		// true, if tile is end location
	bool part_of_pipe = false;	// true, if tile is part of continuous pipeline
	bool enclosed = false;		// true, if tile is enclosed by the pipeline

	maptile() : tile(G) {};	// empty tile ctor
	maptile(char c) {	// construct tile from the puzzle input character
		switch (c) {
			case '|': tile = N_S; north = south = true; break;
			case '-': tile = E_W; east = west = true; break;
			case 'L': tile = N_E; north = east = true; break;
			case 'J': tile = N_W; north = west = true; break;
			case '7': tile = S_W; south = west = true; break;
			case 'F': tile = S_E; south = east = true; break;
			case 'S': tile = START; is_start = true; break;
			default: tile = G; break;
		}
	}

	// Returns a direction this tile extends to.
	dir pickany() const {
		if (east) return dir::East;
		if (south) return dir::South;
		if (west) return dir::West;
		if (north) return dir::North;
		throw "Unthinkable Error";
	}

	// Returns a direction this tile extends to, except the direction passed as argument.
	dir picksecond(dir d) const {
		if (west && (dir::West != d)) return dir::West;
		if (north && (dir::North != d)) return dir::North;
		if (east && (dir::East != d)) return dir::East;
		if (south && (dir::South != d)) return dir::South;
		throw "Unthinkable Error";
	}

	// Return direction which way to go out from this pipe
	// when coming in from direction d.
	// Eg. S_E pipe, in direction is north, out direction is east.
	dir inout(dir in_d) const {
		switch (in_d) {
			case dir::North: if (south) return (west  ? dir::West  : ((north) ? dir::North : dir::East));
			case dir::East:  if (west)  return (south ? dir::South : ((north) ? dir::North : dir::East));
			case dir::South: if (north) return (west  ? dir::West  : ((south) ? dir::South : dir::East));
			case dir::West:  if (east)  return (south ? dir::South : ((north) ? dir::North : dir::West));
			default: break;
		}
		throw "Unthinkable Error";
	}

	// Visualise the map tile.
	const std::string out() const {
		std::string s;
		if (! unit_testing) {	// use terminal colours
			if (part_of_pipe) s += "\e[32m";
			if (is_start) s += "\e[33m";
			if (is_end) s += "\e[31m";
		}
		switch (tile) {
			case G: if (enclosed) s += "*"; else s += " "; break;
			case N_S: s += "║"; break;
			case E_W: s += "═"; break;
			case N_E: s += "╚"; break;
			case N_W: s += "╝"; break;
			case S_W: s += "╗"; break;
			case S_E: s += "╔"; break;
			case START: s += "♦"; break;
			default: s += " "; break;
		}
		if (! unit_testing) {
			if (is_end || is_start || part_of_pipe) s += "\e[0m";
		}
		return s;
	}

	// Return a "polygon" structure for Precessing visualisation of this tile.
	std::vector<coord> draw() const {
		std::vector<coord> v;
		coord properties = {
			(part_of_pipe) ? 1 : 0,
			(is_start) ? 1 : ((is_end) ? -1 : 0)
		};
		v.push_back(properties);
		v.push_back({ 1, 1 });
		if (north) v.push_back({ 1, 0 });
		if (east)  v.push_back({ 2, 1 });
		if (south) v.push_back({ 1, 2 });
		if (west)  v.push_back({ 0, 1 });
		return v;
	}
};


// Modify input x and y based on the cardinal direction.
void move(dir d, coord& loc, const int n = 1) {
	switch (d) {
		case dir::East:  loc.x += n; break;
		case dir::West:  loc.x -= n; break;
		case dir::South: loc.y += n; break;
		case dir::North: loc.y -= n; break;
	}
	return;
}


// Helper function to calculate x,y position in the array.
inline size_t pipeat(coord loc, int max_x) { return loc.y * max_x + loc.x; }
inline size_t pipeat(int x, int y, int max_x) { return y * max_x + x; }


// Maximum size of the map.
constexpr int	max_width = 140;
constexpr int	max_height = 140;


// Parameters for the solution parts.
struct param_s {
	int width = 0;		// Actual width of the puzzle input map.
	int height = 0;		// Actual height of the puzzle input map.
	int scale = 2;		// Precessing plot scale, does not affect solution result.
	coord start { -1, -1 };		// Puzzle starting location.
	coord end { -1, -1 };		// Puzzle end location.
	coord bottom { -1, -1 };	// Most bottom location in pipeline.
	
	std::bitset<max_width * 3 * max_height * 3>	bitmap;
	std::bitset<max_width * max_height> 		pipeline;
};
param_s* params = nullptr;		// Allocated in day10()
maptile* tilemap = nullptr;		// Allocated in day10()


// Callback methods for Precessing.
void p8g::keyPressed() {}
void p8g::keyReleased() {}
void p8g::mouseMoved() {}
void p8g::mousePressed() {}
void p8g::mouseReleased() {}
void p8g::mouseWheel(float delta) {}

// Visualise the pipeline using Precessing.
void p8g::draw() {
	using namespace p8g;
	background(18, 0, 31);
	strokeWeight(params->scale);

	stroke(255, 0, 0);	// Red box around.
	fill(18, 0, 31);
	rect(0, 0, width, height);

	for (int y = 0; y < params->height; ++y) {
		int offset = y * params->width;
		for (int x = 0; x < params->width; ++x) {
			// Choose drawing colour.
			if (params->pipeline[offset + x]) {
				if ((y == params->start.y) && (x == params->start.x)) {		// Pipeline start location
					stroke(227, 121, 51);
				} else if ((y == params->end.y) && (x == params->end.x)) {	// Pipeline end location
					stroke(240, 33, 33);
				} else if ((y == params->bottom.y) && (x == params->bottom.x)) {	// Most bottom location
					stroke(26, 121, 241);
				} else {	// Normal pipeline
					stroke(78, 154, 36);
				}
			} else {
				stroke(220, 220, 220);
			}
			// Draw subpixels.
			for (int suby = y * 3; suby < y * 3 + 3; ++suby) {
				int suboffset = suby * params->width * 3;
				for (int subx = x * 3; subx < x * 3 + 3; ++subx) {
					auto pix = params->bitmap[suboffset + subx];
					if (pix) point(subx * params->scale + 1, suby * params->scale + 1);
				}
			}
		}
	}
}


// Recursive flood-fill paint function.
// Uses the 3× scaled 'bitmap' for painting and whenever a pixel is drawn, the corresponding
// tile in 'tilemap' is marked as being 'enclosed'.
// Does not check x or y boundaries as the pipeline will be bound to those limits anyway.
void paint(coord p) {
	if (params->bitmap[p.y * params->width * 3 + p.x]) return;	// Boundary hit.

	params->bitmap[p.y * params->width * 3 + p.x] = true;
	if (!tilemap[pipeat(p.x/3, p.y/3, params->width)].part_of_pipe) {
		tilemap[pipeat(p.x/3, p.y/3, params->width)].enclosed = true;
	}

	paint({ p.x - 1, p.y     });
	paint({ p.x,     p.y - 1 });
	paint({ p.x + 1, p.y     });
	paint({ p.x,     p.y + 1 });
}


long day10(int puzzle_part, std::istream& puzzle_input)
{
	long total = 0;	// Solution result is stored here.

	// Allocate global data.
	params = new param_s;
	tilemap = new maptile[max_width * max_height];

	// Read puzzle input.
	{
		maptile* pmp = tilemap;
		for (std::string line; std::getline(puzzle_input, line); ) {
			if (0 == params->width) params->width = line.length();
			for (auto c = line.begin(); c != line.end(); ++c) {
				*pmp++ = *c;
				if ('S' == *c) { params->start.x = std::distance(line.begin(), c); params->start.y = params->height; }
			}
			params->height += 1;
		}
	}

	if (true) {	// Part 1 and 2: Find the distance.
		// Determine the shape of the start tile and then replace the tile with proper pipe shape.
		int x = params->start.x;
		int y = params->start.y;
		maptile start_tile;
		if (tilemap[pipeat(x, y-1, params->width)].south && tilemap[pipeat(x, y+1, params->width)].north) start_tile = '|';
		if (tilemap[pipeat(x-1, y, params->width)].east  && tilemap[pipeat(x, y-1, params->width)].south) start_tile = 'J';
		if (tilemap[pipeat(x-1, y, params->width)].east  && tilemap[pipeat(x, y+1, params->width)].north) start_tile = '7';
		if (tilemap[pipeat(x+1, y, params->width)].west  && tilemap[pipeat(x, y+1, params->width)].north) start_tile = 'F';
		if (tilemap[pipeat(x+1, y, params->width)].west  && tilemap[pipeat(x, y-1, params->width)].south) start_tile = 'L';
		if (tilemap[pipeat(x-1, y, params->width)].east  && tilemap[pipeat(x+1, y, params->width)].west)  start_tile = '-';
		start_tile.part_of_pipe = true;
		start_tile.is_start = true;
		tilemap[pipeat(params->start, params->width)] = start_tile;

		if (debug) std::cout << "Start at: " << params->start.x << "," << params->start.y << ":" << tilemap[pipeat(params->start, params->width)].out() << std::endl;

		// Select directions to advance from the start tile.
		dir direction1, direction2;
		direction1 = start_tile.pickany();
		direction2 = start_tile.picksecond(direction1);

		// Move along the pipeline in two directions and stop when they end up in same location.
		coord location1 = params->start;
		coord location2 = params->start;
		bool done = false;
		while (!done) {
			move(direction1, location1);
			maptile& tile1 = tilemap[pipeat(location1, params->width)];
			tile1.part_of_pipe = true;
			direction1 = tile1.inout(direction1);

			move(direction2, location2);
			maptile& tile2 = tilemap[pipeat(location2, params->width)];
			tile2.part_of_pipe = true;
			direction2 = tile2.inout(direction2);

			// Locate the bottom-most pipe section.
			if (location2.y > params->bottom.y) { params->bottom = location2; }
			if (location1.y > params->bottom.y) { params->bottom = location1; }

			// Loop ends when both locations are the same.
			if (location1 == location2) {
				tile2.is_end = true;
				done = true;
			}

			total += 1;	// Count each step, it's the solution for part 1.
		}

		// Make neat bitmap.  Each tile is drawn as 3×3 pixel element.
		for (int y = 0; y < params->height; ++y) {
			for (int x = 0; x < params->width; ++x) {
				// draw() returns a vector of x,y values.
				auto v = tilemap[pipeat(x, y, params->width)].draw();
				// First item is the pixel/line properties.
				auto v_it = v.begin();
				if (v_it->x != 0) {
					// Map tile is part of pipeline, so set that bit in the helper data.
					params->pipeline[pipeat(x, y, params->width)] = true;
				}
				if (v_it->y > 0) {
					// Map tile is the start location, store it.
					params->start.x = x;
					params->start.y = y;
				} else if (v_it->y < 0) {
					// Map tile is the end location, store it.
					params->end.x = x;
					params->end.y = y;
				}
				
				// Draw pixels into the 3× bitmap, using the coordinates from the vector.
				int fx = x * 3;
				int fy = y * 3;
				int fw = params->width * 3;
				for (v_it++; v_it != v.end(); ++v_it) {
					params->bitmap[pipeat(fx + v_it->x, fy + v_it->y, fw)] = true;
				}
			}
		}
	}

	if (2 == puzzle_part) {
		// Paint the inner area to find how many tiles are enclosed.
		// Use the bottom-most tile as starting location.
		// It can only be NW, NE, or EW tile, so y location is at the top and
		// x location is easy to pick (left or right).
		int xadj = 0;	// NW
		if (tilemap[pipeat(params->bottom.x, params->bottom.y, params->width)].east) xadj = 2;	// NE or EW
		paint({ params->bottom.x * 3 + xadj, params->bottom.y * 3 });

		// Count all map tiles that were marked as enclosed, that is the solution to part 2.
		total = 0;
		for (int i = 0; i < params->height * params->width; ++i) {
			if (tilemap[i].enclosed) total += 1;
		}
	}
		
	if (debug) {
		// Output the pipe map to console.
		for (int y = 0; y < params->height; ++y) {
			for (int x = 0; x < params->width; ++x) {
				std::cout << tilemap[y * params->width + x].out();
			}
			std::cout << std::endl;
		}
		// Output the pipe map to Precessing window if X11 is active.
		if (std::getenv("DISPLAY") != nullptr) {
			p8g::run(max_width * 3 * params->scale + 2, max_height * 3 * params->scale + 2, "Day 10");
		} else {
			for (int y = 0; y < params->height; ++y) {
				int offset = y * params->width;
				for (int suby = y * 3; suby < y * 3 + 3; ++suby) {
					int suboffset = suby * params->width * 3;
					for (int x = 0; x < params->width; ++x) {
						char c = ' ';
						std::string s;
						if (tilemap[offset + x].part_of_pipe) {
							if ((y == params->start.y) && (x == params->start.x)) {
								if (!unit_testing) s += "\e[33m";
								c = '>';
							} else if ((y == params->end.y) && (x == params->end.x)) {
								if (!unit_testing) s += "\e[31m";
								c = '<';
							} else if ((y == params->bottom.y) && (x == params->bottom.x)) {
								if (!unit_testing) s += "\e[34m";
								c = '^';
							} else {
								if (!unit_testing) s += "\e[32m";
								c = '.';
							}
						} else {
							if (!unit_testing) s += "\e[37m";
							if (tilemap[offset + x].enclosed) {
								c = '#';
							} else {
								c = '_';
							}
						}
						for (int subx = x * 3; subx < x * 3 + 3; ++subx) {
							auto pix = params->bitmap[suboffset + subx];
							if (pix) s += c; else s+= " ";
						}
						std::cout << s;
					}
					std::cout << std::endl;
				}
			}
		}
	}

	delete[] tilemap;
	delete params;

	if (debug) std::cout << "Total: " << total << "\n" << std::endl;

	return total;
}


/*

*/
