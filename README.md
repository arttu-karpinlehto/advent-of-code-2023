# Advent of Code 2023 solutions
by Arttu Kärpinlehto

Last year I was trying out different tools for different problems, mainly to see if I could produce the solutions with less overhead - 
kind of using the right tool for the right job.  There was some bash in the beginning, then C++, a little bit of Java in the form of Processing, and even PHP for some reason.  The weirdest was day 2 solution made with Excel; which I am very proud of.

This season I will try to solve all puzzles with just C++, having recently built myself a very useful VSCode environment.  I've also built some scaffolding around the daily puzzles.  Basically I need only to create a C++ source file for each day, then iterate between coding and unit test until the solution works, and then run make.

All solutions are linked to a single executable aoc2023.  Each puzzle is launched with two parameters, day and part:

	aoc2023 1 1

starts day 1, part 1.  Optional `debug` parameter switches on the some debugging output.

## day*NN*.cpp
Each day solution is in its own C++ source file, eg. `day01.cpp`

## day*NN*-input.txt

Each puzzle input is in its own text file, eg. `day01-input.txt`

## aocmain.cpp

Main function and simple scaffolding for opening the puzzle input file.

## unit_tests.h

As each puzzle description will have test/example data, those are entered here as unit tests.  These are run using the VSCode extension `cpp-unit-test` by AutumnMoon.

