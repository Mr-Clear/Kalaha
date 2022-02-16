#pragma once

#include "Game/PlayerNumber.h"

#include <set>

class AbstractBoard;
class Pit;

class AbstractPlayer
{
public:
    AbstractPlayer(PlayerNumber number);
    virtual ~AbstractPlayer() = default;

    [[nodiscard]] PlayerNumber playerNumber() const;
    [[nodiscard]] virtual Pit selectHouse(const AbstractBoard &board) const = 0;

protected:
    [[nodiscard]] std::set<Pit> getOptions(const AbstractBoard &board) const;

private:
    PlayerNumber m_number;
};
