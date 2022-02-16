#pragma once

#include "Game/Pit.h"
#include "Game/PlayerNumber.h"

#include <optional>
#include <unordered_set>

class AbstractBoard
{
public:
    struct Turn
    {
        std::optional<PlayerNumber> player;
        std::optional<Pit> selectedPit;
        std::unordered_set<Pit> changedPits;
    };

    virtual ~AbstractBoard() = default;

    [[nodiscard]] virtual int numberOfHouses() const = 0;
    [[nodiscard]] virtual Pit pit(PlayerNumber player, int pitNumber) const = 0;
    [[nodiscard]] virtual Pit house(PlayerNumber player, int houseNumber) const = 0;
    [[nodiscard]] virtual Pit store(PlayerNumber player) const = 0;
    [[nodiscard]] virtual int seedCount(const Pit &pit) const = 0;

    virtual std::optional<PlayerNumber> saw(const Pit &startPit) = 0;
    [[nodiscard]] virtual std::optional<Turn> lastTurn() const = 0;
    virtual std::optional<PlayerNumber> moveRemainingSeedsToStore() = 0;

    void print(std::ostream &stream, int intWidth = 2) const;
};
