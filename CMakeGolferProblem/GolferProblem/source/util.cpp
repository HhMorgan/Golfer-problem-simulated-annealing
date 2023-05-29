#include <util.h>
#include <algorithm>
#include <random>
#include <unordered_set>

void Util::randomIntialization(short players, short group_size, short groups, short weeks, std::vector<std::vector<std::vector<short>>> &schedule) {
    std::vector <short> flattened_players{};
    flattened_players.resize(players);
    for (short i = 1; i <= players; i++) {
        flattened_players[i - 1] = i;
    }
    schedule.resize(weeks);
    std::cout << "size: " << schedule.size() <<std::endl;
    for (int i = 0; i < weeks; i++) {
        unsigned seed = 0;
        std::shuffle(flattened_players.begin(), flattened_players.end(),
            std::default_random_engine(seed));

        schedule[i].resize(groups, std::vector<short>(group_size));

        for (int j = 0; j < groups; j++) {
            for (int k = 0; k < group_size; k++) {
                schedule[i][j][k] = flattened_players[j*group_size + k];
            }
        }
    }
}

int evalForWeek(std::vector<std::vector<short>> week, int penalty) {
    int score = 0;

    struct hashFunctionWeeks {
        unsigned int operator()(const short& x) const {
            return x;
        }
    };

    std::unordered_set<short, hashFunctionWeeks> state_space_weeks;

    for (int i = 0; i < week.size(); i++) {
        for (int j = 0; j < week[i].size(); j++) {
            if (state_space_weeks.count(week[i][j])) {
                score += penalty;
            }
            else {
                state_space_weeks.insert(week[i][j]);
            }
        }
    }
    state_space_weeks.clear();
    return score;
}

using TupleShort = std::tuple<short, short>;

int evalForSchedule(GolferProblem p, int penalty) {
    int score = 0;
    auto schedule = p.schedule;

    struct hashFunctionWeeks {
        std::size_t operator()(const TupleShort& tuple) const {
            std::size_t seed = 7287;

            auto hash_combine = [](std::size_t& seed, const short& value) {
                seed ^= std::hash<short>()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            };

            hash_combine(seed, std::get<0>(tuple));
            hash_combine(seed, std::get<1>(tuple));

            return seed;
        }
    };

    std::unordered_set<TupleShort, hashFunctionWeeks> state_space;

    for (int i = 0; i < schedule.size(); i++) {
            for (auto group : schedule[i]) {
                std::vector<TupleShort> pairs;
                for (size_t i = 0; i < group.size(); ++i) {
                    for (size_t j = i + 1; j < group.size(); ++j) {
                        pairs.emplace_back(std::make_tuple(group[i], group[j]));
                    }
                }

                for (TupleShort tuple : pairs) {
                    TupleShort tuple_reversed = { std::get<1>(tuple), std::get<0>(tuple) };
                    if (state_space.count(tuple) || state_space.count(tuple_reversed)) {
                        score += penalty;
                    }
                    else {
                        state_space.insert(tuple);
                    }
                }

            }
    }

    state_space.clear();
    return score;
}


int Util::eval(GolferProblem p, int penalty_per_week, int penalty_global) {
    int score = 0;
    for (auto week : p.schedule) {
        score += evalForWeek(week, penalty_per_week);
    }
    score += evalForSchedule(p, penalty_global);
    return score;
}

void swap_locations(GolferProblem& p, short week_index, short group_index_1, short player_index_1, short group_index_2, short player_index_2) {
    auto temp = p.schedule[week_index][group_index_1][player_index_1];
    p.schedule[week_index][group_index_1][player_index_1] = p.schedule[week_index][group_index_2][player_index_2];
    p.schedule[week_index][group_index_2][player_index_2] = temp;
}
void swap_randomly(GolferProblem& p, short week_index, short group_index_1, short player_index_1, short range_beginning, short range_ending) {

}

void Util::swap(GolferProblem& p, std::vector<short> meta_info, int mode) {
    switch (mode){
      case 0: 
          swap_locations(p, meta_info[0], meta_info[1], meta_info[2], meta_info[3], meta_info[4]);
      case 1:
          swap_randomly(p, meta_info[0], meta_info[1], meta_info[2], meta_info[3], meta_info[4]);
    default:
        break;
    }
}

