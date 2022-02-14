#pragma once

#include "Game/Pit.h"
#include "Game/PlayerNumber.h"

#include <optional>
#include <vector>

#include <unordered_set>

class IBoard
{
public:
    struct Turn
    {
        std::optional<PlayerNumber> player;
        std::optional<Pit> selectedPit;
        std::unordered_set<Pit> changedPits;
    };

    [[nodiscard]] virtual int numberOfHouses() const = 0;
    [[nodiscard]] virtual Pit pit(PlayerNumber player, int pitNumber) const = 0;
    [[nodiscard]] virtual Pit house(PlayerNumber player, int houseNumber) const = 0;
    [[nodiscard]] virtual Pit store(PlayerNumber player) const = 0;
    [[nodiscard]] virtual int seedCount(const Pit &pit) const = 0;

    virtual std::optional<PlayerNumber> saw(const Pit &startPit) = 0;
    [[nodiscard]] virtual std::optional<Turn> lastTurn() const = 0;

    virtual std::optional<PlayerNumber> moveRemainingSeedsToStore() = 0;
};

class Board : public IBoard
{
public:
    Board(int numberOfHouses, int startSeedsPerHouse);

    [[nodiscard]] int numberOfHouses() const override;
    [[nodiscard]] Pit pit(PlayerNumber player, int pitNumber) const override;
    [[nodiscard]] Pit house(PlayerNumber player, int houseNumber) const override;
    [[nodiscard]] Pit store(PlayerNumber player) const override;
    [[nodiscard]] int seedCount(const Pit &pit) const override;

    std::optional<PlayerNumber> saw(const Pit &startPit) override;
    [[nodiscard]] std::optional<Turn> lastTurn() const override;

    std::optional<PlayerNumber> moveRemainingSeedsToStore() override;

private:
    const int m_numberOfHouses;
    std::vector<int> m_seedNumbers;
    std::optional<Turn> m_lastTurn;

    [[nodiscard]] int arrayIndex(const Pit &pit) const;
    void incrementSeedCount(const Pit &pit);
    void addSeeds(const Pit &pit, int seedNumber);
    void clearSeedCount(const Pit &pit);
    void checkAndHandleCapture(const Pit &pit, PlayerNumber player);
    bool checkForGameEnd() const;
    Pit distributeSeeds(Pit pit, int seedCount);
};

