#pragma once

#include "Game/AbstractBoard.h"
#include "Game/Pit.h"

#include <gtest/gtest_prod.h>
#include <vector>

class Board : public AbstractBoard
{
public:
    Board(int numberOfHouses, int startSeedsPerHouse);
    Board(const AbstractBoard &o);

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

    FRIEND_TEST(BoardTest, constructor);
    FRIEND_TEST(BoardTest, saw);
    FRIEND_TEST(BoardTest, moveRemainingSeedsToStore);
    Board(const std::vector<int> &seedNumbers);

    [[nodiscard]] int arrayIndex(const Pit &pit) const;
    void incrementSeedCount(const Pit &pit);
    void addSeeds(const Pit &pit, int seedNumber);
    void clearSeedCount(const Pit &pit);
    void checkAndHandleCapture(const Pit &pit, PlayerNumber player);
    bool checkForGameEnd() const;
    Pit distributeSeeds(Pit pit, int seedCount);
};

