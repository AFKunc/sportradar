#pragma once

#include <map>
#include <optional>
#include <string>
#include <vector>

// Convenience types
using MatchId = uint64_t;

namespace detail {

struct Match {
    MatchId id;
    std::string home_name;
    std::string away_name;
    unsigned home_score = 0;
    unsigned away_score = 0;

    uint64_t total_score() const;

    bool operator<(const Match& other) const;
};

}// namespace

namespace sbd {

class Scoreboard {
public:
    std::optional<MatchId> start_match(std::string home_name, std::string away_name);

    bool is_match_valid(std::string home_name, std::string away_name) const;

    bool update_match(MatchId id, uint64_t home_score, uint64_t away_score);

    void end_match(MatchId id);

    std::vector<detail::Match> summary() const;

private:
    MatchId next_id = 0;
    std::map<MatchId, detail::Match> matches;
};

}// namespace sbd