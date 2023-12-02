/***
Advent of Code 2023 - Day 2: Cube Conundrum

Part 1

You're launched high into the atmosphere! The apex of your trajectory just
barely reaches the surface of a large island floating in the sky. You
gently land in a fluffy pile of leaves. It's quite cold, but you don't see
much snow. An Elf runs over to greet you.

The Elf explains that you've arrived at Snow Island and apologizes for the
lack of snow. He'll be happy to explain the situation, but it's a bit of a
walk, so you have some time. They don't get many visitors up here; would
you like to play a game in the meantime?

As you walk, the Elf shows you a small bag and some cubes which are either
red, green, or blue. Each time you play this game, he will hide a secret
number of cubes of each color in the bag, and your goal is to figure out
information about the number of cubes.

To get information, once a bag has been loaded with cubes, the Elf will
reach into the bag, grab a handful of random cubes, show them to you, and
then put them back in the bag. He'll do this a few times per game.

You play several games and record the information from each game (your
puzzle input). Each game is listed with its ID number (like the 11 in
Game 11: ...) followed by a semicolon-separated list of subsets of cubes
that were revealed from the bag (like 3 red, 5 green, 4 blue).

For example, the record of a few games might look like this:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

In game 1, three sets of cubes are revealed from the bag (and then put back
again). The first set is 3 blue cubes and 4 red cubes; the second set is 1
red cube, 2 green cubes, and 6 blue cubes; the third set is only 2 green
cubes.

The Elf would first like to know which games would have been possible if
the bag contained only 12 red cubes, 13 green cubes, and 14 blue cubes?

In the example above, games 1, 2, and 5 would have been possible if the
bag had been loaded with that configuration. However, game 3 would have
been impossible because at one point the Elf showed you 20 red cubes at
once; similarly, game 4 would also have been impossible because the Elf
showed you 15 blue cubes at once. If you add up the IDs of the games
that would have been possible, you get 8.

Determine which games would have been possible if the bag had been loaded
with only 12 red cubes, 13 green cubes, and 14 blue cubes. What is the
sum of the IDs of those games?

Part 2

The Elf says they've stopped producing snow because they aren't getting any
water! He isn't sure why the water stopped; however, he can show you how to
get to the water source to check it out for yourself. It's just up ahead!

As you continue your walk, the Elf poses a second question: in each game
you played, what is the fewest number of cubes of each color that could
have been in the bag to make the game possible?

Again consider the example games from earlier:

Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
Game 2: 1 blue, 2 green; 3 green, 4 blue, 1 red; 1 green, 1 blue
Game 3: 8 green, 6 blue, 20 red; 5 blue, 4 red, 13 green; 5 green, 1 red
Game 4: 1 green, 3 red, 6 blue; 3 green, 6 red; 3 green, 15 blue, 14 red
Game 5: 6 red, 1 blue, 3 green; 2 blue, 1 red, 2 green

 - In game 1, the game could have been played with as few as 4 red,
   2 green, and 6 blue cubes. If any color had even one fewer cube,
   the game would have been impossible.
 - Game 2 could have been played with a minimum of 1 red, 3 green, and
   4 blue cubes.
 - Game 3 must have been played with at least 20 red, 13 green, and
   6 blue cubes.
 - Game 4 required at least 14 red, 3 green, and 15 blue cubes.
 - Game 5 needed no fewer than 6 red, 3 green, and 2 blue cubes in the
   bag.

The power of a set of cubes is equal to the numbers of red, green, and blue
cubes multiplied together. The power of the minimum set of cubes in game 1
is 48. In games 2-5 it was 12, 1560, 630, and 36, respectively. Adding up
these five powers produces the sum 2286.

For each game, find the minimum set of cubes that must have been present.
What is the sum of the power of these sets?

***/

// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>

#include "aoc.h"


// Different color cubes are stored in this data structure.
struct cubes {
	int red, green, blue;

	void set_value(std::string name, int value) {
		if (name == "red") red = value;
		else if (name == "green") green = value;
		else if (name == "blue") blue = value;
	}

	bool within_limits() {	// Limits of part 1 puzzle: 12 red, 13 green, 14 blue.
		if (red > 12) return false;
		if (green > 13) return false;
		if (blue > 14) return false;
		return true;
	}

	void set_larger(const cubes& c) {
		if (c.red > red) red = c.red;
		if (c.green > green) green = c.green;
		if (c.blue > blue) blue = c.blue;
	}
};

// Given a string like "3 blue", sets the respective value of the cubes data structure.
void cubeset(cubes& value, std::string s) {
	auto pos = s.find(' ');
	value.set_value(s.substr(pos+1), std::stoi(s.substr(0, pos)));
}

// Given a string like "8 green, 6 blue, 20 red", sets the values in cubes data structure.
void fetch(cubes& value, std::string s)
{
	s += ",";	// Append comma to string for simpler logic.

	size_t pos = 0;
	while (pos < s.length()) {
		// Skip possible leading spaces.
		while (' ' == s.at(pos)) ++pos;
		// Look for next comma in string and send a substring up to that comma to cubeset().
		auto newpos = s.find(',', pos);
		cubeset(value, s.substr(pos, newpos - pos));
		// Set position after comma.
		pos = newpos + 1;
	}
}


int day02(int part, std::istream& puzzle_input)
{
	unsigned long	sum = 0;	// Solution stored here.

	// Parse each line of puzzle input.
	int gameid = 1;	// Game ID is linear so no need to parse the input.
	for (std::string line; std::getline(puzzle_input, line); ++gameid) {
		line += ";";	// Append semicolon to line end for simpler logic.

		bool game_ok = true;		// Game ok for part 1.
		cubes fewest { 0, 0, 0 };	// Fewest cubes for part 2.

		auto pos = line.find(':') + 2;
		while (pos < line.length()) {
			cubes value { 0, 0, 0 };	// Set of cubes fetched from the bag.

			// Look for next semicolon and send substring up to that semicolon to fetch().
			auto newpos = line.find(';', pos);
			fetch(value, line.substr(pos, newpos - pos));
			// Set position after semicolon.
			pos = newpos + 1;

			if (1 == part) {
				// Part 1: When number of cubes is not within set limits,
				// set flag and break from loop. Game ID will not be added.
				if (false == (game_ok = value.within_limits())) break;
			} else {
				// Part 2: Update the fewest cubes.
				fewest.set_larger(value);
			}
		}

		if (1 == part) {
			if (game_ok) sum += gameid;
		} else {
			sum += fewest.red * fewest.green * fewest.blue;
		}
	}

	return sum;
}

/*
More of a string parsing problem than anything else. Was not particularly
difficult but annoying and time-consuming. Other languages might have been
better suited for this, but then again, might have not.

String splitting could have been implemented with stringstream and getline()
but I doubt it would have produced any simpler code.
*/
