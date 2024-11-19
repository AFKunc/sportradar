#include <algorithm>
#include <iostream>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

using MatchId = uint64_t;

struct Match {
    MatchId id;
    std::string home_name;
    std::string away_name;
    unsigned home_score = 0;
    unsigned away_score = 0;

    uint64_t total_score() const {
        return home_score + away_score;
    }

    bool operator<(const Match& other) const {
        if (total_score() != other.total_score()) {
            return total_score() < other.total_score();
        }
        return id > other.id;
    }
};

std::ostream& operator<<(std::ostream& os, const Match& match) {
    os << match.home_name << ": " << match.home_score << " - " << match.away_name << ": " << match.away_score;
    return os;
}

class Scoreboard {
public:
    MatchId start_match(std::string home_name, std::string away_name) {
        Match match{next_id, std::move(home_name), std::move(away_name)};
        matches.insert({next_id, match});
        return next_id++;
    }

    void update_match(MatchId id, uint64_t home_score, uint64_t away_score) {
        if (auto match_itr = matches.find(id); match_itr != matches.end()) {
            match_itr->second.home_score = home_score;
            match_itr->second.away_score = away_score;
        }
    }

    void remove_match(MatchId id) {
        matches.erase(id);
    }

    void end_match(MatchId id) {
        auto match = matches.find(id);
        if (match != matches.end()) {
            match->second.home_score = 0;
            match->second.away_score = 0;
        }
    }

    auto summary() const {
        std::vector<std::pair<MatchId, Match>> summary(matches.cbegin(), matches.cend());
        std::sort(summary.begin(), summary.end());

        for (const auto& [_, match]: summary) {
            std::cout << match << std::endl;
        }

        return summary;
    }

private:
    MatchId next_id = 0;
    std::map<MatchId, Match> matches;
};

int main() {
    std::vector<Match> test_matches1{
            {.home_name = "Mexico", .away_name = "Canada", .home_score = 0, .away_score = 5},
            {.home_name = "Spain", .away_name = "Brazil", .home_score = 10, .away_score = 2},
            {.home_name = "Germany", .away_name = "France", .home_score = 2, .away_score = 2},
            {.home_name = "Uruguay", .away_name = "Italy", .home_score = 6, .away_score = 6},
            {.home_name = "Argentina", .away_name = "Australia", .home_score = 3, .away_score = 1},
            //            {.home_name = "NaszeChłopaki", .away_name = "*******!!!", .home_score = std::numeric_limits<int>().max(), .away_score = 0},
    };
    Scoreboard scoreboard;
    scoreboard.summary();

    for (const auto& match: test_matches1) {
        auto id = scoreboard.start_match(match.home_name, match.away_name);
        scoreboard.update_match(id, match.home_score, match.away_score);
    }
    scoreboard.summary();

    std::cout << std::endl;
    scoreboard.update_match(1, 11, 2);// update mexico vs canada
    scoreboard.summary();


    std::cout << std::endl;
    scoreboard.remove_match(0);// remove mexico vs canada
    scoreboard.summary();
    return 0;
}
