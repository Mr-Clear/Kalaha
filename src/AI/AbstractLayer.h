#pragma once


class AbstractLayer
{
public:
    [[nodiscard]] virtual int size() const = 0;
    [[nodiscard]] virtual float operator[](int index) const = 0;
};

