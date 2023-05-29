#include <solver.h>
#include <random>

void SimulatedAnnealingNPAbsolute::solve(GolferProblem& p) {
    if (k = -1) k = p.groups;
    if (weeks_range.empty()) {
        //std::cout << "weeks empty" << std::endl;
        for (short i = 0; i < p.weeks; i++) {
            weeks_range.push_back(i);
        }
    }
    if (groups_range.empty()) {
        //std::cout << "groups empty" << std::endl;
        for (short i = 0; i < p.groups; i++) {
            groups_range.push_back(i);
        }
    }

    std::random_device device;
    std::default_random_engine engine(device());
    std::uniform_real_distribution<float> distribution_weeks(0.0f, static_cast <float> (weeks_range.size() - 1));
    std::uniform_real_distribution<float> distribution_groups(0.0f, static_cast <float> (groups_range.size() - 1));
    std::uniform_real_distribution<float> distribution_group_size(0.0f, static_cast <float> (p.group_size - 1));
    std::uniform_real_distribution<float> distribution_probability(0.0f, 1.0f);

    //Simulated annealing computation
    for (float temperature = this->max_temperature;
        temperature > this->min_temperature; temperature *= this->cooling_rate) {

        short current_week_index = weeks_range[F_ROUND_INT(distribution_weeks(engine))];
        auto current_week = p.schedule[current_week_index];

        int current_best_eval = Util::eval(p,penalty_per_week,penalty_global);


        for (int t = 0; t < this->steps; t++) {
            short current_group_index = groups_range[F_ROUND_INT(distribution_groups(engine))];
            auto current_group = current_week[current_group_index];
            short current_player_index = F_ROUND_INT(distribution_group_size(engine));
            auto current_player = current_group[current_player_index];

            auto beginning_range = ((current_group_index - (k / 2))) < 0 ?
                0 :
                (current_group_index - k / 2);
            beginning_range = ((current_group_index + (k / 2))) > p.groups - 1 ?
                (beginning_range - k / 2 >= 0 ? beginning_range - k / 2 : 0) :
                beginning_range;
            auto end_range = ((current_group_index + (k / 2))) > p.groups - 1 ?
                p.groups - 1 :
                (current_group_index + (k / 2));
            end_range = ((current_group_index - (k / 2))) < 0 ?
                (end_range + k / 2 <= p.groups - 1 ? end_range + k / 2 : p.groups - 1) :
                end_range;
            //We now get another random point to check if we should swap it with the other one
            short other_group_index;
            std::vector<short> other_group;
            short other_player_index;
            short other_player;

            if (activation_function == 0) {
                std::uniform_real_distribution<float> distribution_ranged_groups(static_cast <float> (beginning_range),
                    static_cast <float> (end_range));

                other_group_index = groups_range[F_ROUND_INT(distribution_ranged_groups(engine))];
                other_group = current_week[other_group_index];
                other_player_index = F_ROUND_INT(distribution_group_size(engine));
                other_player = other_group[other_player_index];
                std::vector<short> parameters = { current_week_index, current_group_index, current_player_index, other_group_index, other_player_index };
                Util::swap(p, parameters, activation_function);
            
            }
            if (activation_function == 1) {
                std::vector<short> parameters = { current_week_index, current_group_index, current_player_index, 1, p.players };
                Util::swap(p, parameters, activation_function);
            }
            

            //Calculates the value of the evaluation of the graph after the swap.
            int new_vertex_eval = Util::Util::eval(p, penalty_per_week, penalty_global);
            //Computes the difference between the magnitude of the two scores.
            int eval_diff = new_vertex_eval - current_best_eval;
            //Computes the probablity which is used if the eval score of the new graph is less than old
            double probablity = std::exp(static_cast<float>(eval_diff * -1) / temperature);
            //Gets a random value that will be checked against the probablity
            double random_variable_probablity = distribution_probability(engine);
            //Due to the manner this approach is done, the check in here tries to confirm if the algorithm needs to return back to the old graph.
            //Hence, we check if the old score is better and probablity is less than the random value that got generated.
            if (current_best_eval <= new_vertex_eval && random_variable_probablity > probablity) {
                //if that is the case then we return back to the old values of the vertices.
                if (activation_function == 0) {
                    std::vector<short> parameters = { current_week_index, current_group_index, current_player_index, other_group_index, other_player_index };
                    Util::swap(p, parameters, activation_function);
                }
                else {
                    if (activation_function == 1) {
                        p.schedule[current_week_index][current_group_index][current_player_index] = current_player;
                    }
                }
            }
            else {
                //otherwise, we set the current best score to the new one and the current location of the vertix which is being checked to the new one.
                current_best_eval = new_vertex_eval;
                current_player = p.schedule[current_week_index][current_group_index][current_player_index];
            }
        }
    }
}
