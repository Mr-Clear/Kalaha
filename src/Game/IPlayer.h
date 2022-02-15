#pragma once

#include "Game/PlayerNumber.h"

#include <set>

class IBoard;
class Pit;

class IPlayer
{
public:
    IPlayer(PlayerNumber number);
    virtual ~IPlayer() = default;

    [[nodiscard]] PlayerNumber playerNumber() const;
    [[nodiscard]] virtual Pit selectHouse(const IBoard &board) const = 0;

protected:
    [[nodiscard]] std::set<int> getOptions(const IBoard &board) const;

private:
    PlayerNumber m_number;
};
