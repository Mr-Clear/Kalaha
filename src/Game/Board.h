#pragma once

#include "Game/Pit.h"
#include "Game/Player.h"

#include <optional>
#include <vector>

class Board
{
public:
    Board(int numberOfHouses, int startSeedsPerHouse);

    [[nodiscard]] int numberOfHouses() const;
    [[nodiscard]] Pit pit(Player player, int pitNumber) const;
    [[nodiscard]] Pit house(Player player, int houseNumber) const;
    [[nodiscard]] Pit store(Player player) const;
    [[nodiscard]] int seedCount(const Pit &pit) const;

    std::optional<Player> saw(const Pit &startPit);

    void moveRemainingSeedsToStore();

private:
    const int m_numberOfHouses;
    std::vector<int> m_seedNumbers;

    [[nodiscard]] int arrayIndex(const Pit &pit) const;
    void incrementSeedCount(const Pit &pit);
    void addSeeds(const Pit &pit, int seedNumber);
    void clearSeedCount(const Pit &pit);
    void checkAndHandleEmptyOwnHouse(const Pit &pit, Player player);
    bool checkForGameEnd();
    Pit distributeSeeds(Pit pit, int seedCount);
};

