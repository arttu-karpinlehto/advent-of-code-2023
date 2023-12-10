/***
Advent of Code 2023 - Day 7: Camel Cards

Part 1

Your all-expenses-paid trip turns out to be a one-way, five-minute ride in
an airship. (At least it's a cool airship!) It drops you off at the edge
of a vast desert and descends back to Island Island.

"Did you bring the parts?"

You turn around to see an Elf completely covered in white clothing,
wearing goggles, and riding a large camel.

"Did you bring the parts?" she asks again, louder this time. You aren't
sure what parts she's looking for; you're here to figure out why the sand
stopped.

"The parts! For the sand, yes! Come with me; I will show you." She beckons
you onto the camel.

After riding a bit across the sands of Desert Island, you can see what
look like very large rocks covering half of the horizon. The Elf explains
that the rocks are all along the part of Desert Island that is directly
above Island Island, making it hard to even get there. Normally, they use
big machines to move the rocks and filter the sand, but the machines have
broken down because Desert Island recently stopped receiving the parts
they need to fix the machines.

You've already assumed it'll be your job to figure out why the parts
stopped when she asks if you can help. You agree automatically.

Because the journey will take a few days, she offers to teach you the game
of Camel Cards. Camel Cards is sort of similar to poker except it's
designed to be easier to play while riding a camel.

In Camel Cards, you get a list of hands, and your goal is to order them
based on the strength of each hand. A hand consists of five cards labeled
one of A, K, Q, J, T, 9, 8, 7, 6, 5, 4, 3, or 2. The relative strength of
each card follows this order, where A is the highest and 2 is the lowest.

Every hand is exactly one type. From strongest to weakest, they are:

 - Five of a kind, where all five cards have the same label: AAAAA
 - Four of a kind, where four cards have the same label and one card has a
   different label: AA8AA
 - Full house, where three cards have the same label, and the remaining
   two cards share a different label: 23332
 - Three of a kind, where three cards have the same label, and the
   remaining two cards are each different from any other card in the hand:
   TTT98
 - Two pair, where two cards share one label, two other cards share a
   second label, and the remaining card has a third label: 23432
 - One pair, where two cards share one label, and the other three cards
   have a different label from the pair and each other: A23A4
 - High card, where all cards' labels are distinct: 23456

Hands are primarily ordered based on type; for example, every full house
is stronger than any three of a kind.

If two hands have the same type, a second ordering rule takes effect.
Start by comparing the first card in each hand. If these cards are
different, the hand with the stronger first card is considered stronger.
If the first card in each hand have the same label, however, then move on
to considering the second card in each hand. If they differ, the hand with
the higher second card wins; otherwise, continue with the third card in
each hand, then the fourth, then the fifth.

So, 33332 and 2AAAA are both four of a kind hands, but 33332 is stronger
because its first card is stronger. Similarly, 77888 and 77788 are both a
full house, but 77888 is stronger because its third card is stronger (and
both hands have the same first and second card).

To play Camel Cards, you are given a list of hands and their corresponding
bid (your puzzle input). For example:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483

This example shows five hands; each hand is followed by its bid amount.
Each hand wins an amount equal to its bid multiplied by its rank, where
the weakest hand gets rank 1, the second-weakest hand gets rank 2, and so
on up to the strongest hand. Because there are five hands in this example,
the strongest hand will have rank 5 and its bid will be multiplied by 5.

So, the first step is to put the hands in order of strength:

 - 32T3K is the only one pair and the other hands are all a stronger type,
   so it gets rank 1.
 - KK677 and KTJJT are both two pair. Their first cards both have the same
   label, but the second card of KK677 is stronger (K vs T), so KTJJT gets
   rank 2 and KK677 gets rank 3.
 - T55J5 and QQQJA are both three of a kind. QQQJA has a stronger first
   card, so it gets rank 5 and T55J5 gets rank 4.

Now, you can determine the total winnings of this set of hands by adding
up the result of multiplying each hand's bid with its rank (765 * 1 + 220
* 2 + 28 * 3 + 684 * 4 + 483 * 5). So the total winnings in this example
are 6440.

Find the rank of every hand in your set. What are the total winnings?

Part 2

To make things a little more interesting, the Elf introduces one
additional rule. Now, J cards are jokers - wildcards that can act like
whatever card would make the hand the strongest type possible.

To balance this, J cards are now the weakest individual cards, weaker even
than 2. The other cards stay in the same order: A, K, Q, T, 9, 8, 7, 6, 5,
4, 3, 2, J.

J cards can pretend to be whatever card is best for the purpose of
determining hand type; for example, QJJQ2 is now considered four of a
kind. However, for the purpose of breaking ties between two hands of the
same type, J is always treated as J, not the card it's pretending to be:
JKKK2 is weaker than QQQQ2 because J is weaker than Q.

Now, the above example goes very differently:

32T3K 765
T55J5 684
KK677 28
KTJJT 220
QQQJA 483

 - 32T3K is still the only one pair; it doesn't contain any jokers, so its
   strength doesn't increase.
 - KK677 is now the only two pair, making it the second-weakest hand.
 - T55J5, KTJJT, and QQQJA are now all four of a kind! T55J5 gets rank 3,
   QQQJA gets rank 4, and KTJJT gets rank 5.

With the new joker rule, the total winnings in this example are 5905.

Using the new joker rule, find the rank of every hand in your set. What
are the new total winnings?

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

#include <cassert>

#include "aoc.h"

// Global flag: Is J card joker or not?
bool jokers_enabled = false;

// Card is stored in this data structure.
struct card {
	int value = 0;	// Instead of the card label, its value is stored.

	// Tables for converting card value back to label.
	static const char labels[13];
	static const char joker_labels[13];

	// Implicit constructor creates an empty card, this
	// method sets the card value.
	void set(const char c) {
		if (false == jokers_enabled) {
			for (int i = 0; i < 13; ++i) {
				if (c == labels[i]) { value = i + 1; break; }
			}
		} else {
			for (int i = 0; i < 13; ++i) {
				if (c == joker_labels[i]) { value = i + 1; break; }
			}
		}
	}

	// Return card label.
	char label() const {
		if (false == jokers_enabled) {
			return (value > 0) ? labels[value - 1] : 0;
		} else {
			return (value > 0) ? joker_labels[value - 1] : 0;
		}
	}

	// Card is joker if jokers are enabled and it's the 'J' card.
	inline bool is_joker() const { return jokers_enabled ? (1 == value) : false; }

	friend inline bool operator==(card lhs, card rhs) { return lhs.value == rhs.value; }
	friend inline bool operator< (card lhs, card rhs) { return lhs.value < rhs.value; }
};

// Card label tables.
const char card::labels[13] = {	'2', '3', '4', '5', '6', '7', '8', '9',	'T', 'J', 'Q', 'K', 'A' };
const char card::joker_labels[13] = { 'J', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'Q', 'K', 'A' };


// The card hand is stored in this data structure.
struct hand {
	// Both arrays contain same cards.
	card sorted_cards[5] { 0, 0, 0, 0, 0 };	// Card sorted by value.
	card inhand_cards[5] { 0, 0, 0, 0, 0 };	// Here we have the cards in original order.
	long bid;

	// Implicit constructor creates an empty hand, this
	// method sets the cards into hand.
	void set(std::string s, long b) {
		for (int i = 0; i < 5; ++i) {
			char c = s[i];
			inhand_cards[i].set(c);
			sorted_cards[i].set(c);
		}
		std::sort(sorted_cards, sorted_cards+5);
		bid = b;
	}

	// Return hand as card label string.
	std::string cardstring() const {
		std::string s;
		for (const auto& c : inhand_cards) {
			s += c.label();
		}
		return s;
	}

	// Return number of different cards.
	// Jokers, if enabled, are not counted.
	// (JJJJJ still returns correctly 1.)
	int num_diff() const {
		int num = 1;
		int last = -1;
		for (int i = 0; i < 5; ++i) {
			if (sorted_cards[i].is_joker()) continue;
			if (-1 == last) {
				last = sorted_cards[i].value;
			} else if (sorted_cards[i].value != last) {
				num += 1;
				last = sorted_cards[i].value;
			}
		}
		return num;
	}

	// Return largest quantity of same cards.
	// When jokers are enabled, count jokers separately and add them to the count.
	int most_same() const {
		int most = 0;
		int num = 0;
		int num_jokers = 0;
		int last = -1;
		for (int i = 0; i < 5; ++i) {
			if (sorted_cards[i].is_joker()) {
				num_jokers += 1;
			} else {
				if (-1 == last) {
					last = sorted_cards[i].value;
					num = 1;
				} else if (sorted_cards[i].value == last) {
					num += 1;
				} else {
					last = sorted_cards[i].value;
					num = 1;
				}
			}
			most = std::max(most, num);
		}
		most += num_jokers;
		return most;
	}

	// Return hand rank value.
	int value() const {
		auto n = num_diff();
		auto m = most_same();
		if (1 == n) return 7;		// five of a kind
		if (2 == n) {
			if (4 == m) return 6;	// four of a kind
			else return 5;			// full house
		}
		if (3 == n) {
			if (3 == m) return 4;	// three of a kind
			else return 3;			// two pair
		}
		if (4 == n) return 2;		// one pair
		return 1;					// high card
	}

	// Return string of hand rank value.
	std::string valuestring() const {
		switch (value()) {
			case 7: return "(7) five of a kind";
			case 6: return "(6) four of a kind";
			case 5: return "(5) full house";
			case 4: return "(4) three of a kind";
			case 3: return "(3) two pair";
			case 2: return "(2) one pair";
			case 1: return "(1) high card";
			default: return "";
		}
	}
};


// Evaluation function for sort().
// Hand has lower value when the hand rank (hand.value) is lower,
// or if the rank is equal, when non-sorted card values are lower.
bool betterhand(const hand& lhs, const hand& rhs) {
	if (lhs.value() == rhs.value()) {
		// Same rank, compare card values.
		for (int i = 0; i < 5; ++i) {
			if (lhs.inhand_cards[i].value == rhs.inhand_cards[i].value) continue;
			return lhs.inhand_cards[i].value < rhs.inhand_cards[i].value;
		}
		// The only case when for loop ends here is when lhs cards are exactly
		// the same as rhs cards. In that case the final comparison result is
		// returned (-> false).
	}
	return lhs.value() < rhs.value();
}


long day07(int puzzle_part, std::istream& puzzle_input)
{
	long total = 0;	// Solution result is stored here.

	// Set the global flag when running puzzle part 2.
	jokers_enabled = (puzzle_part == 2) ? true : false;
	if (debug) std::cout << "\nUsing joker cards: " << (jokers_enabled ? "YES" : "NO") << std::endl;
	
	std::vector<hand> hands;	// All card hands are stored here.

	// Read puzzle input
	for (std::string line; std::getline(puzzle_input, line); ) {
		auto pos = line.find(' ');
		hand h;
		h.set(line.substr(0, pos), std::stol(line.substr(pos + 1)));
		hands.push_back(h);
	}

	if (debug) {
		for (const auto& h : hands) {
			std::cout << "Hand: " << h.cardstring() << " Diff cards: " << h.num_diff()
				<< " Most same: " << h.most_same() << " Bid: " << h.bid << std::endl;
		}
	}

	// Sort hands.
	if (debug) std::cout << "Sorting " << hands.size() << " items." << std::endl;
	std::sort(hands.begin(), hands.end(), betterhand);

	// Count each hand totals.
	long rank = 1;
	for (const auto& h : hands) {
		if (debug) std::cout << "# " << rank << ": " << h.cardstring() << " " << h.valuestring() << std::endl;
		total += h.bid * rank++;
	}

	return total;
}

/*

*/
