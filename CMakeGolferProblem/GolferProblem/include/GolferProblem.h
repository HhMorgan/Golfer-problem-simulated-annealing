// GolferProblem.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>

// TODO: Reference additional headers your program requires here.
struct GolferProblem {	
	short weeks;
	short groups;
	short group_size;
	short players;
	
	std::vector<std::vector<std::vector<short>>> schedule{};

	int score = - 1;

	GolferProblem(short weeks, short groups, short group_size) :
																weeks(weeks), 
																groups(groups), 
																group_size(group_size), 
																players(groups * group_size){}


};

