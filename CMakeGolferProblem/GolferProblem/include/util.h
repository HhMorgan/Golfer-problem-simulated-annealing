#include <iostream>
#include <vector>
#include "GolferProblem.h"

class Util {
public:
	static void randomIntialization(short players, short group_size, short groups, short weeks,std::vector<std::vector<std::vector<short>>> &schedule);
	static int eval(GolferProblem p, int penalty_per_week, int penalty_global);
};

