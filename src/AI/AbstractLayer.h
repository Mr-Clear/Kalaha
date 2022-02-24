#pragma once


class AbstractLayer
{
public:
    virtual ~AbstractLayer() = default;
    [[nodiscard]] virtual int outputSize() const = 0;
};

