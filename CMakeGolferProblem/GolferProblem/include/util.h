#include <iostream>
#include <vector>
#include <GolferProblem.h>

#define F_ROUND_INT(x) static_cast<int> (lroundf(x))

class Util {
public:
	static void randomIntialization(short players, short group_size, short groups, short weeks,std::vector<std::vector<std::vector<short>>> &schedule);
	static int eval(GolferProblem p, int penalty_per_week, int penalty_global);
	static void swap(GolferProblem& p, std::vector<short> meta_info, int mode);
};

