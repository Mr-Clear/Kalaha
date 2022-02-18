#pragma once

#include "Game/AbstractBoard.h"
#include "Game/Pit.h"
#include "Game/Rules.h"

#include <gtest/gtest_prod.h>
#include <vector>

class Board : public AbstractBoard
{
public:
    explicit Board(const Rules &rules);
    Board(const AbstractBoard &o);

    [[nodiscard]] int numberOfHouses() const override;
    [[nodiscard]] int storeId() const override;
    [[nodiscard]] int seedCount(const Pit &pit) const override;

    bool isHouse(const Pit &pit) const;
    bool isStore(const Pit &pit) const;
    bool isPlayersStore(const Pit &pit, PlayerNumber player) const;
    Pit oppositeHouse(const Pit &pit) const;

    Pit nextPit(const Pit &pit) const;
    Pit previousPit(const Pit &pit) const;

    std::optional<PlayerNumber> saw(const Pit &startPit) override;
    [[nodiscard]] std::optional<Turn> lastTurn() const override;
    std::optional<PlayerNumber> moveRemainingSeedsToStore() override;

    class Iterator
    {
    public:
        Iterator(int numberOfHouses, const Pit &currentPit, bool end);
        friend auto operator<=>(const Iterator&, const Iterator&) = default;
        Iterator& operator++();
        const Pit &operator *() const;

    private:
        int m_numberOfHouses;
        Pit m_currentPit;
        bool m_end;
    };
    Iterator begin() const;
    Iterator end() const;

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

