#include <iostream>
#include <map>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

struct Match {
    std::string home_name;
    std::string away_name;
    int home_score = 0;
    int away_score = 0;

    uint64_t total_score() const {
        return home_score + away_score;
    }
};

std::ostream &operator<<(std::ostream &os, const Match &match) {
    os << match.home_name << ": " << match.home_score << " - " << match.away_name << ": " << match.away_score;
    return os;
}

class Scoreboard {
public:
    uint64_t add_match(Match match) {
        static uint64_t id = 0;
        matches.insert({id, std::move(match)});
        return id++;
    }

    void summary() {
        for (const auto &[id, match]: matches) {
            std::cout << match << std::endl;
        }
    }

private:
    std::map<uint64_t, Match> matches;
};

int main() {
    Match match{.home_name = "h1", .away_name = "a1", .home_score = 1, .away_score = 2};
    std::cout << match << std::endl;

    Scoreboard scoreboard;
    scoreboard.add_match({.home_name = "h2", .away_name = "a2", .home_score = 0, .away_score = 3});

    scoreboard.summary();

    return 0;
}
