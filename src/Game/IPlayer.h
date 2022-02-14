#pragma once

class IBoard;
class Pit;

class IPlayer
{
public:
    virtual ~IPlayer() = default;

    [[nodiscard]] virtual Pit selectHouse(const IBoard &board) const = 0;
};
