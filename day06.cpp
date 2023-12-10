/***
Advent of Code 2023 - Day 6: Wait For It

Part 1

The ferry quickly brings you across Island Island. After asking around,
you discover that there is indeed normally a large pile of sand somewhere
near here, but you don't see anything besides lots of water and the small
island where the ferry has docked.

As you try to figure out what to do next, you notice a poster on a wall
near the ferry dock. "Boat races! Open to the public! Grand prize is an
all-expenses-paid trip to Desert Island!" That must be where the sand
comes from! Best of all, the boat races are starting in just a few
minutes.

You manage to sign up as a competitor in the boat races just in time. The
organizer explains that it's not really a traditional race - instead, you
will get a fixed amount of time during which your boat has to travel as
far as it can, and you win if your boat goes the farthest.

As part of signing up, you get a sheet of paper (your puzzle input) that
lists the time allowed for each race and also the best distance ever
recorded in that race. To guarantee you win the grand prize, you need to
make sure you go farther in each race than the current record holder.

The organizer brings you over to the area where the boat races are held.
The boats are much smaller than you expected - they're actually toy boats,
each with a big button on top. Holding down the button charges the boat,
and releasing the button allows the boat to move. Boats move faster if
their button was held longer, but time spent holding the button counts
against the total race time. You can only hold the button at the start of
the race, and boats don't move until the button is released.

For example:

Time:      7  15   30
Distance:  9  40  200

This document describes three races:

 - The first race lasts 7 milliseconds. The record distance in this race
   is 9 millimeters.
 - The second race lasts 15 milliseconds. The record distance in this race
   is 40 millimeters.
 - The third race lasts 30 milliseconds. The record distance in this race
   is 200 millimeters.

Your toy boat has a starting speed of zero millimeters per millisecond.
For each whole millisecond you spend at the beginning of the race holding
down the button, the boat's speed increases by one millimeter per
millisecond.

So, because the first race lasts 7 milliseconds, you only have a few
options:

 - Don't hold the button at all (that is, hold it for 0 milliseconds) at
   the start of the race. The boat won't move; it will have traveled 0
   millimeters by the end of the race.
 - Hold the button for 1 millisecond at the start of the race. Then, the
   boat will travel at a speed of 1 millimeter per millisecond for 6
   milliseconds, reaching a total distance traveled of 6 millimeters.
 - Hold the button for 2 milliseconds, giving the boat a speed of 2
   millimeters per millisecond. It will then get 5 milliseconds to move,
   reaching a total distance of 10 millimeters.
 - Hold the button for 3 milliseconds. After its remaining 4 milliseconds
   of travel time, the boat will have gone 12 millimeters.
 - Hold the button for 4 milliseconds. After its remaining 3 milliseconds
   of travel time, the boat will have gone 12 millimeters.
 - Hold the button for 5 milliseconds, causing the boat to travel a total
   of 10 millimeters.
 - Hold the button for 6 milliseconds, causing the boat to travel a total
   of 6 millimeters.
 - Hold the button for 7 milliseconds. That's the entire duration of the
   race. You never let go of the button. The boat can't move until you let
   go of the button. Please make sure you let go of the button so the boat
   gets to move. 0 millimeters.

Since the current record for this race is 9 millimeters, there are
actually 4 different ways you could win: you could hold the button for 2,
3, 4, or 5 milliseconds at the start of the race.

In the second race, you could hold the button for at least 4 milliseconds
and at most 11 milliseconds and beat the record, a total of 8 different
ways to win.

In the third race, you could hold the button for at least 11 milliseconds
and no more than 19 milliseconds and still beat the record, a total of 9
ways you could win.

To see how much margin of error you have, determine the number of ways you
can beat the record in each race; in this example, if you multiply these
values together, you get 288 (4 * 8 * 9).

Determine the number of ways you could beat the record in each race. What
do you get if you multiply these numbers together?

Part 2

As the race is about to start, you realize the piece of paper with race
times and record distances you got earlier actually just has very bad
kerning. There's really only one race - ignore the spaces between the
numbers on each line.

So, the example from before:

Time:      7  15   30
Distance:  9  40  200

...now instead means this:

Time:      71530
Distance:  940200

Now, you have to figure out how many ways there are to win this single
race. In this example, the race lasts for 71530 milliseconds and the
record distance you need to beat is 940200 millimeters. You could hold the
button anywhere from 14 to 71516 milliseconds and beat the record, a total
of 71503 ways!

How many ways can you beat the record in this one much longer race?

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


struct race {
	long time;
	long distance;

	long travel(long press) const {
		if (press < time) {
			return (time - press) * press;
		}
		return 0;
	}

	friend inline bool operator<(const race lhs, const race rhs) { return lhs.time < rhs.time; }
};


long day06(int puzzle_part, std::istream& puzzle_input)
{
	long margin = 1;	// Solution is stored here.

	// Read puzzle input into two strings.
	std::string times;
	std::string distances;
	std::getline(puzzle_input, times);
	std::getline(puzzle_input, distances);
	if (debug) {
		std::cout << "Line 1: " << times << std::endl;
		std::cout << "Line 2: " << distances << std::endl;
	}
	
	// Parse race data.
	std::vector<race> races;
	size_t t_pos = times.find(':') + 1;
	size_t d_pos = distances.find(':') + 1;

	if (1 == puzzle_part) {
		bool active = true;
		while (active) {
			t_pos = times.find_first_not_of(' ', t_pos);
			d_pos = distances.find_first_not_of(' ', d_pos);
			auto t_len = times.find_first_of(' ', t_pos) - t_pos;
			auto d_len = distances.find_first_of(' ', d_pos) - d_pos;
			
			if (debug) std::cout << "T " << times.substr(t_pos, t_len) << " D " << distances.substr(d_pos, d_len) << std::endl;

			races.push_back({
				std::stol(times.substr(t_pos, t_len)),
				std::stol(distances.substr(d_pos, d_len))
			});
			t_pos += t_len;
			d_pos += d_len;
			if ((t_pos >= times.length()) || (d_pos >= distances.length())) active = false;
		}
	} else {
		std::string timestr;
		while (t_pos < times.length()) {
			if (isdigit(times.at(t_pos))) {
				timestr += times.at(t_pos);
			}
			t_pos += 1;
		}
		std::string distancestr;
		while (d_pos < distances.length()) {
			if (isdigit(distances.at(d_pos))) {
				distancestr += distances.at(d_pos);
			}
			d_pos += 1;
		}

		races.push_back({std::stol(timestr), std::stol(distancestr)});
	}

	if (debug) std::cout << "Races: " << races.size() << std::endl;
	for (const auto& race : races) {
		long beats = 0;

		if (debug) std::cout << "Time: " << race.time << " Distance: " << race.distance << std::endl;
		for (auto i = 1; i < race.time; ++i) {
			auto t = race.travel(i);
			//if (debug) std::cout << "Press: " << i << " Travel: " << t << std::endl;
			if (t > race.distance) beats += 1;
		}

		margin *= beats;
	}

	return margin;
}

/*
Urgh, this was a parsing problem again. Not fun at all.

In fact, I almost started to write a string parsing library, but then
not really.
*/
