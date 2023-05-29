#include <iostream>
#include <algorithm>
#include <GolferProblem.h>
//#include <util.h>
#include <solver.h>

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

	std::cout << "\n====================--------------====================\n" << std::endl;
	
	std::vector<short> weeks_range;
	std::vector<short> groups_range;
	for (short i = 1; i < p.weeks; i++) {
		weeks_range.push_back(i);
	}
	for (short i = 0; i < p.groups; i++) {
		groups_range.push_back(i);
	}

	SimulatedAnnealingNPAbsolute simulated_annealing(weeks_range, groups_range,100, 0.01f, 100.0f, 0.95f,3,0,1,5);
	//SimulatedAnnealingNPAbsolute simulated_annealing(200, 0.01f, 100.0f, 0.95f, 0, 1, 5);
	simulated_annealing.solve(p);
	threeD = p.schedule;
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


	std::cout << "\n====================--------------====================\n" << std::endl;

	SimulatedAnnealingNPAbsolute simulated_annealing2(100, 0.001f, 100.0f, 0.95f, 0, 1, 5);
	simulated_annealing2.solve(p);
	threeD = p.schedule;
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