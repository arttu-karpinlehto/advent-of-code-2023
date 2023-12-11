/***
Advent of Code 2023 - Day 8: Haunted Wasteland

Part 1

You're still riding a camel across Desert Island when you spot a sandstorm
quickly approaching. When you turn to warn the Elf, she disappears before
your eyes! To be fair, she had just finished warning you about ghosts a
few minutes ago.

One of the camel's pouches is labeled "maps" - sure enough, it's full of
documents (your puzzle input) about how to navigate the desert. At least,
you're pretty sure that's what they are; one of the documents contains a
list of left/right instructions, and the rest of the documents seem to
describe some kind of network of labeled nodes.

It seems like you're meant to use the left/right instructions to navigate
the network. Perhaps if you have the camel follow the same instructions,
you can escape the haunted wasteland!

After examining the maps for a bit, two nodes stick out: AAA and ZZZ. You
feel like AAA is where you are now, and you have to follow the left/right
instructions until you reach ZZZ.

This format defines each node of the network individually. For example:

RL

AAA = (BBB, CCC)
BBB = (DDD, EEE)
CCC = (ZZZ, GGG)
DDD = (DDD, DDD)
EEE = (EEE, EEE)
GGG = (GGG, GGG)
ZZZ = (ZZZ, ZZZ)

Starting with AAA, you need to look up the next element based on the next
left/right instruction in your input. In this example, start with AAA and
go right (R) by choosing the right element of AAA, CCC. Then, L means to
choose the left element of CCC, ZZZ. By following the left/right
instructions, you reach ZZZ in 2 steps.

Of course, you might not find ZZZ right away. If you run out of left/right
instructions, repeat the whole sequence of instructions as necessary: RL
really means RLRLRLRLRLRLRLRL... and so on. For example, here is a
situation that takes 6 steps to reach ZZZ:

LLR

AAA = (BBB, BBB)
BBB = (AAA, ZZZ)
ZZZ = (ZZZ, ZZZ)

Starting at AAA, follow the left/right instructions. How many steps are
required to reach ZZZ?

Part 2

The sandstorm is upon you and you aren't any closer to escaping the
wasteland. You had the camel follow the instructions, but you've barely
left your starting position. It's going to take significantly more steps
to escape!

What if the map isn't for people - what if the map is for ghosts? Are
ghosts even bound by the laws of spacetime? Only one way to find out.

After examining the maps a bit longer, your attention is drawn to a
curious fact: the number of nodes with names ending in A is equal to the
number ending in Z! If you were a ghost, you'd probably just start at
every node that ends with A and follow all of the paths at the same time
until they all simultaneously end up at nodes that end with Z.

For example:

LR

11A = (11B, XXX)
11B = (XXX, 11Z)
11Z = (11B, XXX)
22A = (22B, XXX)
22B = (22C, 22C)
22C = (22Z, 22Z)
22Z = (22B, 22B)
XXX = (XXX, XXX)

Here, there are two starting nodes, 11A and 22A (because they both end
with A). As you follow each left/right instruction, use that instruction
to simultaneously navigate away from both nodes you're currently on.
Repeat this process until all of the nodes you're currently on end with Z.
(If only some of the nodes you're on end with Z, they act like any other
node and you continue as normal.) In this example, you would proceed as
follows:

 - Step 0: You are at 11A and 22A.
 - Step 1: You choose all of the left paths, leading you to 11B and 22B.
 - Step 2: You choose all of the right paths, leading you to 11Z and 22C.
 - Step 3: You choose all of the left paths, leading you to 11B and 22Z.
 - Step 4: You choose all of the right paths, leading you to 11Z and 22B.
 - Step 5: You choose all of the left paths, leading you to 11B and 22C.
 - Step 6: You choose all of the right paths, leading you to 11Z and 22Z.

So, in this example, you end up entirely on nodes that end in Z after 6
steps.

Simultaneously start on every node that ends with A. How many steps does
it take before you're only on nodes that end with Z?

***/

// Advent of Code 2023 Solutions by Arttu Kärpinlehto

#include <algorithm>
#include <functional>
#include <numeric>
#include <array>
#include <set>
#include <deque>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <cstring>
#include <cctype>
#include <cmath>

#include <cassert>

#include "aoc.h"


bool ghost_paths = false;


struct node {
	long n;

	node() : n(0) {}
	node(const std::string s) {
		n = (s[0]) << 16 | (s[1]) << 8 | (s[2]);
	}

	std::string name() const {
		std::string s;
		s += (n >> 16);
		s += ((n >> 8) & 0xFF);
		s += (n & 0xFF);
		return s;
	}

	bool ends_with(char c) const {
		return (n & 0xFF) == c;
	}

	friend inline bool operator==(const node& lhs, const node& rhs) { return lhs.n == rhs.n; }
	friend inline bool operator<(const node& lhs, const node& rhs) { return lhs.n < rhs.n; }
};

struct instruction {
	node left, right;
	node tgt;
	instruction* ileft;
	instruction* iright;
	bool is_zzz;
	bool ends_in_z;

	instruction(const std::string s) {
		tgt = s.substr(0, 3);
		left = s.substr(7, 3);
		right = s.substr(12, 3);
		is_zzz =  (s.substr(0, 3) == "ZZZ") ? true : false;
		ends_in_z = (s.substr(2, 1) == "Z") ? true : false;
	}
};


long day08(int puzzle_part, std::istream& puzzle_input)
{
	long total = 0;	// Solution result is stored here.

	ghost_paths = (2 == puzzle_part) ? true : false;

	std::map<long, instruction>	instructions;

	// Read puzzle input
	std::string route;
	std::getline(puzzle_input, route);
	if (debug) std::cout << "Route: " << route << std::endl;

	for (std::string line; std::getline(puzzle_input, line); ) {
		if (line.length() < 1) continue;
		instruction inst(line);
		instructions.insert({inst.tgt.n, inst});
	}

	if (debug) {
		std::cout << "Instructions count: " << instructions.size() << std::endl;
		for (const auto& i : instructions) {
			std::cout << "Idx: " << i.first
				<< "\tTgt: " << i.second.tgt.name() << " (" << i.second.tgt.n << ")"
				<< "\tLeft: " << i.second.left.name() << " (" << i.second.left.n << ")"
				<< "\tRight: " << i.second.right.name() << " (" << i.second.right.n << ")"
				<< std::endl;
		}
	}

	for (auto i_it = instructions.begin(); i_it != instructions.end(); ++i_it) {
		i_it->second.ileft = &instructions.at(i_it->second.left.n);
		i_it->second.iright = &instructions.at(i_it->second.right.n);
	}

	if (1 == puzzle_part) {
		auto r = route.begin();

		instruction* curr = &instructions.at(node("AAA").n);
		while (!curr->is_zzz) {
			if (debug) std::cout << "Node: " << curr->tgt.name()
				<< (('R' == *r) ? std::string(" R: " + curr->iright->tgt.name()) : std::string(" L: " + curr->ileft->tgt.name())) << std::endl;
			curr = ('R' == *r) ? curr->iright : curr->ileft;
			if (++r == route.end()) {
				r = route.begin();
			}
			total += 1;
		}
	} else {
		auto r = route.begin();
		std::vector<node> starts;

		for (auto i : instructions) {
			if (i.second.tgt.ends_with('A')) {
				if (debug) std::cout << "Starting point: " << i.second.tgt.name() << std::endl;
				starts.push_back(i.second.tgt);
			}
		}

		size_t qnum = starts.size();
		std::vector<long> totals;
		for (auto sp : starts) {
			total = 0;
			if (debug) std::cout << "Routing queue " << qnum << std::endl;
			instruction* curr = &instructions.at(sp.n);
			while (!curr->ends_in_z) {
				if (debug) std::cout << "Node: " << curr->tgt.name()
					<< (('R' == *r) ? std::string(" R: " + curr->iright->tgt.name()) : std::string(" L: " + curr->ileft->tgt.name())) << std::endl;
				curr = ('R' == *r) ? curr->iright : curr->ileft;
				if (++r == route.end()) {
					r = route.begin();
				}
				total += 1;
			}
			totals.push_back(total);
		}

		for (auto t : totals) {
			if (debug) std::cout << "Total: " << t << std::endl;
			total = std::lcm(total, t);
		}
	}

	if (debug) std::cout << "End found after step: " << total << std::endl;

	return total;
}


/*

*/
