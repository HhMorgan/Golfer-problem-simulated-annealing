#include <iostream>

#include "../include/GolferProblem.h"

#include <algorithm>
#include "../include/util.h"

int main(){
	GolferProblem p(10,8,4);
	//GolferProblem p(2, 4, 3);
	std::cout << "number of players is "<< p.players << std::endl;
	
	Util::randomIntialization(p.players, p.group_size, p.groups, p.weeks, p.schedule);
	auto threeD = p.schedule;
	std::cout << "the random initialization: " << std::endl;
	std::for_each(threeD.begin(), threeD.end(), [](const auto& row) { 
		std::for_each(row.begin(), row.end(), [](const auto& col) { 
			std::cout << "[";
			std::copy(col.begin(), col.end(), std::ostream_iterator<int>(std::cout, " ")); 
			std::cout << "]";
			}); 
		std::cout << std::endl;
		});
	std::cout << std::endl;
	std::cout << "The evaluation of the current schedule is " << Util::eval(p, 1, 1) << std::endl;

}