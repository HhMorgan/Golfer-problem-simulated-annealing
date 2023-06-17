#include <iostream>
#include <algorithm>
#include <GolferProblem.h>
//#include <util.h>
#include <solver.h>
#include <iostream>
#include <fstream>
#include <numeric>
#include <cmath>
#include <vector>

void executor(std::ofstream& file) {
	std::vector<GolferProblem> instances = { GolferProblem(5, 8, 4), GolferProblem(6, 8, 4), GolferProblem(7, 8, 4), GolferProblem(10, 8, 4),
									GolferProblem(4, 5, 3), GolferProblem(5, 5, 3), GolferProblem(6, 5, 3), GolferProblem(7, 5, 3),
									GolferProblem(3, 7, 5), GolferProblem(4, 7, 5), GolferProblem(5, 7, 5), GolferProblem(6, 7, 5),
									GolferProblem(4, 10, 5), GolferProblem(5, 10, 5), GolferProblem(6, 10, 5), GolferProblem(9, 10, 5),
									GolferProblem(3, 9, 6), GolferProblem(4, 9, 6), GolferProblem(5, 9, 6), GolferProblem(6, 9, 6),
									GolferProblem(6, 12, 4), GolferProblem(7, 12, 4), GolferProblem(8, 12, 4), GolferProblem(11, 12, 4),
									GolferProblem(11, 6, 2) };
	std::vector<int> scores;
	GolferProblem temp = instances[0];

	for (int i = 0; i < instances.size(); i++) {
		scores.clear();
		file << "\n====================--------------====================\n";
		file << "Instance (" << instances[i].groups << "-" << instances[i].group_size << "-" << instances[i].weeks << ")\n";
		for (size_t j = 0; j < 5; j++) {
			SimulatedAnnealingNPAbsolute simulated_annealing(500, 0.001f, 105.0f, 0.99f, 8, 0, 1, 5);
			file << "Iteration " << j + 1 << "\n";
			temp = instances[i];
			Util::randomIntialization(temp.players, temp.group_size, temp.groups, temp.weeks, temp.schedule);
			simulated_annealing.solve(temp);
			file << "Schedule: " << "\n";

			auto threeD = temp.schedule;

			std::for_each(threeD.begin(), threeD.end(), [=,&file](const auto& row) {
				std::for_each(row.begin(), row.end(), [=,&file](const auto& col) {
					file << "[";
					std::copy(col.begin(), col.end(), std::ostream_iterator<int>(file, " "));
					file << "]";
					});
				file << std::endl;
				});
			file << std::endl;

			int score = Util::eval(temp, 1, 5);
			file << "Score: " << score << "\n";
			int conflicts = Util::eval(temp, 1, 1);
			file << "Conflicts: " << conflicts << "\n";
			file << "\n";
			scores.push_back(score);
		}
		double mean = static_cast<double>(std::accumulate(scores.begin(), scores.end(), 0)) / scores.size();
		double sumOfSquares = std::accumulate(scores.begin(), scores.end(), 0.0, [mean](double acc, int value) {
			return acc + pow(value - mean, 2);
			});
		double standardDeviation = sqrt(sumOfSquares / scores.size());
		std::stable_sort(scores.begin(), scores.end());
		double median;
		if (scores.size() % 2 == 0) {
			median = static_cast<double>(scores[scores.size() / 2 - 1] + scores[scores.size() / 2]) / 2;
		}
		else {
			median = static_cast<double>(scores[scores.size() / 2]);
		}
		int maximum = *std::max_element(scores.begin(), scores.end());
		int minimum = *std::min_element(scores.begin(), scores.end());
		file << "Mean for Instance (" << instances[i].groups << "-" << instances[i].group_size << "-" << instances[i].weeks << "): " << mean << "\n";
		file << "Standard Deviation for Instance (" << instances[i].groups << "-" << instances[i].group_size << "-" << instances[i].weeks << "): " << standardDeviation << "\n";
		file << "Median for Instance (" << instances[i].groups << "-" << instances[i].group_size << "-" << instances[i].weeks << "): " << median << "\n";
		file << "Max for Instance (" << instances[i].groups << "-" << instances[i].group_size << "-" << instances[i].weeks << "): " << maximum <<"\n";
		file << "Min for Instance (" << instances[i].groups << "-" << instances[i].group_size << "-" << instances[i].weeks << "): " << minimum << "\n";
		file << "\n";
		file << "\n====================--------------====================\n";
		file.flush();
	}
	file.close();

}
void gridSearch(std::ofstream& file) {
	int cost = 100000;
	float max_temp[7] = { 90.,95.,100.,105.,110.,115. };
	float min_temp[4] = { 0.001,0.01,0.05,0.1 };
	int activation_function[2] = { 0 };
	int k[4] = { 2,3,4,8 };
	float cooling[7] = { 0.65,0.75,0.85,0.9,0.95,0.975,0.99 };

	for (const auto& mt : max_temp) {
		for (const auto& lt : min_temp) {
			for (const auto& ct : cooling) {
				for (const auto& ki : k) {
					for (const auto& af : activation_function) {
						GolferProblem p(10, 8, 4);
						Util::randomIntialization(p.players, p.group_size, p.groups, p.weeks, p.schedule);
						file << "Paramters are " << " Max Temp: " << mt << " Min temp: " << lt << " Cooling Rate: " << ct << " k: " << ki << "Activation: " << af << " Week Penalty: " << 1 << " Global Penalty " << 5 << "\n";
						std::cout << "Paramters are " << " Max Temp: " << mt << " Min temp: " << lt << " Cooling Rate: " << ct << " k: " << ki << "Activation: " << af << " Week Penalty: " << 1 << " Global Penalty " << 5 << "\n";

						file << "\n";

						SimulatedAnnealingNPAbsolute simulated_annealing(100, lt, mt, ct, ki, af, 1, 5);
						simulated_annealing.solve(p);
						int score = Util::eval(p, 1, 1);
						file << "Score is " << score << "\n";
						file << "\n";

						if (score < cost) {
							cost = score;
							std::cout << "New best score is " << score << "\n";
							std::cout << "\n";
							file << "New best score is " << score << "\n";
							file << "\n";

						}
						file.flush();

					}
				}
			}
		}
	}
	file.close();
}

int main() {

	std::ofstream outputFile("results_cont.txt");  // Open file for writing
	executor(outputFile);
	/*GolferProblem p(10, 8, 4);
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
	*/
}

