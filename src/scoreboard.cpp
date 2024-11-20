#include <algorithm>
#include <iostream>
#include <optional>
#include <ranges>
#include <string>
#include <utility>
#include <vector>
#include <include/scoreboard.hpp>

using namespace sbd;

uint64_t detail::Match::total_score() const {
    return home_score + away_score;
}

bool detail::Match::operator<(const Match& other) const {
    if (total_score() != other.total_score()) {
        return total_score() > other.total_score();
    }
    return id > other.id;
}

// for debugging
std::ostream& operator<<(std::ostream& os, const detail::Match& match) {
    os << match.home_name << ": " << match.home_score << " - " << match.away_name << ": " << match.away_score;
    return os;
}


std::optional<MatchId> Scoreboard::start_match(std::string home_name, std::string away_name) {
    if (!is_match_valid(home_name, away_name))
        return std::nullopt;

    detail::Match match{next_id, std::move(home_name), std::move(away_name)};
    matches.insert({next_id, match});
    return next_id++;
}

bool Scoreboard::is_match_valid(std::string home_name, std::string away_name) const {
    for (const auto& [_, match]: matches) {
        if (match.home_name == home_name || match.home_name == away_name || match.away_name == home_name || match.away_name == away_name)
            return false;
    }
    return true;
}

bool Scoreboard::update_match(MatchId id, uint64_t home_score, uint64_t away_score) {
    if (auto match_itr = matches.find(id); match_itr != matches.end()) {
        match_itr->second.home_score = home_score;
        match_itr->second.away_score = away_score;
        return true;
    }
    return false;
}

void Scoreboard::end_match(MatchId id) {
    matches.erase(id);
}

std::vector<detail::Match> Scoreboard::summary() const {
    using std::ranges::views::values;

    std::vector<detail::Match> summary(values(matches).begin(), values(matches).end());
    std::sort(summary.begin(), summary.end());

    // for debugging
    for (const auto& match: summary) {
        std::cout << match << std::endl;
    }

    return summary;
}
