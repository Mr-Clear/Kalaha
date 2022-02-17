#include "Competition.h"

Competition::Competition(const Rules &rules, AbstractPlayer &playerOne, AbstractPlayer &playerTwo)
{

}

Competition::Outcome Competition::runOnce()
{
    return {{5, 3}, PlayerNumber::One, 5};
}

std::ostream &operator<<(std::ostream &os, const Competition::Outcome &o)
{
    return os << "Outcome(Winner: " << o.winner << ", Score: (" << o.seeds.first << " - " << o.seeds.second << "), Rounds: " << o.playedRounds << ")";
}
