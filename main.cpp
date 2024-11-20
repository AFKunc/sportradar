#include <iostream>
#include <include/scoreboard.hpp>

int main() {
    std::vector<detail::Match> test_matches1{
            {.home_name = "Mexico", .away_name = "Canada", .home_score = 0, .away_score = 5},
            {.home_name = "Spain", .away_name = "Brazil", .home_score = 10, .away_score = 2},
            {.home_name = "Germany", .away_name = "France", .home_score = 2, .away_score = 2},
            {.home_name = "Uruguay", .away_name = "Italy", .home_score = 6, .away_score = 6},
            {.home_name = "Argentina", .away_name = "Australia", .home_score = 3, .away_score = 1},
    };
    sbd::Scoreboard scoreboard;
    scoreboard.summary();

    for (const auto& match: test_matches1) {
        auto id = scoreboard.start_match(match.home_name, match.away_name);
        scoreboard.update_match(*id, match.home_score, match.away_score);
    }
    scoreboard.summary();

    std::cout << std::endl;
    scoreboard.update_match(1, 11, 2);// update mexico vs canada
    scoreboard.summary();

    // try to add different combinations of team names that are already playing
    auto same_home= test_matches1[0];
    same_home.away_name = "new_away";
    auto none = scoreboard.start_match(same_home.home_name, same_home.away_name);  //no-op
    std::cout << (none == std::nullopt) << std::endl;

    auto same_away= test_matches1[0];
    same_away.home_name = "new_home";
    none = scoreboard.start_match(same_away.home_name, same_away.away_name); //no-op
    std::cout << (none == std::nullopt) << std::endl;
    scoreboard.summary();
    std::cout << "-----" << std::endl;

    std::cout << std::endl;
    scoreboard.end_match(0);// remove mexico vs canada
    scoreboard.summary();
    std::cout << "-----" << std::endl;

    scoreboard.update_match(-1, 0, 0);
    scoreboard.end_match(-1); // no-op
    scoreboard.summary();

    return 0;
}