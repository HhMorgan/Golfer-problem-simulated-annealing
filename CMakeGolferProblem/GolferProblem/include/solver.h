#include <iostream>
#include <util.h>
/*
    array of shorts of weeks to be modified
    array of shorts of groups to be changed from all weeks
    the nearest neighbors will be the range of the groups one is allowed to swap with
    The swapping function should be versatile 
*/
class SimulatedAnnealingNPAbsolute {
public:
    std::vector<short> weeks_range{};
    std::vector<short> groups_range{};
    int steps;
    float min_temperature;
    float max_temperature;
    //from 0.0f to 1.0f
    float cooling_rate;
    int k = -1;
    int activation_function = 0;
    int penalty_per_week;
    int penalty_global;

    SimulatedAnnealingNPAbsolute(
        const std::vector<short> weeks_range,
        const std::vector<short> groups_range,
        int steps,
        float min_temperature,
        float max_temperature,
        float cooling_rate,
        int k,
        int activation_function,
        int penalty_per_week, 
        int penalty_global) :
        weeks_range(weeks_range), groups_range(groups_range), steps(steps),
        min_temperature(min_temperature), max_temperature(max_temperature), 
        cooling_rate(cooling_rate), k(k), activation_function(activation_function), 
        penalty_per_week(penalty_per_week), penalty_global(penalty_global){};

    SimulatedAnnealingNPAbsolute(
        int steps,
        float min_temperature,
        float max_temperature,
        float cooling_rate,
        int k,
        int activation_function,
        int penalty_per_week,
        int penalty_global) :
        steps(steps),
        min_temperature(min_temperature), max_temperature(max_temperature),
        cooling_rate(cooling_rate), k(k), activation_function(activation_function),
        penalty_per_week(penalty_per_week), penalty_global(penalty_global) {};

   SimulatedAnnealingNPAbsolute(
        int steps,
        float min_temperature,
        float max_temperature,
        float cooling_rate,
        int activation_function,
        int penalty_per_week,
        int penalty_global) :
        weeks_range(weeks_range), groups_range(groups_range), steps(steps),
        min_temperature(min_temperature), max_temperature(max_temperature),
        cooling_rate(cooling_rate), activation_function(activation_function),
        penalty_per_week(penalty_per_week), penalty_global(penalty_global) {};

     void solve(GolferProblem &p);
};

