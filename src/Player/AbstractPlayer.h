#pragma once

#include "Game/PlayerNumber.h"

#include <set>

class AbstractBoard;
class Pit;

class AbstractPlayer
{
public:
    explicit AbstractPlayer(const std::string &name);
    virtual ~AbstractPlayer() = default;

    [[nodiscard]] virtual Pit selectHouse(const AbstractBoard &board, PlayerNumber playerNumber) const = 0;

    [[nodiscard]] const std::string &name() const;

protected:
    [[nodiscard]] std::set<Pit> getOptions(const AbstractBoard &board, PlayerNumber playerNumber) const;

private:
    const std::string m_name;
};
