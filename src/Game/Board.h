#pragma once

#include "Game/Pit.h"
#include "Game/Player.h"

#include <optional>
#include <vector>

class IBoard
{
public:
    [[nodiscard]] virtual int numberOfHouses() const = 0;
    [[nodiscard]] virtual Pit pit(Player player, int pitNumber) const = 0;
    [[nodiscard]] virtual Pit house(Player player, int houseNumber) const = 0;
    [[nodiscard]] virtual Pit store(Player player) const = 0;
    [[nodiscard]] virtual int seedCount(const Pit &pit) const = 0;

    virtual std::optional<Player> saw(const Pit &startPit) = 0;

    virtual void moveRemainingSeedsToStore() = 0;
};

class Board : public IBoard
{
public:
    Board(int numberOfHouses, int startSeedsPerHouse);

    [[nodiscard]] int numberOfHouses() const override;
    [[nodiscard]] Pit pit(Player player, int pitNumber) const override;
    [[nodiscard]] Pit house(Player player, int houseNumber) const override;
    [[nodiscard]] Pit store(Player player) const override;
    [[nodiscard]] int seedCount(const Pit &pit) const override;

    std::optional<Player> saw(const Pit &startPit) override;

    void moveRemainingSeedsToStore() override;

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

