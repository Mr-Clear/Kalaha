#pragma once

#include "Game/PlayerNumber.h"

#include <set>

class AbstractBoard;
class Pit;

class AbstractPlayer
{
public:
    virtual ~AbstractPlayer() = default;

    [[nodiscard]] virtual Pit selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const = 0;

protected:
    [[nodiscard]] std::set<Pit> getOptions(const AbstractBoard &board, PlayerNumber playerNumber) const;
};
