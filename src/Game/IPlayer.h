#pragma once

class IBoard;
class Pit;

class IPlayer
{
public:
    [[nodiscard]] virtual Pit selectHouse(const IBoard &board) const = 0;
};
