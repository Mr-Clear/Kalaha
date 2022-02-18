#pragma once

#include "PlayerNumber.h"

#include <gtest/gtest_prod.h>

class AbstractBoard;

class Pit
{
public:
    Pit(PlayerNumber player, int number);

    friend auto operator<=>(const Pit&, const Pit&) = default;

    [[nodiscard]] PlayerNumber player() const;
    [[nodiscard]] int number() const;

private:
    PlayerNumber m_player;
    int m_number;
};

namespace std {
template <>
struct hash<Pit>
{
    size_t operator()(const Pit &pit) const;
};
}

std::ostream& operator<<(std::ostream& os, const Pit& pit);
